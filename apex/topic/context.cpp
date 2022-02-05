#include "framework.h"


context::context()
{

   m_iUpdateSerial = -1;
   m_bFork = false;

}


context::~context()
{

}


void context::start_task()
{

}


void context::set_up_to_date(const ::topic * ptopic)
{

   m_iUpdateSerial = ptopic->m_pextendedtopic->m_iUpdateSerial;

}


bool context::is_up_to_date(const ::topic * ptopic) const
{

   if (m_iUpdateSerial < 0)
   {

      return false;

   }

   if (ptopic->m_pextendedtopic->m_iUpdateSerial < 0)
   {

      return false;

   }

   return m_iUpdateSerial == ptopic->m_pextendedtopic->m_iUpdateSerial;

}



