#include "framework.h"
#include "text_property.h"
//#include "acme/primitive/collection/sort.h"

//
//namespace user
//{

text_property::text_property(::property_container * ppropertycontainer, const ::atom & atom) :
   property_link(ppropertycontainer, atom)
{
}
text_property::text_property(const text_property & checkproperty) :
   property_link(checkproperty)
{


}
text_property::~text_property()
{

}


//   void text_property::_001GetText(string & str)
//   {
//
//      if (m_linkedpropertyText)
//      {
//
//         str = as_string();
//
//      }
//
//   }
//
//
//   void text_property::_001SetSelText(const ::string & psz, const ::action_context & context)
//   {
//
//      string_reference() = psz;
//
//   }
//
//
//   void text::_001SetText(const ::string & str, const ::action_context & context)
//   {
//
//      string_reference() = str;
//
//   }
//
//
//   strsize text::_001GetTextLength()
//   {
//
//      string str;
//
//      _001GetText(str);
//
//      return str.length();
//
//   }
//
//
//   void text::_001GetText(char * psz, strsize len)
//   {
//
//      string str;
//
//      _001GetText(str);
//
//      ansi_count_copy(psz,str,len);
//
//   }
//
//
//   void text::_001GetText(string & str, strsize iBeg, strsize iEnd)
//   {
//
//      // default implementation, probably inefficient
//      // _001GetText(string) returns big string
//      // or retrieving entire string, instead of portions, is slow
//
//      string strText;
//
//      _001GetText(strText);
//
//      __sort(iBeg, iEnd);
//
//      str = strText.substr(iBeg, iEnd - iBeg);
//
//   }
//
//
//   void text::_001SetText(const ::string & str, strsize iLen, const ::action_context & context)
//   {
//
//      _001SetText(str.substr(0, iLen),context);
//
//   }
//
//
//   void text::_001GetSel(strsize & iBeg, strsize & iEnd)
//   {
//
//      __UNREFERENCED_PARAMETER(iBeg);
//      __UNREFERENCED_PARAMETER(iEnd);
//
//   }
//
//
//   void text::_001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
//   {
//
//      __UNREFERENCED_PARAMETER(iBeg);
//      __UNREFERENCED_PARAMETER(iEnd);
//      __UNREFERENCED_PARAMETER(action_context);
//
//   }
//
//
//   void text::_001GetImpactSel(strsize & iBeg, strsize & iEnd)
//   {
//
//      __UNREFERENCED_PARAMETER(iBeg);
//      __UNREFERENCED_PARAMETER(iEnd);
//
//   }
//
//
//   void text::_001SetSelEnd(strsize iEnd, const ::action_context & actioncontext)
//   {
//
//      __UNREFERENCED_PARAMETER(iEnd);
//      __UNREFERENCED_PARAMETER(actioncontext);
//
//   }
//
//
//   void text::_001GetSelText(string & str)
//   {
//
//      ::collection::index iBeg, iEnd;
//
//      _001GetSel(iBeg, iEnd);
//
//      _001GetText(str, iBeg, iEnd);
//
//   }
//
//
//   void text::MacroBegin()
//   {
//
//   }
//
//
//   void text::MacroEnd()
//   {
//
//   }
//
//
//   void text::insert_text(string str, bool bForceNewStep, const ::action_context& context)
//   {
//
//
//   }
//
//
//   string text::as_string() const
//   { 
//      
//      return m_linkedpropertyText->as_string();
//   
//   }
//
//
//   string& text::string_reference() 
//   {
//      
//      return m_linkedpropertyText->string_reference(); 
//   
//   }
//
//
//
//   bool text::edit_undo()
//   {
//
//      return false;
//
//   }
//
//
//   void text::get_text_composition_area(::rectangle_i32& rectangle)
//   {
//
//
//   }
//
////
////} // namespace user
////
////
////


::string text_property::text() const 
{
   
   return this->get_property({ ID_TEXT }).as_string(); 

}


::strsize text_property::selection_begin() const
{
   
   return this->get_property({ ID_TEXT_SELECTION_BEGIN }).as_iptr(); 

}


::strsize text_property::selection_end() const 
{
   
   return this->get_property({ ID_TEXT_SELECTION_END }).as_iptr(); 


}


void   text_property::get_text(string & str)
{


   str = this->text();

}


bool text_property::set_selection_text(const ::scoped_string & scopedstrNewSelectionText, const ::action_context & actioncontext)
{

   auto strText = this->text();

   strsize iBegin;

   strsize iEnd;

   this->get_selection(iBegin, iEnd);

   auto strLeft = strText(0, iBegin);

   auto strRight = strText(iEnd);

   if (!set_text(strLeft + scopedstrNewSelectionText + strRight, actioncontext))
   {

      return false;

   }

   set_selection_end(iBegin + scopedstrNewSelectionText.size(), actioncontext);

   return true;

}


bool text_property::set_text(const ::scoped_string & scopedstrText, const ::action_context & actioncontext)
{

   return set_property({ ID_TEXT }, scopedstrText, actioncontext);

}


strsize text_property::get_size() const
{

   return this->text().size();

}


void text_property::get_text(char * psz, strsize len)
{

   auto strText = this->text();

   ansi_count_copy(psz, strText, len);

}


void text_property::get_text(string & str, strsize iBeg, strsize iEnd) const
{

   auto strText = this->text();

   __sort(iBeg, iEnd);

   str = strText(iBeg, iEnd - iBeg);

}


void text_property::set_text(const ::scoped_string & scopedstrText, strsize iLen, const ::action_context & actioncontext)
{

   set_text(scopedstrText(0, iLen), actioncontext);

}


void text_property::get_selection(strsize & iBegin, strsize & iEnd) const
{

   iBegin = selection_begin();

   iEnd = selection_end();

}


// strsize selection_begin() const
// {
//
//    ::strsize iBegin;
//
//    ::strsize iEnd;
//
//    get_selection(iBegin, iEnd);
//
//    return iBegin;
//
// }


// strsize selection_end() const
// {
//
//    ::strsize iBegin;
//
//    ::strsize iEnd;
//
//    get_selection(iBegin, iEnd);
//
//    return iEnd;
//
// }


void text_property::set_selection(strsize iBegin, strsize iEnd, const ::action_context & actioncontext)
{

   set_selection_begin(iBegin, actioncontext);

   set_selection_end(iEnd, actioncontext);

}

/*
   void _001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
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
*/

void text_property::set_selection_begin(strsize iBegin, const ::action_context & actioncontext)
{

   set_property({ ID_TEXT_SELECTION_BEGIN }, iBegin, actioncontext);

}


void text_property::set_selection_end(strsize iEnd, const ::action_context & actioncontext)
{

   set_property({ ID_TEXT_SELECTION_END }, iEnd, actioncontext);

}


void text_property::get_selection_text(::string & str) const
{

   ::strsize iBegin;

   ::strsize iEnd;

   get_selection(iBegin, iEnd);

   get_text(str, iBegin, iEnd);

}

/*
   void text::MacroBegin()
   {

   }


   void text::MacroEnd()
   {

   }


   void text::insert_text(string str, bool bForceNewStep, const ::action_context& context)
   {


   }
*/
/*
   string as_string() const
   {

      return get_property().as_string();

   }
*/
/*
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

*/
