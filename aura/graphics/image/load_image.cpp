// Created by camilo on 2021-08-24 23:41 <3ThomasBS_!!
#include "framework.h"
#include "load_image.h"
#include "image_context.h"


load_image::load_image(::image_context * pcontextimage) :
   m_pcontextimage(pcontextimage)
{


}


load_image::~load_image()
{


}


void load_image::run()
{

   ::image::image *pimage = m_pimage;

   try
   {

      m_pcontextimage->_task_load_image(pimage, m_payload, true);

   }
   catch (...)
   {

   }

   if (pimage->is_ok())
   {

      //return pimage->m_estatus;

      if (m_functionLoaded)
      {

         m_functionLoaded(pimage);

      }

      return;

   }

   try
   {

      m_pcontextimage->_task_load_image(pimage, m_payload, false);

   }
   catch (...)
   {

   }

   if (m_functionLoaded)
   {

      m_functionLoaded(pimage);

   }

   //return pimage->m_estatus;

}



