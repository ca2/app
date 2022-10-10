#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
#include "command.h"



namespace user
{


   menu_command::menu_command()
   {

   }


   //void menu_command::delete_this()
   //{

   //   ::message::command::delete_this();

   //}


   void menu_command::enable(bool bOn, const ::action_context & context)
   {

      ::message::command::enable(bOn, context);

      if (m_puiOther != nullptr)
      {

         m_puiOther->enable_window(bOn != false);

      }

   }


   void menu_command::_001SetCheck(const ::e_check & echeck, const ::action_context & context)
   {

      ASSERT(echeck == ::e_check_checked || echeck == ::e_check_unchecked || echeck == ::e_check_tristate); // 0=>off, 1=>on, 2=>indeterminate

      ::message::command::_001SetCheck(echeck, context);

      if (m_puiOther != nullptr)
      {

         ::pointer<::user::check>pcheck = m_puiOther;

         if(pcheck.is_set())
         {

            pcheck->_001SetCheck(echeck, context);

         }

      }

   }


   void menu_command::_001SetText(const ::string & strText, const ::action_context & context)
   {

      if (m_puiOther != nullptr)
      {

         ::pointer<::user::text>ptext = m_puiOther;

         if(ptext.is_set())
         {

            ptext->_001SetText(strText, context);

         }

      }

   }


} // namespace user




