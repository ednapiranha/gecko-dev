/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/**
 * A sample of XPConnect. This file is the header of an implementation
 * nsSample of the nsISample interface.
 *
 */

#include "nsISample.h"

/**
 * SampleImpl is an implementation of the nsISample interface.  In XPCOM,
 * there can be more than one implementation of an given interface.  Class
 * IDs (CIDs) uniquely identify a particular implementation of an interface.
 * Interface IDs (IIDs) uniquely identify an interface.
 *
 * The CID is also a unique number that looks just like an IID
 * and uniquely identifies an implementation
 * {7CB5B7A0-07D7-11d3-BDE2-000064657374}
 */

#define NS_SAMPLE_CID \
{ 0x7cb5b7a0, 0x7d7, 0x11d3, { 0xbd, 0xe2, 0x0, 0x0, 0x64, 0x65, 0x73, 0x74 } }

#define NS_SAMPLE_CONTRACTID "@mozilla.org/sample;1"


class nsSampleImpl : public nsISample
{
public:
    nsSampleImpl();
    virtual ~nsSampleImpl();

    /**
     * This macro expands into a declaration of the nsISupports interface.
     * Every XPCOM component needs to implement nsISupports, as it acts
     * as the gateway to other interfaces this component implements.  You
     * could manually declare QueryInterface, AddRef, and Release instead
     * of using this macro, but why?
     */
    // nsISupports interface
    NS_DECL_ISUPPORTS

    /**
     * This macro is defined in the nsISample.h file, and is generated
     * automatically by the xpidl compiler.  It expands to
     * declarations of all of the methods required to implement the
     * interface.  xpidl will generate a NS_DECL_[INTERFACENAME] macro
     * for each interface that it processes.
     *
     * The methods of nsISample are discussed individually below, but
     * commented out (because this macro already defines them.)
     */
    NS_DECL_NSISAMPLE

    /**
     * The following is an explanation of how the interface header
     * file expands to for a c++ implementation. NS_DELC_NSISAMPLE
     * takes care of defining the right c++ implementation.
     *
     * The following if provided for more understanding.
     *
     * NS_IMETHOD expands to the standard XPCOM return type.  XPCOM methods
     * should never return any other type.  The return value is used
     * behind the scenes by the XPConnect runtime to figure out if the call
     * failed in any way.
     * These methods were generated by "attribute string Value" in 
     * nsISample.idl.  When reflected into JavaScript, XPCOM will use these
     * calls as Getter/Setter ops, so that they can be called transparently
     * as "sample.Value='foo';" and "var val = sample.Value"
     */
    /* NS_IMETHOD GetValue(char * *aValue); */
    /* NS_IMETHOD SetValue(char * aValue); */

    /**
     * The const came from the "in" specifier in nsISample.idl.  "in"
     * specifies that the value of this parameter is used only for input,
     * this method is not allowed to modify the contents of the buffer.
     */
    /* NS_IMETHOD WriteValue(const char *aPrefix); */

    /**
     * nsISample.idl specifies all of it's string types as string, instead
     * of wstring (wide string), the Unicode type.  If the world were a
     * perfect place, all normal strings in XPCOM interfaces would be unicode.
     * If this type had been specified as wstring, it would appear as
     * PRUnichar * in C++, which is the NSPR type for unicode characters.
     */
    /* NS_IMETHOD Poke(const char* aValue); */

private:
    char* mValue;
};
