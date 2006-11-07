/* ***** BEGIN LICENSE BLOCK ***** 
 Version: MPL 1.1/GPL 2.0/LGPL 2.1 

The contents of this file are subject to the Mozilla Public License Version 1.1 (the 
"License"); you may not use this file except in compliance with the License. You may obtain 
a copy of the License at http://www.mozilla.org/MPL/ 

Software distributed under the License is distributed on an "AS IS" basis, WITHOUT 
WARRANTY OF ANY KIND, either express or implied. See the License for the specific 
language governing rights and limitations under the License. 

The Original Code is [Open Source Virtual Machine.] 

The Initial Developer of the Original Code is Adobe System Incorporated.  Portions created 
by the Initial Developer are Copyright (C)[ 2005-2006 ] Adobe Systems Incorporated. All Rights 
Reserved. 

Contributor(s): Adobe AS3 Team

Alternatively, the contents of this file may be used under the terms of either the GNU 
General Public License Version 2 or later (the "GPL"), or the GNU Lesser General Public 
License Version 2.1 or later (the "LGPL"), in which case the provisions of the GPL or the 
LGPL are applicable instead of those above. If you wish to allow use of your version of this 
file only under the terms of either the GPL or the LGPL, and not to allow others to use your 
version of this file under the terms of the MPL, indicate your decision by deleting provisions 
above and replace them with the notice and other provisions required by the GPL or the 
LGPL. If you do not delete the provisions above, a recipient may use your version of this file 
under the terms of any one of the MPL, the GPL or the LGPL. 

 ***** END LICENSE BLOCK ***** */

import DefaultClass.*;


var SECTION = "Definitions";       							// provide a document reference (ie, ECMA section)
var VERSION = "AS 3.0";  								// Version of JavaScript or ECMA
var TITLE   = "Override public function in default class extending default class";    	// Provide ECMA section title or a description
var BUGNUMBER = "";

startTest();                							// leave this alone


var CLASSDEFN = new ExtDefaultOverRidePublic();
var myString = "teststring";

AddTestCase( "CLASSDEFN.setPubString(myString); CLASSDEFN.orSetString", "PASSED", (CLASSDEFN.setPubString(myString), CLASSDEFN.orSetString ) );
AddTestCase( "CLASSDEFN.getPubString()" , "override_teststring_override", CLASSDEFN.getPubString() );
AddTestCase( "CLASSDEFN.orGetString" , "PASSED", CLASSDEFN.orGetString );


AddTestCase( "CLASSDEFN.setPubString(null); CLASSDEFN.getPubString()", "override_null_override", (CLASSDEFN.setPubString(null), CLASSDEFN.getPubString()) );
AddTestCase( "CLASSDEFN.setPubString(undefined); CLASSDEFN.getPubString()", "override_null_override", (CLASSDEFN.setPubString(undefined), CLASSDEFN.getPubString()) );


test();       		// Leave this function alone.
			// This function is for executing the test case and then
			// displaying the result on to the console or the LOG file.
