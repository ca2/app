/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
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
 * so, topic to the following conditions:

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

/* Version 0.1  :  (gw) First published on Google Code
   Version 0.11 :  Making sure the 'root' variable never changes
                   'symbol_axis' added for the current axis of the sybmbol table
   Version 0.12 :  Added findChildOrCreate, changed string passing to use references
                   Fixed broken string encoding in getJSString()
                   Removed getInitCode and added getJSON instead
                   Added nil
                   Added rough JSON parsing
                   Improved example app
   Version 0.13 :  Added tokenEnd/tokenLastEnd to lexer to avoid parsing whitespace
                   Ability to define functions without names
                   Can now do "payload mine = function(a,b) { ... };"
                   Slightly better 'trace' function
                   Added findChildOrCreateByPath function
                   Added simple test suite
                   Added skipping of blocks when not executing
   Version 0.14 :  Added parsing of more number types
                   Added parsing of string defined with '
                   Changed nil to nullptr as per spec, added 'undefined'
                   Now set variables with the correct scope, and treat unknown
                              as 'undefined' rather than failing
                   Added proper (I hope) handling of nullptr and undefined
                   Added === check
   Version 0.15 :  Fix for possible memory leaks
   Version 0.16 :  Removal of un-needed findRecursive calls
                   symbol_axis erased and replaced with 'scopes' stack
                   Added object counting a proper tree structure
                       (Allowing pass by object)
                   Allowed JSON output to output IDs, not strings
                   Added get/set for array indices
                   Changed Callbacks to include user data pointer
                   Added some support for objects
                   Added more Java-esque builtin functions
   Version 0.17 :  Now we don't deepCopy the parent object of the class
                   Added JSON.stringify and eval()
                   Nicer JSON indenting
                   Fixed function output in JSON
                   Added evaluateComplex
                   Fixed some reentrancy issues with evaluate/execute
   Version 0.18 :  Fixed some issues with code being executed when it shouldn't
   Version 0.19 :  Added array.length
                   Changed '__parent' to 'prototype' to bring it more in line with javascript
   Version 0.20 :  Added '%' operator
   Version 0.21 :  Added array type
                   String.length() no more - now String.length
                   Added extra constructors to reduce confusion
                   Fixed checks against undefined
   Version 0.22 :  First part of ardi's changes:
                       sprintf -> sprintf_s
                       extra tokens parsed
                       array memory leak fixed
                   Fixed memory leak in evaluateComplex
                   Fixed memory leak in FOR loops
                   Fixed memory leak for unary minus
   Version 0.23 :  Allowed evaluate[Complex] to take in semi-colon separated
                     statements and then only return the value from the last one.
                     Also checks to make sure *everything* was parsed.
                   Ints + doubles are now stored in binary form (faster + more precise)
   Version 0.24 :  More useful error for maths ops
                   Don't dump everything on a match  < 0.
   Version 0.25 :  Better string escaping
   Version 0.26 :  add CScriptVar::equals
                   add built-in array functions
   Version 0.27 :  Added OZLB's TinyJS.setVariable (with some tweaks)
                   Added OZLB's Maths Functions
   Version 0.28 :  Ternary operator
                   Rudimentary call stack on error
                   Added String Character functions
                   Added shift operators
   Version 0.29 :  Added memory_new object via functions
                   Fixed getString() for double on some platforms
   Version 0.30 :  Rlyeh Mario's patch for Math Functions on VC++
   Version 0.31 :  add exec() to TinyJS functions
                   Now print quoted JSON that can be read by PHP/Python parsers
                   Fixed postfix increment operator

    NOTE:
          Constructing an array with an initial length 'Array(5)' doesn't work
          Recursive loops of data such as a.foo = a; fail to be garbage collected
          length variable cannot be set
          The postfix increment operator returns the current value, not the previous as it should.
          There is no prefix increment operator
          Arrays are implemented as a linked list - hence a lookup time is O(n)

    TODO:
          Utility va-args style function in TinyJS for executing a function directly
          Merge the parsing of expressions/statements so eval("statement") works like we'd expect.

 */

#include "framework.h"
#include "tinyjs.h"
//#include "fiasco_finder.h"
#include <stdio.h>



//#define ASSERT(X) assert(X)
/* Frees the given link IF it isn't owned by anything else */
#define CLEAN(x) { CScriptVarLink *__v = x; if (__v && !__v->owned) { delete __v; } }
/* Create a LINK to point_i32 to VAR and free the old link.
 * BUT this is more clever - it tries to keep the old link if it's not owned to save allocations */
#define CREATE_LINK(LINK, VAR) { if (!LINK || LINK->owned) LINK = memory_new CScriptVarLink(VAR); else LINK->replaceWith(VAR); }


/*using namespace std;

#ifdef _WIN32
#ifdef __DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW memory_new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define memory_new DBG_NEW
   #endif
#endif //__DEBUG
#endif*/

#ifdef __GNUC__
#define vsprintf_s vsnprintf
#define sprintf_s snprintf
#define _strdup strdup
#endif

// ----------------------------------------------------------------------------------- Memory Debug

#define DEBUG_MEMORY 0


bool isWhitespace(char ch);
bool isNumeric(char ch);
bool isNumber(const string &str);
bool isHexadecimal(char ch);
bool isAlpha(char ch);
bool isIDString(const ::string &s);
void replace(string &str, char textFrom, const ::string &textTo);
bool isAlphaNum(const string &str);



#if DEBUG_MEMORY

ref_array < CScriptVar > allocatedVars;
ref_array < CScriptVarLink > allocatedLinks;



void mark_allocated(CScriptVar *v)
{
   allocatedVars.add(v);
}

void mark_deallocated(CScriptVar *v)
{
   for (size_t i=0; i<allocatedVars.size(); i++)
   {
      if (allocatedVars[i] == v)
      {
         allocatedVars.erase(allocatedVars.begin()+i);
         break;
      }
   }
}

void mark_allocated(CScriptVarLink *v)
{
   allocatedLinks.add(v);
}

void mark_deallocated(CScriptVarLink *v)
{
   for (size_t i=0; i<allocatedLinks.size(); i++)
   {
      if (allocatedLinks[i] == v)
      {
         allocatedLinks.erase(allocatedLinks.begin()+i);
         break;
      }
   }
}

void show_allocated()
{
   for (size_t i=0; i<allocatedVars.size(); i++)
   {
      debug_print("ALLOCATED, %d refs\n", allocatedVars[i]->getRefs());
      allocatedVars[i]->trace("  ");
   }
   for (size_t i=0; i<allocatedLinks.size(); i++)
   {
      debug_print("ALLOCATED LINK %s, allocated[%d] to \n", allocatedLinks[i]->name.c_str(), allocatedLinks[i]->payload->getRefs());
      allocatedLinks[i]->payload->trace("  ");
   }
   allocatedVars.clear();
   allocatedLinks.clear();
}
#endif

// ----------------------------------------------------------------------------------- Utils
bool isWhitespace(char ch)
{
   return (ch==' ') || (ch=='\t') || (ch=='\n') || (ch=='\r');
}

bool isNumeric(char ch)
{
   return (ch>='0') && (ch<='9');
}
bool isNumber(const string &str)
{
   for (strsize i=0; i<str.size(); i++)
      if (!isNumeric(str[i])) return false;
   return true;
}
bool isHexadecimal(char ch)
{
   return ((ch>='0') && (ch<='9')) ||
          ((ch>='a') && (ch<='f')) ||
          ((ch>='A') && (ch<='F'));
}
bool isAlpha(char ch)
{
   return ((ch>='a') && (ch<='z')) || ((ch>='A') && (ch<='Z')) || ch=='_';
}

bool isIDString(const ::string &strParam)
{

   auto s = strParam.c_str();

   if (!isAlpha(*s))
      return false;
   while (*s)
   {
      if (!(isAlpha(*s) || isNumeric(*s)))
         return false;
      s++;
   }
   return true;
}

void replace(string &str, char textFrom, const ::string &textTo)
{
   strsize sLen = strlen(textTo);
   strsize iPosition = str.find_index(textFrom);
   while (iPosition >= 0)
   {
      str = str.substr(0, iPosition) + textTo + str.substr(iPosition +1);
      iPosition = str.find_index(textFrom, iPosition +sLen);
   }
}

/// convert the given string into a quoted string suitable for javascript
string getJSString(const string &str)
{
   string nStr = str;
   for (strsize i=0; i<nStr.size(); i++)
   {
      const char *replaceWith = "";
      bool replace = true;

      switch (nStr[i])
      {
      case '\\': replaceWith = "\\\\"; break;
      case '\n': replaceWith = "\\n"; break;
      case '\r': replaceWith = "\\r"; break;
      case '\a': replaceWith = "\\a"; break;
      case '"': replaceWith = "\\\""; break;
      default:
      {
         i32 nCh = ((i32)nStr[i]) &0xFF;
         if (nCh<32 || nCh>127)
         {
            char buffer[5];
            sprintf_s(buffer, 5, "\\x%02X", nCh);
            replaceWith = buffer;
         }
         else replace=false;
      }
      }

      if (replace)
      {
         nStr = nStr.substr(0, i) + replaceWith + nStr.substr(i+1);
         i += strlen(replaceWith)-1;
      }
   }
   return "\"" + nStr + "\"";
}

