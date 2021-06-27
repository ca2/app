#include "framework.h"


#undef new


namespace draw2d_gdiplus
{


   pen::pen()
   {

      m_pthis = this;
      m_egdiplusalign = (Gdiplus::PenAlignment) -1;
      m_ppen = nullptr;

   }


   pen::~pen()
   {
     
      destroy();

   }



#ifdef DEBUG

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

            LOGPEN point_i32;

            VERIFY(GetObject(sizeof(point), &lp));

            dumpcontext << "lgpn.lopnStyle = " << point.lopnStyle;

            dumpcontext << "\nlgpn.lopnWidth.x (width) = " << point.lopnWidth.x;

            dumpcontext << "\nlgpn.lopnColor = " << (void *)(uptr)point.lopnColor;


            dumpcontext << "\n";*/
   }

#endif



   // IMPLEMENT_DYNAMIC(resource_exception, ::exception::base)
   //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

   // IMPLEMENT_DYNAMIC(user_exception, ::exception::base)
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


   /*void __get_gray_bitmap(::aura::application * papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, COLORREF crBackground)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      COLORREF color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer brHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         brShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(nullptr) &&
         graphicsMask->CreateCompatibleDC(nullptr))
      {
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm);
   //         pDest->delete_object();
         if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, nullptr) &&
            bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
         {
            pOldMem = graphicsMem->set(const_cast<::draw2d::bitmap *>(&rSrc));
            pOldMask = graphicsMask->set(bmpMask);

            ASSERT(pOldMem && pOldMask);
            if(!pOldMem || !pOldMask)
               return;

            // Make the upper left corner pixel the "transparent" pixel
            color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
            // Make white pixels transparent too
            graphicsMem->SetBkColor(rgb(255, 255, 255));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

            if(graphicsMem->set(pDest))
            {
               graphicsMem->fill_rectangle(0, 0, bm.bmWidth, bm.bmHeight, crBackground);

               graphicsMem->SetBkColor(rgb(255, 255, 255));

               spbr = graphicsMem->set(brHighLight);
               graphicsMem->BitBlt(1, 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->set(brShadow);
               graphicsMem->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->set(spbr);

               graphicsMem->SetBkColor(color32);
            }
            graphicsMask->set(pOldMask);
            graphicsMem->set(pOldMem);
         }
      }
   }

   void __draw_gray_bitmap(::aura::application * papp, ::draw2d::graphics * pgraphics, i32 x, i32 y, const ::draw2d::bitmap &rSrc, COLORREF crBackground)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsMem, graphicsMask;
      COLORREF color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::draw2d::brush_pointer brHighLight(papp, psession->get_default_color(COLOR_3DHIGHLIGHT)),
         brShadow(papp, psession->get_default_color(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm) &&
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr))
      {
         pOldMem = graphicsMem->set(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->set(bmpMask);

         ASSERT(pOldMem && pOldMask);
         if(!pOldMem || !pOldMask)
            return;

         color32 = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
         graphicsMem->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

         pgraphics->fill_rectangle(x, y, bm.bmWidth, bm.bmHeight, crBackground);

         pgraphics->SetBkColor(rgb(255, 255, 255));

         spbr = pgraphics->set(brHighLight);
         pgraphics->BitBlt(x + 1, y + 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->set(brShadow);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->set(spbr);

         pgraphics->SetBkColor(color32);
         graphicsMask->set(pOldMask);
      }
   }

   void __get_dithered_bitmap(::aura::application * papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, const ::color::color & color1, const ::color::color & color2)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::draw2d::bitmap, pDest);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask, graphicsDest;
      COLORREF color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush brChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

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
               brChecker.CreatePatternBrush(bmpMask);
               //bmpMask->delete_object();

               // Mask
               bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

               pOldSrc = graphicsSrc->set(const_cast<::draw2d::bitmap *>(&rSrc));
               pOldMask = graphicsMask->set(bmpMask);

               ASSERT(pOldSrc && pOldMask);
               if(!pOldSrc || !pOldMask)
                  return;

               // Make the upper left corner pixel of the source a "transparent" color
               color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
               // Make white pixels of the source "transparent" too
               graphicsSrc->SetBkColor(rgb(255, 255, 255));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
               graphicsSrc->SetBkColor(color32);

               // Checker the background with white and crBackground
               pDest = graphicsDest->set(pDest);
               ASSERT(pDest);
               if(pDest)
               {
                  color1 = graphicsDest->SetTextColor(color1);
                  color2 = graphicsDest->SetBkColor(color2);
                  graphicsDest->fill_rectangle(rectangle_i32(0, 0, bm.bmWidth, bm.bmHeight), &brChecker);
                  graphicsDest->SetTextColor(color1);
                  graphicsDest->SetBkColor(color2);

                  // Blt it
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
               }
               graphicsDest->set(pDest);
               graphicsMask->set(pOldMask);
               graphicsSrc->set(pOldSrc);
            }
         }
      }
   }

   void __draw_dithered_bitmap(::aura::application * papp, ::draw2d::graphics * pgraphics, i32 x, i32 y, const ::draw2d::bitmap &rSrc, const ::color::color & color1, const ::color::color & color2)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::draw2d::graphics_pointer, pgraphics);

      BITMAP bm;
      ::draw2d::graphics_pointer graphicsSrc, graphicsMask;
      COLORREF color32;
      ::draw2d::bitmap_pointer bmpMask(papp);
      ::draw2d::bitmap *pOldMask, *pOldSrc;
      ::draw2d::brush brChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::draw2d::bitmap &>(rSrc).GetBitmap(&bm))
      {
         // create checker brush
         bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
         brChecker.CreatePatternBrush(bmpMask);
         //bmpMask->delete_object();

         // Mask
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, nullptr);

         pOldSrc = graphicsSrc->set(const_cast<::draw2d::bitmap *>(&rSrc));
         pOldMask = graphicsMask->set(bmpMask);

         ASSERT(pOldSrc && pOldMask);
         if(!pOldSrc || !pOldMask)
            return;

         // Make the upper left corner pixel of the source a "transparent" color
         color32 = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
         // Make white pixels of the source "transparent" too
         graphicsSrc->SetBkColor(rgb(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
         graphicsSrc->SetBkColor(color32);

         // Checker the background with white and crBackground
         color1 = pgraphics->SetTextColor(color1);
         color2 = pgraphics->SetBkColor(color2);
         pgraphics->fill_rectangle(rectangle_i32(x, y, x + bm.bmWidth, y + bm.bmHeight), &brChecker);
         pgraphics->SetTextColor(color1);
         pgraphics->SetBkColor(color2);

         // Blt it
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);

         graphicsMask->set(pOldMask);
         graphicsSrc->set(pOldSrc);
      }
   }

   */


   bool pen::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      if (m_epen == ::draw2d::e_pen_brush)
      {

         m_ppen = new Gdiplus::Pen(m_pbrush->get_os_data <Gdiplus::Brush *>(pgraphics), (Gdiplus::REAL) m_dWidth);

      }
      else
      {

         m_ppen = new Gdiplus::Pen(gdiplus_color(m_color), (Gdiplus::REAL) m_dWidth);

      }

      switch(m_elinejoin)
      {
      case ::draw2d::e_line_join_miter:
         m_ppen->SetLineJoin(Gdiplus::LineJoinMiter);
         break;
      case ::draw2d::e_line_join_bevel:
         m_ppen->SetLineJoin(Gdiplus::LineJoinBevel);
         break;
      case ::draw2d::e_line_join_round:
         m_ppen->SetLineJoin(Gdiplus::LineJoinRound);
         break;
      case ::draw2d::e_line_join_miter_clipped:
         m_ppen->SetLineJoin(Gdiplus::LineJoinMiterClipped);
         break;
      }

      switch(m_elinecapBeg)
      {
      case ::draw2d::e_line_cap_flat:
         m_ppen->SetStartCap(Gdiplus::LineCapFlat);
         break;
      case ::draw2d::e_line_cap_round:
         m_ppen->SetStartCap(Gdiplus::LineCapRound);
         break;
      case ::draw2d::e_line_cap_square:
         m_ppen->SetStartCap(Gdiplus::LineCapSquare);
         break;
      }

      switch(m_elinecapEnd)
      {
      case ::draw2d::e_line_cap_flat:
         m_ppen->SetEndCap(Gdiplus::LineCapFlat);
         break;
      case ::draw2d::e_line_cap_round:
         m_ppen->SetEndCap(Gdiplus::LineCapRound);
         break;
      case ::draw2d::e_line_cap_square:
         m_ppen->SetEndCap(Gdiplus::LineCapSquare);
         break;
      }

      if(m_epen == ::draw2d::e_pen_dot)
      {

         Gdiplus::REAL dashVals[4];

         dashVals[0] = 1;
         dashVals[1] = 2;

         // Create a Pen object.

         // Set the dash pattern for the custom dashed line.
         m_ppen->SetDashPattern(dashVals,2);

      }
      else if (m_epen == ::draw2d::e_pen_dash)
      {

         Gdiplus::REAL dashVals[4];

         dashVals[0] = 10;
         dashVals[1] = 10;

         // Create a Pen object.

         // Set the dash pattern for the custom dashed line.
         m_ppen->SetDashPattern(dashVals, 2);
         //m_ppen->SetDashStyle(Gdiplus::DashStyleDash
         //                                 );

      }

      if (m_epenalign == ::draw2d::e_pen_align_inset)
      {

         m_ppen->SetAlignment(Gdiplus::PenAlignmentInset);

      }
      else if (m_epenalign == ::draw2d::e_pen_align_center)
      {

         m_ppen->SetAlignment(Gdiplus::PenAlignmentCenter);

      }

      m_osdata[0] = m_ppen;

      return ::is_set(m_ppen);

   }


   void pen::destroy()
   {

      ::acme::del(m_ppen);

      ::draw2d::pen::clear_os_data();

   }


} // namespace draw2d_gdiplus