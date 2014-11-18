/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

const {Cc, Ci, Cu, CC} = require("chrome");
const protocol = require("devtools/server/protocol");
const {Arg, method, RetVal} = protocol;
const {DebuggerServer} = require("devtools/server/main");
const {Promise: promise} = Cu.import("resource://gre/modules/Promise.jsm", {});

Cu.import("resource://gre/modules/FileUtils.jsm");
Cu.import("resource://gre/modules/NetUtil.jsm");
Cu.import("resource://gre/modules/Services.jsm");

let settingsObj = {};
let win = Services.wm.getMostRecentWindow(DebuggerServer.chromeWindowType);
let settingsService = win.navigator.mozSettings;
let settingsFile;

exports.register = function(handle) {
  handle.addGlobalActor(SettingsActor, "settingsActor");
};

exports.unregister = function(handle) {
};

function loadSettingsFile() {
  // Loading resource://app/defaults/settings.json doesn't work because
  // settings.json is not in the omnijar.
  // So we look for the app dir instead and go from here...
  if (settingsFile) {
    return;
  }
  settingsFile = FileUtils.getFile("DefRt", ["settings.json"], false);
  if (!settingsFile || (settingsFile && !settingsFile.exists())) {
    // On b2g desktop builds the settings.json file is moved in the
    // profile directory by the build system.
    settingsFile = FileUtils.getFile("ProfD", ["settings.json"], false);
    if (!settingsFile || (settingsFile && !settingsFile.exists())) {
      console.log("settings.json file does not exist");
    }
  }
}

let SettingsActor = exports.SettingsActor = protocol.ActorClass({
  typeName: "settings",

  getSetting: method(function(name) {
    let deferred = promise.defer();
    let lock = settingsService.createLock();
    let req = lock.get(name);
    req.onsuccess = function() {
      deferred.resolve(req.result[name]);
    };
    req.onerror = function() {
      deferred.reject(req.error);
    };
    return deferred.promise;
  }, {
    request: { value: Arg(0) },
    response: { value: RetVal("json") }
  }),

  setSetting: method(function(name, value) {
    let deferred = promise.defer();
    let data = {};
    data[name] = value;
    let lock = settingsService.createLock();
    let req = lock.set(data);
    req.onsuccess = function() {
      deferred.resolve(true);
    };
    req.onerror = function() {
      deferred.reject(req.error);
    };
    return deferred.promise;
  }, {
    request: { name: Arg(0), value: Arg(1) },
    response: {}
  }),

  _hasUserSetting: function(name, value) {
    if (typeof value === "object") {
      return JSON.stringify(settingsObj[name]) !== JSON.stringify(value);
    }
    return (settingsObj[name] !== value);
  },

  // For tests
  _setSettings: method(function(settings) {
    settingsObj = settings || {};
  }, {
    request: { value: Arg(0) },
    response: {}
  }),

  getAllSettings: method(function() {
    loadSettingsFile();

    if (settingsFile && settingsFile.exists()) {
      let chan = NetUtil.newChannel(settingsFile);
      let stream = chan.open();
      // Obtain a converter to read from a UTF-8 encoded input stream.
      let converter = Cc["@mozilla.org/intl/scriptableunicodeconverter"]
                      .createInstance(Ci.nsIScriptableUnicodeConverter);
      converter.charset = "UTF-8";
      let rawstr = converter.ConvertToUnicode(NetUtil.readInputStreamToString(
                                              stream,
                                              stream.available()) || "");

      try {
        settingsObj = JSON.parse(rawstr);
      } catch(e) {
        if (DEBUG) debug("Error parsing " + settingsFile.path + " : " + e);
        return;
      }
      stream.close();
    }

    let settings = {};
    let self = this;

    let deferred = promise.defer();
    let lock = settingsService.createLock();
    let req = lock.get("*");

    req.onsuccess = function() {
      for (var name in req.result) {
        settings[name] = {
          value: req.result[name],
          hasUserValue: self._hasUserSetting(name, req.result[name])
        };
      }
      deferred.resolve(settings);
    };
    req.onfailure = function() {
      deferred.reject(req.error);
    };

    return deferred.promise;
  }, {
    request: {},
    response: { value: RetVal("json") }
  }),

  clearUserSetting: method(function(name) {
    try {
      this.setSetting(name, settingsObj[name]);
    } catch (e) {
      console.log(e);
    }
  }, {
    request: { name: Arg(0) },
    response: {}
  })
});

let SettingsFront = protocol.FrontClass(SettingsActor, {
  initialize: function(client, form) {
    protocol.Front.prototype.initialize.call(this, client);
    this.actorID = form.settingsActor;
    this.manage(this);
  },
});

const _knownSettingsFronts = new WeakMap();

exports.getSettingsFront = function(client, form) {
  if (!form.settingsActor) {
    return null;
  }
  if (_knownSettingsFronts.has(client)) {
    return _knownSettingsFronts.get(client);
  }
  let front = new SettingsFront(client, form);
  _knownSettingsFronts.set(client, front);
  return front;
};
