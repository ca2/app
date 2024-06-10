#include "framework.h"
//#include "base/user/user/_component.h"


namespace user
{


   check::check()
   {

      m_ppropertyCheck = nullptr;

   }


   check::~check()
   {


   }


   void check::set_check(bool bChecked, const ::action_context & context)
   {

      set_check((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);

   }


   void check::set_check(::enum_check echeck, const ::action_context & context)
   {

      if (!m_ppropertyCheck)
      {

         return;

      }

      if(echeck != this->get_echeck())
      {

         auto pcheck = &m_ppropertyCheck->echeck();

         m_ppropertyCheck->echeck() = echeck;

         get_app()->call_update(m_ppropertyCheck->m_atom, context);

      }

   }


   void check::_001ToggleCheck(const ::action_context & context)
   {

      if(bcheck())
      {

         set_check(::e_check_unchecked, context);

      }
      else
      {

         set_check(::e_check_checked, context);

      }

   }


} // namespace user



