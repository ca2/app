#include "framework.h"
#include "approach.h"
#include "context.h"
#include "device.h"
#include "cpu_buffer.h"
#include "render.h"
#include "renderer.h"
#include "types.h"
//#include "_gpu.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/system.h"
////#include "aura/graphics/draw2d/_component.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/context.h"
#include "aura/windowing/window.h"


namespace gpu
{


   device::device()
   {

      m_bCreated = false;

   }


   device::~device()
   {

   }


   void device::initialize_gpu_device(::gpu::approach  * pgpuapproach, ::windowing::window* pwindow, const ::int_rectangle & rectanglePlacement, bool bAddSwapChainSupport)
   {

      m_pgpuapproach = pgpuapproach;

      m_pwindow = pwindow;


      //::e_status estatus = 
      //::particle::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }



   ::pointer < ::gpu::context > device::allocate_context(::particle* pparticle)
   {

      auto pgpucontext = pparticle->__øcreate< ::gpu::context >();

      return pgpucontext;

   }


   ::pointer < ::gpu::context > device::start_gpu_output_context(::particle* pparticle, const ::gpu::enum_output& eoutput, const ::int_rectangle& rectanglePlacement)
   {

      auto pgpucontext = start_gpu_context(
         start_gpu_output_context_t
         {
            pparticle,
            this,
            eoutput,
            rectanglePlacement
         });

      return pgpucontext;

   }


   ::pointer < ::gpu::context > device::start_cpu_buffer_context(::particle* pparticle, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_rectangle& rectanglePlacement)
   {

      auto pgpucontext = start_gpu_context(
         start_cpu_buffer_context_t
         {
            pparticle,
            this,
            callbackOnImagePixels,
            rectanglePlacement
         });

      return pgpucontext;

   }


   ::pointer < ::gpu::context > device::start_swap_chain_context(::particle* pparticle, ::windowing::window* pwindow)
   {

      auto pgpucontext = start_gpu_context(
         start_swap_chain_context_t
         {
            pparticle,
            this,
            pwindow
         });

      return pgpucontext;

   }


   ::pointer < ::gpu::context > device::start_gpu_context(const start_context_t& startcontext)
   {

      auto pgpucontext = allocate_context(startcontext.m_pparticle);

      if (!pgpucontext)
      {

         throw ::exception(error_resource);

      }

      pgpucontext->m_pgpudevice = this;

      pgpucontext->start_gpu_context(startcontext);

      return pgpucontext;

   }


   bool device::make_current(::gpu::context* pgpucontext)
   {

      if (m_itaskCurrentGpuContext == ::current_itask()
         && m_pgpucontextCurrent2 == pgpucontext)
      {

         return false;

      }

      if (::is_set(m_pgpucontextCurrent2))
      {

         throw ::exception(error_wrong_state, "device is in use by other context");

      }

      if (m_itaskCurrentGpuContext.is_set())
      {

         throw ::exception(error_wrong_state, "HGLRC is in use in other thread");

      }

      ::e_status estatus = ::success;

      bool bMadeCurrentNow = false;

      on_make_current();

      m_pgpucontextCurrent2 = pgpucontext;

      m_itaskCurrentGpuContext = ::current_itask();

      return bMadeCurrentNow;

   }


   void device::release_current(::gpu::context* pgpucontext)
   {

      if (!m_pgpucontextCurrent2)
      {

         // There is no active context in the device, no nothing to release;

         return;

      }
      else if (!m_itaskCurrentGpuContext)
      {

         throw ::exception(error_wrong_state, "HGLRC is in use in other thread");

      }
      else if (m_itaskCurrentGpuContext != ::current_itask())
      {

         throw ::exception(error_wrong_state, "HGLRC is taken by other thread");

      }
      
      on_release_current();

      m_itaskCurrentGpuContext = {};

      m_pgpucontextCurrent2.release();

   }


   void device::on_make_current()
   {


   }


   void device::on_release_current()
   {



   }



   //void device::draw()
   //{
   //   //
   //   //      if (m_VAO != 0)
   //   //      {
   //   //
   //   //         //return ::success;
   //   //         return;
   //   //
   //   //      }
   //   //      //glGenBuffers(1, &VAO);
   //   ////      float vertices[] = {
   //   //         // positions         // colors
   //   //  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
   //   //    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
   //   //      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   //   //      //};
   //   //      float vertices[] = {
   //   //         // first triangle
   //   //          1.f,  1.f, 0.0f,  // top right
   //   //          1.f, -1.f, 0.0f,  // bottom right
   //   //         -1.f,  1.f, 0.0f,  // top left
   //   //         // second triangle
   //   //          1.f, -1.f, 0.0f,  // bottom right
   //   //         -1.f, -1.f, 0.0f,  // bottom left
   //   //         -1.f,  1.f, 0.0f   // top left
   //   //      };

   //         //glGenVertexArrays(1, &m_VAO);
   //         //glGenBuffers(1, &m_VBO);
   //         //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   //         //glBindVertexArray(m_VAO);

   //         //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   //         //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   //         //// position attribute
   //         //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   //         //glEnableVertexAttribArray(0);
   //         //// color attribute
   //         ////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
   //         ////glEnableVertexAttribArray(1);

   //         //return ::success;
   //}


   //void device::prepare_for_gpu_read()
   //{

   //   //return ::success;
   //   swap_buffers();

   //}


   //void device::start_drawing()
   //{

   //   //glClearColor(0.2f, 0.3f, 0.3f, 0.5f);

   //   //glClear(GL_COLOR_BUFFER_BIT);


   //   //if (m_pprogram && m_pprogram->m_pshader)
   //   //{

   //   //   m_pprogram->m_pshader->use();

   //   //}

   //   //// be sure to activate the shader
   //   ////glUseProgram(shaderProgram);

   //   //// update the uniform color
   //   ////float timeValue = glfwGetTime();
   //   ////float greenValue = sin(timeValue) / 2.0f + 0.5f;
   //   ////int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
   //   ////glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

   //   //return ::success;

   //}


   //void device::global_transform()
   //{

   //}


   //void device::render()
   //{

   //   //glBindVertexArray(m_VAO);

   //   //glDrawArrays(GL_TRIANGLES, 0, 6);

   //   //return ::success;

   //}


   //void device::set_bitmap_1(::image::image* pimage)
   //{



   //}


   //void device::swap_buffers()
   //{


   //}


   //void device::create_window_buffer(void* pHwnd)
   //{

   //   ::cast < approach > papproach = m_papproach;

   //   if (::is_null(papproach))
   //   {

   //      throw ::exception(error_null_pointer);

   //   }

   //   //__øconstruct(m_pbuffer);

   //   //m_pbuffer->m_pimage = image()->create_image(size);

   //   //if (!::is_ok(m_pbuffer->m_pimage))
   //   //{

   //   //   throw ::exception(error_resource);

   //   //}

   //   _create_window_buffer(pHwnd);

   //   //if(!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return ::success_none;

   //}


   //void device::_create_window_buffer(void* pHwnd)
   //{

   //   //return ::success_none;

   //}


   //void device::create_offscreen_buffer(const ::int_size& size)
   //{

   //   send([this, size]()
   //      {

   //         ::cast < approach > papproach = m_papproach;

   //         if (::is_null(papproach))
   //         {

   //            throw ::exception(error_null_pointer);

   //         }

   //         __defer_construct(m_pcpubuffer);

   //         m_pcpubuffer->initialize_cpu_buffer(this);

   //         m_pcpubuffer->set_size(size);

   //         _create_offscreen_buffer(size);

   //         //if(!estatus)
   //         //{

   //         //   return estatus;

   //         //}

   //         //return ::success_none;

   //         m_bCreated = true;

   //      });

   //}


   //void device::defer_create_window_context(::windowing::window* pwindow)
   //{

   //   send([this, pwindow]()
   //      {

   //         //::pointer<::aura::system>psystem = system();

   //         //auto pgpu = application()->get_gpu();

   //         //if (::is_null(pgpu))
   //         //{

   //         //   throw ::exception(error_null_pointer);

   //         //}

   //         //__defer_construct(m_pcpubuffer);

   //         //m_pcpubuffer->m_pgpucontext = this;

   //         ////m_pbuffer->m_pimage = image()->create_image(size);

   //         //m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

   //         //if (m_pcpubuffer->m_pixmap.nok())
   //         //{

   //         //   throw ::exception(error_resource);

   //         //}

   //         _defer_create_window_context(pwindow);

   //         //if(!estatus)
   //         //{

   //         //   return estatus;

   //         //}

   //         //return ::success_none;

   //         m_bCreated = true;

   //      });

   //}


   //void device::_create_offscreen_buffer(const ::int_size& size)
   //{

   //   //return ::success_none;

   //}


   //void device::_defer_create_window_context(::windowing::window* pwindow)
   //{

   //   //return ::success_none;

   //}


   //void device::resize_offscreen_buffer(const ::int_size& size)
   //{

   //   send([this, size]()
   //      {

   //         if (!m_pcpubuffer)
   //         {

   //            return create_offscreen_buffer(size);

   //         }

   //         synchronous_lock synchronouslock(m_pcpubuffer->synchronization());

   //         m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

   //      });

   //}


   //void device::start_gpu_context(const start_context_t& startcontext)
   //{

   //   branch_synchronously();

   //   _send([this, &startcontext]()
   //      {

   //         initialize_gpu_context(startcontext);

   //         //            run_vulkan_example();



   //         //m_pimpact->m_ptaskEngine.release();

   //      });
   //   //pgpucontext->initialize_gpu_context(this, eoutput, pwindow, rectanglePlacement);

   //   //return pgpucontext;

   //}


   //void device::initialize_gpu_context(const start_context_t& startcontext)
   //{

   //   ASSERT(is_current_task());

   //   m_papproach = startcontext.m_papproach;

   //   m_eoutput = startcontext.m_eoutput;

   //   if (m_eoutput == ::gpu::e_output_cpu_buffer
   //      && startcontext.m_callbackImage32CpuBuffer
   //      && !m_callbackImage32CpuBuffer)
   //   {

   //      m_callbackImage32CpuBuffer = startcontext.m_callbackImage32CpuBuffer;

   //   }

   //   on_create_context(startcontext);

   //}


   //void device::on_create_context(const start_context_t& startcontext)
   //{


   //}


   //bool device::task_iteration()
   //{

   //   if (!::thread::task_iteration())
   //   {

   //      return false;

   //   }

   //   for (auto prender : m_rendera)
   //   {

   //      if (!prender->render_step())
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   void device::lock_context()
   {

      //return ::success;

   }


   void device::unlock_context()
   {

      //return ::success;

   }


   //void device::make_current()
   //{

   //   //return ::success_none;

   //}


   //void device::destroy_offscreen_buffer()
   //{

   //   //return ::success_none;

   //}


   //::pointer<::gpu::shader> device::create_shader(
   //   const ::file::path& pathVert,
   //   const ::file::path& pathFrag,
   //   const ::array<::gpu::shader::enum_descriptor_set_slot>& eslota,
   //   const ::particle_pointer& pLocalDescriptorSet,
   //   const ::particle_pointer& pVertexInput,
   //   const ::gpu::property* pproperties,
   //   ::gpu::shader::enum_flag eflag)
   //{

   //   auto pshader = __øcreate < ::gpu::shader >();

   //   pshader->initialize_shader(this, pathVert, pathFrag, eslota, pLocalDescriptorSet, pVertexInput, pproperties, eflag);

   //   return pshader;

   //}




   //::int_size device::size()
   //{

   //   return m_size;

   //}


   //::gpu::renderer* device::get_renderer()
   //{

   //   if (!m_prenderer)
   //   {

   //      __øconstruct(m_prenderer);

   //      m_prenderer->initialize_renderer(this);

   //   }

   //   return m_prenderer;

   //}


   //string device::_001GetIntroProjection()
   //{

   //   string strVersion = get_shader_version_text();


   //   string strProjection =
   //      "layout(glm::vec3 = 0) in vec3 aPos;\n"
   //      "layout(glm::vec3 = 1) in vec3 aColor;\n"
   //      "/* out vec3 ourColor; */\n"
   //      "out vec3 ourPosition;\n"
   //      "\n"
   //      "void main()\n"
   //      "{\n"
   //      "   gl_Position = vec4(aPos, 1.0);\n"
   //      "   /* ourColor = aColor;*/\n"
   //      "   ourPosition = aPos;\n"
   //      "}\n";

   //   return strProjection;
   //}


   //string device::_001GetIntroFragment()
   //{

   //   string strVersion = get_shader_version_text();

   //   string strFragment =
   //      "uniform vec2 resolution;\n"
   //      "uniform float time;\n"
   //      "uniform vec2 mouse;\n"
   //      "uniform sampler2D backbuffer;\n"
   //      "\n"
   //      "void main(void) {\n"
   //      "vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / minimum(resolution.x(), resolution.y());\n"
   //      "\n"
   //      "gl_FragColor = vec4(uv, uv/2.0);\n"
   //      "}\n";

   //   return strFragment;

   //}


   bool device::is_mesa()
   {

      return false;

   }


   string device::load_fragment(const ::string& pszPath, enum_shader_source& eshadersource)
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


   string device::get_shader_version_text()
   {

      return "version 330 core";

   }


   void device::on_top_end_frame()
   {


   }


   //void device::set_matrix_uniform(const ::gpu::payload& payloadMatrix)
   //{

   //   throw interface_only();

   //}


   void device::translate_shader(string& strFragment)
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


   void device::_translate_shader(string_array& stra)
   {

   }


   //image_data device::image32(const ::payload& payloadFile)
   //{

   //   auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

   //   class image_data image32;

   //   image32.m_memory.set_size(pimage->area() * 4);

   //   {


   //      auto p = image32.m_memory.data();

   //      for (auto y = 0; y < pimage->height(); y++)
   //      {

   //         auto psource = pimage->line_data(pimage->height() - y - 1);
   //         for (auto x = 0; x < pimage->width(); x++)
   //         {

   //            *p++ = psource->byte_red(pimage->color_indexes());
   //            *p++ = psource->byte_green(pimage->color_indexes());
   //            *p++ = psource->byte_blue(pimage->color_indexes());
   //            *p++ = psource->byte_opacity(pimage->color_indexes());

   //            psource++;

   //         }

   //      }

   //   }

   //   image32.m_iWidth = pimage->width();
   //   image32.m_iHeight = pimage->height();

   //   return ::transfer(image32);


   //}


   //image_data device::image24(const ::payload& payloadFile)
   //{

   //   auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

   //   class image_data image24;

   //   image24.m_memory.set_size(pimage->area() * 3);

   //   {


   //      auto p = image24.m_memory.data();

   //      for (auto y = 0; y < pimage->height(); y++)
   //      {

   //         auto psource = pimage->line_data(pimage->height() - y - 1);
   //         for (auto x = 0; x < pimage->width(); x++)
   //         {

   //            *p++ = psource->byte_red(pimage->color_indexes());
   //            *p++ = psource->byte_green(pimage->color_indexes());
   //            *p++ = psource->byte_blue(pimage->color_indexes());

   //            psource++;

   //         }

   //      }

   //   }

   //   image24.m_iWidth = pimage->width();
   //   image24.m_iHeight = pimage->height();

   //   return ::transfer(image24);

   //}


   //void device::clear(const ::color::color& color)
   //{


   //}




} // namespace gpu



