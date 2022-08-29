#pragma once


#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/region.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/user/user/drawable.h"


namespace user
{


   class CLASS_DECL_BASE picture :
      virtual public ::user::drawable
   {
   public:


      class CLASS_DECL_BASE picture_impl :
         virtual public object
      {
      public:


         rectangle_f64                    m_rectangle;
         rectangle_f64                    m_rectangleDrawing;

         rectangle_f64                    m_rectangleRegion;
         rectangle_f64                    m_rectangleRegionDrawing;


         rectangle_f64                    m_rectangleCursor;
         bool                             m_bDrag;
         double                           m_dRotate;
         ::draw2d::region_pointer         m_region;
         rectangle_f64                    m_rectangleBounding;
         polygon_f64                      m_polygon;
         polygon_f64                      m_polygonDrawing;
         point_f64_array                  m_pointaCursor;
         double                           m_dZoom;
         point_f64                        m_pointDrag2;

         bool                             m_bOutline;
         int                              m_iOutlineWidth;
         ::color::hls                     m_hlsOutline;

         bool                             m_bGlowDropShadow;
         int                              m_iGlowDropShadowOffset;
         int                              m_iGlowDropShadowBlur;
         ::color::hls                     m_hlsGlowDropShadow;

         int                              m_iBlur;
         bool                             m_bGrayscale;
         bool                             m_bInvert;
         int                              m_iOpacity; // 0 - 100
         int                              m_iSaturation; // 0 - 200


         picture_impl();
         ~picture_impl() override;

         
         virtual void exchange(::stream & stream) override;


      };


      point_f64_array                  m_pointaCache1;


      __composite(picture_impl)     m_ppictureimpl;


      picture();
      ~picture() override;

      virtual bool enable_picture(bool bEnable = true);
      virtual bool is_picture_enabled() const;

      //using ::aura::drawable::hit_test;
      virtual ::item_pointer hit_test(const ::point_i32 & point);


      virtual ::item_pointer on_hit_test(const ::point_i32 & point);
      //virtual int on_hit_test_cursor(point_f64 point);
      //virtual int on_hit_test( point_i32) const;
      virtual bool intersects_drawing(const polygon_f64 & polygon_i32) const;
      virtual bool intersects_drawing(const ::rectangle_f64 & rectangle) const;

      virtual bool intersects(const ::rectangle_f64 & rectangle) const;

      virtual ::draw2d::region_pointer get_region() const;

      virtual rectangle_f64 drawing_bounds() const;
      virtual point_f64_array & drawing_polygon() const;

      virtual void update_drawing_rect(::size_f64 sizePage, ::size_f64 sizeClient);
      virtual void update_screen_rect(::size_f64 sizePage, ::size_f64 sizeClient);
      virtual void update_region();
      virtual void update_placement();

      virtual void set_drag_point(const ::point_f64 & point_f64);
      virtual ::point_f64 get_drag_point();

      virtual void _transform_point(point_f64 & point) const;
      virtual void _transform_point_drawing(point_f64 & point) const;
      virtual point_f64 _transform(const point_f64 & point) const;
      virtual point_f64 _transform_drawing(const point_f64 & point) const;
      virtual void _rtransform_point(point_f64 & point) const;
      virtual void _rtransform_point_drawing(point_f64 & point) const;
      virtual point_f64 _rtransform(const point_f64 & point) const;
      virtual point_f64 _rtransform_drawing(const point_f64 & point) const;

      virtual void drag_transform_point(point_f64 & point) const;
      virtual void drag_transform_point_drawing(point_f64 & point) const;
      virtual point_f64 drag_transform(const point_f64 & point) const;
      virtual point_f64 drag_transform_drawing(const point_f64 & point) const;
      inline void drag_rtransform_size(size_f64& size) const { drag_rtransform_point((::point_f64 &) size); }
      virtual void drag_rtransform_point(point_f64 & point) const;
      virtual void drag_rtransform_point_drawing(point_f64 & point) const;
      virtual point_f64 drag_rtransform(const point_f64 & point) const;
      virtual point_f64 drag_rtransform_drawing(const point_f64 & point) const;


      virtual void reset_cursor_rect();
      virtual bool is_dragging();
      virtual bool is_valid();
      virtual ::size_f64 get_size();
      virtual ::size_f64 get_request_size();

      virtual ::image_pointer defer_draw_drop_shadow_phase1(rectangle_i32 & rectangleDropShadow, ::draw2d::fastblur & blurDropShadow, ::image_pointer & imageDropShadow, ::image_pointer pimage);
      virtual void defer_draw_drop_shadow_phase2(::draw2d::graphics_pointer & pgraphics, const rectangle_i32 & rectangleDropShadow, ::draw2d::fastblur & blurDropShadow, ::image_pointer & imageDropShadow);

      virtual bool set_text_editable(bool bEditable = true);

      virtual bool is_text_editable() const;

      virtual bool is_text_editor() const;

      
      virtual ::rectangle_f64 get_rect_for_picture2();


      virtual void draw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_impl(::draw2d::graphics_pointer & pgraphics);


      virtual void move_to(point_f64 point, ::size_f64 sizePage, ::size_f64 sizeClient, const ::rectangle_f64 & rectangleMargin);


      virtual void exchange(::stream & stream) override;


   };


} // namespace user



