#include "framework.h"



namespace hotplugin
{


   void plugin::on_bare_paint_full_screen(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam)
   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      ::rectangle_i32 rectWindow;

      get_window_rect(&rectWindow);

      i32 cx = rectWindow.right - rectWindow.left;
      i32 cy = rectWindow.bottom - rectWindow.top;

      ::rectangle_i32 rectangle;

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.bottom = cy;
      rectangle.right = cx;

      string str;

      str = m_strStatus;

      string strProgress;

      strProgress.Format("%0.3f%%", dRate * 100.0);

      ::draw2d::brush_pointer br(e_create);



      {

         byte uchR, uchG, uchB;
         ::rectangle_i32 rectDraw;
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         br->create_solid(argb(255, uchR, uchG, uchB));
         rectDraw = rect_dim(rectangle.left, rectangle.top, cx, cy);

         pgraphics->fill_rect(rectDraw, br);

      }

      br->create_solid(argb(255, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::draw2d::font_pointer f(e_create);

      f->create_pixel_font(os_font_name(e_font_sans_fx), 50);

      pgraphics->SelectObject(f);

      string strStatus;

      strStatus = str;

      //on_paint_progress(pgraphics, m_rectangle);

      pgraphics->text_out(rectParam.left + 80, rectParam.top + 80, strStatus);


      f->create_pixel_font(os_font_name(e_font_sans_fx), 80, true);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectParam.left + 80, (i32)(rectParam.top + 120 + 50 * 0.2), strProgress);


      f->create_pixel_font(os_font_name(e_font_sans_fx), 30);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectParam.left + 80, (i32)(rectParam.top + 120 + 50 * 0.2 + 120 * 0.2), m_strStatus2);


   }


} // namespace hotplugin


