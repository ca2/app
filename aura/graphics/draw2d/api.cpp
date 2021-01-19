#include "framework.h"


namespace draw2d
{


   api::api()
   {

   }


   api::~api()
   {

   }


   void api::draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::pointd *                    ppoints,
      i32                           iCount,
      double                        dRateX,
      ::pointd *                    ppointOffset)
   {

      ::rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(ppointOffset->x, ppointOffset->y);


      pgraphics->ScaleViewportExt((i32)dRateX, 1, 1, 1);

      pgraphics->begin_path();
      pgraphics->poly_bezier(ppoints, iCount);

      pgraphics->end_path();
      pgraphics->stroke_path();

      pgraphics->set_window_ext(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }


   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pgraphics,
   ::pointd *             ppoints,
   i32                  iCount,
   double               dRateX,
   ::pointd *               ppointOffset)
   {

      ::rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(
      ppointOffset->x,

      ppointOffset->y);


      pgraphics->ScaleViewportExt((i32)dRateX, 1, 1, 1);

      pgraphics->begin_path();
      pgraphics->poly_bezier(ppoints, iCount);

      pgraphics->end_path();
      pgraphics->stroke_and_fill_path();

      pgraphics->set_window_ext(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }

   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pgraphics,
   array<pointd_array, pointd_array &> *
   pglyph,

   double               dRateX,
   pointd *               ppointOffset)

   {

      ::rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(
      ppointOffset->x,

      ppointOffset->y);


      pgraphics->ScaleViewportExt((i32)(dRateX * 1000.0), 1, 1, 1);

      for (i32 i = 0; i < pglyph->get_size(); i++)

      {
         pgraphics->poly_bezier(pglyph->element_at(i).get_data(), (i32)pglyph->element_at(i).get_size());

      }

      pgraphics->set_window_ext(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }

   void api::embossed_text_out(
   ::draw2d::graphics_pointer &     pgraphics,
   const rectd &                    rect,
   double                           dRateX,
   double                           dHeight,
   const char *                     psz,
   int *                            piCharsPositions,
   i32                              iCharsPositions,
   i32                              iOffset)
   {

      ::rect clipRect;



      //      i32 iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      point viewportOrg;
      //      ::draw2d::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != nullptr);
      //      VERIFY(::GetViewportOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         rect.left,
      //         rect.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::ScaleViewportExtEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      pgraphics->text_out(rect.left, rect.top, psz);
      pgraphics->begin_path();
      pgraphics->text_out(rect.left, rect.top, psz);
      pgraphics->end_path();
      pgraphics->stroke_path();


      //      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
      //      VERIFY(::SetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         viewportOrg.x,
      //         viewportOrg.y,
      //         nullptr));
   }


   void api::embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const char *   psz,
   i32            iLeft,
   i32            iTop,
   i32            iWidth,
   color32_t       crText,
   color32_t       crOutline,
   i32            iLen)
   {
      ::rect clipRect;

      //      i32 iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      point viewportOrg;
      //      ::draw2d::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != nullptr);
      //      VERIFY(::GetViewportOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         rect.left,
      //         rect.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::ScaleViewportExtEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      string str;
      str = ::str::international::utf8_to_unicode(psz);

#ifdef WINDOWS_DESKTOP
      ::SetTextColor((HDC)pgraphics->get_os_data(), crOutline);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft - iWidth, iTop, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop - iWidth, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft + iWidth, iTop, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop + iWidth, str, iLen);

      ::SetTextColor((HDC)pgraphics->get_os_data(), crText);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop, str, iLen);
#endif

      //pgraphics->text_out(rect.left, rect.top, str);
//      pgraphics->BeginPath();
//      ::TextOutW((HDC)pgraphics->get_os_data(), rect.left, rect.top, pcsz, iLen);

      //pgraphics->text_out(rect.left, rect.top, str);
//      pgraphics->EndPath();
//      pgraphics->StrokePath();


//      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
//      VERIFY(::SetViewportOrgEx(
//         pgraphics->m_hDC,
//         viewportOrg.x,
//         viewportOrg.y,
//         nullptr));
   }

   void api::simple_text_out(
   ::draw2d::graphics_pointer &  pgraphics,
   const rectd &                 pcrect,
   double                        dRateX,
   double                        dHeight,
   const char *                  psz,
   int *                         piCharsPositions,
   i32                           iCharsPositions,
   i32                           iOffset)
   {
      UNREFERENCED_PARAMETER(dRateX);
      UNREFERENCED_PARAMETER(dHeight);
      UNREFERENCED_PARAMETER(iOffset);
      UNREFERENCED_PARAMETER(iCharsPositions);
      UNREFERENCED_PARAMETER(piCharsPositions);


      pgraphics->text_out(pcrect.left, pcrect.top, psz);

      return;

//      string str;
//      str = ::str::international::utf8_to_unicode(psz);
//      ::TextOutU((HDC)pgraphics->get_os_data(), pcrect.left, pcrect.top, str, (i32)str.get_length());

   }


   void api::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::rectd & rect, double dHeight, double dRateX, const char * psz)
   {

      pgraphics->text_out(rect.left, rect.top, psz);
      pgraphics->begin_path();
      pgraphics->text_out(rect.left, rect.top, psz);
      pgraphics->end_path();
      pgraphics->stroke_path();

   }


   bool api::open()
   {

      return true;

   }


   bool api::close()
   {

      return true;

   }


} // namespace draw2d




