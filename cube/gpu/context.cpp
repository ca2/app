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
//#include "_defer.h"


namespace gpu
{

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

      auto pcontextUpper = pcontext->m_pgpudevice->m_pgpucontextCurrent2.m_p;

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

         //m_pcontextUpper->m_pgpudevice->m_itaskCurrentGpuContext = m_itaskUpper;

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


   //void context::initialize(::particle* pparticle)
   //{

   //   //::e_status estatus = 
   //   ::object::initialize(pparticle);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


   void context::draw()
   {
      //
      //      if (m_VAO != 0)
      //      {
      //
      //         //return ::success;
      //         return;
      //
      //      }
      //      //glGenBuffers(1, &VAO);
      ////      float vertices[] = {
      //         // positions         // colors
      //  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
      //    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
      //      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
      //      //};
      //      float vertices[] = {
      //         // first triangle
      //          1.f,  1.f, 0.0f,  // top right
      //          1.f, -1.f, 0.0f,  // bottom right
      //         -1.f,  1.f, 0.0f,  // top left
      //         // second triangle
      //          1.f, -1.f, 0.0f,  // bottom right
      //         -1.f, -1.f, 0.0f,  // bottom left
      //         -1.f,  1.f, 0.0f   // top left
      //      };

            //glGenVertexArrays(1, &m_VAO);
            //glGenBuffers(1, &m_VBO);
            //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            //glBindVertexArray(m_VAO);

            //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            //// position attribute
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            //glEnableVertexAttribArray(0);
            //// color attribute
            ////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            ////glEnableVertexAttribArray(1);

            //return ::success;
   }


   void context::prepare_for_gpu_read()
   {

      //return ::success;
      swap_buffers();

   }


   void context::start_drawing()
   {

      //glClearColor(0.2f, 0.3f, 0.3f, 0.5f);

      //glClear(GL_COLOR_BUFFER_BIT);


      //if (m_pprogram && m_pprogram->m_pshader)
      //{

      //   m_pprogram->m_pshader->use();

      //}

      //// be sure to activate the shader
      ////glUseProgram(shaderProgram);

      //// update the uniform color
      ////float timeValue = glfwGetTime();
      ////float greenValue = sin(timeValue) / 2.0f + 0.5f;
      ////int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      ////glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      //return ::success;

   }


   void context::global_transform()
   {

   }


   void context::render()
   {

      //glBindVertexArray(m_VAO);

      //glDrawArrays(GL_TRIANGLES, 0, 6);

      //return ::success;

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

      //__øconstruct(m_pbuffer);

      //m_pbuffer->m_pimage = image()->create_image(size);

      //if (!::is_ok(m_pbuffer->m_pimage))
      //{

      //   throw ::exception(error_resource);

      //}

      _create_window_buffer(pwindow);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return ::success_none;

   }


   void context::_create_window_buffer(::windowing::window * pwindow)
   {

      //return ::success_none;

   }


   void context::create_cpu_buffer(const ::int_size& size)
   {

      send([this, size]()
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

            //if(!estatus)
            //{

            //   return estatus;

            //}

            //return ::success_none;

            m_bCreated = true;

         });

   }


   void context::defer_create_window_context(::windowing::window* pwindow)
   {

      send([this, pwindow]()
         {

            //::pointer<::aura::system>psystem = system();

            //auto pgpu = application()->get_gpu();

            //if (::is_null(pgpu))
            //{

            //   throw ::exception(error_null_pointer);

            //}

            //__defer_construct(m_pcpubuffer);

            //m_pcpubuffer->m_pgpucontext = this;

            ////m_pbuffer->m_pimage = image()->create_image(size);

            //m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

            //if (m_pcpubuffer->m_pixmap.nok())
            //{

            //   throw ::exception(error_resource);

            //}

            _defer_create_window_context(pwindow);

            //if(!estatus)
            //{

            //   return estatus;

            //}

            //return ::success_none;

            m_bCreated = true;

         });

   }


   void context::_create_cpu_buffer(const ::int_size& size)
   {

      //return ::success_none;

   }


   void context::_defer_create_window_context(::windowing::window* pwindow)
   {

      //return ::success_none;

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

      rear_guard guard(this);

      _send([this, &startcontext]()
         {


            initialize_gpu_context(startcontext);

            //            run_vulkan_example();



            //m_pimpact->m_ptaskEngine.release();

         });
      //pgpucontext->initialize_gpu_context(this, eoutput, pwindow, rectanglePlacement);

      //return pgpucontext;

   }


   void context::initialize_gpu_context(const start_context_t& startcontext)
   {

      ASSERT(is_current_task());

      m_pgpudevice = startcontext.m_pgpudevice;

      m_eoutput = startcontext.m_eoutput;

      //if (m_eoutput == ::gpu::e_output_cpu_buffer
      //   && startcontext.m_callbackImage32CpuBuffer
      //   && !m_callbackImage32CpuBuffer)
      //{

      //   m_callbackImage32CpuBuffer = startcontext.m_callbackImage32CpuBuffer;

      //}

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



} // namespace gpu



