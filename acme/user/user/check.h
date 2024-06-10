// Changed by camilo with 
// property* system on 2024-06-08 01:58 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/user/user/control.h"
#include "acme/user/user/property.h"
#include "acme/user/user/check_property.h"
#include "acme/primitive/data/property_listener.h"

template < typename FUNCTION >
class function_tracker
{
public:

   ::comparable_array < FUNCTION > *   m_parray;
   ::matter * m_pmatterFunctionHolder;
   function_tracker(::comparable_array < FUNCTION > & array, ::matter * pmatterFunctionHolder) :
      m_parray(&array), m_pmatterFunctionHolder(pmatterFunctionHolder)
   {

   }

   function_tracker & operator += (const FUNCTION & f)
   {

      FUNCTION function = f;

      m_parray->add_item(function);

      auto parray = m_parray;

      m_pmatterFunctionHolder->destroying() += [parray, function]()
         {

            (*parray) -= function;

         };
      return *this;
   }

};
   

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


      virtual bool on_check_will_change(::data::check_property & checkproperty, const ::payload &, const ::action_context &);
      virtual void on_check_changed(::data::check_property & checkproperty, const ::payload &, const ::action_context &);

      virtual ::e_check echeck() const;

      virtual bool bcheck() const;

      //bool is_checked() const;


      bool set_check(::e_check echeck, const ::action_context & actioncontext);
      bool toggle_check(const ::action_context & actioncontext);

      function_tracker < check_will_change > check_will_change(::matter * pmatterFunctionContainer = nullptr);
      function_tracker < check_changed > check_changed(::matter * pmatterFunctionContainer = nullptr);


   };


} // namespace user



