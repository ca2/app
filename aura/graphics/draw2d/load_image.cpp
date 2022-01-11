// Created by camilo on 2021-08-24 23:41 <3ThomasBS_!!
#include "framework.h"
#include "load_image.h"
#include "context_image.h"


load_image::load_image(context_image * pcontextimage) :
   m_pcontextimage(pcontextimage)
{


}


load_image::~load_image()
{


}


void load_image::run()
{

   ::image * pimage = m_pimage;

   try
   {

      m_pcontextimage->_task_load_image(pimage, m_payload, true);

   }
   catch (...)
   {

   }

   if (::is_ok(pimage))
   {

      return pimage->m_estatus;

   }

   try
   {

      m_pcontextimage->_task_load_image(pimage, m_payload, false);

   }
   catch (...)
   {

   }

   return pimage->m_estatus;

}



