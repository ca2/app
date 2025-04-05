//
//  ui_interaction.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/05/20.
// as acme::sandbox_windowing on 2024-11-25 23:25 by
// camilo <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/user/micro/main_window.h"


namespace acme
{

namespace sandbox_windowing
{


class CLASS_DECL_ACME host_interaction :
virtual public ::micro::main_window
{
public:
   
   
   ::pointer < ::micro::button > m_pbuttonContext;

   host_interaction();
   ~host_interaction() override;
   
   
   ::acme::sandbox_windowing::windowing* windowing();
   
   virtual void create_context_button();

   //void install_message_routing(::channel* pchannel) override;
   
   
//   void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
//   void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
//   void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
//   void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
//   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   
   
   //DECLARE_MESSAGE_HANDLER(on_message_create);
   
   
   void post_redraw(bool bAscendants = true) override;
   
   
   //void this->rectangle(::int_rectangle* lprect) override;
   
   
   //void on_layout(::draw2d::graphics_pointer& pgraphics) override;
   //void create_window() override;
   void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
   
   void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


};


} // namespace sandbox_windowing


} // namespace acme

