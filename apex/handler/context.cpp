#include "framework.h"
#include "context.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"


context::context()
{

   m_iUpdateSerial = -1;
   //m_bFork = false;

}


context::~context()
{

}


void context::start_task()
{

}


void context::set_up_to_date(const ::topic * ptopic)
{

   m_iUpdateSerial = ptopic->_extended_topic()->m_iUpdateSerial;

}


bool context::is_up_to_date(const ::topic * ptopic) const
{

   if (m_iUpdateSerial < 0)
   {

      return false;

   }

   if (ptopic->_extended_topic()->m_iUpdateSerial < 0)
   {

      return false;

   }

   return m_iUpdateSerial == ptopic->_extended_topic()->m_iUpdateSerial;

}