/** Is the string alphanumeric */
bool isAlphaNum(const string &str)
{
   if (str.size()==0) return true;
   if (!isAlpha(str[0])) return false;
   for (strsize i=0; i<str.size(); i++)
      if (!(isAlpha(str[i]) || isNumeric(str[i])))
         return false;
   return true;
}

// ----------------------------------------------------------------------------------- CSCRIPTEXCEPTION

CScriptException::CScriptException(const string &exceptionText)
{
   text = exceptionText;
}

// ----------------------------------------------------------------------------------- CSCRIPTLEX

CScriptLex::CScriptLex(const string &input)
{
   data = _strdup(input.c_str());
   dataOwned = true;
   dataStart = 0;
   dataEnd = (i32) strlen(data);
   reset();
}

CScriptLex::CScriptLex(CScriptLex *owner, i32 startChar, i32 endChar)
{
   data = owner->data;
   dataOwned = false;
   dataStart = startChar;
   dataEnd = endChar;
   reset();
}

CScriptLex::~CScriptLex(void)
{
   if (dataOwned)
      free((void*)data);
}

void CScriptLex::reset()
{
   dataPos = dataStart;
   tokenStart = 0;
   tokenEnd = 0;
   tokenLastEnd = 0;
   tk = 0;
   tkStr = "";
   getNextCh();
   getNextCh();
   getNextToken();
}

void CScriptLex::match(i32 expected_tk)
{
   if (tk!=expected_tk)
   {
      string errorString ="Got " + getTokenStr(tk) + " expected " + getTokenStr(expected_tk)
                          + " at " + getPosition(tokenStart);
      throw CScriptException(errorString);
   }
   getNextToken();
}

string CScriptLex::getTokenStr(i32 token)
{
   if (token>32 && token<128)
   {
      char buf[4] = "' '";
      buf[1] = (char)token;
      return buf;
   }
   switch (token)
   {
   case LEX_EOF : return "EOF";
   case LEX_ID : return "ID";
   case LEX_INT : return "::i32";
   case LEX_FLOAT : return "FLOAT";
   case LEX_STR : return "STRING";
   case LEX_EQUAL : return "==";
   case LEX_TYPEEQUAL : return "===";
   case LEX_NEQUAL : return "!=";
   case LEX_NTYPEEQUAL : return "!==";
   case LEX_LEQUAL : return "<=";
   case LEX_LSHIFT : return "<<";
   case LEX_LSHIFTEQUAL : return "<<=";
   case LEX_GEQUAL : return ">=";
   case LEX_RSHIFT : return ">>";
   case LEX_RSHIFTUNSIGNED : return ">>";
   case LEX_RSHIFTEQUAL : return ">>=";
   case LEX_PLUSEQUAL : return "+=";
   case LEX_MINUSEQUAL : return "-=";
   case LEX_PLUSPLUS : return "++";
   case LEX_MINUSMINUS : return "--";
   case LEX_ANDEQUAL : return "&=";
   case LEX_ANDAND : return "&&";
   case LEX_OREQUAL : return "|=";
   case LEX_OROR : return "||";
   case LEX_XOREQUAL : return "^=";
   // reserved words
   case LEX_R_IF : return "if";
   case LEX_R_ELSE : return "else";
   case LEX_R_DO : return "do";
   case LEX_R_WHILE : return "while";
   case LEX_R_FOR : return "for";
   case LEX_R_BREAK : return "break";
   case LEX_R_CONTINUE : return "continue";
   case LEX_R_FUNCTION : return "function";
   case LEX_R_RETURN : return "return";
   case LEX_R_VAR : return "payload";
   case LEX_R_TRUE : return "true";
   case LEX_R_FALSE : return "false";
   case LEX_R_NULL : return "null";
   case LEX_R_UNDEFINED : return "undefined";
   case LEX_R_NEW : return "memory_new";
   }

   string msg;
   msg = string("?[") + as_string(token) + "]";
   return msg;
}

void CScriptLex::getNextCh()
{
   currCh = nextCh;
   if (dataPos < dataEnd)
      nextCh = data[dataPos];
   else
      nextCh = 0;
   dataPos++;
}

void CScriptLex::getNextToken()
{
   tk = LEX_EOF;
   tkStr.clear();
   while (currCh && isWhitespace(currCh)) getNextCh();
   // newline comments
   if (currCh=='/' && nextCh=='/')
   {
      while (currCh && currCh!='\n') getNextCh();
      getNextCh();
      getNextToken();
      return;
   }
   // block comments
   if (currCh=='/' && nextCh=='*')
   {
      while (currCh && (currCh!='*' || nextCh!='/')) getNextCh();
      getNextCh();
      getNextCh();
      getNextToken();
      return;
   }
   // record beginning of this token
   tokenStart = dataPos-2;
   // tokens
   if (isAlpha(currCh))   //  IDs
   {
      while (isAlpha(currCh) || isNumeric(currCh))
      {
         tkStr += currCh;
         getNextCh();
      }
      tk = LEX_ID;
      if (tkStr=="if") tk = LEX_R_IF;
      else if (tkStr=="else") tk = LEX_R_ELSE;
      else if (tkStr=="do") tk = LEX_R_DO;
      else if (tkStr=="while") tk = LEX_R_WHILE;
      else if (tkStr=="for") tk = LEX_R_FOR;
      else if (tkStr=="break") tk = LEX_R_BREAK;
      else if (tkStr=="continue") tk = LEX_R_CONTINUE;
      else if (tkStr=="function") tk = LEX_R_FUNCTION;
      else if (tkStr=="return") tk = LEX_R_RETURN;
      else if (tkStr=="payload") tk = LEX_R_VAR;
      else if (tkStr=="true") tk = LEX_R_TRUE;
      else if (tkStr=="false") tk = LEX_R_FALSE;
      else if (tkStr=="null") tk = LEX_R_NULL;
      else if (tkStr=="undefined") tk = LEX_R_UNDEFINED;
      else if (tkStr=="memory_new") tk = LEX_R_NEW;
   }
   else if (isNumeric(currCh))     // Numbers
   {
      bool isHex = false;
      if (currCh=='0') { tkStr += currCh; getNextCh(); }
      if (currCh=='x')
      {
         isHex = true;
         tkStr += currCh; getNextCh();
      }
      tk = LEX_INT;
      while (isNumeric(currCh) || (isHex && isHexadecimal(currCh)))
      {
         tkStr += currCh;
         getNextCh();
      }
      if (!isHex && currCh=='.')
      {
         tk = LEX_FLOAT;
         tkStr += '.';
         getNextCh();
         while (isNumeric(currCh))
         {
            tkStr += currCh;
            getNextCh();
         }
      }
      // do fancy e-style floating point_i32
      if (!isHex && (currCh=='e'||currCh=='E'))
      {
         tk = LEX_FLOAT;
         tkStr += currCh; getNextCh();
         if (currCh=='-') { tkStr += currCh; getNextCh(); }
         while (isNumeric(currCh))
         {
            tkStr += currCh; getNextCh();
         }
      }
   }
   else if (currCh=='"')
   {
      // strings...
      getNextCh();
      while (currCh && currCh!='"')
      {
         if (currCh == '\\')
         {
            getNextCh();
            switch (currCh)
            {
            case 'n' : tkStr += '\n'; break;
            case '"' : tkStr += '"'; break;
            case '\\' : tkStr += '\\'; break;
            default: tkStr += currCh;
            }
         }
         else
         {
            tkStr += currCh;
         }
         getNextCh();
      }
      getNextCh();
      tk = LEX_STR;
   }
   else if (currCh=='\'')
   {
      // strings again...
      getNextCh();
      while (currCh && currCh!='\'')
      {
         if (currCh == '\\')
         {
            getNextCh();
            switch (currCh)
            {
            case 'n' : tkStr += '\n'; break;
            case 'a' : tkStr += '\a'; break;
            case 'r' : tkStr += '\r'; break;
            case 't' : tkStr += '\t'; break;
            case '\'' : tkStr += '\''; break;
            case '\\' : tkStr += '\\'; break;
            case 'x' :   // hex digits
            {
               char buf[3] = "??";
               getNextCh(); buf[0] = currCh;
               getNextCh(); buf[1] = currCh;
               tkStr += (char)strtol(buf,0,16);
            } break;
            default: if (currCh>='0' && currCh<='7')
               {
                  // octal digits
                  char buf[4] = "???";
                  buf[0] = currCh;
                  getNextCh(); buf[1] = currCh;
                  getNextCh(); buf[2] = currCh;
                  tkStr += (char)strtol(buf,0,8);
               }
               else
                  tkStr += currCh;
            }
         }
         else
         {
            tkStr += currCh;
         }
         getNextCh();
      }
      getNextCh();
      tk = LEX_STR;
   }
   else
   {
      // single chars
      tk = currCh;
      if (currCh) getNextCh();
      if (tk=='=' && currCh=='=')   // ==
      {
         tk = LEX_EQUAL;
         getNextCh();
         if (currCh=='=')   // ===
         {
            tk = LEX_TYPEEQUAL;
            getNextCh();
         }
      }
      else if (tk=='!' && currCh=='=')     // !=
      {
         tk = LEX_NEQUAL;
         getNextCh();
         if (currCh=='=')   // !==
         {
            tk = LEX_NTYPEEQUAL;
            getNextCh();
         }
      }
      else if (tk=='<' && currCh=='=')
      {
         tk = LEX_LEQUAL;
         getNextCh();
      }
      else if (tk=='<' && currCh=='<')
      {
         tk = LEX_LSHIFT;
         getNextCh();
         if (currCh=='=')   // <<=
         {
            tk = LEX_LSHIFTEQUAL;
            getNextCh();
         }
      }
      else if (tk=='>' && currCh=='=')
      {
         tk = LEX_GEQUAL;
         getNextCh();
      }
      else if (tk=='>' && currCh=='>')
      {
         tk = LEX_RSHIFT;
         getNextCh();
         if (currCh=='=')   // >>=
         {
            tk = LEX_RSHIFTEQUAL;
            getNextCh();
         }
         else if (currCh=='>')     // >>>
         {
            tk = LEX_RSHIFTUNSIGNED;
            getNextCh();
         }
      }
      else if (tk=='+' && currCh=='=')
      {
         tk = LEX_PLUSEQUAL;
         getNextCh();
      }
      else if (tk=='-' && currCh=='=')
      {
         tk = LEX_MINUSEQUAL;
         getNextCh();
      }
      else if (tk=='+' && currCh=='+')
      {
         tk = LEX_PLUSPLUS;
         getNextCh();
      }
      else if (tk=='-' && currCh=='-')
      {
         tk = LEX_MINUSMINUS;
         getNextCh();
      }
      else if (tk=='&' && currCh=='=')
      {
         tk = LEX_ANDEQUAL;
         getNextCh();
      }
      else if (tk=='&' && currCh=='&')
      {
         tk = LEX_ANDAND;
         getNextCh();
      }
      else if (tk=='|' && currCh=='=')
      {
         tk = LEX_OREQUAL;
         getNextCh();
      }
      else if (tk=='|' && currCh=='|')
      {
         tk = LEX_OROR;
         getNextCh();
      }
      else if (tk=='^' && currCh=='=')
      {
         tk = LEX_XOREQUAL;
         getNextCh();
      }
   }
   /* This isn't quite right yet */
   tokenLastEnd = tokenEnd;
   tokenEnd = dataPos-3;
}

