/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */
/* AUTO-GENERATED. DO NOT EDIT!!! */

#include "jsapi.h"
#include "nsJSUtils.h"
#include "nsDOMError.h"
#include "nscore.h"
#include "nsIScriptContext.h"
#include "nsIScriptSecurityManager.h"
#include "nsIJSScriptObject.h"
#include "nsIScriptObjectOwner.h"
#include "nsIScriptGlobalObject.h"
#include "nsCOMPtr.h"
#include "nsDOMPropEnums.h"
#include "nsIPtr.h"
#include "nsString.h"
#include "nsIDOMElement.h"
#include "nsIDOMDocument.h"
#include "nsIDOMAttr.h"
#include "nsIDOMProcessingInstruction.h"
#include "nsIDOMCDATASection.h"
#include "nsIDOMStyleSheetCollection.h"
#include "nsIDOMText.h"
#include "nsIDOMDOMImplementation.h"
#include "nsIDOMDocumentType.h"
#include "nsIDOMEntityReference.h"
#include "nsIDOMNSDocument.h"
#include "nsIDOMComment.h"
#include "nsIDOMDocumentFragment.h"
#include "nsIDOMRange.h"
#include "nsIDOMNodeList.h"


static NS_DEFINE_IID(kIScriptObjectOwnerIID, NS_ISCRIPTOBJECTOWNER_IID);
static NS_DEFINE_IID(kIJSScriptObjectIID, NS_IJSSCRIPTOBJECT_IID);
static NS_DEFINE_IID(kIScriptGlobalObjectIID, NS_ISCRIPTGLOBALOBJECT_IID);
static NS_DEFINE_IID(kIElementIID, NS_IDOMELEMENT_IID);
static NS_DEFINE_IID(kIDocumentIID, NS_IDOMDOCUMENT_IID);
static NS_DEFINE_IID(kIAttrIID, NS_IDOMATTR_IID);
static NS_DEFINE_IID(kIProcessingInstructionIID, NS_IDOMPROCESSINGINSTRUCTION_IID);
static NS_DEFINE_IID(kICDATASectionIID, NS_IDOMCDATASECTION_IID);
static NS_DEFINE_IID(kIStyleSheetCollectionIID, NS_IDOMSTYLESHEETCOLLECTION_IID);
static NS_DEFINE_IID(kITextIID, NS_IDOMTEXT_IID);
static NS_DEFINE_IID(kIDOMImplementationIID, NS_IDOMDOMIMPLEMENTATION_IID);
static NS_DEFINE_IID(kIDocumentTypeIID, NS_IDOMDOCUMENTTYPE_IID);
static NS_DEFINE_IID(kIEntityReferenceIID, NS_IDOMENTITYREFERENCE_IID);
static NS_DEFINE_IID(kINSDocumentIID, NS_IDOMNSDOCUMENT_IID);
static NS_DEFINE_IID(kICommentIID, NS_IDOMCOMMENT_IID);
static NS_DEFINE_IID(kIDocumentFragmentIID, NS_IDOMDOCUMENTFRAGMENT_IID);
static NS_DEFINE_IID(kIRangeIID, NS_IDOMRANGE_IID);
static NS_DEFINE_IID(kINodeListIID, NS_IDOMNODELIST_IID);

NS_DEF_PTR(nsIDOMElement);
NS_DEF_PTR(nsIDOMDocument);
NS_DEF_PTR(nsIDOMAttr);
NS_DEF_PTR(nsIDOMProcessingInstruction);
NS_DEF_PTR(nsIDOMCDATASection);
NS_DEF_PTR(nsIDOMStyleSheetCollection);
NS_DEF_PTR(nsIDOMText);
NS_DEF_PTR(nsIDOMDOMImplementation);
NS_DEF_PTR(nsIDOMDocumentType);
NS_DEF_PTR(nsIDOMEntityReference);
NS_DEF_PTR(nsIDOMNSDocument);
NS_DEF_PTR(nsIDOMComment);
NS_DEF_PTR(nsIDOMDocumentFragment);
NS_DEF_PTR(nsIDOMRange);
NS_DEF_PTR(nsIDOMNodeList);

