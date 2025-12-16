// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "pixmap.h"
#include "render_target.h"
#include "renderer.h"
#include "texture.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/context.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"


namespace gpu
{


   texture::texture()
   {

      m_iAtlasX = 0;
      m_iAtlasY = 0;
      m_iAtlasCurrentRowHeight = 0;
      //m_etype = e_type_none;
      m_bClearColor = false;
      //m_bRenderTarget = false;
      //m_bTransferDst = false;
      //m_bTransferSrc = false;
      //m = false;
      //m_flags.m_bWithDepth = false;
      //m_bShaderResourceView = false;
      //m_iLayerCount = 1;
      //m_iMipCount = 1;
      m_iIndex = -1;
      //m_bRedGreen = false;
      //m_bFloat = false;
      m_iCurrentMip = -1;
      m_iCurrentLayer = -1;

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
                                     enum_texture etexture)
   {


         }



   void texture::initialize_texture(::gpu::renderer * pgpurenderer,
      const texture_attributes & textureattributes,
      const texture_flags & textureflags,
      const texture_data & texturedata
      )
   {

      //::gpu::context_lock contextlock(pgpurenderer->m_pgpucontext);

      m_textureflags = textureflags;

      if (m_pgpurenderer != pgpurenderer || m_textureattributes != textureattributes)
      {

         m_pgpurenderer = pgpurenderer;

         m_textureattributes = textureattributes;

         _create_texture(texturedata);

      }
      else if (texturedata.is_set())
      {

         _set_data(texturedata);

      }

      if (m_textureflags.m_bWithDepth)
      {

         create_depth_resources();

      }

      if (m_textureflags.m_bRenderTarget)
      {

         create_render_target();

      }

      if (m_textureflags.m_bShaderResource)
      {

         create_shader_resource_view();

      }

   }


   //void texture::initialize_mipmap_cubemap_texture(::gpu::renderer *pgpurenderer, const ::int_rectangle &rectangleTarget,
   //                                       int iMipCount, bool bRenderTarget, bool bShaderResource)
   //{

   //   ::gpu::texture_attributes textureattributes(rectangleTarget, 8, 4, 0, e_texture_cube_map, 6, iMipCount);

   //   ::gpu::texture_flags textureflags(false, bRenderTarget, bShaderResource);

   //   initialize_texture(pgpurenderer, textureattributes, textureflags);

   //}


   void texture::initialize_depth_texture(::gpu::renderer* pgpurenderer, const ::int_rectangle& rectangleTarget)
   {

      ::gpu::texture_attributes textureattributes(rectangleTarget, 16, 1, 1, e_texture_depth);

      initialize_texture(pgpurenderer, textureattributes);
      // m_etype = e_type_depth;
      // m_pgpurenderer = pgpurenderer;
      // m_textureattributes.m_rectangleTarget = rectangleTarget;

   }


   void texture::_create_texture(const texture_data & texturedata)
   {

      throw ::interface_only();

   }


   void texture::_set_data(const texture_data &texturedata) 
   {
      
      throw ::interface_only(); 
   
   }


   ::int_rectangle texture::rectangle() const
   {

      return m_textureattributes.m_rectangleTarget;

   }



   ::int_size texture::size() const
   {

      return m_textureattributes.m_rectangleTarget.size();

   }


   int texture::width() const
   {

      return m_textureattributes.m_rectangleTarget.width();

   }


   int texture::height() const
   {

      return m_textureattributes.m_rectangleTarget.height();

   }


   int texture::mip_count() const
   {

      if (m_textureattributes.m_iMipCount < -1)
      {

         throw ::exception(error_wrong_state);

      }
      else if(m_textureattributes.m_iMipCount == -1)
      {
         
         return max_mip_count();

      }
      else if (m_textureattributes.m_iMipCount == 0)
      {

         return 1;

      }
      else if (m_textureattributes.m_iMipCount <= max_mip_count())
      {
         
         return m_textureattributes.m_iMipCount;

      }
      else
      {

         throw ::exception(error_wrong_state);

      }


   }


   int texture::max_mip_count() const
   {

      return ::std::floor(::std::log2(this->size().maximum()));

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
      
      auto iMipCount = iMip;

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

      return this->render_target_view_index(m_iCurrentLayer, m_iCurrentMip);

   }


