#include "framework.h"
#include "check.h"
#include "acme/primitive/data/property_container.h"
#include "acme/primitive/primitive/action_context.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
//#endif


namespace user
{


   check_property::check_property(::user::control * pusercontrol, ::data::property_container * ppropertycontainer, const ::atom & atom):
      ::user::property(pusercontrol),
      ::data::check_property(ppropertycontainer, atom)
   {

   }


   check_property::~check_property()
   {

   }


   ::comparable_array < check_will_change > & check_property::check_will_change()
   {

      return m_checkwillchangea;

   }


   ::comparable_array < check_changed > & check_property::check_changed()
   {

      return m_checkchangeda;

   }


   void check_property::set_check_property(const ::data::check_property & checkproperty)
   {

      unhook_callbacks();

      set_data_property(*this, checkproperty);

      hook_callbacks();

   }


   void check_property::unhook_callbacks()
   {

      if (m_ppropertycontainer)
      {

         if (m_propertywillchange)
         {

            m_ppropertycontainer->property_will_change() -= m_propertywillchange;

         }

         if (m_propertychanged)
         {

            m_ppropertycontainer->property_changed() -= m_propertychanged;

         }

      }

   }


   void check_property::hook_callbacks()
   {

      m_propertywillchange = [this](::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
         {

            if (matches(ppropertycontainer, atoma))
            {

               for (auto & checkwillchange : m_checkwillchangea)
               {

                  if (!checkwillchange(*this, payload, actioncontext))
                  {

                     return false;

                  }

               }

            }

            return true;

         };

      m_ppropertycontainer->property_will_change() += m_propertywillchange;

      m_propertychanged = [this](::data::property_container * ppropertycontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
         {

            if (matches(ppropertycontainer, atoma))
            {

               for (auto & checkchanged : m_checkchangeda)
               {

                  checkchanged(*this, payload, actioncontext);

               }

            }

         };

      m_ppropertycontainer->property_changed() += m_propertychanged;

   }


   bool check_property::on_check_will_change(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
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


   void check_property::on_check_changed(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & checkchanged : m_checkchangeda)
      {

         checkchanged(checkproperty, payload, actioncontext);

      }

   }


 /*  void check::set_check(bool bChecked, const ::action_context & context)
   {

      set_check((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);

   }*/


   //void check::set_check(const ::e_check & echeck, const ::action_context & context)
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

   //      set_check(::e_check_unchecked, context);

   //   }
   //   else
   //   {

   //      set_check(::e_check_checked, context);

   //   }

   //}


   //void check::on_check_change()
   //{


   //}


} // namespace user



