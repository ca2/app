//
//  ui_interaction.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//
#pragma once


namespace ios
{


   class host_interaction :
      virtual public ::user::interaction
   {
   public:


      host_interaction();
      virtual ~host_interaction();


      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool is_this_visible() override;


   };


} // namespace universal_windows




