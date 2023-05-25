#pragma once


#include "aura/graphics/draw2d/region.h"


namespace draw2d_cairo
{


   enum enum_mask
   {

      e_mask_fill,
      e_mask_paint,
      e_mask_paint_with_alpha,

   };


} // namespace draw2d_cairo



namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO region :
      virtual public ::draw2d::region
   {
   public:


      cairo_t *                  m_pcairo;
      cairo_surface_t *          m_psurface;
      cairo_region_t *           m_pcairoregion;
      ::rectangle_i32            m_rectangleBoundingBoxInternal;


      region();
      ~region() override;


      virtual bool create(::draw2d::graphics * pgraphics);
      void destroy() override;
      void destroy_os_data() override;


      bool mask_fill(cairo_t * pdc);
      bool mask_paint(cairo_t * pdc);
      bool mask_paint_with_alpha(cairo_t * pdc, double dOpacity);
      bool _mask(cairo_t * pdc, double dOpacity, enum_mask emask);
      bool _mask_combine(cairo_t * pdc);

      bool _fill(cairo_t * pdc);
      bool _path(cairo_t * pdc);
      bool _rect(cairo_t * pdc);
      bool _oval(cairo_t * pdc);
      bool _polygon(cairo_t * pdc);
      bool _poly_polygon(cairo_t * pdc);
      bool _combine(cairo_t * pdc);


      cairo_region_t * create_cairo_region();
      //bool _region(cairo_t * pdc);

      //bool mask(cairo_t * pdc);
      bool clip(cairo_t * pdc);
      //bool clip_rect(cairo_t * pdc);
      //bool clip_oval(cairo_t * pdc);
      //bool clip_polygon(cairo_t * pdc);

      bool is_simple_positive_region();
      bool is_rectangular_shapes_only_region();


   };


} // namespace draw2d_cairo


