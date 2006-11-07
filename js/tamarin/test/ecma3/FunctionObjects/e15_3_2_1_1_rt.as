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
    var SECTION = "15.3.2.1";
    var VERSION = "ECMA_1";
    startTest();
    var TITLE   = "The Function Constructor";

    writeHeaderToLog( SECTION + " "+ TITLE);

    var testcases = getTestCases();
    test();

function getTestCases() {
    var array:Array = new Array();
    var item:Number = 0;
    
    var thisError:String="no error";

    try{
        var MyObject = Function( "value", "this.value = value; this.valueOf = new  Function( 'return this.value' ); this.toString = new Function( 'return String(this.value);' )" );
    }catch(e1:EvalError){
        thisError=(e1.toString()).substring(0,22);
    }finally{//print(thisError);
        array[item++] = new TestCase(   SECTION,"Function('function body') is not supported","EvalError: Error #1066",thisError);
    }
    var myfunc = new Function();

//    not going to test toString here since it is implementation dependent.
    array[item++] = new TestCase( SECTION,  "myfunc.toString()",     "function Function() {}",    myfunc.toString() );


    thisError="no error";
    try{
        myfunc.toString = Object.prototype.toString;
        myfunc.toString();
    }catch(e:Error){
        thisError = e.toString();
    }finally{//print(thisError);
        array[item++] = new TestCase(   SECTION,
                                    "myfunc = new Function(); myfunc.toString = Object.prototype.toString; myfunc.toString()",
                                    "no error",referenceError(thisError));
    }
    myfunc.myToString = Object.prototype.toString;

	// work around for bug 175820
	var expRes = "[object Function-35]";
	try
	{
		if( Capabilities.isDebugger == false )
			expRes = "[object null]";
	} catch(ee) {
		// do nothing, Capabilities is not defined
	}

    array[item++] = new TestCase( SECTION,  "myfunc = new Function(); myfunc.myToString = Object.prototype.toString; myfunc.myToString()",
                                            expRes,
                                            myfunc.toString() );
    array[item++] = new TestCase( SECTION,  "myfunc.length",                            0,                      myfunc.length );
    array[item++] = new TestCase( SECTION,  "myfunc.prototype.toString()",              "[object Object]",      myfunc.prototype.toString() );

    array[item++] = new TestCase( SECTION,  "myfunc.prototype.constructor",             myfunc,                 myfunc.prototype.constructor );
    //array[item++] = new TestCase( SECTION,  "myfunc.arguments",                         null,myfunc.arguments );

    function MyObject(value){
        this.value = value;
        this.valueOf = function() {return this.value;}
        this.toString = function() {return this.value+'';}
    }


    array[item++] = new TestCase( SECTION,  "var OBJ = new MyObject(true), OBJ.valueOf()",    true,             (OBJ = new MyObject(true), OBJ.valueOf() ) );

    array[item++] = new TestCase( SECTION,  "OBJ.toString()",                           "true", (OBJ = new MyObject(true),OBJ.toString()) );

    OBJ.toString = Object.prototype.toString;
    array[item++] = new TestCase( SECTION,  "OBJ.toString = Object.prototype.toString; OBJ.toString()", "[object Object]",   OBJ.toString());


    MyObject.myToString = Object.prototype.toString;

	// work around to bug 175820
	expRes = "[object Function-2]";
	try{
		if(Capabilities.isDebugger == false)
			expRes = "[object null]";
	} catch( ee2 ) {
		// do nothing
	}
    array[item++] = new TestCase( SECTION,  "MyObject.toString = Object.prototype.toString; MyObject.toString()",    expRes,   MyObject.myToString());

    array[item++] = new TestCase( SECTION,  "MyObject.length",                              1,      MyObject.length );


    array[item++] = new TestCase( SECTION,  "MyObject.prototype.constructor",               MyObject,   MyObject.prototype.constructor );

    //not supported
    //array[item++] = new TestCase( SECTION,  "MyObject.arguments",                           null,MyObject.arguments);

    return ( array );
}
