#include "framework.h"


namespace promise
{


   context::context()
   {

      m_iUpdateSerial = -1;
      m_bFork = false;

   }


   context::~context()
   {

   }


   ::estatus context::start_task()
   {

      return ::success_none;

   }


   void context::set_up_to_date(const ::promise::subject *phandler)
   {

      m_iUpdateSerial = phandler->m_iUpdateSerial;

   }


   bool context::is_up_to_date(const ::promise::subject * phandler) const
   {

      if (m_iUpdateSerial < 0)
      {

         return false;

      }

      if (phandler->m_iUpdateSerial < 0)
      {

         return false;

      }

      return m_iUpdateSerial == phandler->m_iUpdateSerial;

   }


} // namespace promise



