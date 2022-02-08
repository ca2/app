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

#ifndef TINYJS_H
#define TINYJS_H

// If defined, this keeps a note of all calls and where from in memory. This is slower, but good for debugging
#define TINYJS_callstack
#ifdef __MCRTDBG
#ifdef _WIN32
#ifdef __DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif //__DEBUG
#endif
#endif

#ifndef TRACE
#define TRACE printf
#endif // TRACE


const i32 TINYJS_LOOP_MAX_ITERATIONS = 8192;


enum LEX_TYPES
{
   LEX_EOF = 0,
   LEX_ID = 256,
   LEX_INT,
   LEX_FLOAT,
   LEX_STR,

   LEX_EQUAL,
   LEX_TYPEEQUAL,
   LEX_NEQUAL,
   LEX_NTYPEEQUAL,
   LEX_LEQUAL,
   LEX_LSHIFT,
   LEX_LSHIFTEQUAL,
   LEX_GEQUAL,
   LEX_RSHIFT,
   LEX_RSHIFTUNSIGNED,
   LEX_RSHIFTEQUAL,
   LEX_PLUSEQUAL,
   LEX_MINUSEQUAL,
   LEX_PLUSPLUS,
   LEX_MINUSMINUS,
   LEX_ANDEQUAL,
   LEX_ANDAND,
   LEX_OREQUAL,
   LEX_OROR,
   LEX_XOREQUAL,
   // reserved words
#define LEX_R_LIST_START LEX_R_IF
   LEX_R_IF,
   LEX_R_ELSE,
   LEX_R_DO,
   LEX_R_WHILE,
   LEX_R_FOR,
   LEX_R_BREAK,
   LEX_R_CONTINUE,
   LEX_R_FUNCTION,
   LEX_R_RETURN,
   LEX_R_VAR,
   LEX_R_TRUE,
   LEX_R_FALSE,
   LEX_R_NULL,
   LEX_R_UNDEFINED,
   LEX_R_NEW,

   LEX_R_LIST_END /* always the last entry */
};

enum SCRIPTVAR_FLAGS
{
   SCRIPTVAR_UNDEFINED   = 0,
   SCRIPTVAR_FUNCTION    = 1,
   SCRIPTVAR_OBJECT      = 2,
   SCRIPTVAR_ARRAY       = 4,
   SCRIPTVAR_DOUBLE      = 8,  // floating point_i32 double
   SCRIPTVAR_INTEGER     = 16, // integer number
   SCRIPTVAR_STRING      = 32, // string
   SCRIPTVAR_NULL        = 64, // it seems nullptr is its own data type

   SCRIPTVAR_NATIVE      = 128, // to specify this is a native function
   SCRIPTVAR_NUMERICMASK = SCRIPTVAR_NULL |
                           SCRIPTVAR_DOUBLE |
                           SCRIPTVAR_INTEGER,
   SCRIPTVAR_VARTYPEMASK = SCRIPTVAR_DOUBLE |
                           SCRIPTVAR_INTEGER |
                           SCRIPTVAR_STRING |
                           SCRIPTVAR_FUNCTION |
                           SCRIPTVAR_OBJECT |
                           SCRIPTVAR_ARRAY |
                           SCRIPTVAR_NULL

};


#define TINYJS_RETURN_VAR "return"
#define TINYJS_PROTOTYPE_CLASS "prototype"
#define TINYJS_TEMP_NAME ""
#define TINYJS_BLANK_DATA ""

/// convert the given string into a quoted string suitable for javascript
string getJSString(const string &str);

class CLASS_DECL_APP_SCRIPTING CScriptException :
   virtual public ::exception
{
public:
   string text;
   CScriptException(const string &exceptionText);
};

class CLASS_DECL_APP_SCRIPTING CScriptLex
{
public:
   CScriptLex(const string &input);
   CScriptLex(CScriptLex *owner, i32 startChar, i32 endChar);
   ~CScriptLex(void);

   char currCh, nextCh;
   i32 tk; ///< The type of the token that we have
   i32 tokenStart; ///< Position in the data at the beginning of the token we have here
   i32 tokenEnd; ///< Position in the data at the last character of the token we have here
   i32 tokenLastEnd; ///< Position in the data at the last character of the last token
   string tkStr; ///< Data contained in the token we have here

   void match(i32 expected_tk); ///< Lexical match wotsit
   static string getTokenStr(i32 token); ///< Get the string representation of the given token
   void reset(); ///< Reset this lex so we can start again

   string getSubString(i32 pos); ///< Return a sub-string from the given position up until right now
   CScriptLex *getSubLex(i32 lastPosition); ///< Return a sub-lexer from the given position up until right now

