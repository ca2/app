#pragma once


namespace user
{


   enum enum_style
   {


      StyleLightBlue,
      StyleBlackBorder,
      StyleLightGreen,
      StyleRedOrange,
      StyleDarkRed,
      StyleBlueRedPurple,
      StyleEveningSun,
      StyleTranslucidLightBlue,
      StyleTranslucidLightGreen,
      StyleTranslucidWarmGray,
      StyleTranslucidWarmLiteGray,
      StyleDarkWarmBlue,

   };


   class CLASS_DECL_AURA style_base :
      virtual public object
   {
   public:


      enum_style        m_estyle;


      style_base();
      virtual ~style_base();

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, menu_item * pitem) = 0;
      //virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;
      //virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;
      virtual void set_style(enum_style estyle);

      virtual void set_style(const char * pszStyle);

      virtual void on_style_change();





      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe);
      virtual bool draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rect & rect, ::draw2d::graphics_pointer & pgraphics);

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics);
      //virtual bool on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction) = 0;
      //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,tab * ptab) = 0;
      //virtual bool _001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * ptab) = 0;
      //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::rect & rect,::draw2d::brush_pointer & brushText) = 0;

      //virtual bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) = 0;
      //virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox) = 0;
      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout);



      virtual enum_control_type get_control_type() const;


      virtual ::color get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const;
      virtual bool get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate = ::user::e_state_none) const;
      virtual bool get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate = ::user::e_state_none) const;


   };


} // namespace user



