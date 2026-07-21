#include "framework.h"
#include "bred_approach.h"
#include "context.h"
#include "context_lease.h"
#include "device.h"
#include "cpu_buffer.h"
#include "frame_ephemeral.h"
#include "frame_storage.h"
#include "layer.h"
#include "render.h"
#include "renderer.h"
#include "render_target.h"
#include "swap_chain.h"
#include "texture.h"
#include "types.h"
#include "frame.h"
#include "acme/call.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/prototype/call.h"
#include "aura/platform/application.h"
#include "aura/platform/system.h"
////#include "aura/graphics/draw2d/_component.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/context.h"
#include "aura/windowing/window.h"
#include <assert.h>
#include <chrono>


namespace gpu
{

   //::pointer <::gpu::context > allocate_egl_context(::particle * pparticle);

   thread_local device* t_pgpudevice = nullptr;

   void thread_set_gpu_device(::gpu::device* pgpudevice)
   {

      t_pgpudevice = pgpudevice;

   }

   device::device()
   {

      m_edevicetarget = e_device_target_undefined;

      t_pgpudevice = this;

      m_bCreated = false;

   }


   device::~device()
   {

      shutdown_draw2d_context_pool();

   }


   void device::initialize_gpu_device_for_swap_chain(::gpu::approach * pgpuapproach, ::windowing::window* pwindow)
   {

      m_edevicetarget = e_device_target_swap_chain;

      m_pgpuapproach = pgpuapproach;

      m_pwindow = pwindow;

      m_pwindow->m_ptaskUpdateScreen = this;

      //branch_synchronously();

   }


   void device::initialize_gpu_device_for_off_screen(::gpu::approach* pgpuapproach, const ::i32_rectangle& rectanglePlacement)
   {

      m_edevicetarget = e_device_target_off_screen;

      m_pgpuapproach = pgpuapproach;

      //branch_synchronously();

      //m_pwindow = pwindow;


      //::e_status estatus = 
      //::particle::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void device::_send(const ::procedure& procedure)
   //{

   //   auto procedureForward = [this, procedure]()
   //      {

   //         _synchronous_lock(this->synchronization());

   //            procedure();
   //         

   //      };

   //   ::thread::_send(procedureForward);

   //}


   //void device::_post(const ::procedure& procedure)
   //{
   //   auto procedureForward = [this, procedure]()
   //      {

   //         _synchronous_lock(this->synchronization());

   //         procedure();


   //      };

   //   ::thread::_post(procedureForward);
   //}



   ::pointer < ::gpu::context > device::allocate_context()
   {

      ::pointer < ::gpu::context > pgpucontext;

      pgpucontext = createø< ::gpu::context >();

      return pgpucontext;

   }


   ::file::path device::shader_path(const ::file::path& pathShader)
   {

      return pathShader;

   }


   ::gpu::payload device::load_dds(const ::scoped_string& scopedstrImagePath)
   {

      throw interface_only();

      return {};

   }


   ::gpu::layer* device::get_previous_layer(::gpu::layer * pgpulayer)
   {

      if (!m_pgpulayera)
      {

         return nullptr;

      }

      auto iFind = m_pgpulayera->find_first(pgpulayer);
      
      if (iFind <= 0)
      {

         return nullptr;

      }

      for(::i32 i = (::i32) iFind - 1; i >= 0; i--)
      {
         
         if (m_pgpulayera->element_at(i)->m_pgpurenderer == pgpulayer->m_pgpurenderer)
         {

            return m_pgpulayera->element_at(i);

         }

      }

      return nullptr;

   }


   //::pointer < ::gpu::context > device::start_gpu_output_context(const ::gpu::enum_output& eoutput, const ::i32_size& size)
   //{

   //   auto pgpucontext = start_gpu_context(eoutput, nullptr,  size);

   //   return pgpucontext;

   //}


   //::pointer < ::gpu::context > device::start_cpu_buffer_context(::particle* pparticle, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::i32_size& size)
   //{

   //   auto pgpucontext = start_gpu_context(
   //      start_cpu_buffer_context_t
   //      {
   //         pparticle,
   //         this,
   //         callbackOnImagePixels,
   //         rectanglePlacement
   //      });

   //   return pgpucontext;

   //}


   ::pointer < ::gpu::context > device::create_window_context(::windowing::window* pwindow)
   {
      
      auto pgpucontext = allocate_context();

      pgpucontext->m_etype = ::gpu::context::e_type_window;

      pgpucontext->create_window_context(this,pwindow);

      return pgpucontext;

   }


   ::pointer < ::gpu::context > device::create_gpu_context(const ::gpu::enum_output& eoutput, const ::gpu::enum_scene & escene, const ::i32_size& size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      auto pgpucontext = allocate_context();

      if (!pgpucontext)
      {

         throw ::exception(error_resource);

      }

      pgpucontext->m_pgpudevice = this;

      pgpucontext->create_gpu_context(this, eoutput, escene, size);

      return pgpucontext;

   }


   //::gpu::context* device::get_main_context()
   //{

   //   if (defer_constructø(m_pgpucontextMain))
   //   {

   //      ::cast < ::user::interaction > puserinteractionMain = m_papplication->m_pacmeuserinteractionMain;

   //      auto pwindowMain = puserinteractionMain->window();

   //      auto rectangleMainWindow = pwindowMain->get_window_rectangle();

   //      m_pgpucontextMain->create_gpu_context(
   //            this,
   //            ::gpu::e_output_gpu_buffer,
   //            rectangleMainWindow.size()
   //         );

   //   }

   //   return m_pgpucontextMain;

   //}


   ::pointer < ::gpu::context > device::create_draw2d_context(const ::gpu::enum_output& eoutput, const ::i32_size& size)
   {

      //auto pgpucontext = createø<::gpu::context>();

      auto pgpucontext = allocate_context();

      pgpucontext->create_draw2d_context(this, eoutput, size);

      return pgpucontext;

   }


   namespace
   {


      ::i64 draw2d_context_pool_steady_nanoseconds()
      {

         return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
            ::std::chrono::steady_clock::now().time_since_epoch()).count();

      }


      void update_draw2d_context_pool_high_water(
         ::std::atomic<::u64> & highWater,
         ::u64 uActive)
      {

         auto uHighWater = highWater.load(::std::memory_order_relaxed);

         while (uActive > uHighWater
            && !highWater.compare_exchange_weak(
               uHighWater,
               uActive,
               ::std::memory_order_relaxed))
         {

         }

      }


   } // namespace


