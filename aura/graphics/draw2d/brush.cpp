#include "framework.h"


namespace draw2d
{


   brush::brush()
   {

      m_etype     = type_solid;

   }


   brush::~brush()
   {

   }


#ifdef WINDOWS


   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage)
   {

      UNREFERENCED_PARAMETER(hPackedDIB);

      UNREFERENCED_PARAMETER(nUsage);

      ::exception::throw_interface_only();

      return false;

   }


#endif


   void brush::finalize()
   {

      if (m_pimage)
      {

         m_pimage.release();

      }

   }


   void brush::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      ::exception::throw_interface_only();

   }


   bool brush::create_null()
   {

      m_color.set_argb(0);

      m_etype     = e_type_null;

      set_modified();

      return true;

   }


   bool brush::create_solid(color color)
   {

      if(m_etype != type_solid || m_color != color)
      {

         m_color     = color;

         m_etype     = type_solid;

         set_modified();

      }

      return true;

   }


   bool brush::CreateHatchBrush(i32 nIndex, color color)
   {

      UNREFERENCED_PARAMETER(nIndex);

      UNREFERENCED_PARAMETER(color);

      ::exception::throw_interface_only();

      return false;

   }


//   bool brush::CreateBrushIndirect(const LOGBRUSH* pLogBrush)
//   {
//
//      UNREFERENCED_PARAMETER(pLogBrush);
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }


   bool brush::CreatePatternBrush(::image * pimage)
   {

      if (m_pimage != pimage || m_etype != type_pattern)
      {

         m_pimage = pimage;

         m_etype = type_pattern;

         set_modified();

      }

      return true;

   }


   bool brush::CreateDIBPatternBrush(const void * pPackedDIB, ::u32 nUsage)
   {

      UNREFERENCED_PARAMETER(pPackedDIB);

      UNREFERENCED_PARAMETER(nUsage);

      ::exception::throw_interface_only();

      return false;

   }


   bool brush::CreateSysColorBrush(i32 nIndex)
   {

      UNREFERENCED_PARAMETER(nIndex);

      ::exception::throw_interface_only();

      return false;

   }


//   i32 brush::GetLogBrush(LOGBRUSH* pLogBrush)
//   {
//
//      UNREFERENCED_PARAMETER(pLogBrush);
//
//      ::exception::throw_interface_only();
//
//      return 0;
//
//   }


   bool brush::CreateLinearGradientBrush(const point & point1,const point & point2,const color & color1,const color & color2)
   {

      return CreateLinearGradientBrush(pointd(point1),pointd(point2),color1,color2);

   }


   bool brush::CreateRadialGradientBrush(const point & point1,size point2,const color & color1,const color & color2)
   {

      return CreateRadialGradientBrush((pointd)point1,(sized)point2,color1,color2);

   }


   bool brush::CreateLinearGradientBrush(pointd point1, pointd point2, const color & color1, const color & color2)
   {

      if (m_etype == type_linear_gradient_point_color
            && m_point1 == point1
            && m_point2 == point2
            && m_color1 == color1
            && m_color2 == color2)
         return true;

      m_etype           = type_linear_gradient_point_color;
      m_point1          = point1;
      m_point2          = point2;
      m_color1          = color1;
      m_color2          = color2;
      set_modified();

      return true;

   }


   bool brush::CreateRadialGradientBrush(pointd point,sized s,const color & color1,const color & color2)
   {

      if(m_etype == type_radial_gradient_color
            && m_point == point
            && m_size == s)
         return true;

      m_etype           = type_radial_gradient_color;
      m_point           = point;
      m_size            = s;
      m_color1          = color1;
      m_color2          = color2;
      set_modified();

      return true;

   }


   brush & brush::operator = (const brush & brushSrc)
   {

      m_etype           = brushSrc.m_etype;
      m_color           = brushSrc.m_color;
      m_point1          = brushSrc.m_point1;
      m_point2          = brushSrc.m_point2;
      m_color1          = brushSrc.m_color1;
      m_color2          = brushSrc.m_color2;
      m_point           = brushSrc.m_point;
      m_size            = brushSrc.m_size;
      m_pimage          = brushSrc.m_pimage;
      set_modified();

      return *this;

   }


} // namespace draw2d



