// Created from graphics3d/impact3d/renderer by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "approach.h"
#include "context.h"
#include "cpu_buffer.h"
#include "device.h"
#include "layer.h"
#include "texture.h"
#include "renderer.h"
#include "render_target.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/system.h"
#include "aura/user/user/interaction.h"


namespace gpu
{

   
   renderer::renderer()
   {


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


   void renderer::set_single_frame()
   {

      m_iFrameSerial2 = 0;
      m_iCurrentFrame2 = 0;
      m_iFrameCount2 = 1;
      m_estate = e_state_single_frame;

   }


   void renderer::restart_frame_counter()
   {

      if (m_estate != e_state_single_frame)
      {

         m_iCurrentFrame2 = -1;
         m_iFrameSerial2 = -1;

         on_happening(e_happening_reset_frame_counter);

      }

   }


   void renderer::on_happening(enum_happening ehappening)
   {

      switch (ehappening)
      {
      case e_happening_reset_frame_counter:
         ASSERT(m_estate != e_state_single_frame);
         m_estate = e_state_initial;
         break;
      case e_happening_new_frame:
         ASSERT(m_estate == e_state_initial || m_estate == e_state_ended_frame);
         m_estate = e_state_new_frame;
         break;
      case e_happening_begin_frame:
         ASSERT(m_estate == e_state_new_frame);
         m_estate = e_state_began_frame;
         break;
      case e_happening_begin_render:
         ASSERT(m_estate == e_state_began_frame);
         m_estate = e_state_began_render;
         break;
      case e_happening_end_render:
         ASSERT(m_estate == e_state_began_render);
         m_estate = e_state_ended_render;
         break;
      case e_happening_end_frame:
         ASSERT(m_estate == e_state_ended_render);
         m_estate = e_state_ended_frame;
         break;
      default:
         throw ::exception(error_unexpected_situation);
      };

   }


   void renderer::initialize_renderer(::gpu::context * pgpucontext)
   {

      m_pgpucontext = pgpucontext;

      //m_pgpucontext->m_prenderer = this;

      //m_eoutput = eoutput;

      //m_escene = escene;

      //::particle::initialize(pparticle);

      //m_pgpucontext = system()->get_gpu()->create_context(this);

      //m_pgpucontext->initialize(this);


   }


   ::pointer < texture> renderer::create_texture(const ::int_size& size)
   {

      auto ptexture = __øcreate< texture>();

      ptexture->initialize_gpu_texture(this, size);

      m_pgpucontext->on_create_texture(ptexture);

      return ptexture;

   }


   void renderer::take_snapshot(layer* player, const ::int_rectangle& rectangleTarget)
   {

      auto ptextureSource = m_pgpurendertarget->current_texture();

      __defer_construct(player->m_pgputexture);

      player->m_pgputexture->initialize_gpu_texture(this, rectangleTarget.size());

      m_pgpucontext->on_take_snapshot(player, ptextureSource);

   }


   ::pointer<::gpu::shader> renderer::create_shader(
      const ::file::path& pathVert,
      const ::file::path& pathFrag,
      const ::array<::gpu::shader::enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      const ::particle_pointer& pVertexInput,
      const ::gpu::property* ppropertiesPush,
      const ::gpu::property* ppropertiesInputLayout,
      ::gpu::shader::enum_flag eflag)
   {

      auto pshader = __øcreate < ::gpu::shader >();

      pshader->initialize_shader(this, 
         pathVert, pathFrag, eslota, 
         pLocalDescriptorSet, pVertexInput, 
         ppropertiesPush, ppropertiesInputLayout, eflag);

      return pshader;

   }



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
         m_pgpucontext->send([this]()
            {
               //if (::is_set(m_pobject))
               {

                  ::gpu::context_lock lock(m_pgpucontext);

                  m_pgpucontext->make_current();

                  // global_transform

                  ////{

                  ////   float x = (float) psession->get_cursor_position().x();

                  ////   float y = (float) psession->get_cursor_position().y();

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

            ::gpu::context_lock lock(m_pgpucontext);

            //m_pgpucontext->make_current();

            //// global_transform

            //////{

            //////   float x = (float) psession->get_cursor_position().x();

            //////   float y = (float) psession->get_cursor_position().y();

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
//   __defer_construct(m_pimageFromGpu);
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


   void renderer::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   int renderer::get_frame_index() const
   {

      assert(m_iFrameSerial2 >= 0
         && m_iCurrentFrame2 >= 0
         && m_estate != e_state_initial
         && "Cannot get frame index when frame not in progress");

      return (int)m_iCurrentFrame2;

   }


   int renderer::get_frame_count() const
   {

      return (int) m_iFrameCount2;

   }


   void renderer::on_new_frame()
   {

      auto iFrameCount = get_frame_count();

      m_iFrameSerial2++;

      m_iCurrentFrame2 = (m_iCurrentFrame2 + 1) % iFrameCount;

      on_happening(e_happening_new_frame);

   }


   ::pointer < frame > renderer::beginFrame()
   {

      on_happening(e_happening_begin_frame);

      return m_pframe;

   }


   //void renderer::on_before_begin_frame(::draw2d_gpu::graphics* pgraphics)
   //{


   //}


   //void renderer::on_after_end_frame(::draw2d_gpu::graphics* pgraphics)
   //{


   //}


   void renderer::on_begin_render(frame* pframe)
   {

      on_happening(e_happening_begin_render);

   }


   void renderer::on_end_render(frame* pframe)
   {

      on_happening(e_happening_end_render);

   }


   void renderer::endFrame()
   {

      on_happening(e_happening_end_frame);

   }

   
   void renderer::endDraw(::draw2d_gpu::graphics * pgraphics, ::user::interaction * puserinteraction)
   {


   }


   void renderer::defer_update_renderer()
   {


   }


   //void renderer::endDraw(::user::interaction* puserinteraction)
   //{



   //}


   void renderer::blend(::gpu::renderer* prenderer)
   {

      throw ::interface_only();

   }


   void renderer::clear(::gpu::texture* ptexture)
   {

      throw ::interface_only();

   }


   void renderer::blend(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource, const ::int_rectangle& rectangleTarget)
   {

      throw::interface_only();

   }


   void renderer::soft_restore_context()
   {


   }


   void renderer::endDrawEndDraw()
   {


   }


   void renderer::do_on_frame(const ::procedure& procedure)
   {

      defer_update_renderer();

      on_new_frame();

      auto pframe = beginFrame();

      on_begin_render(pframe);

      procedure();

      on_end_render(pframe);

      endFrame();

   }


   void renderer::start_layer(const ::int_rectangle& rectangleLayer)
   {

      m_pgpucontext->m_pgpudevice->layer_start(this, rectangleLayer);

   }


   int_rectangle renderer::end_layer()
   {

      return m_pgpucontext->m_pgpudevice->layer_end();

   }


   void renderer::on_start_layer(layer* player)
   {


   }


   void renderer::start_frame()
   {

      auto etype = m_pgpucontext->m_etype;

      auto eoutput = m_pgpucontext->m_eoutput;

      auto escene = m_pgpucontext->m_escene;

      defer_update_renderer();

      on_new_frame();

      beginFrame();

      on_begin_render(m_pframe);

      m_pgpucontext->frame_prefix();

   }


   void renderer::end_frame()
   {

      m_pgpucontext->frame_suffix();

      //end_layer();

      on_end_render(m_pframe);

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


      //   ////VkImage vkimage = prenderer->m_pvkcrenderpass->m_images[prenderer->currentImageIndex];

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

      //   ////   __øconstruct(m_pgpucontextOutput);

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


} // namespace gpu



