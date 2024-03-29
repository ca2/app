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


   void check::_001SetCheck(bool bChecked, const ::action_context & context)
   {

      _001SetCheck((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);

   }


   void check::_001SetCheck(::enum_check echeck, const ::action_context & context)
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

         _001SetCheck(::e_check_unchecked, context);

      }
      else
      {

         _001SetCheck(::e_check_checked, context);

      }

   }


} // namespace user



