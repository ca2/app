#include "framework.h"
#include "graphics.h"
#include "brush.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/image.h"



namespace draw2d
{


   brush::brush()
   {

      m_ebrush     = e_brush_solid;

   }


   brush::~brush()
   {

   }


//#ifdef WINDOWS
//
//
//   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, unsigned int nUsage)
//   {
//
//      __UNREFERENCED_PARAMETER(hPackedDIB);
//
//      __UNREFERENCED_PARAMETER(nUsage);
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   void brush::destroy()
   {

      if (m_pimage)
      {

         m_pimage.release();

      }

      //return ::success;

   }


//   void brush::dump(dump_context & dumpcontext) const
//   {
//
//      __UNREFERENCED_PARAMETER(dumpcontext);
//
//      throw ::interface_only();
//
//   }


   bool brush::create_null()
   {

      m_color = {};

      m_ebrush     = e_brush_null;

      set_modified();

      return true;

   }


   bool brush::create_solid(::color::color color)
   {

      if(m_ebrush != e_brush_solid || m_color != color)
      {

         m_color     = color;

         m_ebrush     = e_brush_solid;

         set_modified();

      }

      return true;

   }


   bool brush::CreateHatchBrush(int nIndex, ::color::color color)
   {

      __UNREFERENCED_PARAMETER(nIndex);

      __UNREFERENCED_PARAMETER(color);

      throw ::interface_only();

      return false;

   }





//   bool brush::CreateBrushIndirect(const LOGBRUSH* pLogBrush)
//   {
//
//      __UNREFERENCED_PARAMETER(pLogBrush);
//
//      throw ::interface_only();
//
//      return false;
//
//   }


   bool brush::CreatePatternBrush(::image::image *pimage, const ::double_size & size)
   {

      if (m_pimage != pimage || m_ebrush != e_brush_pattern)
      {

         m_pimage = pimage;

         m_size = size;

         m_ebrush = e_brush_pattern;

         set_modified();

      }

      return true;

   }


   bool brush::CreateDIBPatternBrush(const void * pPackedDIB, unsigned int nUsage)
   {

      __UNREFERENCED_PARAMETER(pPackedDIB);

      __UNREFERENCED_PARAMETER(nUsage);

      throw ::interface_only();

      return false;

   }


   bool brush::CreateSysColorBrush(int nIndex)
   {

      __UNREFERENCED_PARAMETER(nIndex);

      throw ::interface_only();

      return false;

   }


//   int brush::GetLogBrush(LOGBRUSH* pLogBrush)
//   {
//
//      __UNREFERENCED_PARAMETER(pLogBrush);
//
//      throw ::interface_only();
//
//      return 0;
//
//   }


   bool brush::CreateLinearGradientBrush(const int_point & point1,const int_point & point2,const ::color::color & color1,const ::color::color & color2)
   {

      return CreateLinearGradientBrush(double_point(point1),double_point(point2),color1,color2);

   }


   bool brush::CreateRadialGradientBrush(const int_point & point1,int_size point2,const ::color::color & color1,const ::color::color & color2)
   {

      return CreateRadialGradientBrush((double_point)point1,(double_size)point2,color1,color2);

   }


   bool brush::CreateLinearGradientBrush(double_point point1, double_point point2, const ::color::color & color1, const ::color::color & color2)
   {

      if (m_ebrush == e_brush_linear_gradient_point_color
            && m_point1 == point1
            && m_point2 == point2
            && m_color1 == color1
            && m_color2 == color2)
         return true;

      m_ebrush           = e_brush_linear_gradient_point_color;
      m_point1          = point1;
      m_point2          = point2;
      m_color1          = color1;
      m_color2          = color2;
      set_modified();

      return true;

   }


   bool brush::CreateRadialGradientBrush(double_point point,double_size s,const ::color::color & color1,const ::color::color & color2)
   {

      if(m_ebrush == e_brush_radial_gradient_color
            && m_point == point
            && m_size == s)
         return true;

      m_ebrush           = e_brush_radial_gradient_color;
      m_point           = point;
      m_size            = s;
      m_color1          = color1;
      m_color2          = color2;
      set_modified();

      return true;

   }


   bool brush::CreateBoxGradientBrush(double_point point, double_size s, double dRadius, const ::color::color & colorInner, const ::color::color & colorOuter)
   {

      if (m_ebrush == e_brush_box_gradient
         && m_point == point
         && m_size == s
         && m_dRadius == dRadius)
         return true;

      m_ebrush = e_brush_box_gradient;
      m_point = point;
      m_size = s;
      m_dRadius = dRadius;
      m_color1 = colorInner;
      m_color2 = colorOuter;
      set_modified();

      return true;

   }


   brush & brush::operator = (const brush & brush)
   {

      m_ebrush           = brush.m_ebrush;
      m_color           = brush.m_color;
      m_point1          = brush.m_point1;
      m_point2          = brush.m_point2;
      m_color1          = brush.m_color1;
      m_color2          = brush.m_color2;
      m_point           = brush.m_point;
      m_size            = brush.m_size;
      m_pimage          = brush.m_pimage;
      m_dRadius         = brush.m_dRadius;
      set_modified();

      return *this;

   }


} // namespace draw2d