string CScriptLex::getSubString(i32 lastPosition)
{
   i32 lastCharIdx = tokenLastEnd+1;
   if (lastCharIdx < dataEnd)
   {
      /* save a memory alloc by using our data array to create the
         substring */
      char old = data[lastCharIdx];
      data[lastCharIdx] = 0;
      string value = &data[lastPosition];
      data[lastCharIdx] = old;
      return value;
   }
   else
   {
      return string(&data[lastPosition]);
   }
}


CScriptLex *CScriptLex::getSubLex(i32 lastPosition)
{
   i32 lastCharIdx = tokenLastEnd+1;
   if (lastCharIdx < dataEnd)
      return memory_new CScriptLex(this, lastPosition, lastCharIdx);
   else
      return memory_new CScriptLex(this, lastPosition, dataEnd );
}

string CScriptLex::getPosition(i32 pos)
{
   if (pos<0) pos=tokenLastEnd;
   i32 line = 1,col = 1;
   for (i32 i=0; i<pos; i++)
   {
      char ch;
      if (i < dataEnd)
         ch = data[i];
      else
         ch = 0;
      col++;
      if (ch=='\n')
      {
         line++;
         col = 0;
      }
   }
   char buf[256];
   sprintf_s(buf, 256, "(line: %d, col: %d)", line, col);
   return buf;
}

// ----------------------------------------------------------------------------------- CSCRIPTVARLINK

CScriptVarLink::CScriptVarLink(CScriptVar * payload, const string &name)
{
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   this->name = name;
   this->nextSibling = 0;
   this->prevSibling = 0;
   this->payload = payload->ref();
   this->owned = false;
}

CScriptVarLink::CScriptVarLink(const CScriptVarLink &link)
{
   // Copy constructor
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   this->name = link.name;
   this->nextSibling = 0;
   this->prevSibling = 0;
   this->payload = link.payload->ref();
   this->owned = false;
}

CScriptVarLink::~CScriptVarLink()
{
   payload->unref();
#if DEBUG_MEMORY
   mark_deallocated(this);
#endif
}

void CScriptVarLink::replaceWith(CScriptVar *newVar)
{
   CScriptVar *oldVar = payload;
   payload = newVar->ref();
   oldVar->unref();
}

void CScriptVarLink::replaceWith(CScriptVarLink *newVar)
{
   if (newVar)
      replaceWith(newVar->payload);
   else
      replaceWith(memory_new CScriptVar());
}

i32 CScriptVarLink::getIntName()
{
   return atoi(name.c_str());
}
void CScriptVarLink::setIntName(i32 n)
{
   char sIdx[64];
   sprintf_s(sIdx, sizeof(sIdx), "%d", n);
   name = sIdx;
}

// ----------------------------------------------------------------------------------- CSCRIPTVAR

CScriptVar::CScriptVar()
{
   refs = 0;
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   init();
   flags = SCRIPTVAR_UNDEFINED;
}

CScriptVar::CScriptVar(const string &str)
{
   refs = 0;
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   init();
   flags = SCRIPTVAR_STRING;
   data = str;
}


CScriptVar::CScriptVar(const string &varData, i32 varFlags)
{
   refs = 0;
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   init();
   flags = varFlags;
   if (varFlags & SCRIPTVAR_INTEGER)
   {
      intData = strtol(varData.c_str(),0,0);
   }
   else if (varFlags & SCRIPTVAR_DOUBLE)
   {
      doubleData = strtod(varData.c_str(),0);
   }
   else
      data = varData;
}

CScriptVar::CScriptVar(double val)
{
   refs = 0;
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   init();
   setDouble(val);
}

CScriptVar::CScriptVar(i32 val)
{
   refs = 0;
#if DEBUG_MEMORY
   mark_allocated(this);
#endif
   init();
   setInt(val);
}

CScriptVar::~CScriptVar(void)
{
#if DEBUG_MEMORY
   mark_deallocated(this);
#endif
   eraseAllChildren();
}

void CScriptVar::init()
{
   firstChild = 0;
   lastChild = 0;
   flags = 0;
   jsCallback = 0;
   jsCallbackUserData = 0;
   data = TINYJS_BLANK_DATA;
   intData = 0;
   doubleData = 0;
}


CScriptVar *CScriptVar::getReturnVar()
{
   
   return getParameter(TINYJS_RETURN_VAR);

}


void CScriptVar::setReturnVar(CScriptVar * payload)
{

   findChildOrCreate(TINYJS_RETURN_VAR)->replaceWith(payload);

}


CScriptVar *CScriptVar::getParameter(const string &name)
{
   
   return findChildOrCreate(name)->payload;

}


CScriptVarLink *CScriptVar::findChild(const string &childName)
{

   CScriptVarLink *v = firstChild;

   while (v)
   {

      if (v->name.equals(childName))
      {

         return v;

      }

      v = v->nextSibling;

   }

   return 0;

}


CScriptVarLink *CScriptVar::findChildOrCreate(const string &childName, i32 varFlags)
{

   CScriptVarLink *l = findChild(childName);

   if (l)
   {

      return l;

   }

   return addChild(childName, memory_new CScriptVar(TINYJS_BLANK_DATA, varFlags));

}


CScriptVarLink *CScriptVar::findChildOrCreateByPath(const string &path)
{

   strsize iPosition = path.find_index('.');

   if (iPosition < 0)
   {

      return findChildOrCreate(path);

   }

   return findChildOrCreate(path.substr(0, iPosition), SCRIPTVAR_OBJECT)->payload->findChildOrCreateByPath(path.substr(iPosition +1));

}


CScriptVarLink *CScriptVar::addChild(const string &childName, CScriptVar *child)
{

   if (isUndefined())
   {

      flags = SCRIPTVAR_OBJECT;

   }

   // if no child supplied, create one
   if (!child)
   {

      child = memory_new CScriptVar();

   }

   CScriptVarLink *link = memory_new CScriptVarLink(child, childName);

   link->owned = true;

   if (lastChild)
   {

      lastChild->nextSibling = link;

      link->prevSibling = lastChild;

      lastChild = link;

   }
   else
   {

      firstChild = link;

      lastChild = link;

   }

   return link;

}


CScriptVarLink *CScriptVar::addChildNoDup(const string &childName, CScriptVar *child)
{

   // if no child supplied, create one
   if (!child)
   {

      child = memory_new CScriptVar();

   }

   CScriptVarLink *v = findChild(childName);

   if (v)
   {

      v->replaceWith(child);

   }
   else
   {

      v = addChild(childName, child);

   }

   return v;

}


void CScriptVar::eraseChild(CScriptVar *child)
{

   CScriptVarLink *link = firstChild;

   while (link)
   {

      if (link->payload == child)
      {

         break;

      }

      link = link->nextSibling;

   }

   ASSERT(link);

   eraseLink(link);

}


void CScriptVar::eraseLink(CScriptVarLink *link)
{
   if (!link) return;
   if (link->nextSibling)
      link->nextSibling->prevSibling = link->prevSibling;
   if (link->prevSibling)
      link->prevSibling->nextSibling = link->nextSibling;
   if (lastChild == link)
      lastChild = link->prevSibling;
   if (firstChild == link)
      firstChild = link->nextSibling;
   delete link;
}

