/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

const {classes: Cc, interfaces: Ci, utils: Cu, results: Cr} = Components;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");

var RIL = {};
Cu.import("resource://gre/modules/ril_consts.js", RIL);

const DEBUG = RIL.DEBUG_MSIM_RIL;

const MSIMRADIOINTERFACELAYER_CID =
  Components.ID("{ab558c83-f897-48f0-abb5-2dc8a4edfc1c}");

function MSimRadioInterfaceLayer() {
  debug("Starting MSimRIL Worker");
  this.worker = new ChromeWorker("resource://gre/modules/msim_ril_worker.js");
  this.worker.onerror = this.onerror.bind(this);
  this.worker.onmessage = this.onmessage.bind(this);

};
MSimRadioInterfaceLayer.prototype = {
  classID:   MSIMRADIOINTERFACELAYER_CID,
  classInfo: XPCOMUtils.generateCI(
    {classID: MSIMRADIOINTERFACELAYER_CID,
     classDescription: "MSimRadioInterfaceLayer",
     interfaces: [Ci.nsIWorkerHolder, Ci.nsIMSimRadioInterfaceLayer]}),

  QueryInterface: XPCOMUtils.generateQI([Ci.nsIWorkerHolder,
                                         Ci.nsIMSimRadioInterfaceLayer]),

  onerror: function onerror(event) {
    debug("Got an error: " + event.filename + ":" +
          event.lineno + ": " + event.message + "\n");
    event.preventDefault();
  },

  onmessage: function onmessage(event) {
    let message = event.data;
    debug("Received message from worker: " + JSON.stringify(message));
  }
};

const NSGetFactory = XPCOMUtils.generateNSGetFactory([MSimRadioInterfaceLayer]);

let debug;
if (DEBUG) {
  debug = function (s) {
    dump("-*- RadioInterfaceLayer: " + s + "\n");
  };
} else {
  debug = function (s) {};
}
