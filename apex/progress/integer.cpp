// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


namespace progress
{


   integer::integer()
   {

      m_plistener = nullptr;
      m_dProgressStart = 0.0;
      m_dProgressEnd = 1.0;

   }


   integer::~integer()
   {

      m_plistener = nullptr;

   }


   void integer::trace_progress(i64 iStep)
   {

      m_scalar.set(iStep);

   }

   void integer::trace_progress()
   {

      if (m_plistener != nullptr)
      {

         m_plistener->on_progress(m_dProgressStart + (m_dProgressEnd - m_dProgressStart) * m_scalar.get_rate());

      }

   }

   void integer::progress_step()
   {

      m_scalar++;

      trace_progress();

   }



   void integer::on_set_scalar(int_scalar_source * psource, e_scalar escalar, i64 iValue, int iFlags)
   {

      if (m_scalar.m_psource == psource)
      {

         if (m_scalar.m_escalar == escalar)
         {

            trace_progress();

         }
         else
         {
         }

      }

   }


} // namespace progress



