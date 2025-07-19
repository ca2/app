// Created by camilo on 2025-06-12 21:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"
#include "texture.h"


namespace gpu
{


   layer::layer()
   {


   }


   layer::~layer()
   {


   }


   void layer::initialize_gpu_layer(::gpu::renderer * pgpurenderer, int iFrameIndex, int iLayerIndex)
   {

      m_pgpurenderer = pgpurenderer;

      m_iFrameIndex = iFrameIndex;

      m_iLayerIndex = iLayerIndex;

      m_pgpurenderer->defer_update_renderer();

   }


   //void layer::set_target_texture(texture* ptextureTarget)
   //{

   //   target_texture() = ptextureTarget;

   //}


   void layer::layer_start()
   {

      m_pgpurenderer->on_start_layer(this);

   }


   void layer::layer_end()
   {

      m_pgpurenderer->on_end_layer(this);

   }


   ::pointer < texture >& layer::texture()
   {

      int iFrameIndex = m_pgpurenderer->m_pgpurendertarget->get_frame_index();

      auto & ptexture = m_texturea.element_at_grow(iFrameIndex);

      m_pgpurenderer->__defer_construct(ptexture);

      ptexture->m_bRenderTarget = true;

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      ptexture->m_bTransferDst = true;

      ptexture->initialize_image_texture(m_pgpurenderer, rectangle, false);

      return ptexture;

   }


   ::pointer < texture >& layer::source_texture()
   {

      int iFrameIndex = m_pgpurenderer->m_pgpurendertarget->get_frame_index();

      auto& ptextureSource = m_textureaSource.element_at_grow(iFrameIndex);

      m_pgpurenderer->__defer_construct(ptextureSource);

      ptextureSource->m_bRenderTarget = true;

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      auto escene = m_pgpurenderer->m_pgpucontext->m_escene;

      bool bWithDepth = escene == ::gpu::e_scene_3d;

      ptextureSource->initialize_image_texture(m_pgpurenderer, rectangle, bWithDepth);

      return ptextureSource;

   }


   //::pointer < texture >& layer::target_texture()
   //{
   //   
   //   int iTargetFrameIndex = m_pgpurendererTarget->_get_frame_index();
   //   
   //   auto & ptextureTarget = m_gputextureaTarget[iTargetFrameIndex];

   //   m_pgpurendererTarget->__defer_construct(ptextureTarget);

   //   auto rectangleTarget = m_pgpurendererTarget->m_pgpucontext->rectangle();

   //   ptextureTarget->initialize_gpu_texture(m_pgpurendererTarget, rectangleTarget);

   //   return ptextureTarget;

   //}


} // namespace gpu


