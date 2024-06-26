#include "framework.h"
#include "command.h"


namespace menu
{


   command::command()
   {

   }


   //void menu_command::delete_this()
   //{

   //   ::message::command::delete_this();

   //}

   
   //bool menu_command::on_property_will_change(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{

   //   if (!::user::check::on_property_will_change(pcontainer, atoma, payload, actioncontext))
   //   {

   //      return false;

   //   }

   //   if (!::user::text::on_property_will_change(pcontainer, atoma, payload, actioncontext))
   //   {

   //      return false;

   //   }

   //   return true;

   //}
   //
   //
   //void menu_command::on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   //{

   //   ::user::check::on_property_changed(pcontainer, atoma, payload, actioncontext);

   //   ::user::text::on_property_changed(pcontainer, atoma, payload, actioncontext);

   //}

   void command::enable(bool bOn, const ::action_context & context)
   {

      ::message::command::enable(bOn, context);

      if (m_puiOther != nullptr)
      {

         m_puiOther->enable_window(bOn != false);

      }

   }


   //void menu_command::set_check(const ::e_check & echeck, const ::action_context & context)
   //{

   //   ASSERT(echeck == ::e_check_checked || echeck == ::e_check_unchecked || echeck == ::e_check_tristate); // 0=>off, 1=>on, 2=>indeterminate

   //   ::message::command::set_check(echeck, context);

   //   if (m_puiOther != nullptr)
   //   {

   //      ::pointer<::user::check>pcheck = m_puiOther;

   //      if(pcheck.is_set())
   //      {

   //         pcheck->set_check(echeck, context);

   //      }

   //   }

   //}


   void command::on_check_changed(::data::check_change & change)
   {

      if (m_puiOther != nullptr)
      {

         ::pointer<::user::check>pcheck = m_puiOther;

         if (pcheck.is_set())
         {

            pcheck->set_check(change.payload().as_echeck(), change.action_context());

         }

      }

   }


   void command::on_text_changed(::data::text_change & change)
   {

      if (m_puiOther != nullptr)
      {

         ::pointer<::user::text>ptext = m_puiOther;

         if(ptext.is_set())
         {

            ptext->m_textproperty.set_text(change.payload().as_string(), change.action_context());

         }

      }

   }


} // namespace user




