#include "framework.h"
//#include "berg/user/user.h"


#include <math.h>


namespace hotplugin
{


   void plugin::on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle &lprect)
   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      ::int_rectangle rectangleWindow;
      window_rectangle(&rectangleWindow);
      int cx = rectangleWindow.right() - rectangleWindow.left();
      int cy = rectangleWindow.bottom() - rectangleWindow.top();
      ::int_rectangle int_rectangle;
      rectangle.left() = 0;
      rectangle.top() = 0;
      rectangle.bottom() = cy;
      rectangle.right() = cx;

      auto ppen = øcreate < ::draw2d::pen > ();

      ppen->create_solid(1.0, rgb(84, 90, 80));

      auto pbrush = øcreate < ::draw2d::brush >();

      pbrush->m_etype = ::draw2d::brush::e_type_null;

      

      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      auto rectangleX = this->rectangle();

      pgraphics->Rectangle(rectangleX);



      int iDelta = m_iDelta;
      int iRadius = 8;
      int iPhase = ((((m_timeSync.elapsed()) % iDelta)) * iRadius * 2) / iDelta;

      if (iPhase == 0 && (m_timeSync.elapsed()) > 2000)
      {

         m_iDelta = 2000 + (::get_tick() % ((5000) * 2));
auto m_timeSync = ::time::now();

      }

      int iStep = iPhase;

      if (iStep > iRadius)
         iStep = iRadius * 2 - iStep;

      wstring wstr;

      wstr = m_strStatus;

      int iRate1 = 25;

      unsigned char bA;

      {

         //int iARange = (184 - 23) * 2;
         //int iAClip = iARange / 2;
         double period = 8.4; // seconds
         double frequency = 1.0 / period;
         //int iA = (iARange * ::get_tick() / 8000) % iARange;
         double w = 2.0 * 3.1415 * frequency;
         double t= ::time::now() / 1000.0;


         /*if(iA < iAClip)
         bA = iA + 23;
         else
         bA = 184 * 2 - iA;*/

         bA = minimum(255, maximum(0, (unsigned char)((184.0 * ((sin(w * t) + 1.0) / 2.0)) + 23.0)));



      }

      unsigned char uchR;
      unsigned char uchG;
      unsigned char uchB;

      //graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      int iRate = 10;

      const int iRowCount = cx - cx / (iRate / 2);
      int iProgressCount = maximum(minimum((int)(iRowCount * dRate), iRowCount), 0);



      int iBorder1 = maximum(cx / iRate1, cy / iRate1);

      auto ppathClip1 = øcreate < ::draw2d::path >();

      ::int_rectangle rectangleClip1;

      rectangleClip1.left() = rectangle.left() + iBorder1;
      rectangleClip1.top() = rectangle.top() + iBorder1;
      rectangleClip1.right() = rectangleClip1.left() + cx - iBorder1 * 2;
      rectangleClip1.bottom() = rectangleClip1.top() + cy - iBorder1 * 2;

      ppathClip1->begin_figure(true, ::draw2d::e_fill_mode_winding);

      ppathClip1->add_round_rect(rectangleClip1, iBorder1 * 2);

      ppathClip1->end_figure(true);

      //      pgraphics->replace_clip(pathClip1);



      int iRatePercentMillis = ((int)(dRate * 100.0 * 1000.0)) % 1000;
      int iRatePercent = ((int)(dRate * 100.0));

      wstring wstrProgress;

      {

         stringtow strProgress(wstrProgress);

         string strDecimal = ansi_string_from_long_long(iRatePercentMillis);

         ansi_zero_pad(strDecimal, 3);

         strProgress = ansi_string_from_long_long(iRatePercent) + "." + strDecimal + "%";

      }

      int iBarHeight = 23;



      int iBorder = 16;

      auto ppathClip = øcreate < ::draw2d::path >();

      ::int_rectangle rectangleClip;

      rectangleClip.left() = rectangle.left() + cx / iRate - iBorder;
      rectangleClip.top() = rectangle.top() + (cy - iBarHeight) / 2 - iBorder;
      rectangleClip.right() = rectangleClip.left() + iRowCount + iBorder * 2;
      rectangleClip.bottom() = rectangleClip.top() + iBarHeight + iBorder * 2;


      ppathClip->begin_figure(true, ::draw2d::e_fill_mode_winding);

      ppathClip->add_round_rect(rectangleClip, iBorder);

      ppathClip->end_figure(true);

      //pgraphics->exclude_clip(pathClip);


      ::int_point pa[4];

      //Gdiplus::SolidBrush * pbr = normal_new Gdiplus::SolidBrush(Gdiplus::Color(49, 177 + iBarHeight, 177 + iBarHeight, 177 + 19));
      //graphics2.FillRectangle(pbr, rectangle.left() , rectangle.top(), rectangle.left() + cx, rectangle.top() + cy);
      //delete pbr;

      auto pbrush = øcreate < ::draw2d::brush > ();

      pbrush->create_solid(argb(49, 184 + 23, 184 + 23, 184 + 19));

      int mcy = cy / 2;

      if (m_iHealingSurface == 1)
      {

         pgraphics->SelectObject(br);

         for (int x = 0; x < (cx + cy); x += 46)
         {

            pa[0].x() = rectangle.left() + x;
            pa[0].y() = rectangle.top();

            pa[1].x() = rectangle.left() + x + iBarHeight;
            pa[1].y() = rectangle.top();

            pa[2].x() = rectangle.left() + x - mcy + iBarHeight;
            pa[2].y() = rectangle.top() + mcy;

            pa[3].x() = rectangle.left() + x - mcy;
            pa[3].y() = rectangle.top() + mcy;

            pgraphics->fill_polygon(pa, 4);

            pa[0].x() = rectangle.left() + x - mcy - iBarHeight;
            pa[0].y() = rectangle.top() + mcy;

            pa[1].x() = rectangle.left() + x - mcy;
            pa[1].y() = rectangle.top() + mcy;

            pa[2].x() = rectangle.left() + x - cy;
            pa[2].y() = rectangle.top() + cy;

            pa[3].x() = rectangle.left() + x - cy - iBarHeight;
            pa[3].y() = rectangle.top() + cy;

            pgraphics->fill_polygon(pa, 4);


         }

      }


      inflate_rect(rectangleClip, 3);

      //pgraphics->replace_clip(rectangleClip);

      pbrush->create_solid(argb(84, 90, 90, 80));

      ::int_rectangle r1;

      r1.left() = rectangle.left() + cx / iRate - 1;
      r1.top() = rectangle.top() + (cy - iBarHeight) / 2 - 1;
      r1.right() = r1.left() + iRowCount + 4;
      r1.bottom() = r1.top() + iBarHeight + 2;

      pgraphics->FillRect(r1, br);

      /*for(iRow = 0; iRow < iProgressCount; iRow++)
      {
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 0);
      Gdiplus::SolidBrush * pbr = normal_new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left() + iRow + cx / iRate , rectangle.top() + (cy - iBarHeight) / 2, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 1);
      Gdiplus::SolidBrush * pbr = normal_new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left() + iRow + cx / iRate , rectangle.top() + (cy - iBarHeight) / 2 + 5, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 2);
      Gdiplus::SolidBrush * pbr = normal_new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, rectangle.left() + iRow + cx / iRate , rectangle.top() + (cy - iBarHeight) / 2 + 10, 1, 13);
      delete pbr;
      }
      }*/
      ::int_rectangle rectangle;
      {
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         r = int_rectangle_dimension(rectangle.left() + cx / iRate, rectangle.top() + (cy - iBarHeight) / 2, iProgressCount, 5);
         pgraphics->FillRect(r, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 1);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         r = int_rectangle_dimension(rectangle.left() + cx / iRate, rectangle.top() + (cy - iBarHeight) / 2 + 5, iProgressCount, 5);
         pgraphics->FillRect(r, br);
      }
      {
         get_progress_color(uchR, uchG, uchB, dRate, 2);
         pbrush->create_solid(argb(bA, uchR, uchG, uchB));
         r = int_rectangle_dimension(rectangle.left() + cx / iRate, rectangle.top() + (cy - iBarHeight) / 2 + 10, iProgressCount, 13);
         pgraphics->FillRect(r, br);
      }

      int iOffset = 3;

      ppen->create_solid(1.0, argb(220, 180, 180, 180));
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, ppen);
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);

      ppen->create_solid(1.0, argb(220, 80, 80, 80));
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);
      pgraphics->line(rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);

      iOffset = 2;
      ppen->create_solid(1.0, argb(220, 90, 90, 90));
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, ppen);
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);

      ppen->create_solid(1.0, argb(220, 170, 170, 170));
      pgraphics->line(rectangle.left() + cx / iRate - iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);
      pgraphics->line(rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy - iBarHeight) / 2 - iOffset, rectangle.left() + cx - cx / iRate + iOffset, rectangle.top() + (cy + iBarHeight) / 2 + iOffset, ppen);


      pbrush->create_solid(argb(127, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font("Calibri", iBarHeight * 0.7);

      pgraphics->SelectObject(f);

      wstring wstrStatus;

      wstrStatus = wstr;
      wstrStatus = wstrStatus + unitext(" : ");
      wstrStatus = wstrStatus + wstrProgress;


      pgraphics->text_out(rectangle.left() + cx / iRate - 1 + 18, rectangle.top() + (cy - iBarHeight) / 2 - 1 + 1, string(wstrStatus));

   }


} // namespace hotplugin