void CScriptVar::eraseAllChildren()
{
   CScriptVarLink *ca = firstChild;
   while (ca)
   {
      CScriptVarLink *t = ca->nextSibling;
      delete ca;
      ca = t;
   }
   firstChild = 0;
   lastChild = 0;
}

CScriptVar *CScriptVar::getArrayIndex(i32 idx)
{
   char sIdx[64];
   sprintf_s(sIdx, sizeof(sIdx), "%d", idx);
   CScriptVarLink *link = findChild(sIdx);
   if (link) return link->payload;
   else return memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_NULL); // undefined
}

void CScriptVar::setArrayIndex(i32 idx, CScriptVar *value)
{
   char sIdx[64];
   sprintf_s(sIdx, sizeof(sIdx), "%d", idx);
   CScriptVarLink *link = findChild(sIdx);

   if (link)
   {
      if (value->isUndefined())
         eraseLink(link);
      else
         link->replaceWith(value);
   }
   else
   {
      if (!value->isUndefined())
         addChild(sIdx, value);
   }
}

i32 CScriptVar::getArrayLength()
{
   i32 highest = -1;
   if (!isArray()) return 0;

   CScriptVarLink *link = firstChild;
   while (link)
   {
      if (isNumber(link->name))
      {
         i32 val = atoi(link->name.c_str());
         if (val > highest) highest = val;
      }
      link = link->nextSibling;
   }
   return highest+1;
}

i32 CScriptVar::getChildren()
{
   i32 n = 0;
   CScriptVarLink *link = firstChild;
   while (link)
   {
      n++;
      link = link->nextSibling;
   }
   return n;
}

i32 CScriptVar::getInt()
{
   /* strtol understands about hex and octal */
   if (isInt()) return (i32) intData;
   if (isNull()) return 0;
   if (isUndefined()) return 0;
   if (isDouble()) return (i32)doubleData;
   return 0;
}

double CScriptVar::getDouble()
{
   if (isDouble()) return doubleData;
   if (isInt()) return intData;
   if (isNull()) return 0;
   if (isUndefined()) return 0;
   return 0; /* or NaN? */
}

const string &CScriptVar::getString()
{
   /* Because we can't return a string that is generated on demand.
    * I should really just use char* :) */
   static string s_null = "null";
   static string s_undefined = "undefined";
   if (isInt())
   {
      char buffer[32];
      sprintf_s(buffer, sizeof(buffer), "%ld", intData);
      data = buffer;
      return data;
   }
   if (isDouble())
   {
      char buffer[32];
      sprintf_s(buffer, sizeof(buffer), "%f", doubleData);
      data = buffer;
      return data;
   }
   if (isNull()) return s_null;
   if (isUndefined()) return s_undefined;
   // are we just a string here?
   return data;
}

void CScriptVar::setInt(i32 val)
{
   flags = (flags&~SCRIPTVAR_VARTYPEMASK) | SCRIPTVAR_INTEGER;
   intData = val;
   doubleData = 0;
   data = TINYJS_BLANK_DATA;
}

void CScriptVar::setDouble(double val)
{
   flags = (flags&~SCRIPTVAR_VARTYPEMASK) | SCRIPTVAR_DOUBLE;
   doubleData = val;
   intData = 0;
   data = TINYJS_BLANK_DATA;
}

void CScriptVar::setString(const string &str)
{
   // name sure it's not still a number or integer
   flags = (flags&~SCRIPTVAR_VARTYPEMASK) | SCRIPTVAR_STRING;
   data = str;
   intData = 0;
   doubleData = 0;
}

void CScriptVar::setUndefined()
{
   // name sure it's not still a number or integer
   flags = (flags&~SCRIPTVAR_VARTYPEMASK) | SCRIPTVAR_UNDEFINED;
   data = TINYJS_BLANK_DATA;
   intData = 0;
   doubleData = 0;
   eraseAllChildren();
}

void CScriptVar::setArray()
{
   // name sure it's not still a number or integer
   flags = (flags&~SCRIPTVAR_VARTYPEMASK) | SCRIPTVAR_ARRAY;
   data = TINYJS_BLANK_DATA;
   intData = 0;
   doubleData = 0;
   eraseAllChildren();
}

bool CScriptVar::equals(CScriptVar *v)
{
   CScriptVar *resV = mathsOp(v, LEX_EQUAL);
   bool res = resV->getBool();
   delete resV;
   return res;
}

CScriptVar *CScriptVar::mathsOp(CScriptVar *b, i32 op)
{
   CScriptVar *a = this;
   // Type equality check
   if (op == LEX_TYPEEQUAL || op == LEX_NTYPEEQUAL)
   {
      // check type first, then call again to check data
      bool eql = ((a->flags & SCRIPTVAR_VARTYPEMASK) ==
                  (b->flags & SCRIPTVAR_VARTYPEMASK)) &&
                 a->mathsOp(b, LEX_EQUAL);
      if (op == LEX_TYPEEQUAL)
         return memory_new CScriptVar(eql);
      else
         return memory_new CScriptVar(!eql);
   }
   // do maths...
   if (a->isUndefined() && b->isUndefined())
   {
      if (op == LEX_EQUAL) return memory_new CScriptVar(true);
      else if (op == LEX_NEQUAL) return memory_new CScriptVar(false);
      else return memory_new CScriptVar(); // undefined
   }
   else if ((a->isNumeric() || a->isUndefined()) &&
            (b->isNumeric() || b->isUndefined()))
   {
      if (!a->isDouble() && !b->isDouble())
      {
         // use ints
         i32 da = a->getInt();
         i32 db = b->getInt();
         switch (op)
         {
         case '+': return memory_new CScriptVar(da+db);
         case '-': return memory_new CScriptVar(da-db);
         case '*': return memory_new CScriptVar(da*db);
         case '/': return memory_new CScriptVar(da/db);
         case '&': return memory_new CScriptVar(da&db);
         case '|': return memory_new CScriptVar(da|db);
         case '^': return memory_new CScriptVar(da^db);
         case '%': return memory_new CScriptVar(da%db);
         case LEX_EQUAL:     return memory_new CScriptVar(da==db);
         case LEX_NEQUAL:    return memory_new CScriptVar(da!=db);
         case '<':     return memory_new CScriptVar(da<db);
         case LEX_LEQUAL:    return memory_new CScriptVar(da<=db);
         case '>':     return memory_new CScriptVar(da>db);
         case LEX_GEQUAL:    return memory_new CScriptVar(da>=db);
         default: throw CScriptException("Operation "+CScriptLex::getTokenStr(op)+" not supported on the Int datatype");
         }
      }
      else
      {
         // use doubles
         double da = a->getDouble();
         double db = b->getDouble();
         switch (op)
         {
         case '+': return memory_new CScriptVar(da+db);
         case '-': return memory_new CScriptVar(da-db);
         case '*': return memory_new CScriptVar(da*db);
         case '/': return memory_new CScriptVar(da/db);
         case LEX_EQUAL:     return memory_new CScriptVar(da==db);
         case LEX_NEQUAL:    return memory_new CScriptVar(da!=db);
         case '<':     return memory_new CScriptVar(da<db);
         case LEX_LEQUAL:    return memory_new CScriptVar(da<=db);
         case '>':     return memory_new CScriptVar(da>db);
         case LEX_GEQUAL:    return memory_new CScriptVar(da>=db);
         default: throw CScriptException("Operation "+CScriptLex::getTokenStr(op)+" not supported on the Double datatype");
         }
      }
   }
   else if (a->isArray())
   {
      /* Just check pointers */
      switch (op)
      {
      case LEX_EQUAL: return memory_new CScriptVar(a==b);
      case LEX_NEQUAL: return memory_new CScriptVar(a!=b);
      default: throw CScriptException("Operation "+CScriptLex::getTokenStr(op)+" not supported on the Array datatype");
      }
   }
   else if (a->isObject())
   {
      /* Just check pointers */
      switch (op)
      {
      case LEX_EQUAL: return memory_new CScriptVar(a==b);
      case LEX_NEQUAL: return memory_new CScriptVar(a!=b);
      default: throw CScriptException("Operation "+CScriptLex::getTokenStr(op)+" not supported on the Object datatype");
      }
   }
   else
   {
      string da = a->getString();
      string db = b->getString();
      // use strings
      switch (op)
      {
      case '+':           return memory_new CScriptVar(da+db, SCRIPTVAR_STRING);
      case LEX_EQUAL:     return memory_new CScriptVar(da==db);
      case LEX_NEQUAL:    return memory_new CScriptVar(da!=db);
      case '<':     return memory_new CScriptVar(da<db);
      case LEX_LEQUAL:    return memory_new CScriptVar(da<=db);
      case '>':     return memory_new CScriptVar(da>db);
      case LEX_GEQUAL:    return memory_new CScriptVar(da>=db);
      default: throw CScriptException("Operation "+CScriptLex::getTokenStr(op)+" not supported on the string datatype");
      }
   }
   ASSERT(0);
   return 0;
}

void CScriptVar::copySimpleData(CScriptVar *val)
{
   data = val->data;
   intData = val->intData;
   doubleData = val->doubleData;
   flags = (flags & ~SCRIPTVAR_VARTYPEMASK) | (val->flags & SCRIPTVAR_VARTYPEMASK);
}

