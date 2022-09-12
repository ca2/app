#pragma once


#include "aura/graphics/draw2d/region.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO region :
      virtual public ::draw2d::region
   {
   public:


      cairo_t *                  m_pcairo;
      cairo_surface_t *          m_psurface;
      ::rectangle_i32            m_rectangleBoundingBoxInternal;


      region();
      ~region() override;


      virtual bool create(::draw2d::graphics * pgraphics);
      void destroy() override;
      void destroy_os_data() override;


      bool mask_fill(cairo_t * pdc);
      bool mask_paint(cairo_t * pdc);
      bool mask_paint_with_alpha(cairo_t * pdc, double dOpacity);
      bool _mask(cairo_t * pdc);
      bool _mask(cairo_t * pdc, double dOpacity, enum_mask emask);
      bool mask_rect(cairo_t * pdc);
      bool mask_oval(cairo_t * pdc);
      bool mask_polygon(cairo_t * pdc);
      bool mask_poly_polygon(cairo_t * pdc);
      bool mask_combine(cairo_t * pdc);

      bool clip(cairo_t * pdc);
      //bool clip_rect(cairo_t * pdc);
      //bool clip_oval(cairo_t * pdc);
      //bool clip_polygon(cairo_t * pdc);

      bool is_simple_positive_region();


   };


} // namespace draw2d_cairo


