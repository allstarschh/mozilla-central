/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef mozilla_dom_Crypto_h
#define mozilla_dom_Crypto_h

#ifdef MOZ_DISABLE_CRYPTOLEGACY
#include "nsIDOMCrypto.h"
#else
#include "nsIDOMCryptoLegacy.h"
#include "nsIDOMCRMFObject.h"
#endif

#include "nsPIDOMWindow.h"
#include "nsWrapperCache.h"
#include "mozilla/dom/TypedArray.h"
#define NS_DOMCRYPTO_CID \
  {0x929d9320, 0x251e, 0x11d4, { 0x8a, 0x7c, 0x00, 0x60, 0x08, 0xc8, 0x44, 0xc3} }

namespace mozilla {
namespace dom {

#ifndef MOZ_DISABLE_CRYPTOLEGACY
#undef  IMETHOD_VISIBILITY
#define IMETHOD_VISIBILITY NS_VISIBILITY_DEFAULT
#endif

class Crypto : public nsIDOMCrypto,
               public nsWrapperCache
{
public:
  Crypto(nsPIDOMWindow *aWindow);
  virtual ~Crypto();

  NS_DECL_NSIDOMCRYPTO

  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(Crypto)

  virtual JSObject *
  GetRandomValues(JSContext* aCx, ArrayBufferView& aArray, ErrorResult& aRv);

#ifndef MOZ_DISABLE_CRYPTOLEGACY
  virtual bool EnableSmartCardEvents();
  virtual void SetEnableSmartCardEvents(bool aEnableSmartCardEvents, ErrorResult& aRv);

  virtual void GetVersion(nsAString& aVersion, ErrorResult& aRv);

  virtual already_AddRefed<nsIDOMCRMFObject> GenerateCRMFRequest(ErrorResult& aRv);

  virtual void ImportUserCertificates(const nsAString& aNickName,
                                      const nsAString& aCmmfResponse,
                                            bool aDoForcedBackup,
                                            nsString& aRetVal,
                                            ErrorResult& aRv);

  virtual void PopChallengeResponse(const nsAString& aChallenge,
                                          nsString& aRetVal,
                                          ErrorResult& aRv);

  virtual void Random(int32_t aNumBytes, nsString& aRetVal, ErrorResult& aRv);

  virtual void SignText(const nsAString& aStringToSign,
                        const nsAString& aCaOption,
                              nsString& aRetVal,
                              ErrorResult& aRv);

  virtual void Logout(ErrorResult& aRv);

  virtual void DisableRightClick(ErrorResult& aRv);
#endif

  // WebIDL

  nsPIDOMWindow*
  GetParentObject() const
  {
    return mWindow;
  }

  virtual JSObject*
  WrapObject(JSContext* aCx, JS::Handle<JSObject*> aScope) MOZ_OVERRIDE;

  static uint8_t*
  GetRandomValues(uint32_t aLength);

private:
  nsresult
  GetRandomValues(uint8_t* aData, uint32_t aDataLen);

  nsCOMPtr<nsPIDOMWindow> mWindow;
};

#ifndef MOZ_DISABLE_CRYPTOLEGACY
#undef  IMETHOD_VISIBILITY
#define IMETHOD_VISIBILITY NS_VISIBILITY_HIDDEN
#endif

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_Crypto_h
