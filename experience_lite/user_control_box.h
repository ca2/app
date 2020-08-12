#pragma once


class CLASS_DECL_APP_EXPERIENCE_LITE MetaControlBox :
   virtual public ::experience::control_box
{
public:


   MetaControlBox(::object * pobject);
   virtual ~MetaControlBox();


   virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   virtual void install_message_routing(::channel * pchannel) override;


   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   void _001OnTimer(::timer * ptimer) override;


};