void CScriptVar::copyValue(CScriptVar *val)
{
   if (val)
   {
      copySimpleData(val);
      // erase all current children
      eraseAllChildren();
      // copy children of 'val'
      CScriptVarLink *child = val->firstChild;
      while (child)
      {
         CScriptVar *copied;
         // don't copy the 'parent' object...
         if (child->name != TINYJS_PROTOTYPE_CLASS)
            copied = child->payload->deepCopy();
         else
            copied = child->payload;

         addChild(child->name, copied);

         child = child->nextSibling;
      }
   }
   else
   {
      setUndefined();
   }
}

CScriptVar *CScriptVar::deepCopy()
{
   CScriptVar *newVar = memory_new CScriptVar();
   newVar->copySimpleData(this);
   // copy children
   CScriptVarLink *child = firstChild;
   while (child)
   {
      CScriptVar *copied;
      // don't copy the 'parent' object...
      if (child->name != TINYJS_PROTOTYPE_CLASS)
         copied = child->payload->deepCopy();
      else
         copied = child->payload;

      newVar->addChild(child->name, copied);
      child = child->nextSibling;
   }
   return newVar;
}


void CScriptVar::trace(string indentStr, const string &name)
{

   string str;

   str.format("%s'%s' = '%s' %s\n",
              indentStr.c_str(),
              name.c_str(),
              getString().c_str(),
              getFlagsAsString().c_str());

   ::output_debug_string(str);

   string indent = indentStr+" ";

   CScriptVarLink *link = firstChild;

   while (link)
   {

      link->payload->trace(indent, link->name);

      link = link->nextSibling;

   }

}

string CScriptVar::getFlagsAsString()
{
   string flagstr = "";
   if (flags&SCRIPTVAR_FUNCTION) flagstr = flagstr + "FUNCTION ";
   if (flags&SCRIPTVAR_OBJECT) flagstr = flagstr + "OBJECT ";
   if (flags&SCRIPTVAR_ARRAY) flagstr = flagstr + "ARRAY ";
   if (flags&SCRIPTVAR_NATIVE) flagstr = flagstr + "NATIVE ";
   if (flags&SCRIPTVAR_DOUBLE) flagstr = flagstr + "DOUBLE ";
   if (flags&SCRIPTVAR_INTEGER) flagstr = flagstr + "INTEGER ";
   if (flags&SCRIPTVAR_STRING) flagstr = flagstr + "STRING ";
   return flagstr;
}

string CScriptVar::getParsableString()
{
   // Numbers can just be put in directly
   if (isNumeric())
      return getString();
   if (isFunction())
   {
      string funcStr;
      funcStr += "function (";
      // get list of parameters
      CScriptVarLink *link = firstChild;
      while (link)
      {
         funcStr += link->name;
         if (link->nextSibling) funcStr += ",";
         link = link->nextSibling;
      }
      // add function body
      funcStr += ") " + getString();
      return funcStr;
   }
   // if it is a string then we quote it
   if (isString())
      return getJSString(getString());
   if (isNull())
      return "null";
   return "undefined";
}

void CScriptVar::getJSON(string &destination, const string linePrefix)
{
   if (isObject())
   {
      string indentedLinePrefix = linePrefix+"  ";
      // children - handle with bracketed list
      destination += "{ \n";
      CScriptVarLink *link = firstChild;
      while (link)
      {
         destination += indentedLinePrefix;
         destination  += getJSString(link->name);
         destination  += " : ";
         link->payload->getJSON(destination, indentedLinePrefix);
         link = link->nextSibling;
         if (link)
         {
            destination  += ",\n";
         }
      }
      destination += "\n" + linePrefix + "}";
   }
   else if (isArray())
   {
      string indentedLinePrefix = linePrefix+"  ";
      destination += "[\n";
      i32 len = getArrayLength();
      if (len>10000) len=10000; // we don't want to get stuck here!

      for (i32 i=0; i<len; i++)
      {
         getArrayIndex(i)->getJSON(destination, indentedLinePrefix);
         if (i<len-1) destination  += ",\n";
      }

      destination += "\n" + linePrefix + "]";
   }
   else
   {
      // no children or a function... just write value directly
      destination += getParsableString();
   }
}


void CScriptVar::setCallback(JSCallback callback, void *userdata)
{
   jsCallback = callback;
   jsCallbackUserData = userdata;
}

CScriptVar *CScriptVar::ref()
{
   refs++;
   return this;
}

void CScriptVar::unref()
{
   if (refs<=0) throw ::exception(error_wrong_state, "OMFG, we have unreffed too far!\n");
   if ((--refs)==0)
   {
      delete this;
   }
}

i32 CScriptVar::getRefs()
{
   return refs;
}


// ----------------------------------------------------------------------------------- CSCRIPT

tinyjs::tinyjs()
{
   l = 0;
   root = (memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT))->ref();
   // add built-in classes
   stringClass = (memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT))->ref();
   arrayClass = (memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT))->ref();
   objectClass = (memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT))->ref();
   root->addChild("String", stringClass);
   root->addChild("Array", arrayClass);
   root->addChild("Object", objectClass);
}

tinyjs::~tinyjs()
{
   ASSERT(!l);
   scopes.clear();
   stringClass->unref();
   arrayClass->unref();
   objectClass->unref();
   root->unref();

#if DEBUG_MEMORY
   show_allocated();
#endif
}

void tinyjs::trace()
{
   root->trace();
}

void tinyjs::execute(const string &code)
{
   CScriptLex *oldLex = l;
   address_array < CScriptVar * > oldScopes = scopes;
   l = memory_new CScriptLex(code);
#ifdef TINYJS_callstack
   callstack.clear();
#endif
   scopes.clear();
   scopes.add(root);
   try
   {
      bool execute = true;
      while (l->tk) statement(execute);
   }
   catch (CScriptException *e)
   {
      string msg;
      msg += "Error " + e->text;
#ifdef TINYJS_callstack
      for (i32 i=(i32)callstack.size()-1; i>=0; i--)
         msg += string("\n") + as_string(i) + ": " + callstack[i];
#endif
      msg += " at " + l->getPosition();
      delete l;
      l = oldLex;

      throw CScriptException(msg);
   }
   delete l;
   l = oldLex;
   scopes = oldScopes;
}

CScriptVarLink tinyjs::evaluateComplex(const string &code)
{
   CScriptLex *oldLex = l;
   address_array < CScriptVar * > oldScopes = scopes;

   l = memory_new CScriptLex(code);
#ifdef TINYJS_callstack
   callstack.clear();
#endif
   scopes.clear();
   scopes.add(root);
   CScriptVarLink *v = 0;
   try
   {
      bool execute = true;
      do
      {
         CLEAN(v);
         v = axis(execute);
         if (l->tk!=LEX_EOF) l->match(';');
      }
      while (l->tk!=LEX_EOF);
   }
   catch (CScriptException *e)
   {
      string  msg;
      msg += "Error " + e->text;
#ifdef TINYJS_callstack
      for (i32 i=(i32)callstack.size()-1; i>=0; i--)
         msg += "\n" + as_string(i) + ": " + callstack[i];
#endif
      msg += " at " + l->getPosition();
      delete l;
      l = oldLex;

      throw CScriptException(msg);
   }
   delete l;
   l = oldLex;
   scopes = oldScopes;

   if (v)
   {
      CScriptVarLink r = *v;
      CLEAN(v);
      return r;
   }
   // return undefined...
   return CScriptVarLink(memory_new CScriptVar());
}

string tinyjs::evaluate(const string &code)
{
   return evaluateComplex(code).payload->getString();
}

void tinyjs::parseFunctionArguments(CScriptVar *funcVar)
{
   l->match('(');
   while (l->tk!=')')
   {
      funcVar->addChildNoDup(l->tkStr);
      l->match(LEX_ID);
      if (l->tk!=')') l->match(',');
   }
   l->match(')');
}

void tinyjs::addNative(const string &funcDesc, JSCallback ptr, void *userdata)
{
   CScriptLex *oldLex = l;
   l = memory_new CScriptLex(funcDesc);

   CScriptVar *axis = root;

   l->match(LEX_R_FUNCTION);
   string funcName = l->tkStr;
   l->match(LEX_ID);
   /* Check for dots, we might want to do something like function String.substring ... */
   while (l->tk == '.')
   {
      l->match('.');
      CScriptVarLink *link = axis->findChild(funcName);
      // if it doesn't exist, make an object class
      if (!link) link = axis->addChild(funcName, memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT));
      axis = link->payload;
      funcName = l->tkStr;
      l->match(LEX_ID);
   }

   CScriptVar *funcVar = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_FUNCTION | SCRIPTVAR_NATIVE);
   funcVar->setCallback(ptr, userdata);
   parseFunctionArguments(funcVar);
   delete l;
   l = oldLex;

   axis->addChild(funcName, funcVar);
}

CScriptVarLink *tinyjs::parseFunctionDefinition()
{
   // actually parse a function...
   l->match(LEX_R_FUNCTION);
   string funcName = TINYJS_TEMP_NAME;
   /* we can have functions without names */
   if (l->tk==LEX_ID)
   {
      funcName = l->tkStr;
      l->match(LEX_ID);
   }
   CScriptVarLink *funcVar = memory_new CScriptVarLink(memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_FUNCTION), funcName);
   parseFunctionArguments(funcVar->payload);
   i32 funcBegin = l->tokenStart;
   bool noexecute = false;
   block(noexecute);
   funcVar->payload->data = l->getSubString(funcBegin);
   return funcVar;
}

