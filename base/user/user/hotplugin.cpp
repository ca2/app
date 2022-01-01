#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace hotplugin
{


   CLASS_DECL_BASE void entry_hall_windows_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const ::string & strEntryHallText)
   {

      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if (height(rectangle) < h)
      {
         top = rectangle.top;
         bottom = rectangle.bottom;
      }
      else
      {
         top = rectangle.top + height(rectangle) / 2 - h / 2;
         bottom = rectangle.top + height(rectangle) / 2 + h / 2;
      }

      if (width(rectangle) < m)
      {
         left = rectangle.left;
         right = rectangle.right;
      }
      else
      {

         left = rectangle.left + minimum(m / 2, width(rectangle) / 2);
         right = rectangle.right - minimum(m / 2, width(rectangle) / 2);

      }

      ::rectangle_i32 rectangleBar(left, top, right, bottom);

      int w =300;

      int v = (int) (::get_integral_millisecond().m_i / 2);

      int x = v % rectangleBar.width();

      ::rectangle_i32 rectangleBrick(left + x, rectangleBar.top, left + x + w, rectangleBar.bottom);

      ::rectangle_i32 rectangleDraw;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      string str(strEntryHallText);

      if (str.is_empty())
      {

         //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

         str = "Opening...";

      }

      bool bStatic = false;

      if (::str::begins_eat(str, "***"))
      {

         bStatic = true;

      }

      auto pbrush = pgraphics->__create < ::draw2d::brush >();

      pbrush->create_solid(argb(190, 49, 50, 49));

      pgraphics->fill_rectangle(rectangleBar, pbrush);

      if (!bStatic)
      {

         auto pbrushGreen = pgraphics->__create < ::draw2d::brush > ();

         pbrushGreen->create_solid(argb(190, 80, 190, 123));

         if (rectangleDraw.intersect(rectangleBar, rectangleBrick))
         {

            pgraphics->fill_rectangle(rectangleDraw, pbrushGreen);

         }

         rectangleBrick.offset(-rectangleBar.width(), 0);

         if (rectangleDraw.intersect(rectangleBar, rectangleBrick))
         {

            pgraphics->fill_rectangle(rectangleDraw, pbrushGreen);

         }

         rectangleBrick.offset(rectangleBar.width() * 2, 0);

         if (rectangleDraw.intersect(rectangleBar, rectangleBrick))
         {

            pgraphics->fill_rectangle(rectangleDraw, pbrushGreen);

         }

      }

      auto ppen = pgraphics->__create < ::draw2d::pen > ();

      ppen->create_solid(1.0f, argb(149, 150, 149, 142));

      pgraphics->draw_rectangle(rectangleBar, ppen);

      ::write_text::font_pointer f(e_create, pgraphics);

      f->create_pixel_font("Calibri", 18.0);

      rectangleBar.left += 4;

      rectangleBar.top += 5;

      pgraphics->set_text_color(argb(190, 255, 255, 255));

      pgraphics->text_out(rectangleBar.left, rectangleBar.top, str);

   }


} // namespace hotplugin


