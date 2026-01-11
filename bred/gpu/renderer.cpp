// Created from graphics3d/impact3d/renderer by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "bred_approach.h"
#include "command_buffer.h"
#include "context.h"
#include "cpu_buffer.h"
#include "device.h"
#include "frame.h"
#include "layer.h"
#include "queue.h"
#include "texture.h"
#include "renderer.h"
#include "render_state.h"
#include "render_target.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/graphics.h"
#include "bred/gpu/swap_chain.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"

#include "aura/platform/application.h"
#include "aura/platform/system.h"
#include "aura/user/user/interaction.h"


#include <assert.h>


namespace gpu
{

   interlocked_count g_iGpuRenderer;

   renderer::renderer()
   {

      m_iGpuRenderer = ++g_iGpuRenderer;

      m_iDefaultFrameCount = 3;

   }


   renderer::~renderer()
   {


   }



#ifdef _DEBUG

   long long renderer::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   long long renderer::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif


   bool renderer::render_step()
   {

      return true;

   }


   void renderer::initialize_gpu_renderer(::gpu::context* pgpucontext)
   {

      m_pgpucontext = pgpucontext;

      ødefer_construct_new(m_prenderstate);

      //m_pgpucontext->m_prenderer = this;

      //m_eoutput = eoutput;

      //m_escene = escene;

      //::particle::initialize(pparticle);

      //m_pgpucontext = system()->get_gpu()->create_context(this);

      //m_pgpucontext->initialize(this);


   }


   void renderer::defer_initialize_render_target()
   {

      auto previous = m_pgpurendertarget2;

      auto prendertarget = render_target();

      auto sizeRenderer = m_sizeRenderer;

      if (!prendertarget->has_ok_flag() || prendertarget->m_size != sizeRenderer)
      {

///         m_sizeRenderer = size;

         prendertarget->initialize_render_target(this, sizeRenderer, previous);

         // if (!size.is_empty() && m_pgpucontext->is_current_task())
         if (!prendertarget->m_size.is_empty())
         // if (!size.is_empty())
         {

            render_target()->init();
         }

      }

   }


   void renderer::on_resize(const ::int_size& size)
   {

      if (size == m_sizeRenderer)
      {

         return;

      }

      auto eoutput = m_pgpucontext->m_eoutput;

      //auto previous = render_target();

      ////on_defer_update_renderer_allocate_render_target(eoutput, size, previous);

      //if (!m_pgpurendertarget)
      //{

      //   m_pgpurendertarget = on_create_render_target();

      //   if (!m_pgpurendertarget)
      //   {

      //      throw ::exception(error_wrong_state);

      //   }

      //}

      //m_pgpurendertarget = pgpurendertarget;
      //      else if (eoutput == ::gpu::e_output_gpu_buffer)
      //      {
      //
      //         auto poffscreenrendertargetview = øallocate offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
      //#ifdef WINDOWS_DESKTOP
      //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
      //#else
      //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
      //#endif
      //         m_prendertargetview = poffscreenrendertargetview;
      //         //m_prendererResolve;
      //
      //      }
      //      else if (eoutput == ::gpu::e_output_color_and_alpha_accumulation_buffers)
      //      {
      //
      //         auto paccumulationrendertargetview = øallocate accumulation_render_target(this, m_extentRenderer, m_prendertargetview);
      //         paccumulationrendertargetview->m_formatImage = VK_FORMAT_R32G32B32A32_SFLOAT;
      //         paccumulationrendertargetview->m_formatAlphaAccumulation = VK_FORMAT_R32_SFLOAT;
      //         m_prendertargetview = paccumulationrendertargetview;
      //
      //         //øconstruct_new(m_prendererResolve);
      //
      //         //m_prendererResolve->initialize_renderer(m_pgpucontext, ::gpu::e_output_resolve_color_and_alpha_accumulation_buffers);
      //
      //         //m_prendererResolve->set_placement(m_pgpucontext->rectangle);
      //         //
      //         //            auto poffscreenrendertargetview = øallocate offscreen_render_target(m_pgpucontext, m_extentRenderer, m_prendertargetviewResolve);
      //         //#ifdef WINDOWS_DESKTOP
      //         //            poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
      //         //#else
      //         //            poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
      //         //#endif
      //         //            m_prendertargetviewResolve = poffscreenrendertargetview;
      //      }
      //      else if (eoutput == ::gpu::e_output_resolve_color_and_alpha_accumulation_buffers)
      //      {
      //
      //         auto poffscreenrendertargetview = øallocate offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
      //#ifdef WINDOWS_DESKTOP
      //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
      //#else
      //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
      //#endif
      //         m_prendertargetview = poffscreenrendertargetview;
      //
      //      }
      //      else
      //      {
      //
      //         throw ::exception(error_wrong_state, "Unexpected gpu e_output");
      //
      //      }
      //

      m_sizeRenderer = size;

      defer_initialize_render_target();

      //if (m_pgpurendertarget)
      //{

      //   m_pgpurendertarget->on_resize(size);

      //}

   }


