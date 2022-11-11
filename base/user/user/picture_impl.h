// From picture.cpp by camilo on 2022-09-04 01:23 <3ThomasBorregaardSorensen!!
#pragma once


//#include "aura/graphics/draw2d/pen.h"
//#include "aura/graphics/draw2d/region.h"
//#include "aura/graphics/image/fastblur.h"
//#include "aura/user/user/drawable.h"
#include "acme/primitive/geometry2d/polygon.h"


namespace user
{


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


      ///virtual void exchange(::stream & stream) override;


   };


} // namespace user



