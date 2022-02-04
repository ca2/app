#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



namespace userex
{


   top_toggle_view::top_toggle_view()
   {

      m_ptopview = nullptr;

   }


   top_toggle_view::~top_toggle_view()
   {


   }


   void top_toggle_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void top_toggle_view::handle(::topic * psubject, ::context * pcontext)
   {

      ::user::impact::handle(psubject, pcontext);

   }


   bool top_toggle_view::keyboard_focus_is_focusable() const
   {

      return ::user::button::keyboard_focus_is_focusable();

   }


} // namespace userex



