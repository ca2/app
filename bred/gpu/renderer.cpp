// Created from graphics3d/impact3d/renderer by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "bred_approach.h"
#include "command_buffer.h"
#include "context.h"
#include "cpu_buffer.h"
#include "device.h"
#include "frame.h"
#include "layer.h"
#include "post_frame_context_registry.h"
#include "queue.h"
#include "texture.h"
#include "renderer.h"
//#include "layer_state.h"
#include "render_target.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/graphics.h"
#include "bred/gpu/swap_chain.h"
#include "aura/graphics/graphics/context.h"
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
      
      //m_bFrameStarted = false;

   }


   renderer::~renderer()
   {


   }



#ifdef _DEBUG

   ::i64 renderer::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   ::i64 renderer::decrement_reference_count()
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

      //defer_construct_newø(m_prenderstate);
//
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


   void renderer::on_resize(const ::i32_size& size)
   {

      if (size == m_sizeRenderer)
      {

         return;

      }

      //auto eoutput = m_pgpucontext->m_eoutput;

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
      //         auto poffscreenrendertargetview = allocateø offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
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
      //         auto paccumulationrendertargetview = allocateø accumulation_render_target(this, m_extentRenderer, m_prendertargetview);
      //         paccumulationrendertargetview->m_formatImage = VK_FORMAT_R32G32B32A32_SFLOAT;
      //         paccumulationrendertargetview->m_formatAlphaAccumulation = VK_FORMAT_R32_SFLOAT;
      //         m_prendertargetview = paccumulationrendertargetview;
      //
      //         //construct_newø(m_prendererResolve);
      //
      //         //m_prendererResolve->initialize_renderer(m_pgpucontext, ::gpu::e_output_resolve_color_and_alpha_accumulation_buffers);
      //
      //         //m_prendererResolve->set_placement(m_pgpucontext->rectangle);
      //         //
      //         //            auto poffscreenrendertargetview = allocateø offscreen_render_target(m_pgpucontext, m_extentRenderer, m_prendertargetviewResolve);
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
      //         auto poffscreenrendertargetview = allocateø offscreen_render_target(this, m_extentRenderer, m_prendertargetview);
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


   ::pointer < texture> renderer::create_image_texture(const ::i32_size& size, bool bWithDepth)
   {

      auto ptexture = createø< texture>();

      ::gpu::texture_attributes textureattributes(::i32_rectangle{size});

      ::gpu::texture_flags textureflags;

      textureflags.m_bWithDepth = bWithDepth;

      ptexture->initialize_texture(m_pgpucontext, textureattributes, textureflags);

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

   //   auto pshader = createø < ::gpu::shader >();
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


   //void renderer::set_placement(const ::i32_rectangle& rectanglePlacement)
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


   void renderer::layer_end_copy()
   {

      auto pgpulayer = ::gpu::current_layer();

      if (pgpulayer)
      {

         ::gpu::context_lock contextlock(m_pgpucontext);

         auto ptextureTarget = pgpulayer->texture();

         auto ptextureSource = m_pgpucontext->current_target_texture(pgpulayer);

         m_pgpucontext->copy(ptextureTarget, ptextureSource, &pgpulayer->m_pgpufence);

         //player->m_bFinished = false;
         //ptextureTarget->defer_fence();

      }

   }


   void renderer::layer_end_submit()
   {


   }


   void renderer::layer_end_after_submit()
   {


   }


   ::gpu::render_target * renderer::render_target()
   {

      if (::is_null(m_pgpurendertarget2))
      {

         m_pgpurendertarget2 = on_create_render_target();

         defer_initialize_render_target();

      }

      return m_pgpurendertarget2;

   }


   ::gpu::texture* renderer::current_render_target_texture(::gpu::layer* pgpulayer)
   {

      return render_target()->current_texture(pgpulayer);

   }


   ::gpu::command_buffer* renderer::getCurrentCommandBuffer2(::gpu::layer* pgpulayer)
   {

      auto egpuframestate = m_pgpucontext->m_pgpudevice->current_frame()->m_egpuframestate;

      assert(egpuframestate == e_gpu_frame_state_began_frame &&
             "Cannot get command buffer when frame not in progress");

      if (pgpulayer)
      {

         auto egpulayerstate = pgpulayer->m_egpulayerstate;

         assert(egpulayerstate == e_gpu_layer_state_began_render &&
                "Cannot get command buffer when frame not in progress");

         return pgpulayer->getCurrentCommandBuffer4();

      }

      if (m_pgpucontext->m_eoutput == e_output_swap_chain)
      {
         m_pgpucontext->get_swap_chain()->defer_check_swap_chain();
      }


      if (m_commandbuffera.is_empty())
      {

         create_command_buffers();

      }

      ::collection::index iImageIndex;

      if (m_pgpucontext->m_eoutput == e_output_swap_chain)
      {

         iImageIndex = m_pgpucontext->get_swap_chain()->swap_chain_image_index();

         if (iImageIndex < 0)
         {

            ::warning("iImageIndex < 0 (1)");

         }

      }
      else
      {

         iImageIndex = render_target()->m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

         if (iImageIndex < 0)
         {

            ::warning("iImageIndex < 0 (2)");

         }

      }

      auto pcommandbuffer = m_commandbuffera[iImageIndex];

      pcommandbuffer->m_iCommandBufferFrameIndex2 =
         m_pgpurendertarget2->m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

      pcommandbuffer->m_iCommandBufferImageIndex = iImageIndex;

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

      for (::i32 i = 0; i < m_commandbuffera.size(); i++)
      {

         auto& pcommandbuffer = m_commandbuffera[i];

         defer_constructø(pcommandbuffer);

         pcommandbuffer->initialize_command_buffer(render_target(),
            m_pgpucontext->m_pgpudevice->graphics_queue(),
            e_command_buffer_graphics);

         pcommandbuffer->m_iCommandBufferImageIndex = i;

      }

   }


   void renderer::free_command_buffers()
   {

      m_commandbuffera.clear();

      //return ::gpu::renderer::getCurrentCommandBuffer2(::gpu::current_layer());

      //assert(isFrameStarted && "Cannot get command buffer when frame not in progress");

      //if (m_commandbuffera.is_empty())
      //{

      //   create_command_buffers();

      //}

      //auto pcommandbuffer = m_commandbuffera[m_pgpurendertarget->get_frame_index()];

      //return pcommandbuffer;

   }

   bool renderer::isFrameInProgress() const
   {

      /*if (!m_prenderstate)
      {

         return false;

      }*/

      auto egpuframestate = m_pgpucontext->m_pgpudevice->current_frame()->m_egpuframestate;

      if (egpuframestate < e_gpu_frame_state_began_frame)
      {

         return false;

      }

      if (egpuframestate >= e_gpu_frame_state_ended_frame)
      {

         return false;

      }

      return true;

   }

   ::particle_array * renderer::current_frame_particle_array()
   {

      auto iFrameIndex = m_pgpucontext->m_pgpudevice->get_frame_index3();

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
         m_pgpucontext->sendø() << [this]()
            {
               //if (::is_set(m_pobject))
               {

                  //::gpu::context_lock lock(m_pgpucontext);

                  //m_pgpucontext->make_current();

                  // global_transform

                  ////{

                  ////   ::f32 x = (::f32) psession->get_cursor_position().x;

                  ////   ::f32 y = (::f32) psession->get_cursor_position().y();

                  ////   m_papplication->m_pprogram->m_pshader->setVec2("mouse", x, y);
                  ////   m_papplication->m_pprogram->m_pshader->setVec2("iMouse", x, y);

                  ////}

                  //{

                  //   ::f32 cx = (::f32) m_papplication->m_pbuffer->m_pimage->width();

                  //   ::f32 cy = (::f32) m_papplication->m_pbuffer->m_pimage->height();

                  //   m_papplication->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
                  //   m_papplication->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

                  //}

                  //{

                  //   ::f64 dElapsed = m_timeStart.elapsed().floating_second().m_f64;

                  //   ::f64 dTime = dElapsed / 1000.0;

                  //   ::f32 time = (::f32) dTime;

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

                        //::f64_rectangle rectangleTarget(m_rectangle);

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
            };

      }

      //_001OnDraw1Through3(pgraphics);
      //return {};
      //return {};


   }


   //::gpu::command_buffer* renderer::getCurrentCommandBuffer2(::gpu::current_layer())
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

            //////   ::f32 x = (::f32) psession->get_cursor_position().x;

            //////   ::f32 y = (::f32) psession->get_cursor_position().y();

            //////   m_papplication->m_pprogram->m_pshader->setVec2("mouse", x, y);
            //////   m_papplication->m_pprogram->m_pshader->setVec2("iMouse", x, y);

            //////}

            ////{

            ////   ::f32 cx = (::f32) m_papplication->m_pbuffer->m_pimage->width();

            ////   ::f32 cy = (::f32) m_papplication->m_pbuffer->m_pimage->height();

            ////   m_papplication->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
            ////   m_papplication->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

            ////}

            ////{

            ////   ::f64 dElapsed = m_timeStart.elapsed().floating_second().m_f64;

            ////   ::f64 dTime = dElapsed / 1000.0;

            ////   ::f32 time = (::f32) dTime;

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

         //::f64_rectangle rectangleTarget(m_rectangle);

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


   void renderer::on_end_frame()
   {

      auto bCpuBuffer =
         m_pgpucontext && m_pgpucontext->m_eoutput == ::gpu::e_output_cpu_buffer;

      ::gpu::dispatch_cpu_sampling(
         bCpuBuffer,
         [this]()
         {

            sample_to_cpu_buffer();

         });

   }


   void renderer::sample_to_cpu_buffer()
   {

      read_to_cpu_buffer();

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
   //   defer_constructø(m_pimageFromGpu);
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


   void renderer::on_new_frame()
   {

      //auto prendertarget = render_target();

      //prendertarget->on_new_frame();

      

   }


   void renderer::on_begin_render(::gpu::layer * pgpulayer)
   {

      ///m_prenderstate->on_happening(::gpu::e_happening_begin_render);

      pgpulayer->start_layer_render();

      //bool bLayerStarted = false;

      //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      //{

      //   if (m_pgpucontext->m_pgpucompositor)
      //   {

      //      auto etypeContext = m_pgpucontext->m_etype;

      //      auto eoutputContext = m_pgpucontext->m_eoutput;

      //      m_iSentLayerCount++;

      //      m_pgpucontext->m_pgpucompositor->start_gpu_layer(pgpulayer);

      //      bLayerStarted = true;

      //   }

      //}

      //if (pgpulayer)
      //{

      //   if (m_pgpucontext->m_pgpucompositor)
      //   {

      //      //auto etypeContext = m_pgpucontext->m_etype;

      //      //auto eoutputContext = m_pgpucontext->m_eoutput;

      //      m_iSentLayerCount++;

      //      //m_pgpucontext->m_pgpucompositor->start_gpu_layer(pgpulayer);

      //      pgpulayer->layer_start();

      //      bLayerStarted = true;

      //   }

      //}
      //if (m_iSentLayerCount <= 0)
      //{

      //   auto pcommandbuffer = getCurrentCommandBuffer2(::gpu::current_layer());

      //   if (pcommandbuffer)
      //   {

      //      pcommandbuffer->reset();

      //   }

      //}

      /////if (!bLayerStarted)
      //{

      //   //auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;

      //   //auto etypeGpuContext = m_pgpucontext->m_etype;

      //   //if (!bUseSwapChain
      //      //|| etypeGpuContext != ::gpu::context::e_type_window)
      //   {

      //      _on_begin_render(pgpulayer);

      //   }

      //}

      /////if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      //{

      //   if (m_pgpucontext->m_pgpucompositor)
      //   {

      //      m_pgpucontext->m_pgpucompositor->gpu_layer_on_after_begin_render();

      //   }

      //}

      //on_final_begin_render();

   }


   void renderer::on_final_begin_render()
   {


   }


   void renderer::on_end_render(::gpu::layer * pgpulayer)
   {

      ///if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            m_pgpucontext->m_pgpucompositor->gpu_layer_on_before_end_render();

         }

      }

      bool bLayerPresent = false;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         pgpulayer->layer_end();

         //if (m_pgpucontext->m_pgpucompositor)
         //{

            //m_pgpucontext->m_pgpucompositor->end_gpu_layer(pgpulayer);
            //auto pgpulayer = ::gpu::current_layer();

            //if (pgpulayer)
            //{

//               m_pgpucontext->on_end_layer(pgpulayer);

  //          }

    //        bLayerPresent = true;

         //}

      }

      auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;

      auto etypeGpuContext = m_pgpucontext->m_etype;

      if (!bUseSwapChain || etypeGpuContext != ::gpu::context::e_type_window)
      {

         _on_end_render(pgpulayer);

      }

      layer_end_copy();

      layer_end_submit();

      ///m_prenderstate->on_happening(::gpu::e_happening_end_render);

      pgpulayer->end_layer_render();

   }


   void renderer::_on_begin_render(::gpu::layer * pgpulayer)
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


   void renderer::_on_end_render(::gpu::layer * pgpulayer)
   {


   }


   void renderer::endDraw(::gpu::graphics* pgraphics, ::user::interaction* puserinteraction)
   {


   }


   //void renderer::on_defer_update_renderer_allocate_render_target(::gpu::enum_output eoutput, const ::i32_size& size, ::gpu::render_target* previous)
   //{

   //   throw ::interface_only();
   //   //::pointer < ::gpu::render_target > pgpurendertarget;

   //   //if (eoutput == ::gpu::e_output_cpu_buffer
   //   //   || eoutput == ::gpu::e_output_gpu_buffer)
   //   //{

   //   //   pgpurendertarget = allocateø offscreen_render_target();
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
   //   //   pgpurendertarget = allocateø offscreen_render_target();
   //   //   //#ifdef WINDOWS_DESKTOP
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
   //   //   //#else
   //   //   //         poffscreenrendertargetview->m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
   //   //   //#endif
   //   //   //m_pgpurendertarget = poffscreenrendertargetview;

   //   //   //m_prendertargetview = allocateø swap_chain_render_target(this, size, m_prendertargetview);
   //   //   //m_prendererResolve.release();

   //   //}

   //   //return pgpurendertarget;

   //}


   void renderer::defer_update_renderer()
   {

      auto rectangleContext = m_pgpucontext->rectangle();

      auto sizeContext = rectangleContext.size();

      //auto etypeContext = m_pgpucontext->m_etype;

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

      auto prendertarget = createø<::gpu::render_target>();

      prendertarget->m_bAdvancedPipelineSynchronization = true;

      return prendertarget;

   }


   ::pointer < swap_chain > renderer::on_create_swap_chain()
   {

      return createø<swap_chain>();

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

   //   ::i32_size size = rectangle.size();

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


   // void renderer::clear(::gpu::texture* ptexture)
   // {
   //
   //    throw ::interface_only();
   //
   // }


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

   
   //void renderer::frame_prefix()
   //{

   //   defer_update_renderer();

   //   auto pgpulayer = beginFrame();

   //   on_begin_render(pgpulayer);

   //}


   //void renderer::frame_suffix()
   //{

   //   ::gpu::context_lock contextlock(m_pgpucontext);

   //   on_end_render(::gpu::current_layer());

   //   endFrame();

   //}




   void renderer::layer_start(bool bFirstLayer)
   {

      auto player = m_pgpucontext->m_pgpudevice->create_gpu_layer(this);

      player->m_bFirstLayer = bFirstLayer;

      player->layer_start();

   }


   void renderer::layer_end()
   {

      auto player = m_pgpucontext->m_pgpudevice->current_layer();

      player->layer_end();

   }


   void renderer::on_start_layer(layer* pgpulayer)
   {

      on_begin_render(pgpulayer);

      //m_pgpulayer = player;

      m_pgpucontext->on_start_layer(pgpulayer);

      //if (m_pgpucontext->m_pgpudevice->get_previous_layer(player) != nullptr)
      //{

      //   getCurrentCommandBuffer2(player)->reset();

      //}
      /// if (!bLayerStarted)
      {

         // auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;

         // auto etypeGpuContext = m_pgpucontext->m_etype;

         // if (!bUseSwapChain
         //|| etypeGpuContext != ::gpu::context::e_type_window)
         {

            _on_begin_render(pgpulayer);
         }
      }

      /// if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         if (m_pgpucontext->m_pgpucompositor)
         {

            m_pgpucontext->m_pgpucompositor->gpu_layer_on_after_begin_render();
         }
      }

      on_final_begin_render();


   }


   void renderer::on_end_layer(layer* player)
   {

      m_pgpucontext->on_end_layer(player);

      //auto ptextureTarget = pgpulayer->texture();

      //auto ptextureSource = m_pgpucontext->current_target_texture();
      //
      ////auto ptextureSource = m_pgpurendertarget->current_texture();

      //m_pgpucontext->copy(ptextureTarget, ptextureSource);

      //auto pcommandbuffer = getCurrentCommandBuffer2(player);

      //if (pcommandbuffer)
      //{

      //   pcommandbuffer->submit_command_buffer(player);

      //   pcommandbuffer->wait_commands_to_execute();

      //}

   }

   // aaaxyz
   //void renderer::start_frame()
   void renderer::start_layer(bool bFirstLayer)
   {

      if (bFirstLayer)
      {

         m_pgpucontext->m_pgpudevice->start_stacking_layers();

      }

//      auto etype = m_pgpucontext->m_etype;
//
//      auto eoutput = m_pgpucontext->m_eoutput;
//
//      auto escene = m_pgpucontext->m_escene;

      defer_update_renderer();

      //if (pgraphicscontext->egraphics() == e_graphics_draw)
      {

         layer_start(bFirstLayer);

         //on_begin_render(render_target()->m_pgpulayer);

         auto egpuframestate = m_pgpucontext->m_pgpudevice->current_frame()->m_egpuframestate;

         if (egpuframestate == ::gpu::e_gpu_frame_state_began_frame)
         {

            ::i32 iFrameIndex = m_pgpucontext->m_pgpudevice->get_frame_index3();

            if (iFrameIndex < 0)
            {

               information("iFrameIndex < 0 ::gpu::graphics::on_begin_draw");

            }

            auto ppoolgroupFrame = m_pgpucontext->m_pgpudevice->frame_pool_group(iFrameIndex);

            ppoolgroupFrame->m_pallocator = m_pgpucontext->m_pgpudevice;

            ppoolgroupFrame->m_pongoingparticlearraysource = this;

            ppoolgroupFrame->call_ongoing(e_call_off_to_pool);

            // m_poolmodelbufferCharacter.m_ppoolgroup = ppoolgroupFrame;
            // m_poolmodelbufferLine.m_ppoolgroup = ppoolgroupFrame;

            auto pparticlea = current_frame_particle_array();

            if (pparticlea)
            {

               pparticlea->clear();

            }

         }

      }

      // aaaxyz
      //m_pgpucontext->start_layer(pgraphicscontext);

   }


      // aaaxyz
   // void renderer::end_frame()
   void renderer::end_layer(bool bClosingLayer)
   {

      {

         auto pgpulayer = ::gpu::current_layer();

         pgpulayer->m_bClosingLayer = bClosingLayer;

         on_end_render(pgpulayer);

         if (pgpulayer)
         {

            pgpulayer->layer_on_after_submit();

         }

         ///layer_end();

      }

      // aaaxyz
      // m_pgpucontext->frame_suffix();
      // m_pgpucontext->end_layer(pgraphicscontext);

      //auto pgraphics = pgraphicscontext->draw2d_graphics();


      if (bClosingLayer)
      {

         
      
                                 auto prendererBackBuffer = this;

         auto pgpulayer = ::gpu::current_layer();
         // prendererBackBuffer->frame_prefix();
         //
         // prendererBackBuffer->frame_prefix();
         // on_new_frame();


         ::pointer_array<::gpu::layer> gpulayera;

         auto pgpulayera2 = m_pgpucontext->m_pgpudevice->m_pgpulayera;

         if (pgpulayera2)
         {

            gpulayera = *pgpulayera2;

            auto timeStart = ::time::now();

            while (timeStart.elapsed() < 5_s)
            {

               bool bAnyFailed = false;

               for (auto pgpulayer: gpulayera)
               {

                  if (!pgpulayer->finished_manual_reset_happening()->_wait(0_s))
                  {

                     bAnyFailed = true;

                     break;

                  }

               }

               if (!bAnyFailed)
               {

                  break;

               }

               preempt(1_ms);

            }

            auto fMilliseconds = timeStart.elapsed().floating_millisecond();

            information("it took {} ms waiting for layers to finish drawing", fMilliseconds);

         }

         if (gpulayera.has_element())
         {

            auto prendertargetBackBuffer = prendererBackBuffer->render_target();

            // auto iFrameIndex = prendertargetBackBuffer->get_frame_index();

            auto ptextureBackBuffer = prendertargetBackBuffer->current_texture(pgpulayer);
            //
            // for (auto player : layera)
            // {
            //
            //    if (pgpulayer->getCurrentCommandBuffer4())
            //    {
            //
            //       pgpulayer->getCurrentCommandBuffer4()->wait_commands_to_execute();
            //
            //    }
            //
            // }

            auto iFrameIndex = prendertargetBackBuffer->m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();


            ::pointer_array<::gpu::semaphore> semaphoreaMergeLayersReady;

            {

               // ::i32 iLayer = 0;
               //
               // for (auto player: layera)
               // {
               //
               //    if (iLayer == 2)
               //    {
               //       // information("What happened to the 3D Layer?");
               //    }
               //
               //
               //    //::cast<::gpu_opengl::texture> ptextureSrc = pgpulayer->texture();
               //
               //    auto pgpufence = pgpulayer->m_pgpufence;
               //
               //    if (::is_set(pgpufence))
               //    {
               //
               //       pgpufence->wait_gpu_fence();
               //
               //    }
               //
               //    // m_pshaderBlend3->bind_source(nullptr, ptextureSrc, 0);
               //    iLayer++;
               // }

               //::gpu::context_lock contextlock(this);

               auto pqueueGraphics = m_pgpucontext->m_pgpudevice->graphics_queue();

               auto pgpucommandbuffer = m_pgpucontext->beginSingleTimeCommands(pqueueGraphics);

               m_pgpucontext->merge_layers(pgpucommandbuffer, ptextureBackBuffer, &gpulayera);

               ::pointer_array<::gpu::semaphore> semaphoreaWait;

               for (auto &pgpulayer: gpulayera)
               {

                  if (pgpulayer)
                  {

                     if (pgpulayer->m_pgpusemaphoreSignal)
                     {

                        semaphoreaWait.add(pgpulayer->m_pgpusemaphoreSignal);

                     }

                  }

               }

               if (defer_constructø(m_pgpucontext->m_gpusemaphoreaMergeLayersReady.atø(iFrameIndex)))
               {

                  m_pgpucontext->m_gpusemaphoreaMergeLayersReady[iFrameIndex]->initialize_gpu_semaphore(m_pgpucontext);

               }

               semaphoreaMergeLayersReady.add(m_pgpucontext->m_gpusemaphoreaMergeLayersReady[iFrameIndex]);

               pgpucommandbuffer->m_semaphoreaWait.append_unique(semaphoreaWait);

               pgpucommandbuffer->m_semaphoreaSignal.append_unique(semaphoreaMergeLayersReady);

               m_pgpucontext->endSingleTimeCommands(pgpucommandbuffer);
            }

            //::cast<swap_chain> pswapchain = m_pgpucontext->get_swap_chain();

            //if (!pswapchain->m_bSwapChainInitialized)
            //{

            //   pswapchain->initialize_gpu_swap_chain(prendererBackBuffer);
            //}

            //::cast<gpu::render_target> pgpurendertarget = pswapchain;

            //if (pgpurendertarget)
            //{

            //   if (!pgpurendertarget->m_pgpurenderer)
            //   {

            //      pgpurendertarget->initialize_render_target(this, m_pgpucontext->m_rectangle.size(), nullptr);
            //   }
            //}

            // for (auto player : *playera)
            // {
            //
            //    if (pgpulayer->getCurrentCommandBuffer4())
            //    {
            //
            //       pgpulayer->getCurrentCommandBuffer4()->wait_commands_to_execute();
            //
            //    }
            //
            // }

            // #if !defined(__APPLE__)

            if (m_pgpucontext->m_pgpudevice->m_pgpucontextMain == m_pgpucontext)
            {

               information("we are in the renderer of the context that owns the swap chain????");

            }
            else
            {

               information("we aren't in the renderer of the context that owns the swap chain????");

            }

            auto pgpuswapchain = m_pgpucontext->m_pgpudevice->m_pgpucontextMain->get_swap_chain();

               auto pgpucontextSwapChain = pgpuswapchain->m_pgpucontext;

                           if (!pgpuswapchain->m_bSwapChainInitialized)
               {

                  pgpuswapchain->initialize_gpu_swap_chain(prendererBackBuffer);
               }

               ::cast<gpu::render_target> pgpurendertarget = pgpuswapchain;

               if (pgpurendertarget)
               {

                  if (!pgpurendertarget->m_pgpurenderer)
                  {

                     pgpurendertarget->initialize_render_target(this, m_pgpucontext->m_rectangle.size(), nullptr);
                  }
               }



               ::cast<renderer> pgpurendererSwapChain = pgpucontextSwapChain->m_pgpurenderer;

               //pgpucontextSwapChain->start_frame();

               //pgpucontextSwapChain->start_layer();

               //::cast<command_buffer> pcommandbufferSwapChain =
                 // pgpurendererSwapChain->getCurrentCommandBuffer2(::gpu::current_layer());
               ::pointer<command_buffer> pcommandbufferSwapChain = pgpucontextSwapChain->beginSingleTimeCommands(pgpucontextSwapChain->m_pgpudevice->graphics_queue()
               );


               //pcommandbuffer->begin_command_buffer(false);
               auto iSwapChainFrameIndex = pgpuswapchain->swap_chain_frame_index();

               if (defer_constructø(pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex)))
               {

                  pgpucontextSwapChain->m_gpusemaphoreaPresentReady[iSwapChainFrameIndex]->initialize_gpu_semaphore(
                     m_pgpucontext);
               }

               auto &framesync = pgpuswapchain->frame(iSwapChainFrameIndex);

               if (::is_set(framesync.m_pgpusemaphoreImageAvailable))
               {

                  pcommandbufferSwapChain->m_semaphoreaWait.add_unique(framesync.m_pgpusemaphoreImageAvailable);
               }

               pcommandbufferSwapChain->m_pgpufence = framesync.m_pgpufenceInFlight;
               if (semaphoreaMergeLayersReady.has_element())
               {

                  pcommandbufferSwapChain->m_semaphoreaWait.append_unique(semaphoreaMergeLayersReady);
               }
               pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(
                  pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex));

               // pswapchain->m_pwindowSwapChain->_main_send([pswapchain, ptextureBackBuffer]()
               //  system()->acme_windowing()
               //  ->_main_send([pswapchain, ptextureBackBuffer]()
               //{


               pgpuswapchain->present(ptextureBackBuffer, pcommandbufferSwapChain);


               pgpuswapchain->set_present_state(pcommandbufferSwapChain);
               //pgpucontextSwapChain->end_layer();

               //pgpucontextSwapChain->end_frame();
            //}

            // pcommandbuffer->m_semaphoreaWait.add_unique(pswapchain->m_fr->m_semaphoreaSignal);
            //}

            //});

            // prendererBackBuffer->frame_suffix();


            // #endif
            //          pcommandbuffer->submit_command_buffer(nullptr);

               pgpuswapchain->m_gpusemaphoreaWait.append_unique(pcommandbufferSwapChain->m_semaphoreaSignal);

                              pgpucontextSwapChain->endSingleTimeCommands(pcommandbufferSwapChain);

framesync.m_pcommandbufferLastSwapChainPresentation = pcommandbufferSwapChain;

               //pswapchain->swap_buffers();
         }

      }

      // end_layer();
      //if (pgraphicscontext->egraphics() == e_graphics_draw)


      // endFrame();


      // if (m_pgpudevice->m_edevicetarget
      //    == ::gpu::e_device_target_swap_chain)
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

      //   //::i32_rectangle rectangle;

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

      //   ////   constructø(m_pgpucontextOutput);

      //   ////   m_pgpucontextOutput = m_papplication->get_gpu()->get_device(pwindow,
      //   pwindow->get_window_rectangle())->start_swap_chain_context(this, pwindow);

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



   bool renderer::is_starting_frame()const
   {

      return m_pgpucontext->m_pgpudevice->is_starting_frame();

   }


   //void renderer::on_begin_frame()
   //{


   //}
