#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_AURA scroll_data
   {
   public:


      ::i32          m_iPage;
      ::i32          m_iLine;
      bool           m_bScroll;
      i32            m_iWidth;
      bool           m_bScrollEnable;


   };


   class CLASS_DECL_AURA horizontal_scroll_base :
      virtual public interaction
   {
   public:


      __pointer(scroll_bar)      m_pscrollbarHorizontal;
      scroll_data                m_scrolldataHorizontal;


      horizontal_scroll_base();
      virtual ~horizontal_scroll_base();


      virtual scroll_bar* get_horizontal_scroll_bar() override;

      virtual scroll_data* get_horizontal_scroll_data() override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void send_xscroll_message(int nSBCode);

      //virtual void GetScrollRect(RECT32 * prect);

      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool create_horizontal_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_horizontal_scroll_bar();
      //virtual void on_create_horizontal_scroll_bar();
      virtual bool validate_viewport_offset(point & point) override;
      virtual void scroll_left_line();
      virtual void scroll_right_line();
      virtual void scroll_left_page();
      virtual void scroll_right_page();
      virtual void scroll_horz(int nPos);


      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual int get_final_x_scroll_bar_width() override;

   };



   class CLASS_DECL_AURA vertical_scroll_base :
      virtual public interaction
   {
   public:


      __pointer(scroll_bar)         m_pscrollbarVertical;
      scroll_data                   m_scrolldataVertical;
      i16                           m_iWheelDelta;
      i16                           m_iWheelDeltaScroll;


      vertical_scroll_base();
      virtual ~vertical_scroll_base();


      virtual scroll_bar* get_vertical_scroll_bar() override;
      virtual scroll_data* get_vertical_scroll_data() override;


      virtual void send_yscroll_message(int nSBCode);

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual i32 get_wheel_scroll_delta() override;
      virtual bool create_vertical_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_vertical_scroll_bar();
      //virtual void on_create_vertical_scroll_bar();
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


   class CLASS_DECL_AURA scroll_base :
      virtual public ::user::horizontal_scroll_base,
      virtual public ::user::vertical_scroll_base
   {
   public:


      ::sized            m_sizeTotal;


      scroll_base();
      virtual ~scroll_base();


      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool validate_viewport_offset(point & point) override;
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;


      virtual void install_message_routing(::channel * pchannel) override;


      virtual bool GetActiveClientRect(RECT32 * prect);


      virtual bool GetFocusRect(RECT32 * prect) override;


      virtual ::sized get_total_size() override;


      virtual ::e_status set_total_size(const ::sized& size) override;
      virtual ::e_status set_page_size(const ::sized& size) override;


      virtual void defer_draw_scroll_gap(::draw2d::graphics_pointer & pgraphics);


   };


   template < typename BASE >
   class scroll :
      virtual public scroll_base,
      virtual public BASE
   {
   public:


      scroll()
      {
      }

      virtual ~scroll()
      {
      }

      virtual void install_message_routing(::channel* pchannel) override
      {

         ::user::scroll_base::install_message_routing(pchannel);
         BASE::install_message_routing(pchannel);

      }

   };


} // namespace user
























