#pragma once


#include "core/user/userex/_.h"
#include "aura/user/user/button.h"
#include "berg/user/user/show.h"


namespace userex
{


   class CLASS_DECL_CORE top_toggle_impact :
      virtual public ::user::show < ::user::button >
   {
   public:


      top_impact *           m_ptopimpact;


      top_toggle_impact();
      ~top_toggle_impact() override;


      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual bool keyboard_focus_is_focusable() override;


   };


} // namespace userex