   ::gpu::context_lease device::acquire_draw2d_context(
      const ::gpu::enum_output & eoutput,
      const ::i32_size & size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      if (m_bDraw2dContextPoolShuttingDown.load(::std::memory_order_acquire))
      {

         throw ::exception(error_wrong_state, "draw2d context pool is shutting down");

      }

      ::pointer<::gpu::context> pcontext;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (m_bDraw2dContextPoolShuttingDown.load(::std::memory_order_relaxed))
         {

            throw ::exception(error_wrong_state, "draw2d context pool is shutting down");

         }

         for (::collection::index i = 0; i < m_contextaDraw2dIdle.get_count(); ++i)
         {

            auto pcontextCandidate = m_contextaDraw2dIdle[i];

            if (pcontextCandidate->m_eoutput == eoutput
               && pcontextCandidate->m_etype == ::gpu::context::e_type_draw2d)
            {

               pcontext = pcontextCandidate;
               m_contextaDraw2dIdle.erase_at(i);
               break;

            }

         }

      }

      auto bReused = pcontext.is_set();

      if (bReused)
      {

         pcontext->send(
            [pcontext, size]()
            {

               pcontext->m_pgpucompositor = nullptr;
               pcontext->on_resize(size);

            });

      }
      else
      {

         if (m_bDraw2dContextPoolShuttingDown.load(::std::memory_order_acquire))
         {

            throw ::exception(error_wrong_state, "draw2d context pool is shutting down");

         }

         pcontext = create_draw2d_context(eoutput, size);
         pcontext->m_pgpucompositor = nullptr;

      }

      if (m_bDraw2dContextPoolShuttingDown.load(::std::memory_order_acquire))
      {

         return_draw2d_context(::transfer(pcontext), true);

         throw ::exception(error_wrong_state, "draw2d context pool is shutting down");

      }

