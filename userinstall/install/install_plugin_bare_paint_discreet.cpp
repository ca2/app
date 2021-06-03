﻿#include "framework.h"
//#include "base/user/user.h"


#include <math.h>


namespace hotplugin
{


   void plugin::on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 & lprect)
   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      RECTANGLE_I32 rectWindow;
      get_window_rect(&rectWindow);
      i32 cx = rectWindow.right - rectWindow.left;
      i32 cy = rectWindow.bottom - rectWindow.top;
      RECTANGLE_I32 rectangle_i32;
      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.bottom = cy;
      rectangle.right = cx;

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, rgb(84, 90, 80));

      ::draw2d::brush_pointer brush(e_create);

      brush->m_etype = ::draw2d::brush::e_type_null;

      

      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      pgraphics->Rectangle(rectClient);



      i32 iDelta = m_iDelta;
      i32 iRadius = 8;
      i32 iPhase = ((((m_millisSync.elapsed()) % iDelta)) * iRadius * 2) / iDelta;

      if (iPhase == 0 && (m_millisSync.elapsed()) > 2000)
      {

         m_iDelta = 2000 + (::get_tick() % ((5000) * 2));
auto m_millisSync = ::millis::now();

      }

      i32 iStep = iPhase;

      if (iStep > iRadius)
         iStep = iRadius * 2 - iStep;

      wstring wstr;

      wstr = m_strStatus;

      i32 iRate1 = 25;

      byte bA;

      {

         //i32 iARange = (184 - 23) * 2;
         //i32 iAClip = iARange / 2;
         double period = 8.4; // seconds
         double frequency = 1.0 / period;
         //i32 iA = (iARange * ::get_tick() / 8000) % iARange;
         double w = 2.0 * 3.1415 * frequency;
         double t= ::millis::now() / 1000.0;


         /*if(iA < iAClip)
         bA = iA + 23;
         else
         bA = 184 * 2 - iA;*/

         bA = minimum(255, maximum(0, (byte)((184.0 * ((sin(w * t) + 1.0) / 2.0)) + 23.0)));



      }

      byte uchR;
      byte uchG;
      byte uchB;

      //graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      i32 iRate = 10;

      const i32 iRowCount = cx - cx / (iRate / 2);
      i32 iProgressCount = maximum(minimum((i32)(iRowCount * dRate), iRowCount), 0);



      i32 iBorder1 = maximum(cx / iRate1, cy / iRate1);

      ::draw2d::path_pointer pathClip1(e_create);

      RECTANGLE_I32 rectClip1;

      rectClip1.left = rectangle.left + iBorder1;
      rectClip1.top = rectangle.top + iBorder1;
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

      RECTANGLE_I32 rectClip;

      rectClip.left = rectangle.left + cx / iRate - iBorder;
      rectClip.top = rectangle.top + (cy - iBarHeight) / 2 - iBorder;
      rectClip.right = rectClip.left + iRowCount + iBorder * 2;
      rectClip.bottom = rectClip.top + iBarHeight + iBorder * 2;


      pathClip->begin_figure(true, ::draw2d::fill_mode_winding);

      pathClip->add_round_rect(rectClip, iBorder);

      pathClip->end_figure(true);

      //pgraphics->exclude_clip(pathClip);


      POINT_I32 pa[4];

      //Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(49, 177 + iBarHeight, 177 + iBarHeight, 177 + 19));
      //graphics2.FillRectangle(pbr, rectangle.left , rectangle.top, rectangle.left + cx, rectangle.top + cy);
      //delete pbr;

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(argb(49, 184 + 23, 184 + 23, 184 + 19));

      i32 mcy = cy / 2;

      if (m_iHealingSurface == 1)
      {

         pgraphics->SelectObject(br);

         for (i32 x = 0; x < (cx + cy); x += 46)
         {

            pa[0].x = rectangle.left + x;
            pa[0].y = rectangle.top;

            pa[1].x = rectangle.left + x + iBarHeight;
            pa[1].y = rectangle.top;

            pa[2].x = rectangle.left + x - mcy + iBarHeight;
            pa[2].y = rectangle.top + mcy;

            pa[3].x = rectangle.left + x - mcy;
            pa[3].y = rectangle.top + mcy;

            pgraphics->fill_polygon(pa, 4);

            pa[0].x = rectangle.left + x - mcy - iBarHeight;
            pa[0].y = rectangle.top + mcy;

            pa[1].x = rectangle.left + x - mcy;
            pa[1].y = rectangle.top + mcy;

            pa[2].x = rectangle.left + x - cy;
            pa[2].y = rectangle.top + cy;

            pa[3].x = rectangle.left + x - cy - iBarHeight;
            pa[3].y = rectangle.top + cy;

            pgraphics->fill_polygon(pa, 4);


         }

      }


      inflate_rect(rectClip, 3);

      //pgraphics->replace_clip(rectClip);

      br->create_solid(argb(84, 90, 90, 80));

      RECTANGLE_I32 r1;

      r1.left = rectangle.left + cx / iRate - 1;
      r1.top = rectangle.top + (cy - iBarHeight) / 2 - 1;
      r1.right = r1.left + iRowCount + 4;
      r1.bottom = r1.top + iBarHeight + 2;

      pgraphics->FillRect(r1, br);

      /*for(iRow = 0; iRow < iProgressCount; iRow++)
      {
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 0);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left + iRow + cx / iRate , rectangle.top + (cy - iBarHeight) / 2, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 1);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left + iRow + cx / iRate , rectangle.top + (cy - iBarHeight) / 2 + 5, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 2);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left + iRow + cx / iRate , rectangle.top + (cy - iBarHeight) / 2 + 10, 1, 13);
      delete pbr;
      }
      }*/
      ::rectangle_i32 rectangle;
      {
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         br->create_solid(argb(bA, uchR, uchG, uchB));
         r = rectangle_i32_dimension(rectangle.left + cx / iRate, rectangle.top + (cy - iBarHeight) / 2, iProgressCount, 5);
         pgraphics->FillRect(r, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 1);
         br->create_solid(argb(bA, uchR, uchG, uchB));
         r = rectangle_i32_dimension(rectangle.left + cx / iRate, rectangle.top + (cy - iBarHeight) / 2 + 5, iProgressCount, 5);
         pgraphics->FillRect(r, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 2);
         br->create_solid(argb(bA, uchR, uchG, uchB));
         r = rectangle_i32_dimension(rectangle.left + cx / iRate, rectangle.top + (cy - iBarHeight) / 2 + 10, iProgressCount, 13);
         pgraphics->FillRect(r, br);
      }

      i32 iOffset = 3;

      pen->create_solid(1.0, argb(220, 180, 180, 180));
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, pen);
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx / iRate - iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);

      pen->create_solid(1.0, argb(220, 80, 80, 80));
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);
      pgraphics->draw_line(rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);

      iOffset = 2;
      pen->create_solid(1.0, argb(220, 90, 90, 90));
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, pen);
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx / iRate - iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);

      pen->create_solid(1.0, argb(220, 170, 170, 170));
      pgraphics->draw_line(rectangle.left + cx / iRate - iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);
      pgraphics->draw_line(rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy - iBarHeight) / 2 - iOffset, rectangle.left + cx - cx / iRate + iOffset, rectangle.top + (cy + iBarHeight) / 2 + iOffset, pen);


      br->create_solid(argb(127, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font("Calibri", iBarHeight * 0.7);

      pgraphics->SelectObject(f);

      wstring wstrStatus;

      wstrStatus = wstr;
      wstrStatus = wstrStatus + unitext(" : ");
      wstrStatus = wstrStatus + wstrProgress;


      pgraphics->text_out(rectangle.left + cx / iRate - 1 + 18, rectangle.top + (cy - iBarHeight) / 2 - 1 + 1, string(wstrStatus));

   }


} // namespace hotplugin




