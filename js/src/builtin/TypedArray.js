/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// ES6 draft rev30 (2014/12/24) 22.2.3.6 %TypedArray%.prototype.entries()
function TypedArrayEntries() {
    // Step 1.
    var O = this;

    // Step 2-3.
    if (!IsObject(O) || !IsTypedArray(O)) {
        return callFunction(CallTypedArrayMethodIfWrapped, O, "TypedArrayEntries");
    }

    // Step 4-6. Bug 1101256: detachment checks

    // Step 7.
    return CreateArrayIterator(O, ITEM_KIND_KEY_AND_VALUE);
}

// ES6 draft rev30 (2014/12/24) 22.2.3.7 %TypedArray%.prototype.every(callbackfn[, thisArg]).
function TypedArrayEvery(callbackfn, thisArg = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, callbackfn, thisArg,
                            "TypedArrayEvery");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.every");
    if (!IsCallable(callbackfn))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, callbackfn));

    // Step 7.
    var T = thisArg;

    // Steps 8-9.
    // Omit steps 9.a-9.c and the 'if' clause in step 9.d, since there are no holes in typed arrays.
    for (var k = 0; k < len; k++) {
        // Steps 9.d.i-9.d.ii.
        var kValue = O[k];

        // Steps 9.d.iii-9.d.iv.
        var testResult = callFunction(callbackfn, T, kValue, k, O);

        // Step 9.d.v.
        if (!testResult)
            return false;
    }

    // Step 10.
    return true;
}

// ES6 draft rev29 (2014/12/06) 22.2.3.8 %TypedArray%.prototype.fill(value [, start [, end ]])
function TypedArrayFill(value, start = 0, end = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, value, start, end,
                            "TypedArrayFill");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Steps 6-7.
    var relativeStart = ToInteger(start);

    // Step 8.
    var k = relativeStart < 0
            ? std_Math_max(len + relativeStart, 0)
            : std_Math_min(relativeStart, len);

    // Steps 9-10.
    var relativeEnd = end === undefined ? len : ToInteger(end);

    // Step 11.
    var final = relativeEnd < 0
                ? std_Math_max(len + relativeEnd, 0)
                : std_Math_min(relativeEnd, len);

    // Step 12.
    for (; k < final; k++) {
        O[k] = value;
    }

    // Step 13.
    return O;
}

// ES6 draft rev28 (2014/10/14) 22.2.3.10 %TypedArray%.prototype.find(predicate[, thisArg]).
function TypedArrayFind(predicate, thisArg = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, predicate, thisArg,
                            "TypedArrayFind");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.find");
    if (!IsCallable(predicate))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, predicate));

    // Step 7.
    var T = thisArg;

    // Steps 8-9.
    // Steps a (implicit), and g.
    for (var k = 0; k < len; k++) {
        // Steps a-c.
        var kValue = O[k];
        // Steps d-f.
        if (callFunction(predicate, T, kValue, k, O))
            return kValue;
    }

    // Step 10.
    return undefined;
}

// ES6 draft rev28 (2014/10/14) 22.2.3.11 %TypedArray%.prototype.findIndex(predicate[, thisArg]).
function TypedArrayFindIndex(predicate, thisArg = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, predicate, thisArg,
                            "TypedArrayFindIndex");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.findIndex");
    if (!IsCallable(predicate))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, predicate));

    // Step 7.
    var T = thisArg;

    // Steps 8-9.
    // Steps a (implicit), and g.
    for (var k = 0; k < len; k++) {
        // Steps a-f.
        if (callFunction(predicate, T, O[k], k, O))
            return k;
    }

    // Step 10.
    return -1;
}

