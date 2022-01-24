#include "framework.h"


//cregexp_util::cregexp_util()
//{
//
//}
//
//cregexp_util::~cregexp_util()
//{
//
//}
//
//
//
//
//index cregexp_util::match(string_array & stra, const string & pcsz, const string & pszExpression, bool bCaseInsensitive, strsize iSize)
//
//{
//
//   __pointer(cregexp) pre = CompileExpression(pszExpression, bCaseInsensitive);
//
//
//   return match(stra, pcsz, pre, iSize);
//
//
//}
//
//
//index cregexp_util::match(string_array & stra, const string & pcsz, cregexp * pre, strsize iSize)
//
//{
//
//   if (pre == nullptr)
//   {
//
//      return -1;
//
//   }
//
//   index i = pre->match(stra, pcsz, iSize);
//
//
//   return i;
//
//}
//
//
//
//bool cregexp_util::find(string & strMatch, const ::string & str, const ::string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
//{
//
//   __pointer(cregexp) pre = CompileExpression(strExp, false);
//
//   if(pre.is_null())
//      return false;
//
//
//   bool bOk = pre->find(strMatch, str, iSubString, piStart, piEnd);
//
//   return bOk;
//
//}
//
//
//bool cregexp_util::find(const ::string & str, const ::string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
//{
//
//   __pointer(cregexp) pre = CompileExpression(strExp, false);
//
//   if(pre.is_null())
//      return false;
//
//   bool bOk = pre->find(str, iSubString, piStart, piEnd);
//
//   return bOk;
//
//}
//
//
//
//__pointer(cregexp) cregexp_util::CompileExpression(const string & pszExp, bool bCaseInsensitive)
//
//{
//
//   __UNREFERENCED_PARAMETER(bCaseInsensitive);
//
//   return __new(cregexp(pszExp));
//
//
//}
//
//
//bool cregexp_util::split(string_array & stra, index_array & iaStart, index_array & iaEnd,  const ::string & str, const ::string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
//{
//
//   __pointer(cregexp) pre = CompileExpression(strExp, false);
//
//   if(pre.is_null())
//      return false;
//
//   bool bFound = pre->split(stra, iaStart, iaEnd, str, iLimit, bAddEmpty, bWithSeparator);
//
//   return bFound;
//
//
//}
//
//bool    cregexp_util::split(string_array & stra, const ::string & str, const ::string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
//{
//
//   __pointer(cregexp) pre = CompileExpression(strExp, false);
//
//   if(pre.is_null())
//      return false;
//
//   bool bFound = pre->split(stra, str, iLimit, bAddEmpty, bWithSeparator);
//
//   return bFound;
//
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
////
//// Name: add_tokens
////
//// Purpose:
//// add non overlapping ocurrences of "expression" in "subject".
//// Substring indicates the parenthesis order of the desired substring.
////
//// Output:
//// 'true' if successfull.
////
/////////////////////////////////////////////////////////////////////////////////
//bool cregexp_util::add_tokens(string_array & stra, const string & pszSubject, const ::string & strExp, index iSubString /* =0 */)
//
//{
//
//   __pointer(cregexp) pre = CompileExpression(strExp, false);
//
//   if(pre.is_null())
//      return false;
//
//   pre->setPositionMoves(true);
//
//   string strSubject;
//
//
//   strSubject = pszSubject;
//
//
//   string strToken;
//
//   strsize start;
//   strsize end = 0;
//
//   if(iSubString < 0)
//      iSubString = 0;
//
//   strsize find = 0;
//   while(end < ansi_length(pszSubject))
//
//   {
//      SMatches matches;
//      if(!pre->parse(&pszSubject[find], &matches))
//
//         break;
//      start   = matches.s[iSubString] + find;
//      end     = matches.e[iSubString] + find;
//
//      strToken = strSubject.Mid(start, end - start);
//
//      strToken = strToken;
//
//      stra.add(strToken);
//      find = end + 1;
//   }
//
//   return true;
//
//}
//
//
//bool cregexp_util::match(const string & psz, const ::string & strExp)
//
//{
//
//   __pointer(cregexp) re;
//
//   re = CompileExpression(strExp, true);
//
//   return re->match(psz);
//
//
//}
//
//
//
//void cregexp_util::Format(string & str, string_array & wstraArg)
//{
//
//   string wstrExp;
//
//   for(i32 i = 0; i < wstraArg.get_size(); i++)
//   {
//
//      wstrExp.format("/(%%%d)(\\d?!|$)/", i);
//
//      __pointer(cregexp) pre = CompileExpression(wstrExp, false);
//
//      pre->setPositionMoves(true);
//
//      pre->replace(str, 1, wstraArg[i]);
//
//   }
//
//}
//
//bool cregexp_util::replace(string & str, const ::string & strTopicParam, const ::string & strExp, index iSubString, const ::string & strReplace, strsize start, strsize end)
//{
//
//   __pointer(cregexp) re;
//
//   re = CompileExpression(strExp, true);
//
//   return re->replace(str, strTopicParam, iSubString, strReplace, start, end);
//
//}
//
//bool cregexp_util::replace(string & str, const ::string & strExp, index iSubString, const ::string & strReplace, strsize start, strsize end)
//{
//
//   __pointer(cregexp) re;
//
//   re = CompileExpression(strExp, true);
//
//   return re->replace(str, iSubString, strReplace, start, end);
//
//}
//
