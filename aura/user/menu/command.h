#pragma once


#include "apex/message/command.h"


namespace menu
{



   class CLASS_DECL_AURA command :
      virtual public ::message::command
   {
   public:


      ::menu::item_ptra *     m_pitema;
      ::menu::item *          m_pitemContainer;


      command();


      //void delete_this() override;

      virtual void enable(bool bOn, const ::action_context & action_context) override;
      //virtual void set_check(const ::e_check & echeck, const ::action_context & action_context) override;
      //virtual void set_text(const ::scoped_string & scopedstrText, const ::action_context & action_context) override;
      void on_check_changed(::data::check_change & change) override;

      void on_text_changed(::data::text_change & change) override;


      //virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      //virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);

   };


} // namespace user