// ES6 draft rev29 (2014/12/06) 22.2.3.13 %TypedArray%.prototype.indexOf(searchElement[, fromIndex]).
function TypedArrayIndexOf(searchElement, fromIndex = 0) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, searchElement, fromIndex,
                            "TypedArrayIndexOf");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (len === 0)
        return -1;

    // Steps 7-8.
    var n = ToInteger(fromIndex);

    // Step 9.
    if (n >= len)
        return -1;

    var k;
    // Step 10.
    if (n >= 0) {
        k = n;
    }
    // Step 11.
    else {
        // Step a.
        k = len + n;
        // Step b.
        if (k < 0)
            k = 0;
    }

    // Step 12.
    // Omit steps a-b, since there are no holes in typed arrays.
    for (; k < len; k++) {
        if (O[k] === searchElement)
            return k;
    }

    // Step 13.
    return -1;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.14 %TypedArray%.prototype.join(separator).
function TypedArrayJoin(separator) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, separator, "TypedArrayJoin");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Steps 6-7.
    var sep = separator === undefined ? "," : ToString(separator);

    // Step 8.
    if (len === 0)
        return "";

    // Step 9.
    var element0 = O[0];

    // Steps 10-11.
    // Omit the 'if' clause in step 10, since typed arrays can not have undefined or null elements.
    var R = ToString(element0);

    // Steps 12-13.
    for (var k = 1; k < len; k++) {
        // Step 13.a.
        var S = R + sep;

        // Step 13.b.
        var element = O[k];

        // Steps 13.c-13.d.
        // Omit the 'if' clause in step 13.c, since typed arrays can not have undefined or null elements.
        var next = ToString(element);

        // Step 13.e.
        R = S + next;
    }

    // Step 14.
    return R;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.15 %TypedArray%.prototype.keys()
function TypedArrayKeys() {
    // Step 1.
    var O = this;

    // Step 2-3.
    if (!IsObject(O) || !IsTypedArray(O)) {
        return callFunction(CallTypedArrayMethodIfWrapped, O, "TypedArrayKeys");
    }

    // Step 4-6. Bug 1101256: detachment checks

    // Step 7.
    return CreateArrayIterator(O, ITEM_KIND_KEY);
}

// ES6 draft rev29 (2014/12/06) 22.2.3.16 %TypedArray%.prototype.lastIndexOf(searchElement [,fromIndex]).
function TypedArrayLastIndexOf(searchElement, fromIndex = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, searchElement, fromIndex,
                            "TypedArrayLastIndexOf");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (len === 0)
        return -1;

    // Steps 7-8.
    var n = fromIndex === undefined ? len - 1 : ToInteger(fromIndex);

    // Steps 9-10.
    var k = n >= 0 ? std_Math_min(n, len - 1) : len + n;

    // Step 11.
    // Omit steps a-b, since there are no holes in typed arrays.
    for (; k >= 0; k--) {
        if (O[k] === searchElement)
            return k;
    }

    // Step 12.
    return -1;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.19 %TypedArray%.prototype.reduce(callbackfn[, initialValue]).
function TypedArrayReduce(callbackfn/*, initialValue*/) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this))
        return callFunction(CallTypedArrayMethodIfWrapped, this, callbackfn, "TypedArrayReduce");

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.reduce");
    if (!IsCallable(callbackfn))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, callbackfn));

    // Step 7.
    if (len === 0 && arguments.length === 1)
        ThrowError(JSMSG_EMPTY_ARRAY_REDUCE);

    // Step 8.
    var k = 0;

    // Steps 9-10.
    // Omit some steps, since 'accumulator' should always be O[0] in step 10 for typed arrays.
    var accumulator = arguments.length > 1 ? arguments[1] : O[k++];

    // Step 11.
    // Omit steps 11.b-11.c and the 'if' clause in step 11.d, since there are no holes in typed arrays.
    for (; k < len; k++) {
        accumulator = callFunction(callbackfn, undefined, accumulator, O[k], k, O);
    }

    // Step 12.
    return accumulator;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.20 %TypedArray%.prototype.reduceRight(callbackfn[, initialValue]).
