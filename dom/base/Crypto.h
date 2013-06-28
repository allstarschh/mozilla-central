/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef mozilla_dom_Crypto_h
#define mozilla_dom_Crypto_h

#include <android/log.h>
#define LOGI(args...)  __android_log_print(ANDROID_LOG_INFO, "Crypto.h", args)

#ifdef MOZ_DISABLE_CRYPTOLEGACY
#include "nsIDOMCrypto.h"
#else
#include "nsIDOMCryptoLegacy.h"
#endif
#include "nsPIDOMWindow.h"
#include "nsWrapperCache.h"

#include "mozilla/dom/TypedArray.h"

#define NS_DOMCRYPTO_CID \
  {0x929d9320, 0x251e, 0x11d4, { 0x8a, 0x7c, 0x00, 0x60, 0x08, 0xc8, 0x44, 0xc3} }

//class nsPIDOMWindow;

namespace mozilla {
namespace dom {

class SubtleCrypto;

class Crypto : public nsIDOMCrypto,
               public nsWrapperCache
{
public:
  Crypto(nsPIDOMWindow *aInnerWindow);
  virtual ~Crypto();

  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(Crypto)

  NS_IMETHODIMP
  GetRandomValues(const JS::Value& aData, JSContext *cx, JS::Value* _retval);

  // TODO return type should be ArrayBufferView *
//  JSObject *
  ArrayBufferView *
  GetRandomValues(JSContext *aCx, ArrayBufferView& aArray);

  NS_IMETHODIMP
  GetRandomValues(uint8_t *aData, uint32_t aDataLen);

  nsPIDOMWindow*
  GetParentObject() const
  {
    LOGI("%s enter", __func__);
    return mWindow;
  }

  virtual JSObject*
  WrapObject(JSContext *aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;

  static uint8_t*
  GetRandomValues(uint32_t aLength);

  already_AddRefed<SubtleCrypto> Subtle();

private:
  nsCOMPtr<nsPIDOMWindow> mWindow;
};

class SubtleCrypto : public nsISupports,
                     public nsWrapperCache
{
public:
  SubtleCrypto();
  virtual ~SubtleCrypto();

  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(SubtleCrypto)

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
