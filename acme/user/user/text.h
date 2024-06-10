// Changed by camilo with 
// property* system on 2024-06-08 02:06 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"
#include "acme/user/user/control.h"
#include "acme/user/user/property.h"
#include "acme/user/user/text_property.h"
#include "acme/primitive/data/property_listener.h"


namespace user
{


   class CLASS_DECL_ACME text :
      public ::user::control
   {
   public:


      //::data::property_will_change                 m_propertywillchange;
      //::data::property_changed                     m_propertychanged;
      //::comparable_array < check_will_change >     m_checkwillchangea;
      //::comparable_array < check_changed >         m_checkchangeda;
      //void unhook_callbacks();
      //void hook_callbacks();

      ::user::text_property   m_textproperty;


   public:


      text();
      ~text() override;


      void set_text_property(const ::data::text_property & textproperty);


      virtual bool on_text_will_change(::data::text_property & textproperty, const ::payload &, const ::action_context &);
      virtual void on_text_changed(::data::text_property & textproperty, const ::payload &, const ::action_context &);


      bool on_property_will_change(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext) override;
      void on_property_changed(::data::property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext) override;

      virtual ::string as_text() const;
      virtual void get_text(::string & str) const;
      virtual strsize get_text_length() const;
      virtual ::string get_selection_text() const;
      virtual void get_selection_text(::string & str) const;
      virtual void set_text_selection(strsize iBegin, strsize iEnd, const ::action_context & actioncontext);
      virtual void set_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext);


   };


} // namespace user



