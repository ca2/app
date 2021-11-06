#include "framework.h"


#undef new


namespace draw2d_opengl
{


   pen::pen()
   { 
      //m_egl2dalign = (plusplus::PenAlignment) -1;
      //m_ppen = nullptr;

   }

   pen::~pen()
   { 
   /*   if(m_ppen != nullptr)
      {
         delete m_ppen;
         m_ppen = nullptr;
      }*/
   }

   /*bool pen::CreatePen(i32 nPenStyle, i32 nWidth, color32_t crColor)
   { return attach(::CreatePen(nPenStyle, nWidth, crColor)); }
   bool pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   { return attach(::CreatePenIndirect(lpLogPen)); }
   bool pen::CreatePen(i32 nPenStyle, i32 nWidth, const LOGBRUSH* pLogBrush,
      i32 nStyleCount, const ::u32* lpStyle)
   { return attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
   lpStyle)); }
   i32 pen::GetExtLogPen(EXTLOGPEN* pLogPen)
   { ASSERT(get_handle() != nullptr);
   return ::GetObject(get_handle(), sizeof(EXTLOGPEN), pLogPen); }
   
   i32 pen::GetLogPen(LOGPEN* pLogPen)
   { 
      if(get_handle() == nullptr)
         return 0;
      return ::GetObject(get_handle(), sizeof(LOGPEN), pLogPen); 
   }


   void pen::construct(i32 nPenStyle, double dWidth, color32_t crColor)
   {
      
      if(m_ppen == nullptr)
         delete m_ppen;

      m_nPenStyle    = nPenStyle;
      m_dWidth       = dWidth;
      m_colorColor      = crColor;
      m_ppen         = new plusplus::Pen(plusplus::Color(crColor), dWidth);

   }

   void pen::construct(i32 nPenStyle, i32 nWidth, const LOGBRUSH* pLogBrush,
      i32 nStyleCount, const ::u32* lpStyle)
   {
      if (!attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
         lpStyle)))
         __throw(error_resource);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   void pen::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

/*      if (get_handle() == nullptr)
         return;

      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
      {
         // not a valid object
         dumpcontext << "has ILLEGAL HPEN!";
         return;
      }

      LOGPEN lp;
      VERIFY(GetObject(sizeof(lp), &lp));
      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
      dumpcontext << "\nlgpn.lopnColor = " << (void *)(uptr)lp.lopnColor;

      dumpcontext << "\n";*/
   }





      // IMPLEMENT_DYNAMIC(resource_exception, ::exception)
      //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

      // IMPLEMENT_DYNAMIC(user_exception, ::exception)
      //user_exception _simpleUserException(false, __IDS_USER_EXCEPTION);

      // IMPLEMENT_DYNCREATE(::draw2d::graphics_pointer, object)
      // IMPLEMENT_DYNAMIC(CClientDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CWindowDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CPaintDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNCREATE(::draw2d::object, object)

      // IMPLEMENT_DYNAMIC(pen, ::draw2d::object)
      // IMPLEMENT_DYNAMIC(::draw2d::brush, ::draw2d::object)
      // IMPLEMENT_DYNAMIC(::write_text::font, ::draw2d::object)
      // IMPLEMENT_DYNAMIC(::draw2d::bitmap, ::draw2d::object)
      // IMPLEMENT_DYNAMIC(::draw2d::palette, ::draw2d::object)
      // IMPLEMENT_DYNAMIC(::draw2d::region, ::draw2d::object)

      /////////////////////////////////////////////////////////////////////////////
      // Standard exception processing


   /*void __get_gray_bitmap(::object * pobject, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, color32_t crBackground)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pobject);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const ::u32   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(nullptr) &&
         graphicsMask->CreateCompatibleDC(nullptr))
      {
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm);
//         pDest->delete_object();
         if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, nullptr) &&
            bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
         {
            pOldMem = graphicsMem->SelectObject(const_cast<::draw2d::bitmap *>(&rSrc));
            pOldMask = graphicsMask->SelectObject(bmpMask);

            ASSERT(pOldMem && pOldMask);
            if(!pOldMem || !pOldMask)
               return;

            // Make the upper left corner pixel the "transparent" pixel
            color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0);
            // Make white pixels transparent too
            graphicsMem->SetBkColor(rgb(255, 255, 255));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

            if(graphicsMem->SelectObject(pDest))
            {
               graphicsMem->FillSolidRect(0, 0, bm.bmWidth, bm.bmHeight, crBackground);

               graphicsMem->SetBkColor(rgb(255, 255, 255));

               spbr = graphicsMem->SelectObject(pbrushHighLight);
               graphicsMem->BitBlt(1, 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->SelectObject(pbrushShadow);
               graphicsMem->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->SelectObject(spbr);

               graphicsMem->SetBkColor(color32);
            }
            graphicsMask->SelectObject(pOldMask);
            graphicsMem->SelectObject(pOldMem);
         }
      }
   }

   void __draw_gray_bitmap(::object * pobject, ::draw2d::graphics * pgraphics, i32 x, i32 y, const ::draw2d::bitmap &rSrc, color32_t crBackground)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pobject);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const ::u32   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm) &&
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
      {
         pOldMem = graphicsMem->SelectObject(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->SelectObject(bmpMask);

         ASSERT(pOldMem && pOldMask);
         if(!pOldMem || !pOldMask)
            return;

         color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0);
         graphicsMem->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

         pgraphics->FillSolidRect(x, y, bm.bmWidth, bm.bmHeight, crBackground);

         pgraphics->SetBkColor(rgb(255, 255, 255));

         spbr = pgraphics->SelectObject(pbrushHighLight);
         pgraphics->BitBlt(x + 1, y + 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->SelectObject(pbrushShadow);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->SelectObject(spbr);

         pgraphics->SetBkColor(color32);
         graphicsMask->SelectObject(pOldMask);
      }
   }

   void __get_dithered_bitmap(::object * pobject, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, color32_t cr1, color32_t cr2)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask, graphicsDest;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pobject);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const ::u16 wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->CreateCompatibleDC(nullptr) &&
         graphicsMask->CreateCompatibleDC(nullptr) &&
         graphicsDest->CreateCompatibleDC(nullptr))
      {
         if(const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm))
         {
            //pDest->delete_object();
            if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, nullptr))
            {
               // create checker brush
               bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
               pbrushChecker.CreatePatternBrush(bmpMask);
               //bmpMask->delete_object();

               // Mask
               bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

               pOldSrc = graphicsSrc->SelectObject(const_cast<::draw2d::bitmap *>(&rSrc));
               pOldMask = graphicsMask->SelectObject(bmpMask);

               ASSERT(pOldSrc && pOldMask);
               if(!pOldSrc || !pOldMask)
                  return;

               // Make the upper left corner pixel of the source a "transparent" color
               color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0);
               // Make white pixels of the source "transparent" too
               graphicsSrc->SetBkColor(rgb(255, 255, 255));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
               graphicsSrc->SetBkColor(color32);

               // Checker the background with white and crBackground
               pDest = graphicsDest->SelectObject(pDest);
               ASSERT(pDest);
               if(pDest)
               {
                  cr1 = graphicsDest->SetTextColor(cr1);
                  cr2 = graphicsDest->SetBkColor(cr2);
                  graphicsDest->FillRect(rectangle_i32(0, 0, bm.bmWidth, bm.bmHeight), &pbrushChecker);
                  graphicsDest->SetTextColor(cr1);
                  graphicsDest->SetBkColor(cr2);

                  // Blt it
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
               }
               graphicsDest->SelectObject(pDest);
               graphicsMask->SelectObject(pOldMask);
               graphicsSrc->SelectObject(pOldSrc);
            }
         }
      }
   }

   void __draw_dithered_bitmap(::object * pobject, ::draw2d::graphics * pgraphics, i32 x, i32 y, const ::draw2d::bitmap &rSrc, color32_t cr1, color32_t cr2)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pobject);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const ::u16 wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm))
      {
         // create checker brush
         bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
         pbrushChecker.CreatePatternBrush(bmpMask);
         //bmpMask->delete_object();

         // Mask
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

         pOldSrc = graphicsSrc->SelectObject(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->SelectObject(bmpMask);

         ASSERT(pOldSrc && pOldMask);
         if(!pOldSrc || !pOldMask)
            return;

         // Make the upper left corner pixel of the source a "transparent" color
         color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0);
         // Make white pixels of the source "transparent" too
         graphicsSrc->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
         graphicsSrc->SetBkColor(color32);

         // Checker the background with white and crBackground
         cr1 = pgraphics->SetTextColor(cr1);
         cr2 = pgraphics->SetBkColor(cr2);
         pgraphics->FillRect(rectangle_i32(x, y, x + bm.bmWidth, y + bm.bmHeight), &pbrushChecker);
         pgraphics->SetTextColor(cr1);
         pgraphics->SetBkColor(cr2);

         // Blt it
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);

         graphicsMask->SelectObject(pOldMask);
         graphicsSrc->SelectObject(pOldSrc);
      }
   }

*/

   void * pen::get_os_data() const
   {
      
      //if(m_ppen == nullptr || !m_bUpdated)
      //{
      //   if(m_ppen != nullptr)
      //   {
      //      delete m_ppen;
      //   }
      //   if (m_epen == ::draw2d::e_pen_brush)
      //   {
      //      
      //      ((pen *) this)->m_ppen = new plusplus::Pen((plusplus::Brush *) m_br.cast < brush >()->get_os_data(), (plusplus::REAL) m_dWidth);

      //   }
      //   else
      //   {
      //      ((pen *) this)->m_ppen = new plusplus::Pen(plusplus::Color(
      //         colorref_get_a_value(m_color),
      //         colorref_get_r_value(m_color),
      //         colorref_get_g_value(m_color),
      //         colorref_get_b_value(m_color)), (plusplus::REAL) m_dWidth);

      //   }
      //   switch(m_elinejoin)
      //   {
      //   case ::draw2d::e_line_join_miter:
      //      ((pen *) this)->m_ppen->SetLineJoin(plusplus::LineJoinMiter);
      //      break;
      //   case ::draw2d::e_line_join_bevel:
      //      ((pen *) this)->m_ppen->SetLineJoin(plusplus::LineJoinBevel);
      //      break;
      //   case ::draw2d::e_line_join_round:
      //      ((pen *) this)->m_ppen->SetLineJoin(plusplus::LineJoinRound);
      //      break;
      //   case ::draw2d::e_line_join_miter_clipped:
      //      ((pen *) this)->m_ppen->SetLineJoin(plusplus::LineJoinMiterClipped);
      //      break;
      //   }
      //   switch(m_elinecapBeg)
      //   {
      //   case ::draw2d::e_line_cap_flat:
      //      ((pen *) this)->m_ppen->SetStartCap(plusplus::LineCapFlat);
      //      break;
      //   case ::draw2d::e_line_cap_round:
      //      ((pen *) this)->m_ppen->SetStartCap(plusplus::LineCapRound);
      //      break;
      //   case ::draw2d::e_line_cap_square:
      //      ((pen *) this)->m_ppen->SetStartCap(plusplus::LineCapSquare);
      //      break;
      //   }
      //   switch(m_elinecapEnd)
      //   {
      //   case ::draw2d::e_line_cap_flat:
      //      ((pen *) this)->m_ppen->SetEndCap(plusplus::LineCapFlat);
      //      break;
      //   case ::draw2d::e_line_cap_round:
      //      ((pen *) this)->m_ppen->SetEndCap(plusplus::LineCapRound);
      //      break;
      //   case ::draw2d::e_line_cap_square:
      //      ((pen *) this)->m_ppen->SetEndCap(plusplus::LineCapSquare);
      //      break;
      //   }
      //   if(m_epen == ::draw2d::e_pen_dot)
      //   {
      //      plusplus::REAL dashVals[4];

      //      dashVals[0] = 1;
      //      dashVals[1] = 2;

      //      // Create a Pen object.

      //      // Set the dash pattern for the custom dashed line.
      //      ((pen *) this)->m_ppen->SetDashPattern(dashVals,2);
      //   }
      //}

      //if(m_ppen != nullptr)
      //{
      //   ((pen *) this)->m_bUpdated = true;
      //}

      //return (void *) (plusplus::Pen *) m_ppen;

      return nullptr;

   }


} // namespace draw2d_opengl
