#include "framework.h"
#include "frame_array.h"
#include "aura/graphics/image/drawing.h"


image_frame_array::image_frame_array()
{

   m_iLoop = 0;
   m_countLoop = 0;

}


image_frame_array::~image_frame_array()
{

}


::image_pointer image_frame_array::calc_current_frame(image_dynamic & dynamic)
{

   if (is_empty())
   {

      return nullptr;

   }

   auto pframe = first_pointer();

   if (is_empty(1))
   {

      return pframe->m_pimage;

   }

   if (!dynamic.m_bStart)
   {

      dynamic.m_bStart = true;

      dynamic.m_timeStart.Now();

   }

   auto pimage = m_pimage;

   double dSpeed = 1.0;

   if(pimage && extension())
   { 
   
      dSpeed = extension()->m_dSpeed;

   }

   auto elapsed = dynamic.m_timeStart.elapsed();

   elapsed *= dSpeed;

   if (m_timeTotal <= 0_s)
   {

      return pframe->m_pimage;

   }

   auto uiLoop = elapsed / m_timeTotal;

   if (uiLoop > m_iLoop)
   {

      m_iLoop = (::index) uiLoop;

      dynamic.m_iFrame = -1;

   }

   if (m_countLoop == 0 || m_iLoop < m_countLoop)
   {

      elapsed %= m_timeTotal;

      class ::time timeUpperBound;

      index iFrame = 0;

      for (; iFrame < get_count(); iFrame++)
      {

         auto pframe = this->element_at(iFrame);

         timeUpperBound += pframe->m_time;

         if (elapsed < timeUpperBound)
         {

            break;

         }

      }

      dynamic.m_iFrame = iFrame;

      return element_at(iFrame)->m_pimage;

   }
   else
   {

      dynamic.m_iFrame = get_upper_bound();

      return last()->m_pimage;

   }

}


void image_frame_array::update(::image * pimageHost, const ::image_drawing & imagedrawing)
{

   auto pimageSource = imagedrawing.image();

   auto pframes = pimageSource->frames();

   if (!pframes || pframes->is_empty())
   {

      return;

   }

   m_pimage = pimageHost;

   //auto dx = (double)imagedrawing.m_rectangleTarget.width() / (double)imagedrawing.image()->width();
   //auto dy = (double)imagedrawing.m_rectangleTarget.height() / (double)imagedrawing.image()->height();

   //::size_i32 size;

   //size.cx() = pframes->m_size.cx() * dx;
   //size.cy() = pframes->m_size.cy() * dx;

   //m_size = size;

   m_pimage->pixmap::init(imagedrawing.m_rectangleTarget.size(), nullptr, 0);

   this->set_size(pframes->get_count());

   class ::time timeTotal;

   for (index iFrame = 0; iFrame < pframes->get_count(); iFrame++)
   {

      auto pframeSource = pframes->element_at(iFrame);

      auto time = pframeSource->m_time;

      timeTotal += time;

      auto & pframeHost = this->element_at(iFrame);

      __construct_new(pframeHost);

      pframeHost->create(pframeSource, imagedrawing, this);

   }

   m_timeTotal = timeTotal;

   m_pimage->m_estatus = ::success;

   m_pimage->set_ok_flag();

}
 

