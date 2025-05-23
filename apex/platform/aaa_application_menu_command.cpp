/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:21 <3ThomasBorregaardSorensen
#include "framework.h"
#include "application_menu.h"
#include "application_menu_command.h"
#include "acme/prototype/prototype/action_context.h"


//namespace apex
//{


application_menu_command::application_menu_command(int* pestatus) :
   m_pestatus(pestatus)
   {
      
   }


   void application_menu_command::enable(bool bOn)
   {
      
      enable(bOn, ::e_source_system);
      
   }


   void application_menu_command::enable(bool bOn, const ::action_context& context)
   {
      
      if (bOn)
      {
         
         *m_pestatus &= ~application_menu::e_status_disabled;
         
      }
      else
      {
         
         *m_pestatus |= application_menu::e_status_disabled;
         
      }
      
   }


   void application_menu_command::set_check(enum_check echeck)
   {
      
      set_check(echeck, ::e_source_system);
      
   }

   //   virtual void set_check(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   void application_menu_command::set_check(enum_check echeck, const ::action_context& context)   // 0, 1 or 2 (indeterminate)
   {
      
      if (echeck == e_check_checked)
      {
         
         *m_pestatus |= application_menu::e_status_checked;
         
      }
      else
      {
         
         *m_pestatus &= ~application_menu::e_status_checked;
         
      }
      
   }


//} // namespace apex



