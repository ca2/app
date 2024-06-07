// Changed by camilo with 
// property* system on 2024-06-06 21:19 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"
#include "control.h"
#include "acme/primitive/data/check_property.h"
#include "acme/primitive/data/property_listener.h"


namespace user
{
   
   
   using check_will_change_function = ::function < bool(::check_property & checkproperty, const ::payload &, const ::action_context &) >;

   using check_changed_function = ::function < void(::check_property & checkproperty, const ::payload &, const ::action_context &) >;


   class CLASS_DECL_ACME check_control :
      virtual public ::user::control
   {
   protected:
      check_property                                        m_checkproperty;
   public:
      ::comparable_array < check_will_change_function >     m_checkwillchangea;
      ::comparable_array < check_changed_function >         m_checkchangeda;





      check_control();
      ~check_control() override;


      virtual void set_check_property(const check_property & checkproperty);

      check_property & check() { return m_checkproperty; }

      
      virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);

      virtual bool on_check_will_change(::check_property & checkproperty, const ::payload &, const ::action_context &);
      virtual bool on_check_changed(::check_property & checkproperty, const ::payload &, const ::action_context &);


   };


} // namespace user



