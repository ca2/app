#include "framework.h"
//#include "berg/user/user/_component.h"



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


   void text::set_selection_text(const ::scoped_string & scopedstr, const ::action_context & context)
   {

      strtext() = psz;

   }


   void text::set_text(const ::scoped_string & scopedstr, const ::action_context & context)
   {

      strtext() = str;

   }


   character_count text::get_text_length() const
   {

      string str;

      get_text(str);

      return str.length();

   }


   void text::get_text(char * psz, character_count len) const
   {

      string str;

      get_text(str);

      ansi_count_copy(scopedstr,str,len);

   }


   void text::get_text(string & str, character_count iBeg, character_count iEnd) const
   {

      // default implementation, probably inefficient
      // get_text(string) returns big string
      // or retrieving entire string, instead of portions, is slow

      string strText;

      get_text(strText);

      __sort(iBeg, iEnd);

      str = strText.substr(iBeg, iEnd - iBeg);

   }


   void text::set_text(const ::scoped_string & scopedstr, character_count iLen, const ::action_context & context)
   {

      set_text(string(scopedstr, iLen),context);

   }


   void text::_001GetSel(character_count & iBeg, character_count & iEnd) const
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::set_text_selection(character_count iBeg, character_count iEnd)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::get_text_selection(character_count & iBeg, character_count & iEnd) const
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSelEnd(character_count iEnd)
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



