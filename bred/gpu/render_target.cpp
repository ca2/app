// Created by camilo on 2025-06-12 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "frame.h"
#include "layer.h"
#include "renderer.h"
#include "render_state.h"
#include "render_target.h"
#include "texture.h"
#include "acme/platform/application.h"


#include <assert.h>


namespace gpu
{


   interlocked_count g_iGpuRenderTarget;


   render_target::render_target()
   {

      m_iGpuRenderTarget = ++g_iGpuRenderTarget;

      m_bRenderTargetInit = false;
      m_bBackBuffer = false;
      m_bWithDepth = false;

   }


   render_target::~render_target()
   {


   }


   ::pointer_array < ::gpu::texture >* render_target::texturea()
   {

      return m_ptexturea;

   }


   ::pointer_array < ::gpu::texture >* render_target::depth_texturea()
   {

      return m_ptextureaDepth;

   }


   void render_target::initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
   {

      set_fail_flag();
      m_bRenderTargetInit = false;
      m_pgpurenderer = pgpurenderer;
      m_size = size;
      m_prendertargetOld = previous;

   }


   void render_target::init()
   {

      if (m_size.is_empty())
      {

         return;

      }

      if (m_bRenderTargetInit)
      {

         return;

      }

      m_bRenderTargetInit = true;

      if (!m_ptexturea)
      {

         create_images();

      }

      //if (!m_bBackBuffer)
      //{

      //   restart_frame_counter();

      //}

      if (m_pgpurenderer->m_pgpucontext->m_escene == ::gpu::e_scene_3d)
      {

         m_bWithDepth = true;

      }

      on_init();

      set_ok_flag();

   }



   //void render_target::create_images()
   //{

   //   if (m_ptexturea && m_ptexturea->has_element())
   //   {

   //      return;

   //   }

   //   ødefer_construct_new(m_ptexturea);

   //   m_ptexturea->set_size(m_pgpurenderer->m_iDefaultFrameCount);

   //   auto pcontext = m_pgpurenderer->m_pgpucontext;

   //   for (int i = 0; i < m_ptexturea->size(); i++)
   //   {

   //      auto& ptexture = m_ptexturea->element_at(i);

   //      ødefer_construct(ptexture);

   //      ptexture->initialize_image_texture(
   //         m_pgpurenderer,
   //         pcontext->m_rectangle, false);

   //   }


   //}


   void render_target::restart_frame_counter()
   {

      if (m_pgpurenderer->m_pgpurendertarget->get_frame_count() > 1)
      {

         m_pgpurenderer->m_pgpucontext->m_pgpudevice->restart_frame_counter();

         m_pgpurenderer->m_prenderstate->on_happening(e_happening_reset_frame_counter);

      }

   }


   int render_target::get_frame_index()
   {

      if (m_pgpurenderer->m_pgpucontext->m_iOverrideFrame >= 0)
      {

         return m_pgpurenderer->m_pgpucontext->m_iOverrideFrame;

      }

      if (m_pgpurenderer->m_pgpurendertarget->get_frame_count() > 1)
      {

         auto iFrameSerial2 = m_pgpurenderer->m_pgpucontext->m_pgpudevice->m_iFrameSerial2;

         auto iCurrentFrame2 = m_pgpurenderer->m_pgpucontext->m_pgpudevice->m_iCurrentFrame2;

         auto estate = m_pgpurenderer->m_prenderstate->m_estate;

         assert(
            iFrameSerial2 >= 0 
            && iCurrentFrame2 >= 0 
            && estate != e_state_initial
            && "Cannot get frame index when frame not in progress");

         return (int)m_pgpurenderer->m_pgpucontext->m_pgpudevice->m_iCurrentFrame2;

      }
      else
      {

         return 0;

      }

   }


   int render_target::get_frame_count()
   {

      return (int)m_ptexturea->size();

   }





   void render_target::on_init()
   {

      create_images();

   }


   void render_target::on_resize(const ::int_size& size)
   {

      if (m_size == size)
      {

         return;

      }

      m_size = size;

      create_images();

   }


   void render_target::create_images()
   {

      auto iFrameCount = m_pgpurenderer->m_iDefaultFrameCount;

      ødefer_construct_new(m_ptexturea);

      m_ptexturea->set_size(iFrameCount);

      auto& texturea = *this->texturea();

      for (auto& ptexture : texturea)
      {

         ødefer_construct(ptexture);

         if (ptexture->size() != m_size && !m_size.is_empty())
         {

            on_create_render_target_texture(ptexture);

            //ptexture->m_pgpurendertarget = this;

            ptexture->initialize_texture(m_pgpurenderer, m_size, m_bWithDepth);

         }

      }

   }


   void render_target::on_create_render_target_texture(::gpu::texture* ptexture)
   {

      ptexture->m_bRenderTarget = true;

   }


   int render_target::imageCount() 
   {
      
      return (int) m_ptexturea->size(); 
   
   }


   int render_target::width() 
   {
      
      return m_size.cx; 
   
   }


   int render_target::height() 
   {
      
      return m_size.cy; 
   
   }


   texture * render_target::current_texture(::gpu::frame* pgpuframe)
   {

      if (::is_null(pgpuframe))
      {

         return nullptr;

      }

      if (pgpuframe->m_pgpulayer)
      {

         return pgpuframe->m_pgpulayer->source_texture();

      }

      auto pgpucontext = m_pgpurenderer->m_pgpucontext;

      auto etype = pgpucontext->m_etype;

      int iFrameIndex = get_frame_index();
      
      auto size = m_ptexturea->size();

      auto ptexture = m_ptexturea->element_at(iFrameIndex);

      return ptexture;

   }


   texture* render_target::current_depth_texture(::gpu::frame* pgpuframe)
   {

      if (pgpuframe->m_pgpulayer)
      {

         ::cast < texture > ptexture = pgpuframe->m_pgpulayer->source_texture();

         if (!ptexture)
         {

            throw ::exception(error_wrong_state, "No source texture in layer");

         }

         auto ptextureDepth = ptexture->get_depth_texture();

         if(!ptextureDepth)
         {
          
            throw ::exception(error_wrong_state, "No depth texture in source texture");

         }

         return ptextureDepth;

      }

      auto pgpucontext = m_pgpurenderer->m_pgpucontext;

      auto etype = pgpucontext->m_etype;

      int iFrameIndex = get_frame_index();

      auto size = m_ptexturea->size();

      ::cast < texture > ptexture = m_ptexturea->element_at(iFrameIndex);

      if (!ptexture)
      {

         throw ::exception(error_wrong_state, "No source texture in layer");

      }

      auto ptextureDepth = ptexture->get_depth_texture();

      //if (!ptextureDepth)
      //{

      //   throw ::exception(error_wrong_state, "No depth texture in source texture");

      //}

      return ptextureDepth;

   }


   void render_target::on_before_begin_draw_frame(::gpu::graphics* pgraphics)
   {


   }


   void render_target::on_after_end_draw_frame(::gpu::graphics* pgraphics)
   {


   }




   //void render_target::on_end_render(::gpu::frame* pgpurender)
   //{



   //}


   //void render_target::on_new_frame()
   //{

   //   auto iFrameCount = get_frame_count();

   //   m_iFrameSerial2++;

   //   m_iCurrentFrame2 = (m_iCurrentFrame2 + 1) % iFrameCount;

   //}


   bool render_target::is_starting_frame()const
   {

      return m_pgpurenderer->m_pgpucontext->m_pgpudevice->m_iFrameSerial2 
         == m_pgpurenderer->m_pgpucontext->m_pgpudevice->m_iCurrentFrame2;

   }


} // namespace gpu



