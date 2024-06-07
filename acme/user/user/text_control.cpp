// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "text_control.h"
//#include "acme/primitive/collection/sort.h"


namespace user
{


   text_control::text_control()
   {

   }


   text_control::~text_control()
   {

   }
   
   
   void text_control::set_text_property(const text_property & textproperty)
   {

      initialize_property_link(m_textproperty, textproperty);

   }


   ////void text_property::_001GetText(string & str)
   ////{

   ////   if (m_linkedpropertyText)
   ////   {

   ////      str = as_string();

   ////   }

   //}


   //void text_property::_001SetSelText(const ::string & psz, const ::action_context & context)
   //{

   //   string_reference() = psz;

   //}


   //void text_property::_001SetText(const ::string & str, const ::action_context & context)
   //{

   //   string_reference() = str;

   //}


   //strsize text_property::_001GetTextLength()
   //{

   //   string str;

   //   _001GetText(str);

   //   return str.length();

   //}


   //void text_property::_001GetText(char * psz, strsize len)
   //{

   //   string str;

   //   _001GetText(str);

   //   ansi_count_copy(psz,str,len);

   //}


   //void text_property::_001GetText(string & str, strsize iBeg, strsize iEnd)
   //{

   //   // default implementation, probably inefficient
   //   // _001GetText(string) returns big string
   //   // or retrieving entire string, instead of portions, is slow

   //   string strText;

   //   _001GetText(strText);

   //   __sort(iBeg, iEnd);

   //   str = strText.substr(iBeg, iEnd - iBeg);

   //}


   //void text_property::_001SetText(const ::string & str, strsize iLen, const ::action_context & context)
   //{

   //   _001SetText(str.substr(0, iLen),context);

   //}


   //void text_property::_001GetSel(strsize & iBeg, strsize & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::_001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(action_context);

   //}


   //void text_property::_001GetImpactSel(strsize & iBeg, strsize & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::_001SetSelEnd(strsize iEnd, const ::action_context & actioncontext)
   //{

   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(actioncontext);

   //}


   //void text_property::_001GetSelText(string & str)
   //{

   //   ::collection::index iBeg, iEnd;

   //   _001GetSel(iBeg, iEnd);

   //   _001GetText(str, iBeg, iEnd);

   //}


   void text_control::MacroBegin()
   {

   }


   void text_control::MacroEnd()
   {

   }


   void text_control::insert_text(string str, bool bForceNewStep, const ::action_context& context)
   {


   }


   //string text_control::as_string() const
   //{ 
   //   
   //   return m_linkedpropertyText->as_string();
   //
   //}


   //string& text_control::string_reference() 
   //{
   //   
   //   return m_linkedpropertyText->string_reference(); 
   //
   //}



   bool text_control::edit_undo()
   {

      return false;

   }


   void text_control::get_text_composition_area(::rectangle_i32& rectangle)
   {


   }


} // namespace user



