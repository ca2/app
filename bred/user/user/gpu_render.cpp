// Created by camilo on 2026-11-01 20:24 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "gpu_render.h"
#include "bred/platform/application.h"
#include "acme/parallelization/single_lock.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/context.h"
#include "acme/graphics/image/image32_t.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/texture_site.h"
#include <exception>
#include "bred/gpu/device.h"
#include "bred/gpu/window_attachment.h"
#include "bred/user/user/gpu_interaction.h"
#include "aura/windowing/window.h"
#include "bred/gpu/program.h"
//#include "bred/gpu/cpu_buffer.h"
#include <math.h>
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
//#include "aura/graphics/image/target.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"


CLASS_DECL_ACME::color::color dk_red(); // <3ThomasBorregaardSorensen!!


void image_gl_set(::image::image * pimage);


namespace user
{


   gpu_render::gpu_render()
   {

      //m_bUpdateShader = false;

   }


   gpu_render::~gpu_render()
   {

   }




#ifdef _DEBUG


   ::i64 gpu_render::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   ::i64 gpu_render::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif


   //void gpu_render::initialize_app_shader_render(::user::gpu_interaction * pusergpuinteraction)
   //{

   //   if (!pusergpuinteraction)
   //   {

   //      throw ::exception(error_bad_argument);

   //   }

   //   m_puserinteraction = pusergpuinteraction;

   //   if (m_pgpucontext)
   //   {

   //      return;

   //   }

   //   m_rectangle = pusergpuinteraction->rectangle();

   //   if (m_rectangle.is_empty())
   //   {

   //      return;

   //   }

   //   auto pacmewindowingwindow = pusergpuinteraction->acme_windowing_window();

   //   if (!pacmewindowingwindow)
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   auto pgpudevice = get_app()->get_gpu_approach()->get_gpu_device(pusergpuinteraction->draw2d_domain());

   //   auto pgpucontext = pgpudevice->allocate_gpu_context();

   //   construct_newø(pgpucontext->m_pgpuwindowattachmentOffscreen);

   //   pgpucontext->m_pgpuwindowattachmentOffscreen->initialize_offscreen_frame(pgpucontext);

   //   auto size = m_rectangle.size();

   //   auto sizeRaw = size;

   //   pgpucontext->create_gpu_context(pgpudevice, ::gpu::e_output_aaa_cpu_buffer,
   //      ::gpu::e_scene_2d, pacmewindowingwindow, nullptr, {}, {}, size, sizeRaw);

   //   m_pgpucontext = pgpucontext;

   //}


   //void gpu_render::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   if (m_rectangle.area() <= 0)
   //   {

   //      return;

   //   }

   //   if (m_pgpucontext)
   //   {

   //      auto size = m_rectangle.size();

   //      m_pgpucontext->sendø() << [this, size]
   //         {

   //            m_pgpucontext->m_sizeRaw = size;
   //            m_pgpucontext->set_output_placement(::i32_rectangle(size));
   //            m_pgpucontext->get_gpu_renderer()->on_resize(size);

   //         };

   //   }

   //}


   //void gpu_render::defer_load_fragment(const ::scoped_string & scopedstrPathPrefix)
   //{

   //   information() << "app_shader: loading shader path: " << scopedstrPathPrefix;

   //   if (string(scopedstrPathPrefix) == "default")
   //   {

   //      information() << "app_shader: using built-in default shader";

   //      m_strProjection.empty();

   //      m_strFragment.empty();

   //      defer_update_shader();

   //      return;

   //   }

   //   //auto papp = get_app();

   //   //auto pcontext = ::object::m_pgpucontext;

   //   //directory()->ls_pattern(listing, "cloud://shader/simple shader/", { "*.frag" });

   //   //for (auto& path : listing)
   //   //{

   //   //   if (path.name().case_insensitive_begins(scopedstrPathPrefix))
   //   //   {

   //   m_strFragment = m_pgpucontext->load_fragment(scopedstrPathPrefix, m_eshadersource);

