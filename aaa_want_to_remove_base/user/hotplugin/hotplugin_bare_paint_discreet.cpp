#include "framework.h"



#include <math.h>


namespace hotplugin
{


   void plugin::on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const ::rect & rectParam)

   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      ::rect rectWindow;
      get_window_rect(&rectWindow);
      i32 cx = rectWindow.right - rectWindow.left;
      i32 cy = rectWindow.bottom - rectWindow.top;
      ::rect rect;
      rect.left = 0;
      rect.top = 0;
      rect.bottom = cy;
      rect.right = cx;

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, RGB(84, 90, 80));

      ::draw2d::brush_pointer brush(e_create);

      brush->m_etype = ::draw2d::brush::type_null;



      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      ::rect rectClient;

      get_client_rect(rectClient);

      pgraphics->rectangle(rectClient);



      i32 iDelta = m_iDelta;
      i32 iRadius = 8;
      auto iPhase = ((((m_tickSync.elapsed()) % iDelta)) * iRadius * 2) / iDelta;

      if (iPhase == 0 && m_tickSync.timeout(2000_tick))
      {

         m_iDelta = 2000 + (::get_tick() % ((5000) * 2));

      }

      auto iStep = __i32(iPhase);

      if (iStep > iRadius)
         iStep = iRadius * 2 - iStep;

      wstring wstr;

      wstr = m_strStatus;

      i32 iRate1 = 25;

      BYTE bA;

      {

         //i32 iARange = (184 - 23) * 2;
         //i32 iAClip = iARange / 2;
         double period = 8.4; // seconds
         double frequency = 1.0 / period;
         //i32 iA = (iARange * ::get_tick() / 8000) % iARange;
         double w = 2.0 * 3.1415 * frequency;
         double t = ::get_tick() / 1000.0;


         /*if(iA < iAClip)
         bA = iA + 23;
         else
         bA = 184 * 2 - iA;*/

         bA = MIN(255, MAX(0, (BYTE)((184.0 * ((sin(w * t) + 1.0) / 2.0)) + 23.0)));



      }

      BYTE uchR;
      BYTE uchG;
      BYTE uchB;

      //graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      i32 iRate = 10;

      const i32 iRowCount = cx - cx / (iRate / 2);
      i32 iProgressCount = MAX(MIN((i32)(iRowCount * dRate), iRowCount), 0);



      i32 iBorder1 = MAX(cx / iRate1, cy / iRate1);

      ::draw2d::path_pointer pathClip1(e_create);

      ::rect rectClip1;

      rectClip1.left = rectParam.left + iBorder1;

      rectClip1.top = rectParam.top + iBorder1;

      rectClip1.right = rectClip1.left + cx - iBorder1 * 2;
      rectClip1.bottom = rectClip1.top + cy - iBorder1 * 2;

      pathClip1->begin_figure(true, ::draw2d::fill_mode_winding);

      pathClip1->add_round_rect(rectClip1, iBorder1 * 2);

      pathClip1->end_figure(true);

      //      pgraphics->replace_clip(pathClip1);



      i32 iRatePercentMillis = ((i32)(dRate * 100.0 * 1000.0)) % 1000;
      i32 iRatePercent = ((i32)(dRate * 100.0));

      wstring wstrProgress;

      {

         stringtow strProgress(wstrProgress);

         string strDecimal = ansi_string_from_i64(iRatePercentMillis);

         ansi_zero_pad(strDecimal, 3);

         strProgress = ansi_string_from_i64(iRatePercent) + "." + strDecimal + "%";

      }

      i32 iBarHeight = 23;



      i32 iBorder = 16;

      ::draw2d::path_pointer pathClip(e_create);

      ::rect rectClip;

      rectClip.left = rectParam.left + cx / iRate - iBorder;

      rectClip.top = rectParam.top + (cy - iBarHeight) / 2 - iBorder;

      rectClip.right = rectClip.left + iRowCount + iBorder * 2;
      rectClip.bottom = rectClip.top + iBarHeight + iBorder * 2;


      pathClip->begin_figure(true, ::draw2d::fill_mode_winding);

      pathClip->add_round_rect(rectClip, iBorder);

      pathClip->end_figure(true);

      //pgraphics->exclude_clip(pathClip);


      ::point pa[4];

      //Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(49, 177 + iBarHeight, 177 + iBarHeight, 177 + 19));
      //graphics2.fill_rect(pbr, rectParam.left , rectParam.top, rectParam.left + cx, rectParam.top + cy);

      //delete pbr;

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(ARGB(49, 184 + 23, 184 + 23, 184 + 19));

      i32 mcy = cy / 2;

      if (m_iHealingSurface == 1)
      {

         pgraphics->SelectObject(br);

         for (i32 x = 0; x < (cx + cy); x += 46)
         {

            pa[0].x = rectParam.left + x;

            pa[0].y = rectParam.top;


            pa[1].x = rectParam.left + x + iBarHeight;

            pa[1].y = rectParam.top;


            pa[2].x = rectParam.left + x - mcy + iBarHeight;

            pa[2].y = rectParam.top + mcy;


            pa[3].x = rectParam.left + x - mcy;

            pa[3].y = rectParam.top + mcy;


            pgraphics->fill_polygon(pa, 4);

            pa[0].x = rectParam.left + x - mcy - iBarHeight;

            pa[0].y = rectParam.top + mcy;


            pa[1].x = rectParam.left + x - mcy;

            pa[1].y = rectParam.top + mcy;


            pa[2].x = rectParam.left + x - cy;

            pa[2].y = rectParam.top + cy;


            pa[3].x = rectParam.left + x - cy - iBarHeight;

            pa[3].y = rectParam.top + cy;


            pgraphics->fill_polygon(pa, 4);


         }

      }

      rectClip.inflate(3);

      br->create_solid(ARGB(90, 90, 90, 80));

      ::rect rect1;

      rect1.left = rectParam.left + cx / iRate - 1;

      rect1.top = rectParam.top + (cy - iBarHeight) / 2 - 1;

      rect1.right = rect1.left + iRowCount + 4;
      rect1.bottom = rect1.top + iBarHeight + 2;

      pgraphics->fill_rect(rect1, br);

      /*for(iRow = 0; iRow < iProgressCount; iRow++)
      {
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 0);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rect(pbr, rectParam.left + iRow + cx / iRate , rectParam.top + (cy - iBarHeight) / 2, 1, 5);

      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 1);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rect(pbr, rectParam.left + iRow + cx / iRate , rectParam.top + (cy - iBarHeight) / 2 + 5, 1, 5);

      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 2);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rect(pbr, rectParam.left + iRow + cx / iRate , rectParam.top + (cy - iBarHeight) / 2 + 10, 1, 13);

      delete pbr;
      }
      }*/
      ::rect rect2;
      {
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         br->create_solid(ARGB(bA, uchR, uchG, uchB));
         rect2 = rect_dim(rectParam.left + cx / iRate, rectParam.top + (cy - iBarHeight) / 2, iProgressCount, 5);

         pgraphics->fill_rect(rect2, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 1);
         br->create_solid(ARGB(bA, uchR, uchG, uchB));
         rect2 = rect_dim(rectParam.left + cx / iRate, rectParam.top + (cy - iBarHeight) / 2 + 5, iProgressCount, 5);

         pgraphics->fill_rect(rect2, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 2);
         br->create_solid(ARGB(bA, uchR, uchG, uchB));
         rect2 = rect_dim(rectParam.left + cx / iRate, rectParam.top + (cy - iBarHeight) / 2 + 10, iProgressCount, 13);

         pgraphics->fill_rect(rect2, br);
      }

      i32 iOffset = 3;

      pen->create_solid(1.0, ARGB(220, 180, 180, 180));
      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, pen);

      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx / iRate - iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);


      pen->create_solid(1.0, ARGB(220, 80, 80, 80));
      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);

      pgraphics->draw_line(rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);


      iOffset = 2;
      pen->create_solid(1.0, ARGB(220, 90, 90, 90));
      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, pen);

      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx / iRate - iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);


      pen->create_solid(1.0, ARGB(220, 170, 170, 170));
      pgraphics->draw_line(rectParam.left + cx / iRate - iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);

      pgraphics->draw_line(rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy - iBarHeight) / 2 - iOffset, rectParam.left + cx - cx / iRate + iOffset, rectParam.top + (cy + iBarHeight) / 2 + iOffset, pen);



      br->create_solid(ARGB(127, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::draw2d::font_pointer f(e_create);

      f->create_pixel_font("Calibri", iBarHeight * 0.7);

      pgraphics->SelectObject(f);

      wstring wstrStatus;

      wstrStatus = wstr;
      wstrStatus = wstrStatus + unitext(" : ");
      wstrStatus = wstrStatus + wstrProgress;


      pgraphics->text_out(rectParam.left + cx / iRate - 1 + 18, rectParam.top + (cy - iBarHeight) / 2 - 1 + 1, string(wstrStatus));


   }


} // namespace hotplugin


