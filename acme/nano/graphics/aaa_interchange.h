//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/conversation_message.h"
#include "acme/user/user/drag_client.h"
#include "acme/user/user/interaction_base.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/user/user/item.h"

namespace nano
{


   namespace user
   {

   
class CLASS_DECL_ACME interchange :
   virtual public ::acme::user::interaction
   //virtual public ::conversation_message
{
public:


   ::function < void(interchange *) >        m_functionClose;

   //::pointer<::micro::window_implementation>     m_pnanouserwindowimplementation;
   ::pointer<::nano::graphics::brush>                     m_pbrushWindow;
   ::pointer<::nano::graphics::brush>                     m_pbrushText;
   ::pointer<::nano::graphics::brush>                     m_pbrushHyperlink;
   ::pointer<::nano::graphics::brush>                     m_pbrushHyperlinkHover;
   ::pointer<::nano::graphics::pen>                       m_ppenBorder;
   ::pointer<::nano::graphics::pen>                       m_ppenBorderFocus;
   ::pointer<::nano::graphics::pen>                       m_ppenNull;
   ::pointer<::nano::graphics::font>                      m_pfont;
   ::color::color                            m_colorText;
   ::color::color                            m_colorHyperlink;
   ::color::color                            m_colorHyperlinkHover;
   ::color::color                            m_colorFocus;
   ::color::color                            m_colorWindow;
   bool                                      m_bNcActive;

   rectangle_i32                             m_rectangle;

   pointer_array < ::micro::child >              m_childa;
   ::atom                                    m_atomLeftButtonDown;
   ::atom                                    m_atomLeftButtonUp;
   ::atom                                    m_atomRightButtonDown;
   ::atom                                    m_atomRightButtonUp;
   ::pointer<::micro::child>                     m_pchildFocus;
   ::pointer<::micro::child>                     m_pchildHover;
   ::pointer<::micro::child>                     m_pchildCapture;


   bool                                      m_bCapture;
   bool                                      m_bStartCentered;
   bool                                      m_bArbitraryPositioning;
   int                                       m_iFontSize;
   enum_font                                 m_efont;

   bool                                      m_bTopMost;


   pointer_array < ::micro::button >             m_nanobuttona;
   ::collection::index                                   m_iDefaultButton = -1;

   //map < const ::item *, ::user::item >      m_useritemmap;


   interchange();
   ~interchange() override;


   ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
   void do_asynchronously() override;


   //virtual ::pointer < item_container > item_form();

   void on_initialize_particle() override;

   void create() override;

   void show_window() override;
    
   void hide() override;

   void message_loop() override;

   void draw(::nano::graphics::device * pnanodevice) override;

   void on_draw(::nano::graphics::device * pnanodevice) override;

   void on_char(int iChar) override;

   bool is_active() override;
   void set_active() override;

   void draw_children(::nano::graphics::device * pnanodevice) override;

   void delete_drawing_objects() override;
   bool get_dark_mode() override;

   void create_drawing_objects() override;
   void update_drawing_objects() override;


   //bool defer_perform_entire_reposition_process() override;

   virtual bool defer_perform_entire_reposition_process(::user::mouse * pmouse);

   virtual bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse);

   ::point_i32 try_absolute_mouse_position(const ::point_i32 & point) override;


   ::point_i32 origin() override;


   //::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;
   virtual ::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder);
   virtual ::micro::child * on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
   virtual void add_child(::micro::child * pchild);
   virtual ::micro::child * get_child_by_id(const ::atom & atom);

   ::payload get_result() override;

   void on_mouse_move(::user::mouse * pmouse) override;
   void on_left_button_down(::user::mouse * pmouse) override;
   void on_left_button_up(::user::mouse * pmouse) override;
   void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
   void on_right_button_down(::user::mouse * pmouse) override;
   void on_right_button_up(::user::mouse * pmouse) override;
   void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

   void set_position(const ::point_i32 & point) override;

   ::rectangle_i32 get_window_rectangle() override;

   void on_create_window() override;

   void destroy() override;

   void redraw() override;

   void get_client_rectangle(::rectangle_i32 & rectangle) override;

   //void get_window_rectangle() override;

   void set_capture() override;

   bool has_capture() override;

   void release_capture() override;

   void set_cursor(enum_cursor ecursor) override;


   void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter);


   void display_temporary_file_with_text(const ::string & str);

   
   ::pointer<::nano::graphics::device>create_device();

   
   void _run_modal_loop() override;
   
   
   //::atom do_synchronously() override;
   
   
   void handle(::topic* ptopic, ::context* pcontext) override;


   //::user::item & user_item(const ::item * pitem) override;
   

};


   } // namespace user


} // namespace nano