//
// Document property ids
//
enum Document_slots {
  DOCUMENT_DOCTYPE = -1,
  DOCUMENT_IMPLEMENTATION = -2,
  DOCUMENT_DOCUMENTELEMENT = -3,
  NSDOCUMENT_WIDTH = -4,
  NSDOCUMENT_HEIGHT = -5,
  NSDOCUMENT_STYLESHEETS = -6
};

/***********************************************************************/
//
// Document Properties Getter
//
PR_STATIC_CALLBACK(JSBool)
GetDocumentProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  nsIDOMDocument *a = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == a) {
    return JS_TRUE;
  }

  if (JSVAL_IS_INT(id)) {
    nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
    nsCOMPtr<nsIScriptSecurityManager> secMan;
    if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
    }
    switch(JSVAL_TO_INT(id)) {
      case DOCUMENT_DOCTYPE:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_DOCTYPE, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        nsIDOMDocumentType* prop;
        nsresult result = NS_OK;
        result = a->GetDoctype(&prop);
        if (NS_SUCCEEDED(result)) {
          // get the js object
          nsJSUtils::nsConvertObjectToJSVal((nsISupports *)prop, cx, vp);
        }
        else {
          return nsJSUtils::nsReportError(cx, result);
        }
        break;
      }
      case DOCUMENT_IMPLEMENTATION:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_IMPLEMENTATION, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        nsIDOMDOMImplementation* prop;
        nsresult result = NS_OK;
        result = a->GetImplementation(&prop);
        if (NS_SUCCEEDED(result)) {
          // get the js object
          nsJSUtils::nsConvertObjectToJSVal((nsISupports *)prop, cx, vp);
        }
        else {
          return nsJSUtils::nsReportError(cx, result);
        }
        break;
      }
      case DOCUMENT_DOCUMENTELEMENT:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_DOCUMENTELEMENT, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        nsIDOMElement* prop;
        nsresult result = NS_OK;
        result = a->GetDocumentElement(&prop);
        if (NS_SUCCEEDED(result)) {
          // get the js object
          nsJSUtils::nsConvertObjectToJSVal((nsISupports *)prop, cx, vp);
        }
        else {
          return nsJSUtils::nsReportError(cx, result);
        }
        break;
      }
      case NSDOCUMENT_WIDTH:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_NSDOCUMENT_WIDTH, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        PRInt32 prop;
        nsIDOMNSDocument* b;
        if (NS_OK == a->QueryInterface(kINSDocumentIID, (void **)&b)) {
          nsresult result = NS_OK;
          result = b->GetWidth(&prop);
          if(NS_SUCCEEDED(result)) {
          *vp = INT_TO_JSVAL(prop);
            NS_RELEASE(b);
          }
          else {
            NS_RELEASE(b);
            return nsJSUtils::nsReportError(cx, result);
          }
        }
        else {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_WRONG_TYPE_ERR);
        }
        break;
      }
      case NSDOCUMENT_HEIGHT:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_NSDOCUMENT_HEIGHT, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        PRInt32 prop;
        nsIDOMNSDocument* b;
        if (NS_OK == a->QueryInterface(kINSDocumentIID, (void **)&b)) {
          nsresult result = NS_OK;
          result = b->GetHeight(&prop);
          if(NS_SUCCEEDED(result)) {
          *vp = INT_TO_JSVAL(prop);
            NS_RELEASE(b);
          }
          else {
            NS_RELEASE(b);
            return nsJSUtils::nsReportError(cx, result);
          }
        }
        else {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_WRONG_TYPE_ERR);
        }
        break;
      }
      case NSDOCUMENT_STYLESHEETS:
      {
        PRBool ok = PR_FALSE;
        secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_NSDOCUMENT_STYLESHEETS, PR_FALSE, &ok);
        if (!ok) {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
        }
        nsIDOMStyleSheetCollection* prop;
        nsIDOMNSDocument* b;
        if (NS_OK == a->QueryInterface(kINSDocumentIID, (void **)&b)) {
          nsresult result = NS_OK;
          result = b->GetStyleSheets(&prop);
          if(NS_SUCCEEDED(result)) {
          // get the js object
          nsJSUtils::nsConvertObjectToJSVal((nsISupports *)prop, cx, vp);
            NS_RELEASE(b);
          }
          else {
            NS_RELEASE(b);
            return nsJSUtils::nsReportError(cx, result);
          }
        }
        else {
          return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_WRONG_TYPE_ERR);
        }
        break;
      }
      default:
        return nsJSUtils::nsCallJSScriptObjectGetProperty(a, cx, id, vp);
    }
  }
  else {
    return nsJSUtils::nsCallJSScriptObjectGetProperty(a, cx, id, vp);
  }

  return PR_TRUE;
}

