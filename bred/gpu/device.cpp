#include "framework.h"
#include "bred_approach.h"
#include "context.h"
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
//#include "_gpu.h"
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

   }


   void device::initialize_gpu_device_for_swap_chain(::gpu::approach * pgpuapproach, ::windowing::window* pwindow)
   {

      m_edevicetarget = e_device_target_swap_chain;

      m_pgpuapproach = pgpuapproach;

      m_pwindow = pwindow;

      m_pwindow->m_ptaskUpdateScreen = this;

      //branch_synchronously();

   }


   void device::initialize_gpu_device_for_off_screen(::gpu::approach* pgpuapproach, const ::int_rectangle& rectanglePlacement)
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

      pgpucontext = øcreate< ::gpu::context >();

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


   ::gpu::layer* device::get_previous_layer(::gpu::layer* player)
   {

      if (!m_playera)
      {

         return nullptr;

      }

      auto iFind = m_playera->find_first(player);
      
      if (iFind <= 0)
      {

         return nullptr;

      }

      for(int i = (int) iFind - 1; i >= 0; i--)
      {
         if (m_playera->element_at(i)->m_pgpurenderer
             == player->m_pgpurenderer)
         {
            return m_playera->element_at(i);
         }
      }

      return nullptr;

   }


   //::pointer < ::gpu::context > device::start_gpu_output_context(const ::gpu::enum_output& eoutput, const ::int_size& size)
   //{

   //   auto pgpucontext = start_gpu_context(eoutput, nullptr,  size);

   //   return pgpucontext;

   //}


   //::pointer < ::gpu::context > device::start_cpu_buffer_context(::particle* pparticle, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_size& size)
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


   ::pointer < ::gpu::context > device::create_gpu_context(const ::gpu::enum_output& eoutput, const ::gpu::enum_scene & escene, const ::int_size& size)
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

   //   if (ødefer_construct(m_pgpucontextMain))
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


   ::pointer < ::gpu::context > device::create_draw2d_context(const ::gpu::enum_output& eoutput, const ::int_size& size)
   {

      //auto pgpucontext = øcreate<::gpu::context>();

      auto pgpucontext = allocate_context();

      pgpucontext->create_draw2d_context(this, eoutput, size);

      return pgpucontext;

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
   //   ////      float vertexes[] = {
   //   //         // positions         // colors
   //   //  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
   //   //    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
   //   //      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   //   //      //};
   //   //      float vertexes[] = {
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

   //   //øconstruct(m_pbuffer);

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

   //         ødefer_construct(m_pcpubuffer);

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

   //         //ødefer_construct(m_pcpubuffer);

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

   //         synchronous_lock synchronouslock(m_pcpubuffer->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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
      }

      auto pwindow = pacmewindowingwindow;

      if (::is_null(pwindow))
      {

         pwindow = m_papplication->m_pacmeuserinteractionMain->acme_windowing_window();
      }

      if (!m_pgpucontextMain->m_itask && pwindow)
      {

         m_pgpucontextMain->create_window_context(this, pwindow);

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

         øconstruct(m_pgpucontextMainDraw2d);

         m_pgpucontextMainDraw2d->m_etype = ::gpu::context::e_type_draw2d;

         m_pgpucontextMainDraw2d->m_eoutput = ::gpu::e_output_gpu_buffer;

         m_pgpucontextMainDraw2d->m_pgpudevice = this;

         ::cast < ::user::interaction > puserinteraction = m_papplication->m_pacmeuserinteractionMain;

         if (!m_pgpucontextMainDraw2d->m_itask
            && puserinteraction->m_pacmewindowingwindow)
         {

            m_pgpucontextMainDraw2d->branch_synchronously();

            m_pgpucontextMainDraw2d->_send([this, puserinteraction]()
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

               });

         }

      }

      return m_pgpucontextMainDraw2d;

   }



   void device::lock_context()
   {

      //return ::success;

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


   void device::on_new_frame()
   {

      auto iFrameCount = get_frame_count();

      m_iFrameSerial2++;

      m_iCurrentFrame2 = (m_iCurrentFrame2 + 1) % iFrameCount;

      auto& pframestorage = m_framestoragea.ø(m_iCurrentFrame2);

      if (!pframestorage)
      {

         øconstruct(pframestorage);

         pframestorage->initialize_gpu_frame_storage(this);

      }

      pframestorage->m_iBuffer = 0;

      pframestorage->m_iBufferOffset = 0;

      auto& pframeephemeral = m_frameephemerala.ø(m_iCurrentFrame2);

      øconstruct(pframeephemeral);

   }

   
   void device::on_end_frame()
   {

      auto pframestorage = current_frame_storage();

      try
      {

         pframestorage->on_end_frame();

      }
      catch (...)
      {


      }

   }


   bool device::is_starting_frame()const
   {

      return m_iFrameSerial2 == m_iCurrentFrame2;

   }


   void device::restart_frame_counter()
   {

      if (this->get_frame_count() > 1)
      {

         m_iCurrentFrame2 = -1;
         m_iFrameSerial2 = -1;

         //m_pgpurenderer->m_prenderstate->on_happening(e_happening_reset_frame_counter);

      }

   }


   int device::get_frame_index2()
   {

      if (this->get_frame_count() > 1)
      {

         return (int)m_iCurrentFrame2;

      }
      else
      {

         return 0;

      }

   }


   int device::get_frame_count()
   {

      return (int)m_iFrameCount;

   }



   
   pool_group* device::frame_pool_group(int iFrameIndex)
   {

      auto & ppoolgroupFrame = m_poolgroupaFrame.element_at_grow(iFrameIndex);

      ødefer_construct_new(ppoolgroupFrame);

      ppoolgroupFrame->m_pallocator = this;

      return ppoolgroupFrame;

   }


   ::pointer_array<::particle >* device::frame_particle_array(int iFrameIndex)
   {
      
      auto& pparticleaFrame = m_particleaFrame.element_at_grow(iFrameIndex);

      if (!pparticleaFrame)
      {

         øconstruct_new(pparticleaFrame);

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

   //   auto pshader = øcreate < ::gpu::shader >();

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

   //      øconstruct(m_prenderer);

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
   //      "uniform float time;\n"
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
            //"precision highp float;\n"
            "\n"
            "uniform floating_sequence2 iResolution;\n"
            "uniform float iTime;\n"
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


   void device::on_top_end_frame()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto procedureaOnTopFrameEnd = ::transfer(m_procedureaOnTopFrameEnd);

      for (auto& procedure : procedureaOnTopFrameEnd)
      {

         procedure();

      }


   }


   int device::get_type_size(::gpu::enum_type etype)
   {

      switch (etype)
      {
      case e_type_int: return sizeof(int);
      case e_type_float: return sizeof(float);
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


   layer * device::next_layer(renderer* pgpurenderer)
   {

      m_iLayer = m_iLayerCount;
      m_iLayerCount++;

      ødefer_construct_new(m_playera);

      auto & player = m_playera->element_at_grow(m_iLayer);

      ødefer_construct(player);

      auto iFrameIndex = pgpurenderer->render_target()->get_frame_index();

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

      auto& layera = *m_playera;

      auto& player = layera[m_iLayer];

      player->layer_end();
      //player->take_snapshot();

      //return player->texture()->m_pgpurenderer->m_pgpucontext->rectangle();

   }


   layer* device::current_layer()
   {
      
      if (m_iLayer < 0 || m_iLayer >= m_playera->get_count())
      {
      
         throw ::exception(error_wrong_state);

      }

      auto& layera = *m_playera;

      auto& player = layera[m_iLayer];

      return player;

   }


   ::gpu::queue *device::transfer_queue() { return nullptr; }


   ::gpu::queue *device::graphics_queue() { return nullptr; }


   ::gpu::queue *device::present_queue() { return nullptr; }


   frame_storage* device::current_frame_storage()
   {

      return m_framestoragea.ø(m_iCurrentFrame2);

   }


   ::gpu::frame_ephemeral* device::current_frame_ephemeral()
   {

      return m_frameephemerala.ø(m_iCurrentFrame2);

   }


} // namespace gpu



