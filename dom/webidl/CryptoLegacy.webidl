/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */
interface CRMFObject;

[NoInterfaceObject]
interface RandomSource {
  [Throws]
  ArrayBufferView getRandomValues(ArrayBufferView array);
};

[NoInterfaceObject]
interface CryptoLegacy {
  readonly attribute DOMString version;

  [SetterThrows]
  attribute boolean enableSmartCardEvents;

  [Throws]
  CRMFObject generateCRMFRequest(ByteString  reqDN,
                                 ByteString? regToken,
                                 ByteString? authenticator,
                                 ByteString? eaCert,
                                 ByteString  jsCallback,
                                 ByteString... args);

  [Throws]
  DOMString importUserCertificates(DOMString nickname,
                                   DOMString cmmfResponse,
                                   boolean doForcedBackup);

  [Throws]
  DOMString popChallengeResponse(DOMString challenge);

  [Throws]
  DOMString random(long numBytes);

  DOMString signText(DOMString stringToSign,
                     DOMString caOption,
                     DOMString... args);

  [Throws]
  void logout();

  [Throws]
  void disableRightClick();
};

interface Crypto {
};

Crypto implements RandomSource;
Crypto implements CryptoLegacy;
