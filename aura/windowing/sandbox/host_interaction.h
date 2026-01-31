//
//  ui_interaction.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/05/20.
//
#pragma once


#include "acme/windowing/sandbox/host_interaction.h"
#include "aura/user/user/interaction.h"


namespace sandbox_windowing
{


   class host_interaction :
      virtual public ::user::interaction,
      virtual public ::acme::sandbox_windowing::host_interaction
   {
   public:


      host_interaction();
      ~host_interaction() override;

      void on_initialize_particle() override;
      
      void destroy() override;

      ::sandbox_windowing::windowing* windowing();

      void create_window() override;

      void install_message_routing(::channel* pchannel) override;

      void show() override;
      
      void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      
      DECLARE_MESSAGE_HANDLER(on_message_create);


      void post_redraw(bool bAscendants = true) override;

      
      //void this->rectangle(::int_rectangle* lprect) override;


      void on_layout(::draw2d::graphics_pointer& pgraphics) override;
      
      void set_mouse_capture() override;
      bool has_mouse_capture() override;
       
       
      void set_keyboard_focus() override;
      
      
      void hide() override;
      
      
      ::string get_title() override;
      ::int_rectangle get_rectangle() override;
      

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

   };


} // namespace sandbox_windowing




