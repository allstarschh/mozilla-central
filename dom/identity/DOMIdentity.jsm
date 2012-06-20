/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

const {classes: Cc, interfaces: Ci, utils: Cu} = Components;

// This is the parent process corresponding to nsDOMIdentity.
let EXPORTED_SYMBOLS = ["DOMIdentity"];

Cu.import("resource://gre/modules/Services.jsm");
Cu.import("resource://gre/modules/XPCOMUtils.jsm");

XPCOMUtils.defineLazyModuleGetter(this, "IdentityService",
                                  "resource://gre/modules/identity/Identity.jsm");

function log(msg) {
  if (!IdentityService._debug) {
    return;
  }

  dump("DOMIdentity: " + msg + "\n");
}

function IDDOMMessage(aID) {
  this.id = aID;
}

function IDPProvisioningContext(aID, aOrigin, aTargetMM) {
  this._id = aID;
  this._origin = aOrigin;
  this._mm = aTargetMM;
}

IDPProvisioningContext.prototype = {
  get id() this._id,
  get origin() this._origin,
  get mm() this._mm,

  doBeginProvisioningCallback: function IDPPC_doBeginProvCB(aID, aCertDuration) {
    let message = new IDDOMMessage(this.id);
    message.identity = aID;
    message.certDuration = aCertDuration;
    this.mm.sendAsyncMessage("Identity:IDP:CallBeginProvisioningCallback",
                             message);
  },

  doGenKeyPairCallback: function IDPPC_doGenKeyPairCallback(aPublicKey) {
    log("doGenKeyPairCallback");
    let message = new IDDOMMessage(this.id);
    message.publicKey = aPublicKey;
    this.mm.sendAsyncMessage("Identity:IDP:CallGenKeyPairCallback", message);
  },

  doError: function(msg) {
    log("Provisioning ERROR: " + msg);
  },
};

function IDPAuthenticationContext(aID, aOrigin, aTargetMM) {
  this._id = aID;
  this._origin = aOrigin;
  this._mm = aTargetMM;
}

IDPAuthenticationContext.prototype = {
  get id() this._id,
  get origin() this._origin,
  get mm() this._mm,

  doBeginAuthenticationCallback: function IDPAC_doBeginAuthCB(aIdentity) {
    let message = new IDDOMMessage(this.id);
    message.identity = aIdentity;
    this.mm.sendAsyncMessage("Identity:IDP:CallBeginAuthenticationCallback",
                             message);
  },

  doError: function IDPAC_doError(msg) {
    log("Authentication ERROR: " + msg);
  },
};

function RPWatchContext(aID, aOrigin, aLoggedInEmail, aTargetMM) {
  this._id = aID;
  this._origin = aOrigin;
  this._loggedInEmail = aLoggedInEmail;
  this._mm = aTargetMM;
}

RPWatchContext.prototype = {
  get id() this._id,
  get origin() this._origin,
  get loggedInEmail() this._loggedInEmail,
  get mm() this._mm,

  doLogin: function RPWatchContext_onlogin(aAssertion) {
    log("doLogin: " + this.id);
    let message = new IDDOMMessage(this.id);
    message.assertion = aAssertion;
    this.mm.sendAsyncMessage("Identity:RP:Watch:OnLogin", message);
  },

  doLogout: function RPWatchContext_onlogout() {
    log("doLogout :" + this.id);
    let message = new IDDOMMessage(this.id);
    this.mm.sendAsyncMessage("Identity:RP:Watch:OnLogout", message);
  },

  doReady: function RPWatchContext_onready() {
    log("doReady: " + this.id);
    let message = new IDDOMMessage(this.id);
    this.mm.sendAsyncMessage("Identity:RP:Watch:OnReady", message);
  },

  doError: function RPWatchContext_onerror(aMessage) {
    log("doError: " + aMessage);
  }
};

