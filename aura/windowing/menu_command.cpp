#include "framework.h"
#include "menu_item.h"
#include "menu_command.h"
#include "menu.h"


namespace windowing
{


   menu_command::menu_command(menu_item * pitem) :
      m_pitem(pitem)
   {

   }


   void menu_command::enable(bool bOn, const ::action_context & context)
   {

      if (bOn)
      {

         m_pitem->erase_status(::windowing::e_status_disabled);

      }
      else
      {

         m_pitem->add_status(::windowing::e_status_disabled);

      }

   }


   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   void menu_command::_001SetCheck(enum_check echeck, const ::action_context & context)   // 0, 1 or 2 (indeterminate)
   {

      if (echeck == check_checked)
      {

         m_pitem->add_status(::windowing::e_status_checked);

      }
      else
      {

         m_pitem->erase_status(::windowing::e_status_checked);

      }

   }


} // namespace windowing