   ::particle_array* renderer::ongoing_particle_array()
   {

      return current_frame_particle_array();

   }


   ::pointer < texture> renderer::create_image_texture(const ::int_size& size, bool bWithDepth)
   {

      auto ptexture = øcreate< texture>();

      ::gpu::texture_attributes textureattributes(::int_rectangle{size});

      ::gpu::texture_flags textureflags;

      textureflags.m_bWithDepth = bWithDepth;

      ptexture->initialize_texture(this, textureattributes, textureflags);

      m_pgpucontext->on_create_texture(ptexture);

      return ptexture;

   }


   //::pointer<::gpu::shader> renderer::create_shader(
   //   const ::file::path& pathVert,
   //   const ::file::path& pathFrag,
   //   const ::array<::gpu::shader::enum_descriptor_set_slot>& eslota,
   //   const ::particle_pointer& pLocalDescriptorSet,
   //   //const ::particle_pointer& pVertexInput,
   //   const ::gpu::property* ppropertiesPush,
   //   ::gpu::input_layout* pinputlayout,
   //   ::gpu::shader::enum_flag eflag)
   //{

   //   auto pshader = øcreate < ::gpu::shader >();
   //   pshader->initialize_shader(this,
   //      pathVert, pathFrag, eslota,
   //      pLocalDescriptorSet, ppropertiesPush, pinputlayout, eflag);

   //   return pshader;

   //}



   //void renderer::initialize_render(::user::interaction * puserinteraction)
   //{

   //   m_puserinteraction = puserinteraction;

   //   //auto estatus = 
   //   //::particle::initialize(puserinteraction);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //initialize_application_consumer();

   //   auto psystem = system();

   //   auto pgpu = application()->get_gpu();

   //   m_pgpucontext = pgpu->create_context(this);

   //   //if (m_pgpucontext)
   //   //{

   //   //   m_pgpucontext->initialize(this);

   //   //}

   //   //return estatus;

   //}


   //void renderer::set_placement(const ::int_rectangle& rectanglePlacement)
   //{

   //   m_rectangle = rectanglePlacement;

   //}

   void renderer::on_context_resize()
   {


   }


   void renderer::on_begin_draw()
   {


   }


   void renderer::on_end_draw()
   {


   }


   void renderer::defer_end_frame_layer_copy()
   {

      auto player = ::gpu::current_frame()->m_pgpulayer;

      if (player)
      {

         auto ptextureTarget = player->texture();

         auto ptextureSource = m_pgpucontext->current_target_texture(player->m_pgpuframe);

         m_pgpucontext->copy(ptextureTarget, ptextureSource);

         ptextureTarget->defer_fence();

      }

   }


   ::gpu::render_target * renderer::render_target()
   {

      if (!m_pgpurendertarget2)
      {

         m_pgpurendertarget2 = on_create_render_target();

         defer_initialize_render_target();

      }

      return m_pgpurendertarget2;

   }


   ::gpu::texture* renderer::current_render_target_texture(::gpu::frame* pgpuframe)
   {

      return render_target()->current_texture(pgpuframe);

   }


   ::gpu::command_buffer* renderer::getCurrentCommandBuffer2(::gpu::frame* pgpuframe)
   {

      assert(isFrameStarted && "Cannot get command buffer when frame not in progress");

      if (pgpuframe->m_pgpulayer)
      {

         return pgpuframe->m_pgpulayer->getCurrentCommandBuffer4();

      }

      if (m_pgpucontext->m_eoutput == e_output_swap_chain)
      {
         m_pgpucontext->get_swap_chain()->defer_check_swap_chain();
      }


      if (m_commandbuffera.is_empty())
      {

         create_command_buffers();

      }

      ::collection::index iFrameIndex;

      if (m_pgpucontext->m_eoutput == e_output_swap_chain)
      {

         iFrameIndex = m_pgpucontext->get_swap_chain()->swap_chain_frame_index();

         if (iFrameIndex < 0)
         {

            ::warning("iFrameIndex < 0 (1)");

         }

      }
      else
      {

         iFrameIndex = render_target()->get_frame_index();

         if (iFrameIndex < 0)
         {

            ::warning("iFrameIndex < 0 (2)");

         }

      }

      auto pcommandbuffer = m_commandbuffera[iFrameIndex];

      pcommandbuffer->m_iCommandBufferFrameIndex = iFrameIndex;

      pcommandbuffer->m_strAnnotation.empty();

      return pcommandbuffer;

   }


   ::gpu::command_buffer* renderer::getLoadAssetsCommandBuffer()
   {

      return nullptr;

   }


