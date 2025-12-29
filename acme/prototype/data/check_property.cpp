#include "framework.h"
#include "check_property.h"
#include "acme/prototype/data/property_container.h"


namespace data
{


   check_property::check_property(::data::property_container * ppropertycontainer, const ::atom & atom) :
      property(ppropertycontainer, atom)
   {
   }


   check_property::check_property(const ::data::property & property) :
      ::data::property(property)
   {


   }


   check_property::~check_property()
   {

   }


   // ::e_check get_echeck() const;
   // virtual bool get_bcheck() const;
   ::e_check check_property::echeck() const
   {

      return this->get_property().as_echeck();

   }

   
   bool check_property::is_checked() const
   {

      return this->get_property().as_bool();

   }

   //bool check_property::is_checked() const
   //{

   //   return this->bcheck();

   //}

   bool check_property::set(::e_check echeck, const ::action_context & actioncontext)
   {

      return this->set_property(echeck, actioncontext);

   }
   /*
   check_property::check_property(::property_container * ppropertycontainer, const ::atom & atom) :
   property_link(ppropertycontainer, atom)
   {

   }


   check_property::check_property(const check_property & checkproperty) :
   check_property(checkproperty.m_ppropertycontainer, checkproperty.id())
   {


      }



   check_property::~check_property()
   {


   }

   //
   //   void check_property::set_check(bool bChecked, const ::action_context & context)
   //   {
   //
   //      set_check((::enum_check) (bChecked ? ::e_check_checked : ::e_check_unchecked),context);
   //
   //   }
   //
   //
   //   //::e_check check_property::get_echeck() const
   //   //{
   //
   //   //   return this->echeck();
   //
   //   //}
   //
   //
   //   //bool check_property::get_bcheck() const
   //   //{
   //
   //   //   return this->bcheck();
   //
   //   //}
   //
   //
   //   ::e_check check_property::echeck() const
   //   {
   //
   //      return get_property().as_echeck();
   //
   //   }
   //
   //
   //   bool check_property::bcheck() const
   //   {
   //
   //      return this->echeck() != e_check_unchecked;
   //
   //   }
   //
   //
   //   bool check_property::is_checked() const
   //   {
   //
   //      return this->bcheck();
   //
   //   }
   //
   //
   //   bool check_property::set_check(::e_check echeck, const ::action_context & actioncontext)
   //   {
   //
   //      return set_property(echeck, actioncontext);
   //
   //      // if (!m_linkedpropertyCheck)
   //      // {
   //      //
   //      //    return;
   //      //
   //      // }
   //      //
   //      // if(echeck != this->get_echeck())
   //      // {
   //      //
   //      //    *m_linkedpropertyCheck = echeck;
   //      //
   //      //    if (context.is_user_source())
   //      //    {
   //      //
   //      //       if (m_callbackOnCheck)
   //      //       {
   //      //
   //      //          m_callbackOnCheck(this);
   //      //
   //      //       }
   //      //
   //      //    }
   //      //
   //      //    m_linkedpropertyCheck.notify_property_changed(context);
   //      //
   //      // }
   //
   //   }
   //
   //
   //   bool check_property::toggle_check(const ::action_context & context)
   //   {
   //
   //      if(bcheck())
   //      {
   //
   //         return set_check(::e_check_unchecked, context);
   //
   //      }
   //      else
   //      {
   //
   //         return set_check(::e_check_checked, context);
   //
   //      }
   //
   //   }
   //
   //
   //   bool check_property::on_check_will_change(::e_check echeck, const action_context & actioncontext)
   //   {
   //
   //      return true;
   //
   //   }
   //
   //
   //   void check_property::on_check_changed(::e_check echeck, const action_context & actioncontext)
   //   {
   //
   //
   //
   //   }
   //
   //
   //   bool check_property::on_property_will_change(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
   //   {
   //
   //      if(atom == id())
   //      {
   //
   //         if(!on_check_will_change(atom, payload.as_echeck(), actioncontext))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   void check_property::on_property_changed(const ::atom & atom, const ::payload & payload, const ::action_context & actioncontext)
   //   {
   //
   //      if(atom == id())
   //      {
   //
   //         on_check_changed(payload.as_echeck(), actioncontext);
   //
   //      }
   //
   //   }
   //
   //
   //} // namespace user
   //
   //
   //
   //*/



   bool check_property::toggle(const ::action_context & context)
   {

      if (is_checked())
      {

         return set(::e_check_unchecked, context);

      }
      else
      {

         return set(::e_check_checked, context);

      }

   }


   bool check_property::operator == (const check_property & checkproperty) const
   {

      return ::data::property::operator==(checkproperty);

   }

   //check_property::check_property(::data::property_container * ppropertycontainer, const ::atom & atom) :
   //   ::data::check_property(ppropertycontainer, atom)
   //{

   //}


   //check_property::~check_property()
   //{

   //}


   ::add_signal_function_to_holder < ::data::check_will_change > check_property::check_will_change(::object * pobjectFunctionHolder)
   {

      return { m_checkwillchangesignal, pobjectFunctionHolder };

   }


   ::add_signal_function_to_holder < ::data::check_changed > check_property::check_changed(::object * pobjectFunctionHolder)
   {

      return { m_checkchangedsignal, pobjectFunctionHolder };

   }


   void check_property::set_check_property(const ::data::check_property & checkproperty)
   {

      unhook_callbacks();

      initialize_data_property(checkproperty);

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

      if (!m_propertywillchange)
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

      }

      m_ppropertycontainer->property_will_change() += m_propertywillchange;


      if (!m_propertychanged)
      {

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

      }

      m_ppropertycontainer->property_changed() += m_propertychanged;

   }


   //bool check_property::on_check_will_change(::user::check_change & checkchange)
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


   //void check_property::on_check_changed(::user::check_change & checkchange)
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


   //bool check_property::operator == (const ::data::check_property & checkproperty) const
   //{

   //   return ::data::check_property::operator == (checkproperty);

   //}


   //bool check_property::operator == (const ::data::check_change & change) const
   //{

   //   return this->operator == (change.m_checkproperty);

   //}


} // namespace data