   //   information() << "app_shader: loaded shader path: " << scopedstrPathPrefix
   //      << "; source bytes: " << m_strFragment.length();

   //   //      break;

   //   //   }

   //   //}

   //}


   //void gpu_render::update_shader()
   //{

   //   m_bUpdateShader = true;

   //   //return ::success;

   //}


   //void gpu_render::defer_update_shader()
   //{

   //   if (m_bUpdateShader)
   //   {

   //      m_bUpdateShader = false;

   //      defer_load_fragment(m_strShaderPath);

   //      _update_shader();

   //   }

   //}


   //void gpu_render::_update_shader()
   //{

   //   //::e_status estatus = ::success_none;

   //   if (m_strProjection.is_empty())
   //   {

   //      // A fullscreen triangle needs no vertex buffers or input layout.
   //      m_strProjection =
   //         "out vec3 ourPosition;\n"
   //         "void main() {\n"
   //         "  vec2 p = vec2(float((gl_VertexID << 1) & 2), float(gl_VertexID & 2));\n"
   //         "  ourPosition = vec3(p * 2.0 - 1.0, 0.0);\n"
   //         "  gl_Position = vec4(ourPosition, 1.0);\n"
   //         "}\n";

   //   }

   //   if (m_strFragment.is_empty())
   //   {

   //      m_strFragment = m_pgpucontext->_001GetIntroFragment();

   //   }

   //   color32_t crText = argb(255, 55, 210, 120);

   //   string strProjection = m_strProjection;

   //   string strFragment = m_strFragment;

   //   //::gpu::context_lock lock(m_pgpucontext);

   //   //m_pgpucontext->make_current();

   //   if (!m_pshader)
   //   {

   //      //estatus = 

   //      constructø(m_pshader);

   //   }

   //   m_pgpucontext->translate_shader(strProjection);

   //   m_pgpucontext->translate_shader(strFragment);

   //   //if (::succeeded(estatus))
   //   //{

   //      //estatus = 
   //   m_pshader->m_bDisableDepthTest = true;
   //   m_pshader->m_bEnableBlend = false;
   //   m_pshader->m_etopology = ::gpu::e_topology_triangle_list;
   //   m_pshader->m_ecullmode = ::gpu::e_cull_mode_none;

   //   m_pshader->initialize_shader_with_block(m_pgpucontext->get_gpu_renderer(),
   //      strProjection.as_block(), strFragment.as_block(), nullptr,
   //      ::gpu::shader::e_flag_optional_uniforms);

   //   //}

   //   ::color::color color(crText);

   //   //string strDataId;

   //   //strDataId = m_pinteraction->id();

   //   //pgpucontext->m_pgpuprogram = m_pgpuprogram;

   //   // Shader initialization does not have a command buffer or gpu_render target.
   //   // Binding and drawing belong to the frame rendering pass.

   //   //::u32 texture1;

   //   //glGenTextures(1, &texture1);

   //   ////            glActiveTexture(GL_TEXTURE0);

   //   //glBindTexture(GL_TEXTURE_2D, texture1);
   //   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   //   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   //   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   //   m_timeStart.Now();

   //   //return ::success;

   //}


   ::image::image * gpu_render::drawn_frame_image()
   {

      on_gpu_draw(m_pgpucontext);

      return m_pimageFromGpu;

   }


