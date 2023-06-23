#include "framework.h"
#include "_opengl.h"
#include "brush.h"


namespace draw2d_opengl
{


   brush::brush()
   { 

   }


   brush::~brush()
   { 
      //::acme::del(m_pbrush);
   }

   //bool brush::create_solid(color32_t crColor)
   //{

   //   if(m_pbrush != nullptr)
   //   {
   //      delete m_pbrush;
   //   }

   //   m_pbrush = memory_new plusplus::SolidBrush(plusplus::Color(color32_u8_opacity(crColor), color32_u8_red(crColor), color32_u8_green(crColor), color32_u8_blue(crColor)));

   //   return m_pbrush != nullptr;
   //      
   //}

   // bool brush::CreateHatchBrush(i32 nIndex, color32_t crColor)
   // { 
   //    //return attach(::CreateHatchBrush(nIndex, crColor));
   //    return false;
   // }
//    bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
  //  {
       //return attach(::CreateBrushIndirect(lpLogBrush)); 
    //   return false;
    //}
    //bool brush::CreatePatternBrush(::draw2d::bitmap* pBitmap)
    //{ 
    //   //return attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data()));
    //   return false;
    //}
    //bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, ::u32 nUsage)
    //{ 
    //   //return attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
    //   return false;
    //}
    //bool brush::CreateSysColorBrush(i32 nIndex)
    //{ 
    //   //return attach(::GetSysColorBrush(nIndex));
    //   return false;

    //}
/*    i32 brush::GetLogBrush(LOGBRUSH* pLogBrush)
    { 
       //ASSERT(get_os_data() != nullptr);
       //return ::GetObject(get_os_data(), sizeof(LOGBRUSH), pLogBrush); 
       return false;
    }*/


//   void brush::construct(color32_t crColor)
//   {
////      if (!attach(::create_solid(crColor)))
//  //       throw ::exception(error_resource);
//   }
//
//   void brush::construct(i32 nIndex, color32_t crColor)
//   {
//    //  if (!attach(::CreateHatchBrush(nIndex, crColor)))
//      //   throw ::exception(error_resource);
//   }
//
//   void brush::construct(::draw2d::bitmap* pBitmap)
//   {
//      //ASSERT_VALID(pBitmap);
//
//      //if (!attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())))
//        // throw ::exception(error_resource);
//   }
//
//   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage)
//   {
//      //ASSERT(hPackedDIB != nullptr);
//      //const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
//      //ASSERT(lpPackedDIB != nullptr);
//      //bool bResult = attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
//      //::GlobalUnlock(hPackedDIB);
//      //return bResult;
//      return false;
//   }


//   void brush::dump(dump_context & dumpcontext) const
//   {
//      ::draw2d::object::dump(dumpcontext);
//
//      //if (get_os_data() == nullptr)
//        // return;
//
///*      LOGBRUSH lb;
//      VERIFY(GetObject(sizeof(lb), &lb));
//      dumpcontext << "lb.lbStyle = " << lb.lbStyle;
//      dumpcontext << "\nlb.lbHatch = " << lb.lbHatch;
//      dumpcontext << "\nlb.lbColor = " << (void *)(uptr)lb.lbColor;
//
//      dumpcontext << "\n";
//      */
//   }



   //void * brush::get_os_data() const
   //{
   //   
   //   //if(m_pbrush == nullptr || !m_bUpdated)
   //   //{
   //   //   ::acme::del(((brush *) this)->m_pbrush);
   //   //   if(m_etype == type_solid)
   //   //   {
   //   //      try
   //   //      {
   //   //         ((brush *) this)->m_pbrush = memory_new plusplus::SolidBrush(plusplus::Color(color32_u8_opacity(m_color), color32_u8_red(m_color), color32_u8_green(m_color), color32_u8_blue(m_color)));
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //   else if(m_etype == type_linear_gradient_point_color)
   //   //   {
   //   //      try
   //   //      {
   //   //         ((brush *) this)->m_pbrush = memory_new plusplus::LinearGradientBrush(
   //   //            plusplus::PointF((plusplus::REAL) m_point1.x(),(plusplus::REAL) m_point1.y()),
   //   //            plusplus::PointF((plusplus::REAL) m_point2.x(),(plusplus::REAL) m_point2.y()),
   //   //            plusplus::Color(color32_u8_opacity(m_color1), color32_u8_red(m_color1), color32_u8_green(m_color1), color32_u8_blue(m_color1)),
   //   //            plusplus::Color(color32_u8_opacity(m_color2), color32_u8_red(m_color2), color32_u8_green(m_color2), color32_u8_blue(m_color2)));
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //   else if(m_etype == type_radial_gradient_color)
   //   //   {
   //   //      try
   //   //      {

   //   //         plusplus::GraphicsPath * gp = memory_new plusplus::GraphicsPath();
   //   //         gp->AddEllipse((plusplus::REAL) (m_point.x() - m_size.cx() / 2),(plusplus::REAL)(m_point.y() - m_size.cy() / 2),(plusplus::REAL) (m_size.cx()),(plusplus::REAL) (m_size.cy()));

   //   //         plusplus::PathGradientBrush * pgb = memory_new plusplus::PathGradientBrush(gp);

   //   //         plusplus::Color c1(color32_u8_opacity(m_color1),color32_u8_red(m_color1),color32_u8_green(m_color1),color32_u8_blue(m_color1));
   //   //         plusplus::Color c2(color32_u8_opacity(m_color2),color32_u8_red(m_color2),color32_u8_green(m_color2),color32_u8_blue(m_color2));

   //   //            ::i32 c = 1;

   //   //            pgb->SetCenterPoint(plusplus::PointF((plusplus::REAL) m_point.x(),(plusplus::REAL) m_point.y()));
   //   //         pgb->SetCenterColor(c1);
   //   //         pgb->SetSurroundColors(&c2,&c);

   //   //         ((brush *) this)->m_pbrush = pgb;
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //   else
   //   //   {
   //   //      try
   //   //      {
   //   //         ((brush *) this)->m_pbrush = memory_new plusplus::SolidBrush(plusplus::Color(color32_u8_opacity(m_color), color32_u8_red(m_color), color32_u8_green(m_color), color32_u8_blue(m_color)));
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //}

   //   //if(m_pbrush != nullptr)
   //   //{
   //   //   ((brush *) this)->m_bUpdated = true;
   //   //}

   //   //return (void *) (plusplus::Brush *) m_pbrush;

   //   return nullptr;

   //}

} // namespace draw2d_opengl


