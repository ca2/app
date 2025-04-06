#include "framework.h"
#include "text_property.h"
#include "acme/prototype/data/property_container.h"


namespace data
{


   text_property::text_property(::data::property_container * ppropertycontainer, const ::atom & atom) :
      property(ppropertycontainer, atom)
   {


   }


   text_property::text_property(const ::data::property & property) :
      ::data::property(property)
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
   //   void text_property::set_selection_text(const ::string & psz, const ::action_context & context)
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
   //   character_count text_property::get_text_length()
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
   //   void text_property::get_text(char * psz, character_count len)
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
   //   void text_property::get_text(string & str, character_count iBeg, character_count iEnd)
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
   //   void text_property::set_text(const ::string & str, character_count iLen, const ::action_context & context)
   //   {
   //
   //      set_text(str.substr(0, iLen),context);
   //
   //   }
   //
   //
   //   void text_property::_001GetSel(character_count & iBeg, character_count & iEnd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //
   //   }
   //
   //
   //   void text_property::set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & action_context)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //      __UNREFERENCED_PARAMETER(action_context);
   //
   //   }
   //
   //
   //   void text_property::get_text_selection(character_count & iBeg, character_count & iEnd)
   //   {
   //
   //      __UNREFERENCED_PARAMETER(iBeg);
   //      __UNREFERENCED_PARAMETER(iEnd);
   //
   //   }
   //
   //
   //   void text_property::_001SetSelEnd(character_count iEnd, const ::action_context & actioncontext)
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
   //   void text_property::get_text_composition_area(::int_rectangle& rectangle)
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

