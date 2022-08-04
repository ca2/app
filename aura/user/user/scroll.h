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
      ~horizontal_scroll_base() override;


      virtual scroll_bar* get_horizontal_scroll_bar() override;

      virtual scroll_data* get_horizontal_scroll_data() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void send_xscroll_message(enum_scroll_command ecommand);

      //virtual void GetScrollRect(RECTANGLE_I32 * prectangle);

      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_impactport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool create_horizontal_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_horizontal_scroll_bar();
      //virtual void on_create_horizontal_scroll_bar();
      virtual bool validate_impactport_offset(point_i32 & point) override;
      virtual void scroll_left_line();
      virtual void scroll_right_line();
      virtual void scroll_left_page();
      virtual void scroll_right_page();
      virtual void scroll_horz(int nPos);


      DECLARE_MESSAGE_HANDLER(_001OnHScroll);

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
      ~vertical_scroll_base() override;


      virtual scroll_bar* get_vertical_scroll_bar() override;
      virtual scroll_data* get_vertical_scroll_data() override;


      virtual void send_yscroll_message(enum_scroll_command ecommand);

      void install_message_routing(::channel * pchannel) override;

      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_impactport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual i32 get_wheel_scroll_delta() override;
      virtual bool create_vertical_scroll_bar();
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;
      virtual void defer_create_vertical_scroll_bar();
      //virtual void on_create_vertical_scroll_bar();
      virtual bool validate_impactport_offset(point_i32 & point) override;


      DECLARE_MESSAGE_HANDLER(on_message_vertical_scroll);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_wheel);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);


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


      ::size_f64            m_sizeTotal;


      scroll_base();
      virtual ~scroll_base();


      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_change_impactport_offset(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool validate_impactport_offset(point_i32 & point) override;
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics) override;


      void install_message_routing(::channel * pchannel) override;


      virtual bool GetActiveClientRect(RECTANGLE_I32 * prectangle);


      virtual bool GetFocusRect(RECTANGLE_I32 * prectangle) override;


      virtual ::size_f64 get_total_size() override;


      virtual void set_total_size(const ::size_f64& size) override;
      virtual void set_page_size(const ::size_f64& size) override;


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




inline wparam __scroll_message_wparam(enum_scroll_command ecommand, int iPosition)
{

   return ((((int)ecommand) & 0xffff) | ((iPosition << 16) & 0xffff0000));

}



















