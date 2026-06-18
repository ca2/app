// From picture.cpp by camilo on 2022-09-04 01:23 <3ThomasBorregaardSorensen!!
#pragma once


//#include "aura/graphics/draw2d/pen.h"
//#include "aura/graphics/draw2d/region.h"
//#include "aura/graphics/image/fastblur.h"
//#include "aura/user/user/drawable.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/polygon.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace user
{


   class CLASS_DECL_BERG picture_impl :
      virtual public object
   {
   public:


      ::f64_rectangle                    m_rectangle;
      ::f64_rectangle                    m_rectangleDrawing;

      ::f64_rectangle                    m_rectangleRegion;
      ::f64_rectangle                    m_rectangleRegionDrawing;


      ::f64_rectangle                    m_rectangleCursor;
      bool                             m_bDrag;
      ::f64                           m_dRotate;
      ::draw2d::region_pointer         m_region;
      ::f64_rectangle                    m_rectangleBounding;
      f64_polygon                      m_polygon;
      f64_polygon                      m_polygonDrawing;
      f64_point_array                  m_pointaCursor;
      ::f64                           m_dZoom;
      ::f64_point                        m_pointDrag2;

      bool                             m_bOutline;
      ::i32                              m_iOutlineWidth;
      ::color::hls                     m_hlsOutline;

      bool                             m_bGlowDropShadow;
      ::i32                              m_iGlowDropShadowOffset;
      ::i32                              m_iGlowDropShadowBlur;
      ::color::hls                     m_hlsGlowDropShadow;

      ::i32                              m_iBlur;
      bool                             m_bGrayscale;
      bool                             m_bInvert;
      ::i32                              m_iOpacity; // 0 - 100
      ::i32                              m_iSaturation; // 0 - 200


      picture_impl();
      ~picture_impl() override;


      ///virtual void exchange(::stream & stream) override;


   };


} // namespace user



