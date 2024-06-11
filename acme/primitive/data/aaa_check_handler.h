// Created by camilo on 2024-06-10 21:55 <3ThomasBorregaardSorensen!! ThomasLikesNumber5!!
#pragma once


#include "acme/primitive/data/check_property.h"
#include "acme/primitive/primitive/signal.h"


namespace data
{



   class CLASS_DECL_ACME check_handler :
      public ::data::check_property
   {
   public:


      ::data::property_will_change              m_propertywillchange;
      ::data::property_changed                  m_propertychanged;
      ::signal < ::data::check_will_change >    m_checkwillchangesignal;
      ::signal < ::data::check_changed >        m_checkchangedsignal;


      void unhook_callbacks();
      void hook_callbacks();


   public:


      check_handler(::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      ~check_handler();


      void set_check_property(const ::data::check_property & checkproperty);

      //check_property & check() { return m_checkproperty; }

      /*
      //virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      //virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */

      bool on_check_will_change(check_change & checkchange);
      void on_check_changed(check_change & checkchange);

      add_signal_function_to_holder < check_will_change > check_will_change(::matter * pmatterFunctionHolder);
      add_signal_function_to_holder < check_changed > check_changed(::matter * pmatterFunctionHolder);


      bool operator == (const check_property & checkproperty) const;
      bool operator == (const check_change & change) const;


   };


} // namespace data



