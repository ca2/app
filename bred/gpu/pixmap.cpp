// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "layer.h"
#include "renderer.h"
#include "pixmap.h"
#include "frame.h"
#include "texture.h"
#include "texture_site.h"
#include "window_attachment.h"
#include "acme/exception/interface_only.h"


namespace gpu
{


   pixmap::pixmap()
   {

      //m_pgputexture = nullptr;
      //m_bClearColor = false;
      //m_bRenderTarget = false;
      //m_bDepthStencil = false;
      //m_bTransferDst = false;
      //m_bCpuRead = false;

   }


   pixmap::~pixmap()
   {

   }


   void pixmap::initialize_gpu_pixmap(::gpu::texture* pgputexture, const ::i32_rectangle& rectangle)
   {

      defer_construct_newø(m_pgputexturesite);

      m_pgputexturesite->m_pgputextureSite = pgputexture;

      m_rectangle = rectangle;

      on_initialize_gpu_pixmap();

   }


   void pixmap::on_initialize_gpu_pixmap()
   {



   }


   ::i32_size pixmap::size()
   {

      return m_rectangle.size();

   }


   void pixmap::set_pixels(const void* pdata)
   {
      
      if(::is_null(pdata))
      {
         
         throw ::exception(error_bad_argument);
         
      }

      auto pgputexture = m_pgputexturesite->gpu_texture();

      auto bDeferredWrite = pgputexture->m_bWritesPixelsDeferred;

      m_bPixelsReadyForSampling = false;

      try
      {

         pgputexture->set_pixels(false, m_rectangle, pdata);

      }
      catch (...)
      {

         throw;

      }

      if (bDeferredWrite)
      {

         auto pgpuwindowattachment =
            ::gpu::window_attachment::get(pgputexture->m_pgpucontext);

         auto pframe = pgpuwindowattachment
            ? pgpuwindowattachment->current_frame()
            : nullptr;

         if (pframe)
         {

            ::pointer<::gpu::pixmap> ppixmap = this;

            // texture::write_pixels registered its upload callback before
            // returning.  Appending this callback therefore marks this exact
            // atlas region ready only after the upload submission has waited.
            pframe->post_on_after_end_frame(
               [ppixmap]()
               {

                  ppixmap->m_bPixelsReadyForSampling = true;

               });

         }
         else
         {

            m_bPixelsReadyForSampling = true;

         }

      }
      else
      {

         m_bPixelsReadyForSampling = true;

      }

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


   //void pixmap::blend(::gpu::layer * pgpulayer)
   //{

   //   blend(player->pixmap());

   //}


   //void pixmap::blend(::gpu::pixmap* ptexture)
   //{

   //   m_pgpurenderer->blend(this, ptexture);

   //}


} // namespace gpu



