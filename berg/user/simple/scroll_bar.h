#pragma once


#include "acme/prototype/geometry2d/point_array.h"
#include "aura/user/user/scroll_bar.h"


class CLASS_DECL_BERG simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   ::draw2d::pen_pointer            m_ppenDraw;
   ::draw2d::brush_pointer          m_pbrushDraw;
   ::image::image_pointer                  m_pimageDots;
   bool                             m_bTrackOffsetThumbAdjusted;
   i32_point                        m_pointaTrack[::user::e_layout_maximum_count];
   //::status < ::i32_rectangle >     m_statusrectangleTrack;
   //::i32_rectangle                  m_rectangleA;
   //::i32_rectangle                  m_rectangleB;
   //::f64_point                        m_pointaA[4]; // pontos da primeira seta
   //::f64_point                        m_pointaB[4]; // pontos da segunda seta
   ::draw2d::region_pointer         m_pregionA; // regiao da primeira seta
   ::draw2d::region_pointer         m_pregionB; // regiao da segunda seta
   ::u32                            m_uiTimer;
   ::i32                            m_iaScrollBarWidth[::user::e_layout_maximum_count];


   simple_scroll_bar();
   ~simple_scroll_bar() override;


   virtual void pre_translate_message(::message::message * pmessage) override;
   //virtual bool create_interaction(const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName,::u32 uStyle, ::user::interaction * puiParent, const ::atom & atom, ::request * prequest = nullptr) override;

   void install_message_routing(::channel * pchannel) override;

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnVerisimpleDraw(::draw2d::graphics_pointer & pgraphics);

   //void update_drawing_objects() override;

   virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

   //::i32_rectangle get_buttonA_rectangle(const ::i32_rectangle & rectangleX, ::draw2d::graphics_pointer & pgraphics);

   //::i32_rectangle get_buttonB_rectangle(const ::i32_rectangle & rectangleX, ::draw2d::graphics_pointer & pgraphics);

   //::f64_point_array get_arrowA(const ::i32_rectangle & rectangleX, ::draw2d::graphics_pointer & pgraphics);

   //::f64_point_array get_arrowB(const ::i32_rectangle & rectangleX, ::draw2d::graphics_pointer & pgraphics);

   //::status < ::i32_rectangle > get_pageA_rectangle(const ::i32_rectangle & rectangleX, const ::i32_rectangle & rectangleTrack, ::draw2d::graphics_pointer & pgraphics);

   //::status < ::i32_rectangle > get_pageB_rectangle(const ::i32_rectangle & rectangleX, const ::i32_rectangle & rectangleTrack, ::draw2d::graphics_pointer & pgraphics);

   ::f64_rectangle get_buttonA_rectangle(const ::f64_rectangle & rectangle);

   ::f64_rectangle get_buttonB_rectangle(const ::f64_rectangle & rectangle);

   ::f64_point_array get_arrowA(const ::f64_rectangle & rectangle);

   ::f64_point_array get_arrowB(const ::f64_rectangle & rectangle);

   ::status < ::f64_rectangle > get_pageA_rectangle(const ::f64_rectangle & rectangle, const ::f64_rectangle & rectangleTrack);

   ::status < ::f64_rectangle > get_pageB_rectangle(const ::f64_rectangle & rectangle, const ::f64_rectangle & rectangleTrack);


   ::f64_rectangle _user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout) override;


   //virtual void update_rectangles(::draw2d::graphics_pointer & pgraphics);
   virtual void update_rectangles(::user::enum_layout elayout);
   void UpdateBitmaps();
   //void OnDisplayChange(::i32 iBitsPerPixel, ::i32_size sizeScreen);
   //virtual void OnDraw(::image::image *pimage);
   //virtual ::i32 _001GetScrollPos() override;
   //virtual ::i32 _001SetScrollPos(::i32 iPos) override;
   //virtual bool _001GetScrollState(::user::scroll_state * pscrollstate) override;
   //virtual bool set_scroll_state(::user::scroll_state * pscrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch) override;

   bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;
   bool on_drag_start(::i32_point & point, ::user::mouse * pmouse, ::item * pitem) override;
   //virtual bool create_interaction(enum_orientation eorientation, ::u32 uStyle, ::user::interaction * puiParent, ::atom atom) override;

   //::i32 SetTrackingPos(const ::i32_point & point, ::draw2d::graphics_pointer & pgraphics);
   //::i32 GetTrackSize(::i32_size & size, ::draw2d::graphics_pointer & pgraphics);
   //bool GetTrackClientRect(::i32_rectangle * prectangle, ::draw2d::graphics_pointer & pgraphics);

   //::status < ::i32_rectangle > get_track_rectangle(::draw2d::graphics_pointer & pgraphics) override;

   void set_scroll_tracking_position(const ::f64_point & point, ::user::enum_layout elayout = ::user::e_layout_sketch);
   ::f64_size get_track_size(::user::enum_layout elayout = ::user::e_layout_sketch);
   //::f64_rectangle get_track_client_rectangle();

   ::status < ::f64_rectangle > get_track_rectangle(::user::enum_layout elayout) override;

   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
   void operator()(::timer * ptimer) override;
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_show_window);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   //LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);

   void draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics,const ::i32_rectangle & rectangleDraw,const ::i32_rectangle & lpcrectClip,::u8 uchAlpha);

   void draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics,const ::i32_rectangle & rectangleDraw,const ::i32_rectangle & lpcrectClip,::u8 uchAlpha);



   virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   virtual ::item_pointer on_hit_test(const ::i32_point & point, ::user::e_zorder ezorder) override;
   //virtual ::enum_element _001HitTest(const ::i32_point & point, ::collection::index & iItem, ::collection::index & iSubItem, ::collection::index & iListItem) override;

   //virtual bool scrollbar_action(const ::item * pitem, ::draw2d::graphics_pointer & pgraphics);

   virtual bool scrollbar_action(const ::item * pitem, ::user::enum_layout elayout);

   virtual bool scrollbar_lineA(::user::enum_layout elayout);
   virtual bool scrollbar_lineB(::user::enum_layout elayout);
   virtual bool scrollbar_pageB(const ::i32_point & point, ::user::enum_layout elayout);
   virtual bool scrollbar_pageA(const ::i32_point & point, ::user::enum_layout elayout);

   //virtual bool scrollbar_lineA(::draw2d::graphics_pointer & pgraphics);
   //virtual bool scrollbar_lineB(::draw2d::graphics_pointer & pgraphics);
   //virtual bool scrollbar_pageB(const ::i32_point & point, ::draw2d::graphics_pointer & pgraphics);
   //virtual bool scrollbar_pageA(const ::i32_point & point, ::draw2d::graphics_pointer & pgraphics);

   virtual ::color::color scrollbar_color_strong(::user::style * pstyle, const ::e_element & eelement) override;
   virtual ::color::color scrollbar_color(::user::style* pstyle, const ::e_element & eelement)override;
   virtual ::color::color scrollbar_border_color(::user::style* pstyle, const ::e_element & eelement)override;
   virtual ::color::color scrollbar_lite_border_color(::user::style* pstyle, const ::e_element & eelement)override;
   virtual ::color::color scrollbar_draw_color(::user::style* pstyle, const ::e_element & eelement)override;


   ::i32_point drag_point(::item * pitem, ::user::mouse * pmouse) override;


   //::f64 scroll_bar_thickness(::user::enum_layout elayout) override;


};


