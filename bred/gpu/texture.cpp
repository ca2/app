// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "renderer.h"
#include "texture.h"
#include "acme/exception/interface_only.h"


namespace gpu
{


   texture::texture()
   {

      m_bClearColor = false;
      m_bRenderTarget = false;
      m_bDepthStencil = false;
      m_bTransferDst = false;
      m_bCpuRead = false;

   }


   texture::~texture()
   {

   }


   void texture::initialize_gpu_texture(::gpu::renderer * pgpurenderer, const ::int_rectangle& rectangleTarget)
   {

      m_pgpurenderer = pgpurenderer;
      m_rectangleTarget = rectangleTarget;

   }


   ::int_size texture::size()
   {

      return m_rectangleTarget.size();

   }


   void texture::merge_layers(::pointer_array < ::gpu::layer >* playera)
   {

      //return;

      auto& layera = *playera;

      for (auto player : layera)
      {

         blend(player);

         break;

      }

   }


   void texture::blend(::gpu::layer* player)
   {

      blend(player->texture());

   }


   void texture::blend(::gpu::texture* ptexture)
   {

      m_pgpurenderer->blend(this, ptexture);

   }


} // namespace gpu



