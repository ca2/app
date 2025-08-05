#pragma once


#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/region.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/user/user/drawable.h"
#include "acme/graphics/draw2d/_binary_stream.h"


namespace user
{


   class CLASS_DECL_BERG picture :
      virtual public ::user::drawable
   {
   public:


      class CLASS_DECL_BERG picture_impl :
         virtual public object
      {
      public:


         double_rectangle                    m_rectangle;
         double_rectangle                    m_rectangleDrawing;

         double_rectangle                    m_rectangleRegion;
         double_rectangle                    m_rectangleRegionDrawing;


         double_rectangle                    m_rectangleCursor;
         bool                             m_bDrag;
         double                           m_dRotate;
         ::draw2d::region_pointer         m_region;
         double_rectangle                    m_rectangleBounding;
         double_polygon                      m_polygon;
         double_polygon                      m_polygonDrawing;
         double_point_array                  m_pointaCursor;
         double                           m_dZoom;
         double_point                        m_pointDrag2;

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

         
         //virtual void exchange(::stream & stream) override;

         void read_from_stream(::binary_stream & binarystream) override;
         void write_to_stream(::binary_stream & binarystream) override;



      };


      double_point_array                  m_pointaCache1;


      ::pointer<picture_impl>    m_ppictureimpl;


      picture();
      ~picture() override;

      virtual bool enable_picture(bool bEnable = true);
      virtual bool is_picture_enabled() const;

      
      virtual ::double_point get_point_transform();


      virtual bool is_picture_hover();


      using ::user::drawable::parent_client_hit_test;
      ::item_pointer parent_client_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;


      ::item_pointer parent_client_on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;
      //virtual int on_hit_test_cursor(double_point point);
      //virtual int on_hit_test( int_point) const;
      virtual bool intersects_drawing(const double_polygon & int_polygon) const;
      virtual bool intersects_drawing(const ::double_rectangle & rectangle) const;

      virtual bool intersects(const ::double_rectangle & rectangle) const;

      virtual ::draw2d::region_pointer get_region() const;

      virtual double_rectangle drawing_bounds() const;
      virtual double_point_array & drawing_polygon() const;

      virtual void update_drawing_rect(::double_size sizePage, ::double_size sizeClient);
      virtual void update_screen_rect(::double_size sizePage, ::double_size sizeClient);
      virtual void update_region();
      virtual void update_placement();

      virtual void set_drag_point(const ::double_point & double_point);
      virtual ::double_point get_drag_point();

      virtual void _transform_sequence(sequence2_double & sequence) const;
      virtual void _transform_sequence_drawing(sequence2_double & sequence) const;
      template < typename T >
      inline T _transform(const T & t) const
      {
         auto tTransform = t;
         _transform_sequence(tTransform);
         return tTransform;
      }
      template < typename T >
      inline T _transform_drawing(const T & t) const
      {
         auto tTransform = t;
         _transform_sequence(tTransform);
         return tTransform;
      }
      virtual void _rtransform_sequence(sequence2_double & sequence) const;
      virtual void _rtransform_sequence_drawing(sequence2_double & sequence) const;
      template < typename T >
      inline T _rtransform(const T & t) const
      {
         auto tTransform = t;
         _rtransform_sequence(tTransform);
         return tTransform;
      }
      template < typename T >
      inline T _rtransform_drawing(const T & t) const
      {
         auto tTransform = t;
         _rtransform_sequence(tTransform);
         return tTransform;
      }

      virtual void drag_transform_sequence(sequence2_double & sequence) const;
      virtual void drag_transform_sequence_drawing(sequence2_double & sequence) const;
      template < typename T >
      inline T drag_transform(const T & t) const
      {
         auto tTransform = t;
         drag_transform_sequence(tTransform);
         return tTransform;
      }
      template < typename T >
      inline T drag_transform_drawing(const T & t) const
      {
         auto tTransform = t;
         drag_transform_sequence(tTransform);
         return tTransform;
      }
      //inline void drag_rtransform_size(double_size& size) const { drag_rtransform_point((::double_point &) size); }
      virtual void drag_rtransform_sequence(sequence2_double & sequence) const;
      virtual void drag_rtransform_sequence_drawing(sequence2_double & sequence) const;
      template < typename T >
      inline T drag_rtransform(const T & t) const
      {
         auto tTransform = t;
         drag_rtransform_sequence(tTransform);
         return tTransform;
      }
      template < typename T >
      inline T drag_rtransform_drawing(const T & t) const
      {
         auto tTransform = t;
         drag_rtransform_sequence(tTransform);
         return tTransform;
      }


      virtual void reset_cursor_rect();
      virtual bool is_dragging();
      virtual bool is_valid();
      virtual ::double_size get_size();
      virtual ::double_size get_request_size();

      virtual ::image::image_pointer defer_draw_drop_shadow_phase1(int_rectangle & rectangleDropShadow, ::image::fastblur & blurDropShadow, ::image::image_pointer & imageDropShadow, ::image::image_pointer pimage);
      virtual void defer_draw_drop_shadow_phase2(::draw2d::graphics_pointer & pgraphics, const int_rectangle & rectangleDropShadow, ::image::fastblur & blurDropShadow, ::image::image_pointer & imageDropShadow);

      virtual bool set_text_editable(bool bEditable = true);

      virtual bool is_text_editable();

      virtual bool is_text_editor();

      
      virtual ::double_rectangle get_rect_for_picture2();


      virtual void draw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_impl(::draw2d::graphics_pointer & pgraphics);


      virtual void move_to(double_point point, ::double_size sizePage, ::double_size sizeClient, const ::double_rectangle & rectangleMargin);


      void read_from_stream(::binary_stream & stream) override;
      void write_to_stream(::binary_stream & stream) override;


   };


} // namespace user



// template < typename FILE >
binary_stream & operator << (binary_stream & stream, const ::user::picture::picture_impl & t);

// template < typename FILE >
binary_stream & operator >> (binary_stream & stream, ::user::picture::picture_impl & t);

// template < typename FILE >
binary_stream & operator << (binary_stream & stream, const ::user::picture::picture_impl & t);

// template < typename FILE >
binary_stream & operator >> (binary_stream & stream, ::user::picture::picture_impl & t);
