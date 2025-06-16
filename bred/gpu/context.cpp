#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "cpu_buffer.h"
#include "render.h"
#include "renderer.h"
#include "render_target.h"
#include "layer.h"
#include "texture.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/application.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/context.h"
#include "bred/gpu/graphics.h"


namespace gpu
{


   extern thread_local device* t_pgpudevice;

   context_guard::context_guard(context* pcontext) :
      m_pcontext(pcontext)
   {

      m_pcontext->make_current();

   }


   context_guard::~context_guard()
   {

      m_pcontext->release_current();

   }


   rear_guard::rear_guard(context* pcontext)
   {

      if (::is_null(pcontext))
      {

         m_itaskUpper = {};

         m_pcontextUpper = nullptr;

         return;

      }

      if (::is_null(pcontext->m_pgpudevice))
      {

         throw ::exception(error_wrong_state);

      }

      auto pcontextUpper = pcontext->m_pgpudevice->current_context();

      ::gpu::context::enum_type etypeContextUpper = ::gpu::context::e_type_undefined;

      if (pcontextUpper)
      {

         etypeContextUpper = pcontextUpper->m_etype;

      }

      auto itaskUpperCurrent = pcontext->m_pgpudevice->m_itaskCurrentGpuContext;

      if (pcontextUpper
         && pcontextUpper->m_itask == itaskUpperCurrent)
      {

         m_pcontextUpper = pcontextUpper;

         m_itaskUpper = pcontext->m_pgpudevice->m_itaskCurrentGpuContext;

         if (m_itaskUpper != ::current_itask())
         {

            throw ::exception(error_wrong_state);

         }

         m_pcontextUpper->release_current();

      }
      else
      {

         m_pcontextUpper = nullptr;

      }

   }


   rear_guard::~rear_guard()
   {

      if (m_pcontextUpper)
      {

         if (m_itaskUpper != ::current_itask())
         {

            warning() << "rear_guard::~rear_guard() - m_itaskUpper != ::current_itask()";
            //throw ::exception(error_wrong_state);

         }

         m_pcontextUpper->make_current();

      }

   }


   context::context()
   {

      m_eoutput = ::gpu::e_output_none;

      m_etype = e_type_undefined;

      m_escene = e_scene_none;

      m_bCreated = false;

   }


   context::~context()
   {


   }


   void context::draw()
   {


   }


   void context::prepare_for_gpu_read()
   {

      swap_buffers();

   }


   void context::start_drawing()
   {


   }


   void context::global_transform()
   {


   }


   void context::render()
   {


   }


   void context::set_bitmap_1(::image::image* pimage)
   {



   }


   void context::swap_buffers()
   {


   }


   void context::create_window_buffer(::windowing::window* pwindow)
   {

      ::cast < device > pgpudevice = m_pgpudevice;

      if (::is_null(pgpudevice))
      {

         throw ::exception(error_null_pointer);

      }

      _create_window_buffer(pwindow);

   }


   void context::_create_window_buffer(::windowing::window* pwindow)
   {

   }


   void context::create_cpu_buffer(const ::int_size& size)
   {

      if (size.is_empty())
      {

         return;

      }

      _send([this, size]()
         {

            ::cast < device > pgpudevice = m_pgpudevice;

            if (::is_null(pgpudevice))
            {

               throw ::exception(error_null_pointer);

            }

            __defer_construct(m_pcpubuffer);

            m_pcpubuffer->initialize_cpu_buffer(this);

            m_pcpubuffer->set_size(size);

            _create_cpu_buffer(size);

            m_bCreated = true;

         });

   }


   void context::defer_create_window_context(::windowing::window* pwindow)
   {

      send([this, pwindow]()
         {

            _defer_create_window_context(pwindow);

            m_bCreated = true;

         });

   }


   void context::_create_cpu_buffer(const ::int_size& size)
   {

   }


   void context::_defer_create_window_context(::windowing::window* pwindow)
   {

   }


