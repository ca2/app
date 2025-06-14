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
      m_rectangleTarget = rectangleTarget;

      m_pgpurenderer->defer_update_renderer();

   }


   void layer::set_texture(texture* ptexture)
   {

      m_pgputexture = ptexture;

   }


   void layer::take_snapshot()
   {

      m_pgpurenderer->take_snapshot(this, m_rectangleTarget);

   }


} // namespace gpu


