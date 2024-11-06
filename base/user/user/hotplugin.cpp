#include "framework.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/write_text/font.h"


namespace hotplugin
{


   CLASS_DECL_BASE void entry_hall_windows_on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, const ::string & strEntryHallText)
   {

      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if (height(rectangle) < h)
      {
         top = rectangle.top();
         bottom = rectangle.bottom();
      }
      else
      {
         top = rectangle.top() + height(rectangle) / 2 - h / 2;
         bottom = rectangle.top() + height(rectangle) / 2 + h / 2;
      }

      if (width(rectangle) < m)
      {
         left = rectangle.left();
         right = rectangle.right();
      }
      else
      {

         left = rectangle.left() + minimum(m / 2, width(rectangle) / 2);
         right = rectangle.right() - minimum(m / 2, width(rectangle) / 2);

      }

      ::int_rectangle rectangleBar(left, top, right, bottom);

      int w =300;

      int v = (int) (::i64_millisecond() / 2);

      int x = v % rectangleBar.width();

      ::int_rectangle rectangleBrick(left + x, rectangleBar.top(), left + x + w, rectangleBar.bottom());

      ::int_rectangle rectangleDraw;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      string str(strEntryHallText);

      if (str.is_empty())
      {

         //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

         str = "Opening...";

      }

      bool bStatic = false;

      if (str.begins_eat("***"))
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

      ::write_text::font_pointer f(e_create, pgraphics.m_p);

      f->create_font("Calibri", 18_px);

      rectangleBar.left() += 4;

      rectangleBar.top() += 5;

      pgraphics->set_text_color(argb(190, 255, 255, 255));

      pgraphics->text_out(rectangleBar.left(), rectangleBar.top(), str);

   }


} // namespace hotplugin