//
//
//   //::pointer < frame > renderer::beginFrame()
//   void renderer::start_frame()
//   {
//
//      if (m_procedureaOnJustBeforeFrameNextStart.has_element())
//      {
//
//         try
//         {
//
//            for (auto & procedure : m_procedureaOnJustBeforeFrameNextStart)
//            {
//
//               try
//               {
//
//                  procedure();
//
//               }
//               catch (...)
//               {
//
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//
//         }
//
//         m_procedureaOnJustBeforeFrameNextStart.clear();
//
//      }
//
//      auto pcontext = m_pgpucontext;
//
//      auto pgpudevice = pcontext->m_pgpudevice;
//
//      //auto pgpulayer = createø < ::gpu::frame >();
//
//      //::gpu::set_current_layer(pgpulayer);
//
//      assert(!isFrameInProgress() && "Can't call beginFrame while already in progress");
//
//      m_prenderstate->on_happening(e_happening_begin_frame);
//
//      //m_bFrameStarted = true;
//
//      //if (m_papplication->m_gpu.m_bUseSwapChainWindow
//      //   && m_pgpucontext->m_etype != ::gpu::context::e_type_window)
//      //{
//
//      //   auto player = pgpudevice->next_layer(pcontext->m_pgpurenderer);
//
//      //   //m_pgpulayer = player;
//
//      //   //player = pgpulayer;
//
//      //   pgpulayer = player;
//
//      //}
//
//      ///::cast < command_buffer > pcommandbuffer = getCurrentCommandBuffer2(pgpulayer);
//
//      //auto iImageIndex = pcommandbuffer->m_iCommandBufferImageIndex;
//
////      auto pszCommandBufferAnnotation = pcommandbuffer->m_strAnnotation.c_str();
//
//      static ::i32 s_iFrameIndex0LayerDraw2dCount = 0;
//
////      auto iLayer = pgpudevice->m_iLayer;
////
////      auto iFrameSerial = pgpudevice->m_iFrameSerial2;
////
////      auto iCurrentFrame = pgpudevice->m_iCurrentFrame2;
//
//      //if (iImageIndex == 0 && pcommandbuffer->m_strAnnotation == "layer.draw2d")
//      //{
//
//      //   s_iFrameIndex0LayerDraw2dCount++;
//
//      //}
//
//      //on_begin_frame();
//
//      ///pgpulayer->m_pgpucommandbuffer = pcommandbuffer.m_p;
//
//      //render_target()->m_pgpulayer = pgpulayer;
//
//      auto bUseSwapChain = m_papplication->m_gpu.m_bUseSwapChainWindow;
//
//      auto etypeGpuContext = m_pgpucontext->m_etype;
//
//      //if (!bUseSwapChain
//        // || etypeGpuContext != ::gpu::context::e_type_window)
//      //{
//
//        // wait_command_buffer_ready();
//
//         //pcommandbuffer->begin_command_buffer(false);
//
//      //}
//
//      //return render_target()->m_pgpulayer;
//
//   }
//
//
//   void renderer::end_frame()
//   {
//
//      m_prenderstate->on_happening(e_happening_end_frame);
//
//      //m_bFrameStarted = false;
//
//      if (m_procedureaOnAfterEndFrame.has_element())
//      {
//
//         try
//         {
//
//            for (auto &procedure: m_procedureaOnAfterEndFrame)
//            {
//               try
//               {
//
//                  procedure();
//
//               }
//               catch (...)
//               {
//
//
//               }
//            }
//
//         }
//         catch (...)
//         {
//
//
//         }
//         m_procedureaOnAfterEndFrame.clear();
//
//      }
//
//      if (m_timeLast5s.elapsed() > 5_s)
//      {
//
//         m_timeLast5s.Now();
//
//         m_papplication->post([this]()
//            {
//
//               m_pgpucontext->manage_retired_objects();
//
//            });
//
//      }
//
//   }


   void renderer::wait_swap_chain_command_buffer_ready()
   {


   }


   void renderer::wait_command_buffer_ready()
   {


   }





} // namespace gpu



