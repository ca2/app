#pragma once


namespace universal_windows
{


   class directx_interaction :
      virtual public ::user::interaction
   {
   public:


      directx_interaction();
      virtual ~directx_interaction();


      virtual bool is_host_top_level() const override;
      virtual bool is_os_host() const override;


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace universal_windows