   void renderer::create_command_buffers()
   {

      m_commandbuffera.set_size(m_pgpucontext->m_pgpudevice->get_frame_count());

      //::array<VkCommandBuffer > a;

      //a.set_size(m_commandbuffera.size());

      //VkCommandBufferAllocateInfo allocInfo{};
      //allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
      //allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      //allocInfo.commandPool = m_pgpucontext->m_pgpudevice->getCommandPool();
      //allocInfo.commandBufferCount = (uint32_t) a.size();

      //if (vkAllocateCommandBuffers(
      //   m_pgpucontext->logicalDevice(),
      //   &allocInfo, 
      //   a.data()
      //) !=  VK_SUCCESS) 
      //{

      //   throw ::exception(error_failed, "failed to allocate command buffers!");

      //}

      for (int i = 0; i < m_commandbuffera.size(); i++)
      {

         auto& pcommandbuffer = m_commandbuffera[i];

         ødefer_construct(pcommandbuffer);

         pcommandbuffer->initialize_command_buffer(render_target(),
            m_pgpucontext->m_pgpudevice->graphics_queue(),
            e_command_buffer_graphics);

         pcommandbuffer->m_iCommandBufferFrameIndex = i;

      }

   }


   void renderer::free_command_buffers()
   {

      m_commandbuffera.clear();

      //return ::gpu::renderer::getCurrentCommandBuffer2(::gpu::current_frame());

      //assert(isFrameStarted && "Cannot get command buffer when frame not in progress");

      //if (m_commandbuffera.is_empty())
      //{

      //   create_command_buffers();

      //}

      //auto pcommandbuffer = m_commandbuffera[m_pgpurendertarget->get_frame_index()];

      //return pcommandbuffer;

   }

   ::particle_array * renderer::current_frame_particle_array()
   {

      auto iFrameIndex = m_pgpucontext->m_pgpudevice->get_frame_index2();

      auto pparticlea = m_pgpucontext->m_pgpudevice->frame_particle_array(iFrameIndex);

      return pparticlea;

   }

   void renderer::draw()
   {

      //::gpu::context_lock lock(m_pgpucontext);

      //if (::is_set(m_papplication) && ::is_set(m_papplication->m_pbuffer)
      //   && m_papplication->m_pbuffer->m_pimage.ok()
      //   && ::is_set(m_pprogram))
         //if (::is_set(m_pgpucontext) && ::is_set(m_pgpucontext->m_pbuffer)
           // && m_pgpucontext->m_pbuffer->m_pixmap.is_ok())
      if (::is_set(m_pgpucontext))
      {
         m_pgpucontext->_send([this]()
            {
               //if (::is_set(m_pobject))
               {

                  //::gpu::context_lock lock(m_pgpucontext);

                  //m_pgpucontext->make_current();

                  // global_transform

                  ////{

                  ////   float x = (float) psession->get_cursor_position().x;

                  ////   float y = (float) psession->get_cursor_position().y;

                  ////   m_papplication->m_pprogram->m_pshader->setVec2("mouse", x, y);
                  ////   m_papplication->m_pprogram->m_pshader->setVec2("iMouse", x, y);

                  ////}

                  //{

                  //   float cx = (float) m_papplication->m_pbuffer->m_pimage->width();

                  //   float cy = (float) m_papplication->m_pbuffer->m_pimage->height();

                  //   m_papplication->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
                  //   m_papplication->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

                  //}

                  //{

                  //   double dElapsed = m_timeStart.elapsed().floating_second().m_d;

                  //   double dTime = dElapsed / 1000.0;

                  //   float time = (float) dTime;

                  //   m_papplication->m_pprogram->m_pshader->setFloat("time", time);
                  //   m_papplication->m_pprogram->m_pshader->setFloat("iTime", time);

                  //}

                  on_start_drawing();

                  on_global_transform();

                  on_draw();

                  read_to_cpu_buffer();

                  ///m_pobject->draw();

                  //m_papplication->renderer();

                  //m_pgpucontext->prepare_for_gpu_read();

                  //m_pgpucontext->m_pbuffer->gpu_read();

               }

               //#if !defined(__APPLE__)
               //         ::geometry2d::matrix matrixOriginal;
               //         pgraphics->get(matrixOriginal);
               //         ::geometry2d::matrix matrix(matrixOriginal);
               //         matrix.scale(1.0, -1.0);
               //         matrix.translate(0, m_rectangle.height());
               //         pgraphics->set(matrix);
               //#endif

                        //auto & pixmap = m_pgpucontext->m_pbuffer->m_pixmap;

                        //if (pixmap.is_ok())
                        //{

                        //   //pimage->map();

                        //   //pimage->fill_channel(255, ::color::e_channel_opacity);

                        //}
                        //return pixmap;

                        //::image::image_source imagesource(m_pgpucontext->m_pbuffer->m_pimage);

                        //::double_rectangle rectangleTarget(m_rectangle);

                        //::image::image_drawing_options imagedrawingoptions(rectangleTarget);

                        //::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                        //pgraphics->draw(imagedrawing);

               //         pgraphics->draw(pixmap, m_rectangleTarget);
               //
               //#if !defined(__APPLE__)
               //
               //         pgraphics->set(matrixOriginal);
               //
               //#endif
            });

      }

      //_001OnDraw1Through3(pgraphics);
      //return {};
      //return {};


   }


