// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSørensen!!
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

   void real::on_set_scalar(e_scalar escalar, double d, int iFlags)
   {

   }


   void real::get_scalar_minimum(e_scalar escalar, double & d)
   {

      d = 0.0;

   }


   void real::get_scalar(e_scalar escalar, double & d)
   {

      d = (double)m_iStep / (double)m_iStepCount;

   }


   void real::get_scalar_maximum(e_scalar escalar, double & d)
   {

      d = 1.0;

   }


   void real::redraw()
   {




   }

   void real::format_status(const char * pszFormat)
   {

      string strStatus(pszFormat);

      strStatus.replace_with(__string(m_iStep), "%1");
      strStatus.replace_with(__string(m_iStepCount), "%2");

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



