#pragma once

//
//#include "aura/user/user/interaction.h"
//
//
//namespace user
//{
//
//
//   class CLASS_DECL_BERG static_control :
//      virtual public ::user::interaction
//   {
//   public:
//
//
//      enum enum_type
//      {
//         type_text,
//         type_icon,
//         type_bitmap,
//         type_cursor,
//      };
//
//
//      union
//      {
//         ::draw2d::bitmap *            m_pbitmap;
//         ::image::icon *              m_picon;
//         ::image::cursor *            m_pcursor;
//      };
//
//
//      enum_type                              m_etype;
//
//      bool                                m_bLButtonDown;
//      bool                                m_bHover;
//
//
//      static_control();
//      virtual ~static_control();
//
//
//      void install_message_routing(::channel * pchannel) override;
//
//
//      //virtual bool create_interaction(::user::interaction * puiParent,atom atom);
//
//
//      virtual ::write_text::font_pointer get_font(style* pstyle, enum_element eelement = e_element_none, ::user::enum_state estate = e_state_none) const override;
//
////#ifdef WINDOWS_DESKTOP
////      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
////      HENHMETAFILE GetEnhMetaFile();
////#endif
//      void static_set_icon(::image::icon * picon);
//      ::image::icon * static_get_icon();
//      void static_set_bitmap(::draw2d::bitmap * pbitmap);
//      ::draw2d::bitmap * static_get_bitmap();
//      void static_set_cursor(::image::cursor * pcursor);
//      ::image::cursor * static_get_cursor();
//
//
//      enum_type get_type();
//
//
//      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
//
//
////      virtual bool OnChildNotify(::user::message * pusermessage) override;
//
//      DECLARE_MESSAGE_HANDLER(on_message_create);
//      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
//      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
//      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
//      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
//
//
//   };
//
//
//} // namespace user
//
//
