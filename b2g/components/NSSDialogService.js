/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

const Ci = Components.interfaces;
const Cu = Components.utils;
const Cc = Components.classes;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");
Cu.import("resource://gre/modules/Services.jsm");

// -----------------------------------------------------------------------
// NSS DB I/O helper, imported from gecko/security/manager/pki/resources/content/password.js
// -----------------------------------------------------------------------
const nsPK11TokenDB = "@mozilla.org/security/pk11tokendb;1";
const nsIPK11TokenDB = Ci.nsIPK11TokenDB;
const nsIDialogParamBlock = Ci.nsIDialogParamBlock;
const nsPKCS11ModuleDB = "@mozilla.org/security/pkcs11moduledb;1";
const nsIPKCS11ModuleDB = Ci.nsIPKCS11ModuleDB;
const nsIPKCS11Slot = Ci.nsIPKCS11Slot;
const nsIPK11Token = Ci.nsIPK11Token;

// -----------------------------------------------------------------------
// NSS Dialog Service
// -----------------------------------------------------------------------

function dump(a) {
  Cc["@mozilla.org/consoleservice;1"].getService(Ci.nsIConsoleService).logStringMessage(a);
}

function NSSDialogs() { }

NSSDialogs.prototype = {
  classID: Components.ID("{cbc08081-49b6-4561-9c18-a7707a50bda1}"),
  QueryInterface: XPCOMUtils.generateQI([Ci.nsICertificateDialogs,
                                         Ci.nsIClientAuthDialogs,
                                         Ci.nsITokenPasswordDialogs,
                                         Ci.nsITokenDialogs,
                                         Ci.nsIPrompt]),
  // UseToken: "Generic Crypto Services",
  // UseToken: "Builtin Object Token",
  UseToken: "Software Security Device",
  UsePassword: "12345678",

  // -----------------------------------------------------------------------
  // NSS DB I/O helper, imported from gecko/security/manager/pki/resources/content/password.js
  // -----------------------------------------------------------------------
  _iterateToken: function _iterateToken(callback) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs._iterateToken()\n");
    var sectokdb = Cc[nsPK11TokenDB].getService(nsIPK11TokenDB);
    var tokenList = sectokdb.listTokens();
    var enumElement;

    try {
       for ( ; !tokenList.isDone(); tokenList.next()) {
          enumElement = tokenList.currentItem();
          var token = enumElement.QueryInterface(nsIPK11Token);

          callback(token);
       }
    } catch (e) {}
  },

  _getSlot: function _getSlot(tokenName) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs._getSlot(" + tokenName + ")\n");
    var secmoddb = Cc[nsPKCS11ModuleDB].getService(nsIPKCS11ModuleDB);
    var slot = secmoddb.findSlotByName(tokenName);

    if (!slot) {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._getSlot(), failed to get slot\n");
    }

    return slot;
  },

  _getToken: function _getToken(tokenName) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs._getToken(" + tokenName + ")\n");
    var pk11db = Cc[nsPK11TokenDB].getService(nsIPK11TokenDB);
    var token = pk11db.findTokenByName(tokenName);

    if (!token) {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._getToken(), failed to get token\n");
    }

    return token;
  },

  _initPassword: function _initPassword(token, password) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs._initPassword(" + password + ")\n");
    try {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._initPassword(), success\n");
      token.initPassword(password);
    } catch (e) {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._initPassword(), error\n");
    }
  },

  _setPassword: function _setPassword(token, oldPw, newPw) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs._setPassword(" + token.tokenName + ", " + oldPw + ", " + newPw + ")\n");

    if (newPw == "") {
      var secmoddb = Cc[nsPKCS11ModuleDB].getService(nsIPKCS11ModuleDB);
      if (secmoddb.isFIPSEnabled) {
        // empty passwords are not allowed in FIPS mode
        dump("#### Chucklee: NSSDialogService.js: NSSDialogs._setPassword(), empty passwords are not allowed in FIPS mode\n");
        return false;
      }
    }

    try {
      token.changePassword(oldPw, newPw);
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._setPassword(), change password success\n");
      return true;
    } catch (e) {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs._setPassword(), change password failed\n");
      return false;
    }
  },

  doPrompt: function doPrompt(msg) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.doPrompt(" + msg + ")\n");
    /* [JavaScript Error: "Couldn't play common dialog event sound: TypeError: Cc['@mozilla.org/sound;1'] is undefined" {file: "resource://gre/modules/CommonDialog.jsm" line: 181}]
    let prompts = Cc["@mozilla.org/embedcomp/prompt-service;1"].
      getService(Ci.nsIPromptService);
    prompts.alert(null, null, msg);
    //*/
    return true;
  },

  getString: function(aName) {
    /*
    if (!this.bundle) {
        this.bundle = Services.strings.createBundle("chrome://browser/locale/pippki.properties");
    }
    return this.bundle.GetStringFromName(aName);
    //*/
    return "getString()";
  },

  formatString: function(aName, argList) {
    /*
    if (!this.bundle) {
      this.bundle = Services.strings.createBundle("chrome://browser/locale/pippki.properties");
    }
    return this.bundle.formatStringFromName(aName, argList, 1);
    //*/
    return "formatString()";
  },

  showPrompt: function(aTitle, aText, aButtons, aInputs) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.showPrompt()\n");
    /*
    let msg = {
      type: "Prompt:Show",
      title: aTitle,
      text: aText,
      buttons: aButtons,
      inputs: aInputs
    };
    let data = Cc["@mozilla.org/android/bridge;1"].getService(Ci.nsIAndroidBridge).handleGeckoMessage(JSON.stringify(msg));
    return JSON.parse(data);
    //*/
    return true;
  },

  /**
   * nsICertificateDialogs
   */
  confirmDownloadCACert: function(aCtx, aCert, aTrust) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.confirmDownloadCACert()\n");
    /*
    while (true) {
      let response = this.showPrompt(this.getString("downloadCert.title"),
                                     this.getString("downloadCert.message1"),
                                     [ this.getString("nssdialogs.ok.label"),
                                       this.getString("downloadCert.viewCert.label"),
                                       this.getString("nssdialogs.cancel.label")
                                     ],
                                     [ { type: "checkbox", id: "trustSSL", label: this.getString("downloadCert.trustSSL"), checked: false },
                                       { type: "checkbox", id: "trustEmail", label: this.getString("downloadCert.trustEmail"), checked: false },
                                       { type: "checkbox", id: "trustSign", label: this.getString("downloadCert.trustObjSign"), checked: false }
                                     ]);
      if (response.button == 1) {
        // they hit the "view cert" button, so show the cert and try again
        this.viewCert(aCtx, aCert);
        continue;
      } else if (response.button != 0) {
        return false;
      }

      aTrust.value = Ci.nsIX509CertDB.UNTRUSTED;
      if (response.trustSSL == "true") aTrust.value |= Ci.nsIX509CertDB.TRUSTED_SSL;
      if (response.trustEmail == "true") aTrust.value |= Ci.nsIX509CertDB.TRUSTED_EMAIL;
      if (response.trustSign == "true") aTrust.value |= Ci.nsIX509CertDB.TRUSTED_OBJSIGN;
      return true;
    }
    //*/
    throw "Unimplemented";
  },

  notifyCACertExists: function(aCtx) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.notifyCACertExists()\n");
    this.showPrompt(this.getString("caCertExists.title"), this.getString("caCertExists.message"), [], []);
  },

  setPKCS12FilePassword: function(aCtx, aPassword) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPKCS12FilePassword()\n");
    // this dialog is never shown in Fennec; in Desktop it is shown while backing up a personal
    // certificate to a file via Preferences->Advanced->Encryption->View Certificates->Your Certificates
    throw "Unimplemented";
  },

  getPKCS12FilePassword: function(aCtx, aPassword) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.getPKCS12FilePassword()\n");
    /*
    let response = this.showPrompt(this.getString("pkcs12.getpassword.title"),
                                   this.getString("pkcs12.getpassword.message"),
                                   [ this.getString("nssdialogs.ok.label"),
                                     this.getString("nssdialogs.cancel.label")
                                   ],
                                   [ { type: "password", id: "pw" } ]);
    if (response.button != 0) {
      return false;
    }
    aPassword.value = response.pw;
    //*/
    aPassword.value = this.UsePassword;
