/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

const {Cu} = require("chrome");

const {Services} = Cu.import("resource://gre/modules/Services.jsm");
const {AppProjects} = require("devtools/app-manager/app-projects");
const {AppManager} = require("devtools/webide/app-manager");
const {Promise: promise} = Cu.import("resource://gre/modules/Promise.jsm", {});
const EventEmitter = require("devtools/toolkit/event-emitter");
const {RuntimeScanners, WiFiScanner} = require("devtools/webide/runtimes");
const {Devices} = Cu.import("resource://gre/modules/devtools/Devices.jsm");
const {Task} = Cu.import("resource://gre/modules/Task.jsm", {});
const utils = require("devtools/webide/utils");

const HELP_URL = "https://developer.mozilla.org/docs/Tools/WebIDE/Troubleshooting";

const Strings = Services.strings.createBundle("chrome://browser/locale/devtools/webide.properties");

let RuntimeList;

module.exports = RuntimeList = function(window, parentWindow) {
  EventEmitter.decorate(this);
  this._doc = window.document;
  this._UI = parentWindow.UI;
  this._Cmds = parentWindow.Cmds;
  this._parentWindow = parentWindow;
  this._panelNodeEl = "toolbarbutton";
  this._sidebarsEnabled = Services.prefs.getBoolPref("devtools.webide.sidebars");

  if (this._sidebarsEnabled) {
    this._panelNodeEl = "button";
  }

  return this;
};

