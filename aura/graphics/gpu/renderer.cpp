// Created from graphics3d/impact3d/renderer by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "approach.h"
#include "context.h"
#include "cpu_buffer.h"
#include "renderer.h"
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

      m_eoutput = ::gpu::e_output_none;

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


   //::int_rectangle renderer::rectangle()
   //{

   //   return m_rectangle;

   //}


   bool renderer::render_step()
   {

      return true;

   }


   void renderer::on_happening(enum_happening ehappening)
   {

      switch (ehappening)
      {
      case e_happening_reset_frame_counter:
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


   void renderer::initialize_renderer(::gpu::context * pgpucontext, ::gpu::enum_output eoutput, ::gpu::enum_scene escene)
   {

      m_pgpucontext = pgpucontext;

      //m_pgpucontext->m_prenderer = this;

      m_eoutput = eoutput;

      m_escene = escene;

      //::particle::initialize(pparticle);

      //m_pgpucontext = system()->get_gpu()->create_context(this);

      //m_pgpucontext->initialize(this);


   }


   ::pointer<::gpu::shader> renderer::create_shader(
      const ::file::path& pathVert,
      const ::file::path& pathFrag,
      const ::array<::gpu::shader::enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      const ::particle_pointer& pVertexInput,
      const ::gpu::property* pproperties,
      ::gpu::shader::enum_flag eflag)
   {

      auto pshader = __øcreate < ::gpu::shader >();

      pshader->initialize_shader(this, pathVert, pathFrag, eslota, pLocalDescriptorSet, pVertexInput, pproperties, eflag);

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

      throw ::interface_only();

      return -1;

   }


   int renderer::get_frame_count() const
   {

      throw ::interface_only();

      return -1;

   }


   void renderer::on_new_frame()
   {


   }


   ::pointer < frame > renderer::beginFrame()
   {

      return m_pframe;

   }


   void renderer::on_begin_render(frame* pframe)
   {

   }

   void renderer::on_end_render(frame* pframe)
   {

   }

   void renderer::endFrame()
   {

   }

   
   void renderer::endDraw(::user::interaction * puserinteraction, ::gpu::renderer * pgpurenderer)
   {


   }


   void renderer::defer_update_render_pass()
   {


   }


   //void renderer::endDraw(::user::interaction* puserinteraction)
   //{



   //}


} // namespace gpu



