// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "real.h"


namespace progress
{


   real::real()
   {

      defer_create_synchronization();


   }


   real::~real()
   {

   }


   void real::close_progress()
   {

   }


   bool real::on_set_scalar(enum_scalar escalar, ::number number, int iFlags)
   {

      return false;

   }


   ::number real::get_scalar_minimum(enum_scalar escalar)
   {

      return 0.0;

   }


   ::number real::get_scalar(enum_scalar escalar)
   {

      return (double)m_iStep / (double)m_iStepCount;

   }


   ::number real::get_scalar_maximum(enum_scalar escalar)
   {

      return 1.0;

   }


   void real::redraw()
   {




   }


   void real::format_status(const char * pszFormat)
   {

      string strStatus(pszFormat);

      strStatus.replace_with(::as_string(m_iStep), "%1");
      strStatus.replace_with(::as_string(m_iStepCount), "%2");

      m_strStatus = strStatus;

      redraw();

   }


   bool real::step()
   {

      ASSERT(m_iStep + 1 <= m_iStepCount);

      if (m_iStep + 1 > m_iStepCount)
      {

         return ::success;

      }

      m_iStep++;

      redraw();

      return true;

   }


} // namespace progress