/** Handle a function call (assumes we've parsed the function name and we're
 * on the start bracket). 'parent' is the object that contains this method,
 * if there was one (otherwise it's just a normnal function).
 */
CScriptVarLink *tinyjs::functionCall(bool &execute, CScriptVarLink *function, CScriptVar *parent)
{
   if (execute)
   {
      if (!function->payload->isFunction())
      {
         string errorMsg = "Expecting '";
         errorMsg = errorMsg + function->name + "' to be a function";
         throw CScriptException(errorMsg.c_str());
      }
      l->match('(');
      // create a memory_new symbol table entry for execution of this function
      CScriptVar *functionRoot = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_FUNCTION);
      if (parent)
         functionRoot->addChildNoDup("this", parent);
      // grab in all parameters
      CScriptVarLink *v = function->payload->firstChild;
      while (v)
      {
         CScriptVarLink *value = axis(execute);
         if (execute)
         {
            if (value->payload->isBasic())
            {
               // pass by value
               functionRoot->addChild(v->name, value->payload->deepCopy());
            }
            else
            {
               // pass by object
               functionRoot->addChild(v->name, value->payload);
            }
         }
         CLEAN(value);
         if (l->tk!=')') l->match(',');
         if(l->tk == ')')break;
         v = v->nextSibling;
      }
      l->match(')');
      // setup a return variable
      CScriptVarLink *returnVar = nullptr;
      // execute function!
      // add the function's execute space to the symbol table so we can recurse
      CScriptVarLink *returnVarLink = functionRoot->addChild(TINYJS_RETURN_VAR);
      scopes.add(functionRoot);
#ifdef TINYJS_callstack
      callstack.add(function->name + " from " + l->getPosition());
#endif

      if (function->payload->isNative())
      {
         ASSERT(function->payload->jsCallback);
         function->payload->jsCallback(functionRoot, function->payload->jsCallbackUserData);
      }
      else
      {
         /* we just want to execute the block, but something could
          * have messed up and left us with the wrong ScriptLex, so
          * we want to be careful here... */

         ::exception exception;

         CScriptLex *oldLex = l;
         CScriptLex *newLex = memory_new CScriptLex(function->payload->getString());
         l = newLex;
         try
         {
            block(execute);
            // because return will probably have called this, and set execute to false
            execute = true;
         }
         catch (CScriptException & e)
         {
            exception = e;
         }
         delete newLex;
         l = oldLex;

         if (!exception.m_estatus)
         {

            throw exception;

         }

      }
#ifdef TINYJS_callstack
      if (!callstack.is_empty()) callstack.pop();
#endif
      scopes.pop_back();
      /* get the real return payload before we erase it from our function */
      returnVar = memory_new CScriptVarLink(returnVarLink->payload);
      functionRoot->eraseLink(returnVarLink);
      delete functionRoot;
      if (returnVar)
         return returnVar;
      else
         return memory_new CScriptVarLink(memory_new CScriptVar());
   }
   else
   {
      // function, but not executing - just parse args and be done
      l->match('(');
      while (l->tk != ')')
      {
         CScriptVarLink *value = axis(execute);
         CLEAN(value);
         if (l->tk!=')') l->match(',');
      }
      l->match(')');
      if (l->tk == '{')
      {
         block(execute);
      }
      /* function will be a blank scriptvarlink if we're not executing,
       * so just return it rather than an alloc/free */
      return function;
   }
}

CScriptVarLink *tinyjs::factor(bool &execute)
{
   if (l->tk=='(')
   {
      l->match('(');
      CScriptVarLink *a = axis(execute);
      l->match(')');
      return a;
   }
   if (l->tk==LEX_R_TRUE)
   {
      l->match(LEX_R_TRUE);
      return memory_new CScriptVarLink(memory_new CScriptVar(1));
   }
   if (l->tk==LEX_R_FALSE)
   {
      l->match(LEX_R_FALSE);
      return memory_new CScriptVarLink(memory_new CScriptVar(0));
   }
   if (l->tk==LEX_R_NULL)
   {
      l->match(LEX_R_NULL);
      return memory_new CScriptVarLink(memory_new CScriptVar(TINYJS_BLANK_DATA,SCRIPTVAR_NULL));
   }
   if (l->tk==LEX_R_UNDEFINED)
   {
      l->match(LEX_R_UNDEFINED);
      return memory_new CScriptVarLink(memory_new CScriptVar(TINYJS_BLANK_DATA,SCRIPTVAR_UNDEFINED));
   }
   if (l->tk==LEX_ID)
   {
      CScriptVarLink *a = execute ? findInScopes(l->tkStr) : memory_new CScriptVarLink(memory_new CScriptVar());
      //debug_print("0x%08X for %s at %s\n", (u32)a, l->tkStr.c_str(), l->getPosition().c_str());
      /* The parent if we're executing a method call */
      CScriptVar *parent = 0;

      if (execute && !a)
      {
         /* Variable doesn't exist! JavaScript says we should create it
          * (we won't add it here. This is done in the assignment operator)*/
         a = memory_new CScriptVarLink(memory_new CScriptVar(), l->tkStr);
      }
      l->match(LEX_ID);
      while (l->tk=='(' || l->tk=='.' || l->tk=='[')
      {
         if (l->tk=='(')   // ------------------------------------- Function Call
         {
            a = functionCall(execute, a, parent);
         }
         else if (l->tk == '.')     // ------------------------------------- Record Access
         {
            l->match('.');
            if (execute)
            {
               const string &name = l->tkStr;
               CScriptVarLink *child = a->payload->findChild(name);
               if (!child) child = findInParentClasses(a->payload, name);
               if (!child)
               {
                  /* if we haven't found this defined yet, use the built-in
                     'length' properly */
                  if (a->payload->isArray() && name == "length")
                  {
                     i32 l = a->payload->getArrayLength();
                     child = memory_new CScriptVarLink(memory_new CScriptVar(l));
                  }
                  else if (a->payload->isString() && name == "length")
                  {
                     i32 l = (i32) a->payload->getString().size();
                     child = memory_new CScriptVarLink(memory_new CScriptVar(l));
                  }
                  else
                  {
                     child = a->payload->addChild(name);
                  }
               }
               parent = a->payload;
               a = child;
            }
            l->match(LEX_ID);
         }
         else if (l->tk == '[')     // ------------------------------------- Array Access
         {
            l->match('[');
            CScriptVarLink *index = axis(execute);
            l->match(']');
            if (execute)
            {
               CScriptVarLink *child = a->payload->findChildOrCreate(index->payload->getString());
               parent = a->payload;
               a = child;
            }
            CLEAN(index);
         }
         else ASSERT(0);
      }
      return a;
   }
   if (l->tk==LEX_INT || l->tk==LEX_FLOAT)
   {
      CScriptVar *a = memory_new CScriptVar(l->tkStr,
                                     ((l->tk==LEX_INT)?SCRIPTVAR_INTEGER:SCRIPTVAR_DOUBLE));
      l->match(l->tk);
      return memory_new CScriptVarLink(a);
   }
   if (l->tk==LEX_STR)
   {
      CScriptVar *a = memory_new CScriptVar(l->tkStr, SCRIPTVAR_STRING);
      l->match(LEX_STR);
      return memory_new CScriptVarLink(a);
   }
   if (l->tk=='{')
   {
      CScriptVar *contents = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT);
      /* JSON-style object definition */
      l->match('{');
      while (l->tk != '}')
      {
         string atom = l->tkStr;
         // we only allow strings or IDs on the left hand side of an initialisation
         if (l->tk==LEX_STR) l->match(LEX_STR);
         else l->match(LEX_ID);
         l->match(':');
         if (execute)
         {
            CScriptVarLink *a = axis(execute);
            contents->addChild(atom, a->payload);
            CLEAN(a);
         }
         // no need to clean here, as it will definitely be used
         if (l->tk != '}') l->match(',');
      }

      l->match('}');
      return memory_new CScriptVarLink(contents);
   }
   if (l->tk=='[')
   {
      CScriptVar *contents = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_ARRAY);
      /* JSON-style array */
      l->match('[');
      i32 idx = 0;
      while (l->tk != ']')
      {
         if (execute)
         {
            char idx_str[16]; // big enough for 2^32
            sprintf_s(idx_str, sizeof(idx_str), "%d",idx);

            CScriptVarLink *a = axis(execute);
            contents->addChild(idx_str, a->payload);
            CLEAN(a);
         }
         // no need to clean here, as it will definitely be used
         if (l->tk != ']') l->match(',');
         idx++;
      }
      l->match(']');
      return memory_new CScriptVarLink(contents);
   }
   if (l->tk==LEX_R_FUNCTION)
   {
      CScriptVarLink *funcVar = parseFunctionDefinition();
      if (funcVar->name != TINYJS_TEMP_NAME)
         information("Functions not defined at statement-level are not meant to have a name");
      return funcVar;
   }
   if (l->tk==LEX_R_NEW)
   {
      // memory_new -> create a memory_new object
      l->match(LEX_R_NEW);
      const string &className = l->tkStr;
      if(className.case_insensitive_order("array") == 0)
      {
         l->match(LEX_ID);
         i32 idx = 0;
         CScriptVar *contents = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT);
         /* JSON-style object definition */
         l->match('(');
         while (l->tk != ')')
         {
            //string atom = l->tkStr;
            // we only allow strings or IDs on the left hand side of an initialisation
            //if (l->tk==LEX_STR) l->match(LEX_STR);
            //else l->match(LEX_ID);
            //l->match(':');
            if (execute)
            {
               CScriptVarLink *a = axis(execute);
               contents->addChild(as_string(idx), a->payload);
               CLEAN(a);
            }
            idx++;
            // no need to clean here, as it will definitely be used
            if (l->tk != ')') l->match(',');
         }

         l->match(')');
         return memory_new CScriptVarLink(contents);

      }
      else
      {
         if (execute)
         {
            CScriptVarLink *objClassOrFunc = findInScopes(className);
            if (!objClassOrFunc)
            {
               information("%s is not a valid class name", className.c_str());
               return memory_new CScriptVarLink(memory_new CScriptVar());
            }
            l->match(LEX_ID);
            CScriptVar *obj = memory_new CScriptVar(TINYJS_BLANK_DATA, SCRIPTVAR_OBJECT);
            CScriptVarLink *objLink = memory_new CScriptVarLink(obj);
            if (objClassOrFunc->payload->isFunction())
            {
               CLEAN(functionCall(execute, objClassOrFunc, obj));
            }
            else
            {
               obj->addChild(TINYJS_PROTOTYPE_CLASS, objClassOrFunc->payload);
               if (l->tk == '(')
               {
                  l->match('(');
                  l->match(')');
               }
            }
            return objLink;
         }
         else
         {
            l->match(LEX_ID);
            if (l->tk == '(')
            {
               l->match('(');
               l->match(')');
            }
         }
      }
   }
   // Nothing we can do here... just hope it's the end...
   l->match(LEX_EOF);
   return 0;
}

