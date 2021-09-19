#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_view :
      virtual public ::user::impact
   {
   public:


      ::image_pointer                     m_pimageMem;
      __composite(::xml::document)        m_pxmldoc;
      ::image_pointer                     m_pimageLogo;
      ::write_text::font_pointer              m_fontTitle;
      ::write_text::font_pointer              m_font;
      ::draw2d::brush_pointer             m_brBkSel;
      ::draw2d::brush_pointer             m_brBkHoverSel;
      ::draw2d::pen_pointer               m_penBkSel;
      ::draw2d::pen_pointer               m_pen;
      string_map < ::image_pointer >      m_pimageMap;
      string_map < ::image_pointer >      m_pimageMapGray;
      int_array                           m_iaPopup;


      menu_view();
      virtual ~menu_view();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

#ifdef _DEBUG

      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }

#endif

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      ::user::document * get_document();

      bool load_xml(::payload varFile);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);

      virtual bool get_item_rect(index i, RECTANGLE_I32 * prectangle);


      virtual void on_hit_test(::item & item) override;


      virtual bool on_click(const ::item & item) override;

      virtual void draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point1, const ::point_i32& point2);
      virtual void draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      virtual void draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point_i32& point1, const ::point_i32& point2);


   };


} // namespace user