/***********************************************************************/
//
// Document Properties Setter
//
PR_STATIC_CALLBACK(JSBool)
SetDocumentProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  nsIDOMDocument *a = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == a) {
    return JS_TRUE;
  }

  if (JSVAL_IS_INT(id)) {
    nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
    nsCOMPtr<nsIScriptSecurityManager> secMan;
    if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
    }
    switch(JSVAL_TO_INT(id)) {
      case 0:
      default:
        return nsJSUtils::nsCallJSScriptObjectSetProperty(a, cx, id, vp);
    }
  }
  else {
    return nsJSUtils::nsCallJSScriptObjectSetProperty(a, cx, id, vp);
  }

  return PR_TRUE;
}


//
// Document finalizer
//
PR_STATIC_CALLBACK(void)
FinalizeDocument(JSContext *cx, JSObject *obj)
{
  nsJSUtils::nsGenericFinalize(cx, obj);
}


//
// Document enumerate
//
PR_STATIC_CALLBACK(JSBool)
EnumerateDocument(JSContext *cx, JSObject *obj)
{
  return nsJSUtils::nsGenericEnumerate(cx, obj);
}


//
// Document resolve
//
PR_STATIC_CALLBACK(JSBool)
ResolveDocument(JSContext *cx, JSObject *obj, jsval id)
{
  return nsJSUtils::nsGenericResolve(cx, obj, id);
}


