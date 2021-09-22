#include "framework.h"
#include <math.h>


CLASS_DECL_AURA color32_t dk_red(); // <3 tbs


namespace simple_shader
{


   void render::_001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics)
   {

      //string strFontFamily = get_font();

      //auto ppen = __create < ::draw2d::pen > ();

      //auto pbrush = __create < ::draw2d::brush >();

      //auto pfont = __create < ::write_text::font > ();

      //if (m_iDrawing == 3)
      //{

      //   if (!m_pimage1)
      //   {

      //      m_pimage1.create();

      //      fork([this]()
      //         {

      //            m_pimage1 = get_image("matter://pat1.jpg");

      //            if (::is_ok(m_pimage1))
      //            {

      //               __construct(m_pimage2);

      //               m_pimage2->copy_from(m_pimage1);

      //               if (::is_ok(m_pimage2))
      //               {

      //                  m_pimage2->transform(image_grayscale);

      //                  m_pimpact->set_need_redraw();

      //                  m_pimpact->post_redraw();

      //               }

      //            }

      //         });

      //   }


      //}

      //rectangle_i32 rectangle;

      //int iSize = minimum(m_rectangle.width(), m_rectangle.height());

      //iSize = iSize * 3 / 4;

      //rectangle.set_size(iSize, iSize);

      //rectangle.Align(e_align_center, m_rectangle);

      //rectangle.offset_x(-iSize / 5 * 3);

      //rectangle.offset_x(iSize / 5 * m_iDrawing);
      //
      //::size_f64 size(0., 0.);
      //
      //bool bDrawText = true;
      //
      //string strTitle;
      //
      //if(bDrawText)
      //{

      //   pfont->create_pixel_font(strFontFamily, 100.0, 800);

      //   pgraphics->selectFont(font);

      //   strTitle = papplication->get_main_title();

      //   size = pgraphics->get_text_extent(strTitle);

      //   if (!size.is_empty())
      //   {

      //      if (m_iDrawing == 1)
      //      {

      //         pfont->create_pixel_font(strFontFamily, rectangle.height() * 80.0 / size.get_maximum_dimension(), 800);

      //      }
      //      else
      //      {

      //         pfont->create_pixel_font(strFontFamily, rectangle.height() * 160.0 / size.get_maximum_dimension(), 800);

      //      }

      //   }

      //   pgraphics->selectFont(font);

      //   size = pgraphics->get_text_extent(strTitle);
      //      
      //}

      //auto& echeckSimple = papplication->m_echeckSimple;

      //if (__bool(echeckSimple))
      //{

      //   ppen->create_null();

      //}
      //else
      //{

      //   ppen->create_solid(4.0, argb(255, 50, 180, 255));

      //}

      //if (m_iDrawing == 3 && ::is_ok(m_pimage1))
      //{

      //   pbrush->CreatePatternBrush(m_pimage1);

      //}
      //else
      //{

      //   if (__bool(papplication->m_echeckSimple))
      //   {

      //      pbrush->create_solid(argb(255, 255, 255, 200));

      //   }
      //   else
      //   {

      //      pbrush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

      //   }

      //}

      //pgraphics->SelectObject(pen);

      //pgraphics->SelectObject(brush);

      //pgraphics->ellipse(rectangle);

      //::rectangle_i32 rectangleText;

      //rectangleText.set_size(size);

      //rectangleText.inflate(10, 10);

      //rectangleText.Align(e_align_center, rectangle);

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //if (m_iDrawing == 1)
      //{

      //   pbrush->create_solid(m_hlsText);

      //}
      //else if (m_iDrawing == 3)
      //{

      //   if (__bool(papplication->m_echeckSimple))
      //   {

      //      pbrush->create_solid(m_hlsText);

      //   }
      //   else
      //   {

      //      if (::is_ok(m_pimage2))
      //      {

      //         pbrush->CreatePatternBrush(m_pimage2);

      //      }
      //      else
      //      {

      //         pbrush->create_solid(m_hlsText);

      //      }

      //   }

      //}
      //else
      //{

      //   if (__bool(papplication->m_echeckSimple))
      //   {

      //      pbrush->create_solid(m_hlsText);

      //   }
      //   else
      //   {

      //      pbrush->CreateLinearGradientBrush(rectangleText.top_left(), rectangleText.bottom_right(), m_hlsText, argb(255, 255, 255, 200));

      //   }

      //}

      //pgraphics->SelectObject(brush);

      //if(bDrawText)
      //{
      //
      //   pgraphics->draw_text(strTitle, rectangleText, e_align_center);
      //   
      //}

   }


} // namespace simple_shader