let DOMIdentity = {
  // nsIFrameMessageListener
  receiveMessage: function DOMIdentity_receiveMessage(aMessage) {
    let msg = aMessage.json;

    // Target is the frame message manager that called us and is
    // used to send replies back to the proper window.
    let targetMM = aMessage.target
                           .QueryInterface(Ci.nsIFrameLoaderOwner)
                           .frameLoader.messageManager;

    switch (aMessage.name) {
      // RP
      case "Identity:RP:Watch":
        this._watch(msg, targetMM);
        break;
      case "Identity:RP:Request":
        this._request(msg);
        break;
      case "Identity:RP:Logout":
        this._logout(msg);
        break;
      // IDP
      case "Identity:IDP:BeginProvisioning":
        this._beginProvisioning(msg, targetMM);
        break;
      case "Identity:IDP:GenKeyPair":
        this._genKeyPair(msg);
        break;
      case "Identity:IDP:RegisterCertificate":
        this._registerCertificate(msg);
        break;
      case "Identity:IDP:ProvisioningFailure":
        this._provisioningFailure(msg);
        break;
      case "Identity:IDP:BeginAuthentication":
        this._beginAuthentication(msg, targetMM);
        break;
      case "Identity:IDP:CompleteAuthentication":
        this._completeAuthentication(msg);
        break;
      case "Identity:IDP:AuthenticationFailure":
        this._authenticationFailure(msg);
        break;
    }
  },

  // nsIObserver
  observe: function DOMIdentity_observe(aSubject, aTopic, aData) {
    switch (aTopic) {
      case "domwindowopened":
      case "domwindowclosed":
        let win = aSubject.QueryInterface(Ci.nsIInterfaceRequestor)
                          .getInterface(Ci.nsIDOMWindow);
        this._configureMessages(win, aTopic == "domwindowopened");
        break;

      case "xpcom-shutdown":
        Services.ww.unregisterNotification(this);
        Services.obs.removeObserver(this, "xpcom-shutdown");
        break;
    }
  },

  messages: ["Identity:RP:Watch", "Identity:RP:Request", "Identity:RP:Logout",
             "Identity:IDP:BeginProvisioning", "Identity:IDP:ProvisioningFailure",
             "Identity:IDP:RegisterCertificate", "Identity:IDP:GenKeyPair",
             "Identity:IDP:BeginAuthentication",
             "Identity:IDP:CompleteAuthentication",
             "Identity:IDP:AuthenticationFailure"],

  // Private.
  _init: function DOMIdentity__init() {
    Services.ww.registerNotification(this);
    Services.obs.addObserver(this, "xpcom-shutdown", false);
  },

  _configureMessages: function DOMIdentity__configureMessages(aWindow, aRegister) {
    if (!aWindow.messageManager)
      return;

    let func = aRegister ? "addMessageListener" : "removeMessageListener";

    for (let message of this.messages) {
      aWindow.messageManager[func](message, this);
    }
  },

  _watch: function DOMIdentity__watch(message, targetMM) {
    // Pass an object with the watch members to Identity.jsm so it can call the
    // callbacks.
    let context = new RPWatchContext(message.id, message.origin,
                                     message.loggedInEmail, targetMM);
    IdentityService.RP.watch(context);
  },

  _request: function DOMIdentity__request(message) {
    IdentityService.RP.request(message.id, message);
  },

  _logout: function DOMIdentity__logout(message) {
    IdentityService.RP.logout(message.id, message.origin);
  },

  _beginProvisioning: function DOMIdentity__beginProvisioning(message, targetMM) {
    let context = new IDPProvisioningContext(message.id, message.origin,
                                             targetMM);
    IdentityService.IDP.beginProvisioning(context);
  },

  _genKeyPair: function DOMIdentity__genKeyPair(message) {
    IdentityService.IDP.genKeyPair(message.id);
  },

  _registerCertificate: function DOMIdentity__registerCertificate(message) {
    IdentityService.IDP.registerCertificate(message.id, message.cert);
  },

  _provisioningFailure: function DOMIdentity__provisioningFailure(message) {
    IdentityService.IDP.raiseProvisioningFailure(message.id, message.reason);
  },

  _beginAuthentication: function DOMIdentity__beginAuthentication(message, targetMM) {
    let context = new IDPAuthenticationContext(message.id, message.origin,
                                               targetMM);
    IdentityService.IDP.beginAuthentication(context);
  },

  _completeAuthentication: function DOMIdentity__completeAuthentication(message) {
    IdentityService.IDP.completeAuthentication(message.id);
  },

  _authenticationFailure: function DOMIdentity__authenticationFailure(message) {
    IdentityService.IDP.cancelAuthentication(message.id);
  },
};

// Object is initialized by nsIDService.js
