#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



namespace userex
{


   top_toggle_impact::top_toggle_impact()
   {

      m_ptopview = nullptr;

   }


   top_toggle_impact::~top_toggle_impact()
   {


   }


   void top_toggle_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void top_toggle_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   bool top_toggle_impact::keyboard_focus_is_focusable() const
   {

      return ::user::button::keyboard_focus_is_focusable();

   }


} // namespace userex



