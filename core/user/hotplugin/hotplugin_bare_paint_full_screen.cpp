#include "framework.h"



namespace hotplugin
{


   void plugin::on_bare_paint_full_screen(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangleParam)
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

      string str;

      str = m_strStatus;

      string strProgress;

      strProgress.format("%0.3f%%", dRate * 100.0);

      auto pbrush = __create < ::draw2d::brush > ();



      {

         byte uchR, uchG, uchB;
         ::rectangle_i32 rectangleDraw;
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         pbrush->create_solid(argb(255, uchR, uchG, uchB));
         rectangleDraw = rectangle_i32_dimension(rectangle.left, rectangle.top, cx, cy);

         pgraphics->fill_rectangle(rectangleDraw, br);

      }

      pbrush->create_solid(argb(255, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 50);

      pgraphics->SelectObject(f);

      string strStatus;

      strStatus = str;

      //on_paint_progress(pgraphics, m_rectangle);

      pgraphics->text_out(rectangleParam.left + 80, rectangleParam.top + 80, strStatus);


      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 80, true);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectangleParam.left + 80, (i32)(rectangleParam.top + 120 + 50 * 0.2), strProgress);


      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 30);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectangleParam.left + 80, (i32)(rectangleParam.top + 120 + 50 * 0.2 + 120 * 0.2), m_strStatus2);


   }


} // namespace hotplugin


