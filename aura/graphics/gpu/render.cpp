// Created from graphics3d/impact3d/render by camilo on 2023-06-16 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#include "framework.h"
#include "approach.h"
#include "buffer.h"
#include "context.h"
#include "render.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/matrix.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/platform/system.h"


namespace gpu
{

   
   render::render()
   {


   }


   render::~render()
   {


   }



#ifdef __DEBUG

   int64_t render::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t render::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif



   void render::initialize(::particle * pparticle)
   {

      ::particle::initialize(pparticle);

      m_pgpucontext = acmesystem()->m_paurasystem->get_gpu()->create_context(this);

      m_pgpucontext->initialize(this);

   }



   void render::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::gpu::context_lock lock(m_pgpucontext);

      //if (::is_set(m_pcontext) && ::is_set(m_pcontext->m_pbuffer)
      //   && m_pcontext->m_pbuffer->m_pimage.ok()
      //   && ::is_set(m_pprogram))
         if (::is_set(m_pgpucontext) && ::is_set(m_pgpucontext->m_pbuffer)
            && m_pgpucontext->m_pbuffer->m_pimage.ok())
         {

         //if (::is_set(m_pobject))
         {

            ::gpu::context_lock lock(m_pgpucontext);

            m_pgpucontext->make_current();

            // global_transform

            ////{

            ////   float x = (float) psession->get_cursor_position().x();

            ////   float y = (float) psession->get_cursor_position().y();

            ////   m_pcontext->m_pprogram->m_pshader->setVec2("mouse", x, y);
            ////   m_pcontext->m_pprogram->m_pshader->setVec2("iMouse", x, y);

            ////}

            //{

            //   float cx = (float) m_pcontext->m_pbuffer->m_pimage->width();

            //   float cy = (float) m_pcontext->m_pbuffer->m_pimage->height();

            //   m_pcontext->m_pprogram->m_pshader->setVec2("resolution", cx, cy);
            //   m_pcontext->m_pprogram->m_pshader->setVec2("iResolution", cx, cy);

            //}

            //{

            //   double dElapsed = m_timeStart.elapsed().floating_second().m_d;

            //   double dTime = dElapsed / 1000.0;

            //   float time = (float) dTime;

            //   m_pcontext->m_pprogram->m_pshader->setFloat("time", time);
            //   m_pcontext->m_pprogram->m_pshader->setFloat("iTime", time);

            //}

            start_drawing(m_pgpucontext);

            global_transform(m_pgpucontext);

            draw(m_pgpucontext);

            ///m_pobject->draw();

            //m_pcontext->render();

            m_pgpucontext->prepare_for_gpu_read();

            m_pgpucontext->m_pbuffer->gpu_read();

         }

#if !defined(__APPLE__)
         ::draw2d::matrix matrixOriginal;
         pgraphics->get(matrixOriginal);
         ::draw2d::matrix matrix(matrixOriginal);
         matrix.scale(1.0, -1.0);
         matrix.translate(0, m_rectangle.height());
         pgraphics->set(matrix);
#endif

         auto pimage = m_pgpucontext->m_pbuffer->m_pimage;

         if (::is_set(pimage))
         {

            //pimage->map();

            //pimage->fill_channel(255, ::color::e_channel_opacity);

         }

         image_source imagesource(m_pgpucontext->m_pbuffer->m_pimage);

         ::rectangle_f64 rectangleTarget(m_rectangle);

         image_drawing_options imagedrawingoptions(rectangleTarget);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

#if !defined(__APPLE__)

         pgraphics->set(matrixOriginal);

#endif

      }

      //_001OnDraw1Through3(pgraphics);


   }


   void render::start_drawing(context * pcontext)
   {


   }


   void render::global_transform(context * pcontext)
   {


   }


   void render::draw(context * pcontext)
   {



   }


   void render::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


} // namespace gpu



