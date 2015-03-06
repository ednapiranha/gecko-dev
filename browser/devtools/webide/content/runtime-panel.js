/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

let RuntimePanel = {
  // TODO: Expand function to save toggle state.
  toggle: function(sidebarsEnabled, triggerPopup) {
    RuntimeScanners.scan();

    let deferred = promise.defer();
    let doc = document;

    if (sidebarsEnabled) {
      doc.querySelector("#runtime-listing-panel").setAttribute("sidebar-displayed", true);
      doc.querySelector("#runtime-listing-splitter").setAttribute("sidebar-displayed", true);
      deferred.resolve();
    } else if (triggerPopup) {
      let panel = doc.querySelector("#runtime-panel");
      let anchor = doc.querySelector("#runtime-panel-button > .panel-button-anchor");

      function onPopupShown() {
        panel.removeEventListener("popupshown", onPopupShown);
        deferred.resolve();
      }

      panel.addEventListener("popupshown", onPopupShown);
      panel.openPopup(anchor);
    } else {
      deferred.resolve();
    }

    return deferred.promise;
  }
};
