//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSørensen!!
//
#pragma once



class CLASS_DECL_ACME nano_window :
   virtual public ::nano_window_interface,
   virtual public ::conversation,
   virtual public ::user::drag_move_client
{
public:


   __pointer(nano_window_implementation)  m_pimplementation;
   __pointer(nano_brush)                  m_pbrushWindow;
   __pointer(nano_brush)                  m_pbrushText;
   __pointer(nano_brush)                  m_pbrushHyperlink;
   __pointer(nano_brush)                  m_pbrushHyperlinkHover;
   __pointer(nano_pen)                    m_ppenBorder;
   __pointer(nano_pen)                    m_ppenBorderFocus;
   __pointer(nano_pen)                    m_ppenNull;
   __pointer(nano_font)                   m_pfont;
   ::color::color                         m_colorText;
   ::color::color                         m_colorHyperlink;
   ::color::color                         m_colorHyperlinkHover;
   ::color::color                         m_colorFocus;
   ::color::color                         m_colorWindow;
   string                                 m_strTitle;
   bool                                   m_bNcActive;

   rectangle_i32                          m_rectangle;

   __pointer_array(nano_child)            m_childa;
   ::atom                                 m_atomLeftButtonDown;
   ::atom                                 m_atomLeftButtonUp;
   __pointer(nano_child)                  m_pchildFocus;
   __pointer(nano_child)                  m_pchildHover;
   __pointer(nano_child)                  m_pchildCapture;

   bool                                   m_bCapture;
   bool                                   m_bStartCentered;
   int                                    m_iFontSize;
   enum_font                              m_efont;


   nano_window();
   ~nano_window() override;


   void on_initialize_object() override;

   void create() override;

   void display_synchronously() override;

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

   ::nano_child * hit_test(int x, int y) override;
   void add_child(nano_child * pchild) override;
   nano_child * get_child_by_id(const ::atom & atom);

   ::atom get_result() override;

   void on_mouse_move(int x, int y) override;
   void on_left_button_down(int x, int y) override;
   void on_left_button_up(int x, int y) override;
   void on_click(const ::atom & atom) override;

   void move_to(int x, int y) override;

   virtual void on_create();

   void destroy() override;

   void redraw() override;

   void get_client_rectangle(::rectangle_i32 & rectangle) override;

   void get_window_rectangle(::rectangle_i32 & rectangle) override;

   void set_capture() override;

   bool has_capture() const override;

   void release_capture() override;

   void set_cursor(enum_cursor ecursor) override;

   
   __pointer(nano_device) create_device();


};


CLASS_DECL_ACME void initialize_nano();



