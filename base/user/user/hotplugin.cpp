#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace hotplugin
{


   CLASS_DECL_BASE void entry_hall_windows_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const string & strEntryHallText)
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

         left = rectangle.left + min(m / 2, width(rectangle) / 2);
         right = rectangle.right - min(m / 2, width(rectangle) / 2);

      }

      ::rectangle_i32 rectBar(left, top, right, bottom);

      int w = 284;

      int v = (int) (::get_millis() * 484 / 1000);

      int x = v % rectBar.width();

      ::rectangle_i32 rectBrick(left + x, rectBar.top, left + x + w, rectBar.bottom);

      ::rectangle_i32 rectDraw;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

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

      ::draw2d::brush_pointer brush(e_create);

      brush->create_solid(ARGB(190, 49, 50, 49));

      pgraphics->fill_rect(rectBar, brush);

      if (!bStatic)
      {

         ::draw2d::brush_pointer brushGreen(e_create);

         brushGreen->create_solid(ARGB(190, 80, 190, 123));

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

         rectBrick.offset(-rectBar.width(), 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

         rectBrick.offset(rectBar.width() * 2, 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

      }

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0f, ARGB(149, 150, 149, 142));

      pgraphics->draw_rect(rectBar, pen);

      ::draw2d::font_pointer f(e_create);

      f->create_pixel_font("Calibri", 18.0);

      rectBar.left += 4;

      rectBar.top += 5;

      pgraphics->set_text_color(ARGB(190, 255, 255, 255));

      pgraphics->text_out(rectBar.left, rectBar.top, str);

   }


} // namespace hotplugin


