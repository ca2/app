// Created by camilo on 2025-06-12 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "renderer.h"
#include "render_target.h"
#include "texture.h"


namespace gpu
{


   render_target::render_target()
   {

      m_bInit = false;

   }


   render_target::~render_target()
   {


   }


   void render_target::initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
   {

      m_bInit = false;
      m_pgpurenderer = pgpurenderer;
      m_size = size;
      m_prendertargetOld = previous;

   }


   void render_target::init()
   {

      if (m_bInit)
      {

         return;

      }

      m_bInit = true;

      createImages();

   }


   void render_target::createImages()
   {

      auto iFrameCount = m_pgpurenderer->m_iFrameCountRequest;

      m_texturea.set_size(iFrameCount);

      for (auto& ptexture : m_texturea)
      {

         __defer_construct(ptexture);

         if (ptexture->size() != m_size && !m_size.is_empty())
         {

            ptexture->initialize_gpu_texture(m_pgpurenderer, m_size);

         }

      }

   }


   int render_target::get_frame_index()
   {

      return m_pgpurenderer->_default_get_frame_index();

   }


   texture * render_target::current_texture()
   {

      auto pgpucontext = m_pgpurenderer->m_pgpucontext;

      auto etype = pgpucontext->m_etype;

      int iFrameIndex;
      
      if (m_bBackBuffer)
      {

         iFrameIndex = m_pgpurenderer->_get_frame_index();

      }
      else
      {

         iFrameIndex = m_pgpurenderer->get_frame_index();

      }

      auto size = m_texturea.size();

      auto ptexture = m_texturea[iFrameIndex];

      return ptexture;

   }


   void render_target::on_before_begin_draw_frame(::draw2d_gpu::graphics* pgraphics)
   {


   }


   void render_target::on_after_end_draw_frame(::draw2d_gpu::graphics* pgraphics)
   {


   }

   
   void render_target::on_end_render(::gpu::frame* pgpurender)
   {



   }


} // namespace gpu



