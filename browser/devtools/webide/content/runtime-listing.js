/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

const Cu = Components.utils;
const {require} = Cu.import("resource://gre/modules/devtools/Loader.jsm", {}).devtools;
const {AppManager} = require("devtools/webide/app-manager");
const RuntimeList = require("devtools/webide/runtime-list");

let runtimeList = new RuntimeList(window, window.parent);

window.addEventListener("load", function onLoad() {
  window.removeEventListener("load", onLoad);
  AppManager.on("app-manager-update", onAppManagerUpdate);
  document.getElementById("runtime-panel-nousbdevice").onclick = ShowTroubleShooting;
  document.getElementById("runtime-panel-installsimulator").onclick = ShowAddons;
  document.getElementById("runtime-screenshot").onclick = TakeScreenshot;
  document.getElementById("runtime-permissions").onclick = ShowPermissionsTable;
  document.getElementById("runtime-details").onclick = ShowRuntimeDetails;
  document.getElementById("runtime-disconnect").onclick = DisconnectRuntime;
  document.getElementById("runtime-preferences").onclick = ShowDevicePreferences;
  document.getElementById("runtime-settings").onclick = ShowSettings;
  runtimeList.update();
  runtimeList.updateCommands();
}, true);

window.addEventListener("unload", function onUnload() {
  window.removeEventListener("unload", onUnload);
  runtimeList = null;
  AppManager.off("app-manager-update", onAppManagerUpdate);
});

function onAppManagerUpdate(event, what) {
  switch (what) {
    case "runtimelist":
      runtimeList.update();
      runtimeList.autoConnectRuntime();
      break;
    case "connection":
      runtimeList.updateRuntimeButton();
      runtimeList.updateCommands();
      break;
    case "runtime-details":
      runtimeList.updateRuntimeButton();
      break;
    case "runtime-changed":
      runtimeList.updateRuntimeButton();
      runtimeList.saveLastConnectedRuntime();
      break;
    case "project":
    case "project-validated":
    case "project-is-not-running":
    case "project-is-running":
    case "list-tabs-response":
      runtimeList.updateCommands();
      break;
  };
}

function ShowTroubleShooting() {
  runtimeList.showTroubleShooting();
}

function ShowAddons() {
  runtimeList.showAddons();
}

function TakeScreenshot() {
  runtimeList.takeScreenshot();
}

function ShowRuntimeDetails() {
  runtimeList.showRuntimeDetails();
}

function ShowPermissionsTable() {
  runtimeList.showPermissionsTable();
}

function ShowDevicePreferences() {
  runtimeList.showDevicePreferences();
}

function ShowSettings() {
  runtimeList.showSettings();
}

function DisconnectRuntime() {
  runtimeList.disconnectRuntime();
}
