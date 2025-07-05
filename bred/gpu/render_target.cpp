// Created by camilo on 2025-06-12 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "layer.h"
#include "renderer.h"
#include "render_state.h"
#include "render_target.h"
#include "texture.h"
#include "acme/platform/application.h"


namespace gpu
{


   render_target::render_target()
   {

      m_bRenderTargetInit = false;
      m_bBackBuffer = false;
      m_bWithDepth = false;

   }


   render_target::~render_target()
   {


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

      if (!m_bBackBuffer)
      {

         restart_frame_counter();

      }

      if (m_pgpurenderer->m_pgpucontext->m_escene == ::gpu::e_scene_3d)
      {

         m_bWithDepth = true;

      }

      on_init();

      set_ok_flag();

   }


   void render_target::restart_frame_counter()
   {

      if (m_pgpurenderer->m_pgpurendertarget->get_frame_count() > 1)
      {

         m_iCurrentFrame2 = -1;
         m_iFrameSerial2 = -1;

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

         assert(m_iFrameSerial2 >= 0
            && m_iCurrentFrame2 >= 0
            && m_pgpurenderer->m_prenderstate->m_estate != e_state_initial
            && "Cannot get frame index when frame not in progress");

         return (int)m_iCurrentFrame2;

      }
      else
      {

         return 0;

      }

   }


   int render_target::get_frame_count()
   {

      return (int)m_texturea.size();

   }





   void render_target::on_init()
   {

      createImages();

   }


   void render_target::createImages()
   {

      auto iFrameCount = m_pgpurenderer->m_iDefaultFrameCount;

      m_texturea.set_size(iFrameCount);

      for (auto& ptexture : m_texturea)
      {

         __defer_construct(ptexture);

         if (ptexture->size() != m_size && !m_size.is_empty())
         {

            ptexture->initialize_image_texture(m_pgpurenderer, m_size, m_bWithDepth);

         }

      }

   }


   int render_target::imageCount() 
   {
      
      return (int) m_texturea.size(); 
   
   }


   int render_target::width() 
   {
      
      return m_size.cx(); 
   
   }


   int render_target::height() 
   {
      
      return m_size.cy(); 
   
   }


   texture * render_target::current_texture()
   {

      if (m_pgpurenderer->m_pgpulayer)
      {

         return m_pgpurenderer->m_pgpulayer->source_texture();

      }

      auto pgpucontext = m_pgpurenderer->m_pgpucontext;

      auto etype = pgpucontext->m_etype;

      int iFrameIndex = get_frame_index();
      
      auto size = m_texturea.size();

      auto ptexture = m_texturea[iFrameIndex];

      return ptexture;

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


   void render_target::on_new_frame()
   {

      auto iFrameCount = get_frame_count();

      m_iFrameSerial2++;

      m_iCurrentFrame2 = (m_iCurrentFrame2 + 1) % iFrameCount;

   }


   bool render_target::is_starting_frame()const
   {

      return m_iFrameSerial2 == m_iCurrentFrame2;

   }

} // namespace gpu