   void gpu_render::on_gpu_draw(::gpu::context * pgpucontext)
   {

      if (!pgpucontext || m_rectangle.is_empty())
      {

         return;

      }

      pgpucontext->sendø() << [this, pgpucontext]
         {

            on_gpu_render(pgpucontext);
            //auto pcontext = pgpucontext;
            //::gpu::context_lock contextlock(pcontext);
            //auto pattachment = pcontext->m_pgpuwindowattachmentOffscreen;
            //::pointer<::gpu::layer> playerPrevious = ::gpu::current_layer();
            //::std::exception_ptr exceptionRender;
            //bool bFrameStarted = false;
            //bool bLayerStarted = false;

            //try
            //{

            //   auto size = m_rectangle.size();
            //   pcontext->m_sizeRaw = size;
            //   pcontext->set_output_placement(::i32_rectangle(size));
            //   pcontext->get_gpu_renderer()->on_resize(size);
            //   defer_update_shader();

            //   if (!m_pmodelbufferFullscreen)
            //   {

            //      constructø(m_pmodelbufferFullscreen);
            //      m_pmodelbufferFullscreen->initialize_dummy_model(pcontext, 3);

            //   }

            //   pattachment->start_frame();
            //   bFrameStarted = true;
            //   pcontext->start_layer(false, ::gpu::e_start_layer_none);
            //   bLayerStarted = true;

            //   ::pointer<::gpu::texture_site> ptarget =
            //      pcontext->current_target_texture(::gpu::current_layer());
            //   auto pcommands = ::gpu::current_layer()->getCurrentCommandBuffer4();
            //   pcommands->begin_render(m_pshader, ptarget);
            //   pcommands->set_viewport(::i32_rectangle(size), ptarget->raw_size());
            //   pcommands->set_scissor(::i32_rectangle(size), ptarget->raw_size());

            //   auto pointCursor = m_puserinteraction->mouse_cursor_position();
            //   m_puserinteraction->screen_to_client()(pointCursor);
            //   auto x = (::f32)pointCursor.x;
            //   auto y = (::f32)(size.cy - pointCursor.y);
            //   m_pshader->set_sequence2("mouse", x, y);
            //   m_pshader->set_sequence4("iMouse", x, y, 0.f, 0.f);
            //   m_pshader->set_sequence2("resolution", (::f32)size.cx, (::f32)size.cy);
            //   m_pshader->set_sequence3("iResolution", (::f32)size.cx, (::f32)size.cy, 1.f);
            //   auto time = (::f32)m_timeStart.elapsed().floating_second();
            //   m_pshader->set_f32("time", time);
            //   m_pshader->set_f32("iTime", time);
            //   pcommands->draw(m_pmodelbufferFullscreen);
            //   pcommands->end_render();
            //   bLayerStarted = false;
            //   pcontext->end_layer();

            //   // Read the finished layer, rather than the legacy CPU buffer.
            //   defer_constructø(m_pimageFromGpu);
            //   m_pimageFromGpu->create_as_descriptor(ptarget->raw_size(),
            //      pcontext->m_pgpudevice->draw2d_domain());
            //   {

            //      auto ppixmap = m_pimageFromGpu->map(::image::e_map_discard, ptarget->output_placement());
            //      auto pread = pcontext->beginSingleTimeCommands(pcontext->m_pgpudevice->graphics_queue());
            //      auto ptexture = ptarget->gpu_texture()->resolved_texture(ptarget->output_placement());
            //      ptexture->read_pixels(pread, ppixmap, ptarget->m_pointOutput);
            //      if (!m_bLoggedReadback)
            //      {

            //         auto pcenter = (const ::image32_t *)((const ::u8 *)ppixmap->m_pimage32
            //            + (size.cy / 2) * ppixmap->m_iScan) + size.cx / 2;
            //         informationf("app_shader readback: path=%s size=%dx%d center=0x%08x",
            //            m_strShaderPath.c_str(), size.cx, size.cy, pcenter->m_u32);
            //         m_bLoggedReadback = true;

            //      }
            //      if (pread.is_pending())
            //      {

            //         pread.commit();

            //      }

            //   }
            //   m_pimageFromGpu->set_ok_flag();
            //   m_pimageFromGpu->m_estatus = success;

            //}
            //catch (...)
            //{

            //   exceptionRender = ::std::current_exception();

            //}

            //if (bLayerStarted)
            //{

            //   try { pcontext->end_layer(); }
            //   catch (...) { if (!exceptionRender) exceptionRender = ::std::current_exception(); }

            //}
            //if (bFrameStarted)
            //{

            //   try { pattachment->end_frame(); }
            //   catch (...) { if (!exceptionRender) exceptionRender = ::std::current_exception(); }

            //}
            //::gpu::set_current_layer(playerPrevious);
            //if (exceptionRender)
            //{

            //   ::std::rethrow_exception(exceptionRender);

            //}

         };

      //if (m_pimageFromGpu.ok())
      //{

      //   ::image::image_source source(m_pimageFromGpu, ::i32_rectangle(m_rectangle.size()));
      //   ::image::image_drawing_options options(m_rectangle);
      //   ::image::image_drawing drawing(options, source);
      //   pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      //   try
      //   {

      //      pdraw2dgraphics->draw(drawing);


      //   }
      //   catch (const ::exception & e)
      //   {

      //      error() << "app_shader: draw2d image transfer failed: " << e.get_message();
      //      throw;

      //   }


      //}

      // The host presents only shader output; window UI belongs to main_window.

   }


