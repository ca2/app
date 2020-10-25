#include "framework.h"
#include "menu_shared_command.h"
#include "menu_shared.h"


menu_shared_command::menu_shared_command(int* pestatus) :
   m_pestatus(pestatus)
{

}


void menu_shared_command::enable(bool bOn, const ::action_context& context)
{

   if (bOn)
   {

      *m_pestatus &= ~menu_shared::status_disabled;

   }
   else
   {

      *m_pestatus |= menu_shared::status_disabled;

   }

}


//   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::source_system);   // 0, 1 or 2 (indeterminate)
void menu_shared_command::_001SetCheck(enum_check echeck, const ::action_context& context)   // 0, 1 or 2 (indeterminate)
{

   if (echeck == check_checked)
   {

      *m_pestatus |= menu_shared::status_checked;

   }
   else
   {

      *m_pestatus &= ~menu_shared::status_checked;

   }

}



