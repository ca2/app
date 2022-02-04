#include "framework.h"


//namespace topic
//{
//

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

   //return ::success_none;

}


void context::set_up_to_date(const ::topic *phandler)
{

   m_iUpdateSerial = phandler->m_iUpdateSerial;

}


bool context::is_up_to_date(const ::topic * phandler) const
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


//} // namespace topic



