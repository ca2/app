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


   void text::get_text(string & str) const
   {

      str = strtext();

   }


   void text::_001SetSelText(const ::string & psz, const ::action_context & context)
   {

      strtext() = psz;

   }


   void text::set_text(const ::string & str, const ::action_context & context)
   {

      strtext() = str;

   }


   strsize text::_001GetTextLength() const
   {

      string str;

      get_text(str);

      return str.length();

   }


   void text::get_text(char * psz, strsize len) const
   {

      string str;

      get_text(str);

      ansi_count_copy(psz,str,len);

   }


   void text::get_text(string & str, strsize iBeg, strsize iEnd) const
   {

      // default implementation, probably inefficient
      // get_text(string) returns big string
      // or retrieving entire string, instead of portions, is slow

      string strText;

      get_text(strText);

      __sort(iBeg, iEnd);

      str = strText.substr(iBeg, iEnd - iBeg);

   }


   void text::set_text(const ::string & psz, strsize iLen, const ::action_context & context)
   {

      set_text(string(psz, iLen),context);

   }


   void text::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSel(strsize iBeg, strsize iEnd)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::get_impact_selection(strsize & iBeg, strsize & iEnd) const
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSelEnd(strsize iEnd)
   {

      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::get_selection_text(string & str) const
   {

      ::collection::index iBeg, iEnd;

      _001GetSel(iBeg, iEnd);

      get_text(str, iBeg, iEnd);

   }


   void text::MacroBegin()
   {

   }


   void text::MacroEnd()
   {

   }


} // namespace user



