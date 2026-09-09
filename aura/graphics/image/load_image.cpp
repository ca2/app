// Created by camilo on 2021-08-24 23:41 <3ThomasBS_!!
#include "platform.h"
#include "load_image.h"
#include "context.h"
#include "acme/graphics/image/frame_array.h"
#include <exception>


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

            auto ppixmapLoad = ploadimage->m_pimageframearray
               ? ploadimage->m_pimageframearray->get_pixmap() : nullptr;

            if (!ppixmapLoad || !ppixmapLoad->is_ok())
            {
               throw ::exception(error_failed, "image load: completion has no valid decoded pixmap");
            }

            if (ppixmapLoad)
            {

               ppixmap->create_as_descriptor(ppixmapLoad->m_sizeRaw, DEFAULT_CREATE_IMAGE_FLAG, ppixmapLoad->m_iScan);

               ppixmap->m_size = ppixmapLoad->m_size;

               ppixmap->copy_from(ppixmapLoad);

               ppixmap->m_eflagElement = ::e_flag_success;

               ppixmap->m_estatus = ::success;

               if (!ppixmap->is_ok())
               {
                  throw ::exception(error_failed, "image load: copied destination pixmap is invalid");
               }

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
      // Preserve the cached attempt followed by the no-cache retry, but never
      // silently discard the reason for a failed decode or completion callback.
      for (int attempt = 0; attempt < 2; ++attempt)
      {
         ::string reason;
         try
         {
            m_pimagecontext->_task_load_image(this, m_payload, attempt == 0);
            if (is_ok())
               return;
            reason = "loader returned without a successful completion";
         }
         catch (const ::exception & exception)
         {
            reason = exception.get_message();
            auto details = exception.m_strDetails;
            if (details.has_character())
               reason += " | " + details;
         }
         catch (const ::std::exception & exception)
         {
            reason = exception.what();
         }
         catch (...)
         {
            reason = "unknown exception during image loading or completion";
         }

         // A callback can throw after on_image_loaded has marked us successful.
         // Do not return a false success or skip the retry in that case.
         m_estatus = ::error_failed;
         set_nok();
         errorf("[image.load] failed path=%s attempt=%d cache=%d action=%s reason=%s",
            m_payload.as_file_path().c_str(), attempt + 1, attempt == 0,
            attempt == 0 ? "retry-without-cache" : "give-up", reason.c_str());
      }
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

         try
         {
            m_loadoptions.functionLoaded(this);
         }
         catch (const ::exception & exception)
         {
            throw ::exception(exception.m_estatus,
               "image load: completion callback failed: " + exception.get_message(), exception.m_strDetails);
         }
         catch (const ::std::exception & exception)
         {
            throw ::exception(error_failed, "image load: completion callback failed: " + ::string(exception.what()));
         }
         catch (...)
         {
            throw ::exception(error_failed, "image load: completion callback failed with an unknown exception");
         }

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



