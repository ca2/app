#include "framework.h"
#include "render.h"
#include "application.h"
#include "acme/parallelization/single_lock.h"
#include "aura/graphics/gpu/shader.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/gpu/context.h"
#include "aura/graphics/gpu/program.h"
#include "aura/graphics/gpu/cpu_buffer.h"
#include <math.h>
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"


CLASS_DECL_ACME ::color::color dk_red(); // <3ThomasBorregaardSorensen!!


void image_gl_set(::image::image* pimage);


namespace app_shader
{


   render::render()
   {

      m_bUpdateShader = false;

   }


   render::~render()
   {

   }




#ifdef _DEBUG


   long long render::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   long long render::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_rectangle.area() <= 0)
      {

         return;

      }

      if (m_pgpucontext)
      {

         m_pgpucontext->resize_offscreen_buffer(m_rectangle.size());

      }
      
   }


   void render::defer_load_fragment(const ::string & pszPathPrefix)
   {

      if (string(pszPathPrefix) == "default")
      {

         m_strProjection.empty();

         m_strFragment.empty();

         defer_update_shader();

         return;

      }

      //auto papp = get_app();

      //auto pcontext = ::object::m_pgpucontext;

      //directory()->ls_pattern(listing, "dropbox://shader/simple shader/", { "*.frag" });

      //for (auto& path : listing)
      //{

      //   if (path.name().case_insensitive_begins(pszPathPrefix))
      //   {

      m_strFragment = m_pgpucontext->load_fragment(pszPathPrefix, m_eshadersource);

      //      break;

      //   }

      //}

   }


   void render::update_shader()
   {

      m_bUpdateShader = true;

      //return ::success;

   }


   void render::defer_update_shader()
   {

      if (m_bUpdateShader)
      {

         m_bUpdateShader = false;

         defer_load_fragment(m_strShaderPath);

         _update_shader();

      }

   }


   void render::_update_shader()
   {

      //::e_status estatus = ::success_none;

      if(m_strProjection.is_empty())
      {

         m_strProjection = m_pgpucontext->_001GetIntroProjection();

      }

      if(m_strFragment.is_empty())
      {

         m_strFragment = m_pgpucontext->_001GetIntroFragment();

      }

      color32_t crText = argb(255, 55, 210, 120);

      string strProjection = m_strProjection;

      string strFragment = m_strFragment;

      ::gpu::context_lock lock(m_pgpucontext);

      m_pgpucontext->make_current();

      if (!m_pgpuprogram)
      {

         //estatus = 
         
         __øconstruct(m_pgpuprogram);

      }

      m_pgpucontext->translate_shader(strProjection);

      m_pgpucontext->translate_shader(strFragment);

      //if (::succeeded(estatus))
      //{

         //estatus = 
         m_pgpuprogram->create_program(this, strProjection, strFragment);

      //}

      ::color::color color(crText);

      //string strDataId;

      //strDataId = m_pinteraction->id();

      m_pgpucontext->m_pprogram = m_pgpuprogram;

      m_pgpucontext->draw();

      //unsigned int texture1;

      //glGenTextures(1, &texture1);

      ////            glActiveTexture(GL_TEXTURE0);

      //glBindTexture(GL_TEXTURE_2D, texture1);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      m_timeStart.Now();

      //return ::success;

   }


   void render::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      
      if(!m_pgpucontext)
      {
         
         return;
         
      }
      
      if(!m_pgpucontext->m_bCreated)
      {
       
         return;
         
      }
      
      m_pgpucontext->send([this]
                                    {
         
         ::gpu::context_lock lock(m_pgpucontext);
         
         defer_update_shader();
         
         if (m_pgpucontext &&
             ::is_set(m_pgpucontext->m_pprogram) &&
             m_pgpucontext->m_pcpubuffer && m_pgpucontext->m_pcpubuffer->m_pixmap.is_ok())
         {
            
            {
               
               //::gpu::context_lock lock(m_pgpucontext);
               
               m_pgpucontext->make_current();
               
               m_pgpucontext->start_drawing();
               
               {
                  
                  //::pointer<::aura::session>psession = get_session();
                  
                  //auto puser = user();
                  
                  auto pointCursor = m_puserinteraction->mouse_cursor_position();
                  
                  float x = (float)pointCursor.x();
                  
                  float y = (float)pointCursor.y();
                  
                  m_pgpucontext->m_pprogram->m_pshader->setVec2("mouse", x, y);
                  m_pgpucontext->m_pprogram->m_pshader->setVec2("iMouse", x, y);
                  
               }
               
               {
                  
                  float cx = (float)m_pgpucontext->m_pcpubuffer->m_pixmap.width();
                  
                  float cy = (float)m_pgpucontext->m_pcpubuffer->m_pixmap.height();
                  
                  m_pgpucontext->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
                  m_pgpucontext->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);
                  
               }
               
               {
                  
                  auto dTime = m_timeStart.elapsed().floating_second();
                  
                  float time = (float)dTime;
                  
                  m_pgpucontext->m_pprogram->m_pshader->setFloat("time", time);
                  m_pgpucontext->m_pprogram->m_pshader->setFloat("iTime", time);
                  
               }

               m_pgpucontext->render();
               
               read_to_cpu_buffer();

            }
            
            
            
         }
      }
                                    );

         
         {
            
            to_draw2d_graphics(pgraphics);
            
            
         };
      ::int_rectangle rectangle;


      //rectangle.left() = rectangle.right() - 48;
      //rectangle.top() = rectangle.bottom() - 48;

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //pgraphics->fill_rectangle(rectangle, argb(128, 128, 128, 128));

      //_001OnDraw1Through3(pgraphics);

      _001OnDrawLabel(pgraphics);

      _001OnDrawError(pgraphics);

   }


   void render::_001OnDrawLabel(::draw2d::graphics_pointer & pgraphics)
   {

      auto pathShader = m_strShaderPath;

      auto strLabel = ::file::path(pathShader).name();

      auto pinteraction = pgraphics->m_puserinteraction;

      ::color::color colorBackground = argb(127, 255, 255, 255);

      if (::is_set(pinteraction))
      {

         auto pstyle = pinteraction->get_style(pgraphics);

         colorBackground = pinteraction->get_color(pstyle, ::e_element_background);

      }

      if(m_strLastLabel != strLabel
         || m_colorLastLabelBackground != colorBackground)
      {

         m_strLastLabel = strLabel;

         if (strLabel.has_character())
         {

            colorBackground.m_uchOpacity = 128;

            ::draw2d::brush_pointer pbrush;

            __øconstruct(pbrush);

            pbrush->create_solid(colorBackground);

            ::write_text::font_pointer pfont;

            __øconstruct(pfont);

            pfont->create_font(e_font_sans_ui, 12_pt);

            __defer_construct(m_pimageLabel);

            if (m_pimageLabel->g() == nullptr)
            {

               m_pimageLabel->create({ 16, 16 });

            }

            auto pgraphicsLabel = m_pimageLabel->g();

            pgraphicsLabel->set(pfont);

            auto size = pgraphicsLabel->get_text_extent(strLabel);

            ::int_rectangle rect(::double_point(0, 0), size);

            rect.inflate(4);

            rect.move_to(0, 0);

            m_pimageLabel->create(rect.size());

            pgraphicsLabel = m_pimageLabel->g();

            pgraphicsLabel->set(pfont);

            pgraphicsLabel->set_alpha_mode(::draw2d::e_alpha_mode_set);

            pgraphicsLabel->set(pbrush);

            pgraphicsLabel->fill_rectangle(rect);

            pgraphicsLabel->set_text_color({});

            pgraphicsLabel->text_out({ 4,4 }, strLabel);

         }
         else
         {

            m_pimageLabel.release();

         }

      }

      if(m_pimageLabel.ok())
      {

         ::image::image_source imagesource(m_pimageLabel);

         double_rectangle rectangle(double_point(10, 10), m_pimageLabel->size());

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw(imagedrawing);

      }

   }


   void render::_001OnDrawError(::draw2d::graphics_pointer & pgraphics)
   {
      
      auto pgpuprogram = m_pgpuprogram;

      if (!pgpuprogram)
      {

         return;

      }
      
      auto pshader = pgpuprogram->m_pshader;
      
      if(!pshader)
      {
       
         return;
         
      }

      if (pshader->m_strError.is_empty())
      {

         return;

      }

      string strError = m_pgpuprogram->m_pshader->m_strError;

      auto pathShader = m_strShaderPath;

      if(m_strLastError != strError)
      {

         m_strLastError = strError;

         if(strError.has_character())
         {

            auto pinteraction = pgraphics->m_puserinteraction;

            auto colorBackground = argb(127, 255, 255, 255);

            if (::is_set(pinteraction))
            {

               auto pstyle = pinteraction->get_style(pgraphics);

               //            auto color = m_pinteraction->get_color(pstyle, ::e_element_text);

               colorBackground = pinteraction->get_color(pstyle, ::e_element_background);

            }

            colorBackground.m_uchOpacity = 128;

            ::draw2d::brush_pointer pbrush;

            __øconstruct(pbrush);

            pbrush->create_solid(colorBackground);

            ::write_text::font_pointer pfont;

            __øconstruct(pfont);

            auto pnode = system()->node();

            auto strFontName = pnode->font_name(e_font_sans_ui);

            pfont->create_font(e_font_sans_ui, 12_pt);

            __defer_construct(m_pimageError);

            if(m_pimageError->g() == nullptr)
            {

               m_pimageError->create({ 16 });

            }

            auto pgraphicsError = m_pimageLabel->g();

            pgraphicsError->set(pfont);

            auto size = pgraphicsError->get_text_extent(strError);

            ::int_rectangle rect(::double_point( 0, 0 ), size);

            rect.move_to(10, 10);
            rect.inflate(4);

            m_pimageError->create(rect.size());

            pgraphicsError = m_pimageError->g();

            pgraphicsError->set(pfont);

            rect.move_to(0, 0);

            pgraphicsError->set_alpha_mode(::draw2d::e_alpha_mode_set);
            pgraphicsError->set(pbrush);
            pgraphicsError->fill_rectangle(rect);
            pgraphicsError->set_text_color(::color::transparent);


            pgraphicsError->text_out({ 4,4 }, strError);

         }
         else
         {

            m_pimageError.release();

         }

      }

      if(m_pimageError.ok())
      {

         ::image::image_source imagesource(m_pimageError);

         double_rectangle rectangle(double_point(10, 40), m_pimageError->size());

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw(imagedrawing);

      }

   }
   void render::_001OnDraw1Through3(::draw2d::graphics_pointer& pgraphics)
   {

      //string strFontFamily = get_font();

      //auto ppen = __øcreate < ::draw2d::pen > ();

      //auto pbrush = __øcreate < ::draw2d::brush >();

      //auto pfont = __øcreate < ::write_text::font > ();

      //if (m_iDrawing == 3)
      //{

      //   if (!m_pimage1)
      //   {

      //      m_pimage1.create();

      //      fork([this]()
      //         {

      //            m_pimage1 = get_image("matter://pat1.jpg");

      //            if (m_pimage1.ok())
      //            {

      //               __øconstruct(m_pimage2);

      //               m_pimage2->copy_from(m_pimage1);

      //               if (m_pimage2.ok())
      //               {

      //                  m_pimage2->transform(e_image_grayscale);

      //                  m_pimpact->set_need_redraw();

      //                  m_pimpact->post_redraw();

      //               }

      //            }

      //         });

      //   }


      //}

      //int_rectangle rectangle;

      //int iSize = minimum(m_rectangle.width(), m_rectangle.height());

      //iSize = iSize * 3 / 4;

      //rectangle.set_size(iSize, iSize);

      //rectangle.Align(e_align_center, m_rectangle);

      //rectangle.offset_x(-iSize / 5 * 3);

      //rectangle.offset_x(iSize / 5 * m_iDrawing);
      //
      //::double_size size(0., 0.);
      //
      //bool bDrawText = true;
      //
      //string strTitle;
      //
      //if(bDrawText)
      //{

      //   pfont->create_pixel_font(strFontFamily, 100.0, 800);

      //   pgraphics->selectFont(font);

      //   strTitle = papp->get_main_title();

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

      //auto& echeckSimple = papp->m_echeckSimple;

      //if (__bool(echeckSimple))
      //{

      //   ppen->create_null();

      //}
      //else
      //{

      //   ppen->create_solid(4.0, argb(255, 50, 180, 255));

      //}

      //if (m_iDrawing == 3 && m_pimage1.ok())
      //{

      //   pbrush->CreatePatternBrush(m_pimage1);

      //}
      //else
      //{

      //   if (__bool(papp->m_echeckSimple))
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

      //::int_rectangle rectangleText;

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

      //   if (__bool(papp->m_echeckSimple))
      //   {

      //      pbrush->create_solid(m_hlsText);

      //   }
      //   else
      //   {

      //      if (m_pimage2.ok())
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

      //   if (__bool(papp->m_echeckSimple))
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


} // namespace app_shader



