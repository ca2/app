#pragma once


#include "acme/primitive/geometry2d/point_array.h"
#include "aura/user/user/scroll_bar.h"


class CLASS_DECL_BASE simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   ::draw2d::pen_pointer            m_ppenDraw;
   ::draw2d::brush_pointer          m_pbrushDraw;
   ::image_pointer                  m_pimageDots;
   bool                             m_bTrackOffsetThumbAdjusted;
   point_i32                        m_pointTrack;
   ::status < ::rectangle_i32 >     m_statusrectangleTrack;
   //::rectangle_i32                  m_rectangleA;
   //::rectangle_i32                  m_rectangleB;
   //point_f64                        m_pointaA[4]; // pontos da primeira seta
   //point_f64                        m_pointaB[4]; // pontos da segunda seta
   ::draw2d::region_pointer         m_pregionA; // regiao da primeira seta
   ::draw2d::region_pointer         m_pregionB; // regiao da segunda seta
   ::u32                            m_uiTimer;


   simple_scroll_bar();
   ~simple_scroll_bar() override;


   virtual void pre_translate_message(::message::message * pmessage) override;
   //virtual bool create_interaction(const ::string & pszClassName, const ::string & pszWindowName,u32 uStyle, ::user::interaction * puiParent, const ::atom & atom, ::request * prequest = nullptr) override;

   void install_message_routing(::channel * pchannel) override;

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnVerisimpleDraw(::draw2d::graphics_pointer & pgraphics);

   void update_drawing_objects();

   virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

   ::rectangle_i32 get_buttonA_rectangle(const ::rectangle_i32 & rectangleClient, ::draw2d::graphics_pointer & pgraphics);

   ::rectangle_i32 get_buttonB_rectangle(const ::rectangle_i32 & rectangleClient, ::draw2d::graphics_pointer & pgraphics);

   ::point_f64_array get_arrowA(const ::rectangle_i32 & rectangleClient, ::draw2d::graphics_pointer & pgraphics);

   ::point_f64_array get_arrowB(const ::rectangle_i32 & rectangleClient, ::draw2d::graphics_pointer & pgraphics);

   ::status < ::rectangle_i32 > get_pageA_rectangle(const ::rectangle_i32 & rectangleClient, const ::rectangle_i32 & rectangleTrack, ::draw2d::graphics_pointer & pgraphics);

   ::status < ::rectangle_i32 > get_pageB_rectangle(const ::rectangle_i32 & rectangleClient, const ::rectangle_i32 & rectangleTrack, ::draw2d::graphics_pointer & pgraphics);

   void UpdateBitmaps();
   //void OnDisplayChange(i32 iBitsPerPixel, ::size_i32 sizeScreen);
   //virtual void OnDraw(::image * pimage);
   virtual i32 _001GetScrollPos() override;
   virtual i32 _001SetScrollPos(i32 iPos) override;
   virtual bool _001GetScrollInfo(::user::scroll_info * psi) override;
   virtual bool _001SetScrollInfo(::user::scroll_info * psi, bool bRedraw = true) override;

   //virtual bool create_interaction(enum_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::atom atom) override;

   i32 SetTrackingPos(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics);
   i32 GetTrackSize(::size_i32 & size, ::draw2d::graphics_pointer & pgraphics);
   bool GetTrackClientRect(::rectangle_i32 * prectangle, ::draw2d::graphics_pointer & pgraphics);

   ::status < ::rectangle_i32 > get_track_rectangle(::draw2d::graphics_pointer & pgraphics) override;

   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(_001OnHScroll);
   void _001OnTimer(::timer * ptimer) override;
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_show_window);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   //LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);

   void draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleDraw,const ::rectangle_i32 & lpcrectClip,::u8 uchAlpha);

   void draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleDraw,const ::rectangle_i32 & lpcrectClip,::u8 uchAlpha);



   virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   virtual ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
   //virtual ::enum_element _001HitTest(const ::point_i32 & point, index & iItem, index & iSubItem, index & iListItem) override;

   virtual bool scrollbar_action(const ::item * pitem, ::draw2d::graphics_pointer & pgraphics);

   virtual bool scrollbar_lineA(::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_lineB(::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_pageB(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_pageA(const ::point_i32 & point, ::draw2d::graphics_pointer & pgraphics);

   virtual ::color::color scrollbar_color_strong(::user::style * pstyle, ::enum_element eelement) override;
   virtual ::color::color scrollbar_color(::user::style* pstyle, ::enum_element eelement)override;
   virtual ::color::color scrollbar_border_color(::user::style* pstyle, ::enum_element eelement)override;
   virtual ::color::color scrollbar_lite_border_color(::user::style* pstyle, ::enum_element eelement)override;
   virtual ::color::color scrollbar_draw_color(::user::style* pstyle, ::enum_element eelement)override;


};


