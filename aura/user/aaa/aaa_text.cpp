#include "framework.h"
//#include "base/user/user/_component.h"



namespace user
{


   text::text()
   {

      m_ppropertyText = nullptr;

   }


   text::~text()
   {

   }


   void text::_001GetText(string & str) const
   {

      str = strtext();

   }


   void text::_001SetSelText(const ::string & psz, const ::action_context & context)
   {

      strtext() = psz;

   }


   void text::_001SetText(const ::string & str, const ::action_context & context)
   {

      strtext() = str;

   }


   strsize text::_001GetTextLength() const
   {

      string str;

      _001GetText(str);

      return str.length();

   }


   void text::_001GetText(char * psz, strsize len) const
   {

      string str;

      _001GetText(str);

      ansi_count_copy(psz,str,len);

   }


   void text::_001GetText(string & str, strsize iBeg, strsize iEnd) const
   {

      // default implementation, probably inefficient
      // _001GetText(string) returns big string
      // or retrieving entire string, instead of portions, is slow

      string strText;

      _001GetText(strText);

      __sort(iBeg, iEnd);

      str = strText.substr(iBeg, iEnd - iBeg);

   }


   void text::_001SetText(const ::string & psz, strsize iLen, const ::action_context & context)
   {

      _001SetText(string(psz, iLen),context);

   }


   void text::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSel(strsize iBeg, strsize iEnd)
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001GetImpactSel(strsize & iBeg, strsize & iEnd) const
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSelEnd(strsize iEnd)
   {

      UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001GetSelText(string & str) const
   {

      index iBeg, iEnd;

      _001GetSel(iBeg, iEnd);

      _001GetText(str, iBeg, iEnd);

   }


   void text::MacroBegin()
   {

   }


   void text::MacroEnd()
   {

   }


} // namespace user



