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
      ::draw2d::font_pointer              m_fontTitle;
      ::draw2d::font_pointer              m_font;
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

#ifdef DEBUG

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

#endif

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_apply(::subject * paction) override;

      ::user::document * get_document();

      bool load_xml(payload varFile);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      //DECL_GEN_SIGNAL(_001OnMouseMove);
      //DECL_GEN_SIGNAL(_001OnMouseLeave);
      //DECL_GEN_SIGNAL(_001OnLButtonDown);

      virtual bool get_item_rect(index i, RECT32 * prect);


      virtual void on_hit_test(::user::item & item) override;


      virtual bool on_click(const ::user::item & item) override;

      virtual void draw_border_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_header_separator(::draw2d::graphics_pointer & pgraphics, const ::point & point1, const ::point& point2);
      virtual void draw_header_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_item_rectangle(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_item_rectangle_hover001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_item_rectangle_sel001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_item_rectangle_hover_sel001(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      virtual void draw_item_separator(::draw2d::graphics_pointer & pgraphics, const ::point& point1, const ::point& point2);


   };


} // namespace user


