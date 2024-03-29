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
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      menu_item_ptra *     m_pitema;
      menu_item *          m_pitemContainer;


      menu_command();


      //void delete_this() override;

      virtual void enable(bool bOn, const ::action_context & action_context) override;
      virtual void _001SetCheck(const ::e_check & echeck, const ::action_context & action_context) override;
      virtual void _001SetText(const string & pszText, const ::action_context & action_context) override;


   };


} // namespace user