function TypedArrayReduceRight(callbackfn/*, initialValue*/) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this))
        return callFunction(CallTypedArrayMethodIfWrapped, this, callbackfn, "TypedArrayReduceRight");

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.reduceRight");
    if (!IsCallable(callbackfn))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, callbackfn));

    // Step 7.
    if (len === 0 && arguments.length === 1)
        ThrowError(JSMSG_EMPTY_ARRAY_REDUCE);

    // Step 8.
    var k = len - 1;

    // Steps 9-10.
    // Omit some steps, since 'accumulator' should always be O[len-1] in step 10 for typed arrays.
    var accumulator = arguments.length > 1 ? arguments[1] : O[k--];

    // Step 11.
    // Omit steps 11.b-11.c and the 'if' clause in step 11.d, since there are no holes in typed arrays.
    for (; k >= 0; k--) {
        accumulator = callFunction(callbackfn, undefined, accumulator, O[k], k, O);
    }

    // Step 12.
    return accumulator;
}

// ES6 draft rev29 (2014/12/06) 22.2.3.21 %TypedArray%.prototype.reverse().
function TypedArrayReverse() {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, "TypedArrayReverse");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    var middle = std_Math_floor(len / 2);

    // Steps 7-8.
    // Omit some steps, since there are no holes in typed arrays.
    // Especially all the HasProperty/*exists checks always succeed.
    for (var lower = 0; lower !== middle; lower++) {
        // Step 8.a.
        var upper = len - lower - 1;

        // Step 8.f.i.
        var lowerValue = O[lower];

        // Step 8.i.i.
        var upperValue = O[upper];

        // We always end up in the step 8.j. case.
        O[lower] = upperValue;
        O[upper] = lowerValue;
    }

    // Step 9.
    return O;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.25 %TypedArray%.prototype.some(callbackfn[, thisArg]).
function TypedArraySome(callbackfn, thisArg = undefined) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, callbackfn, thisArg,
                            "TypedArraySome");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-5.
    var len = TypedArrayLength(O);

    // Step 6.
    if (arguments.length === 0)
        ThrowError(JSMSG_MISSING_FUN_ARG, 0, "%TypedArray%.prototype.some");
    if (!IsCallable(callbackfn))
        ThrowError(JSMSG_NOT_FUNCTION, DecompileArg(0, callbackfn));

    // Step 7.
    var T = thisArg;

    // Steps 8-9.
    // Omit steps 9.a-9.c and the 'if' clause in step 9.d, since there are no holes in typed arrays.
    for (var k = 0; k < len; k++) {
        // Steps 9.d.i-9.d.ii.
        var kValue = O[k];

        // Steps 9.d.iii-9.d.iv.
        var testResult = callFunction(callbackfn, T, kValue, k, O);

        // Step 9.d.v.
        if (testResult)
            return true;
    }

    // Step 10.
    return false;
}

// ES6 draft rev30 (2014/12/24) 22.2.3.30 %TypedArray%.prototype.values()
function TypedArrayValues() {
    // Step 1.
    var O = this;

    // Step 2-3.
    if (!IsObject(O) || !IsTypedArray(O)) {
        return callFunction(CallTypedArrayMethodIfWrapped, O, "TypedArrayValues");
    }

    // Step 4-6. Bug 1101256: detachment checks

    // Step 7.
    return CreateArrayIterator(O, ITEM_KIND_VALUE);
}

// Proposed for ES7:
// https://github.com/tc39/Array.prototype.includes/blob/7c023c19a0/spec.md
function TypedArrayIncludes(searchElement, fromIndex = 0) {
    // This function is not generic.
    if (!IsObject(this) || !IsTypedArray(this)) {
        return callFunction(CallTypedArrayMethodIfWrapped, this, searchElement,
                            fromIndex, "TypedArrayIncludes");
    }

    // Steps 1-2.
    var O = this;

    // Steps 3-4.
    var len = TypedArrayLength(O);

    // Step 5.
    if (len === 0)
        return false;

    // Steps 6-7.
    var n = ToInteger(fromIndex);

    var k;
    // Step 8.
    if (n >= 0) {
        k = n;
    }
    // Step 9.
    else {
        // Step a.
        k = len + n;
        // Step b.
        if (k < 0)
            k = 0;
    }

    // Step 10.
    while (k < len) {
        // Steps a-c.
        if (SameValueZero(searchElement, O[k]))
            return true;

        // Step d.
        k++;
    }

    // Step 11.
    return false;
}
