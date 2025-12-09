// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "pixmap.h"
#include "render_target.h"
#include "renderer.h"
#include "texture.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/context.h"
#include "bred/gpu/context_lock.h"


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
      m_bShaderResourceView = false;
      m_iLayerCount = 1;
      m_iMipCount = 1;
      m_iIndex = -1;
      m_bRedGreen = false;
      m_bFloat = false;
      m_iCurrentMip = 0;
      m_iCurrentFace = 0;

   }


   texture::~texture()
   {

   }



   void texture::initialize_hdr_texture_on_memory(::gpu::renderer *prenderer, const ::block & block)
   {


   }


   void texture::initialize_with_image_data(::gpu::renderer * pgpurenderer,
                                              const ::int_rectangle & rectangleTarget,
                                     int numChannels, bool bSrgb, const void * pdata,
                                     enum_type etype)
   {


         }



   void texture::initialize_texture(::gpu::renderer * pgpurenderer,
      const ::int_rectangle& rectangleTarget, bool bWithDepth,
      const ::pointer_array < ::image::image > *pimagea, enum_type etype)
   {

      ///::gpu::context_lock contextlock(pgpurenderer->m_pgpucontext);

      if (m_pgpurenderer != pgpurenderer
         || rectangleTarget != m_rectangleTarget
         || etype != m_etype)
      {

         m_etype = etype;
         m_pgpurenderer = pgpurenderer;
         m_rectangleTarget = rectangleTarget;

         create_texture(pimagea);

      }

      m_bWithDepth = bWithDepth;

      if (bWithDepth)
      {

         create_depth_resources();

      }

   }


   void texture::initialize_mipmap_cubemap_texture(::gpu::renderer *pgpurenderer, const ::int_rectangle &rectangleTarget,
                                          int iMipCount, bool bRenderTarget, bool bShaderResourceView)
   {

      if (m_pgpurenderer != pgpurenderer
         || m_etype != e_type_cube_map
         || m_rectangleTarget != rectangleTarget
         || m_iMipCount != iMipCount)
      {

         m_pgpurenderer = pgpurenderer;
         m_etype = e_type_cube_map;
         m_rectangleTarget = rectangleTarget;
         m_iMipCount = iMipCount;

         create_texture(nullptr);

      }

      m_bRenderTarget = bRenderTarget;

      if (bRenderTarget)
      {

         create_render_target();

      }

      m_bShaderResourceView = bShaderResourceView;

      if (bShaderResourceView)
      {

         create_shader_resource_view();

      }

   }


   void texture::initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget)
   {

      m_etype = e_type_depth;
      m_pgpurenderer = pgpurenderer;
      m_rectangleTarget = rectangleTarget;

   }


   void texture::create_texture(const ::pointer_array < ::image::image > *pimagea)
   {

      throw ::interface_only();

   }
      


   ::int_size texture::size() const
   {

      return m_rectangleTarget.size();

   }


   int texture::width() const
   {

      return m_rectangleTarget.width();

   }


   int texture::height() const
   {

      return m_rectangleTarget.height();

   }


   // Helper: compute integer mip size (never below 1)
   int texture::mip_width_for_mip(int baseWidth, int level) const
   {
      
      return ::maximum(1, baseWidth >> level);

   }

   
   int texture::mip_height_for_mip(int baseHeight, int level) const
   {
      
      return ::maximum(1, baseHeight >> level);

   }


   int texture::render_target_view_index(int iFace, int iMip) const
   {
      
      auto iMipCount = m_iMipCount;

      if (iMip < 0 || iMip >= iMipCount)
      {

         throw ::exception(error_wrong_state);

      }

      if (iFace < 0 || iFace >= 6)
      {

         throw ::exception(error_wrong_state);

      }

      return iFace * iMipCount + iMip;

   }


   int texture::current_render_target_view_index() const
   {

      return this->render_target_view_index(m_iCurrentFace, m_iCurrentMip);

   }
   
   
   int texture::mip_width() const
   {

      return this->mip_width_for_mip(this->width(), m_iCurrentMip);

   }


   int texture::mip_height() const 
   {
      
      return this->mip_height_for_mip(this->height(), m_iCurrentMip); 
   
   }


   void texture::initialize_texture_from_file_path(::gpu::renderer* pgpurenderer, const ::file::path& path, bool bIsSrgb)
   {

      auto pimage = image()->path_image(path);

      ::pointer_array < ::image::image > imagea({ pimage });

      initialize_texture_from_image(pgpurenderer, imagea);

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


   void texture::initialize_texture_from_image(::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image >& imagea, enum_type etype)
   {

      auto r = imagea.first()->rectangle();

      if (imagea.has_element())
      {

         if (etype == e_type_cube_map)
         {

            defer_throw_if_cube_map_images_are_not_ok(imagea);

         }

      }

      initialize_texture(pgpurenderer, r, false, &imagea, etype);

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

      if (size.cx > m_rectangleTarget.width() - iAtlasX)
      {

         if (iAtlasX <= 0)
         {

            throw ::exception(error_wrong_state, "pixmap is wider than texture atlas");

         }

         iAtlasX = 0;
         iAtlasY += iAtlasH;
         iAtlasH = 0;

      }

      if (size.cy > m_rectangleTarget.height() - iAtlasY)
      {

         if (iAtlasY <= 0)
         {

            throw ::exception(error_wrong_state, "pixmap is higher than texture height");

         }

         // this texture atlas would be full with this new image

         return nullptr;

      }

      iAtlasH = maximum(iAtlasH, size.cy);

      m_iAtlasX = iAtlasX;
      m_iAtlasY = iAtlasY;
      m_iAtlasCurrentRowHeight = iAtlasH;

      auto ppixmap = øcreate<::gpu::pixmap>();

      ppixmap->initialize_gpu_pixmap(this, 
         {iAtlasX, iAtlasY,
         iAtlasX + size.cx,
         iAtlasY + size.cy});

      m_iAtlasX += size.cx;
      m_iAtlasCurrentRowHeight = maximum(m_iAtlasCurrentRowHeight, size.cy);

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


   void texture::create_shader_resource_view() 
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


   void texture::set_cube_face(int iFace)
   {


   }


   void texture::generate_mipmap()
   {


   }


} // namespace gpu



