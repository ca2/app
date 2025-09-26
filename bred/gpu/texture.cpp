// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "pixmap.h"
#include "render_target.h"
#include "renderer.h"
#include "texture.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/context.h"


namespace gpu
{


   texture::texture()
   {

      m_iAtlasX = 0;
      m_iAtlasY = 0;
      m_iAtlasCurrentRowHeight = 0;
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

   
   void texture::defer_throw_if_cube_map_images_are_not_ok(const ::pointer_array < ::image::image >& imagea)
   {

      if (imagea.size() != 6)
      {

         throw ::exception(error_failed, "Cube map texture must have exactly 6 images");

      }

      auto pimageFirst = imagea.first();

      if (pimageFirst->is_empty())
      {

         throw ::exception(error_failed, "Cube map texture cannot be empty");

      }

      if (pimageFirst->width() != pimageFirst->height())
      {

         throw ::exception(error_failed, "Cube map texture images must be square");

      }

      for (auto& pimage : imagea)
      {
         
         if (pimage != pimageFirst)
         {

            if (pimage->size() != pimageFirst->size())
            {
               
               throw ::exception(error_failed, "Cube map texture images must have the same dimensions");

            }

         }

      }

   }

   void texture::initialize_image_texture(::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image >& imagea, enum_type etype)
   {

      auto r = imagea.first()->rectangle();

      if (imagea.has_element())
      {

         if (etype == e_type_cube_map)
         {

            defer_throw_if_cube_map_images_are_not_ok(imagea);

         }

      }

      initialize_image_texture(pgpurenderer, r, false, imagea, etype);

   }


   ::pointer < ::gpu::pixmap > texture::create_gpu_pixmap(const ::int_size& size)
   {

      if (m_iAtlasX >= m_rectangleTarget.width() ||
         m_iAtlasY >= m_rectangleTarget.height())
      {

         return nullptr;

      }

      int iAtlasX = m_iAtlasX;
      int iAtlasY = m_iAtlasY;
      int iAtlasH = m_iAtlasCurrentRowHeight;

      if (size.cx() > m_rectangleTarget.width() - iAtlasX)
      {

         if (iAtlasX <= 0)
         {

            throw ::exception(error_wrong_state, "pixmap is wider than texture atlas");

         }

         iAtlasX = 0;
         iAtlasY += iAtlasH;
         iAtlasH = 0;

      }

      if (size.cy() > m_rectangleTarget.height() - iAtlasY)
      {

         if (iAtlasY <= 0)
         {

            throw ::exception(error_wrong_state, "pixmap is higher than texture height");

         }

         // this texture atlas would be full with this new image

         return nullptr;

      }

      iAtlasH = maximum(iAtlasH, size.cy());

      m_iAtlasX = iAtlasX;
      m_iAtlasY = iAtlasY;
      m_iAtlasCurrentRowHeight = iAtlasH;

      auto ppixmap = øcreate<::gpu::pixmap>();

      ppixmap->initialize_gpu_pixmap(this, 
         {iAtlasX, iAtlasY,
         iAtlasX + size.cx(),
         iAtlasY + size.cy()});

      m_iAtlasX += size.cx();
      m_iAtlasCurrentRowHeight = maximum(m_iAtlasCurrentRowHeight, size.cy());

      return ppixmap;

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

      ødefer_construct(m_ptextureDepth);

      m_ptextureDepth->initialize_depth_texture(m_pgpurenderer, m_rectangleTarget);

      return m_ptextureDepth;

   }

   ::string texture::texture_type()
   {

      return m_strTextureType;

   }


   void texture::set_pixels(const ::int_rectangle& rectangle, const void* data)
   {


   }


   bool texture::is_in_shader_sampling_state()
   {

      return true;

   }


} // namespace gpu



