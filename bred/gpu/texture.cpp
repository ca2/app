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

   }


   texture::~texture()
   {

   }


   void texture::initialize_gpu_texture(::gpu::renderer * pgpurenderer, const ::int_size& size)
   {

      m_pgpurenderer = pgpurenderer;
      m_size = size;

   }


   void texture::merge_layers(::pointer_array < ::gpu::layer >* playera)
   {

      //return;

      auto& layera = *playera;

      for (auto player : layera)
      {

         blend(player->m_pgputexture, player->m_rectangleTarget);

      }

   }


   void texture::blend(::gpu::layer* player)
   {

      blend(player->m_pgputexture, player->m_rectangleTarget);

   }


   void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   {

      throw ::interface_only();

   }


} // namespace gpu



