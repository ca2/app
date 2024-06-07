#include "framework.h"
#include "check_control.h"
#include "acme/primitive/primitive/action_context.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
//#endif


namespace user
{


   check_control::check_control()
   {

   }


   check_control::~check_control()
   {

   }


   void check_control::set_check_property(const check_property & checkproperty)
   {

      initialize_property_link(m_checkproperty, checkproperty);

   }


   bool check_control::on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
    {

      if (m_checkproperty.matches(pcontainer, atoma))
      {

         if (!on_check_will_change(m_checkproperty, payload, actioncontext))
         {

            return false;

         }

      }

      return true;

   }

   void check_control::on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   {

      if (m_checkproperty.matches(pcontainer, atoma))
      {

         on_check_changed(m_checkproperty, payload, actioncontext);

      }

   }


   bool check_control::on_check_will_change(::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & checkwillchange : m_checkwillchangea)
      {

         if (!checkwillchange(checkproperty, payload, actioncontext))
         {

            return false;

         }

      }

      return true;

   }


   bool check_control::on_check_changed(::check_property & checkproperty, const ::payload &, const ::action_context &)
   {


   }


 /*  void check::_001SetCheck(bool bChecked, const ::action_context & context)
   {

      _001SetCheck((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);

   }*/


   //void check_control::_001SetCheck(const ::e_check & echeck, const ::action_context & context)
   //{

   //   if (!m_linkedpropertyCheck)
   //   {

   //      return;

   //   }

   //   if(echeck != this->get_echeck())
   //   {

   //      *m_linkedpropertyCheck = echeck;

   //      if (context.is_user_source())
   //      {

   //         if (m_callbackOnCheck)
   //         {

   //            m_callbackOnCheck(this);

   //         }

   //      }

   //      m_linkedpropertyCheck.notify_property_changed(context);

   //   }

   //}


   //void check::_001ToggleCheck(const ::action_context & context)
   //{

   //   if(bcheck())
   //   {

   //      _001SetCheck(::e_check_unchecked, context);

   //   }
   //   else
   //   {

   //      _001SetCheck(::e_check_checked, context);

   //   }

   //}


   //void check::on_check_change()
   //{


   //}

//
//} // namespace user