   string getPosition(i32 pos=-1); ///< Return a string representing the position in lines and columns of the character pos given

protected:
   /* When we go into a loop, we use getSubLex to get a lexer for just the sub-part of the
      relevant string. This doesn't re-allocate and copy the string, but instead copies
      the data pointer and sets dataOwned to false, and dataStart/dataEnd to the relevant things. */
   char *data; ///< Data string to get tokens from
   i32 dataStart, dataEnd; ///< Start and end position in data string
   bool dataOwned; ///< Do we own this data string?

   i32 dataPos; ///< Position in data (we CAN go past the end of the string here)

   void getNextCh();
   void getNextToken(); ///< Get the text token from our text string
};

class CScriptVar;

typedef void (*JSCallback)(CScriptVar * payload, void * userdata);

class CLASS_DECL_APP_SCRIPTING CScriptVarLink
{
public:
   string name;
   CScriptVarLink * nextSibling;
   CScriptVarLink * prevSibling;
   CScriptVar * payload;
   bool owned;

   CScriptVarLink(CScriptVar * payload, const string &name = TINYJS_TEMP_NAME);
   CScriptVarLink(const CScriptVarLink &link); ///< Copy constructor
   ~CScriptVarLink();
   void replaceWith(CScriptVar *newVar); ///< Replace the Variable pointed to
   void replaceWith(CScriptVarLink *newVar); ///< Replace the Variable pointed to (just dereferences)
   i32 getIntName(); ///< Get the name as an integer (for arrays)
   void setIntName(i32 n); ///< set the name as an integer (for arrays)
};

/// Variable class (containing a doubly-linked list of children)
class CLASS_DECL_APP_SCRIPTING CScriptVar
{
public:
   CScriptVar(); ///< Create undefined
   CScriptVar(const string &varData, i32 varFlags); ///< User defined
   CScriptVar(const string &str); ///< Create a string
   CScriptVar(double varData);
   CScriptVar(i32 val);
   ~CScriptVar(void);

   CScriptVar *getReturnVar(); ///< If this is a function, get the result value (for use by native functions)
   void setReturnVar(CScriptVar * payload); ///< set the result value. Use this when setting complex return data as it avoids a deepCopy()
   CScriptVar *getParameter(const string &name); ///< If this is a function, get the parameter with the given name (for use by native functions)

   CScriptVarLink *findChild(const string &childName); ///< Tries to find a child with the given name, may return 0
   CScriptVarLink *findChildOrCreate(const string &childName, i32 varFlags=SCRIPTVAR_UNDEFINED); ///< Tries to find a child with the given name, or will create it with the given flags
   CScriptVarLink *findChildOrCreateByPath(const string &path); ///< Tries to find a child with the given path (separated by dots)
   CScriptVarLink *addChild(const string &childName, CScriptVar *child=nullptr);
   CScriptVarLink *addChildNoDup(const string &childName, CScriptVar *child=nullptr); ///< add a child overwriting any with the same name
   void eraseChild(CScriptVar *child);
   void eraseLink(CScriptVarLink *link); ///< Remove a specific link (this is faster than finding via a child)
   void eraseAllChildren();
   CScriptVar *getArrayIndex(i32 idx); ///< The the value at an array index
   void setArrayIndex(i32 idx, CScriptVar *value); ///< set the value at an array index
   i32 getArrayLength(); ///< If this is an array, return the number of items in it (else 0)
   i32 getChildren(); ///< Get the number of children

   i32 getInt();
   bool getBool() { return getInt() != 0; }
   double getDouble();
   const string &getString();
   string getParsableString(); ///< get Data as a parsable javascript string
   void setInt(i32 num);
   void setDouble(double val);
   void setString(const string &str);
   void setUndefined();
   void setArray();
   bool equals(CScriptVar *v);

   bool isInt() { return (flags&SCRIPTVAR_INTEGER)!=0; }
   bool isDouble() { return (flags&SCRIPTVAR_DOUBLE)!=0; }
   bool isString() { return (flags&SCRIPTVAR_STRING)!=0; }
   bool isNumeric() { return (flags&SCRIPTVAR_NUMERICMASK)!=0; }
   bool isFunction() { return (flags&SCRIPTVAR_FUNCTION)!=0; }
   bool isObject() { return (flags&SCRIPTVAR_OBJECT)!=0; }
   bool isArray() { return (flags&SCRIPTVAR_ARRAY)!=0; }
   bool isNative() { return (flags&SCRIPTVAR_NATIVE)!=0; }
   bool isUndefined() { return (flags & SCRIPTVAR_VARTYPEMASK) == SCRIPTVAR_UNDEFINED; }
   bool isNull() { return (flags & SCRIPTVAR_NULL)!=0; }
   bool isBasic() { return firstChild==0; } ///< Is this *not* an array/object/etc

