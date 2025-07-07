#include "framework.h"
#include <math.h>


CLASS_DECL_AURA color32_t dk_red(); // <3 tbs


namespace simple_shader
{


   void render::draw_arc(::draw2d::graphics_pointer & pgraphics, int_rectangle& r, double dStart, double dAngle, bool bPath)
   {

      auto pfont = __øcreate < ::write_text::font > ();

      string strFontFamily = get_font();

      pfont->create_pixel_font(strFontFamily, 14.0, FW_LIGHT);

      ::color::color color(m_hlsText);

      pgraphics->set_text_color(color);

      pgraphics->set(pfont);

      string str1;

      str1.format("Start: %0.0f", dStart);

      string str2;

      str2.format("Angle: %0.0f", dAngle);

      auto size1 = pgraphics->get_text_extent(str1);

      size1.cx() += 32;

      size1.cy() += 4;

      auto size2 = pgraphics->get_text_extent(str2);

      size2.cx() += 32;

      size2.cy() += 4;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_size size;

      size = size1.maximum(size2);

      ::int_rectangle rectangleBack(r);

      rectangleBack.deflate(2, 2);

      rectangleBack.bottom() = rectangleBack.top() + size.cy() * 2 + 4 * 3;

      pgraphics->fill_rectangle(rectangleBack, argb(127, 80, 80, 80));

      pgraphics->text_out(rectangleBack.left() + 4, rectangleBack.top() + 4, str1);

      pgraphics->text_out(rectangleBack.left() + 4, rectangleBack.top() + size.cy() + 8, str2);

      auto ppen = __øcreate < ::draw2d::pen > ();

      auto pbrush = __øcreate < ::draw2d::brush >();

      pbrush->create_null();

      pgraphics->set(pbrush);

      if (__bool(papp->m_echeckSimple))
      {

         if (dAngle < 0.0)
         {

            ppen->create_solid(4.0, argb(255, 120, 120, 120));

         }
         else
         {

            ppen->create_solid(4.0, argb(255, 255, 255, 255));

         }

      }
      else
      {

         if (dAngle < 0.0)
         {

            if (bPath)
            {

               ppen->create_solid(4.0, dk_red());

            }
            else
            {

               ppen->create_solid(4.0, argb(255, 255, 230, 155));

            }

         }
         else
         {

            if (bPath)
            {

               ppen->create_solid(4.0, argb(255, 255, 255, 255));

            }
            else
            {

               ppen->create_solid(4.0, argb(255, 50, 180, 255));

            }

         }

      }

      pgraphics->set(ppen);

      pgraphics->arc(r, dStart, dAngle);


   }


   void render::_001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      double_array daStart;

      double_array daAngle;

      daStart.add(0.0);
      daAngle.add(100.0);

      daStart.add(90.0);
      daAngle.add(100.0);

      daStart.add(180.0);
      daAngle.add(100.0);

      daStart.add(270.0);
      daAngle.add(100.0);

      daStart.add(-90.0);
      daAngle.add(100.0);

      daStart.add(-180.0);
      daAngle.add(100.0);

      daStart.add(-270.0);
      daAngle.add(100.0);

      daStart.add(45.0);
      daAngle.add(100.0);


      daStart.add(0.0);
      daAngle.add(-100.0);

      daStart.add(90.0);
      daAngle.add(-100.0);

      daStart.add(180.0);
      daAngle.add(-100.0);

      daStart.add(270.0);
      daAngle.add(-100.0);

      daStart.add(-90.0);
      daAngle.add(-100.0);

      daStart.add(-180.0);
      daAngle.add(-100.0);

      daStart.add(-270.0);
      daAngle.add(-100.0);

      daStart.add(45.0);
      daAngle.add(-100.0);

      ::int_rectangle rClient(m_rectangle);

      if (__bool(papp->m_echeckSimple))
      {

         pgraphics->fill_rectangle(rClient, argb(127, 192, 192, 192));

      }
      else
      {

         pgraphics->fill_rectangle(rClient, argb(127, 120, 120, 120));

      }

      int iColumnCount = 8;

      int_rectangle r;

      r.top() = 0;

      r.left() = 0;

      r.bottom() = rClient.center().y();

      int i = 0;

      int iColumnWidth = rClient.width() / iColumnCount;

      for (i = 0; i < iColumnCount && i < daStart.get_size(); i++)
      {

         r.right() = r.left() + iColumnWidth;

         draw_arc(pgraphics, r, daStart[i], daAngle[i], bPath);

         r.left() = r.right();

      }

      r.top() = r.bottom();

      r.left() = 0;

      r.bottom() = rClient.bottom();

      for (; i < iColumnCount * 2 && i < daStart.get_size(); i++)
      {

         r.right() = r.left() + iColumnWidth;

         draw_arc(pgraphics, r, daStart[i], daAngle[i], bPath);

         r.left() = r.right();

      }

   }


} // namespace simple_shader



