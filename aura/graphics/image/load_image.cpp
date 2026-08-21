// Created by camilo on 2021-08-24 23:41 <3ThomasBS_!!
#include "platform.h"
#include "load_image.h"
#include "context.h"
#include "acme/graphics/image/frame_array.h"


namespace image
{


   load_image::load_image()
   {


   }


   load_image::~load_image()
   {


   }


   void load_image::initialize_load_image(::image::image_context * pimagecontext, ::pixmap * ppixmapCallback)
   {

      auto ppixmap = ::as_pointer(ppixmapCallback);

      m_loadoptions.functionLoaded = [ppixmap](::image::load_image * ploadimage)
      {

         if (ploadimage->is_ok())
         {

            auto ppixmapLoad = ploadimage->m_pimageframearray->get_pixmap();

            if (ppixmapLoad)
            {

               ppixmap->create_as_descriptor(ppixmapLoad->m_sizeRaw, DEFAULT_CREATE_IMAGE_FLAG, ppixmapLoad->m_iScan);

               ppixmap->m_size = ppixmapLoad->m_size;

               ppixmap->copy_from(ppixmapLoad);

               ppixmap->m_eflagElement = ::e_flag_success;

               ppixmap->m_estatus = ::success;

            }

         }

      };

      m_pimagecontext = pimagecontext;

   }


   void load_image::initialize_load_image(::image::image_context* pimagecontext)
   {

      m_pimagecontext = pimagecontext;

   }


   pixmap * load_image::get_pixmap()
   {

      defer_construct_newø(m_pimageframearray);

      defer_construct_newø(m_pimageframearray->m_ppixmap);

      return m_pimageframearray->m_ppixmap;

   }


   pixmap * load_image::get_pixmap(const ::i32_size & size, ::i32 iScan)
   {

      auto ppixmap = get_pixmap();

      ppixmap->create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

      return ppixmap;

   }


   pixmap * load_image::get_pixmap_from_data(const ::i32_size & size, const image32_t *pimage32, ::i32 iScan)
   {

      auto ppixmap = get_pixmap();

      ppixmap->create_from_data(size, pimage32, iScan, DEFAULT_CREATE_IMAGE_FLAG);

      //on_image_loaded(success);

      return ppixmap;

   }





   void load_image::run()
   {

      try
      {

         m_pimagecontext->_task_load_image(this, m_payload, true);

      }
      catch (...)
      {

      }
      // simulate a long load time
      //preempt(2_s);

      if (this->is_ok())
      {

         ////return pimage->m_estatus;

         ////if (m_pimage)
         //{

         //   if (m_functionLoaded)
         //   {

         //      m_functionLoaded(ploadimageinterface);

         //   }

         //}

         return;

      }

      try
      {

         m_pimagecontext->_task_load_image(this, m_payload, false);

      }
      catch (...)
      {

      }

      //if (m_pimage)
      //{

      //   if (m_functionLoaded)
      //   {

      //      m_functionLoaded(ploadimageinterface);

      //   }

      //}

      //return pimage->m_estatus;

   }


   void load_image::on_load_image(const ::i32_size &size, const image32_t *pimage32, int iScan)
   {

      auto ppixmap = get_pixmap_from_data(size, pimage32, iScan);

      on_image_loaded(success);

   }


   void load_image::on_image_loaded(const ::e_status & estatus)
   {

      m_estatus = estatus;

      if (estatus.succeeded())
      {

         m_eflagElement = ::e_flag_success;

      }
      else
      {

         m_eflagElement = ::e_flag_failure;

      }

      if (m_loadoptions.functionLoaded)
      {

         // if (!m_pimageframearray && m_ppixmap)
         // {
         //
         //    construct_newø(m_pimageframearray);
         //
         //    m_pimageframearray->m_ppixmap = m_ppixmap;
         //
         // }

         //m_functionLoaded(m_pimageframearray);

         m_loadoptions.functionLoaded(this);

      }

      // m_ppixmap->m_estatus = estatus;
      //
      // if (estatus.succeeded())
      // {
      //
      //    m_ppixmap->set_ok_flag();
      //
      // }
      // else
      // {
      //
      //    m_ppixmap->set_nok();
      //
      // }

   }


   // pixmap_lease load_image::map(const ::i32_size & size, ::i32 * piScan)
   // {
   //
   //    if (piScan && *piScan > size.cx * 4)
   //    {
   //
   //       m_ppixmap->create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, *piScan);
   //
   //    }
   //    else
   //    {
   //
   //       m_ppixmap->create_as_descriptor(size);
   //
   //    }
   //
   //    if (piScan)
   //    {
   //
   //       *piScan = m_ppixmap->m_iScan;
   //
   //    }
   //
   //    return ::transfer(m_ppixmap->map());
   //
   // }


} // namespace image



