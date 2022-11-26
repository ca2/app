#include "framework.h"
#include "frame_array.h"


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

   if (m_timeTotal.is_null())
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

      ::time timeUpperBound;

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
