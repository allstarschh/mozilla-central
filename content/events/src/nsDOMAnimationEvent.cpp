/* vim: set shiftwidth=2 tabstop=8 autoindent cindent expandtab: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "nsDOMAnimationEvent.h"
#include "nsGUIEvent.h"
#include "nsDOMClassInfoID.h"
#include "nsIClassInfo.h"
#include "nsIXPCScriptable.h"

nsDOMAnimationEvent::nsDOMAnimationEvent(mozilla::dom::EventTarget* aOwner,
                                         nsPresContext *aPresContext,
                                         nsAnimationEvent *aEvent)
  : nsDOMEvent(aOwner, aPresContext,
               aEvent ? aEvent : new nsAnimationEvent(false, 0,
                                                      EmptyString(),
                                                      0.0,
                                                      EmptyString()))
{
  if (aEvent) {
    mEventIsInternal = false;
  }
  else {
    mEventIsInternal = true;
    mEvent->time = PR_Now();
  }
  SetIsDOMBinding();
}

nsDOMAnimationEvent::~nsDOMAnimationEvent()
{
  if (mEventIsInternal) {
    delete AnimationEvent();
    mEvent = nullptr;
  }
}

DOMCI_DATA(AnimationEvent, nsDOMAnimationEvent)

NS_INTERFACE_MAP_BEGIN(nsDOMAnimationEvent)
  NS_INTERFACE_MAP_ENTRY(nsIDOMAnimationEvent)
  NS_DOM_INTERFACE_MAP_ENTRY_CLASSINFO(AnimationEvent)
NS_INTERFACE_MAP_END_INHERITING(nsDOMEvent)

NS_IMPL_ADDREF_INHERITED(nsDOMAnimationEvent, nsDOMEvent)
NS_IMPL_RELEASE_INHERITED(nsDOMAnimationEvent, nsDOMEvent)

//static
already_AddRefed<nsDOMAnimationEvent>
nsDOMAnimationEvent::Constructor(const mozilla::dom::GlobalObject& aGlobal,
                                 const nsAString& aType,
                                 const mozilla::dom::AnimationEventInit& aParam,
                                 mozilla::ErrorResult& aRv)
{
  nsCOMPtr<mozilla::dom::EventTarget> t = do_QueryInterface(aGlobal.Get());
  nsRefPtr<nsDOMAnimationEvent> e = new nsDOMAnimationEvent(t, nullptr, nullptr);
  bool trusted = e->Init(t);
  aRv = e->InitAnimationEvent(aType, aParam.mBubbles, aParam.mCancelable,
                              aParam.mAnimationName, aParam.mElapsedTime,
                              aParam.mPseudoElement);
  e->SetTrusted(trusted);
  return e.forget();
}

NS_IMETHODIMP
nsDOMAnimationEvent::GetAnimationName(nsAString & aAnimationName)
{
  aAnimationName = AnimationEvent()->animationName;
  return NS_OK;
}

NS_IMETHODIMP
nsDOMAnimationEvent::GetElapsedTime(float *aElapsedTime)
{
  *aElapsedTime = ElapsedTime();
  return NS_OK;
}

NS_IMETHODIMP
nsDOMAnimationEvent::GetPseudoElement(nsAString& aPseudoElement)
{
  aPseudoElement = AnimationEvent()->pseudoElement;
  return NS_OK;
}

NS_IMETHODIMP
nsDOMAnimationEvent::InitAnimationEvent(const nsAString & typeArg,
                                        bool canBubbleArg,
                                        bool cancelableArg,
                                        const nsAString & animationNameArg,
                                        float elapsedTimeArg,
                                        const nsAString & pseudoElementArg)
{
  nsresult rv = nsDOMEvent::InitEvent(typeArg, canBubbleArg, cancelableArg);
  NS_ENSURE_SUCCESS(rv, rv);

  AnimationEvent()->animationName = animationNameArg;
  AnimationEvent()->elapsedTime = elapsedTimeArg;
  AnimationEvent()->pseudoElement = pseudoElementArg;
  return NS_OK;
}

nsresult
NS_NewDOMAnimationEvent(nsIDOMEvent **aInstancePtrResult,
                        mozilla::dom::EventTarget* aOwner,
                        nsPresContext *aPresContext,
                        nsAnimationEvent *aEvent)
{
  nsDOMAnimationEvent* it =
    new nsDOMAnimationEvent(aOwner, aPresContext, aEvent);
  return CallQueryInterface(it, aInstancePtrResult);
}
