#include "framework.h"
#include "top_toggle_impact.h"


namespace userex
{


   top_toggle_impact::top_toggle_impact()
   {

      m_ptopimpact = nullptr;

      m_bEmptyAreaIsClientArea = true;

   }


   top_toggle_impact::~top_toggle_impact()
   {


   }


   void top_toggle_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void top_toggle_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   bool top_toggle_impact::keyboard_focus_is_focusable()
   {

      return ::user::button::keyboard_focus_is_focusable();

   }


} // namespace userex



