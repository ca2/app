#include "framework.h"
#include "text.h"
//#include "acme/primitive/collection/sort.h"


namespace user
{


   text::text()
   {

   }


   text::~text()
   {

   }


   void text::_001GetText(string & str)
   {

      if (m_linkedpropertyText)
      {

         str = as_string();

      }

   }


   void text::_001SetSelText(const ::string & psz, const ::action_context & context)
   {

      string_reference() = psz;

   }


   void text::_001SetText(const ::string & str, const ::action_context & context)
   {

      string_reference() = str;

   }


   strsize text::_001GetTextLength()
   {

      string str;

      _001GetText(str);

      return str.length();

   }


   void text::_001GetText(char * psz, strsize len)
   {

      string str;

      _001GetText(str);

      ansi_count_copy(psz,str,len);

   }


   void text::_001GetText(string & str, strsize iBeg, strsize iEnd)
   {

      // default implementation, probably inefficient
      // _001GetText(string) returns big string
      // or retrieving entire string, instead of portions, is slow

      string strText;

      _001GetText(strText);

      __sort(iBeg, iEnd);

      str = strText.substr(iBeg, iEnd - iBeg);

   }


   void text::_001SetText(const ::string & str, strsize iLen, const ::action_context & context)
   {

      _001SetText(str.substr(0, iLen),context);

   }


   void text::_001GetSel(strsize & iBeg, strsize & iEnd)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);
      __UNREFERENCED_PARAMETER(action_context);

   }


   void text::_001GetImpactSel(strsize & iBeg, strsize & iEnd)
   {

      __UNREFERENCED_PARAMETER(iBeg);
      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001SetSelEnd(strsize iEnd)
   {

      __UNREFERENCED_PARAMETER(iEnd);

   }


   void text::_001GetSelText(string & str)
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


   void text::insert_text(string str, bool bForceNewStep, const ::action_context& context)
   {


   }


   string text::as_string() const
   { 
      
      return m_linkedpropertyText->as_string();
   
   }


   string& text::string_reference() 
   {
      
      return m_linkedpropertyText->string_reference(); 
   
   }



   bool text::edit_undo()
   {

      return false;

   }


   void text::get_text_composition_area(::rectangle_i32& rectangle)
   {


   }


} // namespace user