      return this->get_property({ id_text }).as_string();

   }


   ::string text_property::as_text(character_count iBegin, character_count iEnd) const
   {

      return this->get_property({ id_text, iBegin, iEnd }).as_string();
   }


   ::character_count text_property::selection_begin() const
   {

      return this->get_property({ id_text_selection_begin }).as_iptr();

   }


   ::character_count text_property::selection_end() const
   {

      return this->get_property({ id_text_selection_end }).as_iptr();


   }


   //::string text_property::as_text() const
   //{

   //   return this->operator string_base<const ansi_character *>();

   //}


   bool text_property::set_selection_text(const ::scoped_string & scopedstrNewSelectionText, const ::action_context & actioncontext)
   {

      auto strText = this->as_text();

      character_count iBegin;

      character_count iEnd;

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

      return set_property({ id_text }, scopedstrText, actioncontext);

   }


   character_count text_property::get_size() const
   {

      return this->get_text_length();

   }


   character_count text_property::get_text_length() const
   {

      return this->get_property({ id_text_length }).as_long_long();

   }


  /* void text_property::get_text(char * psz, character_count len)
   {

      auto strText = this->as_text();

      ansi_count_copy(psz, strText, len);

   }*/


   ::string text_property::get_text() const
   {

      return this->as_text();

   }


   ::string text_property::get_text(character_count iBegin, character_count iEnd) const
   {

      return this->as_text(iBegin, iEnd);

   }

   //void text_property::get_text(::string & str, character_count iBeg, character_count iEnd) const
   //{

   //   auto strText = this->as_text();

   //   sort_non_negative(iBeg, iEnd);

   //   str = strText(iBeg, iEnd - iBeg);

   //}


   void text_property::set_text(const ::scoped_string & scopedstrText, character_count iLen, const ::action_context & actioncontext)
   {

      set_text(scopedstrText(0, iLen), actioncontext);

   }


   text_property & text_property::operator = (const payload_action_context & payloadactioncontext)
   {

      set_text(payloadactioncontext.m_payload.as_string(),
         payloadactioncontext.m_actioncontext);

      return*this;

   }


   void text_property::get_selection(character_count & iBegin, character_count & iEnd) const
   {

      iBegin = selection_begin();

      iEnd = selection_end();

   }


   // character_count selection_begin() const
   // {
   //
   //    ::character_count iBegin;
   //
   //    ::character_count iEnd;
   //
   //    get_selection(iBegin, iEnd);
   //
   //    return iBegin;
   //
   // }


   // character_count selection_end() const
   // {
   //
   //    ::character_count iBegin;
   //
   //    ::character_count iEnd;
   //
   //    get_selection(iBegin, iEnd);
   //
   //    return iEnd;
   //
   // }


   void text_property::set_selection(character_count iBegin, character_count iEnd, const ::action_context & actioncontext)
   {

      set_selection_begin(iBegin, actioncontext);

      set_selection_end(iEnd, actioncontext);

   }

   /*
      void set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & action_context)
      {

         __UNREFERENCED_PARAMETER(iBeg);
         __UNREFERENCED_PARAMETER(iEnd);
         __UNREFERENCED_PARAMETER(action_context);

      }


      void text_property::get_text_selection(character_count & iBeg, character_count & iEnd)
      {

         __UNREFERENCED_PARAMETER(iBeg);
         __UNREFERENCED_PARAMETER(iEnd);

      }
   */

   void text_property::set_selection_begin(character_count iBegin, const ::action_context & actioncontext)
   {

      set_property({ id_text_selection_begin }, iBegin, actioncontext);

   }


   void text_property::set_selection_end(character_count iEnd, const ::action_context & actioncontext)
   {

      set_property({ id_text_selection_end }, iEnd, actioncontext);

   }


   ::string text_property::get_selection_text() const
   {

      ::character_count iBegin;

      ::character_count iEnd;

      get_selection(iBegin, iEnd);

      auto strFull = as_text();

      __sort(iBegin, iEnd);

      auto str = strFull(iBegin, iEnd - iBegin);

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


      void text_property::get_text_composition_area(::int_rectangle& rectangle)
      {


      }

   */

   bool text_property::operator == (const text_property & textproperty) const
   {

      return ::data::property::operator ==(textproperty);

   }


   //text_property::text_property(::data::property_container * ppropertycontainer, const ::atom & atom) :
   //   ::data::text_property(ppropertycontainer, atom)
   //{

   //}


   //text_property::~text_property()
   //{

   //}


   void text_property::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext)
   {


   }


   void text_property::set_text_property(const ::data::text_property & textproperty)
   {

      unhook_callbacks();

      initialize_data_property(textproperty);

      hook_callbacks();

   }


   void text_property::unhook_callbacks()
   {

      if (m_ppropertycontainer)
      {

         if (m_propertywillchange)
         {

            m_ppropertycontainer->property_will_change() -= m_propertywillchange;

         }

         if (m_propertychanged)
         {

            m_ppropertycontainer->property_changed() -= m_propertychanged;

         }

      }

   }


   void text_property::hook_callbacks()
   {

      m_propertywillchange = [this](auto & change)
         {

            if (operator &&(change))
            {

               ::data::text_change textchange{ *this, change };

               for (auto & textwillchange : m_textwillchangea)
               {

                  if (!textwillchange(textchange))
                  {

                     return false;

                  }

               }

            }

            return true;

         };

      m_ppropertycontainer->property_will_change() += m_propertywillchange;

      m_propertychanged = [this](auto & change)
         {

            if (operator&&(change))
            {

               ::data::text_change textchange{ *this, change };

               for (auto & textchanged : m_textchangeda)
               {

                  textchanged(textchange);

               }

            }

         };

      m_ppropertycontainer->property_changed() += m_propertychanged;

   }


   //bool text_property::on_property_will_change(::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{

   //   if (m_textproperty.matches(ppropertycontainer, atoma))
   //   {

   //      if (!on_text_will_change(m_textproperty, payload, actioncontext))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void text_property::on_property_changed(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{


   //}


   ////void text_property::get_text(string & str)
   ////{

   ////   if (m_linkedpropertyText)
   ////   {

   ////      str = as_string();

   ////   }

   //}


   //void text_property::set_selection_text(const ::string & psz, const ::action_context & context)
   //{

   //   string_reference() = psz;

   //}


   //void text_property::set_text(const ::string & str, const ::action_context & context)
   //{

   //   string_reference() = str;

   //}


   //character_count text_property::get_text_length()
   //{

   //   string str;

   //   get_text(str);

   //   return str.length();

   //}


   //void text_property::get_text(char * psz, character_count len)
   //{

   //   string str;

   //   get_text(str);

   //   ansi_count_copy(psz,str,len);

   //}


   //void text_property::get_text(string & str, character_count iBeg, character_count iEnd)
   //{

   //   // default implementation, probably inefficient
   //   // get_text(string) returns big string
   //   // or retrieving entire string, instead of portions, is slow

   //   string strText;

   //   get_text(strText);

   //   __sort(iBeg, iEnd);

   //   str = strText.substr(iBeg, iEnd - iBeg);

   //}


   //void text_property::set_text(const ::string & str, character_count iLen, const ::action_context & context)
   //{

   //   set_text(str.substr(0, iLen),context);

   //}


   //void text_property::_001GetSel(character_count & iBeg, character_count & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & action_context)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(action_context);

   //}


   //void text_property::get_text_selection(character_count & iBeg, character_count & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::_001SetSelEnd(character_count iEnd, const ::action_context & actioncontext)
   //{

   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(actioncontext);

   //}


   //void text_property::get_selection_text(string & str)
   //{

   //   ::collection::index iBeg, iEnd;

   //   _001GetSel(iBeg, iEnd);

   //   get_text(str, iBeg, iEnd);

   //}


   //void text::MacroBegin()
   //{

   //}


   //void text::MacroEnd()
   //{

   //}


   //void text::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context& context)
   //{


   //}


   //string text::as_string() const
   //{ 
   //   
   //   return m_linkedpropertyText->as_string();
   //
   //}


   //string& text::string_reference() 
   //{
   //   
   //   return m_linkedpropertyText->string_reference(); 
   //
   //}



   //bool text::edit_undo()
   //{

   //   return false;

   //}


   //void text::get_text_composition_area(::int_rectangle& rectangle)
   //{


   //}


   //bool text::on_property_will_change(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{

   //   if (matches(pcontainer, atoma))
   //   {

   //      if (!on_text_will_change(*this, payload, actioncontext))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void text::on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{

   //   if (matches(pcontainer, atoma))
   //   {

   //      on_text_changed(*this, payload, actioncontext);

   //   }

   //}


   //bool text_property::on_text_will_change(::user::text_change & textchange)
   //{

   //   for (auto & textwillchange : m_textwillchangea)
   //   {

   //      if (!textwillchange(textchange))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void text_property::on_text_changed(::user::text_change & textchange)
   //{

   //   for (auto & textchanged : m_textchangeda)
   //   {

   //      textchanged(textchange);

   //   }

   //}


   //bool text_property::operator == (const ::data::text_property & textproperty) const
   //{

   //   return ::data::text_property::operator == (textproperty);

   //}


   //bool text_property::operator == (const ::data::text_change & change) const
   //{

   //   return this->operator == (change.m_textproperty);

   //}


   //::comparable_array < text_will_change > & text::text_will_change()
   //{

   //   return m_textwillchangea;

   //}


   //::comparable_array < text_changed > & text::text_changed()
   //{

   //   return m_textchangeda;

   //}


} // namespace data
