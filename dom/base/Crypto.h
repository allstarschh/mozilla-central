/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef mozilla_dom_Crypto_h
#define mozilla_dom_Crypto_h

#ifdef MOZ_DISABLE_CRYPTOLEGACY
#include "nsIDOMCrypto.h"
#else
#include "nsIDOMCryptoLegacy.h"
#endif
#include "nsPIDOMWindow.h"
#include "nsWrapperCache.h"

#define NS_DOMCRYPTO_CID \
  {0x929d9320, 0x251e, 0x11d4, { 0x8a, 0x7c, 0x00, 0x60, 0x08, 0xc8, 0x44, 0xc3} }

namespace mozilla {
namespace dom {

class SubtleCrypto;

class Crypto : public nsIDOMCrypto,
               public nsWrapperCache
{
public:
  Crypto();
  virtual ~Crypto();

  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMCRYPTO

  nsPIDOMWindow*
  GetParentObject() const
  {
    //TODO
    return nullptr;
  }

  virtual JSObject*
  WrapObject(JSContext *aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;

  static uint8_t*
  GetRandomValues(uint32_t aLength);

  already_AddRefed<SubtleCrypto> Subtle();
};

class SubtleCrypto : public nsISupports,
                     public nsWrapperCache
{
public:
  SubtleCrypto();
  virtual ~SubtleCrypto();

//  NS_DECL_ISUPPORTS
//  NS_DECL_NSIDOMCRYPTO

  nsPIDOMWindow*
  GetParentObject() const
  {
    //TODO
    return nullptr;
  }

  virtual JSObject*
  WrapObject(JSContext *aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;

};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_Crypto_h
