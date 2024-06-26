//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/conversation_message.h"
#include "acme/user/user/drag_client.h"
#include "window_interface.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/user/user/item.h"

namespace nano
{


   namespace user
   {

   
class CLASS_DECL_ACME window :
   virtual public ::nano::user::window_interface
   //virtual public ::conversation_message
{
public:


   ::function < void(window *) >        m_functionClose;

   ::pointer<::nano::user::window_implementation>     m_pimplementation;
   ::pointer<::nano::user::brush>                     m_pbrushWindow;
   ::pointer<::nano::user::brush>                     m_pbrushText;
   ::pointer<::nano::user::brush>                     m_pbrushHyperlink;
   ::pointer<::nano::user::brush>                     m_pbrushHyperlinkHover;
   ::pointer<::nano::user::pen>                       m_ppenBorder;
   ::pointer<::nano::user::pen>                       m_ppenBorderFocus;
   ::pointer<::nano::user::pen>                       m_ppenNull;
   ::pointer<::nano::user::font>                      m_pfont;
   ::color::color                            m_colorText;
   ::color::color                            m_colorHyperlink;
   ::color::color                            m_colorHyperlinkHover;
   ::color::color                            m_colorFocus;
   ::color::color                            m_colorWindow;
   bool                                      m_bNcActive;

   rectangle_i32                             m_rectangle;

   pointer_array < ::nano::user::child >              m_childa;
   ::atom                                    m_atomLeftButtonDown;
   ::atom                                    m_atomLeftButtonUp;
   ::atom                                    m_atomRightButtonDown;
   ::atom                                    m_atomRightButtonUp;
   ::pointer<::nano::user::child>                     m_pchildFocus;
   ::pointer<::nano::user::child>                     m_pchildHover;
   ::pointer<::nano::user::child>                     m_pchildCapture;


   bool                                      m_bCapture;
   bool                                      m_bStartCentered;
   bool                                      m_bArbitraryPositioning;
   int                                       m_iFontSize;
   enum_font                                 m_efont;

   bool                                      m_bTopMost;


   pointer_array < ::nano::user::button >             m_nanobuttona;
   ::collection::index                                   m_iDefaultButton = -1;

   //map < const ::item *, ::user::item >      m_useritemmap;


   window();
   ~window() override;


   ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;
   void do_asynchronously() override;


   //virtual ::pointer < item_container > item_form();

   void on_initialize_particle() override;

   void create() override;

   void display() override;
    
   void hide() override;

   void message_loop() override;

   void draw(::nano::user::device * pnanodevice) override;

   void on_draw(::nano::user::device * pnanodevice) override;

   void on_char(int iChar) override;

   bool is_active() override;
   void set_active() override;

   void draw_children(::nano::user::device * pnanodevice) override;

   void delete_drawing_objects() override;
   bool get_dark_mode() override;

   void create_drawing_objects() override;
   void update_drawing_objects() override;


   bool defer_perform_entire_reposition_process() override;


   ::point_i32 try_absolute_mouse_position(const ::point_i32 & point) override;


   ::point_i32 origin() override;


   //::nano::user::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;
   ::nano::user::child * on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
   void add_child(::nano::user::child * pchild) override;
   ::nano::user::child * get_child_by_id(const ::atom & atom);

   ::atom get_result() override;

   void on_mouse_move(::user::mouse * pmouse) override;
   void on_left_button_down(::user::mouse * pmouse) override;
   void on_left_button_up(::user::mouse * pmouse) override;
   void on_click(const ::atom & atom, ::user::mouse * pmouse) override;
   void on_right_button_down(::user::mouse * pmouse) override;
   void on_right_button_up(::user::mouse * pmouse) override;
   void on_right_click(const ::atom & atom, ::user::mouse * pmouse) override;

   void move_to(const ::point_i32 & point) override;


   virtual void on_create();

   void destroy() override;

   void redraw() override;

   void get_client_rectangle(::rectangle_i32 & rectangle) override;

   void get_window_rectangle(::rectangle_i32 & rectangle) override;

   void set_capture() override;

   bool has_capture() const override;

   void release_capture() override;

   void set_cursor(enum_cursor ecursor) override;


   void add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter);


   void display_temporary_file_with_text(const ::string & str);

   
   ::pointer<::nano::user::device>create_device();

   
   void _run_modal_loop() override;
   
   
   //::atom do_synchronously() override;
   
   
   void handle(::topic* ptopic, ::context* pcontext) override;


   //::user::item & user_item(const ::item * pitem) override;
   

};


   } // namespace user


} // namespace nano