RuntimeList.prototype = {
  get doc() {
    return this._doc;
  },

  get sidebarsEnabled() {
    return this._sidebarsEnabled;
  },

  get lastConnectedRuntime() {
    return Services.prefs.getCharPref("devtools.webide.lastConnectedRuntime");
  },

  set lastConnectedRuntime(runtime) {
    Services.prefs.setCharPref("devtools.webide.lastConnectedRuntime", runtime);
  },

  autoConnectRuntime: function() {
    // Automatically reconnect to the previously selected runtime,
    // if available and has an ID and feature is enabled
    if (AppManager.selectedRuntime ||
        !Services.prefs.getBoolPref("devtools.webide.autoConnectRuntime") ||
        !this.lastConnectedRuntime) {
      return;
    }
    let [_, type, id] = this.lastConnectedRuntime.match(/^(\w+):(.+)$/);

    type = type.toLowerCase();

    // Local connection is mapped to AppManager.runtimeList.other array
    if (type == "local") {
      type = "other";
    }

    // We support most runtimes except simulator, that needs to be manually
    // launched
    if (type == "usb" || type == "wifi" || type == "other") {
      for (let runtime of AppManager.runtimeList[type]) {
        // Some runtimes do not expose an id and don't support autoconnect (like
        // remote connection)
        if (runtime.id == id) {
          // Only want one auto-connect attempt, so clear last runtime value
          this.lastConnectedRuntime = "";
          this.connectToRuntime(runtime);
        }
      }
    }
  },

  connectToRuntime: function(runtime) {
    let name = runtime.name;
    let promise = AppManager.connectToRuntime(runtime);
    promise.then(() => this._UI.initConnectionTelemetry())
           .catch(() => {
             // Empty rejection handler to silence uncaught rejection warnings
             // |busyUntil| will listen for rejections.
             // Bug 1121100 may find a better way to silence these.
           });
    return this._UI.busyUntil(promise, "Connecting to " + name);
  },

  updateRuntimeButton: function() {
    let labelNode = this._parentWindow.document.querySelector("#runtime-panel-button > .panel-button-label");
    if (!AppManager.selectedRuntime) {
      labelNode.setAttribute("value", Strings.GetStringFromName("runtimeButton_label"));
    } else {
      let name = AppManager.selectedRuntime.name;
      labelNode.setAttribute("value", name);
    }
  },

  saveLastConnectedRuntime: function () {
    if (AppManager.selectedRuntime &&
        AppManager.selectedRuntime.id !== undefined) {
      this.lastConnectedRuntime = AppManager.selectedRuntime.type + ":" +
                                  AppManager.selectedRuntime.id;
    } else {
      this.lastConnectedRuntime = "";
    }
  },

  showTroubleShooting: function() {
    this._UI.openInBrowser(HELP_URL);
  },

  showAddons: function() {
    this._UI.selectDeckPanel("addons");
  },

  takeScreenshot: function() {
    return this._UI.busyUntil(AppManager.deviceFront.screenshotToDataURL().then(longstr => {
       return longstr.string().then(dataURL => {
         longstr.release().then(null, console.error);
         this._UI.openInBrowser(dataURL);
       });
    }), "taking screenshot");
  },

  showRuntimeDetails: function() {
    this._UI.selectDeckPanel("runtimedetails");
  },

  showPermissionsTable: function() {
    this._UI.selectDeckPanel("permissionstable");
  },

  showDevicePreferences: function() {
    this._UI.selectDeckPanel("devicepreferences");
  },

  showSettings: function() {
    this._UI.selectDeckPanel("devicesettings");
  },

  disconnectRuntime: function() {
    let self = this;
    let disconnecting = Task.spawn(function*() {
      yield self._UI.destroyToolbox();
      yield AppManager.disconnectRuntime();
    });
    return this._UI.busyUntil(disconnecting, "disconnecting from runtime");
  },

  updateCommands: function() {
    let doc = this._doc;
    let parentDoc = this._parentWindow.document;

    // Runtime commands
    let screenshotCmd = doc.querySelector("#runtime-screenshot");
    let permissionsCmd = doc.querySelector("#runtime-permissions");
    let detailsCmd = doc.querySelector("#runtime-details");
    let disconnectCmd = doc.querySelector("#runtime-disconnect");
    let devicePrefsCmd = doc.querySelector("#runtime-preferences");
    let settingsCmd = doc.querySelector("#runtime-settings");

    if (parentDoc.querySelector("window").classList.contains("busy")) {
      disconnectCmd.setAttribute("disabled", "true");
      permissionsCmd.setAttribute("disabled", "true");
      screenshotCmd.setAttribute("disabled", "true");
      detailsCmd.setAttribute("disabled", "true");
      devicePrefsCmd.setAttribute("disabled", "true");
      settingsCmd.setAttribute("disabled", "true");
      parentDoc.querySelector("#cmd_removeProject").setAttribute("disabled", "true");
      parentDoc.querySelector("#cmd_play").setAttribute("disabled", "true");
      parentDoc.querySelector("#cmd_stop").setAttribute("disabled", "true");
      parentDoc.querySelector("#cmd_toggleToolbox").setAttribute("disabled", "true");
      return;
    }

    parentDoc.querySelector("#cmd_showRuntimePanel").removeAttribute("disabled");

    // Action commands
    let playCmd = parentDoc.querySelector("#cmd_play");
    let stopCmd = parentDoc.querySelector("#cmd_stop");
    let debugCmd = parentDoc.querySelector("#cmd_toggleToolbox");
    let playButton = parentDoc.querySelector('#action-button-play');

    if (!AppManager.selectedProject || !AppManager.connected) {
      playCmd.setAttribute("disabled", "true");
      stopCmd.setAttribute("disabled", "true");
      debugCmd.setAttribute("disabled", "true");
    } else {
      let isProjectRunning = AppManager.isProjectRunning();
      if (isProjectRunning) {
        playButton.classList.add("reload");
        stopCmd.removeAttribute("disabled");
        debugCmd.removeAttribute("disabled");
      } else {
        playButton.classList.remove("reload");
        stopCmd.setAttribute("disabled", "true");
        debugCmd.setAttribute("disabled", "true");
      }

      // If connected and a project is selected
      if (AppManager.selectedProject.type == "runtimeApp") {
        playCmd.removeAttribute("disabled");
      } else if (AppManager.selectedProject.type == "tab") {
        playCmd.removeAttribute("disabled");
        stopCmd.setAttribute("disabled", "true");
      } else if (AppManager.selectedProject.type == "mainProcess") {
        playCmd.setAttribute("disabled", "true");
        stopCmd.setAttribute("disabled", "true");
      } else {
        if (AppManager.selectedProject.errorsCount == 0 &&
            AppManager.runtimeCanHandleApps()) {
          playCmd.removeAttribute("disabled");
        } else {
          playCmd.setAttribute("disabled", "true");
        }
      }
    }

    // Remove command
    let removeCmdNode = parentDoc.querySelector("#cmd_removeProject");
    if (AppManager.selectedProject) {
      removeCmdNode.removeAttribute("disabled");
    } else {
      removeCmdNode.setAttribute("disabled", "true");
    }

    let runtimePanelButton = parentDoc.querySelector("#runtime-panel-button");
    if (AppManager.connected) {
      if (AppManager.deviceFront) {
        detailsCmd.removeAttribute("disabled");
        permissionsCmd.removeAttribute("disabled");
        screenshotCmd.removeAttribute("disabled");
      }
      if (AppManager.preferenceFront) {
        devicePrefsCmd.removeAttribute("disabled");
      }
      if (AppManager.settingsFront) {
        settingsCmd.removeAttribute("disabled");
      }
      disconnectCmd.removeAttribute("disabled");
      runtimePanelButton.setAttribute("active", "true");
    } else {
      detailsCmd.setAttribute("disabled", "true");
      permissionsCmd.setAttribute("disabled", "true");
      screenshotCmd.setAttribute("disabled", "true");
      disconnectCmd.setAttribute("disabled", "true");
      devicePrefsCmd.setAttribute("disabled", "true");
      settingsCmd.setAttribute("disabled", "true");
      runtimePanelButton.removeAttribute("active");
    }
  },

  update: function() {
    let doc = this._doc;
    let wifiHeaderNode = doc.querySelector("#runtime-header-wifi");

    if (WiFiScanner.allowed) {
      wifiHeaderNode.removeAttribute("hidden");
    } else {
      wifiHeaderNode.setAttribute("hidden", "true");
    }

    let usbListNode = doc.querySelector("#runtime-panel-usb");
    let wifiListNode = doc.querySelector("#runtime-panel-wifi");
    let simulatorListNode = doc.querySelector("#runtime-panel-simulator");
    let otherListNode = doc.querySelector("#runtime-panel-other");
    let noHelperNode = doc.querySelector("#runtime-panel-noadbhelper");
    let noUSBNode = doc.querySelector("#runtime-panel-nousbdevice");

    if (Devices.helperAddonInstalled) {
      noHelperNode.setAttribute("hidden", "true");
    } else {
      noHelperNode.removeAttribute("hidden");
    }

    let runtimeList = AppManager.runtimeList;

    if (runtimeList.usb.length === 0 && Devices.helperAddonInstalled) {
      noUSBNode.removeAttribute("hidden");
    } else {
      noUSBNode.setAttribute("hidden", "true");
    }

    for (let [type, parent] of [
      ["usb", usbListNode],
      ["wifi", wifiListNode],
      ["simulator", simulatorListNode],
      ["other", otherListNode],
    ]) {
      while (parent.hasChildNodes()) {
        parent.firstChild.remove();
      }

      for (let runtime of runtimeList[type]) {
        let panelItemNode = doc.createElement(this._panelNodeEl);
        panelItemNode.className = "panel-item runtime-panel-item-" + type;
        panelItemNode.textContent = runtime.name;
        parent.appendChild(panelItemNode);
        let r = runtime;
        panelItemNode.addEventListener("click", () => {
          this._UI.hidePanels();
          this._UI.dismissErrorNotification();
          this.connectToRuntime(r);
        }, true);
      }
    }
  }
};