   //::gpu::command_buffer* renderer::getCurrentCommandBuffer2(::gpu::current_frame())
   //{

   //   assert(isFrameStarted && "Cannot get command buffer when frame not in progress");

   //   if (m_commandbuffera.is_empty())
   //   {

   //      create_command_buffers();

   //   }

   //   auto pcommandbuffer = m_commandbuffera[m_pgpurendertarget->get_frame_index()];

   //   return pcommandbuffer;

   //}


   void renderer::read_to_cpu_buffer()
   {

      //      ::gpu::context_lock lock(m_pgpucontext);

            //if (::is_set(m_papplication) && ::is_set(m_papplication->m_pbuffer)
            //   && m_papplication->m_pbuffer->m_pimage.ok()
            //   && ::is_set(m_pprogram))
      if (::is_set(m_pgpucontext) && ::is_set(m_pgpucontext->m_pcpubuffer)
         && m_pgpucontext->m_pcpubuffer->m_pimagetarget->m_pimage.ok())
      {

         //if (::is_set(m_pobject))
         {

            //::gpu::context_lock lock(m_pgpucontext);

            //m_pgpucontext->make_current();

            //// global_transform

            //////{

            //////   float x = (float) psession->get_cursor_position().x;

            //////   float y = (float) psession->get_cursor_position().y;

            //////   m_papplication->m_pprogram->m_pshader->setVec2("mouse", x, y);
            //////   m_papplication->m_pprogram->m_pshader->setVec2("iMouse", x, y);

            //////}

            ////{

            ////   float cx = (float) m_papplication->m_pbuffer->m_pimage->width();

            ////   float cy = (float) m_papplication->m_pbuffer->m_pimage->height();

            ////   m_papplication->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
            ////   m_papplication->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

            ////}

            ////{

            ////   double dElapsed = m_timeStart.elapsed().floating_second().m_d;

            ////   double dTime = dElapsed / 1000.0;

            ////   float time = (float) dTime;

            ////   m_papplication->m_pprogram->m_pshader->setFloat("time", time);
            ////   m_papplication->m_pprogram->m_pshader->setFloat("iTime", time);

            ////}

            //start_drawing(m_pgpucontext);

            //global_transform(m_pgpucontext);

            //draw(m_pgpucontext);

            /////m_pobject->draw();

            ////m_papplication->renderer();

            m_pgpucontext->prepare_for_gpu_read();

            m_pgpucontext->m_pcpubuffer->gpu_read();

         }

         //#if !defined(__APPLE__)
         //         ::geometry2d::matrix matrixOriginal;
         //         pgraphics->get(matrixOriginal);
         //         ::geometry2d::matrix matrix(matrixOriginal);
         //         matrix.scale(1.0, -1.0);
         //         matrix.translate(0, m_rectangle.height());
         //         pgraphics->set(matrix);
         //#endif

         //auto & pixmap = m_pgpucontext->m_pbuffer->m_pixmap;

         //if (pixmap.is_ok())
         //{

         //   //pimage->map();

         //   //pimage->fill_channel(255, ::color::e_channel_opacity);

         //}
         //return pixmap;

         //::image::image_source imagesource(m_pgpucontext->m_pbuffer->m_pimage);

         //::double_rectangle rectangleTarget(m_rectangle);

         //::image::image_drawing_options imagedrawingoptions(rectangleTarget);

         //::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //pgraphics->draw(imagedrawing);

//         pgraphics->draw(pixmap, m_rectangleTarget);
//
//#if !defined(__APPLE__)
//
//         pgraphics->set(matrixOriginal);
//
//#endif

      }

      //_001OnDraw1Through3(pgraphics);
      //return {};


   }