   void context::resize_cpu_buffer(const ::int_size& size)
   {

      send([this, size]()
         {

            if (!m_pcpubuffer)
            {

               return create_cpu_buffer(size);

            }

            _synchronous_lock synchronouslock(m_pcpubuffer->synchronization());

            m_pcpubuffer->set_size(size);

         });

   }


   void context::create_window_context(::gpu::device* pgpudevice, ::windowing::window* pwindow)
   {

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      m_escene = e_scene_2d;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      rear_guard guard(this);

      _send([this, pgpudevice, pwindow]()
         {

            auto eoutput = ::gpu::e_output_swap_chain;

            initialize_gpu_context(pgpudevice, eoutput, pwindow, {});

         });

   }


   void context::create_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::gpu::enum_scene& escene, const ::int_size& size)
   {

      m_eoutput = eoutput;

      m_escene = escene;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      rear_guard guard(this);

      _send([this, pgpudevice, eoutput, size]()
         {

            initialize_gpu_context(pgpudevice, eoutput, nullptr, size);

         });

   }


   void context::create_draw2d_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::int_size& size)
   {

      m_etype = e_type_draw2d;

      m_escene = e_scene_2d;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      rear_guard guard(this);

      _send([this, pgpudevice, eoutput, size]()
         {

            initialize_gpu_context(pgpudevice, eoutput, nullptr, size);

         });

   }


   //void context::create_draw2d_window_context(::gpu::device* pgpudevice, const ::gpu::enum_output & eoutput,  ::windowing::window* pwindow)
   //{

   //   m_etype = e_type_draw2d;

   //   branch_synchronously();

   //   m_pgpudevice = pgpudevice;

   //   rear_guard guard(this);

   //   _send([this, pgpudevice, eoutput, pwindow]()
   //      {

   //         initialize_gpu_context(pgpudevice, eoutput, pwindow, {});

   //      });

   //}


   //void context::create_draw2d_off_screen_context(::gpu::device* pgpudevice, const ::gpu::enum_output & eoutput, const::int_size& size)
   //{

   //   m_etype = e_type_draw2d;

   //   branch_synchronously();

   //   m_pgpudevice = pgpudevice;

   //   rear_guard guard(this);

   //   _send([this]()
   //      {

   //         initialize_gpu_context(startcontext);

   //      });

   //}


   //void context::start_gpu_context(const start_context_t& startcontext)
   //{

   //   branch_synchronously();

   //   m_pgpudevice = startcontext.m_pgpudevice;

   //   rear_guard guard(this);

   //   _send([this, &startcontext]()
   //      {

   //         initialize_gpu_context(startcontext);

   //      });

   //}

   void context::initialize_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size)
   {

      ASSERT(is_current_task());

      if (m_etype == e_type_window)
      {

         task_set_name("gctx::window");

      }
      else if (m_etype == e_type_graphics3d)
      {

         task_set_name("gctx::3d");

      }
      else
      {

         task_set_name("gctx::unknown");

      }

      m_pgpudevice = pgpudevice;

      t_pgpudevice = m_pgpudevice;

      m_eoutput = eoutput;

      m_rectangle.top_left() = { 0, 0 };

      m_rectangle.set_size(size);

      m_escene = m_escene;

      on_create_context(pgpudevice, eoutput, pwindow, size);

   }


   void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size)
   {


   }


   void context::engine_on_frame_context_initialization()
   {



   }


   bool context::task_iteration()
   {

      if (!::thread::task_iteration())
      {

         return false;

      }

      for (auto prender : m_rendera)
      {

         if (!prender->render_step())
         {

            return false;

         }

      }

      return true;

   }


   void context::lock_context()
   {

      //return ::success;

   }


   void context::unlock_context()
   {

      //return ::success;

   }


   ::gpu::enum_output context::get_eoutput()
   {

      return m_eoutput;

   }


   ::gpu::cpu_buffer* context::get_cpu_buffer()
   {

      if (!m_pcpubuffer)
      {

         create_cpu_buffer(m_rectangle.size());

      }

      return m_pcpubuffer;

   }


   void context::make_current()
   {

      m_pgpudevice->make_current(this);

   }


   void context::release_current()
   {

      m_pgpudevice->release_current(this);

   }


   void context::destroy_cpu_buffer()
   {

      //return ::success_none;

   }


   ::int_rectangle context::rectangle()
   {

      return m_rectangle;

   }


   void context::set_placement(const ::int_rectangle& rectanglePlacement)
   {

      m_rectangle = rectanglePlacement;

      //get_renderer()->on_context_resize();

   }


   void context::resize_offscreen_buffer(const ::int_size& size)
   {


   }


   void context::do_on_context(const ::procedure& procedure)
   {

      context_guard contextguard(this);

      procedure();

   }


   void context::send_on_context(const ::procedure& procedureParam)
   {

      ::gpu::rear_guard rear_guard(this);

      auto procedure = procedureParam;

      _send([this, procedure]()
         {

            do_on_context(procedure);

         });

   }


   void context::top_send_on_context(::gpu::context* pcontextInnerStart, bool bForDrawing, const ::procedure& procedure)
   {

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

      pgpudevice->start_stacking_layers();

      send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
         {

            get_gpu_renderer()->do_on_frame([this, pcontextInnerStart, bForDrawing, procedure]()
               {

                  pcontextInnerStart->send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
                     {

                        if (bForDrawing)
                        {

                           auto prenderer = pcontextInnerStart->get_gpu_renderer();

                           prenderer->defer_update_renderer();

                           ::procedure λ = [procedure]()
                              {

                                 procedure();

                              };

                           prenderer->do_on_frame(λ);

                        }
                        else
                        {

                           procedure();

                        }

                     });

                  auto playera = m_pgpudevice->m_playera;

                  if (playera)
                  {

                     auto prenderer = get_gpu_renderer();

                     auto prendertarget = prenderer->m_pgpurendertarget;

                     auto ptexture = prendertarget->current_texture();

                     ptexture->merge_layers(m_pgpudevice->m_playera);

                     this->copy(ptexture);

                  }

               });

         });

   }


   bool context::create_offscreen_graphics_for_swap_chain_blitting(::draw2d_gpu::graphics* pgraphics, const ::int_size& size)
   {

      return false;

   }


   ::gpu::renderer* context::get_gpu_renderer()
   {

      if (!m_pgpurendererOutput2)
      {

         __øconstruct(m_pgpurendererOutput2);

         m_pgpurendererOutput2->initialize_renderer(this);

         m_pgpurendererOutput2->m_iFrameCount2 = ::gpu::render_target::MAX_FRAMES_IN_FLIGHT;

         m_pgpurendererOutput2->defer_update_renderer();

      }

      return m_pgpurendererOutput2;

   }


   //::gpu::renderer* context::draw2d_renderer()
   //{

   //   if (!m_pgpucontextDraw2d->m_pgpurendererOutput2)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      __øconstruct(m_pgpucontextDraw2d->m_pgpurendererOutput2);

   //      auto eoutputDraw2d = m_papplication->m_gpu.m_eoutputDraw2d;

   //      m_pgpucontextDraw2d->m_pgpurendererOutput2->initialize_renderer(this, eoutputDraw2d, escene);

   //      m_pgpucontextDraw2d->m_pgpurendererOutput2->set_single_frame();

   //      m_pgpucontextDraw2d->m_pgpurendererOutput2->defer_update_renderer();

   //   }

   //   return m_pgpucontextDraw2d->m_pgpurendererOutput2;

   //}


   //::gpu::renderer* context::graphics3d_renderer()
   //{

   //   if (!m_pgpurendererEngine)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      __øconstruct(m_pgpurendererEngine);

   //      auto eoutputEngine = m_papplication->m_gpu.m_eoutputEngine;

   //      m_pgpurendererEngine->initialize_renderer(this, eoutputEngine, escene);

   //      //m_pgpurendererEngine->set_single_frame();

   //      m_pgpurendererEngine->m_iFrameCount2 = ::gpu::render_target::MAX_FRAMES_IN_FLIGHT;

   //      m_pgpurendererEngine->defer_update_renderer();

   //   }

   //   return m_pgpurendererEngine;

   //}


   //::gpu::renderer* context::new_draw2d_renderer()
   //{

   //   ::pointer < ::gpu::renderer > pgpurendererDraw2d;

   //   ::gpu::enum_scene escene = m_escene;

   //   __øconstruct(pgpurendererDraw2d);

   //   //auto eoutputDraw2d = m_papplication->m_gpu.m_eoutputDraw2d;

   //   auto eoutputDraw2d = ::gpu::e_output_gpu_buffer;

   //   pgpurendererDraw2d->initialize_renderer(this, eoutputDraw2d, escene);

   //   m_gpurendereraDraw2d.add(pgpurendererDraw2d);

   //   return pgpurendererDraw2d;

   //}



   string context::_001GetIntroProjection()
   {

      string strVersion = get_shader_version_text();


      string strProjection =
         "layout(glm::vec3 = 0) in vec3 aPos;\n"
         "layout(glm::vec3 = 1) in vec3 aColor;\n"
         "/* out vec3 ourColor; */\n"
         "out vec3 ourPosition;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   gl_Position = vec4(aPos, 1.0);\n"
         "   /* ourColor = aColor;*/\n"
         "   ourPosition = aPos;\n"
         "}\n";

      return strProjection;
   }


   string context::_001GetIntroFragment()
   {

      string strVersion = get_shader_version_text();

      string strFragment =
         "uniform vec2 resolution;\n"
         "uniform float time;\n"
         "uniform vec2 mouse;\n"
         "uniform sampler2D backbuffer;\n"
         "\n"
         "void main(void) {\n"
         "vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / minimum(resolution.x(), resolution.y());\n"
         "\n"
         "gl_FragColor = vec4(uv, uv/2.0);\n"
         "}\n";

      return strFragment;

   }


   bool context::is_mesa()
   {

      return false;

   }


   string context::load_fragment(const ::string& pszPath, enum_shader_source& eshadersource)
   {

      ::file::path path(pszPath);

      string strFragment = file()->as_string(path);

      string strExtension = path.all_extensions();

      string strVersion = get_shader_version_text();

      if (strExtension.case_insensitive_begins("shadertoy"))
      {

         eshadersource = e_shader_source_shadertoy;

         strFragment =
            //"#" + strVersion + "\n"
            //"\n"
            //"precision highp float;\n"
            "\n"
            "uniform vec2 iResolution;\n"
            "uniform float iTime;\n"
            "uniform vec2 iMouse;\n"
            "uniform sampler2D backbuffer;\n"
            "\n"
            "\n"
            + strFragment;


         strFragment +=
            "\n\n"
            "void main(void)\n"
            "{\n"
            "   mainImage(gl_FragColor, gl_FragCoord.xy);\n"
            "}\n";

      }
      else
      {

         strFragment =
            //            "#" + strVersion + "\n"
            //            "\n"
            +strFragment;

         eshadersource = e_shader_source_neort;

      }

      return strFragment;

   }


   string context::get_shader_version_text()
   {

      return "version 330 core";

   }


   void context::set_matrix_uniform(const ::gpu::payload& payloadMatrix)
   {

      throw interface_only();

   }


   void context::translate_shader(string& strFragment)
   {

      string_array stra;

      stra.add_lines(strFragment);

      auto iFind = stra.case_insensitive_find_first_begins("#version ");

      if (found(iFind))
      {

         stra[iFind] = get_shader_version_text();

      }
      else
      {

         stra.insert_at(0, get_shader_version_text());

      }

      _translate_shader(stra);

      strFragment = stra.implode("\n");

   }


   void context::_translate_shader(string_array& stra)
   {

   }


   image_data context::image32(const ::payload& payloadFile)
   {

      auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

      class image_data image32;

      image32.m_memory.set_size(pimage->area() * 4);

      {


         auto p = image32.m_memory.data();

         for (auto y = 0; y < pimage->height(); y++)
         {

            auto psource = pimage->line_data(pimage->height() - y - 1);
            for (auto x = 0; x < pimage->width(); x++)
            {

               *p++ = psource->byte_red(pimage->color_indexes());
               *p++ = psource->byte_green(pimage->color_indexes());
               *p++ = psource->byte_blue(pimage->color_indexes());
               *p++ = psource->byte_opacity(pimage->color_indexes());

               psource++;

            }

         }

      }

      image32.m_iWidth = pimage->width();
      image32.m_iHeight = pimage->height();

      return ::transfer(image32);


   }


   image_data context::image24(const ::payload& payloadFile)
   {

      auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

      class image_data image24;

      image24.m_memory.set_size(pimage->area() * 3);

      {


         auto p = image24.m_memory.data();

         for (auto y = 0; y < pimage->height(); y++)
         {

            auto psource = pimage->line_data(pimage->height() - y - 1);
            for (auto x = 0; x < pimage->width(); x++)
            {

               *p++ = psource->byte_red(pimage->color_indexes());
               *p++ = psource->byte_green(pimage->color_indexes());
               *p++ = psource->byte_blue(pimage->color_indexes());

               psource++;

            }

         }

      }

      image24.m_iWidth = pimage->width();
      image24.m_iHeight = pimage->height();

      return ::transfer(image24);

   }


   void context::clear(const ::color::color& color)
   {


   }


   void context::create_global_ubo(int iSize, int iFrameCount)
   {


   }


   void context::update_global_ubo(const ::block& block)
   {


   }


   void context::copy(::gpu::texture* ptexture)
   {


   }


   void context::on_create_texture(texture* ptexture)
   {


   }


   void context::on_take_snapshot(layer* player, texture* ptextureSource)
   {


   }


   void context::on_begin_draw_attach(::draw2d_gpu::graphics* pgpugraphics, const ::int_rectangle& rectangle)
   {

      draw2d_on_begin_draw(pgpugraphics, rectangle);

   }

   void context::on_end_draw_detach(::draw2d_gpu::graphics* pgpugraphics)
   {

      draw2d_on_end_draw(pgpugraphics);

   }


   void context::draw2d_on_begin_draw(::draw2d_gpu::graphics* pgpugraphics, const ::int_rectangle& rectangle)
   {

      if (pgpugraphics->m_egraphics == e_graphics_draw)
      {

         auto pgpurendererDraw2d = get_gpu_renderer();

         //if (pgpurendererDraw2d->m_pgpurendertarget)
         //{

         //   pgpurendererDraw2d->m_pgpurendertarget->on_before_begin_draw_frame(pgpugraphics);

         //}

         //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->start_frame();

         //pgpurendererDraw2d->m_pgpucontext->m_pgpudevice->start_stacking_layers();

         pgpurendererDraw2d->start_layer(rectangle);

      }

   }


   void context::frame_prefix()
   {


   }


   void context::frame_suffix()
   {


   }





   void context::draw2d_on_end_draw(::draw2d_gpu::graphics* pgpugraphics)
   {

      if (pgpugraphics->m_egraphics == e_graphics_draw)
      {

         auto pgpurendererDraw2d = m_pgpurendererOutput2;

         pgpurendererDraw2d->end_layer();

         //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->end_frame();

         //if (pgpurendererDraw2d->m_pgpurendertarget)
         //{

         //   pgpurendererDraw2d->m_pgpurendertarget->on_after_end_draw_frame(pgpugraphics);

         //}

      }

   }


   //render_target* context::draw2d_render_target()
   //{

   //   return nullptr;

   //}


   //render_target* context::graphics3d_render_target()
   //{

   //   return nullptr;

   //}


} // namespace gpu



