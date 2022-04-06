//
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSørensen!!
//
#pragma once



class CLASS_DECL_ACME nano_window :
   virtual public ::nano_window_interface,
   virtual public ::conversation,
   virtual public ::user::drag_client
{
public:


   string                                 m_strMessage;
   //string                                 m_strTitle;
   ::function < void(nano_window *) >     m_functionClose;

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
   ::atom                                 m_atomRightButtonDown;
   ::atom                                 m_atomRightButtonUp;
   __pointer(nano_child)                  m_pchildFocus;
   __pointer(nano_child)                  m_pchildHover;
   __pointer(nano_child)                  m_pchildCapture;

   string                                 m_strDetails;

   bool                                   m_bCapture;
   bool                                   m_bStartCentered;
   bool                                   m_bArbitraryPositioning;
   int                                    m_iFontSize;
   enum_font                              m_efont;

   bool                                   m_bTopMost;


   __pointer_array(nano_button)           m_buttona;


   nano_window();
   ~nano_window() override;


   void on_initialize_object() override;

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

   //::nano_child * hit_test(::user::mouse * pmouse) override;
   ::nano_child * on_hit_test(const ::point_i32 & point) override;
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


   void add_button(const char * pszText, enum_dialog_result edialogresult);


   void display_temporary_file_with_text(const ::string & str);

   
   __pointer(nano_device) create_device();


};


CLASS_DECL_ACME void initialize_nano();



