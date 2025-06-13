#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "cpu_buffer.h"
#include "render.h"
#include "renderer.h"
#include "render_target.h"
#include "snapshot.h"
#include "texture.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/context.h"


namespace gpu
{


   extern thread_local device * t_pgpudevice;

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

      if(::is_null(pcontext))
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


   void context::create_window_buffer(::windowing::window * pwindow)
   {

      ::cast < device > pgpudevice = m_pgpudevice;

      if (::is_null(pgpudevice))
      {

         throw ::exception(error_null_pointer);

      }

      _create_window_buffer(pwindow);

   }


   void context::_create_window_buffer(::windowing::window * pwindow)
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


   void context::start_gpu_context(const start_context_t & startcontext)
   {

      branch_synchronously();

      m_pgpudevice = startcontext.m_pgpudevice;

      rear_guard guard(this);

      _send([this, &startcontext]()
         {

            initialize_gpu_context(startcontext);

         });

   }


   void context::initialize_gpu_context(const start_context_t& startcontext)
   {

      ASSERT(is_current_task());

      m_pgpudevice = startcontext.m_pgpudevice;

      t_pgpudevice = m_pgpudevice;

      m_eoutput = startcontext.m_eoutput;

      on_create_context(startcontext);

   }


   void context::on_create_context(const start_context_t& startcontext)
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


   ::gpu::enum_output context::eoutput_for_begin_draw()
   {

      return ::gpu::e_output_gpu_buffer;

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


   void context::do_on_context(const ::procedure & procedure)
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


   bool context::create_offscreen_graphics_for_swap_chain_blitting(::draw2d_gpu::graphics* pgraphics, const ::int_size& size)
   {

      return false;

   }


   ::gpu::renderer* context::get_renderer(::gpu::enum_scene escene)
   {

      if (!m_pgpurenderer)
      {

         __øconstruct(m_pgpurenderer);

         m_pgpurenderer->initialize_renderer(this, m_eoutput, escene);

      }

      return m_pgpurenderer;

   }


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


   void context::start_composition()
   {

      m_pgpudevice->composition_start(this);

   }


   void context::end_composition()
   {

      m_pgpudevice->composition_end(this);

   }

   
   ::pointer < texture> context::create_texture(const ::int_size& size)
   {

      auto ptexture = __øcreate< texture>();

      ptexture->initialize_gpu_texture(size);

      on_create_texture(ptexture);

      return nullptr;

   }


   ::pointer < snapshot > context::take_snapshot(const ::int_rectangle& rectangleTarget)
   {

      auto psnapshot = __øcreate< snapshot>();

      auto ptexture = m_pgpurenderer->m_pgpurendertarget->current_texture();

      psnapshot->initialize_gpu_snapshot(this, ptexture, rectangleTarget);

      on_take_snapshot(psnapshot);

      return psnapshot;

   }

   void context::merge_snapshots(::pointer<::pointer_array < snapshot >>&& psnapshota)
   {


   }


   void context::on_create_texture(texture* ptexture)
   {


   }



   void context::on_take_snapshot(snapshot* psnapshot)
   {


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



