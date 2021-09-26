#include "framework.h"
//#include "base/user/user.h"


#ifdef 


namespace hotplugin
{


   void plugin::on_bare_paint_full_screen(::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 & lprect)
   {

      double dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      RECTANGLE_I32 rectangleWindow;

      get_window_rect(&rectangleWindow);

      i32 cx = rectangleWindow.right - rectangleWindow.left;
      i32 cy = rectangleWindow.bottom - rectangleWindow.top;

      RECTANGLE_I32 rectangle_i32;

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.bottom = cy;
      rectangle.right = cx;

      string str;

      str = m_strStatus;

      string strProgress;

      strProgress.Format("%0.3f%%", dRate * 100.0);

      auto pbrush = __create < ::draw2d::brush > ();

      

      {

         byte uchR, uchG, uchB;
         ::rectangle_i32 rectangle;
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         pbrush->create_solid(argb(255, uchR, uchG, uchB));
         r = rectangle_i32_dimension(rectangle.left, rectangle.top, cx, cy);
         pgraphics->FillRect(r, br);

      }

      pbrush->create_solid(argb(255, 255, 255, 255));

      pgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 49);

      pgraphics->SelectObject(f);

      string strStatus;

      strStatus = str;

      //on_paint_progress(pgraphics, m_rectangle);

      pgraphics->text_out(rectangle.left + 84, rectangle.top + 84, strStatus);

      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 90, true);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectangle.left + 84, (i32)(rectangle.top + 133 + 49 * 0.2), strProgress);

      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 23);

      pgraphics->SelectObject(f);

      pgraphics->text_out(rectangle.left + 84, (i32)(rectangle.top + 133 + 49 * 0.2 + 133 * 0.2), m_strStatus2);

   }


} // namespace hotplugin


#endif