   void render::on_gpu_render(::gpu::context * pgpucontext)
   {


   }


   //void gpu_render::_001OnDrawLabel(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   auto pathShader = m_strShaderPath;

   //   auto strLabel = ::file::path(pathShader).name();

   //   auto pinteraction = m_puserinteraction;

   //   ::color::color colorBackground = argb(127, 255, 255, 255);

   //   if (::is_set(pinteraction))
   //   {

   //      auto pstyle = pinteraction->get_style(pdraw2dgraphics);

   //      colorBackground = pinteraction->get_color(pstyle, ::e_element_background);

   //   }

   //   if (m_strLastLabel != strLabel
   //      || m_colorLastLabelBackground != colorBackground)
   //   {

   //      m_strLastLabel = strLabel;

   //      if (strLabel.has_character())
   //      {

   //         colorBackground.m_u8Opacity = 128;

   //         ::draw2d::brush_pointer pbrush;

   //         constructø(pbrush);

   //         pbrush->create_solid(colorBackground);

   //         ::write_text::font_pointer pfont;

   //         constructø(pfont);

   //         pfont->create_font(e_font_sans_ui, 12_pt);

   //         defer_constructø(m_pimageLabel);

   //         if (m_pimageLabel->size().is_empty())
   //         {

   //            m_pimageLabel->create_as_descriptor({ 16, 16 }, pdraw2dgraphics->draw2d_domain());

   //         }

   //         auto pgraphicsLabel = m_pimageLabel->acquire_graphics();

   //         pgraphicsLabel->set(pfont);

   //         auto size = pgraphicsLabel->get_text_extent(strLabel);

   //         ::i32_rectangle rect(::f64_point(0, 0), size);

   //         rect.inflate(4);

   //         rect.move_to(0, 0);

   //         pgraphicsLabel.close();

   //         m_pimageLabel->create_as_descriptor(rect.size(), pdraw2dgraphics->draw2d_domain());

   //         pgraphicsLabel = m_pimageLabel->acquire_graphics();

   //         pgraphicsLabel->set(pfont);

   //         pgraphicsLabel->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //         pgraphicsLabel->set(pbrush);

   //         pgraphicsLabel->fill_rectangle(rect);

   //         pbrush->create_solid(argb(255, 0, 0, 0));

   //         pgraphicsLabel->set(pbrush);

   //         pgraphicsLabel->text_out({ 4,4 }, strLabel);

   //      }
   //      else
   //      {

   //         m_pimageLabel.release();

   //      }

   //   }

   //   if (m_pimageLabel.ok())
   //   {

   //      ::image::image_source imagesource(m_pimageLabel);

   //      ::f64_rectangle rectangle(::f64_point(10, 10), m_pimageLabel->size());

   //      ::image::image_drawing_options imagedrawingoptions(rectangle);

   //      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   //      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      pdraw2dgraphics->draw(imagedrawing);

   //   }

   //}


   //void gpu_render::_001OnDrawError(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   auto pgpushader = m_pshader;

   //   if (!pgpushader)
   //   {

   //      return;

   //   }

   //   if (pgpushader->m_strError.is_empty())
   //   {

   //      return;

   //   }

   //   string strError = pgpushader->m_strError;

   //   auto pathShader = m_strShaderPath;