   //   void renderer::to_draw2d_graphics(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      
   //   //   m_pgpucontext->prepare_for_gpu_read();
   //
   //   //   slImage.lock();
   //
   //   //   m_pgpucontext->m_pcpubuffer->gpu_read();
   //
   //   //}
   //
   //#if !defined(__APPLE__)
   //
   //   ::geometry2d::matrix matrixOriginal;
   //
   //   pgraphics->get(matrixOriginal);
   //
   //   ::geometry2d::matrix matrix(matrixOriginal);
   //
   //   matrix.scale(1.0, -1.0);
   //
   //   matrix.translate(0, m_rectangle.height());
   //
   //   pgraphics->set(matrix);
   //
   //#endif
   //
   //
   //   ødefer_construct(m_pimageFromGpu);
   //
   //   auto size = m_pgpucontext->m_pcpubuffer->m_pixmap.m_size;
   //
   //   m_pimageFromGpu->create(size);
   //
   //   m_pimageFromGpu->map();
   //
   //   m_pimageFromGpu->copy(&m_pgpucontext->m_pcpubuffer->m_pixmap);
   //
   //   ::image::image_source imagesource(m_pimageFromGpu);
   //
   //   ::image::image_drawing_options imagedrawingoptions(m_rectangle);
   //
   //   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //   pgraphics->draw(imagedrawing);
   //
   //#if !defined(__APPLE__)
   //
   //   pgraphics->set(matrixOriginal);
   //
   //#endif
   //
   //
   //   }


   void renderer::on_start_drawing()
   {


   }


   void renderer::on_global_transform()
   {


   }


   void renderer::on_draw()
   {


   }


   void renderer::on_layout(::draw2d::graphics_pointer& pgraphics)
   {


   }


