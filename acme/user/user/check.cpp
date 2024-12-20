#include "framework.h"
#include "check.h"
#include "acme/prototype/data/property_container.h"
#include "acme/prototype/prototype/action_context.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
//#endif


namespace user
{


   check::check() :
      m_checkproperty(this, this, id_check)
   {

      m_checkproperty.set_check_property(m_checkproperty);

      m_propertywillchangea += [this](auto & change)
         {

            if (m_checkproperty && change)
            {

               ::data::check_change checkchange{ m_checkproperty, change };

               if (!on_check_will_change(checkchange))
               {

                  return false;

               }

            }

            return true;

         };

      m_propertychangeda += [this](auto & change)
         {

            if (m_checkproperty && change)
            {

               ::data::check_change checkchange{ m_checkproperty, change };

               on_check_changed(checkchange);

            }

            return true;

         };

   }


   check::~check()
   {

   }


   void check::set_check_property(const ::data::check_property & checkproperty)
   {

      m_checkproperty.set_check_property(checkproperty);

   }


   ::user::check_property check::check_property() const
   {

      return m_checkproperty;

   }


   bool check::on_check_will_change(::data::check_change & checkchange)
   {

      return true;

   }


   void check::on_check_changed(::data::check_change & checkchange)
   {


   }


   ::e_check check::echeck() const
   {

      return m_checkproperty.echeck();

   }


   bool check::is_checked() const
   {

      return m_checkproperty.is_checked();

   }


   bool check::set_check(::e_check echeck, const ::action_context & actioncontext)
   {

      return m_checkproperty.set(echeck, actioncontext);

   }


   bool check::toggle_check(const ::action_context & actioncontext)
   {

      return m_checkproperty.toggle(actioncontext);

   }


   add_signal_function_to_holder < ::data::check_will_change > check::check_will_change(::object * pobjectFunctionContainer)
   {

      return m_checkproperty.check_will_change(pobjectFunctionContainer);

   }


   add_signal_function_to_holder < ::data::check_changed > check::check_changed(::object * pobjectFunctionContainer)
   {

      return m_checkproperty.check_changed(pobjectFunctionContainer);

   }



} // namespace user



