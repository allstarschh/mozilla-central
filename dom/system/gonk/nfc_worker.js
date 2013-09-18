/* Copyright 2012 Mozilla Foundation and Mozilla contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Copyright © 2013, Deutsche Telekom, Inc. */

"use strict";

importScripts("systemlibs.js", "nfc_consts.js");
importScripts("resource://gre/modules/workers/require.js");

// We leave this as 'undefined' instead of setting it to 'false'. That
// way an outer scope can define it to 'true' (e.g. for testing purposes)
// without us overriding that here.
let DEBUG = true;

let Buf = {
  __proto__: (function(){
    return require("resource://gre/modules/workers/worker_buf.js").Buf;
  })(),

  init: function init() {
    this._init();
  },

  /**
   * Process one parcel.
   */
  processParcel: function processParcel() {
    let pduType = this.readUint32();
    Nfc.handleParcel(pduType, this.readAvailable);
  },

  /**
   * Start a new outgoing parcel.
   *
   * @param type
   *        Integer specifying the request type.
   * @param options [optional]
   *        Object containing information about the request, e.g. the
   *        original main thread message object that led to the RIL request.
   */
  newParcel: function newParcel(type, options) {
    if (DEBUG) debug("New outgoing parcel of type " + type);

    // We're going to leave room for the parcel size at the beginning.
    this.outgoingIndex = this.PARCEL_SIZE_SIZE;
    this.writeUint32(type);
  },

  simpleRequest: function simpleRequest(type) {
    this.newParcel(type);
    this.sendParcel();
  },

  onSendParcel: function onSendParcel(parcel) {
    postNfcMessage(parcel);
  }
};


/**
 * Provide a high-level API representing NFC capabilities. This is
 * where JSON is sent and received from and translated into API calls.
 * For the most part, this object is pretty boring as it simply translates
 * between method calls and NFC JSON. Somebody's gotta do the job...
 */
