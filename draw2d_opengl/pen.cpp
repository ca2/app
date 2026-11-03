#include "platform.h"
#include "_draw2d_opengl.h"
#include "pen.h"


namespace draw2d_opengl
{


   pen::pen()
   { 
      //m_egl2dalign = (plusplus::PenAlignment) -1;
      //m_pdraw2dpen = nullptr;

   }

   pen::~pen()
   { 
   /*   if(m_pdraw2dpen != nullptr)
      {
         delete m_pdraw2dpen;
         m_pdraw2dpen = nullptr;
      }*/
   }

   /*bool pen::CreatePen(int nPenStyle, int nWidth, color32_t crColor)
   { return attach(::CreatePen(nPenStyle, nWidth, crColor)); }
   bool pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   { return attach(::CreatePenIndirect(lpLogPen)); }
   bool pen::CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
      int nStyleCount, const unsigned int* lpStyle)
   { return attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
   lpStyle)); }
   int pen::GetExtLogPen(EXTLOGPEN* pLogPen)
   { ASSERT(get_handle() != nullptr);
   return ::GetObject(get_handle(), sizeof(EXTLOGPEN), pLogPen); }
   
   int pen::GetLogPen(LOGPEN* pLogPen)
   { 
      if(get_handle() == nullptr)
         return 0;
      return ::GetObject(get_handle(), sizeof(LOGPEN), pLogPen); 
   }


   void pen::construct(int nPenStyle, double dWidth, color32_t crColor)
   {
      
      if(m_pdraw2dpen == nullptr)
         delete m_pdraw2dpen;

      m_nPenStyle    = nPenStyle;
      m_dWidth       = dWidth;
      m_colorColor      = crColor;
      m_pdraw2dpen         = allocateø< plusplus::Pen(plusplus::Color >(crColor), dWidth);

   }

   void pen::construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
      int nStyleCount, const unsigned int* lpStyle)
   {
      if (!attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
         lpStyle)))
         throw ::exception(error_resource);
   }*/

   /////////////////////////////////////////////////////////////////////////////

//
//   void pen::dump(dump_context & dumpcontext) const
//   {
//      ::draw2d::object::dump(dumpcontext);
//
///*      if (get_handle() == nullptr)
//         return;
//
//      if (!::windows_definition::Data.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
//      {
//         // not a valid object
//         dumpcontext << "has ILLEGAL HPEN!";
//         return;
//      }
//
//      LOGPEN lp;
//      VERIFY(GetObject(sizeof(lp), &lp));
//      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
//      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
//      dumpcontext << "\nlgpn.lopnColor = " << (void *)(uptr)lp.lopnColor;
//
//      dumpcontext << "\n";*/
//   }
//
//



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


   /*void __get_gray_bitmap(::particle * pparticle, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, color32_t crBackground)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pparticle);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const unsigned int   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->create_compatible_graphics(nullptr) &&
         graphicsMask->create_compatible_graphics(nullptr))
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

   void __draw_gray_bitmap(::particle * pparticle, ::draw2d::graphics * pdraw2dgraphics, int x, int y, const ::draw2d::bitmap &rSrc, color32_t crBackground)
   {
      ASSERT(pdraw2dgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pdraw2dgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pparticle);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const unsigned int   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer pbrushHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         pbrushShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->create_compatible_graphics(pdraw2dgraphics) &&
         graphicsMask->create_compatible_graphics(pdraw2dgraphics) &&
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

         pdraw2dgraphics->FillSolidRect(x, y, bm.bmWidth, bm.bmHeight, crBackground);

         pdraw2dgraphics->SetBkColor(rgb(255, 255, 255));

         spbr = pdraw2dgraphics->SelectObject(pbrushHighLight);
         pdraw2dgraphics->BitBlt(x + 1, y + 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pdraw2dgraphics->SelectObject(pbrushShadow);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pdraw2dgraphics->SelectObject(spbr);

         pdraw2dgraphics->SetBkColor(color32);
         graphicsMask->SelectObject(pOldMask);
      }
   }

   void __get_dithered_bitmap(::particle * pparticle, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, color32_t cr1, color32_t cr2)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask, graphicsDest;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pparticle);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const unsigned short wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->create_compatible_graphics(nullptr) &&
         graphicsMask->create_compatible_graphics(nullptr) &&
         graphicsDest->create_compatible_graphics(nullptr))
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
                  graphicsDest->FillRect(i32_rectangle(0, 0, bm.bmWidth, bm.bmHeight), &pbrushChecker);
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

   void __draw_dithered_bitmap(::particle * pparticle, ::draw2d::graphics * pdraw2dgraphics, int x, int y, const ::draw2d::bitmap &rSrc, color32_t cr1, color32_t cr2)
   {
      ASSERT(pdraw2dgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pdraw2dgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask;
      color32_t color32;
      ::draw2d::bitmap_pointer bmpMask(pparticle);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush pbrushChecker;
      static const unsigned short wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->create_compatible_graphics(pdraw2dgraphics) &&
         graphicsMask->create_compatible_graphics(pdraw2dgraphics) &&
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
         cr1 = pdraw2dgraphics->SetTextColor(cr1);
         cr2 = pdraw2dgraphics->SetBkColor(cr2);
         pdraw2dgraphics->FillRect(i32_rectangle(x, y, x + bm.bmWidth, y + bm.bmHeight), &pbrushChecker);
         pdraw2dgraphics->SetTextColor(cr1);
         pdraw2dgraphics->SetBkColor(cr2);

         // Blt it
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
         pdraw2dgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);

         graphicsMask->SelectObject(pOldMask);
         graphicsSrc->SelectObject(pOldSrc);
      }
   }

*/

