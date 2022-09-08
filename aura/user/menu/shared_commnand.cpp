#include "framework.h"
#include "shared_command.h"
#include "shared.h"


menu_shared_command::menu_shared_command(int* pestatus) :
   m_pestatus(pestatus)
{

}


void menu_shared_command::enable(bool bOn)
{
   
   enable(bOn, ::e_source_system);
   
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


void menu_shared_command::_001SetCheck(enum_check echeck)
{
   
   _001SetCheck(echeck, ::e_source_system);
   
}

//   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
void menu_shared_command::_001SetCheck(enum_check echeck, const ::action_context& context)   // 0, 1 or 2 (indeterminate)
{

   if (echeck == e_check_checked)
   {

      *m_pestatus |= menu_shared::status_checked;

   }
   else
   {

      *m_pestatus &= ~menu_shared::status_checked;

   }

}



