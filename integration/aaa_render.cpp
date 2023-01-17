#include "framework.h"
#include "render.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/graphics/draw2d/_binary_stream.h"
#include "acme/platform/node.h"
#include "apex/database/_binary_stream.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "base/user/user/impact.h"
#include <math.h>


CLASS_DECL_ACME ::color::color dk_red(); // <3 tbs


namespace app_integration
{


   render::render()
   {

      m_iDrawing = 1;

   }


   render::~render()
   {

   }


#ifdef _DEBUG


   int64_t render::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t render::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void render::initialize_simple_drawing(int iDrawing)
   {

      m_iDrawing = iDrawing;

      color32_t crText = argb(255, 55, 210, 120);

      if (m_iDrawing == 1)
      {

         crText = argb(127, 0, 127, 200);

      }
      else if (m_iDrawing == 3)
      {

         crText = argb(255, 180, 180, 180);

      }

      ::color::color color(crText);

      string strDataId;

      strDataId = m_pimpact->m_atom;

      //m_hlsText.m_dH = 0.1;
      //m_hlsText.m_dL = 0.5;
      //m_hlsText.m_dS = 0.9;

      //papplication->datastream()->set(strDataId, m_hlsText);

      if(!get_app()->datastream()->get(strDataId +".color", m_hlsText))
      {

         m_hlsText = color.get_hls();

      }

   }


   void render::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_rectangle.is_empty())
      {

         return;

      }

      if (get_app()->application_properties().m_echeckNoClientFrame != ::e_check_checked)
      {

         ::rectangle_i32 rectangle(m_rectangle);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         for (index i = 0; i < 5; i++)
         {

            pgraphics->draw_inset_rectangle(rectangle, argb(127, 225, 225, 225));

            rectangle.deflate(1, 1);

         }

      }

      if(m_iDrawing <= 3)
      {

         _001OnDraw1Through3(pgraphics);

      }
      else if(m_iDrawing == 4)
      {

         _001OnDrawBoxGradient(pgraphics);

      }
      else if (m_iDrawing == 5)
      {

         _001OnDrawCirclePath(pgraphics);

      }
      else if(m_iDrawing == 6)
      {

         _001OnDrawArcs(pgraphics, false);

      }
      else if(m_iDrawing == 7)
      {

         _001OnDrawArcs(pgraphics, true);

      }

   }


   ::e_status render::set_font(const ::string & strFont)
   {

      if (strFont.is_empty())
      {

         return error_bad_argument;

      }

      string strDataId;

      strDataId = m_pimpact->m_atom;

      get_app()->datastream()->set(strDataId + ".font_family", m_strFont1);

      m_strFont1 = strFont;

      return ::success;

   }


   ::e_status render::set_hover_font(const ::string & strHoverFont)
   {

      m_strHoverFont = strHoverFont;

      return ::success;

   }


   string render::get_font()
   {

      string strFont;

      strFont = m_strHoverFont;

      if (strFont.has_char())
      {

         return strFont;

      }

      if (m_strFont1.is_empty())
      {

         string strDataId;

         strDataId = m_pimpact->m_atom;

         if (!get_app()->datastream()->get(strDataId + ".font_family", m_strFont1)
            || m_strFont1.is_empty())
         {

            m_strFont1 = acmesystem()->m_pnode->font_name(e_font_sans_ex);

         }

      }

      return m_strFont1;

   }


   void render::draw_text(::draw2d::graphics_pointer & pgraphics)
   {
      //Text

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

      auto pbrush = __create < ::draw2d::brush >();

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pwritetext = pdraw2d->write_text();

      auto pfont1 = pwritetext->create_font();

      auto pfont2 = pwritetext->create_font();

      string strFontFamily = get_font();

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

         ::rectangle_i32 rectangleText;

         rectangleText.set_size(size);

         rectangleText.inflate(10, 10);

         rectangleText.Align(e_align_center, rectangle);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);


         if (m_iDrawing == 4)
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


   }


} // namespace simple_drawing