   CScriptVar *mathsOp(CScriptVar *b, i32 op); ///< do a maths op with another script variable
   void copyValue(CScriptVar *val); ///< copy the value from the value given
   CScriptVar *deepCopy(); ///< deep copy this node and return the result

   void trace(string indentStr = "", const string &name = ""); ///< Dump out the contents of this using trace
   string getFlagsAsString(); ///< For debugging - just dump a string version of the flags
   void getJSON(string & str, const string linePrefix=""); ///< Write out all the JS code needed to recreate this script variable to the stream (as JSON)
   void setCallback(JSCallback callback, void *userdata); ///< set the callback for native functions

   CScriptVarLink *firstChild;
   CScriptVarLink *lastChild;

   /// For memory management/garbage collection
   CScriptVar *ref(); ///< add object to this variable
   void unref(); ///< Remove a object, and delete this variable if required
   i32 getRefs(); ///< Get the number of references to this script variable
protected:
   i32 refs; ///< The number of references held to this - used for garbage collection

   string data; ///< The contents of this variable if it is a string
   long intData; ///< The contents of this variable if it is an i32
   double doubleData; ///< The contents of this variable if it is a double
   i32 flags; ///< the flags determine the type of the variable - i32/double/string/etc
   JSCallback jsCallback; ///< Callback for native functions
   void *jsCallbackUserData; ///< user data passed as element2() argument to native functions

   void init(); ///< initialisation of data members

   /** Copy the basic data and flags from the variable given, with no
     * children. Should be used internally only - by copyValue and deepCopy */
   void copySimpleData(CScriptVar *val);

   friend class tinyjs;
};


class CLASS_DECL_APP_SCRIPTING tinyjs :
   virtual public ::matter
{
public:


   tinyjs();
   virtual ~tinyjs();

   void execute(const string &code);
   /** Evaluate the given code and return a link to a javascript object,
    * useful for (dangerous) JSON parsing. If nothing to return, will return
    * 'undefined' variable type. CScriptVarLink is returned as this will
    * automatically unref the result as it goes out of scope. If you want to
    * keep it, you must use ref() and unref() */
   CScriptVarLink evaluateComplex(const string &code);
   /** Evaluate the given code and return a string. If nothing to return, will return
    * 'undefined' */
   string evaluate(const string &code);

   /// add a native function to be called from TinyJS
   /** example:
      \code
          void scRandInt(CScriptVar *ca, void *userdata) { ... }
          tinyJS->addNative("function randInt(minimum, maximum)", scRandInt, 0);
      \endcode

      or

      \code
          void scSubstring(CScriptVar *ca, void *userdata) { ... }
          tinyJS->addNative("function String.substring(lo, hi)", scSubstring, 0);
      \endcode
   */
   void addNative(const string &funcDesc, JSCallback ptr, void *userdata);

   /// Get the given variable specified by a path (var1.var2.etc), or return 0
   CScriptVar *getScriptVariable(const string &path);
   /// Get the value of the given variable, or return 0
   const string *getVariable(const string &path);
   /// set the value of the given variable, return trur if it exists and gets set
   bool setVariable(const string &path, const string &varData);

   /// Send all variables to stdout
   void trace();

   object *   m_p;
   CScriptVar *root;   /// root of symbol table
private:
   CScriptLex *l;             /// current lexer
   address_array < CScriptVar * >  scopes; /// stack of scopes when parsing
#ifdef TINYJS_callstack
   string_array callstack; /// Names of places called so we can show when erroring
#endif

   CScriptVar *stringClass; /// Built in string class
   CScriptVar *objectClass; /// Built in object class
   CScriptVar *arrayClass; /// Built in array class

   // parsing - in order of precedence
   CScriptVarLink *functionCall(bool &execute, CScriptVarLink *function, CScriptVar *parent);
   CScriptVarLink *factor(bool &execute);
   CScriptVarLink *unary(bool &execute);
   CScriptVarLink *term(bool &execute);
   CScriptVarLink *expression(bool &execute);
   CScriptVarLink *shift(bool &execute);
   CScriptVarLink *condition(bool &execute);
   CScriptVarLink *logic(bool &execute);
   CScriptVarLink *ternary(bool &execute);
   CScriptVarLink *axis(bool &execute);
   void block(bool &execute);
   void statement(bool &execute);
   // parsing utility functions
   CScriptVarLink *parseFunctionDefinition();
   void parseFunctionArguments(CScriptVar *funcVar);

   CScriptVarLink *findInScopes(const string &childName); ///< Finds a child, looking recursively up the scopes
   /// Look up in any parent classes of the given object
   CScriptVarLink *findInParentClasses(CScriptVar *object, const string &name);
};

#endif
