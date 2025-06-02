// Created from graphics3d/impact3d/render by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "approach.h"
#include "context.h"
#include "cpu_buffer.h"
#include "render.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
#include "aura/platform/system.h"
#include "aura/user/user/interaction.h"


namespace gpu
{

   
   render::render()
   {


   }


   render::~render()
   {


   }



#ifdef _DEBUG

   long long render::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   long long render::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif

   bool render::render_step()
   {

      return true;

   }

   void render::initialize(::particle * pparticle)
   {

      ::particle::initialize(pparticle);

      //m_pgpucontext = system()->get_gpu()->create_context(this);

      //m_pgpucontext->initialize(this);


   }


   //void render::initialize_render(::user::interaction * puserinteraction)
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



   void render::draw()
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

                  on_start_drawing(m_pgpucontext);

                  on_global_transform(m_pgpucontext);

                  on_draw(m_pgpucontext);

                  read_to_cpu_buffer();

                  ///m_pobject->draw();

                  //m_papplication->render();

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


   void render::read_to_cpu_buffer()
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

            ////m_papplication->render();

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


   void render::to_draw2d_graphics(::draw2d::graphics_pointer & pgraphics)
   {

      
   //   m_pgpucontext->prepare_for_gpu_read();

   //   slImage.lock();

   //   m_pgpucontext->m_pcpubuffer->gpu_read();

   //}

#if !defined(__APPLE__)

   ::geometry2d::matrix matrixOriginal;

   pgraphics->get(matrixOriginal);

   ::geometry2d::matrix matrix(matrixOriginal);

   matrix.scale(1.0, -1.0);

   matrix.translate(0, m_rectangle.height());

   pgraphics->set(matrix);

#endif


   __defer_construct(m_pimageFromGpu);

   auto size = m_pgpucontext->m_pcpubuffer->m_pimagetarget->m_pimage->m_size;

   m_pimageFromGpu->create(size);

   m_pimageFromGpu->map();

   m_pimageFromGpu->copy(m_pgpucontext->m_pcpubuffer->m_pimagetarget->m_pimage);

   ::image::image_source imagesource(m_pimageFromGpu);

   ::image::image_drawing_options imagedrawingoptions(m_rectangle);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

#if !defined(__APPLE__)

   pgraphics->set(matrixOriginal);

#endif


   }


   void render::on_start_drawing(::gpu::context * pgpucontext)
   {


   }


   void render::on_global_transform(::gpu::context * pgpucontext)
   {


   }


   void render::on_draw(::gpu::context * pgpucontext)
   {


   }


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


} // namespace gpu



