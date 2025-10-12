#include "framework.h"
#include "bred_approach.h"
#include "context.h"
#include "debug_scope.h"
#include "device.h"
#include "cpu_buffer.h"
#include "guard.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "queue.h"
#include "render.h"
#include "renderable.h"
#include "renderer.h"
#include "render_state.h"
#include "render_target.h"
#include "layer.h"
#include "swap_chain.h"
#include "texture.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/application.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/windowing/window.h"
#include "aura/graphics/image/context.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/graphics.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/renderable.h"
#include "bred/graphics3d/types.h"


namespace gpu
{


   extern thread_local device* t_pgpudevice;

   context::context()
   {

      //m_pdraw2dgraphics = nullptr;

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

      //swap_buffers();

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




   //void context::swap_buffers()
   //{

   //   ::cast < swap_chain > pswapchain = m_pgpurenderer->m_pgpurendertarget;

   //   if (pswapchain)
   //   {

   //      pswapchain->present();

   //   }

   //}


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

            ødefer_construct(m_pcpubuffer);

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

            _synchronous_lock synchronouslock(m_pcpubuffer->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            m_pcpubuffer->set_size(size);

         });

   }


   void context::_send(const ::procedure& procedure)
   {

      auto procedureForward = [this, procedure]()
      {

         _synchronous_lock(this->synchronization());

         defer_make_current();

         procedure();

      };

      //rear_guard rearguard(this);

      ::thread::_send(procedureForward);

   }


   //void context::_post(const ::procedure& procedure)
   //{

   //   //throw ::error_not_supported;

   //   ////auto procedureForward = [this, procedure]()
   //   ////   {

   //   ////      _synchronous_lock(this->synchronization());

   //   ////      procedure();


   //   ////   };

   //   ::thread::_post(procedureForward);

   //}


   ::gpu::texture* context::current_target_texture(::gpu::frame* pgpuframe)
   {

      if (m_pgpucompositor)
      {

         auto ptexture = m_pgpucompositor->current_target_texture(pgpuframe);

         if (ptexture)
         {

            return ptexture;

         }

      }

      return m_pgpurenderer->current_render_target_texture(pgpuframe);

   }




   void context::construct(::pointer < ::gpu::shader >& pgpushader)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         if (::is_set(pgpushader))
         {

            pgpushader->m_timeRetire.Now();

            m_shaderaRetire.add(pgpushader);

         }

      }
      catch (...)
      {


      }

      øconstruct(pgpushader);

   }


   void context::manage_retired_objects()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      for (::collection::index i = 0; i < m_shaderaRetire.size();)
      {

         auto& pshader = m_shaderaRetire[i];

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


   void context::start_debug_happening(const ::scoped_string& scopedstrDebugHappening)
   {


   }
   
   
   void context::end_debug_happening()
   {



   }


   ::gpu::texture* context::texture(const ::file::path& path)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto& ptexture = m_texturemap[path];

      if (!ptexture)
      {

         load_texture(ptexture, path, false);

      }

      return ptexture;

   }


   void context::load_texture(::pointer < ::gpu::texture >& ptexture, const ::file::path& path, bool bIsSrgb)
   {

      if (ødefer_construct(ptexture))
      {

         ptexture->initialize_image_texture(m_pgpurenderer, path, bIsSrgb);

      }

   }


   ::gpu::texture* context::generic_texture(const ::file::path& path, int iAssimpTextureType)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pnode = m_texturemapGeneric.find(path);

      if (!pnode)
      {

         pnode = m_texturemapGeneric.get(path);

         try
         {

            load_generic_texture(pnode->element2(), path, iAssimpTextureType);

         }
         catch (...)
         {

            pnode->element2() = nullptr;

         }

      }

      return pnode->element2();

   }


   void context::load_generic_texture(::pointer < ::gpu::texture >& ptexture, const ::file::path& path, int iAssimpTextureType)
   {

      throw interface_only();

      // if (ødefer_construct(ptexture))
      // {
      //
      //    ptexture->initialize_image_texture(m_pgpurenderer, path);
      //
      // }

   }

   void context::defer_make_current()
   {


   }


   ::pointer < ::gpu::command_buffer >context::beginSingleTimeCommands(::gpu::queue * pqueue, ::gpu::enum_command_buffer ecommandbuffer)
   {

      ::pointer < command_buffer > pcommandbuffer;

      ødefer_construct(pcommandbuffer);

      pcommandbuffer->initialize_command_buffer(
         m_pgpurenderer->m_pgpurendertarget, 
         pqueue,
         ecommandbuffer);

      pcommandbuffer->begin_command_buffer(true);

      return pcommandbuffer;

   }


   void context::endSingleTimeCommands(::gpu::command_buffer *pcommandbuffer)
   {

      pcommandbuffer->submit_command_buffer(nullptr);

      pcommandbuffer->wait_commands_to_execute();

   }


   ::pointer<::graphics3d::renderable> context::load_wavefront_obj_renderable(const ::gpu::renderable_t & model)
   {
      // // 1) cache check
      // if (auto it = m_mapObjectModel.find(name); it != m_mapObjectModel.end())
      //    return it->element2();

      // 2) load

      ASSERT(model.m_erenderabletype == ::gpu::e_renderable_type_wavefront_obj);

      auto prenderable = _load_wavefront_obj_renderable(model);

      
      // // 3) cache & return
      // m_mapObjectModel[name] = model;
      return prenderable;

   }


   ::pointer<::graphics3d::renderable> context::_load_wavefront_obj_renderable(const ::gpu::renderable_t & model)
   {

      auto prenderable = m_pengine->_load_wavefront_obj_renderable(model);

      return prenderable;

   }


   ::pointer<::graphics3d::renderable> context::load_gltf_model(const ::gpu::renderable_t & model)
   {
      ASSERT(model.m_erenderabletype == ::gpu::e_renderable_type_gltf);
      auto prenderable = _load_gltf_model(model);
      return prenderable;

      // //if (auto it = m_mapGltfModel.find(name); it != m_mapGltfModel.end())
      //   // return it->element2();
      //
      // auto model = øcreate_pointer<gltf::Model>();
      //
      // model->loadFromFile(filepath, &m_pgpudevice, m_pgpudevice->graphicsQueue(), gltfFlags, scale);
      //
      // //m_mapGltfModel[name] = model;
      // return model;

   }


   ::pointer<::graphics3d::renderable> context::_load_gltf_model(const ::gpu::renderable_t & model)
   {

return {};

   }


   ::gpu::command_buffer* context::defer_get_upload_command_buffer()
   {

      if (!m_pcommandbufferUpload)
      {

         m_pcommandbufferUpload = beginSingleTimeCommands(transfer_queue());

      }

      return m_pcommandbufferUpload;

   }


   void context::defer_end_upload_command_buffer()
   {

      if (m_pcommandbufferUpload)
      {

         endSingleTimeCommands(m_pcommandbufferUpload);

         m_pcommandbufferUpload.release();

      }

   }


   ::gpu::queue * context::transfer_queue()
   {

      return nullptr;

   }


   ::gpu::queue * context::graphics_queue()
   {

      return nullptr;

   }


   ::gpu::queue * context::present_queue()
   {

      return nullptr;

   }



   void context::_context_lock()
   {


   }


   void context::_context_unlock()
   {



   }


   void context::defer_bind(::gpu::shader* pgpushader)
   {

      if (pgpushader == m_pshaderBound)
      {

         return;

      }

      if (m_pshaderBound)
      {

         end_debug_happening();

         m_pshaderBound->unbind();

      }
      start_debug_happening("shader changing");

      pgpushader->bind();

      m_pshaderBound = pgpushader;

   }


   void context::defer_unbind(::gpu::shader* pgpushader)
   {


   }


   void context::defer_unbind_shader()
   {

      if (m_pshaderBound)
      {

         auto pshaderBound = m_pshaderBound;

         m_pshaderBound.release();

         pshaderBound->unbind();

         end_debug_happening();

      }

   }


   //bool context::defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, memsize size, memory_buffer::enum_type etype)
   //{

   //   if (ødefer_construct(pmemorybuffer))
   //   {

   //      pmemorybuffer->initialize_memory_buffer_with_conext(this, size, etype);

   //      return true;

   //   }

   //   return false;

   //}


   //bool context::defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, const ::block& block, memory_buffer::enum_type etype)
   //{

   //   if (defer_construct_new(pmemorybuffer, block.size(), etype))
   //   {

   //      pmemorybuffer->assign(block.data(), block.size());

   //      return true;

   //   }

   //   return false;

   //}





   void context::create_window_context(::gpu::device* pgpudevice, ::windowing::window* pwindow)
   {

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      m_escene = e_scene_2d;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      //rear_guard guard(this);

      _send([this, pgpudevice, pwindow]()
         {

            auto eoutput = ::gpu::e_output_swap_chain;

            auto pwindowWindow = (::windowing::window*)pwindow;

            auto rectangleWindow = pwindowWindow->get_window_rectangle();

            auto size = rectangleWindow.size();

            initialize_gpu_context(pgpudevice, eoutput, pwindow, size);

         });

   }


   void context::create_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::gpu::enum_scene& escene, const ::int_size& size)
   {

      m_eoutput = eoutput;

      m_escene = escene;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      //rear_guard guard(this);

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

      //rear_guard guard(this);

      m_bD3D11On12Shared = true;

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
      else if (m_etype == e_type_draw2d)
      {

         task_set_name("gctx::draw2d");

      }
      else if (m_etype == e_type_generic)
      {

         task_set_name("gctx::generic");

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

      on_create_context(pgpudevice, eoutput, pwindow, size);

   }


   void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size)
   {


   }


   void context::engine_on_frame_context_initialization()
   {



   }


   void context::onBeforePreloadGlobalAssets()
   {


   }


   //bool context::task_iteration()
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


   ::pointer < ::gpu::input_layout > context::input_layout(const ::gpu::properties & properties)
   {

      auto pinputlayout = øcreate<::gpu::input_layout>();

      pinputlayout->initialize_input_layout(this, properties);

      return pinputlayout;

   }


   ::gpu::cpu_buffer* context::get_cpu_buffer()
   {

      if (!m_pcpubuffer)
      {

         create_cpu_buffer(m_rectangle.size());

      }

      return m_pcpubuffer;

   }


   //void context::make_current()
   //{

   //   m_pgpudevice->make_current(this);

   //}


   //void context::release_current()
   //{

   //   m_pgpudevice->release_current(this);

   //}


   void context::destroy_cpu_buffer()
   {

      //return ::success_none;

   }


   //void context::set_topic_texture(int iIndex)
   //{

   //   m_iTopicTexture = iIndex;

   //}


   void context::set_cull_face(::gpu::enum_cull_mode ecullmode)
   {

      m_ecullmode = ecullmode;

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


   void context::on_resize(const ::int_size& size)
   {

      m_rectangle.top_left() = { 0, 0 };

      m_rectangle.set_size(size);

      if (m_pgpurenderer)
      {

         m_pgpurenderer->on_resize(size);

      }

      if (m_pgpucompositor)
      {

         m_pgpucompositor->on_gpu_context_placement_change(size);

      }

   }


   void context::do_on_context(const ::procedure& procedure)
   {

      ///context_guard contextguard(this);

      procedure();

   }


   void context::send_on_context(const ::procedure& procedureParam)
   {

      //::gpu::rear_guard rear_guard(this);

      auto procedure = procedureParam;

      procedure.set_timeout(5_min);

      _send([this, procedure]()
         {

            do_on_context(procedure);

         });

   }


   ////void context::gpu_debug_message(const ::scoped_string& scopedstrMessage)
   //void context::gpu_debug_message(const ::scoped_string& scopedstrMessage)
   //{

   //   //{

   //   //   ::string strMessage(scopedstrMessage);

   //   //   glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
   //   //      GL_DEBUG_TYPE_MARKER,
   //   //      0,
   //   //      GL_DEBUG_SEVERITY_NOTIFICATION,
   //   //      -1,
   //   //      strMessage);

   //   //}

   //}


   ::pointer < ::gpu::pixmap > context::create_gpu_pixmap(const ::int_size& size)
   {

      ::pointer < ::gpu::pixmap > ppixmap;

      if (m_textureaAtlas.is_empty()
         || (!(ppixmap = m_textureaAtlas.last()->create_gpu_pixmap(size))))
      {

         auto ptextureNewAtlas = øcreate<::gpu::texture >();

         ptextureNewAtlas->initialize_image_texture(m_pgpurenderer, 
            { 0, 0, 4096, 4096 }, false);

         m_textureaAtlas.add(ptextureNewAtlas);

         ppixmap = m_textureaAtlas.last()->create_gpu_pixmap(size);

         if (!ppixmap)
         {

            throw ::exception(error_failed);

         }

      }

      return ppixmap;

   }


   ::gpu::swap_chain* context::get_swap_chain()
   {

      if (m_etype != e_type_window)
      {

         //throw ::exception(error_failed);

         return m_pgpudevice->m_pgpucontextMain->get_swap_chain();

//         return nullptr;

      }

      if (!m_pgpuswapchain)
      {

         ødefer_construct(m_pgpuswapchain);

         ///m_pswapchain->initialize_gpu_swap_chain(this, m_pwindow);

      }

      return m_pgpuswapchain;

   }





   void context::top_send_on_context(::gpu::context* pcontextInnerStart, bool bForDrawing, const ::procedure& procedure)
   {

      auto etype = this->m_etype;

      auto eoutput = this->m_eoutput;

      auto rectangleContext = this->rectangle();

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      if (!bForDrawing)
      {

         m_pgpudevice->on_new_frame();

         //auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

         m_pgpudevice->start_stacking_layers();

      }

      send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
         {

            auto pgpurenderer = get_gpu_renderer();

            pgpurenderer->do_on_frame(bForDrawing, [this, pcontextInnerStart, bForDrawing, procedure](::gpu::frame* pgpuframe)
               {

                  if (bForDrawing)
                  {

                     pcontextInnerStart->send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
                        {

                           //if (bForDrawing)
                           {

                              auto prenderer = pcontextInnerStart->get_gpu_renderer();

                              prenderer->defer_update_renderer();

                              auto λ = [procedure](::gpu::frame* pgpuframe)
                                 {

                                    procedure();

                                 };

                              prenderer->do_on_frame(bForDrawing, λ);

                           }
                           //else
                           //{

                           //   procedure();

                           //}

                        });

                     if (bForDrawing)
                     {
                        //while (!m_pgpudevice->m_playera || 
                        //   m_pgpudevice->m_playera->count() < 3)
                        //{

                        //   preempt(10_ms);

                        //}

                        auto playera = m_pgpudevice->m_playera;

                        if (playera)
                        {

                           auto prendererBackBuffer = get_gpu_renderer();

                           auto iFrameIndex = prendererBackBuffer->m_pgpurendertarget->get_frame_index();

                           auto prendertargetBackBuffer = prendererBackBuffer->m_pgpurendertarget;

                           auto ptextureBackBuffer = prendertargetBackBuffer->current_texture(pgpuframe);

                           merge_layers(ptextureBackBuffer, m_pgpudevice->m_playera);

                           ::cast < swap_chain > pswapchain = get_swap_chain();

                           if (!pswapchain->m_bSwapChainInitialized)
                           {

                              pswapchain->initialize_gpu_swap_chain(prendererBackBuffer);

                           }

                           ::cast < gpu::render_target > pgpurendertarget = pswapchain;

                           if (pgpurendertarget)
                           {

                              if (!pgpurendertarget->m_pgpurenderer)
                              {

                                 pgpurendertarget->initialize_render_target(
                                 m_pgpurenderer,
                                    m_rectangle.size(), 
                                    nullptr);
                                 
                              }

                           }

                           //auto ptextureSwapChain = pswapchain->current_texture();

                           //clear(::color::transparent);
                           /////clear(::rgba(0.5*0.5, 0.75 * 0.5, 0.95 * 0.5, 0.5));


                           pswapchain->present(ptextureBackBuffer);

                           for (auto player : *playera)
                           {

                              if (player->getCurrentCommandBuffer4())
                              {

                                 player->getCurrentCommandBuffer4()->wait_commands_to_execute();

                              }

                           }

                        }

                     }

                  }
                  else
                  {

                     pcontextInnerStart->send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
                        {

                           //if (bForDrawing)
                           {

                              auto prenderer = pcontextInnerStart->get_gpu_renderer();

                              prenderer->defer_update_renderer();

                              auto λ = [procedure](::gpu::frame* pgpuframe)
                                 {

                                    procedure();

                                 };

                              prenderer->do_on_frame(bForDrawing, λ);

                           }
                           //else
                           //{

                           //   procedure();

                           //}

                        });

                  }

               });

         });

         if (bForDrawing)
         {

            m_pgpudevice->on_end_frame();

         }




   }


   bool context::create_offscreen_graphics_for_swap_chain_blitting(::gpu::graphics* pgraphics, const ::int_size& size)
   {

      return false;

   }


   ::gpu::renderer* context::get_gpu_renderer()
   {

      if (!m_pgpurenderer)
      {

         øconstruct(m_pgpurenderer);

         m_pgpurenderer->initialize_gpu_renderer(this);

         m_pgpurenderer->defer_update_renderer();

      }

      return m_pgpurenderer;

   }


   //::gpu::renderer* context::back_buffer_gpu_renderer()
   //{

   //   if (!m_pgpurendererBackBuffer)
   //   {

   //      øconstruct(m_pgpurendererBackBuffer);

   //      m_pgpurendererBackBuffer->initialize_gpu_renderer(this);

   //      //m_pgpurendererBackBuffer->m_pgpurendertarget->m_iFrameCountRequest = 1;

   //      m_pgpurendererBackBuffer->m_prenderstate->m_estate = ::gpu::e_state_single_frame;

   //      m_pgpurendererBackBuffer->defer_update_renderer();

   //   }

   //   return m_pgpurenderer;

   //}


   //::gpu::renderer* context::draw2d_renderer()
   //{

   //   if (!m_pgpucontextDraw2d->m_pgpurenderer)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      øconstruct(m_pgpucontextDraw2d->m_pgpurenderer);

   //      auto eoutputDraw2d = m_papplication->m_gpu.m_eoutputDraw2d;

   //      m_pgpucontextDraw2d->m_pgpurenderer->initialize_renderer(this, eoutputDraw2d, escene);

   //      m_pgpucontextDraw2d->m_pgpurenderer->set_single_frame();

   //      m_pgpucontextDraw2d->m_pgpurenderer->defer_update_renderer();

   //   }

   //   return m_pgpucontextDraw2d->m_pgpurenderer;

   //}


   //::gpu::renderer* context::graphics3d_renderer()
   //{

   //   if (!m_pgpurendererEngine)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      øconstruct(m_pgpurendererEngine);

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

   //   øconstruct(pgpurendererDraw2d);

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


   string context::load_fragment(const ::scoped_string & scopedstrPath, enum_shader_source& eshadersource)
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


   void context::_translate_shader(string_array_base& stra)
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

      throw ::interface_only();

   }


   void context::copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource)
   {

      throw ::interface_only();

   }


   void context::merge_layers(::gpu::texture* ptextureTarget, ::pointer_array < ::gpu::layer >* playera)
   {

      throw ::interface_only();

   }


   void context::on_start_layer(::gpu::layer* player)
   {


   }


   void context::on_end_layer(::gpu::layer* player)
   {

      //::gpu::context_lock contextlock(this);

      defer_unbind_shader();

      if (m_pgpucompositor)
      {

         m_pgpucompositor->on_end_layer(player);

      }

      //auto ptextureTarget = player->texture();

      //auto ptextureSource = current_target_texture(player->m_pgpuframe);

      ////auto ptextureSource = m_pgpurendertarget->current_texture();

      //copy(ptextureTarget, ptextureSource);


   }



   void context::on_create_texture(::gpu::texture* ptexture)
   {


   }


   //void context::on_take_snapshot(layer* player)
   //{


   //}


   void context::on_begin_draw_attach(::gpu::graphics* pgpugraphics)
   {

      draw2d_on_begin_draw(pgpugraphics);

   }

   void context::on_end_draw_detach(::gpu::graphics* pgpugraphics)
   {

      draw2d_on_end_draw(pgpugraphics);

   }


   void context::draw2d_on_begin_draw(::gpu::graphics* pgpugraphics)
   {

      //if (pgpugraphics->m_egraphics == e_graphics_draw)
      //{

      //   pgpugraphics->start_gpu_layer();

      //   //auto pgpurendererDraw2d = get_gpu_renderer();

      //   //if (pgpurendererDraw2d->m_pgpurendertarget)
      //   //{

      //   //   pgpurendererDraw2d->m_pgpurendertarget->on_before_begin_draw_frame(pgpugraphics);

      //   //}

      //   //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->start_frame();

      //   //pgpurendererDraw2d->m_pgpucontext->m_pgpudevice->start_stacking_layers();

      //   //pgpurendererDraw2d->start_layer(rectangle);


      //}

   }


   void context::frame_prefix()
   {


   }


   void context::frame_suffix()
   {


   }





   void context::draw2d_on_end_draw(::gpu::graphics* pgpugraphics)
   {

      //if (pgpugraphics->m_egraphics == e_graphics_draw)
      //{

      //   auto pgpurendererDraw2d = m_pgpurenderer;

      //   pgpurendererDraw2d->end_layer();

      //   //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->end_frame();

      //   //if (pgpurendererDraw2d->m_pgpurendertarget)
      //   //{

      //   //   pgpurendererDraw2d->m_pgpurendertarget->on_after_end_draw_frame(pgpugraphics);

      //   //}

      //}

   }


   void context::__bind_draw2d_compositor(::gpu::compositor* pgpucompositor, ::gpu::layer* player)
   {


   }


   void context::__defer_soft_unbind_draw2d_compositor(::gpu::compositor* pgpucompositor, ::gpu::layer* player)
   {


   }


   ::memory context::rectangle_shader_vert()
   {

      return {};

   }


   ::memory context::rectangle_shader_frag()
   {

      return {};

   }



   ::memory context::white_to_color_sampler_vert()
   {

      return {};

   }


   //void context::white_to_color_sampler_shader_setup(gpu::shader* pshader)
   //{


   //}


   ::memory context::white_to_color_sampler_frag()
   {

      return {};

   }



   void context::initialize_rectangle_shader(::gpu::shader* pshader)
   {

      //auto pcontext = gpu_context();

      //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
      pshader->initialize_shader_with_block(
         m_pgpurenderer,
         rectangle_shader_vert(),
         //as_memory_block(g_uaAccumulationFragmentShader),
         rectangle_shader_frag(),
         {},
         {},
         {},
         this->input_layout < ::graphics3d::sequence2_color>()
      );

   }


   ::gpu::model_buffer* context::sequence2_uv_fullscreen_quad_model_buffer(::gpu::frame* pgpuframe)
   {

      if (!m_pmodelbufferFullscreenQuad)
      {

         ødefer_construct(m_pmodelbufferFullscreenQuad);

         m_pmodelbufferFullscreenQuad->sequence2_uv_create_fullscreen_quad(pgpuframe);

      }

      return m_pmodelbufferFullscreenQuad;

   }


   //render_target* context::draw2d_render_target()
   //{

   //   return nullptr;

   //}


   //render_target* context::graphics3d_render_target()
   //{

   //   return nullptr;

   //}


   ::pointer<::graphics3d::renderable> context::load_model(const ::gpu::renderable_t & model)
   {

      ::pointer<::graphics3d::renderable> prenderable;

      try
      {

         if (model.m_erenderabletype == ::gpu::e_renderable_type_wavefront_obj)
         {

            prenderable = load_wavefront_obj_renderable(model);

            // information("[asset_manager] Successfully loaded OBJ model '{}' from '{}'",
            //    model.m_strName,
            //    model.m_path);

         }
         else if (model.m_erenderabletype == ::gpu::e_renderable_type_gltf)
         {

            //uint32_t flags = entry.get("flags", 0); // Optional flags
            //float scale = entry.get("scale", 1.0f); // Optional scale
            prenderable = load_gltf_model(model);

            //name, path, flags, scale);
            // if (entry.get("usage", "") == "skybox" || name == "cube")
            // {
            //    m_pmodelSkybox = pmodel;
            // }

            //information("[asset_manager] Successfully loaded glTF model '{}' from '{}'",
              // loadmodel.m_strName,
               //loadmodel.m_path);

         }
         else
         {

            warningf("[context::load_model] Unknown model type '%s' for asset '%s'",
               model.m_strRenderableType1.c_str(),
               model.m_strName.c_str());

         }

      }
      catch (const ::exception &e)
      {

         errorf("[asset_manager] Failed to load model '%s': %s", model.m_strName.c_str(), e.get_message().c_str());

      }

      //prenderable->set_emodel(loadmodel.m_emodel);

      //prenderable->set_model_usage(loadmodel.m_emodelusage);

      //
      // if (loadmodel.m_emodelusage == gpu::e_model_usage_default)
      // {
      //
      //    m_prenderableSkybox = prenderable;
      //
      // }

      return prenderable;

   }


   ::pointer<::gpu::texture> context::load_cube_map(
      const ::scoped_string & scopedstrName,
      const ::file::path & path, 
      bool b32)
   {

return {};

   }


   ::pointer<::gpu::texture> context::load_sandbox_texture(const ::scoped_string & scopedstrName,
                                                    const ::file::path & path,
                                                    const ::scoped_string & scopedstrImageFormat)
   {

      return {};

   }

   
   ::pointer<::gpu::texture> context::cubemap_from_hdr(const ::file::path & path)
   {

      return {};

   }


   // ::pointer < ::graphics3d::renderable> context::create_tinyobj_renderable(const ::file::path& path)
   // {
   //
   //    auto pmodel = m_pengine->create_tinyobjloader_model(path);
   //
   //    return pmodel;
   //
   // }




} // namespace gpu



