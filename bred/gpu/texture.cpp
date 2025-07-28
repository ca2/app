// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "render_target.h"
#include "renderer.h"
#include "texture.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/context.h"


namespace gpu
{


   texture::texture()
   {

      m_etype = e_type_none;
      m_bClearColor = false;
      m_bRenderTarget = false;
      m_bTransferDst = false;
      m_bTransferSrc = false;
      m_bCpuRead = false;
      m_bWithDepth = false;

   }


   texture::~texture()
   {

   }


   void texture::initialize_image_texture(::gpu::renderer * pgpurenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth, const ::pointer_array < ::image::image >& imagea, enum_type etype)
   {

      m_etype = etype;
      m_pgpurenderer = pgpurenderer;
      //m_pgpurendertarget = pgpurenderer->m_pgpurendertarget;
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


   int texture::width()
   {

      return m_rectangleTarget.width();

   }


   int texture::height()
   {

      return m_rectangleTarget.height();

   }


   void texture::initialize_image_texture(::gpu::renderer* pgpurenderer, const ::file::path& path)
   {

      auto pimage = image()->path_image(path);

      ::pointer_array < ::image::image > imagea({ pimage });

      initialize_image_texture(pgpurenderer, imagea);

   }


   void texture::initialize_image_texture(::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image >& imagea, enum_type etype)
   {

      auto r = imagea.first()->rectangle();

      initialize_image_texture(pgpurenderer, r, false, imagea, etype);

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

   ::string texture::texture_type()
   {

      return m_strTextureType;

   }

} // namespace gpu



