#include "framework.h"


namespace draw2d_xlib
{


   brush::brush(::context_object * pcontextobject) :
      ::object(pobject)
   {


   }


   brush::~brush()
   {
   }

   //bool brush::CreateSolidBrush(color32_t crColor)
   //{

   //   if(m_pbrush != nullptr)
   //   {
   //      delete m_pbrush;
   //   }

   //   m_pbrush = new Gdiplus::SolidBrush(Gdiplus::Color(GetAValue(crColor), colorref_get_r_value(crColor), GetGValue(crColor), GetBValue(crColor)));

   //   return m_pbrush != nullptr;
   //
   //}

   // bool brush::CreateHatchBrush(i32 nIndex, color32_t crColor)
   // {
   //    //return Attach(::CreateHatchBrush(nIndex, crColor));
   //    return false;
   // }
//    bool brush::CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
  //  {
       //return Attach(::CreateBrushIndirect(lpLogBrush));
    //   return false;
    //}
    //bool brush::CreatePatternBrush(::draw2d::bitmap* pBitmap)
    //{
    //   //return Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data()));
    //   return false;
    //}
    //bool brush::CreateDIBPatternBrush(const void * lpPackedDIB, ::u32 nUsage)
    //{
    //   //return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
    //   return false;
    //}
    //bool brush::CreateSysColorBrush(i32 nIndex)
    //{
    //   //return Attach(::GetSysColorBrush(nIndex));
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
////      if (!Attach(::CreateSolidBrush(crColor)))
//  //       __throw(error_resource);
//   }
//
//   void brush::construct(i32 nIndex, color32_t crColor)
//   {
//    //  if (!Attach(::CreateHatchBrush(nIndex, crColor)))
//      //   __throw(error_resource);
//   }
//
//   void brush::construct(::draw2d::bitmap* pBitmap)
//   {
//      //ASSERT_VALID(pBitmap);
//
//      //if (!Attach(::CreatePatternBrush((HBITMAP)pBitmap->get_os_data())))
//        // __throw(error_resource);
//   }
//
//   bool brush::CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage)
//   {
//      //ASSERT(hPackedDIB != nullptr);
//      //const void * lpPackedDIB = ::GlobalLock(hPackedDIB);
//      //ASSERT(lpPackedDIB != nullptr);
//      //bool bResult = Attach(::CreateDIBPatternBrushPt(lpPackedDIB, nUsage));
//      //::GlobalUnlock(hPackedDIB);
//      //return bResult;
//      return false;
//   }


   void brush::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

      //if (get_os_data() == nullptr)
        // return;

/*      LOGBRUSH lb;
      VERIFY(GetObject(sizeof(lb), &lb));
      dumpcontext << "lb.lbStyle = " << lb.lbStyle;
      dumpcontext << "\nlb.lbHatch = " << lb.lbHatch;
      dumpcontext << "\nlb.lbColor = " << (void *)(dword_ptr)lb.lbColor;

      dumpcontext << "\n";
      */
   }



   void * brush::get_os_data() const
   {

      if(!m_bUpdated)
      {
         if(m_etype == type_solid)
         {

//            ((brush *) this)->m_iStock = -1;

  //          ((brush *) this)->m_iStyle = FillSolid;

         }
         else if(m_etype == type_linear_gradient_point_color)
         {
/*
            ((brush *) this)->m_pbrush = new Gdiplus::LinearGradientBrush(
               Gdiplus::Point(m_point1.x, m_point1.y),
               Gdiplus::Point(m_point2.x, m_point2.y),
               Gdiplus::Color(GetAValue(m_color1), colorref_get_r_value(m_color1), GetGValue(m_color1), GetBValue(m_color1)),
               Gdiplus::Color(GetAValue(m_color2), colorref_get_r_value(m_color2), GetGValue(m_color2), GetBValue(m_color2)));
*/
         }
         else
         {

    //        ((brush *) this)->m_iStock = -1;

      //      ((brush *) this)->m_iStyle = FillSolid;

         }
      }

      ((brush *) this)->m_bUpdated = true;

      return (void *) (brush*) this;

   }


} // namespace draw2d_xlib



