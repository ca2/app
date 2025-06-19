// Created by camilo on 2025-06-12 21:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "layer.h"
#include "renderer.h"
#include "texture.h"


namespace gpu
{


   layer::layer()
   {


   }


   layer::~layer()
   {


   }


   void layer::initialize_gpu_layer(::gpu::renderer * pgpurenderer)
   {

      m_pgpurenderer = pgpurenderer;

      m_pgpurenderer->defer_update_renderer();

   }


   //void layer::set_target_texture(texture* ptextureTarget)
   //{

   //   target_texture() = ptextureTarget;

   //}


   void layer::take_snapshot()
   {

      m_pgpurenderer->take_snapshot(this);

   }


   ::pointer < texture >& layer::texture()
   {

      int iFrameIndex = m_pgpurenderer->_get_frame_index();

      auto & ptexture = m_gputexturea.element_at_grow(iFrameIndex);

      m_pgpurenderer->__defer_construct(ptexture);

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      ptexture->initialize_gpu_texture(m_pgpurenderer, rectangle);

      return ptexture;

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


