#include "platform.h"



namespace hotplugin
{


   void plugin::on_bare_paint_full_screen(::draw2d::graphics_pointer & pdraw2dgraphics,const ::i32_rectangle & rectangleParam)
   {

      ::f64 dRate = get_progress_rate();

      if (dRate <= 0.0)
      {

         return;

      }

      ::i32_rectangle rectangleWindow;

      window_rectangle(&rectangleWindow);

      ::i32 cx = rectangleWindow.right - rectangleWindow.left;
      ::i32 cy = rectangleWindow.bottom - rectangleWindow.top;

      ::i32_rectangle rectangle;

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.bottom = cy;
      rectangle.right = cx;

      string str;

      str = m_strStatus;

      string strProgress;

      strProgress.formatf("%0.3f%%", dRate * 100.0);

      auto pbrush = createø < ::draw2d::brush > ();



      {

         ::u8 uchR, uchG, uchB;
         ::i32_rectangle rectangleDraw;
         get_progress_color(uchR, uchG, uchB, dRate, 0);
         pbrush->create_solid(argb(255, uchR, uchG, uchB));
         rectangleDraw = i32_rectangle_dimension(rectangle.left, rectangle.top, cx, cy);

         pdraw2dgraphics->fill_rectangle(rectangleDraw, br);

      }

      pbrush->create_solid(argb(255, 255, 255, 255));

      pdraw2dgraphics->SelectObject(br);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 50);

      pdraw2dgraphics->SelectObject(f);

      string strStatus;

      strStatus = str;

      //on_paint_progress(pdraw2dgraphics, m_rectangle);

      pdraw2dgraphics->text_out(rectangleParam.left + 80, rectangleParam.top + 80, strStatus);


      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 80, true);

      pdraw2dgraphics->SelectObject(f);

      pdraw2dgraphics->text_out(rectangleParam.left + 80, (::i32)(rectangleParam.top + 120 + 50 * 0.2), strProgress);


      f->create_pixel_font(pnode->font_name(e_font_sans_fx), 30);

      pdraw2dgraphics->SelectObject(f);

      pdraw2dgraphics->text_out(rectangleParam.left + 80, (::i32)(rectangleParam.top + 120 + 50 * 0.2 + 120 * 0.2), m_strStatus2);


   }


} // namespace hotplugin


