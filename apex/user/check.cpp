#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
//#endif


namespace user
{


   check::check()
   {

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

      if (!m_propertyCheck)
      {

         return;

      }

      if(echeck != this->get_echeck())
      {

         auto pcheck = &m_propertyCheck->echeck();

         m_propertyCheck->echeck() = echeck;

         get_context_application()->process_subject(m_propertyCheck->m_id);

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



