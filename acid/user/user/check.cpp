#include "framework.h"
#include "check.h"
#include "acid/primitive/primitive/action_context.h"
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


 /*  void check::_001SetCheck(bool bChecked, const ::action_context & context)
   {

      _001SetCheck((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);

   }*/


   void check::_001SetCheck(const ::e_check & echeck, const ::action_context & context)
   {

      if (!m_linkedpropertyCheck)
      {

         return;

      }

      if(echeck != this->get_echeck())
      {

         *m_linkedpropertyCheck = echeck;

         if (context.is_user_source())
         {

            if (m_callbackOnCheck)
            {

               m_callbackOnCheck(this);

            }

         }

         m_linkedpropertyCheck.notify_property_changed(context);

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


   void check::on_check_change()
   {


   }


} // namespace user



