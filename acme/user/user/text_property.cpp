// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "text.h"
#include "acme/primitive/data/property_container.h"
//#include "acme/primitive/collection/sort.h"


namespace user
{


   text_property::text_property(::user::control * pusercontrol, ::data::property_container * ppropertycontainer, const ::atom & atom) :
      ::user::property(pusercontrol),
      ::data::text_property(ppropertycontainer, atom)
   {

   }


   text_property::~text_property()
   {

   }


   void text_property::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext)
   {


   }
   
   
   void text_property::set_text_property(const ::data::text_property & textproperty)
   {

      set_data_property(*this, textproperty);

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


   //void text_property::_001SetSelText(const ::string & psz, const ::action_context & context)
   //{

   //   string_reference() = psz;

   //}


   //void text_property::set_text(const ::string & str, const ::action_context & context)
   //{

   //   string_reference() = str;

   //}


   //strsize text_property::_001GetTextLength()
   //{

   //   string str;

   //   get_text(str);

   //   return str.length();

   //}


   //void text_property::get_text(char * psz, strsize len)
   //{

   //   string str;

   //   get_text(str);

   //   ansi_count_copy(psz,str,len);

   //}


   //void text_property::get_text(string & str, strsize iBeg, strsize iEnd)
   //{

   //   // default implementation, probably inefficient
   //   // get_text(string) returns big string
   //   // or retrieving entire string, instead of portions, is slow

   //   string strText;

   //   get_text(strText);

   //   __sort(iBeg, iEnd);

   //   str = strText.substr(iBeg, iEnd - iBeg);

   //}


   //void text_property::set_text(const ::string & str, strsize iLen, const ::action_context & context)
   //{

   //   set_text(str.substr(0, iLen),context);

   //}


   //void text_property::_001GetSel(strsize & iBeg, strsize & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::set_text_selection(strsize iBeg, strsize iEnd, const ::action_context & action_context)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);
   //   __UNREFERENCED_PARAMETER(action_context);

   //}


   //void text_property::get_text_selection(strsize & iBeg, strsize & iEnd)
   //{

   //   __UNREFERENCED_PARAMETER(iBeg);
   //   __UNREFERENCED_PARAMETER(iEnd);

   //}


   //void text_property::_001SetSelEnd(strsize iEnd, const ::action_context & actioncontext)
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


   //void text::get_text_composition_area(::rectangle_i32& rectangle)
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


   bool text_property::on_text_will_change(::data::text_property & textproperty, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & textwillchange : m_textwillchangea)
      {

         if (!textwillchange(textproperty, payload, actioncontext))
         {

            return false;

         }

      }

      return true;

   }


   void text_property::on_text_changed(::data::text_property & textproperty, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & textchanged : m_textchangeda)
      {

         textchanged(textproperty, payload, actioncontext);

      }

   }


   bool text_property::operator == (const text_property & textproperty) const
   {

      return ::data::text_property::operator == (textproperty);

   }


   //::comparable_array < text_will_change > & text::text_will_change()
   //{

   //   return m_textwillchangea;

   //}


   //::comparable_array < text_changed > & text::text_changed()
   //{

   //   return m_textchangeda;

   //}


} // namespace user



