#include "framework.h"

#undef new

namespace draw2d_opengl
{


   brush::brush()
   { 

   }


   brush::~brush()
   { 
      //::acme::del(m_pbrush);
   }

   //bool brush::create_solid(COLORREF crColor)
   //{

   //   if(m_pbrush != nullptr)
   //   {
   //      delete m_pbrush;
   //   }

   //   m_pbrush = new plusplus::SolidBrush(plusplus::Color(colorref_get_a_value(crColor), colorref_get_r_value(crColor), colorref_get_g_value(crColor), colorref_get_b_value(crColor)));

   //   return m_pbrush != nullptr;
   //      
   //}

   // bool brush::CreateHatchBrush(i32 nIndex, COLORREF crColor)
   // { 
   //    //return attach(::CreateHatchBrush(nIndex, crColor));
   //    return FALSE;
   // }
//    bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
  //  {
       //return attach(::CreateBrushIndirect(lpLogBrush)); 
    //   return FALSE;
    //}
    //bool brush::CreatePatternBrush(::draw2d::bitmap* pBitmap)
    //{ 
    //   //return attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data()));
    //   return FALSE;
    //}
    //bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage)
    //{ 
    //   //return attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
    //   return FALSE;
    //}
    //bool brush::CreateSysColorBrush(i32 nIndex)
    //{ 
    //   //return attach(::GetSysColorBrush(nIndex));
    //   return FALSE;

    //}
/*    i32 brush::GetLogBrush(LOGBRUSH* pLogBrush)
    { 
       //ASSERT(get_os_data() != nullptr);
       //return ::GetObject(get_os_data(), sizeof(LOGBRUSH), pLogBrush); 
       return FALSE;
    }*/


//   void brush::construct(COLORREF crColor)
//   {
////      if (!attach(::create_solid(crColor)))
//  //       __throw(resource_exception());
//   }
//
//   void brush::construct(i32 nIndex, COLORREF crColor)
//   {
//    //  if (!attach(::CreateHatchBrush(nIndex, crColor)))
//      //   __throw(resource_exception());
//   }
//
//   void brush::construct(::draw2d::bitmap* pBitmap)
//   {
//      //ASSERT_VALID(pBitmap);
//
//      //if (!attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())))
//        // __throw(resource_exception());
//   }
//
//   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
//   {
//      //ASSERT(hPackedDIB != nullptr);
//      //const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
//      //ASSERT(lpPackedDIB != nullptr);
//      //bool bResult = attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
//      //::GlobalUnlock(hPackedDIB);
//      //return bResult;
//      return FALSE;
//   }


   void brush::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      //if (get_os_data() == nullptr)
        // return;

/*      LOGBRUSH lb;
      VERIFY(GetObject(sizeof(lb), &lb));
      dumpcontext << "lb.lbStyle = " << lb.lbStyle;
      dumpcontext << "\nlb.lbHatch = " << lb.lbHatch;
      dumpcontext << "\nlb.lbColor = " << (void *)(uptr)lb.lbColor;

      dumpcontext << "\n";
      */
   }



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
   //   //         ((brush *) this)->m_pbrush = new plusplus::SolidBrush(plusplus::Color(colorref_get_a_value(m_color), colorref_get_r_value(m_color), colorref_get_g_value(m_color), colorref_get_b_value(m_color)));
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //   else if(m_etype == type_linear_gradient_point_color)
   //   //   {
   //   //      try
   //   //      {
   //   //         ((brush *) this)->m_pbrush = new plusplus::LinearGradientBrush(
   //   //            plusplus::PointF((plusplus::REAL) m_point1.x,(plusplus::REAL) m_point1.y),
   //   //            plusplus::PointF((plusplus::REAL) m_point2.x,(plusplus::REAL) m_point2.y),
   //   //            plusplus::Color(colorref_get_a_value(m_color1), colorref_get_r_value(m_color1), colorref_get_g_value(m_color1), colorref_get_b_value(m_color1)),
   //   //            plusplus::Color(colorref_get_a_value(m_color2), colorref_get_r_value(m_color2), colorref_get_g_value(m_color2), colorref_get_b_value(m_color2)));
   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }
   //   //   }
   //   //   else if(m_etype == type_radial_gradient_color)
   //   //   {
   //   //      try
   //   //      {

   //   //         plusplus::GraphicsPath * gp = new plusplus::GraphicsPath();
   //   //         gp->AddEllipse((plusplus::REAL) (m_point.x - m_size.cx / 2),(plusplus::REAL)(m_point.y - m_size.cy / 2),(plusplus::REAL) (m_size.cx),(plusplus::REAL) (m_size.cy));

   //   //         plusplus::PathGradientBrush * pgb = new plusplus::PathGradientBrush(gp);

   //   //         plusplus::Color c1(colorref_get_a_value(m_color1),colorref_get_r_value(m_color1),colorref_get_g_value(m_color1),colorref_get_b_value(m_color1));
   //   //         plusplus::Color c2(colorref_get_a_value(m_color2),colorref_get_r_value(m_color2),colorref_get_g_value(m_color2),colorref_get_b_value(m_color2));

   //   //            INT c = 1;

   //   //            pgb->SetCenterPoint(plusplus::PointF((plusplus::REAL) m_point.x,(plusplus::REAL) m_point.y));
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
   //   //         ((brush *) this)->m_pbrush = new plusplus::SolidBrush(plusplus::Color(colorref_get_a_value(m_color), colorref_get_r_value(m_color), colorref_get_g_value(m_color), colorref_get_b_value(m_color)));
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


