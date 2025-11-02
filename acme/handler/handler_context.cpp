#include "framework.h"
#include "acme/handler/handler_context.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"




handler_context::~handler_context()
{

}


void handler_context::start_task()
{

}


void handler_context::set_up_to_date(const ::topic * ptopic)
{

   m_uUpdateSerial = ptopic->_extended_topic()->m_uUpdateSerial;

}


//bool handler_context::is_up_to_date(const ::topic * ptopic) const
//{
//
//   if (!m_uUpdateSerial)
//   {
//
//      return false;
//
//   }
//   
//   if (!ptopic->_extended_topic()->m_uUpdateSerial)
//   {
//
//      return false;
//
//   }
//
//   return m_iUpdateSerial == ptopic->_extended_topic()->m_iUpdateSerial;
//
//}