//    aPassword.value = "yoshi2";//this.UsePassword;
    return true;
  },

  certInfoSection: function(aHeading, aDataPairs, aTrailingNewline = true) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.certInfoSection()\n");
    var str = "<big>" + this.getString(aHeading) + "</big><br/>";
    for (var i = 0; i < aDataPairs.length; i += 2) {
      str += this.getString(aDataPairs[i]) + ": " + aDataPairs[i+1] + "<br/>";
    }
    return str + (aTrailingNewline ? "<br/>" : "");
  },

  viewCert: function(aCtx, aCert) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.viewCert()\n");
    this.showPrompt(this.getString("certmgr.title"),
                    "",
                    [ this.getString("nssdialogs.ok.label") ],
                    [ { type: "label", label:
                        this.certInfoSection("certmgr.subjectinfo.label",
                          ["certmgr.certdetail.cn", aCert.commonName,
                           "certmgr.certdetail.o", aCert.organization,
                           "certmgr.certdetail.ou", aCert.organizationalUnit,
                           "certmgr.certdetail.serialnumber", aCert.serialNumber]) +
                        this.certInfoSection("certmgr.issuerinfo.label",
                          ["certmgr.certdetail.cn", aCert.issuerCommonName,
                           "certmgr.certdetail.o", aCert.issuerOrganization,
                           "certmgr.certdetail.ou", aCert.issuerOrganizationUnit]) +
                        this.certInfoSection("certmgr.validity.label",
                          ["certmgr.issued", aCert.validity.notBeforeLocalDay,
                           "certmgr.expires", aCert.validity.notAfterLocalDay]) +
                        this.certInfoSection("certmgr.fingerprints.label",
                          ["certmgr.certdetail.sha1fingerprint", aCert.sha1Fingerprint,
                           "certmgr.certdetail.md5fingerprint", aCert.md5Fingerprint], false) }
                    ]);
  },

  crlImportStatusDialog: function(aCtx, aCrl) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.crlImportStatusDialog()\n");
    // this dialog is never shown in Fennec; in Desktop it is shown after importing a CRL
    // via Preferences->Advanced->Encryption->Revocation Lists->Import.
    throw "Unimplemented";
  },

  viewCertDetails: function(details) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.viewCertDetails()\n");
    this.showPrompt(this.getString("clientAuthAsk.message3"),
                    '',
                    [ this.getString("nssdialogs.ok.label") ],
                    [ { type: "label", label: details
                      }
                    ]);
  },

  /**
   * nsIClientAuthDialogs
   */
  ChooseCertificate: function(aCtx, cn, organization, issuer, certNickList, certDetailsList, count, selectedIndex, canceled) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.ChooseCertificate()\n");
    let rememberSetting = true;
    var pref = Cc['@mozilla.org/preferences-service;1']
               .getService(Ci.nsIPrefService);
    if (pref) {
      pref = pref.getBranch(null);
      try {
        rememberSetting = pref.getBoolPref("security.remember_cert_checkbox_default_setting");
      } catch (e) {
        // pref is missing
      }
    }

    let organizationString = this.formatString("clientAuthAsk.organization",
                                               [organization]);
    let issuerString = this.formatString("clientAuthAsk.issuer",
                                         [issuer]);
    let serverRequestedDetails = cn + '<br/>' + organizationString + '<br/>' + issuerString;

    selectedIndex = 0;
    while (true) {
      let response = this.showPrompt(this.getString("clientAuthAsk.title"),
                                     this.getString("clientAuthAsk.message1"),
                                     [ this.getString("nssdialogs.ok.label"),
                                       this.getString("clientAuthAsk.viewCert.label"),
                                       this.getString("nssdialogs.cancel.label")
                                     ],
                                     [ { type: "label", id: "requestedDetails", label: serverRequestedDetails },
                                       { type: "menulist", id: "nicknames", label: this.getString("clientAuthAsk.message2"), values: certNickList, selected: selectedIndex },
                                       { type: "checkbox", id: "rememberBox", label: this.getString("clientAuthAsk.remember.label"), checked: rememberSetting },
                                     ]);
      selectedIndex = response.nicknames;
      if (response.button == 1) {
        this.viewCertDetails(certDetailsList[selectedIndex]);
        continue;
      } else if (response.button == 0) {
        canceled.value = false;
        if (response.rememberBox == "true") {
          aCtx.QueryInterface(Ci.nsIClientAuthUserDecision).rememberClientAuthCertificate = true;
        }
        return true;
      }
      canceled.value = true;
      return false;
    }
  },

  /**
   * nsITokenPasswordDialogs
   */
  setPassword: function setPassword(aCtx, aTokenName, aCanceled) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPassword(), tokenName: " + aTokenName + "\n");

    /*
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPassword(), iterate db token:\n");
    this._iterateToken(function (token) {
                  dump("Token: name(" + token.tokenName + "), needsLogin(" + token.needsLogin() + "), needsUserInit(" + token.needsUserInit + ")\n");
                });

    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPassword(), test doPrompt()\n");
    this.doPrompt("doPrompt() Test");
    //*/

    var slot = this._getSlot(aTokenName);
    var token = this._getToken(aTokenName);
    if (slot.status === nsIPKCS11Slot.SLOT_UNINITIALIZED) {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPassword(), init password\n");
      this._initPassword(token, this.UsePassword);
    } else {
      dump("#### Chucklee: NSSDialogService.js: NSSDialogs.setPassword(), change password\n");
      this._setPassword(token, "", this.UsePassword);
    }
    /*
    let response = this.showPrompt("Chucklee : Set Password Title",
                                   "Chucklee : Set Password Text",
                                   [ "Chucklee : Set Password OK",
                                     "Chucklee : Set Password Cancel"
                                   ],
                                   [ { type: "password", id: "pw" } ]);
    //*/
    aCanceled.value = false;
    return true;
  },

  getPasswrod: function getPasswrod(aCtx, aTokenName, aPassword, aCanceled) {
    dump("#### Chucklee: NSSDialogService.js: NSSDialogs.getPasswrod()\n");
    aPassword.value = this.UsePassword;
    aCanceled.value = false;
    return true;
  },

  /**
   * nsITokenDialogs
   */
  ChooseToken: function ChooseToken(aCtx, aTokenNameList, aCount, aTokenName, aCanceled) {
    dump("XXX chooseToken");
    aTokenName.value = "Token Name Test";
    aCanceled.value = false;
    return true;
  },

  displayProtectedAuth: function displayProtectedAuth(aCtx, aRunnable) {
    dump("XXX displayProtectedAuth");
    return true;
  },

  // nsIPrompt
  prompt: function prompt(dialogTitle, text, value, checkMsg, checkValue) {
    dump("XXX dialogTitle="+dialogTitle+" text="+text+" value="+value+" checkMsg="+checkMsg+" checkValue="+checkValue);
    return true;
  }
};

this.NSGetFactory = XPCOMUtils.generateNSGetFactory([NSSDialogs]);
