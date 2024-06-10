#pragma once


#include "apex/message/command.h"
#include "acme/user/user/check.h"
#include "acme/user/user/text.h"
#include "apex/message/channel.h"


namespace user
{

   
   class menu_item_ptra;
   class menu_item;


   class CLASS_DECL_AURA menu_command :
      virtual public ::message::command,
      virtual public ::data::property_container,      
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      menu_item_ptra *     m_pitema;
      menu_item *          m_pitemContainer;


      menu_command();


      //void delete_this() override;

      virtual void enable(bool bOn, const ::action_context & action_context) override;
      //virtual void set_check(const ::e_check & echeck, const ::action_context & action_context) override;
      //virtual void set_text(const string & pszText, const ::action_context & action_context) override;
      void on_check_changed(::data::check_property & checkproperty, const ::payload & payload, const ::action_context & actioncontext) override;

      void on_text_changed(::data::text_property & textproperty, const ::payload &, const ::action_context &) override;


      //virtual bool on_property_will_change(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);
      //virtual void on_property_changed(property_container * pcontainer, const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext);

   };


} // namespace user



