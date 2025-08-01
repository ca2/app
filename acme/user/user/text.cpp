// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "text.h"
#include "acme/prototype/data/property_container.h"
//#include "acme/prototype/collection/sort.h"


namespace user
{


   text::text() :
      m_textproperty(this, this, id_text)
   {

      m_textproperty.set_text_property(m_textproperty);

      m_propertywillchangea += [this](auto & change)
         {

            if (m_textproperty && change)
            {

               ::data::text_change textchange{ m_textproperty, change };

               if (!on_text_will_change(textchange))
               {

                  return false;

               }

            }

            return true;

         };

      m_propertychangeda += [this](auto & change)
         {

            if (m_textproperty && change)
            {

               ::data::text_change textchange{ m_textproperty, change };

               on_text_changed(textchange);

            }

            return true;

         };

   }


   text::~text()
   {

   }
   
   
   void text::set_text_property(const ::data::text_property & textproperty)
   {

      m_textproperty.set_text_property(textproperty);

   }


   //void text::unhook_callbacks()
   //{

   //   if (m_ppropertycontainer)
   //   {

   //      if (m_propertywillchange)
   //      {

   //         m_ppropertycontainer->property_will_change() -= m_propertywillchange;

   //      }

   //      if (m_propertychanged)
   //      {

   //         m_ppropertycontainer->property_changed() -= m_propertychanged;

   //      }

   //   }

   //}


   //void text::hook_callbacks()
   //{

   //   m_propertywillchange = [this](::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //      {

   //         if (matches(ppropertycontainer, atoma))
   //         {

   //            for (auto & textwillchange : m_textwillchangea)
   //            {

   //               if (!textwillchange(*this, payload, actioncontext))
   //               {

   //                  return false;

   //               }

   //            }

   //         }

   //         return true;

   //      };

   //   m_ppropertycontainer->property_will_change() += m_propertywillchange;

   //   m_propertychanged = [this](::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //      {

   //         if (matches(ppropertycontainer, atoma))
   //         {

   //            for (auto & textchanged : m_textchangeda)
   //            {

   //               textchanged(*this, payload, actioncontext);

   //            }

   //         }

   //      };

   //   m_ppropertycontainer->property_changed() += m_propertychanged;

   //}


   ::user::text_property text::text_property() const
   {

      return m_textproperty;

   }



   //bool text::on_property_will_change(::data::property_change & change)
   //{

   //   if (m_textproperty && change)
   //   {

   //      ::data::text_change textchange{ m_textproperty, change };

   //      if (!on_text_will_change(textchange))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void text::on_property_changed(::data::property_change & change)
   //{


   //}


   ////void text_property::get_text(string & str)
   ////{

   ////   if (m_linkedpropertyText)
   ////   {

   ////      str = as_string();

   ////   }

   //}


   //void text_property::set_selection_text(const ::scoped_string & scopedstr, const ::action_context & context)
   //{

   //   string_reference() = psz;

   //}


   //void text_property::set_text(const ::scoped_string & scopedstr, const ::action_context & context)
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

   //   ansi_count_copy(scopedstr,str,len);

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


   //void text_property::set_text(const ::scoped_string & scopedstr, character_count iLen, const ::action_context & context)
   //{

   //   set_text(str.substr(0, iLen),context);

   //}


   //void text_property::_001GetSel(character_count & iBeg, character_count & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}

   //void text::get_text_selection(character_count & iBeg, character_count & iEnd) const
   //{

   //   m_textproperty.get_selection(iBeg, iEnd);

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


   bool text::on_text_will_change(::data::text_change & textchange)
   {

      return true;

   }


   void text::on_text_changed(::data::text_change & textchange)
   {


   }


   //::comparable_array < text_will_change > & text::text_will_change()
   //{

   //   return m_textwillchangea;

   //}


   //::comparable_array < text_changed > & text::text_changed()
   //{

   //   return m_textchangeda;

   //}


   ::string text::as_text() const
   {

      return m_textproperty.as_text();

   }


   ::string text::get_text() const
   {

      return m_textproperty.get_text();

   }


   ::string text::get_text(character_count iBegin, character_count iEnd) const
   {

      return m_textproperty.get_text(iBegin, iEnd);

   }


   character_count text::get_text_length() const
   {

      return m_textproperty.get_size();

   }


   ::string text::get_selection_text() const
   {

      return m_textproperty.get_selection_text();

   }


 /*  ::string text::get_selection_text() const
   {

      str = get_selection_text();

   }*/


   void text::get_text_selection(character_count & iBegin, character_count & iEnd) const
   {

      m_textproperty.get_selection(iBegin, iEnd);

   }


   void text::set_text_selection(character_count iBegin, character_count iEnd, const ::action_context & actioncontext)
   {

      m_textproperty.set_selection(iBegin, iEnd, actioncontext);

   }


   void text::set_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext)
   {

      m_textproperty.set_text(scopedstr, actioncontext);

   }


} // namespace user