   void * pen::get_os_data() const
   {
      
      //if(m_pdraw2dpen == nullptr || !m_bUpdated)
      //{
      //   if(m_pdraw2dpen != nullptr)
      //   {
      //      delete m_pdraw2dpen;
      //   }
      //   if (m_epen == ::draw2d::e_pen_brush)
      //   {
      //      
      //      ((pen *) this)->m_pdraw2dpen = allocateø< plusplus::Pen((plusplus::Brush *) m_br.cast < brush >()->get_os_data(),  >(plusplus::REAL) m_dWidth);

      //   }
      //   else
      //   {
      //      ((pen *) this)->m_pdraw2dpen = allocateø< plusplus::Pen(plusplus::Color >(
      //         color32_byte_opacity(m_color),
      //         color32_byte_red(m_color),
      //         color32_byte_green(m_color),
      //         color32_byte_blue(m_color)), (plusplus::REAL) m_dWidth);

      //   }
      //   switch(m_elinejoin)
      //   {
      //   case ::draw2d::e_line_join_miter:
      //      ((pen *) this)->m_pdraw2dpen->SetLineJoin(plusplus::LineJoinMiter);
      //      break;
      //   case ::draw2d::e_line_join_bevel:
      //      ((pen *) this)->m_pdraw2dpen->SetLineJoin(plusplus::LineJoinBevel);
      //      break;
      //   case ::draw2d::e_line_join_round:
      //      ((pen *) this)->m_pdraw2dpen->SetLineJoin(plusplus::LineJoinRound);
      //      break;
      //   case ::draw2d::e_line_join_miter_clipped:
      //      ((pen *) this)->m_pdraw2dpen->SetLineJoin(plusplus::LineJoinMiterClipped);
      //      break;
      //   }
      //   switch(m_elinecapBeg)
      //   {
      //   case ::draw2d::e_line_cap_flat:
      //      ((pen *) this)->m_pdraw2dpen->SetStartCap(plusplus::LineCapFlat);
      //      break;
      //   case ::draw2d::e_line_cap_round:
      //      ((pen *) this)->m_pdraw2dpen->SetStartCap(plusplus::LineCapRound);
      //      break;
      //   case ::draw2d::e_line_cap_square:
      //      ((pen *) this)->m_pdraw2dpen->SetStartCap(plusplus::LineCapSquare);
      //      break;
      //   }
      //   switch(m_elinecapEnd)
      //   {
      //   case ::draw2d::e_line_cap_flat:
      //      ((pen *) this)->m_pdraw2dpen->SetEndCap(plusplus::LineCapFlat);
      //      break;
      //   case ::draw2d::e_line_cap_round:
      //      ((pen *) this)->m_pdraw2dpen->SetEndCap(plusplus::LineCapRound);
      //      break;
      //   case ::draw2d::e_line_cap_square:
      //      ((pen *) this)->m_pdraw2dpen->SetEndCap(plusplus::LineCapSquare);
      //      break;
      //   }
      //   if(m_epen == ::draw2d::e_pen_dot)
      //   {
      //      plusplus::REAL dashVals[4];

      //      dashVals[0] = 1;
      //      dashVals[1] = 2;

      //      // Create a Pen object.

      //      // Set the dash pattern for the custom dashed line.
      //      ((pen *) this)->m_pdraw2dpen->SetDashPattern(dashVals,2);
      //   }
      //}

      //if(m_pdraw2dpen != nullptr)
      //{
      //   ((pen *) this)->m_bUpdated = true;
      //}

      //return (void *) (plusplus::Pen *) m_pdraw2dpen;

      return nullptr;

   }


} // namespace draw2d_opengl
