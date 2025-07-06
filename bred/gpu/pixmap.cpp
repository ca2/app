// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "layer.h"
#include "renderer.h"
#include "pixmap.h"
#include "acme/exception/interface_only.h"


namespace gpu
{


   pixmap::pixmap()
   {

      //m_bClearColor = false;
      //m_bRenderTarget = false;
      //m_bDepthStencil = false;
      //m_bTransferDst = false;
      //m_bCpuRead = false;

   }


   pixmap::~pixmap()
   {

   }


   void pixmap::initialize_gpu_pixmap(::gpu::renderer* pgpurenderer, const ::int_size& size)
   {

      /*m_pgpurenderer = pgpurenderer;
      m_rectangleTarget = rectangleTarget;*/

      m_size = size;

   }


   ::int_size pixmap::size()
   {

      return m_size;

   }


   void pixmap::set_pixels(const void* data, int w, int h)
   {


   }


   void pixmap::bind_texture(::gpu::shader* pgpushader)
   {


   }


   void pixmap::unbind_texture(::gpu::shader* pgpushader)
   {


   }


   //void pixmap::merge_layers(::pointer_array < ::gpu::layer >* playera)
   //{

   //   //return;

   //   auto& layera = *playera;

   //   for (auto player : layera)
   //   {

   //      blend(player);

   //      break;

   //   }

   //}


   //void pixmap::blend(::gpu::layer* player)
   //{

   //   blend(player->pixmap());

   //}


   //void pixmap::blend(::gpu::pixmap* ptexture)
   //{

   //   m_pgpurenderer->blend(this, ptexture);

   //}


} // namespace gpu



