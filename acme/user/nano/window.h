//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/platform/conversation_message.h"
#include "acme/user/user/drag_client.h"
#include "window_interface.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


class CLASS_DECL_ACME nano_window :
   virtual public ::nano_window_interface,
   virtual public ::conversation_message,
   virtual public ::user::drag_client
{
public:


   ::function < void(nano_window *) >     m_functionClose;

   ::pointer<nano_window_implementation> m_pimplementation;
   ::pointer<nano_brush>                 m_pbrushWindow;
   ::pointer<nano_brush>                 m_pbrushText;
   ::pointer<nano_brush>                 m_pbrushHyperlink;
   ::pointer<nano_brush>                 m_pbrushHyperlinkHover;
   ::pointer<nano_pen>                   m_ppenBorder;
   ::pointer<nano_pen>                   m_ppenBorderFocus;
   ::pointer<nano_pen>                   m_ppenNull;
   ::pointer<nano_font>                  m_pfont;
   ::color::color                         m_colorText;
   ::color::color                         m_colorHyperlink;
   ::color::color                         m_colorHyperlinkHover;
   ::color::color                         m_colorFocus;
   ::color::color                         m_colorWindow;
   bool                                   m_bNcActive;

   rectangle_i32                          m_rectangle;

   pointer_array < nano_child >            m_childa;
   ::atom                                 m_atomLeftButtonDown;
   ::atom                                 m_atomLeftButtonUp;
   ::atom                                 m_atomRightButtonDown;
   ::atom                                 m_atomRightButtonUp;
   ::pointer<nano_child>                 m_pchildFocus;
   ::pointer<nano_child>                 m_pchildHover;
   ::pointer<nano_child>                 m_pchildCapture;


   bool                                   m_bCapture;
   bool                                   m_bStartCentered;
   bool                                   m_bArbitraryPositioning;
   int                                    m_iFontSize;
   enum_font                              m_efont;

   bool                                   m_bTopMost;


   pointer_array < nano_button >           m_buttona;


   nano_window();
   ~nano_window() override;


   ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
   void do_asynchronously() override;




   void on_initialize_particle() override;

   void create() override;

   void display() override;

   void message_loop() override;

   void draw(nano_device * pnanodevice) override;

   void on_draw(nano_device * pnanodevice) override;

   void on_char(int iChar) override;

   bool is_active() override;
   void set_active() override;

   void draw_children(nano_device * pnanodevice) override;

   void delete_drawing_objects() override;
   bool get_dark_mode() override;

   void create_drawing_objects() override;
   void update_drawing_objects() override;

   //::nano_child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;
   ::nano_child * on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
   void add_child(nano_child * pchild) override;
   nano_child * get_child_by_id(const ::atom & atom);

   ::atom get_result() override;

   void on_mouse_move(::user::mouse * pmouse) override;
   void on_left_button_down(::user::mouse * pmouse) override;
   void on_left_button_up(::user::mouse * pmouse) override;
   void on_click(const ::atom & atom, ::user::mouse * pmouse) override;
   void on_right_button_down(::user::mouse * pmouse) override;
   void on_right_button_up(::user::mouse * pmouse) override;
   void on_right_click(const ::atom & atom, ::user::mouse * pmouse) override;

   void move_to(const ::point_i32 & point) override;

   // drag_client
   void drag_set_capture() override;
   ::point_i32 on_drag_start(::user::drag * pdrag) override;
   bool drag_shift(::user::drag * pdrag) override;
   bool drag_hover(::user::drag * pdrag) override;
   void drag_release_capture() override;
   void drag_set_cursor(::user::drag * pdrag) override;

   virtual void on_create();

   void destroy() override;

   void redraw() override;

   void get_client_rectangle(::rectangle_i32 & rectangle) override;

   void get_window_rectangle(::rectangle_i32 & rectangle) override;

   void set_capture() override;

   bool has_capture() const override;

   void release_capture() override;

   void set_cursor(enum_cursor ecursor) override;


   void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult);


   void display_temporary_file_with_text(const ::string & str);

   
   ::pointer<nano_device>create_device();

   
   void _run_modal_loop() override;
   
   
   //::atom do_synchronously() override;
   
   
   void handle(::topic* ptopic, ::context* pcontext) override;
   

};


CLASS_DECL_ACME void initialize_nano_window();



