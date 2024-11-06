// Created by camilo on 2024-06-10 23:27 <3ThomasBorregaardSorensen!! ThomasLikesNumber5!!
#include "framework.h"
#include "text_handler.h"
#include "acme/prototype/data/property_container.h"


namespace data
{


   text_handler::text_handler(::data::property_container * ppropertycontainer, const ::atom & atom) :
      ::data::text_property(ppropertycontainer, atom)
   {

   }


   text_handler::~text_handler()
   {

   }


   void text_handler::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext)
   {


   }


   void text_handler::set_text_property(const ::data::text_property & textproperty)
   {

      unhook_callbacks();

      initialize_data_property(textproperty);

      hook_callbacks();

   }


   void text_handler::unhook_callbacks()
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


   void text_handler::hook_callbacks()
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


   //bool text_handler::on_property_will_change(::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
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


   //void text_handler::on_property_changed(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{


   //}


   ////void text_handler::get_text(string & str)
   ////{

   ////   if (m_linkedpropertyText)
   ////   {

   ////      str = as_string();

   ////   }

   //}


   //void text_handler::set_selection_text(const ::string & psz, const ::action_context & context)
   //{

   //   string_reference() = psz;

   //}


   //void text_handler::set_text(const ::string & str, const ::action_context & context)
   //{

   //   string_reference() = str;

   //}


   //character_count text_handler::get_text_length()
   //{

   //   string str;

   //   get_text(str);

   //   return str.length();

   //}


   //void text_handler::get_text(char * psz, character_count len)
   //{

   //   string str;

   //   get_text(str);

   //   ansi_count_copy(psz,str,len);

   //}


   //void text_handler::get_text(string & str, character_count iBeg, character_count iEnd)
   //{

   //   // default implementation, probably inefficient
   //   // get_text(string) returns big string
   //   // or retrieving entire string, instead of portions, is slow

   //   string strText;

   //   get_text(strText);

   //   __sort(iBeg, iEnd);

   //   str = strText.substr(iBeg, iEnd - iBeg);

   //}


   //void text_handler::set_text(const ::string & str, character_count iLen, const ::action_context & context)
   //{

   //   set_text(str.substr(0, iLen),context);

   //}


   //void text_handler::_001GetSel(character_count & iBeg, character_count & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_handler::set_text_selection(character_count iBeg, character_count iEnd, const ::action_context & action_context)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(action_context);

   //}


   //void text_handler::get_text_selection(character_count & iBeg, character_count & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_handler::_001SetSelEnd(character_count iEnd, const ::action_context & actioncontext)
   //{

   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(actioncontext);

   //}


   //void text_handler::get_selection_text(string & str)
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


   //bool text_handler::on_text_will_change(::user::text_change & textchange)
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


   //void text_handler::on_text_changed(::user::text_change & textchange)
   //{

   //   for (auto & textchanged : m_textchangeda)
   //   {

   //      textchanged(textchange);

   //   }

   //}


   bool text_handler::operator == (const ::data::text_property & textproperty) const
   {

      return ::data::text_property::operator == (textproperty);

   }


   bool text_handler::operator == (const ::data::text_change & change) const
   {

      return this->operator == (change.m_textproperty);

   }


   //::comparable_array < text_will_change > & text::text_will_change()
   //{

   //   return m_textwillchangea;

   //}


   //::comparable_array < text_changed > & text::text_changed()
   //{

   //   return m_textchangeda;

   //}



} // namespace data



