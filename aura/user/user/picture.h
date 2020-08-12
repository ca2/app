#pragma once


namespace user
{


   class CLASS_DECL_AURA picture :
      virtual public ::aura::drawable
   {
   public:


      class CLASS_DECL_AURA picture_impl :
         virtual public context_object
      {
      public:

         rectd                   m_rect;
         rectd                   m_rectDrawing;

         rectd                   m_rectRegion;
         rectd                   m_rectRegionDrawing;


         rectd                   m_rectCursor;
         bool                    m_bDrag;
         double                  m_dRotate;
         ::draw2d::region_pointer     m_region;
         rectd                   m_rectBounding;
         polygond                m_polygon;
         polygond                m_polygonDrawing;
         pointd_array            m_ptaCursor;
         double                  m_dZoom;
         pointd                  m_pointDrag2;

         bool                    m_bOutline;
         int                     m_iOutlineWidth;
         ::hls                   m_hlsOutline;

         bool                    m_bGlowDropShadow;
         int                     m_iGlowDropShadowOffset;
         int                     m_iGlowDropShadowBlur;
         ::hls                   m_hlsGlowDropShadow;

         int                     m_iBlur;
         bool                    m_bGrayscale;
         bool                    m_bInvert;
         int                     m_iOpacity; // 0 - 100
         int                     m_iSaturation; // 0 - 200


         picture_impl();
         virtual ~picture_impl();

         
         virtual void exchange(::stream & stream) override;


      };


      pointd_array                  m_ptaCache1;


      __composite(picture_impl)     m_ppictureimpl;


      picture();
      virtual ~picture();

      virtual bool enable_picture(bool bEnable = true);
      virtual bool is_picture_enabled() const;

      using ::aura::drawable::hit_test;
      virtual void hit_test(::user::item & item, const ::point & point) override;


      virtual void on_hit_test(::user::item & item) override;
      //virtual int on_hit_test_cursor(pointd point);
      //virtual int on_hit_test( point) const;
      virtual bool intersects_drawing(const polygond & polygon) const;
      virtual bool intersects_drawing(const ::rectd & rect) const;

      virtual bool intersects(const ::rectd & rect) const;

      virtual ::draw2d::region_pointer get_region() const;

      virtual rectd drawing_bounds() const;
      virtual pointd_array & drawing_polygon() const;

      virtual void update_drawing_rect(::sized sizePage, ::sized sizeClient);
      virtual void update_screen_rect(::sized sizePage, ::sized sizeClient);
      virtual void update_region();
      virtual void update_placement();

      virtual void set_drag_point(const ::pointd & pointd);
      virtual ::pointd get_drag_point();

      virtual void _transform_point(pointd & point) const;
      virtual void _transform_point_drawing(pointd & point) const;
      virtual pointd _transform(const pointd & point) const;
      virtual pointd _transform_drawing(const pointd & point) const;
      virtual void _rtransform_point(pointd & point) const;
      virtual void _rtransform_point_drawing(pointd & point) const;
      virtual pointd _rtransform(const pointd & point) const;
      virtual pointd _rtransform_drawing(const pointd & point) const;

      virtual void drag_transform_point(pointd & point) const;
      virtual void drag_transform_point_drawing(pointd & point) const;
      virtual pointd drag_transform(const pointd & point) const;
      virtual pointd drag_transform_drawing(const pointd & point) const;
      inline void drag_rtransform_size(sized& size) const { drag_rtransform_point((::pointd &) size); }
      virtual void drag_rtransform_point(pointd & point) const;
      virtual void drag_rtransform_point_drawing(pointd & point) const;
      virtual pointd drag_rtransform(const pointd & point) const;
      virtual pointd drag_rtransform_drawing(const pointd & point) const;


      virtual void reset_cursor_rect();
      virtual bool is_dragging();
      virtual bool is_valid();
      virtual ::sized get_size();
      virtual ::sized get_request_size();

      virtual ::image_pointer defer_draw_drop_shadow_phase1(rect & rectDropShadow, ::draw2d::fastblur & blurDropShadow, ::image_pointer & imageDropShadow, ::image_pointer pimage);
      virtual void defer_draw_drop_shadow_phase2(::draw2d::graphics_pointer & pgraphics, const rect & rectDropShadow, ::draw2d::fastblur & blurDropShadow, ::image_pointer & imageDropShadow);

      virtual bool set_text_editable(bool bEditable = true);

      virtual bool is_text_editable();

      virtual bool is_text_editor();

      
      virtual ::rectd get_rect_for_picture2();


      virtual void draw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_impl(::draw2d::graphics_pointer & pgraphics);


      virtual void move_to(pointd point, ::sized sizePage, ::sized sizeClient, const ::rectd & rectMargin);


      virtual void exchange(::stream & stream) override;


   };


} // namespace user