      auto bDiagnostics = m_papplication
         && m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed);

      auto uActive = m_uDraw2dContextPoolActive.fetch_add(
         1,
         ::std::memory_order_relaxed) + 1;

      update_draw2d_context_pool_high_water(
         m_uDraw2dContextPoolHighWater,
         uActive);

      if (bDiagnostics)
      {

         m_uDraw2dContextPoolAcquisitions.fetch_add(1, ::std::memory_order_relaxed);

         if (bReused)
         {

            m_uDraw2dContextPoolReuses.fetch_add(1, ::std::memory_order_relaxed);

         }
         else
         {

            m_uDraw2dContextPoolCreations.fetch_add(1, ::std::memory_order_relaxed);

         }

         report_draw2d_context_pool_diagnostics_if_due();

      }

      return {this, pcontext};

   }


   void device::return_draw2d_context(
      ::pointer<::gpu::context> pcontext,
      bool bDamaged)
   {

      if (!pcontext)
      {

         return;

      }

      pcontext->send(
         [pcontext]()
         {

            pcontext->defer_unbind_shader();
            pcontext->m_prendertargetBound.release();
            pcontext->m_pgpucompositor = nullptr;

         });

      auto bShuttingDown = m_bDraw2dContextPoolShuttingDown.load(
         ::std::memory_order_acquire);

      if (!bDamaged && !bShuttingDown)
      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (!m_bDraw2dContextPoolShuttingDown.load(::std::memory_order_relaxed))
         {

            m_contextaDraw2dIdle.add(pcontext);
            pcontext.release();

         }

      }

      auto uActive = m_uDraw2dContextPoolActive.load(::std::memory_order_relaxed);

      while (uActive > 0
         && !m_uDraw2dContextPoolActive.compare_exchange_weak(
            uActive,
            uActive - 1,
            ::std::memory_order_relaxed))
      {

      }

      if (m_papplication
         && m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         report_draw2d_context_pool_diagnostics_if_due();

      }

   }


   void device::shutdown_draw2d_context_pool()
   {

      if (m_bDraw2dContextPoolShuttingDown.exchange(
         true,
         ::std::memory_order_acq_rel))
      {

         return;

      }

      ::pointer_array<::gpu::context> contextaIdle;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         while (m_contextaDraw2dIdle.has_element())
         {

            contextaIdle.add(m_contextaDraw2dIdle.pop());

         }

      }

      contextaIdle.erase_all();

   }


   void device::report_draw2d_context_pool_diagnostics_if_due()
   {

      if (!m_papplication
         || !m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         return;

      }

      auto uGeneration =
         m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(
            ::std::memory_order_relaxed);
      auto uGenerationLast =
         m_uDraw2dContextPoolDiagnosticsGenerationLast.load(
            ::std::memory_order_relaxed);

      if (uGeneration != uGenerationLast)
      {

         m_uDraw2dContextPoolDiagnosticsGenerationLast.store(
            uGeneration,
            ::std::memory_order_relaxed);
         m_iDraw2dContextPoolNextReportNanoseconds.store(
            0,
            ::std::memory_order_relaxed);

      }

      auto iNowNanoseconds = draw2d_context_pool_steady_nanoseconds();
      auto iDeadlineNanoseconds =
         m_iDraw2dContextPoolNextReportNanoseconds.load(
            ::std::memory_order_relaxed);

      if (iNowNanoseconds < iDeadlineNanoseconds)
      {

         return;

      }

      auto iIntervalMilliseconds = maximum(
         100,
         minimum(
            60'000,
            m_papplication->m_gpu.m_iPerformanceDiagnosticsIntervalMilliseconds.load(
               ::std::memory_order_relaxed)));
      auto iNextNanoseconds = iNowNanoseconds
         + (::i64) iIntervalMilliseconds * 1'000'000;

      if (!m_iDraw2dContextPoolNextReportNanoseconds.compare_exchange_strong(
         iDeadlineNanoseconds,
         iNextNanoseconds,
         ::std::memory_order_relaxed))
      {

         return;

      }

      ::collection::count cIdle;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         cIdle = m_contextaDraw2dIdle.get_count();

      }

      information() << "[gpu.context_pool] acquisitions="
         << m_uDraw2dContextPoolAcquisitions.exchange(0, ::std::memory_order_relaxed)
         << " reuses="
         << m_uDraw2dContextPoolReuses.exchange(0, ::std::memory_order_relaxed)
         << " creations="
         << m_uDraw2dContextPoolCreations.exchange(0, ::std::memory_order_relaxed)
         << " active="
         << m_uDraw2dContextPoolActive.load(::std::memory_order_relaxed)
         << " high_water="
         << m_uDraw2dContextPoolHighWater.load(::std::memory_order_relaxed)
         << " idle=" << cIdle;

   }


   //bool device::make_current(::gpu::context* pgpucontext)
   //{

   //   if (m_itaskCurrentGpuContext == ::current_itask()
   //      && pgpucontext == current_context())
   //   {

   //      return false;

   //   }

   //   if (::is_set(current_context()))
   //   {

   //      throw ::exception(error_wrong_state, "device is in use by other context");

   //   }

   //   if (m_itaskCurrentGpuContext.is_set())
   //   {

   //      throw ::exception(error_wrong_state, "HGLRC is in use in other thread");

   //   }

   //   ::e_status estatus = ::success;

   //   bool bMadeCurrentNow = false;

   //   on_make_current();

   //   m_pgpucontextCurrent4 = pgpucontext;

   //   if (m_pgpucontextCurrent4->m_itask != ::current_itask())
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   m_itaskCurrentGpuContext = ::current_itask();

   //   return bMadeCurrentNow;

   //}


   //void device::release_current(::gpu::context* pgpucontext)
   //{

   //   if (::is_null(current_context()))
   //   {

   //      // There is no active context in the device, no nothing to release;

   //      return;

   //   }
   //   else if (!m_itaskCurrentGpuContext)
   //   {

   //      throw ::exception(error_wrong_state, "HGLRC is in use in other thread");

   //   }
   //   else if (m_itaskCurrentGpuContext != ::current_itask())
   //   {

   //      throw ::exception(error_wrong_state, "HGLRC is taken by other thread");

   //   }
   //   else if (pgpucontext != current_context())
   //   {

   //      throw ::exception(error_wrong_state, "should release current context");

   //   }
   //   
   //   on_release_current();

   //   m_itaskCurrentGpuContext = {};

   //   m_pgpucontextCurrent4.release();

   //}


   //void device::on_make_current()
   //{


   //}


   //void device::on_release_current()
   //{



   //}



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
   //   ////      ::f32 vertexes[] = {
   //   //         // positions         // colors
   //   //  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
   //   //    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
   //   //      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   //   //      //};
   //   //      ::f32 vertexes[] = {
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
   //         //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

   //         //// position attribute
   //         //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(::f32), (void*)0);
   //         //glEnableVertexAttribArray(0);
   //         //// color attribute
   //         ////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(::f32), (void*)(3 * sizeof(::f32)));
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
   //   ////::f32 timeValue = glfwGetTime();
   //   ////::f32 greenValue = sin(timeValue) / 2.0f + 0.5f;
   //   ////::i32 vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
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

   //   //constructø(m_pbuffer);

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


   //void device::create_offscreen_buffer(const ::i32_size& size)
   //{

   //   send([this, size]()
   //      {

   //         ::cast < approach > papproach = m_papproach;

   //         if (::is_null(papproach))
   //         {

   //            throw ::exception(error_null_pointer);

   //         }

   //         defer_constructø(m_pcpubuffer);

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

   //         //defer_constructø(m_pcpubuffer);

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


   //void device::_create_offscreen_buffer(const ::i32_size& size)
   //{

   //   //return ::success_none;

   //}


   //void device::_defer_create_window_context(::windowing::window* pwindow)
   //{

   //   //return ::success_none;

   //}


   //void device::resize_offscreen_buffer(const ::i32_size& size)
   //{

   //   send([this, size]()
   //      {

   //         if (!m_pcpubuffer)
   //         {

   //            return create_offscreen_buffer(size);

   //         }

   //         synchronous_lock synchronouslock(m_pcpubuffer->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //         m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

   //      });

   //}


   //void device::start_gpu_context(const start_context_t& startcontext)
   //{

   //   branch_synchronously();

   //   sendø() << [this, &startcontext]()
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


   //::gpu::context* device::current_context()
   //{

   //   return m_pgpucontextCurrent4;

   //}


