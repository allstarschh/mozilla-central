/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

importScripts("ril_consts.js");

let DEBUG = DEBUG_MSIM_WORKER;

const INDEX_SIZE = 4;
const DATA_SIZE = 4;
const HEADER_SIZE = INDEX_SIZE + DATA_SIZE;

/**
 * Global stuff.
 */
if (!this.debug) {
  this.debug = function debug(message) {
    dump("RIL MSimWorker: " + message + "\n");
  };
}

function onRILMessage(data) {
  debug("MSimWorker onRILMessage length "+data.length);

  let offset = 0, length = data.length;
  while (offset < length) {
    let index = data[offset];
    let size = (data[offset + 1] << 24) |
               (data[offset + 2] << 16) |
               (data[offset + 3] << 8)  |
                data[offset + 4];
    //TODO
    if (index === 1) {
      return;
    }

    let array = data.subarray(offset + HEADER_SIZE, offset + HEADER_SIZE + size);
//    postMessage({
//      rilMessageType: "receiveParcel",
//      parcel: array});
//    offset += size + 5;
  }
};

onmessage = function onmessage(event) {
//  switch (event.data.rilMessageType) {
//    case "sendParcel":
//      let array = new Uint8Array(event.data.parcel.length + INDEX_SIZE);
//      array[0] = event.data.index;
//      array.set(event.data.parcel, INDEX_SIZE);
//      postRILMessage(array);
//      break;
//  }
};

onerror = function onerror(event) {
  debug("RIL MSimWorker error" + event.message + "\n");
};
