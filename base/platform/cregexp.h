#pragma once
//
///**
//    @addtogroup cregexp Regular Expressions
//      Colorer Regular Expressions (cregexp) class implementation.
//*/
//
///// with this define class uses extended command set for
///// colorer compatibility mode
///// if you undef it, it will compile stantard set for
///// regexp compatibility mode
//#define COLORERMODE
//
///// use hashes for saving named brackets
////#define NAMED_MATCHES_IN_HASH
//
///// check duplicate brackets
////#define CHECKNAMES
//
//#if defined COLORERMODE && defined NAMED_MATCHES_IN_HASH
//#error COLORERMODE && NAMED_MATCHES_IN_HASH not realyzed yet
//#endif
//
///// numeric matches num
//#define MATCHES_NUM 0x10
//#define NAMED_MATCHES_NUM 0x10
//
//struct SMatch
//{
//   strsize s,e;
//};
//// you can redefine this class
//class SMatchHash
//{
//public:
//
//
//   string_map<SMatch> m_map;
//
//
//   SMatch *setItem(string name, SMatch &smatch);
//   SMatch *getItem(string name);
//
//};
//
//
//typedef class SMatchHash *PMatchHash;
//
//enum EOps
//{
//   ReBlockOps,
//   ReMul,              // *
//   RePlus,             // +
//   ReQuest,            // ?
//   ReNGMul,            // *?
//   ReNGPlus,           // +?
//   ReNGQuest,          // ??
//   ReRangeN,           // {n,}
//   ReRangeNM,          // {n,m}
//   ReNGRangeN,         // {n,}?
//   ReNGRangeNM,        // {n,m}?
//   ReOr,               // |
//   ReBehind,           // ?#n
//   ReNBehind,          // ?~n
//   ReAhead,            // ?=
//   ReNAhead,           // ?!
//
//   ReSymbolOps,
//   ReEmpty,
//   ReMetaSymb,         // \W \s \d ...
//   ReSymb,             // a b ca ...
//   ReWord,             // u16...
//   ReEnum,             // []
//   ReNEnum,            // [^]
//   ReBrackets,         // (...)
//   ReNamedBrackets,    // (?{name} ...)
//#ifdef COLORERMODE
//   ReBkTrace,          // \yN
//   ReBkTraceN,         // \YN
//   ReBkTraceName,      // \y{name}
//   ReBkTraceNName,     // \Y{name}
//#endif
//   ReBkBrack,          // \N
//   ReBkBrackName       // \point{name}
//};
//
//enum EMetaSymbols
//{
//   ReBadMeta,
//   ReAnyChr,           // .
//   ReSoL,              // ^
//#ifdef COLORERMODE
//   ReSoScheme,         // ~
//#endif
//   ReEoL,              // $
//   ReDigit,            // \d
//   ReNDigit,           // \D
//   ReWordSymb,         // \w
//   ReNWordSymb,        // \W
//   ReWSpace,           // \s isWhiteSpace()
//   ReNWSpace,          // \S
//   ReUCase,            // \u
//   ReNUCase,           // \l
//   ReWBound,           // \b
//   ReNWBound,          // \B
//   RePreNW,            // \ca
//#ifdef COLORERMODE
//   ReStart,            // \m
//   ReEnd,              // \M
//#endif
//
//   ReChrLast
//
//};
//
//enum EError
//{
//   EOK = 0, EERROR, ESYNTAX, EBRACKETS, EENUM, EOP
//};
//
//
///// @ingroup cregexp
//struct SMatches
//{
//   strsize s[MATCHES_NUM];
//   strsize e[MATCHES_NUM];
//   ::count cMatch;
//};
//
///** Regular expressions internal tree node.
//    @ingroup cregexp
//*/
//class CLASS_DECL_AURA SRegInfo
//{
//public:
//   SRegInfo();
//   ~SRegInfo();
//
//////#include "ca_memory_operator.h"
//
//   EOps op;
//   union
//   {
//      EMetaSymbols metaSymbol;
//      string *symbol;
//      string *ui;
//      ::str::ch_class *charclass;
//      SRegInfo *lparam;
//   } un;
//   string namedata;
//   strsize oldParse;
//   strsize param0, param1;
//   strsize s, e;
//
//   SRegInfo *parent;
//   SRegInfo *next;
//   SRegInfo *prev;
//};
//
///** Regular Expression compiler and matcher.
//    Colorer regular expressions library cregexp.
//
//\par 1. Features.
//
//\par 1.1. Colorer Unicode classes.
//   - Unicode Consortium regexp level 1 support.
//     All characters are treated as independent 16-bit units.
//     The result of RE is independent of current locale.
//   - Unicode syntax extensions:
//     - Unicode general category char class:
//         - [{L}{Nd}] - all letters and decimal digits,
//         - [{ALL}]   - as '.',
//         - [{ASSIGNED}] - all assigned unicode characters,
//         - [{UNASSIGNED}] - all unassigned unicode characters.
//     - char classes substraction unicode extension:
//         - [{ASSIGNED}-[{Lu}]-[{Ll}]] - all assigned characters except,
//         - upper and lower case characters.
//     - char classes connection syntax:
//         - [{Lu}[{Ll}]] - upper and lower case characters.
//     - char classes intersection syntax:
//         - [{ALL}&&[{L}]] - only Letter characters.
//     - Character context_object syntax: \\x{2028} \\x0A as in Perl.
//     - Unicode form \\u2028 is unused (\\u - upper case char).
//
//\par 1.2. Extensions.
//   - Bracket extensions:
//     - (?{name} pattern ) - named bracket,
//     - \\point{name} - named bracket context_object.
//     - (?{} pattern ) - no capturing bracket as (?: pattern ) in Perl.
//   - Look Ahead/Backward:
//     - pattern?=  as Perl's (?=pattern)
//     - pattern?!  as Perl's (?!pattern)
//     - pattern?#N - N symbols backward look for pattern
//     - pattern?~N - N symbols backward look for no pattern
//   - Colorer library extensions:
//     - \\m \\M - sets new start and end of zero(default) bracket.
//     - \\yN \\YN \\y{name} \\Y{name} - back context_object into another RE's bracket.
//
//\par 1.3. Perl compatibility.
//   - Modifiers //ismx
//   - \\ point{name} - back context_object to named bracket (but not named property as in Perl!)
//   - No POSIX character classes support.
//
//
//
//\par 2. Dislikes:
//
//\par 2.1. According to Unicode RE level 1 support:
//   - No surrogate symbols support,
//   - No string get_length changes on case mappings (only 1 <-> 1 mappings),
//\par 2.2. Algorithmic problems:
//   - Stack recursion implementation.
//
//    @ingroup cregexp
//*/
//class CLASS_DECL_AURA cregexp :
//   virtual public ::object
//{
//public:
//   /**
//     Empty constructor. No RE tree is builded with this constructor.
//     Use #setRE method to change pattern.
//   */
//   cregexp();
//   /**
//     Constructs regular expression and compile it with @ca text pattern.
//   */
//   cregexp(string text);
//   ~cregexp();
//
//   /**
//     Is compilied RE well-formed.
//   */
//   bool isOk();
//
//   /**
//     Returns information about RE compilation error.
//   */
//   EError getError();
//
//   /**
//     Tells RE parser, that it must make moves on tested string while RE matching.
//   */
//   bool setPositionMoves(bool moves);
//   /**
//     Returns ::count of named brackets.
//   */
//
//#ifdef COLORERMODE
//   bool setBackRE(cregexp *bkre);
//   /**
//     Changes RE object, used for backreferences with named \y{} \Y{} operators.
//   */
//   bool setBackTrace(string str, SMatches *trace);
//   /**
//     Returns current RE object, used for backreferences with \y \Y operators.
//   */
//   bool getBackTrace(string *str, SMatches **trace);
//#endif
//   /**
//     Compiles specified regular expression and drops all
//     previous structures.
//   */
//   bool setRE(string re);
//   /** Runs RE parser against input string @ca str
//   */
//   bool parse(string str, SMatches *mtch, SMatchHash *nmtch = nullptr);
//   /** Runs RE parser against input string @ca str
//   */
//   bool parse(string str, strsize pos, strsize eol, SMatches *mtch, SMatchHash *nmtch = nullptr, i32 soscheme = 0, i32 moves = -1);
//
//
//   bool ignoreCase, extend, positionMoves, singleLine, multiLine;
//   SRegInfo *tree_root;
//   EError error;
//   string firstChar;
//   EMetaSymbols firstMetaChar;
//#ifdef COLORERMODE
//   cregexp *backRE;
//   string backStr;
//   SMatches *backTrace;
//   strsize schemeStart;
//#endif
//   bool startChange, endChange;
//   string global_pattern;
//   strsize end;
//
//   SMatches *matches;
//   i32 cMatch;
//   SMatchHash *namedMatches;
//
//   void init();
//   EError setRELow(const char * re);
//   EError setStructs(SRegInfo *&, const char * expr, strsize &endPos);
//
//   void optimize();
//   bool quickCheck(strsize toParse);
//   bool isWordBoundary(strsize &toParse);
//   bool isNWordBoundary(strsize &toParse);
//   bool checkMetaSymbol(EMetaSymbols metaSymbol, strsize &toParse);
//   bool lowParse(SRegInfo *re, SRegInfo *prev, strsize toParse);
//   bool parseRE(strsize toParse);
//
//
//
//
//   bool    match(const string & pcsz);
//
//   index   match(string_array & stra, const string & pcsz, strsize iSize);
//
//   bool    find(string & strMatch, const string & str, index iSubString, strsize * piStart = nullptr, strsize * piEnd = nullptr);
//   bool    find(const string & str, index iSubString, strsize * piStart = nullptr, strsize * piEnd = nullptr);
//   bool    split(string_array & stra, index_array & iaStart, index_array & iaEnd, const string & str, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
//   bool    split(string_array & stra, const string & str, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
//   bool    replace(string & str, const string & strTopic, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
//   bool    replace(string & str, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
//
//};
//
//
///* ***** BEGIN LICENSE BLOCK *****
// * Version: MPL 1.1/GPL 2.0/LGPL 2.1
// *
// * The contents of this file are subject to the Mozilla Public License Version
// * 1.1 (the "License"); you may not use this file except in compliance with
// * the License. You may obtain a copy of the License at
// * http://www.mozilla.org/MPL/
// *
// * Software distributed under the License is distributed on an "AS IS" basis,
// * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// * for the specific language governing rights and limitations under the
// * License.
// *
// * The Original Code is the Colorer Library.
// *
// * The Initial Developer of the Original Code is
// * Cail Lomecb <cail@nm.ru>.
// * Portions created by the Initial Developer are Copyright (C) 1999-2005
// * the Initial Developer.
// *
// * Contributor(s):
// *
// * Alternatively, the contents of this file may be used under the terms of
// * either the GNU General Public License Version 2 or later (the "GPL"), or
// * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
// * in which case the provisions of the GPL or the LGPL are applicable instead
// * of those above. If you wish to allow use of your version of this file only
// * under the terms of either the GPL or the LGPL, and not to allow others to
// * use your version of this file under the terms of the MPL, indicate your
// * decision by deleting the provisions above and replace them with the notice
// * and other provisions required by the GPL or the LGPL. If you do not delete
// * the provisions above, a recipient may use your version of this file under
// * the terms of any one of the MPL, the GPL or the LGPL.
// *
// * ***** END LICENSE BLOCK ***** */
//
//
//
//
//
