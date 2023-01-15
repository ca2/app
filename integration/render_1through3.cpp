#include "framework.h"
#include "application.h"
#include "render.h"
#include <math.h>
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/context_image.h"
#include "base/user/user/impact.h"



CLASS_DECL_ACME ::color::color dk_red(); // <3 tbs


namespace app_simple_drawing
{


   void render::_001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics)
   {

      string strFontFamily = get_font();

      auto ppen = __create < ::draw2d::pen >();

      auto pbrush = __create < ::draw2d::brush >();

      if (m_iDrawing == 3)
      {

         if (!m_pimage1)
         {

            __construct(m_pimage1);

            m_pcontext->fork([this]()
            {

               auto pcontext = m_pcontext;

               auto pcontextimage = pcontext->context_image();

               auto pimage1 = pcontextimage->get_image("matter://pat1.jpg");

               if (pimage1.ok())
               {

                  ::pointer<::image> pimage2;

                  __construct(pimage2);

                  pimage2->copy_from(pimage1);

                  m_pimage1 = pimage1;

                  if (::is_set(pimage2))
                  {

                     pimage2->transform(e_image_grayscale);

                     pimage2->unmap();

                     pimage2->set_ok_flag();

                     m_pimage2 = pimage2;

                     m_pimpact->set_need_redraw();

                     m_pimpact->post_redraw();

                  }

               }

            });

         }

      }

      rectangle_i32 rectangle;

      int iSize = minimum(m_rectangle.width(), m_rectangle.height());

      iSize = iSize * 3 / 4;

      rectangle.set_size(iSize, iSize);

      rectangle.Align(e_align_center, m_rectangle);

      rectangle.offset_x(-iSize / 5 * 3);

      rectangle.offset_x(iSize / 5 * m_iDrawing);
      
      ::size_f64 size(0., 0.);
      
      bool bDrawText = true;
      
      string strTitle;
      
      auto psystem = acmesystem()->m_paurasystem;
      
      auto pdraw2d = psystem->draw2d();
      
      auto pwritetext = pdraw2d->write_text();
      
      auto pfont1 = pwritetext->create_font();
      
      auto pfont2 = pwritetext->create_font();

      if(bDrawText)
      {

         pfont1->create_pixel_font(strFontFamily, 100.0, 800);

         pgraphics->set(pfont1);

         strTitle = get_app()->application_properties().m_strSimple;

         if(strTitle.is_empty())
         {
         
            strTitle = get_app()->application_properties().m_strMainTitle;
         
         }

         size = pgraphics->get_text_extent(strTitle);

         if (!size.is_empty())
         {

            int iHeight = rectangle.height();

            double dMaxDimension = size.get_maximum_dimension();

            if (m_iDrawing == 1)
            {

               float fSize = (float) (iHeight * 80.0 / dMaxDimension);

               pfont2->create_pixel_font(strFontFamily, fSize, 800);

            }
            else
            {

               float fSize = (float) (iHeight * 160.0 / dMaxDimension);

               pfont2->create_pixel_font(strFontFamily, fSize, 800);

            }

         }

         pgraphics->set(pfont2);

         size = pgraphics->get_text_extent(strTitle);
            
      }

      auto & echeckSimple = get_app()->application_properties().m_echeckSimple;

      if (__bool(echeckSimple))
      {

         ppen->create_null();

      }
      else
      {

         ppen->create_solid(4.0, argb(255, 50, 180, 255));

      }

      if (m_iDrawing == 3 && m_pimage1.ok())
      {

         pbrush->CreatePatternBrush(m_pimage1);

      }
      else
      {

         if (__bool(get_app()->application_properties().m_echeckSimple))
         {

            pbrush->create_solid(argb(255, 255, 255, 200));

         }
         else
         {

            pbrush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

         }

      }

      pgraphics->set(ppen);

      pgraphics->set(pbrush);
      
      //pgraphics->draw_ellipse(rectangle);
      
      //pgraphics->fill_ellipse(rectangle);

      pgraphics->ellipse(rectangle);

      ::rectangle_i32 rectangleText;

      rectangleText.set_size(size);

      rectangleText.inflate(10, 10);

      rectangleText.Align(e_align_center, rectangle);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_iDrawing == 1)
      {

         pbrush->create_solid(m_hlsText);

      }
      else if (m_iDrawing == 3)
      {

         if (__bool(get_app()->application_properties().m_echeckSimple))
         {

            pbrush->create_solid(m_hlsText);

         }
         else
         {

            if (m_pimage2.ok())
            {

               pbrush->CreatePatternBrush(m_pimage2);

            }
            else
            {

               pbrush->create_solid(m_hlsText);

            }

         }

      }
      else
      {

         if (__bool(get_app()->application_properties().m_echeckSimple))
         {

            pbrush->create_solid(m_hlsText);

         }
         else
         {

            pbrush->CreateLinearGradientBrush(rectangleText.top_left(), rectangleText.bottom_right(), m_hlsText, argb(255, 255, 255, 200));

         }

      }

      pgraphics->set(pbrush);

      if(bDrawText)
      {
      
         pgraphics->draw_text(strTitle, rectangleText, e_align_center);
         
      }

   }


} // namespace simple_drawing



