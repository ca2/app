// Created by camilo on 2024-06-10 23:27 <3ThomasBorregaardSorensen!! ThomasLikesNumber5!!
#include "framework.h"
#include "check_handler.h"
#include "acme/primitive/data/property_container.h"


namespace data
{


   check_handler::check_handler(::data::property_container * ppropertycontainer, const ::atom & atom) :
      ::data::check_property(ppropertycontainer, atom)
   {

   }


   check_handler::~check_handler()
   {

   }


   ::add_signal_function_to_holder < ::data::check_will_change > check_handler::check_will_change(::matter * pmatterFunctionHolder)
   {

      return { m_checkwillchangesignal, pmatterFunctionHolder };

   }


   ::add_signal_function_to_holder < ::data::check_changed > check_handler::check_changed(::matter * pmatterFunctionHolder)
   {

      return { m_checkchangedsignal, pmatterFunctionHolder };

   }


   void check_handler::set_check_property(const ::data::check_property & checkproperty)
   {

      unhook_callbacks();

      initialize_data_property(checkproperty);

      hook_callbacks();

   }


   void check_handler::unhook_callbacks()
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


   void check_handler::hook_callbacks()
   {

      m_propertywillchange = [this](::data::property_change & change)
         {

            if (operator &&(change))
            {

               check_change checkchange{ *this, change };

               for (auto & checkwillchange : m_checkwillchangesignal.m_functiona)
               {

                  if (!checkwillchange(checkchange))
                  {

                     return false;

                  }

               }

            }

            return true;

         };

      m_ppropertycontainer->property_will_change() += m_propertywillchange;

      m_propertychanged = [this](::data::property_change & change)
         {

            if (operator &&(change))
            {

               check_change checkchange{ *this, change };

               for (auto & checkchanged : m_checkchangedsignal.m_functiona)
               {

                  checkchanged(checkchange);

               }

            }

         };

      m_ppropertycontainer->property_changed() += m_propertychanged;

   }


   //bool check_handler::on_check_will_change(::user::check_change & checkchange)
   //{

   //   for (auto & checkwillchange : m_checkwillchangea)
   //   {

   //      if (!checkwillchange(checkchange))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void check_handler::on_check_changed(::user::check_change & checkchange)
   //{

   //   for (auto & checkchanged : m_checkchangeda)
   //   {

   //      checkchanged(checkchange);

   //   }

   //}


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


   //void check::toggle_check(const ::action_context & context)
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


   bool check_handler::operator == (const ::data::check_property & checkproperty) const
   {

      return ::data::check_property::operator == (checkproperty);

   }


   bool check_handler::operator == (const ::data::check_change & change) const
   {

      return this->operator == (change.m_checkproperty);

   }


} // namespace data




