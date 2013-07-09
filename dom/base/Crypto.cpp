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
#ifdef MOZ_DISABLE_CRYPTOLEGACY
#include "mozilla/dom/WebCryptoBinding.h"
#else
#include "mozilla/dom/CryptoLegacyBinding.h"
#endif

using mozilla::dom::ContentChild;

using namespace js::ArrayBufferView;

namespace mozilla {
namespace dom {

NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Crypto)
  NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
  NS_INTERFACE_MAP_ENTRY(nsISupports)
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

JSObject *
Crypto::GetRandomValues(JSContext* aCx, ArrayBufferView& aArray, ErrorResult& aRv)
{
  NS_ABORT_IF_FALSE(NS_IsMainThread(), "Called on the wrong thread");

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
  if (dataLen == 0) {
    NS_WARNING("ArrayBufferView length is 0, cannot continue");
    return aArray.Obj();
  } else if (dataLen > 65536) {
    aRv.Throw(NS_ERROR_DOM_QUOTA_EXCEEDED_ERR);
    return nullptr;
  }

  uint8_t* data = reinterpret_cast<uint8_t*>(aArray.Data());
  GetRandomValues(data, dataLen);

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

bool
Crypto::EnableSmartCardEvents()
{
  return false;
}

void
Crypto::SetEnableSmartCardEvents(bool aEnableSmartCardEvents)
{
  // NOT_IMPLEMENTED
}

void
Crypto::GetVersion(nsAString& aVersion)
{
  // NOT_IMPLEMENTED
}

already_AddRefed<nsIDOMCRMFObject>
Crypto::GenerateCRMFRequest()
{
  // NOT_IMPLEMENTED
  return nullptr;
}

void
Crypto::ImportUserCertificates(const nsAString& aNickname,
                               const nsAString& aCmmfResponse,
                                     bool aDoForcedBackup,
                                     nsString& aRetval)
{
  // NOT_IMPLEMENTED
}

void
Crypto::PopChallengeResponse(const nsAString& aChallenge,
                             nsString& aRetval)
{
  // NOT_IMPLEMENTED
}

void
Crypto::Random(int32_t aNumBytes, nsString& aRetval)
{
  // NOT_IMPLEMENTED
}

void
Crypto::SignText(const nsAString& aStringToSign,
                 const nsAString& aCaOption,
                       nsString& aRetval)
{
  // NOT_IMPLEMENTED
}

void
Crypto::Logout()
{
  // NOT_IMPLEMENTED
}

void
Crypto::DisableRightClick()
{
  // NOT_IMPLEMENTED
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
