#pragma once

//
//namespace aura
//{
//
//
//   class str_context;
//
//
//} // namespace aura
//
//
//class CLASS_DECL_AURA cregexp_util
//{
//public:
//
//
//   cregexp_util();
//   virtual ~cregexp_util();
//
//
//   static void    Format(string & str, string_array & wstraArg);
//
//
//   static bool    add_tokens(string_array & stra, const string & psz, const string & pszExp, index iSubString = 0);
//
//
//
//   static bool    match(const string & pcsz, const string & strExp);
//
//
//
//   static index   match(string_array & stra, const string & pcsz, cregexp * pre, strsize iSize);
//
//
//   static index   match(string_array & stra, const string & pcsz, const string & pszExpression, bool bCaseInsensitive, strsize iSize);
//
//
//
//   static bool    find(string & strMatch, const string & str, const string & strExp, index iSubString, strsize * piStart = nullptr, strsize * piEnd = nullptr);
//
//   static bool    find(const string & str, const string & strExp, index iSubString, strsize * piStart = nullptr, strsize * piEnd = nullptr);
//
//   static bool    split(string_array & stra, index_array & iaStart, index_array & iaEnd, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
//   static bool    split(string_array & stra, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
//
//
//
//   static bool    replace(string & str, const string & strTopic, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
//   static bool    replace(string & str, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
//
//
//
//   static __pointer(cregexp) CompileExpression(const string & pszExp, bool bCaseInsensitive);
//
//
//
//
//
//};
//
//