   int texture::layer_count() const
   {

      if (m_textureattributes.m_etexture == ::gpu::e_texture_cube_map)
      {

         return 6;

      }
      else if (m_textureattributes.m_iLayerCount <= 1)
      {

         return 1;

      }
      else
      {

         return m_textureattributes.m_iLayerCount;

      }
   }
   

   void texture::set_state(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_texture_state etexturestate)
   {

      m_etexturestate = etexturestate;

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


   void texture::initialize_texture_from_image(
      ::gpu::renderer* pgpurenderer, const ::pointer_array < ::image::image >& imagea, enum_texture etexture)
   {

      auto rectangle = imagea.first()->rectangle();

      ::gpu::texture_attributes textureattributes(rectangle, 8, 4, 0, etexture,
         etexture == e_texture_cube_map ? 6 : 1);

      if (imagea.has_element())
      {

         if (etexture == e_texture_cube_map)
         {

            defer_throw_if_cube_map_images_are_not_ok(imagea);

         }

      }

      initialize_texture(pgpurenderer, textureattributes, {}, &imagea);

      if (is_ok())
      {

         auto pcommandbuffer = pgpurenderer->m_pgpucontext->beginSingleTimeCommands(pgpurenderer->m_pgpucontext->m_pgpudevice->transfer_queue());

         this->set_state(pcommandbuffer, ::gpu::e_texture_state_shader_read);

         pgpurenderer->m_pgpucontext->endSingleTimeCommands(pcommandbuffer);

      }

   }


   ::pointer < ::gpu::pixmap > texture::create_gpu_pixmap(const ::int_size& size)
   {

      if (m_iAtlasX >= m_textureattributes.m_rectangleTarget.width() ||
         m_iAtlasY >= m_textureattributes.m_rectangleTarget.height())
      {

         return nullptr;

      }

      int iAtlasX = m_iAtlasX;
      int iAtlasY = m_iAtlasY;
      int iAtlasH = m_iAtlasCurrentRowHeight;

      if (size.cx > m_textureattributes.m_rectangleTarget.width() - iAtlasX)
      {

         if (iAtlasX <= 0)
         {

            throw ::exception(error_wrong_state, "pixmap is wider than texture atlas");

         }

         iAtlasX = 0;
         iAtlasY += iAtlasH;
         iAtlasH = 0;

      }

      if (size.cy > m_textureattributes.m_rectangleTarget.height() - iAtlasY)
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


   //void texture::merge_layers(::pointer_array < ::gpu::layer >* playera)
   //{

   //   //return;

   //   auto& layera = *playera;

   //   for (auto player : layera)
   //   {

   //      blend(player);

   //      break;

   //   }

   //}


   //void texture::blend(::gpu::layer* player)
   //{

   //   blend(player->texture());

   //}


   //void texture::blend(::gpu::texture* ptexture)
   //{

   //   m_pgpurenderer->blend(this, ptexture);

   //}


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

      if (m_textureattributes.m_etexture & ::gpu::e_texture_depth)
      {

         return this;

      }

      if (!m_textureflags.m_bWithDepth)
      {

         return nullptr;

      }

      if (m_ptextureDepth)
      {

         return m_ptextureDepth;

      }

      ødefer_construct(m_ptextureDepth);

      m_ptextureDepth->initialize_depth_texture(m_pgpurenderer, m_textureattributes.m_rectangleTarget);

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


   void texture::set_current_mip(int iCurrentMip)
   {

      m_iCurrentMip = iCurrentMip;

   }


   int texture::mip_width()
   {

      if (m_sizeMip.width() < 0)
      {

         return (int)((double)this->width() * ::pow((double)0.5, (double)maximum(m_iCurrentMip, 0)));

      }
           
      return m_sizeMip.width();

   }


   int texture::mip_height() 
   {
      
      if (m_sizeMip.height() < 0)
      {

         return  (int)((double)this->height() * ::pow((double)0.5, (double)maximum(m_iCurrentMip, 0)));


      }
      
      return m_sizeMip.height();
   
   }


   void texture::set_cube_face(int iFace, ::gpu::shader *pgpushader)
   {

      m_iCurrentLayer = iFace;

   }


   void texture::generate_mipmap(::gpu::command_buffer * pgpucommandbuffer)
   {


   }


} // namespace gpu



