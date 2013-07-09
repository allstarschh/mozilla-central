/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */
interface CRMFObject;
//interface CRMFObject;

[NoInterfaceObject]
interface RandomSource {
  [Throws]
  ArrayBufferView getRandomValues(ArrayBufferView array);
};

[NoInterfaceObject]
interface CryptoLegacy {
  readonly attribute DOMString version;
  attribute boolean enableSmartCardEvents;

  CRMFObject generateCRMFRequest(/* ... */);
  DOMString importUserCertificates(DOMString nickname,
                                   DOMString cmmfResponse,
                                   boolean doForcedBackup);
  DOMString popChallengeResponse(DOMString challenge);
  DOMString random(long numBytes);
  DOMString signText(DOMString stringToSign,
                     DOMString caOption /* ... */);
  void logout();
  void disableRightClick();
};

interface Crypto {
};

Crypto implements RandomSource;
Crypto implements CryptoLegacy;
