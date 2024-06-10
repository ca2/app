#include "framework.h"
#include "text_property.h"
//#include "acme/primitive/collection/sort.h"


namespace data
{


   text_property::text_property(::data::property_container * ppropertycontainer, const ::atom & atom) :
      property(ppropertycontainer, atom)
   {


   }


   text_property::text_property(const text_property & text_property) :
      property(text_property)
   {


   }


   text_property::~text_property()
   {

   }


   //   void text_property::get_text(string & str)
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
   //   void text_property::set_text(const ::string & str, const ::action_context & context)
   //   {
   //
   //      string_reference() = str;
   //
   //   }
   //
   //
   //   strsize text_property::_001GetTextLength()
   //   {
   //
   //      string str;
   //
   //      get_text(str);
   //
   //      return str.length();
   //
   //   }
   //
   //
   //   void text_property::get_text(char * psz, strsize len)
   //   {
   //
   //      string str;
   //
   //      get_text(str);
   //
   //      ansi_count_copy(psz,str,len);
   //
   //   }
   //
   //
   //   void text_property::get_text(string & str, strsize iBeg, strsize iEnd)
   //   {
   //
   //      // default implementation, probably inefficient
   //      // get_text(string) returns big string
   //      // or retrieving entire string, instead of portions, is slow
   //
   //      string strText;
   //
   //      get_text(strText);
   //
   //      __sort(iBeg, iEnd);
   //
   //      str = strText.substr(iBeg, iEnd - iBeg);
   //
   //   }
   //
   //
   //   void text_property::set_text(const ::string & str, strsize iLen, const ::action_context & context)
   //   {
   //
   //      set_text(str.substr(0, iLen),context);
   //
   //   }
   //
   //
   //   void text_property::_001GetSel(strsize & iBeg, strsize & iEnd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //
   //   }
   //
   //
   //   void text_property::_001SetSel(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //      __UNREFERENCED_PARAMETER(action_context);
   //
   //   }
   //
   //
   //   void text_property::get_text_selection(strsize & iBeg, strsize & iEnd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //
   //   }
   //
   //
   //   void text_property::_001SetSelEnd(strsize iEnd, const ::action_context & actioncontext)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iEnd);
   //      __UNREFERENCED_PARAMETER(actioncontext);
   //
   //   }
   //
   //
   //   void text_property::get_selection_text(string & str)
   //   {
   //
   //      ::collection::index iBeg, iEnd;
   //
   //      _001GetSel(iBeg, iEnd);
   //
   //      get_text(str, iBeg, iEnd);
   //
   //   }
   //
   //
   //   void text_property::MacroBegin()
   //   {
   //
   //   }
   //
   //
   //   void text_property::MacroEnd()
   //   {
   //
   //   }
   //
   //
   //   void text_property::insert_text(string str, bool bForceNewStep, const ::action_context& context)
   //   {
   //
   //
   //   }
   //
   //
   //   string text_property::as_string() const
   //   { 
   //      
   //      return m_linkedpropertyText->as_string();
   //   
   //   }
   //
   //
   //   string& text_property::string_reference() 
   //   {
   //      
   //      return m_linkedpropertyText->string_reference(); 
   //   
   //   }
   //
   //
   //
   //   bool text_property::edit_undo()
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   void text_property::get_text_composition_area(::rectangle_i32& rectangle)
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


   ::string text_property::as_text() const
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


   //::string text_property::as_text() const
   //{

   //   return this->operator string_base<const ansi_character *>();

   //}


   bool text_property::set_selection_text(const ::scoped_string & scopedstrNewSelectionText, const ::action_context & actioncontext)
   {

      auto strText = this->as_text();

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

      return this->as_text().size();

   }


   void text_property::get_text(char * psz, strsize len)
   {

      auto strText = this->as_text();

      ansi_count_copy(psz, strText, len);

   }


   void text_property::get_text(::string & str) const
   {

      str = this->as_text();

   }


   void text_property::get_text(::string & str, strsize iBeg, strsize iEnd) const
   {

      auto strText = this->as_text();

      __sort(iBeg, iEnd);

      str = strText(iBeg, iEnd - iBeg);

   }


   void text_property::set_text(const ::scoped_string & scopedstrText, strsize iLen, const ::action_context & actioncontext)
   {

      set_text(scopedstrText(0, iLen), actioncontext);

   }


   text_property & text_property::operator = (const payload_action_context & payloadactioncontext)
   {

      set_text(payloadactioncontext.m_payload.as_string(),
         payloadactioncontext.m_actioncontext);

      return*this;

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


      void text_property::get_text_selection(strsize & iBeg, strsize & iEnd)
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


   ::string text_property::get_selection_text() const
   {

      ::strsize iBegin;

      ::strsize iEnd;

      get_selection(iBegin, iEnd);

      auto strFull = as_text();

      auto str = strFull(iBegin, iEnd);

      return str;

   }

   /*
      void text_property::MacroBegin()
      {

      }


      void text_property::MacroEnd()
      {

      }


      void text_property::insert_text(string str, bool bForceNewStep, const ::action_context& context)
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
      string& text_property::string_reference()
      {

         return m_linkedpropertyText->string_reference();

      }



      bool text_property::edit_undo()
      {

         return false;

      }


      void text_property::get_text_composition_area(::rectangle_i32& rectangle)
      {


      }

   */


} // namespace data