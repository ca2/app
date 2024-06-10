// Changed by camilo with 
// property* system on 2024-06-06 21:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/user/user/property.h"
#include "acme/primitive/data/check_property.h"
#include "acme/primitive/data/property_listener.h"


namespace user
{
   
   
   using check_will_change = ::function < bool(::data::check_property & checkproperty, const ::payload &, const ::action_context &) >;

   using check_changed = ::function < void(::data::check_property & checkproperty, const ::payload &, const ::action_context &) >;


   class CLASS_DECL_ACME check_property :
      public ::user::property,
      public ::data::check_property
   {
   public:
      

      ::data::property_will_change                 m_propertywillchange;
      ::data::property_changed                     m_propertychanged;
      ::comparable_array < ::user::check_will_change >     m_checkwillchangea;
      ::comparable_array < ::user::check_changed >         m_checkchangeda;
      void unhook_callbacks();
      void hook_callbacks();


   public:


      check_property(::user::control * pusercontrol, ::data::property_container * ppropertycontainer = nullptr, const ::atom & atom = {});
      ~check_property();


      void set_check_property(const ::data::check_property & checkproperty);

      //check_property & check() { return m_checkproperty; }

      /*
      //virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      //virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      */

      bool on_check_will_change(::data::check_property & checkproperty, const ::payload &, const ::action_context &);
      void on_check_changed(::data::check_property & checkproperty, const ::payload &, const ::action_context &);

      ::comparable_array < ::user::check_will_change > & check_will_change();
      ::comparable_array < ::user::check_changed > & check_changed();


   };


} // namespace user



