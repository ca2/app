#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif



namespace user
{


   menu_command::menu_command(::layered * pobjectContext) :
      ::user::command(pobjectContext)
   {

   }


   //void menu_command::delete_this()
   //{

   //   ::user::command::delete_this();

   //}


   void menu_command::enable(bool bOn, const ::action_context & context)
   {

      ::user::command::enable(bOn, context);

      if (m_puiOther != nullptr)
      {

         m_puiOther->enable_window(bOn != FALSE);

      }

   }


   void menu_command::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      ASSERT(echeck == ::check_checked || echeck == ::check_unchecked || echeck == ::check_tristate); // 0=>off, 1=>on, 2=>indeterminate

      ::user::command::_001SetCheck(echeck, context);

      if (m_puiOther != nullptr)
      {

         __pointer(::user::check) pcheck = m_puiOther;

         if(pcheck.is_set())
         {

            pcheck->_001SetCheck(echeck, context);

         }

      }

   }


   void menu_command::_001SetText(const string & strText, const ::action_context & context)
   {

      if (m_puiOther != nullptr)
      {

         __pointer(::user::text) ptext = m_puiOther;

         if(ptext.is_set())
         {

            ptext->_001SetText(strText, context);

         }

      }

   }


} // namespace user




