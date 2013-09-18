/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

this.NFC_REQUEST_CONFIG = 0;
this.NFC_REQUEST_CONNECT = 1;
this.NFC_REQUEST_CLOSE = 2;
this.NFC_REQUEST_GET_DETAILS = 3;
this.NFC_REQUEST_READ_NDEF = 4;
this.NFC_REQUEST_WRITE_NDEF = 5;
this.NFC_REQUEST_MAKE_NDEF_READ_ONLY = 6;

this.NFC_RESPONSE_GENERAL = 1000;
this.NFC_RESPONSE_CONFIG = 1001;
this.NFC_RESPONSE_READ_NDEF_DETAILS = 1002;
this.NFC_RESPONSE_READ_NDEF = 1003;

this.NFC_NOTIFICATION_INITIALIZED = 2000;
this.NFC_NOTIFICATION_TECH_DISCOVERED = 2001;
this.NFC_NOTIFICATION_TECH_LOST = 2002;

this.NFC_TECHS = {
  0:'P2P',
  1:'NDEF',
  2:'NDEF_FORMATTABLE',
  3:'NFC_A',
  9:'MIFARE_ULTRALIGHT'
};

