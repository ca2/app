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


   void layer::initialize_gpu_layer(renderer * pgpurenderer, const ::int_rectangle& rectangleTarget)
   {

      m_pgpurenderer = pgpurenderer;

      __defer_construct(m_pgputextureTarget);

      m_pgputextureTarget->initialize_gpu_texture(pgpurenderer, rectangleTarget);

      m_pgpurenderer->defer_update_renderer();

   }


   void layer::set_target_texture(texture* ptextureTarget)
   {

      m_pgputextureTarget = ptextureTarget;

   }


   void layer::take_snapshot()
   {

      m_pgpurenderer->take_snapshot(this);

   }


} // namespace gpu


