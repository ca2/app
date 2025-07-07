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

      m_etype = e_type_none;
      m_bClearColor = false;
      m_bRenderTarget = false;
      m_bTransferDst = false;
      m_bCpuRead = false;
      m_bWithDepth = false;

   }


   texture::~texture()
   {

   }


   void texture::initialize_image_texture(::gpu::renderer * pgpurenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth)
   {

      m_etype = e_type_image;
      m_pgpurenderer = pgpurenderer;
      m_rectangleTarget = rectangleTarget;
      m_bWithDepth = bWithDepth;

   }


   void texture::initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget)
   {

      m_etype = e_type_depth;
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


   void texture::create_render_target()
   {


   }


   void texture::create_depth_resources()
   {


   }


   void texture::bind_render_target()
   {


   }


   texture* texture::get_depth_texture()
   {

      if (m_etype & ::gpu::texture::e_type_depth)
      {

         return this;

      }

      if (!m_bWithDepth)
      {

         return nullptr;

      }

      if (m_ptextureDepth)
      {

         return m_ptextureDepth;

      }

      __defer_construct(m_ptextureDepth);

      m_ptextureDepth->initialize_depth_texture(m_pgpurenderer, m_rectangleTarget);

      return m_ptextureDepth;

   }



} // namespace gpu