let Nfc = {
  /**
   * Handle incoming messages from the main UI thread.
   *
   * @param message
   *        Object containing the message. Messages are supposed
   */
  handleDOMMessage: function handleMessage(message) {
    if (DEBUG) debug("Received DOM message " + JSON.stringify(message));
    let method = this[message.type];
    if (typeof method != "function") {
      if (DEBUG) {
        debug("Don't know what to do with message " + JSON.stringify(message));
      }
      return;
    }
    method.call(this, message);
  },

  /**
   * Retrieve metadata describing the NDEF formatted data, if present.
   */
  ndefDetails: function ndefDetails(message) {
    postNfcMessage(JSON.stringify(message.content));
  },

  /**
   * Read and return NDEF data, if present.
   */
  ndefRead: function ndefRead(message) {
    Buf.newParcel(NFC_REQUEST_READ_NDEF /*, message*/);
    //TODO sessionId
    Buf.sendParcel();
  },

  /**
   * Write to a target that accepts NDEF formattable data
   */
  ndefWrite: function ndefWrite(message) {
    debug("ndefWrite message="+JSON.stringify(message));
    Buf.newParcel(NFC_REQUEST_WRITE_NDEF/*, message*/);
    let records = message.content.content.records;
    let numRecords = records.length;
    debug("ndefWrite numRecords="+numRecords);
    Buf.writeUint32(numRecords);

    for (let i = 0; i < numRecords; i++) {
      let record = records[i];
      debug("tnf="+record.tnf);
      Buf.writeUint32(record.tnf);

      let typeLength = record.type.length;
      debug("typeLength="+typeLength);
      Buf.writeUint32(typeLength);
      for (let j = 0; j < typeLength; j++) {
        debug("type ["+j+"]=  "+record.type[j]);
        debug("type ["+j+"]=  "+record.type.charCodeAt(j));
        Buf.writeUint32(record.type.charCodeAt(j));
      }

      let idLength = record.id.length;
      debug("idLength="+idLength);
      Buf.writeUint32(idLength);
      for (let j = 0; j < idLength; j++) {
        debug("id ["+j+"]=  "+record.id[j]);
        debug("id ["+j+"]=  "+record.id.charCodeAt(j));
        Buf.writeUint32(record.id.charCodeAt(j));
      }

      let payloadLength = record.payload && record.payload.length;
      debug("payloadLength="+payloadLength);
      Buf.writeUint32(payloadLength);
      for (let j = 0; j < payloadLength; j++) {
        debug("payload ["+j+"]=  "+record.payload[j]);
        debug("payload ["+j+"]=  "+record.payload.charCodeAt(j));
        Buf.writeUint32(record.payload.charCodeAt(j));
      }
    }

    Buf.sendParcel();
  },

  /**
   * Make the NFC NDEF tag permenantly read only
   */
  ndefMakeReadOnly: function ndefMakeReadOnly(message) {
//    postNfcMessage(JSON.stringify(message.content));
  },

  /**
   * P2P NDEF message push between a pair of NFC devices.
   */
  ndefPush: function ndefPush(message) {
//    postNfcMessage(JSON.stringify(message.content));
  },

  /**
   * Retrieve metadata describing the NfcA tag type, if present.
   */
  nfcATagDetails: function nfcATagDetails(message) {
//    postNfcMessage(JSON.stringify(message.requestId)); // Just request ID.
  },

  /**
   *  Excahnge PDUs with the NFC target. Request ID is required.
   */
  nfcATagTransceive: function nfcATagTransceive(message) {
//    postNfcMessage(JSON.stringify(message.content));
  },

  /**
   * Open a connection to the NFC target. Request ID is required.
   */
  connect: function connect(message) {
    debug("connect message="+JSON.stringify(message));
    Buf.newParcel(NFC_REQUEST_CONNECT, message);
    Buf.writeUint32(message.content.techType);
    Buf.sendParcel();
//    postNfcMessage(JSON.stringify(message.content));
  },

  /**
   * NFC Configuration
   */
  configRequest: function configRequest(message) {
    debug("config:"+JSON.stringify(message.content));
  },

  /**
   * Close connection to the NFC target. Request ID is required.
   */
  close: function close(message) {
    Buf.newParcel(2, message);
    Buf.sendParcel();
  },

  handleParcel: function handleParcel(request_type, length) {
    let method = this[request_type];
    if (typeof method == "function") {
      if (DEBUG) debug("Handling parcel as " + method.name);
      method.call(this, length);
    }
  },

  /**
   * Send messages to the main UI thread.
   */
  sendDOMMessage: function sendDOMMessage(message) {
    postMessage(message);
  }
};
Nfc[NFC_REQUEST_CONNECT] = function NFC_REQUEST_CONNECT(length, options) {
  debug("NFC_CONNECT_REQUEST options="+JSON.stringify(options));
  options.requestId = options.content.requestId;
  options.sessionId = "12345";
  options.content.status = "OK";
  //TODO
  options.type = "ConnectResponse";
  this.sendDOMMessage(options);
};
Nfc[NFC_REQUEST_READ_NDEF] = function NFC_REQUEST_READ_NDEF(length, options) {
  debug("NFC_READ_NDEF_REQUEST options="+JSON.stringify(options));
  let numOfRecords = Buf.readUint32();
  debug("numOfRecords="+numOfRecords);
  let records = [];
  for (let i = 0; i < numOfRecords; i++) {
//    let tnf = Buf.readUint8();
    let tnf = Buf.readUint32();
    debug("tnf="+tnf.toString(16));
    let typeLength = Buf.readUint32();
    debug("typeLength="+typeLength);
//    let type = Buf.readUint8Array(typeLength);
    let type = [];
    for (let i = 0; i < typeLength; i++) {
        type.push(Buf.readUint32());
    }
//    let type = Buf.readUint32Array(typeLength);
    debug("type="+type);

//    let idLength = Buf.readUint8();
    let idLength = Buf.readUint32();
    debug("idLength="+idLength);
//    let id = Buf.readUint8Array(idLength);
    let id = [];
    for (let i = 0; i < idLength; i++) {
        id.push(Buf.readUint32());
    }
    debug("id="+id);

    let payloadLength = Buf.readUint32();
    debug("payloadLength="+payloadLength);
    let payload = [];
    for (let i = 0; i < payloadLength; i++) {
        payload.push(Buf.readUint32());
    }

    debug("payload="+payload);

    records.push({tnf: tnf,
                  type: type,
                  id: id,
                  payload: payload});
  }

  options.requestId = options.content.requestId;
  options.sessionId = "12345";
  options.content.records = records;
  options.type = "NDEFReadResponse";
  this.sendDOMMessage(options);
};

Nfc[NFC_NOTIFICATION_INITIALIZED] = function NFC_NOTIFICATION_INITIALIZED (length) {
  let status = Buf.readUint32();
  let majorVersion = Buf.readUint32();
  let minorVersion = Buf.readUint32();
  debug("NFC_NOTIFICATION_INITIALIZED status:"+status+" major:"+majorVersion+" minor:"+minorVersion);
};

Nfc[NFC_NOTIFICATION_TECH_DISCOVERED] = function NFC_NOTIFICATION_TECH_DISCOVERED(length) {
  debug("NFC_NOTIFICATION_TECH_DISCOVERED");
  let sessionId = Buf.readUint32();
  let num = Buf.readUint32();

  let techs = [];
  for (let i = 0; i < num; i++) {
    techs.push(NFC_TECHS[Buf.readUint8()]);
  }
  debug("techs = "+techs);
  this.sendDOMMessage({type: "techDiscovered",
                       sessionId: sessionId,
                       content: { tech: techs}
                       });
};

/**
 * Global stuff.
 */

if (!this.debug) {
  // Debugging stub that goes nowhere.
  this.debug = function debug(message) {
    dump("Nfc Worker: " + message + "\n");
  };
}

// Initialize buffers. This is a separate function so that unit tests can
// re-initialize the buffers at will.
Buf.init();

function onNfcMessage(data) {
  Buf.processIncoming(data);
};

onmessage = function onmessage(event) {
  Nfc.handleDOMMessage(event.data);
};

onerror = function onerror(event) {
  debug("OnError: event: " + JSON.stringify(event));
  debug("NFC Worker error " + event.message + " " + event.filename + ":" +
        event.lineno + ":\n");
};