   //   if (m_strLastError != strError)
   //   {

   //      m_strLastError = strError;

   //      if (strError.has_character())
   //      {

   //         auto pinteraction = m_puserinteraction;

   //         auto colorBackground = argb(127, 255, 255, 255);

   //         if (::is_set(pinteraction))
   //         {

   //            auto pstyle = pinteraction->get_style(pdraw2dgraphics);

   //            //            auto color = m_pinteraction->get_color(pstyle, ::e_element_text);

   //            colorBackground = pinteraction->get_color(pstyle, ::e_element_background);

   //         }

   //         colorBackground.m_u8Opacity = 128;

   //         ::draw2d::brush_pointer pbrush;

   //         constructø(pbrush);

   //         pbrush->create_solid(colorBackground);

   //         ::write_text::font_pointer pfont;

   //         constructø(pfont);

   //         auto pnode = system()->node();

   //         auto strFontName = pnode->font_name(e_font_sans_ui);

   //         pfont->create_font(e_font_sans_ui, 12_pt);

   //         defer_constructø(m_pimageError);

   //         if (m_pimageError->size().is_empty())
   //         {

   //            m_pimageError->create_as_descriptor({ 16, 16 }, pdraw2dgraphics->draw2d_domain());

   //         }

   //         auto pgraphicsError = m_pimageError->acquire_graphics();

   //         pgraphicsError->set(pfont);

   //         auto size = pgraphicsError->get_text_extent(strError);

   //         ::i32_rectangle rect(::f64_point(0, 0), size);

   //         rect.move_to(10, 10);
   //         rect.inflate(4);

   //         pgraphicsError.close();

   //         m_pimageError->create_as_descriptor(rect.size(), pdraw2dgraphics->draw2d_domain());

   //         pgraphicsError = m_pimageError->acquire_graphics();

   //         pgraphicsError->set(pfont);

   //         rect.move_to(0, 0);

   //         pgraphicsError->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         pgraphicsError->set(pbrush);
   //         pgraphicsError->fill_rectangle(rect);
   //         pbrush->create_solid(argb(255, 0, 0, 0));
   //         pgraphicsError->set(pbrush);


   //         pgraphicsError->text_out({ 4,4 }, strError);

   //      }
   //      else
   //      {

   //         m_pimageError.release();

   //      }

   //   }

   //   if (m_pimageError.ok())
   //   {

   //      ::image::image_source imagesource(m_pimageError);

   //      ::f64_rectangle rectangle(::f64_point(10, 40), m_pimageError->size());

   //      ::image::image_drawing_options imagedrawingoptions(rectangle);

   //      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   //      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      pdraw2dgraphics->draw(imagedrawing);

   //   }

   //}
   //void gpu_render::_001OnDraw1Through3(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   //string strFontFamily = get_font();

   //   //auto ppen = createø < ::draw2d::pen > ();

   //   //auto pbrush = createø < ::draw2d::brush >();

   //   //auto pfont = createø < ::write_text::font > ();

   //   //if (m_iDrawing == 3)
   //   //{

   //   //   if (!m_pimage1)
   //   //   {

   //   //      m_pimage1.create();

   //   //      fork([this]()
   //   //         {

   //   //            m_pimage1 = get_image("matter://pat1.jpg");

   //   //            if (m_pimage1.ok())
   //   //            {

   //   //               constructø(m_pimage2);

   //   //               m_pimage2->copy_from(m_pimage1);

   //   //               if (m_pimage2.ok())
   //   //               {

   //   //                  m_pimage2->transform(e_image_grayscale);

   //   //                  m_pimpact->set_need_redraw();

   //   //                  m_pimpact->post_redraw();

   //   //               }

   //   //            }

   //   //         });

   //   //   }


   //   //}

   //   //i32_rectangle rectangle;

   //   //::i32 iSize = minimum(m_rectangle.width(), m_rectangle.height());

   //   //iSize = iSize * 3 / 4;

   //   //rectangle.set_size(iSize, iSize);

   //   //rectangle.Align(e_align_center, m_rectangle);