void device::create_main_context(::acme::windowing::window * pacmewindowingwindow)
{

         if (m_pgpucontextMain)
   {
            throw ::exception(error_wrong_state, "main context already created");
   }

      m_pgpucontextMain = allocate_context();

      ::gpu::enum_output eoutput;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         m_pgpucontextMain->m_etype = ::gpu::context::e_type_window;

         eoutput = ::gpu::e_output_swap_chain;
      }
      else
      {

         m_pgpucontextMain->m_etype = ::gpu::context::e_type_generic;

         eoutput = ::gpu::e_output_gpu_buffer;

         //eoutput = ::gpu::e_output_cpu_buffer;

      }

      m_eoutput = eoutput;

      m_pgpucontextMain->m_eoutput = eoutput;

      auto pwindow = pacmewindowingwindow;

      if (::is_null(pwindow))
      {

         pwindow = m_papplication->m_pacmeuserinteractionMain->acme_windowing_window();
      }

      auto sizeWindow = pwindow->get_window_rectangle().size();

      if (!m_pgpucontextMain->m_itask && pwindow)
      {

         if (m_pgpucontextMain->m_etype == ::gpu::context::e_type_window)
         {

            m_pgpucontextMain->create_window_context(this, pwindow);

         }
         else
         {

            m_pwindow = pwindow;

            m_pgpucontextMain->create_gpu_context(this, m_eoutput, e_scene_2d, sizeWindow);
            //m_pgpucontextMain->create_cpu_buffer(sizeWindow);

         }

         /*m_pgpucontextMain->branch_synchronously();

         m_pgpucontextMain->m_pgpudevice = this;

         m_pgpucontextMain->_send(
            [this, eoutput, pwindow]()
            {
               m_pgpucontextMain->initialize_gpu_context(this, eoutput, pwindow,
                                                         pwindow->get_window_rectangle().size());
            });*/
      }
   



         //auto pcontext = main_context(pacmewindowingwindow);

   //pcontext->m_pgpudevice = this;

   //pcontext->_send(
   //   [this, pcontext]()
   //   {
   //      pcontext->initialize_gpu_context(this, ::gpu::e_output_gpu_buffer, m_pwindow,
   //                                       m_pwindow->get_window_rectangle().size());

   //      auto pswapchain = pcontext->get_swap_chain();

   //      pswapchain->initialize_swap_chain_window(pcontext, m_pwindow);
   //   });
}


   ::gpu::context* device::main_context()
   {

      return m_pgpucontextMain;

      //if(!m_pgpucontextMainWindow)
      //{

      //   ::cast < ::user::interaction > puserinteractionMain = m_papplication->m_pacmeuserinteractionMain;

      //   auto pwindowMain = puserinteractionMain->window();

      //   m_pgpucontextMainWindow = create_window_context(pwindowMain);

      //}

      //return m_pgpucontextMainWindow;

   }


   ::gpu::context* device::main_draw2d_context()
   {

      if (!m_pgpucontextMainDraw2d)
      {

         constructø(m_pgpucontextMainDraw2d);

         m_pgpucontextMainDraw2d->m_etype = ::gpu::context::e_type_draw2d;

         m_pgpucontextMainDraw2d->m_eoutput = ::gpu::e_output_gpu_buffer;

         m_pgpucontextMainDraw2d->m_pgpudevice = this;

         ::cast < ::user::interaction > puserinteraction = m_papplication->m_pacmeuserinteractionMain;

         if (!m_pgpucontextMainDraw2d->m_itask
            && puserinteraction->m_pacmewindowingwindow)
         {

            m_pgpucontextMainDraw2d->branch_synchronously();

            m_pgpucontextMainDraw2d->sendø() << [this, puserinteraction]()
               {

                  auto pinteraction = (::user::interaction*)puserinteraction.m_p;

                  auto eoutput = m_pgpucontextMainDraw2d->m_eoutput;

                  auto pwindow = pinteraction->window();

                  auto size = pwindow->get_window_rectangle().size();

                  m_pgpucontextMainDraw2d->initialize_gpu_context(
                     this,
                     eoutput,
                     pwindow,
                     size
                  );

               };

         }

      }

      return m_pgpucontextMainDraw2d;

   }


   ::pointer<::gpu::context> device::create_work_context()
   {

      auto pgpucontext = createø<::gpu::context>();

      pgpucontext->m_etype = ::gpu::context::e_type_generic;

      pgpucontext->m_eoutput = ::gpu::e_output_none;

      pgpucontext->m_pgpudevice = this;

      ::cast<::user::interaction> puserinteraction = m_papplication->m_pacmeuserinteractionMain;

      if (!pgpucontext->m_itask && puserinteraction->m_pacmewindowingwindow)
      {

         pgpucontext->branch_synchronously();

         pgpucontext->sendø() << [this, puserinteraction, pgpucontext]()
         {
            
            auto pinteraction = (::user::interaction *)puserinteraction.m_p;

            auto eoutput = pgpucontext->m_eoutput;

            auto pwindow = pinteraction->window();

            auto size = pwindow->get_window_rectangle().size();

            pgpucontext->initialize_gpu_context(this, eoutput, pwindow, size);

         };

      }

      return pgpucontext;

   }


   ::gpu::context * device::work_context()
   {

      if (!m_pgpucontextWork)
      {

         m_pgpucontextWork = create_work_context();

      }

      return m_pgpucontextWork;

   }


   void * device::current_operating_system_gpu_context()
   {
      
      throw ::interface_only();
      
      return nullptr;
      
   }
   

   void device::lock_context()
   {

      //return ::success;

   }


   ::gpu::frame *device::current_frame() 
   {

      _synchronous_lock lock(this->synchronization());
      
      auto iFrameIndex = get_frame_index3();
      
      auto &pframe = m_framea.atø(iFrameIndex);

      if (defer_construct_newø(pframe))
      {

         pframe->initialize_gpu_frame();

      }

      return pframe;


   }


   void device::register_frame_context(::gpu::context *pcontext, ::gpu::layer *player)
   {

      _synchronous_lock lock(this->synchronization());

      m_postframecontextregistry.register_context(pcontext, player);

   }


   void device::dispatch_post_frame_contexts()
   {

      post_frame_context_registry_t::entry_array entrya;
      ::pointer<::gpu::context> pcontextMain;

      {

         _synchronous_lock lock(this->synchronization());

         entrya = m_postframecontextregistry.take_entries();
         pcontextMain = m_pgpucontextMain;

      }

      post_frame_context_registry_t::dispatch(
         std::move(entrya),
         pcontextMain,
         []()
         {

            return ::pointer<::gpu::layer>(::gpu::current_layer());

         },
         [](const ::pointer<::gpu::layer> &player)
         {

            ::gpu::set_current_layer(player);

         },
         [](const ::pointer<::gpu::context> &pcontext)
         {

            pcontext->on_end_frame();

         });

   }


   void device::start_frame()
   {

      {

         _synchronous_lock lock(this->synchronization());

         m_postframecontextregistry.clear();

      }

      start_stacking_layers();

      m_iFrameSerial2++;

      m_pgpucontextMain->on_new_frame();

      // m_iCurrentFrame3 = (m_iCurrentFrame3 + 1) % iFrameCount;

      auto &pframestorage = m_framestoragea.atø(m_iCurrentFrame3);

      if (!pframestorage)
      {

         constructø(pframestorage);

         pframestorage->initialize_gpu_frame_storage(this);
      }

      pframestorage->m_iBuffer = 0;

      pframestorage->m_iBufferOffset = 0;

      auto &pframeephemeral = m_frameephemerala.atø(m_iCurrentFrame3);

      constructø(pframeephemeral);

      _synchronous_lock lock(this->synchronization());

      auto pframe = current_frame();

      pframe->start_frame();

   }


   void device::end_frame()
   {

      on_end_frame();

      {

         _synchronous_lock lock(this->synchronization());

         auto pframe = current_frame();

         pframe->end_frame();

      }

      dispatch_post_frame_contexts();

   }


   //void device::start_offscreen_frame()
   //{

   //   auto iFrameCount = get_frame_count();

   //}

   //
   //void device::end_offscreen_frame()
   //{

   //   on_end_frame();

   //   _synchronous_lock lock(this->synchronization());

   //   auto pframe = current_frame();

   //   pframe->end_frame();

   //}


   void device::on_start_frame()
   {

   }


   void device::on_end_frame()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto procedureaOnTopFrameEnd = ::transfer(m_procedureaOnTopFrameEnd);

         for (auto &procedure: procedureaOnTopFrameEnd)
         {

            procedure();
         }
      }

      auto pframestorage = current_frame_storage();

      if (::is_set(pframestorage))
      {

         try
         {

            pframestorage->on_end_frame();
         }
         catch (...)
         {
         }
      }

      if (m_timeLast5s.elapsed() > 5_s)
      {

         m_timeLast5s.Now();

         m_papplication->post(
            [this]()
            {
               manage_retired_objects();
            });
      }
   }


   void device::defer_shader_memory(::memory &memory, const ::file::path &pathShader)
   {

      if (memory.is_empty())
      {

         auto path = this->shader_path(pathShader);

         if (path.contains("_ibl_hdr"))
         {

            information() << "_ibl_hdr";

         }

         memory = file()->as_memory(path);

      }

   }


   void device::on_initialize_gpu_device()
   {


   }


   void device::manage_retired_objects()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      for (::collection::index i = 0; i < m_shaderaRetire.size();)
      {

         auto &pshader = m_shaderaRetire[i];

         if (pshader->m_timeRetire.elapsed() > 15_s)
         {

            ::release(pshader);

            m_shaderaRetire.erase_at(i);
         }
         else
         {

            i++;
         }
      }
   }


   bool device::is_starting_frame()const
   {

      return m_iFrameSerial2 == m_iCurrentFrame3;

   }


   void device::restart_frame_counter()
   {

      if (this->get_frame_count() > 1)
      {

         m_iCurrentFrame3 = 0;
         m_iFrameSerial2 = -1;

         //m_pgpurenderer->m_prenderstate->on_happening(e_happening_reset_frame_counter);

      }

   }


   ::i32 device::get_frame_index3()
   {

      auto iFrameCount = this->get_frame_count();

      if (iFrameCount > 1)
      {

         return (::i32)(m_iCurrentFrame3 % iFrameCount);

      }
      else
      {

         return 0;

      }

   }


   ::i32 device::get_image_index()
   {

      if (this->get_frame_count() > 1)
      {

         return (::i32)m_iCurrentImage;
      }
      else
      {

         return 0;
      }

   }


   ::i32 device::get_frame_count()
   {

      return (::i32)m_iFrameCount;

   }



   
   pool_group* device::frame_pool_group(::i32 iFrameIndex)
   {

      auto & ppoolgroupFrame = m_poolgroupaFrame.element_at_grow(iFrameIndex);

      defer_construct_newø(ppoolgroupFrame);

      ppoolgroupFrame->m_pallocator = this;

      return ppoolgroupFrame;

   }


   ::pointer_array<::particle >* device::frame_particle_array(::i32 iFrameIndex)
   {
      
      auto& pparticleaFrame = m_particleaFrame.element_at_grow(iFrameIndex);

      if (!pparticleaFrame)
      {

         construct_newø(pparticleaFrame);

      }

      return pparticleaFrame;

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

   //   auto pshader = createø < ::gpu::shader >();

   //   pshader->initialize_shader(this, pathVert, pathFrag, eslota, pLocalDescriptorSet, pVertexInput, pproperties, eflag);

   //   return pshader;

   //}




   //::i32_size device::size()
   //{

   //   return m_size;

   //}


   //::gpu::renderer* device::get_renderer()
   //{

   //   if (!m_prenderer)
   //   {

   //      constructø(m_prenderer);

   //      m_prenderer->initialize_renderer(this);

   //   }

   //   return m_prenderer;

   //}


   //string device::_001GetIntroProjection()
   //{

   //   string strVersion = get_shader_version_text();


   //   string strProjection =
   //      "layout(floating_sequence3 = 0) in floating_sequence3 aPos;\n"
   //      "layout(floating_sequence3 = 1) in floating_sequence3 aColor;\n"
   //      "/* out floating_sequence3 ourColor; */\n"
   //      "out floating_sequence3 ourPosition;\n"
   //      "\n"
   //      "void main()\n"
   //      "{\n"
   //      "   gl_Position = floating_sequence4(aPos, 1.0);\n"
   //      "   /* ourColor = aColor;*/\n"
   //      "   ourPosition = aPos;\n"
   //      "}\n";

   //   return strProjection;
   //}


   //string device::_001GetIntroFragment()
   //{

   //   string strVersion = get_shader_version_text();

   //   string strFragment =
   //      "uniform floating_sequence2 resolution;\n"
   //      "uniform ::f32 time;\n"
   //      "uniform floating_sequence2 mouse;\n"
   //      "uniform sampler2D backbuffer;\n"
   //      "\n"
   //      "void main(void) {\n"
   //      "floating_sequence2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / minimum(resolution.x, resolution.y);\n"
   //      "\n"
   //      "gl_FragColor = floating_sequence4(uv, uv/2.0);\n"
   //      "}\n";

   //   return strFragment;

   //}


   //bool device::is_mesa()
   //{

   //   return false;

   //}


   string device::load_fragment(const ::scoped_string & scopedstrPath, enum_shader_source& eshadersource)
   {

      ::file::path path(scopedstrPath);

      string strFragment = file()->as_string(path);

      string strExtension = path.all_extensions();

      string strVersion = get_shader_version_text();

      if (strExtension.case_insensitive_begins("shadertoy"))
      {

         eshadersource = e_shader_source_shadertoy;

         strFragment =
            //"#" + strVersion + "\n"
            //"\n"
            //"precision highp ::f32;\n"
            "\n"
            "uniform floating_sequence2 iResolution;\n"
            "uniform ::f32 iTime;\n"
            "uniform floating_sequence2 iMouse;\n"
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




   ::i32 device::get_type_size(::gpu::enum_type etype)
   {

      switch (etype)
      {
      case e_type_i32: return sizeof(::i32);
      case e_type_f32: return sizeof(::f32);
      case e_type_seq4: return sizeof(floating_sequence4);
      case e_type_mat4: return sizeof(floating_matrix4);
      case e_type_seq3: return sizeof(floating_sequence3);
      case e_type_mat3: return sizeof(floating_matrix3);
      case e_type_seq2: return sizeof(floating_sequence2);
      case e_type_mat2: return sizeof(floating_matrix2);
      default:
         throw ::exception(error_wrong_state);

      }
      
   }


   void device::set_matrix4(void* p, const ::floating_matrix4& floating_matrix4)
   {

      *((::floating_matrix4*)p) = floating_matrix4;

   }


   void device::translate_shader(string& strFragment)
   {

      string_array_base stra;

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


   void device::_translate_shader(string_array_base& stra)
   {

   }


   void device::start_stacking_layers()
   {

      m_iLayerCount = 0;

   }


   layer * device::create_gpu_layer(renderer* pgpurenderer)
   {

      m_iLayer = m_iLayerCount;
      m_iLayerCount++;

      defer_construct_newø(m_pgpulayera);

      auto & player = m_pgpulayera->element_at_grow(m_iLayer);

      defer_constructø(player);

      auto iFrameIndex = pgpurenderer->render_target()->m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

      player->initialize_gpu_layer(pgpurenderer, iFrameIndex, m_iLayer);

      pgpurenderer->defer_update_renderer();

      //if (pgpurenderer->m_pgpurendertarget)
      //{

      //   player->m_pgputextureSource = pgpurenderer->m_pgpurendertarget->current_texture();

      //}

      return player;

   }


   void device::layer_end()
   {

      auto& layera = *m_pgpulayera;

      auto& player = layera[m_iLayer];

      player->layer_end();
      //player->take_snapshot();

      //return pgpulayer->texture()->m_pgpurenderer->m_pgpucontext->rectangle();

   }


   layer* device::current_layer()
   {
      
      if (m_iLayer < 0 || m_iLayer >= m_pgpulayera->get_count())
      {
      
         throw ::exception(error_wrong_state);

      }

      auto& layera = *m_pgpulayera;

      auto& player = layera[m_iLayer];

      return player;

   }


   ::gpu::queue *device::transfer_queue() { return nullptr; }


   ::gpu::queue *device::graphics_queue() { return nullptr; }


   ::gpu::queue *device::present_queue() { return nullptr; }


   frame_storage* device::current_frame_storage()
   {

      return m_framestoragea.atø(m_iCurrentFrame3);

   }


   ::gpu::frame_ephemeral* device::current_frame_ephemeral()
   {

      return m_frameephemerala.atø(m_iCurrentFrame3);

   }


} // namespace gpu



