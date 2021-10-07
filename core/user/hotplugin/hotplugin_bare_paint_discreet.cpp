#include "framework.h"



#include <math.h>


namespace hotplugin
{


   void plugin::on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)

   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      ::rectangle_i32 rectangleWindow;
      get_window_rect(&rectangleWindow);
      i32 cx = rectangleWindow.right - rectangleWindow.left;
      i32 cy = rectangleWindow.bottom - rectangleWindow.top;
      ::rectangle_i32 rectangle;
      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.bottom = cy;
      rectangle.right = cx;

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, rgb(84, 90, 80));

      auto pbrush = __create < ::draw2d::brush >();

      pbrush->m_etype = ::draw2d::brush::e_type_null;



      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      pgraphics->rectangle(rectangleClient);



      i32 iDelta = m_iDelta;
      i32 iRadius = 8;
      auto iPhase = ((((m_durationSync.elapsed()) % iDelta)) * iRadius * 2) / iDelta;

      if (iPhase == 0 && m_durationSync.timeout(2000_tick))
      {

         m_iDelta = 2000 + (::get_tick() % ((5000) * 2));

      }

      auto iStep = __i32(iPhase);

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
         double t= ::duration::now() / 1000.0;


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

      auto ppathClip1 = __create < ::draw2d::path >();

      ::rectangle_i32 rectangleClip1;

      rectangleClip1.left = rectangleParam.left + iBorder1;

      rectangleClip1.top = rectangleParam.top + iBorder1;

      rectangleClip1.right = rectangleClip1.left + cx - iBorder1 * 2;
      rectangleClip1.bottom = rectangleClip1.top + cy - iBorder1 * 2;

      ppathClip1->begin_figure(true, ::draw2d::fill_mode_winding);

      ppathClip1->add_round_rect(rectangleClip1, iBorder1 * 2);

      ppathClip1->end_figure(true);

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

      auto ppathClip = __create < ::draw2d::path >();

      ::rectangle_i32 rectangleClip;

      rectangleClip.left = rectangleParam.left + cx / iRate - iBorder;

      rectangleClip.top = rectangleParam.top + (cy - iBarHeight) / 2 - iBorder;

      rectangleClip.right = rectangleClip.left + iRowCount + iBorder * 2;
      rectangleClip.bottom = rectangleClip.top + iBarHeight + iBorder * 2;


      ppathClip->begin_figure(true, ::draw2d::fill_mode_winding);

      ppathClip->add_round_rect(rectangleClip, iBorder);

      ppathClip->end_figure(true);

      //pgraphics->exclude_clip(pathClip);


      ::point_i32 pa[4];

      //Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(49, 177 + iBarHeight, 177 + iBarHeight, 177 + 19));
      //graphics2.fill_rectangle(pbr, rectangleParam.left , rectangleParam.top, rectangleParam.left + cx, rectangleParam.top + cy);

      //delete pbr;

      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->create_solid(argb(49, 184 + 23, 184 + 23, 184 + 19));

      i32 mcy = cy / 2;

      if (m_iHealingSurface == 1)
      {

         pgraphics->SelectObject(br);

         for (i32 x = 0; x < (cx + cy); x += 46)
         {

            pa[0].x = rectangleParam.left + x;

            pa[0].y = rectangleParam.top;


            pa[1].x = rectangleParam.left + x + iBarHeight;

            pa[1].y = rectangleParam.top;


            pa[2].x = rectangleParam.left + x - mcy + iBarHeight;

            pa[2].y = rectangleParam.top + mcy;


            pa[3].x = rectangleParam.left + x - mcy;

            pa[3].y = rectangleParam.top + mcy;


            pgraphics->fill_polygon(pa, 4);

            pa[0].x = rectangleParam.left + x - mcy - iBarHeight;

            pa[0].y = rectangleParam.top + mcy;


            pa[1].x = rectangleParam.left + x - mcy;

            pa[1].y = rectangleParam.top + mcy;


            pa[2].x = rectangleParam.left + x - cy;

            pa[2].y = rectangleParam.top + cy;


            pa[3].x = rectangleParam.left + x - cy - iBarHeight;

            pa[3].y = rectangleParam.top + cy;


            pgraphics->fill_polygon(pa, 4);


         }

      }

      rectangleClip.inflate(3);

      pbrush->create_solid(argb(90, 90, 90, 80));

      ::rectangle_i32 rect1;

      rect1.left = rectangleParam.left + cx / iRate - 1;

      rect1.top = rectangleParam.top + (cy - iBarHeight) / 2 - 1;

      rect1.right = rect1.left + iRowCount + 4;
      rect1.bottom = rect1.top + iBarHeight + 2;

      pgraphics->fill_rectangle(rect1, br);

      /*for(iRow = 0; iRow < iProgressCount; iRow++)
      {
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 0);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rectangle(pbr, rectangleParam.left + iRow + cx / iRate , rectangleParam.top + (cy - iBarHeight) / 2, 1, 5);

      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 1);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rectangle(pbr, rectangleParam.left + iRow + cx / iRate , rectangleParam.top + (cy - iBarHeight) / 2 + 5, 1, 5);

      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 2);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.fill_rectangle(pbr, rectangleParam.left + iRow + cx / iRate , rectangleParam.top + (cy - iBarHeight) / 2 + 10, 1, 13);

      delete pbr;
      }
      }*/
      ::rectangle_i32 rect2;
      {
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         rect2 = rectangle_i32_dimension(rectangleParam.left + cx / iRate, rectangleParam.top + (cy - iBarHeight) / 2, iProgressCount, 5);

         pgraphics->fill_rectangle(rect2, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 1);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         rect2 = rectangle_i32_dimension(rectangleParam.left + cx / iRate, rectangleParam.top + (cy - iBarHeight) / 2 + 5, iProgressCount, 5);

         pgraphics->fill_rectangle(rect2, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 2);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         rect2 = rectangle_i32_dimension(rectangleParam.left + cx / iRate, rectangleParam.top + (cy - iBarHeight) / 2 + 10, iProgressCount, 13);

         pgraphics->fill_rectangle(rect2, br);
      }

      i32 iOffset = 3;

      ppen->create_solid(1.0, argb(220, 180, 180, 180));
      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, ppen);

      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);


      ppen->create_solid(1.0, argb(220, 80, 80, 80));
      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);

      pgraphics->draw_line(rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);


      iOffset = 2;
      ppen->create_solid(1.0, argb(220, 90, 90, 90));
      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, ppen);

      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);


      ppen->create_solid(1.0, argb(220, 170, 170, 170));
      pgraphics->draw_line(rectangleParam.left + cx / iRate - iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);

      pgraphics->draw_line(rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy - iBarHeight) / 2 - iOffset, rectangleParam.left + cx - cx / iRate + iOffset, rectangleParam.top + (cy + iBarHeight) / 2 + iOffset, ppen);



      pbrush->create_solid(argb(127, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font("Calibri", iBarHeight * 0.7);

      pgraphics->SelectObject(f);

      wstring wstrStatus;

      wstrStatus = wstr;
      wstrStatus = wstrStatus + unitext(" : ");
      wstrStatus = wstrStatus + wstrProgress;


      pgraphics->text_out(rectangleParam.left + cx / iRate - 1 + 18, rectangleParam.top + (cy - iBarHeight) / 2 - 1 + 1, string(wstrStatus));


   }


} // namespace hotplugin


