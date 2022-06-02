//
//  ui_interaction.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//
#pragma once


namespace sandbox_windowing
{


   class host_interaction :
      virtual public ::user::interaction
   {
   public:


      host_interaction();
      ~host_interaction() override;


      ::sandbox_windowing::windowing* windowing();


      void install_message_routing(::channel* pchannel) override;


      void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      
      DECLARE_MESSAGE_HANDLER(on_message_create);


      void post_redraw(bool bAscendants = true) override;
      //virtual bool is_this_visible() override;


      void on_layout(::draw2d::graphics_pointer& pgraphics) override;


   };


} // namespace sandbox_windowing