   //   //rectangle.offset_x(-iSize / 5 * 3);

   //   //rectangle.offset_x(iSize / 5 * m_iDrawing);
   //   //
   //   //::f64_size size(0., 0.);
   //   //
   //   //bool bDrawText = true;
   //   //
   //   //string strTitle;
   //   //
   //   //if(bDrawText)
   //   //{

   //   //   pfont->create_pixel_font(strFontFamily, 100.0, 800);

   //   //   pdraw2dgraphics->selectFont(font);

   //   //   strTitle = papp->get_main_title();

   //   //   size = pdraw2dgraphics->get_text_extent(strTitle);

   //   //   if (!size.is_empty())
   //   //   {

   //   //      if (m_iDrawing == 1)
   //   //      {

   //   //         pfont->create_pixel_font(strFontFamily, rectangle.height() * 80.0 / size.get_maximum_dimension(), 800);

   //   //      }
   //   //      else
   //   //      {

   //   //         pfont->create_pixel_font(strFontFamily, rectangle.height() * 160.0 / size.get_maximum_dimension(), 800);

   //   //      }

   //   //   }

   //   //   pdraw2dgraphics->selectFont(font);

   //   //   size = pdraw2dgraphics->get_text_extent(strTitle);
   //   //      
   //   //}

   //   //auto& echeckSimple = papp->m_echeckSimple;

   //   //if (__bool(echeckSimple))
   //   //{

   //   //   ppen->create_null();

   //   //}
   //   //else
   //   //{

   //   //   ppen->create_solid(4.0, argb(255, 50, 180, 255));

   //   //}

   //   //if (m_iDrawing == 3 && m_pimage1.ok())
   //   //{

   //   //   pbrush->CreatePatternBrush(m_pimage1);

   //   //}
   //   //else
   //   //{

   //   //   if (__bool(papp->m_echeckSimple))
   //   //   {

   //   //      pbrush->create_solid(argb(255, 255, 255, 200));

   //   //   }
   //   //   else
   //   //   {

   //   //      pbrush->CreateLinearGradientBrush(rectangle.top_left(), rectangle.bottom_right(), argb(255, 255, 255, 200), argb(255, 255, 125, 100));

   //   //   }

   //   //}

   //   //pdraw2dgraphics->SelectObject(pen);

   //   //pdraw2dgraphics->SelectObject(brush);

   //   //pdraw2dgraphics->ellipse(rectangle);

   //   //::i32_rectangle rectangleText;

   //   //rectangleText.set_size(size);

   //   //rectangleText.inflate(10, 10);

   //   //rectangleText.Align(e_align_center, rectangle);

   //   //pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   //if (m_iDrawing == 1)
   //   //{

   //   //   pbrush->create_solid(m_hlsText);

   //   //}
   //   //else if (m_iDrawing == 3)
   //   //{

   //   //   if (__bool(papp->m_echeckSimple))
   //   //   {

   //   //      pbrush->create_solid(m_hlsText);

   //   //   }
   //   //   else
   //   //   {

   //   //      if (m_pimage2.ok())
   //   //      {

   //   //         pbrush->CreatePatternBrush(m_pimage2);

   //   //      }
   //   //      else
   //   //      {

   //   //         pbrush->create_solid(m_hlsText);

   //   //      }

   //   //   }

   //   //}
   //   //else
   //   //{

   //   //   if (__bool(papp->m_echeckSimple))
   //   //   {

   //   //      pbrush->create_solid(m_hlsText);

   //   //   }
   //   //   else
   //   //   {

   //   //      pbrush->CreateLinearGradientBrush(rectangleText.top_left(), rectangleText.bottom_right(), m_hlsText, argb(255, 255, 255, 200));

   //   //   }

   //   //}

   //   //pdraw2dgraphics->SelectObject(brush);

   //   //if(bDrawText)
   //   //{
   //   //
   //   //   pdraw2dgraphics->draw_text(strTitle, rectangleText, e_align_center);
   //   //   
   //   //}

   //}


} // namespace user



