/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * - Useful language functions
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 *
 * Copyright (C) 2009 Pur3 Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "framework.h"
//#include "fiasco_finder.h"




void scTrace(CScriptVar *ca, void *userdata);
void scObjectDump(CScriptVar *ca, void *);
void scObjectClone(CScriptVar *ca, void *);
void scMathRand(CScriptVar *ca, void *);
void scMathRandInt(CScriptVar *ca, void *);
void scCharToInt(CScriptVar *ca, void *);
void scStringIndexOf(CScriptVar *ca, void *);
void scStringSubstring(CScriptVar *ca, void *);
void scStringCharAt(CScriptVar *ca, void *);
void scStringCharCodeAt(CScriptVar *ca, void *);
void scStringSplit(CScriptVar *ca, void *);
void scStringFromCharCode(CScriptVar *ca, void *);
void scStringToLowerCase(CScriptVar *ca,void *);
void scStringToUpperCase(CScriptVar *ca,void *);
void scIntegerParseInt(CScriptVar *ca, void *);
void scIntegerValueOf(CScriptVar *ca, void *);
void scJSONStringify(CScriptVar *ca, void *);
void scExec(CScriptVar *ca, void *data);
void scEval(CScriptVar *ca, void *data);
void scArrayContains(CScriptVar *ca, void *data);
void scArrayRemove(CScriptVar *ca, void *data);
void scArrayJoin(CScriptVar *ca, void *data);


// ----------------------------------------------- Actual Functions
void scTrace(CScriptVar *ca, void *userdata) {
    tinyjs *js = (tinyjs*)userdata;
    js->root->trace();
}

void scObjectDump(CScriptVar *ca, void *) {
    ca->getParameter("this")->trace("> ");
}

void scObjectClone(CScriptVar *ca, void *) {
    CScriptVar *obj = ca->getParameter("this");
    ca->getReturnVar()->copyValue(obj);
}

void scMathRand(CScriptVar *ca, void *) {
    ca->getReturnVar()->setDouble((double)rand()/RAND_MAX);
}

void scMathRandInt(CScriptVar *ca, void *) {
    i32 min = ca->getParameter("min")->getInt();
    i32 max = ca->getParameter("max")->getInt();
    i32 val = min + (i32)((long)rand()*(1+max-min)/RAND_MAX);
    if (val>max) val=max;
    ca->getReturnVar()->setInt(val);
}

void scCharToInt(CScriptVar *ca, void *) {
    string str = ca->getParameter("ch")->getString();;
    i32 val = 0;
    if (str.length()>0)
        val = (i32)str.c_str()[0];
    ca->getReturnVar()->setInt(val);
}

void scStringIndexOf(CScriptVar *ca, void *) {
    string str = ca->getParameter("this")->getString();
    string search = ca->getParameter("search")->getString();
    strsize point = str.find(search);
    i32 val = (i32) ((point < 0) ? -1 : point);
    ca->getReturnVar()->setInt(val);
}

void scStringSubstring(CScriptVar *ca, void *) {
    string str = ca->getParameter("this")->getString();
    i32 lo = ca->getParameter("lo")->getInt();
    strsize hi;
    if(ca->findChild("hi") == nullptr)
    {
       hi = str.get_length();
    }
    else
    {
       hi = ca->getParameter("hi")->getInt();
    }

    strsize l = hi-lo;
    if (l>0 && lo>=0 && lo+l<=(i32)str.length())
      ca->getReturnVar()->setString(str.substr(lo, l));
    else
      ca->getReturnVar()->setString("");
}


void scStringToLowerCase(CScriptVar *ca,void *) {
   ca->getReturnVar()->setString(::str::ansi_lower(ca->getParameter("this")->getString()));
}

void scStringToUpperCase(CScriptVar *ca,void *) {
   ca->getReturnVar()->setString(::str::ansi_upper(ca->getParameter("this")->getString()));
}

void scStringCharAt(CScriptVar *ca, void *) {
    string str = ca->getParameter("this")->getString();
    i32 point = ca->getParameter("pos")->getInt();
    if (point>=0 && point<(i32)str.length())
      ca->getReturnVar()->setString(str.substr(point, 1));
    else
      ca->getReturnVar()->setString("");
}

void scStringCharCodeAt(CScriptVar *ca, void *) {
    string str = ca->getParameter("this")->getString();
    i32 point = ca->getParameter("pos")->getInt();
    if (point>=0 && point<(i32)str.length())
      ca->getReturnVar()->setInt(str[point]);
    else
      ca->getReturnVar()->setInt(0);
}

void scStringSplit(CScriptVar *ca, void *) {
    string str = ca->getParameter("this")->getString();
    string sep = ca->getParameter("separator")->getString();
    CScriptVar *result = ca->getReturnVar();
    result->setArray();
    i32 length = 0;

    strsize pos = str.find(sep);
    while (pos>= 0) {
      result->setArrayIndex(length++, new CScriptVar(str.substr(0,pos)));
      str = str.substr(pos+1);
      pos = str.find(sep);
    }

    if (str.size()>0)
      result->setArrayIndex(length++, new CScriptVar(str));
}

