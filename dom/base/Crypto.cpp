/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "Crypto.h"
#include "DOMError.h"
#include "nsString.h"
#include "jsfriendapi.h"
#include "nsIServiceManager.h"
#include "nsCOMPtr.h"
#include "nsIRandomGenerator.h"

#include "mozilla/dom/ContentChild.h"
#include "mozilla/dom/WebCryptoBinding.h"

#include <android/log.h>
#define LOGI(args...)  __android_log_print(ANDROID_LOG_INFO, "Crypto", args)
//#define LOGI(args...)
using mozilla::dom::ContentChild;

using namespace js::ArrayBufferView;

namespace mozilla {
namespace dom {

NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Crypto)
  NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
  NS_INTERFACE_MAP_ENTRY(nsISupports)
  NS_INTERFACE_MAP_ENTRY(nsIDOMCrypto)
NS_INTERFACE_MAP_END

NS_IMPL_CYCLE_COLLECTING_ADDREF(Crypto)
NS_IMPL_CYCLE_COLLECTING_RELEASE(Crypto)

NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE_1(Crypto, mWindow)

Crypto::Crypto(nsPIDOMWindow *aWindow)
  : mWindow(aWindow)
{
  MOZ_COUNT_CTOR(Crypto);
  SetIsDOMBinding();
}

Crypto::~Crypto()
{
  MOZ_COUNT_DTOR(Crypto);
}

/* virtual */ JSObject*
Crypto::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aScope)
{
  return CryptoBinding::Wrap(aCx, aScope, this);
}

NS_IMETHODIMP
Crypto::GetRandomValues(const JS::Value& aData, JSContext* aCx,
                        JS::Value* _retval)
{
  NS_ABORT_IF_FALSE(NS_IsMainThread(), "Called on the wrong thread");

  // Make sure this is a JavaScript object
  if (!aData.isObject()) {
    return NS_ERROR_DOM_NOT_OBJECT_ERR;
  }

  JS::Rooted<JSObject*> view(aCx, &aData.toObject());

  // Make sure this object is an ArrayBufferView
  if (!JS_IsTypedArrayObject(view)) {
    return NS_ERROR_DOM_TYPE_MISMATCH_ERR;
  }

  // Throw if the wrong type of ArrayBufferView is passed in
  // (Part of the Web Crypto API spec)
  switch (JS_GetArrayBufferViewType(view)) {
    case TYPE_INT8:
    case TYPE_UINT8:
    case TYPE_UINT8_CLAMPED:
    case TYPE_INT16:
    case TYPE_UINT16:
    case TYPE_INT32:
    case TYPE_UINT32:
      break;
    default:
      return NS_ERROR_DOM_TYPE_MISMATCH_ERR;
  }

  uint32_t dataLen = JS_GetTypedArrayByteLength(view);

  if (dataLen == 0) {
    NS_WARNING("ArrayBufferView length is 0, cannot continue");
    return NS_OK;
  } else if (dataLen > 65536) {
    return NS_ERROR_DOM_QUOTA_EXCEEDED_ERR;
  }

  void *dataptr = JS_GetArrayBufferViewData(view);
  NS_ENSURE_TRUE(dataptr, NS_ERROR_FAILURE);
  uint8_t* data = static_cast<uint8_t*>(dataptr);

  nsresult rv = GetRandomValues(data, dataLen);
  NS_ENSURE_SUCCESS(rv, rv);

  *_retval = OBJECT_TO_JSVAL(view);
  return NS_OK;
}

JSObject *
Crypto::GetRandomValues(JSContext* aCx, ArrayBufferView& aArray, ErrorResult& aRv)
{
  NS_ABORT_IF_FALSE(NS_IsMainThread(), "Called on the wrong thread");
  LOGI("%s enter", __func__);

  JS::Rooted<JSObject*> view(aCx, aArray.Obj());

  // Throw if the wrong type of ArrayBufferView is passed in
  // (Part of the Web Crypto API spec)
  switch (JS_GetArrayBufferViewType(view)) {
    case TYPE_INT8:
    case TYPE_UINT8:
    case TYPE_UINT8_CLAMPED:
    case TYPE_INT16:
    case TYPE_UINT16:
    case TYPE_INT32:
    case TYPE_UINT32:
      break;
    default:
      aRv.Throw(NS_ERROR_DOM_TYPE_MISMATCH_ERR);
      return nullptr;
  }

  uint32_t dataLen = aArray.Length();
  LOGI("%s length=%d", __func__, dataLen);
  if (dataLen == 0) {
    NS_WARNING("ArrayBufferView length is 0, cannot continue");
    return aArray.Obj();
  } else if (dataLen > 65536) {
    aRv.Throw(NS_ERROR_DOM_QUOTA_EXCEEDED_ERR);
    return nullptr;
  }

  uint8_t* data = reinterpret_cast<uint8_t*>(aArray.Data());
  GetRandomValues(data, dataLen);

  LOGI("%s exit", __func__);
  return aArray.Obj();
}

NS_IMETHODIMP
Crypto::GetRandomValues(uint8_t* aData, uint32_t aDataLen)
{
  if (XRE_GetProcessType() != GeckoProcessType_Default) {
    InfallibleTArray<uint8_t> randomValues;
    // Tell the parent process to generate random values via PContent
    ContentChild* cc = ContentChild::GetSingleton();
    if (!cc->SendGetRandomValues(aDataLen, &randomValues)) {
      return NS_ERROR_FAILURE;
    }
    NS_ASSERTION(aDataLen == randomValues.Length(),
                 "Invalid length returned from parent process!");
    memcpy(aData, randomValues.Elements(), aDataLen);
  } else {
    uint8_t *buf = GetRandomValues(aDataLen);

    if (!buf) {
      return NS_ERROR_FAILURE;
    }

    memcpy(aData, buf, aDataLen);
    NS_Free(buf);
  }
  return NS_OK;
}

#ifndef MOZ_DISABLE_CRYPTOLEGACY
// Stub out the legacy nsIDOMCrypto methods. The actual
// implementations are in security/manager/ssl/src/nsCrypto.{cpp,h}

NS_IMETHODIMP
Crypto::GetVersion(nsAString & aVersion)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::GetEnableSmartCardEvents(bool *aEnableSmartCardEvents)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::SetEnableSmartCardEvents(bool aEnableSmartCardEvents)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::GenerateCRMFRequest(nsIDOMCRMFObject * *_retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::ImportUserCertificates(const nsAString & nickname,
                               const nsAString & cmmfResponse,
                               bool doForcedBackup, nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::PopChallengeResponse(const nsAString & challenge,
                             nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::Random(int32_t numBytes, nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::SignText(const nsAString & stringToSign, const nsAString & caOption,
                 nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::Logout()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
Crypto::DisableRightClick()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}
#endif

/* static */ uint8_t*
Crypto::GetRandomValues(uint32_t aLength)
{
  nsCOMPtr<nsIRandomGenerator> randomGenerator;
  nsresult rv;
  randomGenerator = do_GetService("@mozilla.org/security/random-generator;1");
  NS_ENSURE_TRUE(randomGenerator, nullptr);

  uint8_t* buf;
  rv = randomGenerator->GenerateRandomBytes(aLength, &buf);

  NS_ENSURE_SUCCESS(rv, nullptr);

  return buf;
}

} // namespace dom
} // namespace mozilla
