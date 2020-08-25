#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_BASE scroll_data
   {
   public:


      LONG        m_iPage;
      LONG        m_iLine;
      bool        m_bScroll;
      i32     m_iWidth;
      bool        m_bScrollEnable;


   };


   class CLASS_DECL_BASE scroll_x :
      virtual public interaction
   {
   public:


      __pointer(scroll_bar)    m_pscrollbarHorz;
      scroll_data       m_scrolldataHorz;


      scroll_x();
      virtual ~scroll_x();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void send_xscroll_message(int nSBCode);

      //virtual void GetScrollRect(RECT * prect);

      virtual void on_change_view_size() override;
      virtual void on_change_viewport_offset() override;
      virtual void create_x_scroll_bar(const ::rect & rect);
      virtual void layout_scroll_bar() override;
      virtual void _001DeferCreateXScrollBar();
      virtual void _001OnDeferCreateXScrollBar();
      virtual bool validate_viewport_offset(point & point) override;
      virtual void scroll_left_line();
      virtual void scroll_right_line();
      virtual void scroll_left_page();
      virtual void scroll_right_page();
      virtual void scroll_horz(int nPos);


      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual int get_final_x_scroll_bar_width() override;

   };























   class CLASS_DECL_BASE scroll_y :
      virtual public interaction
   {
   public:

      //int                  m_iVScrollOffset;
      __pointer(scroll_bar)       m_pscrollbarVert;
      scroll_data          m_scrolldataVert;
      i16              m_iWheelDelta;
      i16              m_iWheelDeltaScroll;


      scroll_y();
      virtual ~scroll_y();


      virtual void send_yscroll_message(int nSBCode);

      virtual void install_message_routing(::channel * pchannel) override;


      //virtual void GetScrollRect(RECT * prect);

      virtual void on_change_view_size() override;
      virtual void on_change_viewport_offset() override;
      virtual i32 get_wheel_scroll_delta();
      virtual void create_y_scroll_bar(const ::rect & rect);
      virtual void layout_scroll_bar() override;
      virtual void _001DeferCreateYScrollBar();
      virtual void _001OnDeferCreateYScrollBar();
      virtual bool validate_viewport_offset(point & point) override;


      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);


      virtual int get_final_y_scroll_bar_width() override;

      virtual void scroll_up_line();
      virtual void scroll_down_line();
      virtual void scroll_up_page();
      virtual void scroll_down_page();
      virtual void scroll_vert(int nPos);


   };

   class CLASS_DECL_BASE scroll :
      virtual public ::user::scroll_x,
      virtual public ::user::scroll_y
   {
   public:


      ::size            m_sizeTotal;


      scroll();
      scroll(::object * pobject);
      virtual ~scroll();



      virtual void on_change_view_size() override;
      virtual void on_change_viewport_offset() override;
      virtual bool validate_viewport_offset(point & point) override;
      void layout_scroll_bar() override;

      virtual void install_message_routing(::channel * pchannel) override;

      //void GetScrollRect(RECT * prect);


      //virtual bool get_client_rect(RECT * prect) override;


      virtual bool GetActiveClientRect(RECT * prect);


      virtual bool GetFocusRect(RECT * prect);



      virtual ::size get_total_size() override;


      virtual ::estatus set_total_size(const ::sized& size) override;
      virtual ::estatus set_page_size(const ::sized& size) override;


      virtual void defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace user
























