#include "framework.h"
#include "check.h"
#include "acme/primitive/data/property_container.h"
#include "acme/primitive/primitive/action_context.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
//#endif


namespace user
{


   check::check() :
      m_checkproperty(this, this, ID_CHECK)
   {

   }


   check::~check()
   {

   }


   void check::set_check_property(const ::data::check_property & checkproperty)
   {

      m_checkproperty.set_check_property(checkproperty);

   }


   bool check::on_check_will_change(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
   {

      return true;

   }


   void check::on_check_changed(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext)
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


   function_tracker < check_will_change > check::check_will_change(::matter * pmatterFunctionContainer)
   {

      return { m_checkproperty.check_will_change(), pmatterFunctionContainer };

   }


   function_tracker < check_changed > check::check_changed(::matter * pmatterFunctionContainer)
   {

      return { m_checkproperty.check_changed(), pmatterFunctionContainer };

   }



} // namespace user



