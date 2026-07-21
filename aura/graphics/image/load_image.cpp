// Created by camilo on 2021-08-24 23:41 <3ThomasBS_!!
#include "framework.h"
#include "load_image.h"
#include "context.h"


namespace image
{


   load_image::load_image()
   {


   }


   load_image::~load_image()
   {


   }


   void load_image::initialize_load_image(::image::image_context * pimagecontext, ::pixmap * ppixmap)
   {

      m_pimagecontext = pimagecontext;

      m_ppixmap = ppixmap;

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

      if (m_ppixmap->is_ok())
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


   void load_image::on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan) 
   {

      m_ppixmap->on_load_image(pimage32, size, iScan);
   
      on_image_loaded(success);

   }


   void load_image::on_image_loaded(const ::e_status & estatus)
   {

      if (m_functionLoaded)
      {

         m_functionLoaded(m_ppixmap);

      }

      m_ppixmap->m_estatus = estatus;

      if (estatus.succeeded())
      {

         m_ppixmap->set_ok_flag();

      }
      else
      {

         m_ppixmap->set_nok();

      }

   }


   image32_t * load_image::defer_image32(const ::i32_size & size, ::i32 * piScan)
   {
      
      if (piScan && *piScan > size.cx * 4)
      {

         m_ppixmap->create(size, DEFAULT_CREATE_IMAGE_FLAG, *piScan);

      }
      else
      {

         m_ppixmap->create(size);

      }

      if (piScan)
      {

         *piScan = m_ppixmap->m_iScan;

      }

      return m_ppixmap->m_pimage32Raw;

   }


} // namespace image