//
// Native method CreateElement
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateElement(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMElement* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATEELEMENT, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateElement(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateDocumentFragment
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateDocumentFragment(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMDocumentFragment* nativeRet;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATEDOCUMENTFRAGMENT, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {

    result = nativeThis->CreateDocumentFragment(&nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateTextNode
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateTextNode(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMText* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATETEXTNODE, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateTextNode(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateComment
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateComment(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMComment* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATECOMMENT, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateComment(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateCDATASection
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateCDATASection(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMCDATASection* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATECDATASECTION, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateCDATASection(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateProcessingInstruction
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateProcessingInstruction(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMProcessingInstruction* nativeRet;
  nsAutoString b0;
  nsAutoString b1;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATEPROCESSINGINSTRUCTION, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 2) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);
    nsJSUtils::nsConvertJSValToString(b1, cx, argv[1]);

    result = nativeThis->CreateProcessingInstruction(b0, b1, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateAttribute
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateAttribute(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMAttr* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATEATTRIBUTE, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateAttribute(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateEntityReference
//
PR_STATIC_CALLBACK(JSBool)
DocumentCreateEntityReference(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMEntityReference* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_CREATEENTITYREFERENCE, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->CreateEntityReference(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method GetElementsByTagName
//
PR_STATIC_CALLBACK(JSBool)
DocumentGetElementsByTagName(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *nativeThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsresult result = NS_OK;
  nsIDOMNodeList* nativeRet;
  nsAutoString b0;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_DOCUMENT_GETELEMENTSBYTAGNAME, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 1) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);

    result = nativeThis->GetElementsByTagName(b0, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateElementWithNameSpace
//
PR_STATIC_CALLBACK(JSBool)
NSDocumentCreateElementWithNameSpace(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *privateThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsIDOMNSDocumentPtr nativeThis = nsnull;
  nsresult result = NS_OK;
  if (NS_OK != privateThis->QueryInterface(kINSDocumentIID, (void **)&nativeThis)) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_WRONG_TYPE_ERR);
  }

  nsIDOMElement* nativeRet;
  nsAutoString b0;
  nsAutoString b1;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_NSDOCUMENT_CREATEELEMENTWITHNAMESPACE, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {
    if (argc < 2) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_TOO_FEW_PARAMETERS_ERR);
    }

    nsJSUtils::nsConvertJSValToString(b0, cx, argv[0]);
    nsJSUtils::nsConvertJSValToString(b1, cx, argv[1]);

    result = nativeThis->CreateElementWithNameSpace(b0, b1, &nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


//
// Native method CreateRange
//
PR_STATIC_CALLBACK(JSBool)
NSDocumentCreateRange(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  nsIDOMDocument *privateThis = (nsIDOMDocument*)nsJSUtils::nsGetNativeThis(cx, obj);
  nsIDOMNSDocumentPtr nativeThis = nsnull;
  nsresult result = NS_OK;
  if (NS_OK != privateThis->QueryInterface(kINSDocumentIID, (void **)&nativeThis)) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_WRONG_TYPE_ERR);
  }

  nsIDOMRange* nativeRet;

  *rval = JSVAL_NULL;

  nsIScriptContext *scriptCX = (nsIScriptContext *)JS_GetContextPrivate(cx);
  nsCOMPtr<nsIScriptSecurityManager> secMan;
  if (NS_OK != scriptCX->GetSecurityManager(getter_AddRefs(secMan))) {
    return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECMAN_ERR);
  }
  {
    PRBool ok;
    secMan->CheckScriptAccess(scriptCX, obj, NS_DOM_PROP_NSDOCUMENT_CREATERANGE, PR_FALSE, &ok);
    if (!ok) {
      return nsJSUtils::nsReportError(cx, NS_ERROR_DOM_SECURITY_ERR);
    }
  }

  // If there's no private data, this must be the prototype, so ignore
  if (nsnull == nativeThis) {
    return JS_TRUE;
  }

  {

    result = nativeThis->CreateRange(&nativeRet);
    if (NS_FAILED(result)) {
      return nsJSUtils::nsReportError(cx, result);
    }

    nsJSUtils::nsConvertObjectToJSVal(nativeRet, cx, rval);
  }

  return JS_TRUE;
}


/***********************************************************************/
//
// class for Document
//
JSClass DocumentClass = {
  "Document", 
  JSCLASS_HAS_PRIVATE | JSCLASS_PRIVATE_IS_NSISUPPORTS,
  JS_PropertyStub,
  JS_PropertyStub,
  GetDocumentProperty,
  SetDocumentProperty,
  EnumerateDocument,
  ResolveDocument,
  JS_ConvertStub,
  FinalizeDocument
};


//
// Document class properties
//
static JSPropertySpec DocumentProperties[] =
{
  {"doctype",    DOCUMENT_DOCTYPE,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {"implementation",    DOCUMENT_IMPLEMENTATION,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {"documentElement",    DOCUMENT_DOCUMENTELEMENT,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {"width",    NSDOCUMENT_WIDTH,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {"height",    NSDOCUMENT_HEIGHT,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {"styleSheets",    NSDOCUMENT_STYLESHEETS,    JSPROP_ENUMERATE | JSPROP_READONLY},
  {0}
};


//
// Document class methods
//
static JSFunctionSpec DocumentMethods[] = 
{
  {"createElement",          DocumentCreateElement,     1},
  {"createDocumentFragment",          DocumentCreateDocumentFragment,     0},
  {"createTextNode",          DocumentCreateTextNode,     1},
  {"createComment",          DocumentCreateComment,     1},
  {"createCDATASection",          DocumentCreateCDATASection,     1},
  {"createProcessingInstruction",          DocumentCreateProcessingInstruction,     2},
  {"createAttribute",          DocumentCreateAttribute,     1},
  {"createEntityReference",          DocumentCreateEntityReference,     1},
  {"getElementsByTagName",          DocumentGetElementsByTagName,     1},
  {"createElementWithNameSpace",          NSDocumentCreateElementWithNameSpace,     2},
  {"createRange",          NSDocumentCreateRange,     0},
  {0}
};


//
// Document constructor
//
PR_STATIC_CALLBACK(JSBool)
Document(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
  return JS_FALSE;
}


//
// Document class initialization
//
extern "C" NS_DOM nsresult NS_InitDocumentClass(nsIScriptContext *aContext, void **aPrototype)
{
  JSContext *jscontext = (JSContext *)aContext->GetNativeContext();
  JSObject *proto = nsnull;
  JSObject *constructor = nsnull;
  JSObject *parent_proto = nsnull;
  JSObject *global = JS_GetGlobalObject(jscontext);
  jsval vp;

  if ((PR_TRUE != JS_LookupProperty(jscontext, global, "Document", &vp)) ||
      !JSVAL_IS_OBJECT(vp) ||
      ((constructor = JSVAL_TO_OBJECT(vp)) == nsnull) ||
      (PR_TRUE != JS_LookupProperty(jscontext, JSVAL_TO_OBJECT(vp), "prototype", &vp)) || 
      !JSVAL_IS_OBJECT(vp)) {

    if (NS_OK != NS_InitNodeClass(aContext, (void **)&parent_proto)) {
      return NS_ERROR_FAILURE;
    }
    proto = JS_InitClass(jscontext,     // context
                         global,        // global object
                         parent_proto,  // parent proto 
                         &DocumentClass,      // JSClass
                         Document,            // JSNative ctor
                         0,             // ctor args
                         DocumentProperties,  // proto props
                         DocumentMethods,     // proto funcs
                         nsnull,        // ctor props (static)
                         nsnull);       // ctor funcs (static)
    if (nsnull == proto) {
      return NS_ERROR_FAILURE;
    }

  }
  else if ((nsnull != constructor) && JSVAL_IS_OBJECT(vp)) {
    proto = JSVAL_TO_OBJECT(vp);
  }
  else {
    return NS_ERROR_FAILURE;
  }

  if (aPrototype) {
    *aPrototype = proto;
  }
  return NS_OK;
}


//
// Method for creating a new Document JavaScript object
//
extern "C" NS_DOM nsresult NS_NewScriptDocument(nsIScriptContext *aContext, nsISupports *aSupports, nsISupports *aParent, void **aReturn)
{
  NS_PRECONDITION(nsnull != aContext && nsnull != aSupports && nsnull != aReturn, "null argument to NS_NewScriptDocument");
  JSObject *proto;
  JSObject *parent;
  nsIScriptObjectOwner *owner;
  JSContext *jscontext = (JSContext *)aContext->GetNativeContext();
  nsresult result = NS_OK;
  nsIDOMDocument *aDocument;

  if (nsnull == aParent) {
    parent = nsnull;
  }
  else if (NS_OK == aParent->QueryInterface(kIScriptObjectOwnerIID, (void**)&owner)) {
    if (NS_OK != owner->GetScriptObject(aContext, (void **)&parent)) {
      NS_RELEASE(owner);
      return NS_ERROR_FAILURE;
    }
    NS_RELEASE(owner);
  }
  else {
    return NS_ERROR_FAILURE;
  }

  if (NS_OK != NS_InitDocumentClass(aContext, (void **)&proto)) {
    return NS_ERROR_FAILURE;
  }

  result = aSupports->QueryInterface(kIDocumentIID, (void **)&aDocument);
  if (NS_OK != result) {
    return result;
  }

  // create a js object for this class
  *aReturn = JS_NewObject(jscontext, &DocumentClass, proto, parent);
  if (nsnull != *aReturn) {
    // connect the native object to the js object
    JS_SetPrivate(jscontext, (JSObject *)*aReturn, aDocument);
  }
  else {
    NS_RELEASE(aDocument);
    return NS_ERROR_FAILURE; 
  }

  return NS_OK;
}
