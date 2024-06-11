// Changed by camilo with 
// property* system on 2024-06-08 01:58 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/user/user/control.h"
#include "acme/user/user/property.h"
#include "acme/user/user/check_property.h"
#include "acme/primitive/data/property_listener.h"



namespace user
{


   class CLASS_DECL_ACME check :
      public ::user::control
   {
   public:


      //::data::property_will_change                 m_propertywillchange;
      //::data::property_changed                     m_propertychanged;
      //::comparable_array < check_will_change >     m_checkwillchangea;
      //::comparable_array < check_changed >         m_checkchangeda;
      //void unhook_callbacks();
      //void hook_callbacks();

      ::user::check_property   m_checkproperty;


   public:


      check();
      ~check();


      void set_check_property(const ::data::check_property & checkproperty);

      ::user::check_property check_property() const;


      virtual bool on_check_will_change(::data::check_change & checkchange);
      virtual void on_check_changed(::data::check_change & checkchange);

      virtual ::e_check echeck() const;

      virtual bool is_checked() const;

      //bool is_checked() const;


      bool set_check(::e_check echeck, const ::action_context & actioncontext);
      bool toggle_check(const ::action_context & actioncontext);

      add_signal_function_to_holder < ::data::check_will_change > check_will_change(::matter * pmatterFunctionContainer);
      add_signal_function_to_holder < ::data::check_changed > check_changed(::matter * pmatterFunctionContainer);


   };


} // namespace user



