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


   class CLASS_DECL_BASE picture_impl :
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


      ///virtual void exchange(::stream & stream) override;


   };


} // namespace user



