#pragma once


//#include "core/user/experience/control_box.h"


namespace experience
{


   namespace anthill
   {

class CLASS_DECL_APP_EXPERIENCE_ANTHILL control_box :
   virtual public ::experience::control_box
{
public:


   control_box();
   virtual ~control_box();


   virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   virtual void install_message_routing(::channel * pchannel) override;


   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(on_message_left_button_down);
   DECL_GEN_SIGNAL(on_message_left_button_up);
   void _001OnTimer(::timer * ptimer) override;


};





   } // namespace anthill


} // namespace experience




