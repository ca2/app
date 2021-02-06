#include "framework.h"
#include <math.h>


CLASS_DECL_AURA color32_t dk_red(); // <3 tbs


void image_gl_set(image* pimage);


namespace app_shader
{


   render::render()
   {

      m_bUpdateShader = false;

      m_strShaderPrefix = "default";

   }


   render::~render()
   {

   }


   ::e_status render::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      initialize_application_consumer();

      m_pcontext = System.get_gpu()->create_context();

      if (!m_pcontext)
      {

         return ::error_failed;

      }

      estatus = m_pcontext->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


#ifdef _DEBUG


   int64_t render::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t render::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


#endif


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_rectangle.area() <= 0)
      {

         return;

      }

      if (m_pcontext)
      {

         m_pcontext->resize_offscreen_buffer(m_rectangle.size());

      }
      
   }


   void render::defer_load_fragment(const char* pszPathPrefix)
   {

      if (string(pszPathPrefix) == "default")
      {

         m_strProjection.Empty();

         m_strFragment.Empty();

         defer_update_shader();

         return;

      }

      ::file::listing listing;

      Application.dir().ls_pattern(listing, "dropbox://shader/simple shader/", { "*.frag" });

      for (auto& path : listing)
      {

         if (path.name().begins_ci(pszPathPrefix))
         {

            m_strFragment = m_pcontext->load_fragment(path, m_eshadersource);

            m_bUpdateShader = true;

            break;

         }

      }

   }


   ::e_status render::update_shader()
   {

      m_bUpdateShader = true;

      return ::success;

   }


   void render::defer_update_shader()
   {

      if (m_bUpdateShader)
      {

         m_bUpdateShader = false;

         _update_shader();

      }

   }


   ::e_status render::_update_shader()
   {

      ::e_status estatus = ::success_none;

      if(m_strProjection.is_empty())
      {

         m_strProjection = m_pcontext->_001GetIntroProjection();

      }

      if(m_strFragment.is_empty())
      {

         m_strFragment = m_pcontext->_001GetIntroFragment();

      }

      color32_t crText = argb(255, 55, 210, 120);

      string strProjection = m_strProjection;

      string strFragment = m_strFragment;

      ::gpu::context_lock lock(m_pcontext);

      m_pcontext->make_current();

      if (!m_pprogram)
      {

         estatus = __construct(m_pprogram);

      }

      m_pcontext->translate_shader(strProjection);

      m_pcontext->translate_shader(strFragment);

      if (::succeeded(estatus))
      {

         estatus = m_pprogram->create_program(strProjection, strFragment);

      }

      ::color::color color(crText);

      string strDataId;

      strDataId = m_pinteraction->m_id;

      m_pcontext->m_pprogram = m_pprogram;

      m_pcontext->draw();

      //unsigned int texture1;

      //glGenTextures(1, &texture1);

      ////            glActiveTexture(GL_TEXTURE0);

      //glBindTexture(GL_TEXTURE_2D, texture1);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      m_millisStart.Now();

      return ::success;

   }


   void render::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      
      ::gpu::context_lock lock(m_pcontext);

      if (m_strShaderPrefix.has_char())
      {

         defer_load_fragment(m_strShaderPrefix);

         m_strShaderPrefix.Empty();

      }

      defer_update_shader();

      if (m_pcontext &&
        ::is_set(m_pcontext->m_pprogram) &&
       m_pcontext->m_pbuffer && ::is_ok(m_pcontext->m_pbuffer->m_pimage))
      {
         
         {

            ::gpu::context_lock lock(m_pcontext);
            
            m_pcontext->make_current();

            m_pcontext->start();

            {

               auto psession = Session;

               auto puser = psession->user();

               auto pwindowing = puser->windowing();

               auto pointCursor = pwindowing->get_cursor_pos();

               float x = (float) pointCursor.x;

               float y = (float) pointCursor.y;

               m_pcontext->m_pprogram->m_pshader->setVec2("mouse", x, y);
               m_pcontext->m_pprogram->m_pshader->setVec2("iMouse", x, y);

            }

            {

               float cx = (float) m_pcontext->m_pbuffer->m_pimage->width();

               float cy = (float) m_pcontext->m_pbuffer->m_pimage->height();

               m_pcontext->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
               m_pcontext->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

            }

            {

               double dElapsed = __double(m_millisStart.elapsed());

               double dTime = dElapsed / 1000.0;

               float time = (float) dTime;

               m_pcontext->m_pprogram->m_pshader->setFloat("time", time);
               m_pcontext->m_pprogram->m_pshader->setFloat("iTime", time);

            }

            m_pcontext->render();

            m_pcontext->prepare_for_gpu_read();

            m_pcontext->m_pbuffer->gpu_read();
            
         }
      
         
#if !defined(__APPLE__)
         ::draw2d::matrix matrixOriginal;
         pgraphics->get(matrixOriginal);
         ::draw2d::matrix matrix(matrixOriginal);
         matrix.scale(1.0, -1.0);
         matrix.translate(0, m_rectangle.height());
         pgraphics->set(matrix);
#endif

         pgraphics->stretch(m_rectangle, m_pcontext->m_pbuffer->m_pimage);

#if !defined(__APPLE__)
         pgraphics->set(matrixOriginal);
#endif
      }

      //_001OnDraw1Through3(pgraphics);

   }


   void render::_001OnDraw1Through3(::draw2d::graphics_pointer& pgraphics)
   {

      //string strFontFamily = get_font();

      //::draw2d::pen_pointer pen(e_create);

      //::draw2d::brush_pointer brush(e_create);

      //::draw2d::font_pointer font(e_create);

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

      //                  m_pview->set_need_redraw();

      //                  m_pview->post_redraw();

      //               }

      //            }

      //         });

      //   }


      //}

      //rectangle_i32 rectangle;

      //int iSize = min(m_rectangle.width(), m_rectangle.height());

      //iSize = iSize * 3 / 4;

      //rectangle.set_size(iSize, iSize);

      //rectangle.Align(e_align_center, m_rectangle);

      //rectangle.offset_x(-iSize / 5 * 3);

      //rectangle.offset_x(iSize / 5 * m_iDrawing);
      //
      //::size_f64 size_i32(0., 0.);
      //
      //bool bDrawText = true;
      //
      //string strTitle;
      //
      //if(bDrawText)
      //{

      //   font->create_pixel_font(strFontFamily, 100.0, 800);

      //   pgraphics->selectFont(font);

      //   strTitle = Application.get_main_title();

      //   size = pgraphics->GetTextExtent(strTitle);

      //   if (!size.is_empty())
      //   {

      //      if (m_iDrawing == 1)
      //      {

      //         font->create_pixel_font(strFontFamily, rectangle.height() * 80.0 / size.get_maximum_dimension(), 800);

      //      }
      //      else
      //      {

      //         font->create_pixel_font(strFontFamily, rectangle.height() * 160.0 / size.get_maximum_dimension(), 800);

      //      }

      //   }

      //   pgraphics->selectFont(font);

      //   size = pgraphics->GetTextExtent(strTitle);
      //      
      //}

      //auto& echeckSimple = Application.m_echeckSimple;

      //if (__bool(echeckSimple))
      //{

      //   pen->create_null();

      //}
      //else
      //{

      //   pen->create_solid(4.0, argb(255, 50, 180, 255));

      //}

      //if (m_iDrawing == 3 && ::is_ok(m_pimage1))
      //{

      //   brush->CreatePatternBrush(m_pimage1);

      //}
      //else
      //{

      //   if (__bool(Application.m_echeckSimple))
      //   {

      //      brush->create_solid(argb(255, 255, 255, 200));

      //   }
      //   else
      //   {

      //      brush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

      //   }

      //}

      //pgraphics->SelectObject(pen);

      //pgraphics->SelectObject(brush);

      //pgraphics->ellipse(rectangle);

      //::rectangle_i32 rectText;

      //rectText.set_size(size);

      //rectText.inflate(10, 10);

      //rectText.Align(e_align_center, rectangle);

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      //if (m_iDrawing == 1)
      //{

      //   brush->create_solid(m_hlsText);

      //}
      //else if (m_iDrawing == 3)
      //{

      //   if (__bool(Application.m_echeckSimple))
      //   {

      //      brush->create_solid(m_hlsText);

      //   }
      //   else
      //   {

      //      if (::is_ok(m_pimage2))
      //      {

      //         brush->CreatePatternBrush(m_pimage2);

      //      }
      //      else
      //      {

      //         brush->create_solid(m_hlsText);

      //      }

      //   }

      //}
      //else
      //{

      //   if (__bool(Application.m_echeckSimple))
      //   {

      //      brush->create_solid(m_hlsText);

      //   }
      //   else
      //   {

      //      brush->CreateLinearGradientBrush(rectText.top_left(), rectText.bottom_right(), m_hlsText, argb(255, 255, 255, 200));

      //   }

      //}

      //pgraphics->SelectObject(brush);

      //if(bDrawText)
      //{
      //
      //   pgraphics->draw_text(strTitle, rectText, e_align_center);
      //   
      //}

   }


} // namespace app_shader