CScriptVarLink *tinyjs::unary(bool &execute)
{
   CScriptVarLink *a;
   if (l->tk=='!')
   {
      l->match('!'); // binary not
      a = factor(execute);
      if (execute)
      {
         CScriptVar zero(0);
         CScriptVar *res = a->payload->mathsOp(&zero, LEX_EQUAL);
         CREATE_LINK(a, res);
      }
   }
   else
      a = factor(execute);
   return a;
}

CScriptVarLink *tinyjs::term(bool &execute)
{
   CScriptVarLink *a = unary(execute);
   while (l->tk=='*' || l->tk=='/' || l->tk=='%')
   {
      i32 op = l->tk;
      l->match(l->tk);
      CScriptVarLink *b = unary(execute);
      if (execute)
      {
         CScriptVar *res = a->payload->mathsOp(b->payload, op);
         CREATE_LINK(a, res);
      }
      CLEAN(b);
   }
   return a;
}

CScriptVarLink *tinyjs::expression(bool &execute)
{
   bool negate = false;
   if (l->tk=='-')
   {
      l->match('-');
      negate = true;
   }
   CScriptVarLink *a = term(execute);
   if (negate)
   {
      CScriptVar zero(0);
      CScriptVar *res = zero.mathsOp(a->payload, '-');
      CREATE_LINK(a, res);
   }

   while (l->tk=='+' || l->tk=='-' ||
          l->tk==LEX_PLUSPLUS || l->tk==LEX_MINUSMINUS)
   {
      i32 op = l->tk;
      l->match(l->tk);
      if (op==LEX_PLUSPLUS || op==LEX_MINUSMINUS)
      {
         if (execute)
         {
            CScriptVar one(1);
            CScriptVar *res = a->payload->mathsOp(&one, op==LEX_PLUSPLUS ? '+' : '-');
            CScriptVarLink *oldValue = memory_new CScriptVarLink(a->payload);
            // in-place add/subtract
            a->replaceWith(res);
            CLEAN(a);
            a = oldValue;
         }
      }
      else
      {
         CScriptVarLink *b = term(execute);
         if (execute)
         {
            // not in-place, so just replace
            CScriptVar *res = a->payload->mathsOp(b->payload, op);
            CREATE_LINK(a, res);
         }
         CLEAN(b);
      }
   }
   return a;
}

CScriptVarLink *tinyjs::shift(bool &execute)
{
   CScriptVarLink *a = expression(execute);
   if (l->tk==LEX_LSHIFT || l->tk==LEX_RSHIFT || l->tk==LEX_RSHIFTUNSIGNED)
   {
      i32 op = l->tk;
      l->match(op);
      CScriptVarLink *b = axis(execute);
      i32 shift = execute ? b->payload->getInt() : 0;
      CLEAN(b);
      if (execute)
      {
         if (op==LEX_LSHIFT) a->payload->setInt(a->payload->getInt() << shift);
         if (op==LEX_RSHIFT) a->payload->setInt(a->payload->getInt() >> shift);
         if (op==LEX_RSHIFTUNSIGNED) a->payload->setInt(((u32)a->payload->getInt()) >> shift);
      }
   }
   return a;
}

CScriptVarLink *tinyjs::condition(bool &execute)
{
   CScriptVarLink *a = shift(execute);
   CScriptVarLink *b;
   while (l->tk==LEX_EQUAL || l->tk==LEX_NEQUAL ||
          l->tk==LEX_TYPEEQUAL || l->tk==LEX_NTYPEEQUAL ||
          l->tk==LEX_LEQUAL || l->tk==LEX_GEQUAL ||
          l->tk=='<' || l->tk=='>')
   {
      i32 op = l->tk;
      l->match(l->tk);
      b = shift(execute);
      if (execute)
      {
         CScriptVar *res = a->payload->mathsOp(b->payload, op);
         CREATE_LINK(a,res);
      }
      CLEAN(b);
   }
   return a;
}

CScriptVarLink *tinyjs::logic(bool &execute)
{
   CScriptVarLink *a = condition(execute);
   CScriptVarLink *b;
   while (l->tk=='&' || l->tk=='|' || l->tk=='^' || l->tk==LEX_ANDAND || l->tk==LEX_OROR)
   {
      bool noexecute = false;
      i32 op = l->tk;
      l->match(l->tk);
      bool shortCircuit = false;
      bool tristate = false;
      // if we have i16-circuit ops, then if we know the outcome
      // we don't bother to execute the other op. Even if not
      // we need to tell mathsOp it's an & or |
      if (op==LEX_ANDAND)
      {
         op = '&';
         shortCircuit = !a->payload->getBool();
         tristate = true;
      }
      else if (op==LEX_OROR)
      {
         op = '|';
         shortCircuit = a->payload->getBool();
         tristate = true;
      }
      b = condition(shortCircuit ? noexecute : execute);
      if (execute && !shortCircuit)
      {
         if (tristate)
         {
            CScriptVar *newa = memory_new CScriptVar(a->payload->getBool());
            CScriptVar *newb = memory_new CScriptVar(b->payload->getBool());
            CREATE_LINK(a, newa);
            CREATE_LINK(b, newb);
         }
         CScriptVar *res = a->payload->mathsOp(b->payload, op);
         CREATE_LINK(a, res);
      }
      CLEAN(b);
   }
   return a;
}

CScriptVarLink *tinyjs::ternary(bool &execute)
{
   CScriptVarLink *lhs = logic(execute);
   bool noexec = false;
   if (l->tk=='?')
   {
      l->match('?');
      if (!execute)
      {
         CLEAN(lhs);
         CLEAN(axis(noexec));
         l->match(':');
         CLEAN(axis(noexec));
      }
      else
      {
         bool first = lhs->payload->getBool();
         CLEAN(lhs);
         if (first)
         {
            lhs = axis(execute);
            l->match(':');
            CLEAN(axis(noexec));
         }
         else
         {
            CLEAN(axis(noexec));
            l->match(':');
            lhs = axis(execute);
         }
      }
   }

   return lhs;
}

CScriptVarLink *tinyjs::axis(bool &execute)
{
   CScriptVarLink *lhs = ternary(execute);
   if (l->tk=='=' || l->tk==LEX_PLUSEQUAL || l->tk==LEX_MINUSEQUAL)
   {
      /* If we're assigning to this and we don't have a parent,
       * add it to the symbol table root as per JavaScript. */
      if (execute && !lhs->owned)
      {
         if (lhs->name.length()>0)
         {
            CScriptVarLink *realLhs = root->addChildNoDup(lhs->name, lhs->payload);
            CLEAN(lhs);
            lhs = realLhs;
         }
         else
            information("Trying to assign to an un-named type\n");
      }

      i32 op = l->tk;
      l->match(l->tk);
      CScriptVarLink *rhs = axis(execute);
      if (execute)
      {
         if (op=='=')
         {
            lhs->replaceWith(rhs);
         }
         else if (op==LEX_PLUSEQUAL)
         {
            CScriptVar *res = lhs->payload->mathsOp(rhs->payload, '+');
            lhs->replaceWith(res);
         }
         else if (op==LEX_MINUSEQUAL)
         {
            CScriptVar *res = lhs->payload->mathsOp(rhs->payload, '-');
            lhs->replaceWith(res);
         }
         else ASSERT(0);
      }
      CLEAN(rhs);
   }
   return lhs;
}

