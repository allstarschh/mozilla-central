/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "CryptoLegacy.h"
#include "nsIDOMClassInfo.h"
#include "DOMError.h"
#include "nsString.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "nsIServiceManager.h"
#include "nsCOMPtr.h"
#include "nsIRandomGenerator.h"

#include "mozilla/dom/ContentChild.h"

using mozilla::dom::ContentChild;

using namespace js::ArrayBufferView;

namespace mozilla {
namespace dom {

NS_INTERFACE_MAP_BEGIN(CryptoLegacy)
  NS_INTERFACE_MAP_ENTRY(nsISupports)
  NS_INTERFACE_MAP_ENTRY(nsIDOMCrypto)
  NS_DOM_INTERFACE_MAP_ENTRY_CLASSINFO(CryptoLegacy)
NS_INTERFACE_MAP_END

NS_IMPL_ADDREF(CryptoLegacy)
NS_IMPL_RELEASE(CryptoLegacy)

CryptoLegacy::CryptoLegacy()
{
  MOZ_COUNT_CTOR(CryptoLegacy);
}

CryptoLegacy::~CryptoLegacy()
{
  MOZ_COUNT_DTOR(CryptoLegacy);
}

NS_IMETHODIMP
CryptoLegacy::GetRandomValues(const JS::Value& aData, JSContext *cx,
                        JS::Value* _retval)
{
  NS_ABORT_IF_FALSE(NS_IsMainThread(), "Called on the wrong thread");

  // Make sure this is a JavaScript object
  if (!aData.isObject()) {
    return NS_ERROR_DOM_NOT_OBJECT_ERR;
  }

  JS::Rooted<JSObject*> view(cx, &aData.toObject());

  // Make sure this object is an ArrayBufferView
  if (!JS_IsTypedArrayObject(view)) {
    return NS_ERROR_DOM_TYPE_MISMATCH_ERR;
  }

  // Throw if the wrong type of ArrayBufferView is passed in
  // (Part of the Web CryptoLegacy API spec)
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
  unsigned char* data =
    static_cast<unsigned char*>(dataptr);

  if (XRE_GetProcessType() != GeckoProcessType_Default) {
    InfallibleTArray<uint8_t> randomValues;
    // Tell the parent process to generate random values via PContent
    ContentChild* cc = ContentChild::GetSingleton();
    if (!cc->SendGetRandomValues(dataLen, &randomValues)) {
      return NS_ERROR_FAILURE;
    }
    NS_ASSERTION(dataLen == randomValues.Length(),
                 "Invalid length returned from parent process!");
    memcpy(data, randomValues.Elements(), dataLen);
  } else {
    uint8_t *buf = GetRandomValues(dataLen);

    if (!buf) {
      return NS_ERROR_FAILURE;
    }

    memcpy(data, buf, dataLen);
    NS_Free(buf);
  }

  *_retval = OBJECT_TO_JSVAL(view);

  return NS_OK;
}

NS_IMETHODIMP
CryptoLegacy::GetVersion(nsAString & aVersion)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::GetEnableSmartCardEvents(bool *aEnableSmartCardEvents)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::SetEnableSmartCardEvents(bool aEnableSmartCardEvents)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::GenerateCRMFRequest(nsIDOMCRMFObject * *_retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::ImportUserCertificates(const nsAString & nickname,
                               const nsAString & cmmfResponse,
                               bool doForcedBackup, nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::PopChallengeResponse(const nsAString & challenge,
                             nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::Random(int32_t numBytes, nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::SignText(const nsAString & stringToSign, const nsAString & caOption,
                 nsAString & _retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::Logout()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
CryptoLegacy::DisableRightClick()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

uint8_t*
CryptoLegacy::GetRandomValues(uint32_t aLength)
{
  nsCOMPtr<nsIRandomGenerator> randomGenerator;
  nsresult rv;
  randomGenerator =
    do_GetService("@mozilla.org/security/random-generator;1");
  NS_ENSURE_TRUE(randomGenerator, nullptr);

  uint8_t* buf;
  rv = randomGenerator->GenerateRandomBytes(aLength, &buf);

  NS_ENSURE_SUCCESS(rv, nullptr);

  return buf;
}
} // namespace dom
} // namespace mozilla