   void renderer::on_begin_render(frame* pframe)
   {

      m_prenderstate->on_happening(::gpu::e_happening_begin_render);

      bool bLayerStarted = false;

      //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      //{

      //   if (m_pgpucontext->m_pgpucompositor)
      //   {

      //      auto etypeContext = m_pgpucontext->m_etype;

      //      auto eoutputContext = m_pgpucontext->m_eoutput;

      //      m_iSentLayerCount++;

      //      m_pgpucontext->m_pgpucompositor->start_gpu_layer(pframe);

      //      bLayerStarted = true;

      //   }

      //}

      if (pframe->m_pgpulayer)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            auto etypeContext = m_pgpucontext->m_etype;

            auto eoutputContext = m_pgpucontext->m_eoutput;

            m_iSentLayerCount++;

            m_pgpucontext->m_pgpucompositor->start_gpu_layer(pframe);

            bLayerStarted = true;

         }

      }
      //if (m_iSentLayerCount <= 0)
      //{

      //   auto pcommandbuffer = getCurrentCommandBuffer2(::gpu::current_frame());

      //   if (pcommandbuffer)
      //   {

      //      pcommandbuffer->reset();

      //   }

      //}

      if (!bLayerStarted)
      {

         auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;

         auto etypeGpuContext = m_pgpucontext->m_etype;

         if (!bUseSwapChain
            || etypeGpuContext != ::gpu::context::e_type_window)
         {

            _on_begin_render(pframe);

         }

      }

      ///if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            m_pgpucontext->m_pgpucompositor->gpu_layer_on_after_begin_render();

         }

      }

      on_final_begin_render();

   }


   void renderer::on_final_begin_render()
   {


   }

   void renderer::on_end_render(frame* pframe)
   {


      ///if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            m_pgpucontext->m_pgpucompositor->gpu_layer_on_before_end_render();

         }

      }


      _on_end_render(pframe);



      bool bLayerPresent = false;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            //m_pgpucontext->m_pgpucompositor->end_gpu_layer(pframe);
            auto player = ::gpu::current_frame()->m_pgpulayer;

            if (player)
            {

                  m_pgpucontext->on_end_layer(player);


            }

            bLayerPresent = true;

         }

      }

      m_prenderstate->on_happening(::gpu::e_happening_end_render);

   }


   void renderer::_on_begin_render(frame* pframe)
   {


   }


   void renderer::on_after_load_scene(::graphics3d::scene_base* pscene)
   {

//      auto pcommandbufferLoadAssets = ::transfer(m_pcommandbufferLoadAssets);
//
//      if (pcommandbufferLoadAssets)
//      {
//
//         m_pcommandbufferLoadAssets2 = pcommandbufferLoadAssets;
//         //if (prenderer->m_pcommandbufferLoadAssets)
//         //{
//
//         //   auto pcommandbufferLoadAssets = ::transfer(prenderer->m_pcommandbufferLoadAssets);
//
//         //   m_papplication->fork([pcommandbufferLoadAssets]()
//         //      {
//
//         pcommandbufferLoadAssets->submit_command_buffer(nullptr);
//
//         pcommandbufferLoadAssets->wait_commands_to_execute();
//
////         });
//
////   }
//
////}
//
//      }

   }


   void renderer::_on_end_render(frame* pframe)
   {


   }


   void renderer::endDraw(::gpu::graphics* pgraphics, ::user::interaction* puserinteraction)
   {


   }


   //void renderer::on_defer_update_renderer_allocate_render_target(::gpu::enum_output eoutput, const ::int_size& size, ::gpu::render_target* previous)
   //{

   //   throw ::interface_only();
   //   //::pointer < ::gpu::render_target > pgpurendertarget;

   //   //if (eoutput == ::gpu::e_output_cpu_buffer
   //   //   || eoutput == ::gpu::e_output_gpu_buffer)
   //   //{

   //   //   pgpurendertarget = øallocate offscreen_render_target();
   //   //   //#ifdef WINDOWS_DESKTOP
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   //   //#else
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   //   //#endif
   //   //   //m_pgpurendertarget = poffscreenrendertargetview;
   //   //   //         //m_prendererResolve.release();
   //   //   //
   //   //}
   //   //else if (eoutput == ::gpu::e_output_swap_chain)
   //   //{
   //   //   pgpurendertarget = øallocate offscreen_render_target();
   //   //   //#ifdef WINDOWS_DESKTOP
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   //   //#else
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   //   //#endif
   //   //   //m_pgpurendertarget = poffscreenrendertargetview;

   //   //   //m_prendertargetview = øallocate swap_chain_render_target(this, size, m_prendertargetview);
   //   //   //m_prendererResolve.release();

   //   //}

   //   //return pgpurendertarget;

   //}


   void renderer::defer_update_renderer()
   {

      auto rectangleContext = m_pgpucontext->rectangle();

      auto sizeContext = rectangleContext.size();

      auto etypeContext = m_pgpucontext->m_etype;

      auto prendertarget = render_target();

      if (prendertarget && m_sizeRenderer == sizeContext)
      {

         //if (m_pgpucontext->is_current_task())
         {

            if (!sizeContext.is_empty())
            {

               if (!prendertarget->m_bRenderTargetInit)
               {

                  prendertarget->init();

               }

            }

         }

         return;

      }

      on_resize(sizeContext);

   }

   
   ::pointer < render_target > renderer::on_create_render_target()
   {

      auto prendertarget = øcreate<::gpu::render_target>();

      prendertarget->m_bAdvancedPipelineSynchronization = true;

      return prendertarget;

   }


   ::pointer < swap_chain > renderer::on_create_swap_chain()
   {

      return øcreate<swap_chain>();

   }


   //render_target* renderer::back_buffer_render_target()
   //{

   //   auto rectangle = m_pgpucontext->rectangle();

   //   if (m_pgpurendertargetBackBuffer)
   //   {

   //      auto size = m_pgpurendertargetBackBuffer->m_size;

   //      auto sizeNew = rectangle.size();

   //      if (size == sizeNew)
   //      {

   //         if (m_pgpucontext->is_current_task())
   //         {

   //            if (!m_pgpurendertargetBackBuffer->m_bRenderTargetInit
   //               || !m_pgpurendertargetBackBuffer->is_ok())
   //            {

   //               m_pgpurendertargetBackBuffer->init();

   //            }

   //         }

   //         return m_pgpurendertargetBackBuffer;

   //      }

   //   }

   //   auto pgpurendertargetBackBufferOld = m_pgpurendertargetBackBuffer;

   //   auto poffscreenrenderpass = allocate_offscreen_render_target();

   //   poffscreenrenderpass->m_bBackBuffer = true;

   //   m_pgpurendertargetBackBuffer = poffscreenrenderpass;

   //   ::int_size size = rectangle.size();

   //   m_pgpurendertargetBackBuffer->initialize_render_target(
   //      this, size, pgpurendertargetBackBufferOld);

   //   if (m_pgpucontext->is_current_task())
   //   {

   //      m_pgpurendertargetBackBuffer->init();

   //   }

   //   return m_pgpurendertargetBackBuffer;

   //}


   //::pointer < render_target > renderer::allocate_offscreen_render_target()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void renderer::blend(::gpu::renderer* prenderer)
   {

      throw ::interface_only();

   }


   void renderer::clear(::gpu::texture* ptexture)
   {

      throw ::interface_only();

   }


   //void renderer::copy(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   //{

   //   throw::interface_only();

   //}


   //void renderer::blend(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   //{

   //   throw::interface_only();

   //}


   void renderer::soft_restore_context()
   {


   }


   void renderer::endDrawEndDraw()
   {


   }

   
   void renderer::frame_prefix()
   {

      defer_update_renderer();

      auto pframe = beginFrame();

      on_begin_render(pframe);

   }


   void renderer::frame_suffix()
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      on_end_render(::gpu::current_frame());

      endFrame();

   }


   void renderer::do_on_frame(bool bForDrawing, const ::function < void(::gpu::frame*) > & on_frame)
   {

      if (!bForDrawing)
      {

         frame_prefix();

         on_frame(::gpu::current_frame());

         return;

      }

//      frame_prefix();

      on_frame(::gpu::current_frame());

      frame_suffix();

   }


   void renderer::start_layer()
   {

      auto player = m_pgpucontext->m_pgpudevice->next_layer(this);

      player->layer_start();

   }


   void renderer::end_layer()
   {

      auto player = m_pgpucontext->m_pgpudevice->current_layer();

      player->layer_end();

   }


   void renderer::on_start_layer(layer* player)
   {

      //m_pgpulayer = player;

      m_pgpucontext->on_start_layer(player);

      //if (m_pgpucontext->m_pgpudevice->get_previous_layer(player) != nullptr)
      //{

      //   getCurrentCommandBuffer2(player->m_pgpuframe)->reset();

      //}

      _on_begin_render(player->m_pgpuframe);

   }


   void renderer::on_end_layer(layer* player)
   {

      m_pgpucontext->on_end_layer(player);

      //auto ptextureTarget = player->texture();

      //auto ptextureSource = m_pgpucontext->current_target_texture();
      //
      ////auto ptextureSource = m_pgpurendertarget->current_texture();

      //m_pgpucontext->copy(ptextureTarget, ptextureSource);

      //auto pcommandbuffer = getCurrentCommandBuffer2(player->m_pgpuframe);

      //if (pcommandbuffer)
      //{

      //   pcommandbuffer->submit_command_buffer(player);

      //   pcommandbuffer->wait_commands_to_execute();

      //}

   }


   void renderer::start_frame()
   {

      auto etype = m_pgpucontext->m_etype;

      auto eoutput = m_pgpucontext->m_eoutput;

      auto escene = m_pgpucontext->m_escene;

      defer_update_renderer();

      beginFrame();

      on_begin_render(render_target()->m_pgpuframe);

      m_pgpucontext->frame_prefix();

   }


   bool renderer::is_starting_frame()const
   {

      return m_pgpucontext->m_pgpudevice->is_starting_frame();

   }


   void renderer::on_begin_frame()
   {


   }


   ::pointer < frame > renderer::beginFrame()
   {

      if (m_procedureaOnJustBeforeFrameNextStart.has_element())
      {

         try
         {

            for (auto & procedure : m_procedureaOnJustBeforeFrameNextStart)
            {

               try
               {

                  procedure();

               }
               catch (...)
               {


               }

            }

         }
         catch (...)
         {


         }

         m_procedureaOnJustBeforeFrameNextStart.clear();

      }

      auto pcontext = m_pgpucontext;

      auto pgpudevice = pcontext->m_pgpudevice;

      auto pgpuframe = øcreate < ::gpu::frame >();

      ::gpu::set_current_frame(pgpuframe);

      m_prenderstate->on_happening(e_happening_begin_frame);

      assert(!isFrameStarted && "Can't call beginFrame while already in progress");

      isFrameStarted = true;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow
         && m_pgpucontext->m_etype != ::gpu::context::e_type_window)
      {

         auto player = pgpudevice->next_layer(pcontext->m_pgpurenderer);

         //m_pgpulayer = player;

         player->m_pgpuframe = pgpuframe;

         pgpuframe->m_pgpulayer = player;

      }

      ::cast < command_buffer > pcommandbuffer = getCurrentCommandBuffer2(pgpuframe);

      auto iFrameIndex = pcommandbuffer->m_iCommandBufferFrameIndex;

      auto pszCommandBufferAnnotation = pcommandbuffer->m_strAnnotation.c_str();

      static int s_iFrameIndex0LayerDraw2dCount = 0;

      auto iLayer = pgpudevice->m_iLayer;

      auto iFrameSerial = pgpudevice->m_iFrameSerial2;

      auto iCurrentFrame = pgpudevice->m_iCurrentFrame2;

      if (iFrameIndex == 0 && pcommandbuffer->m_strAnnotation == "layer.draw2d")
      {

         s_iFrameIndex0LayerDraw2dCount++;

      }

      on_begin_frame();

      pgpuframe->m_pgpucommandbuffer = pcommandbuffer.m_p;

      render_target()->m_pgpuframe = pgpuframe;

      auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;

      auto etypeGpuContext = m_pgpucontext->m_etype;

      if (!bUseSwapChain
         || etypeGpuContext != ::gpu::context::e_type_window)
      {

         wait_command_buffer_ready();

         pcommandbuffer->begin_command_buffer(false);

      }

      return render_target()->m_pgpuframe;

   }


   void renderer::endFrame()
   {

      m_prenderstate->on_happening(e_happening_end_frame);

      isFrameStarted = false;

      if (m_procedureaOnAfterEndFrame.has_element())
      {

         try
         {

            for (auto &procedure: m_procedureaOnAfterEndFrame)
            {
               try
               {

                  procedure();

               }
               catch (...)
               {


               }
            }

         }
         catch (...)
         {


         }
         m_procedureaOnAfterEndFrame.clear();

      }

      if (m_timeLast5s.elapsed() > 5_s)
      {

         m_timeLast5s.Now();

         m_papplication->post([this]()
            {

               m_pgpucontext->manage_retired_objects();

            });

      }

   }


   void renderer::wait_swap_chain_command_buffer_ready()
   {


   }


   void renderer::wait_command_buffer_ready()
   {


   }


   void renderer::end_frame()
   {

      m_pgpucontext->frame_suffix();

      //end_layer();

      on_end_render(render_target()->m_pgpuframe);

      endFrame();


      //if (m_pgpudevice->m_edevicetarget
      //   == ::gpu::e_device_target_swap_chain)
      //{

      //   //if (!m_puserinteraction)
      //   //{

      //   //   throw ::exception(error_not_ready, "m_puserinteraction is null in graphics::on_end_draw()");

      //   //}


      //   ////auto prendererOutput = m_pgpucontextOutput->get_renderer();

      //   ////m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

      //   ///*prendererOutput->defer_update_renderer();

      //   //prendererOutput->on_graphics_end_draw(m_puserinteraction);

      //   //prenderer->_blend_image(vkimage, rectangle);*/

      //   ////if (m_eoutputOnEndDraw == ::gpu::e_output_swap_chain)
      //   ////{

      //   ////   m_pgpucontext->swap_buffers();

      //   //   //m_pwindow->m_timeLastDrawGuard1.Now();


      //   ////VkImage vkimage = prenderer->m_pvkcrenderpass->m_images[prenderer->m_uCurrentSwapChainImage];

      //   //::int_rectangle rectangle;

      //   //if (!m_puserinteraction->host_rectangle().size().is_empty())
      //   //{

      //   //   rectangle = m_puserinteraction->host_rectangle();

      //   //}
      //   //else
      //   //{

      //   //   rectangle = { 0, 0, 1920, 1080 };

      //   //}

      //   ////::cast < ::windowing::window > pwindow = m_puserinteraction->m_pacmewindowingwindow;

      //   ////if (!m_pgpucontextOutput)
      //   ////{

      //   ////   øconstruct(m_pgpucontextOutput);

      //   ////   m_pgpucontextOutput = m_papplication->get_gpu()->get_device(pwindow, pwindow->get_window_rectangle())->start_swap_chain_context(this, pwindow);

      //   ////   //m_pgpucontextOutput->create_window_buffer(pwindow);

      //   ////}

      //   ////auto prendererOutput = m_pgpucontextOutput->get_renderer();


      //   ////m_pgpucontextOutput->m_size = rectanglePlacement.size();

      //   ////auto pgpucontextOpenGL = m_pgpucontextOutput;

      //   ////pgpucontextOpenGL->m_sizeHost = rectanglePlacement.size();

      //   ////pgpucontextOpenGL->set_placement(rectanglePlacement);

      //   ////m_pgpucontext->m_eoutput = ::gpu::e_output_gpu_buffer;

      //   ////prendererOutput->defer_update_render_pass();

      //   ////if (!m_penddraw)
      //   ////{

      //   ////   create_end_draw();

      //   ////}

      //   ////if (m_penddraw)
      //   ////{

      //   ////   on_endDraw(m_puserinteraction, pgpurenderer);

      //   ////}
      //   ////else
      ////   {

      ////      //auto pswapchain = m_pgpucontext->m_pgpudevice->get_swap_chain();

      ////      auto pgpurenderer = m_pgpurenderer;

      ////      pgpurenderer->endDraw(this, m_puserinteraction);

      ////      //auto prendererOutput = end_draw_renderer_output();

      ////      //prendererOutput->endDraw(m_puserinteraction, pgpurenderer);

      ////   }

      ////   m_pgpucontext->m_pgpudevice->on_top_end_frame();

      ////}
      ////else if (m_pgpucontext->m_pgpudevice->m_edevicetarget
      ////   == ::gpu::e_device_target_off_screen)
      ////{

      ////   //m_pgpucontext->swap_buffers();

      //// //}
      //// //else
      //// //{

      ////   //read_to_cpu_buffer();

      ////   throw ::exception(error_not_implemented, "renderer::endDraw() not implemented for e_output_cpu_buffer");

      ////   /*m_pimage->map();

      ////   m_pimage->copy(&m_pgpucontext->m_pcpubuffer->m_pixmap);*/

      ////}

      //}

   }


   void renderer::post_on_after_end_frame(const ::procedure &procedure)
   {

      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_procedureaOnAfterEndFrame.add(procedure);

   }


   void renderer::post_on_just_before_frame_next_start(const ::procedure & procedure)
   {

      m_procedureaOnJustBeforeFrameNextStart.add(procedure);

   }




} // namespace gpu