void tinyjs::block(bool &execute)
{
   l->match('{');
   if (execute)
   {
      while (l->tk && l->tk!='}')
         statement(execute);
      l->match('}');
   }
   else
   {
      // fast skip of blocks
      i32 brackets = 1;
      while (l->tk && brackets)
      {
         if (l->tk == '{') brackets++;
         if (l->tk == '}') brackets--;
         l->match(l->tk);
      }
   }

}

void tinyjs::statement(bool &execute)
{
   if (l->tk==LEX_ID ||
         l->tk==LEX_INT ||
         l->tk==LEX_FLOAT ||
         l->tk==LEX_STR ||
         l->tk=='-')
   {
      /* Execute a simple statement that only contains basic arithmetic... */
      CLEAN(axis(execute));
      l->match(';');
   }
   else if (l->tk=='{')
   {
      /* A block of code */
      block(execute);
   }
   else if (l->tk==';')
   {
      /* Empty statement - to allow things like ;;; */
      l->match(';');
   }
   else if (l->tk==LEX_R_VAR)
   {
      /* variable creation. TODO - we need a better way of parsing the left
       * hand side. Maybe just have a flag called can_create_var that we
       * set and then we parse as if we're doing a normal equals.*/
      l->match(LEX_R_VAR);
      while (l->tk != ';')
      {
         CScriptVarLink *a = 0;
         if (execute)
            a = scopes.last()->findChildOrCreate(l->tkStr);
         l->match(LEX_ID);
         // now do stuff defined with dots
         while (l->tk == '.')
         {
            l->match('.');
            if (execute)
            {
               CScriptVarLink *lastA = a;
               a = lastA->payload->findChildOrCreate(l->tkStr);
            }
            l->match(LEX_ID);
         }
         // sort out initialiser
         if (l->tk == '=')
         {
            l->match('=');
            CScriptVarLink *payload = axis(execute);
            if (execute)
               a->replaceWith(payload);
            CLEAN(payload);
         }
         if (l->tk != ';')
            l->match(',');
      }
      l->match(';');
   }
   else if (l->tk==LEX_R_IF)
   {
      l->match(LEX_R_IF);
      l->match('(');
      CScriptVarLink *payload = axis(execute);
      l->match(')');
      bool cond = execute && payload->payload->getBool();
      CLEAN(payload);
      bool noexecute = false; // because we need to be abl;e to write to it
      statement(cond ? execute : noexecute);
      if (l->tk==LEX_R_ELSE)
      {
         l->match(LEX_R_ELSE);
         statement(cond ? noexecute : execute);
      }
   }
   else if (l->tk==LEX_R_WHILE)
   {
      // We do repetition by pulling out the string representing our statement
      // there's definitely some opportunity for optimisation here
      l->match(LEX_R_WHILE);
      l->match('(');
      i32 whileCondStart = l->tokenStart;
      bool noexecute = false;
      CScriptVarLink *cond = axis(execute);
      bool loopCond = execute && cond->payload->getBool();
      CLEAN(cond);
      CScriptLex *whileCond = l->getSubLex(whileCondStart);
      l->match(')');
      i32 whileBodyStart = l->tokenStart;
      statement(loopCond ? execute : noexecute);
      CScriptLex *whileBody = l->getSubLex(whileBodyStart);
      CScriptLex *oldLex = l;
      i32 loopCount = TINYJS_LOOP_MAX_ITERATIONS;
      while (loopCond && loopCount-->0)
      {
         whileCond->reset();
         l = whileCond;
         cond = axis(execute);
         loopCond = execute && cond->payload->getBool();
         CLEAN(cond);
         if (loopCond)
         {
            whileBody->reset();
            l = whileBody;
            statement(execute);
         }
      }
      l = oldLex;
      delete whileCond;
      delete whileBody;

      if (loopCount<=0)
      {
         root->trace();
         information() << "WHILE Loop exceeded " << TINYJS_LOOP_MAX_ITERATIONS <<" iterations at " << l->getPosition();
         throw CScriptException("LOOP_ERROR");
      }
   }
   else if (l->tk==LEX_R_FOR)
   {
      l->match(LEX_R_FOR);
      l->match('(');
      statement(execute); // initialisation
      //l->match(';');
      i32 forCondStart = l->tokenStart;
      bool noexecute = false;
      CScriptVarLink *cond = axis(execute); // condition
      bool loopCond = execute && cond->payload->getBool();
      CLEAN(cond);
      CScriptLex *forCond = l->getSubLex(forCondStart);
      l->match(';');
      i32 forIterStart = l->tokenStart;
      CLEAN(axis(noexecute)); // iterator
      CScriptLex *forIter = l->getSubLex(forIterStart);
      l->match(')');
      i32 forBodyStart = l->tokenStart;
      statement(loopCond ? execute : noexecute);
      CScriptLex *forBody = l->getSubLex(forBodyStart);
      CScriptLex *oldLex = l;
      if (loopCond)
      {
         forIter->reset();
         l = forIter;
         CLEAN(axis(execute));
      }
      i32 loopCount = TINYJS_LOOP_MAX_ITERATIONS;
      while (execute && loopCond && loopCount-->0)
      {
         forCond->reset();
         l = forCond;
         cond = axis(execute);
         loopCond = cond->payload->getBool();
         CLEAN(cond);
         if (execute && loopCond)
         {
            forBody->reset();
            l = forBody;
            statement(execute);
         }
         if (execute && loopCond)
         {
            forIter->reset();
            l = forIter;
            CLEAN(axis(execute));
         }
      }
      l = oldLex;
      delete forCond;
      delete forIter;
      delete forBody;
      if (loopCount<=0)
      {
         root->trace();
         information() << "FOR Loop exceeded " << TINYJS_LOOP_MAX_ITERATIONS << "iterations at " << l->getPosition();
         throw CScriptException("LOOP_ERROR");
      }
   }
   else if (l->tk==LEX_R_RETURN)
   {
      l->match(LEX_R_RETURN);
      CScriptVarLink *result = 0;
      if (l->tk != ';')
         result = axis(execute);
      if (execute)
      {
         CScriptVarLink *resultVar = scopes.last()->findChild(TINYJS_RETURN_VAR);
         if (resultVar)
            resultVar->replaceWith(result);
         else
            information("RETURN statement, but not in a function.\n");
         execute = false;
      }
      CLEAN(result);
      l->match(';');
   }
   else if (l->tk==LEX_R_FUNCTION)
   {
      CScriptVarLink *funcVar = parseFunctionDefinition();
      if (execute)
      {
         if (funcVar->name == TINYJS_TEMP_NAME)
            information("Functions defined at statement-level are meant to have a name\n");
         else
            scopes.last()->addChildNoDup(funcVar->name, funcVar->payload);
      }
      CLEAN(funcVar);
   }
   else l->match(LEX_EOF);
}

/// Get the given variable specified by a path (var1.var2.etc), or return 0
CScriptVar *tinyjs::getScriptVariable(const string &path)
{
   // traverse path
   strsize prevIdx = 0;
   strsize thisIdx = path.find_index('.');
   if (thisIdx < 0) thisIdx = path.length();
   CScriptVar *payload = root;
   while (payload && prevIdx<path.length())
   {
      string el = path.substr(prevIdx, thisIdx-prevIdx);
      CScriptVarLink *varl = payload->findChild(el);
      payload = varl?varl->payload:0;
      prevIdx = thisIdx+1;
      thisIdx = path.find_index('.', prevIdx);
      if (thisIdx < 0) thisIdx = path.length();
   }
   return payload;
}

/// Get the value of the given variable, or return 0
const string *tinyjs::getVariable(const string &path)
{
   CScriptVar *payload = getScriptVariable(path);
   // return result
   if (payload)
      return &payload->getString();
   else
      return 0;
}

/// set the value of the given variable, return trur if it exists and gets set
bool tinyjs::setVariable(const string &path, const string &varData)
{
   CScriptVar *payload = getScriptVariable(path);
   // return result
   if (payload)
   {
      if (payload->isInt())
         payload->setInt((i32)strtol(varData.c_str(),0,0));
      else if (payload->isDouble())
         payload->setDouble(strtod(varData.c_str(),0));
      else
         payload->setString(varData.c_str());
      return true;
   }
   else
      return false;
}

/// Finds a child, looking recursively up the scopes
CScriptVarLink *tinyjs::findInScopes(const string &childName)
{
   for (i32 s=(i32) scopes.size()-1; s>=0; s--)
   {
      CScriptVarLink *v = scopes[s]->findChild(childName);
      if (v) return v;
   }
   return nullptr;

}

/// Look up in any parent classes of the given object
CScriptVarLink *tinyjs::findInParentClasses(CScriptVar *object, const string &name)
{
   // Look for links to actual parent classes
   CScriptVarLink *parentClass = object->findChild(TINYJS_PROTOTYPE_CLASS);
   while (parentClass)
   {
      CScriptVarLink *implementation = parentClass->payload->findChild(name);
      if (implementation) return implementation;
      parentClass = parentClass->payload->findChild(TINYJS_PROTOTYPE_CLASS);
   }
   // else fake it for strings and finally objects
   if (object->isString())
   {
      CScriptVarLink *implementation = stringClass->findChild(name);
      if (implementation) return implementation;
   }
   if (object->isArray())
   {
      CScriptVarLink *implementation = arrayClass->findChild(name);
      if (implementation) return implementation;
   }
   CScriptVarLink *implementation = objectClass->findChild(name);
   if (implementation) return implementation;

   return 0;
}
