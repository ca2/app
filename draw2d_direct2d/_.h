#pragma once


#include "aura/_.h"
#include "aura/os/windows_common/graphics.h"
#include "aura/os/windows/d2d1_1.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"






#ifdef _DRAW2D_DIRECT2D_LIBRARY
#define CLASS_DECL_DRAW2D_DIRECT2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_DIRECT2D  CLASS_DECL_IMPORT
#endif


namespace draw2d_direct2d
{

   enum enum_data
   {

      data_bitmap = 0,
      data_bitmap1 = 1,
      data_device_context = 0,
      data_render_target = 1,

   };


} // namespace draw2d_direct2d


namespace d2d1
{


   inline D2D1_RECT_F rectf(const ::rect & rect)
   {

      return D2D1::Rect<FLOAT>(
             (FLOAT)(rect.left),
             (FLOAT)(rect.top),
             (FLOAT)(rect.right),
             (FLOAT)(rect.bottom)
             );

   }


   inline D2D1_POINT_2F Point2F(double x = 0.0, double y = 0.0)
   {

      return Point2F(
             (FLOAT)(x),
             (FLOAT)(y)
             );

   }


} // namespace d2d1

inline void copy(D2D1_POINT_2F* ppointDst, const POINTD* ppointSrc) 
{
   ppointDst->x = (FLOAT) ppointSrc->x;
   ppointDst->y = (FLOAT) ppointSrc->y;
}


namespace draw2d_direct2d
{

   CLASS_DECL_AURA void initialize();

   CLASS_DECL_AURA void finalize();

   class graphics;

   inline void throw_if_failed(HRESULT hr)
   {

      if(FAILED(hr))
         __throw(hresult_exception(hr));
      //if(FAILED(hr))
      // __throw(hr);

   }


} // namespace draw2d_direct2d


#define __graphics(pgraphics) ((::draw2d_direct2d::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_direct2d::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_direct2d::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_direct2d::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_direct2d::path *) ppath->m_pthis)




#include "factory_exchange.h"


#include "object.h"
#include "pen.h"
#include "bitmap.h"
#include "brush.h"
#include "font.h"
#include "palette.h"
#include "region.h"
#include "image.h"
#include "path.h"
//#include "printer.h"


#include "graphics.h"


#define new ACME_NEW


inline D2D1_COLOR_F * copy(D2D1_COLOR_F * pcolorTarget, const ::color * pcolor)
{

   pcolorTarget->a = pcolor->m_iA / 255.0f;
   pcolorTarget->r = pcolor->m_iR / 255.0f;
   pcolorTarget->g = pcolor->m_iG / 255.0f;
   pcolorTarget->b = pcolor->m_iB / 255.0f;

   return pcolorTarget;

}


inline D2D1_COLOR_F * copy(D2D1_COLOR_F * pcolorTarget, const color32_t * pcolor)
{

   pcolorTarget->a = colorref_get_a_value(*pcolor) / 255.0f;
   pcolorTarget->r = colorref_get_r_value(*pcolor) / 255.0f;
   pcolorTarget->g = colorref_get_g_value(*pcolor) / 255.0f;
   pcolorTarget->b = colorref_get_b_value(*pcolor) / 255.0f;

   return pcolorTarget;

}