void scStringFromCharCode(CScriptVar *ca, void *) {
    char str[2];
    str[0] = ca->getParameter("char")->getInt();
    str[1] = 0;
    ca->getReturnVar()->setString(str);
}

void scIntegerParseInt(CScriptVar *ca, void *) {
    string str = ca->getParameter("str")->getString();
    i32 val = (i32) strtol(str.c_str(),0,0);
    ca->getReturnVar()->setInt(val);
}

void scIntegerValueOf(CScriptVar *ca, void *) {
    string str = ca->getParameter("str")->getString();

    i32 val = 0;
    if (str.length()==1)
      val = str[0];
    ca->getReturnVar()->setInt(val);
}

void scJSONStringify(CScriptVar *ca, void *) {
    string result;
    ca->getParameter("obj")->getJSON(result);
    ca->getReturnVar()->setString(result);
}

void scExec(CScriptVar *ca, void *data) {
    tinyjs *tinyJS = (tinyjs *)data;
    string str = ca->getParameter("jsCode")->getString();
    tinyJS->execute(str);
}

void scEval(CScriptVar *ca, void *data) {
    tinyjs *tinyJS = (tinyjs *)data;
    string str = ca->getParameter("jsCode")->getString();
    ca->setReturnVar(tinyJS->evaluateComplex(str).::payload);
}

void scArrayContains(CScriptVar *ca, void *data) {
  CScriptVar *obj = ca->getParameter("obj");
  CScriptVarLink *v = ca->getParameter("this")->firstChild;

  bool contains = false;
  while (v) {
      if (v->::payload->equals(obj)) {
        contains = true;
        break;
      }
      v = v->nextSibling;
  }

  ca->getReturnVar()->setInt(contains);
}

void scArrayRemove(CScriptVar *ca, void *data) {
  CScriptVar *obj = ca->getParameter("obj");
  int_array removedIndices;
  CScriptVarLink *v;
  // remove
  v = ca->getParameter("this")->firstChild;
  while (v) {
      if (v->::payload->equals(obj)) {
        removedIndices.push_back(v->getIntName());
      }
      v = v->nextSibling;
  }
  // renumber
  v = ca->getParameter("this")->firstChild;
  while (v) {
      i32 n = v->getIntName();
      i32 newn = n;
      for (strsize i=0;i<removedIndices.get_size();i++)
        if (n>=removedIndices[i])
          newn--;
      if (newn!=n)
        v->setIntName(newn);
      v = v->nextSibling;
  }
}

void scArrayJoin(CScriptVar *ca, void *data) {
  string sep = ca->getParameter("separator")->getString();
  CScriptVar *arr = ca->getParameter("this");

  string sstr;
  i32 l = arr->getArrayLength();
  for (i32 i=0;i<l;i++) {
    if (i>0) sstr += sep;
    sstr += arr->getArrayIndex(i)->getString();
  }

  ca->getReturnVar()->setString(sstr);
}

// ----------------------------------------------- Register Functions
void registerFunctions(tinyjs *tinyJS) {
    tinyJS->addNative("function exec(jsCode)", scExec, tinyJS); // execute the given code
    tinyJS->addNative("function eval(jsCode)", scEval, tinyJS); // execute the given string (an expression) and return the result
    tinyJS->addNative("function trace()", scTrace, tinyJS);
    tinyJS->addNative("function Object.dump()", scObjectDump, 0);
    tinyJS->addNative("function Object.clone()", scObjectClone, 0);
    tinyJS->addNative("function Math.rand()", scMathRand, 0);
    tinyJS->addNative("function Math.randInt(min, max)", scMathRandInt, 0);
    tinyJS->addNative("function charToInt(ch)", scCharToInt, 0); //  convert a character to an i32 - get its value
    tinyJS->addNative("function String.indexOf(search)", scStringIndexOf, 0); // find the position of a string in a string, -1 if not
    tinyJS->addNative("function String.substring(lo,hi)", scStringSubstring, 0);
    tinyJS->addNative("function String.charAt(pos)", scStringCharAt, 0);
    tinyJS->addNative("function String.charCodeAt(pos)", scStringCharCodeAt, 0);
    tinyJS->addNative("function String.fromCharCode(char)", scStringFromCharCode, 0);
    tinyJS->addNative("function String.toUpperCase()",scStringToUpperCase,0);
    tinyJS->addNative("function String.toLowerCase()",scStringToLowerCase,0);
    tinyJS->addNative("function String.split(separator)", scStringSplit, 0);
    tinyJS->addNative("function Integer.parseInt(str)", scIntegerParseInt, 0); // string to i32
    tinyJS->addNative("function Integer.valueOf(str)", scIntegerValueOf, 0); // value of a single character
    tinyJS->addNative("function JSON.stringify(obj, replacer)", scJSONStringify, 0); // convert to JSON. replacer is ignored at the moment
    // JSON.parse is left out as you can (unsafely!) use eval instead
    tinyJS->addNative("function Array.contains(obj)", scArrayContains, 0);
    tinyJS->addNative("function Array.remove(obj)", scArrayRemove, 0);
    tinyJS->addNative("function Array.join(separator)", scArrayJoin, 0);
}

