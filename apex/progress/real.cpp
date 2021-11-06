// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"


namespace progress
{


   real::real()
   {

      defer_create_mutex();


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

      strStatus.replace("%1", __string(m_iStep));
      strStatus.replace("%2", __string(m_iStepCount));

      m_strStatus = strStatus;

      redraw();

   }


   ::e_status real::step()
   {

      ASSERT(m_iStep + 1 <= m_iStepCount);

      if (m_iStep + 1 > m_iStepCount)
      {

         return ::success;

      }

      m_iStep++;

      redraw();

      return ::success;

   }


} // namespace progress



