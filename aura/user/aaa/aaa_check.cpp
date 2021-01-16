#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


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

      _001SetCheck((::enum_check) (bChecked ? ::check_checked : ::check_unchecked),context);

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

         get_context_application()->call_update(m_ppropertyCheck->m_id, context);

      }

   }


   void check::_001ToggleCheck(const ::action_context & context)
   {

      if(bcheck())
      {

         _001SetCheck(::check_unchecked, context);

      }
      else
      {

         _001SetCheck(::check_checked, context);

      }

   }


} // namespace user



