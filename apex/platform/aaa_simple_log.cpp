#include "framework.h"
#include "simple_log.h"


simple_log::simple_log()
{

   m_psimplelog = nullptr;

   m_iLogTarget = -1;

}


simple_log::simple_log(simple_log * psimplelog, index iLogTarget)
{

   m_psimplelog = psimplelog;

   m_iLogTarget = iLogTarget;

}


simple_log::~simple_log()
{


}


void simple_log::log_line(string str, index iLogTarget)
{

   if (m_psimplelog != nullptr)
   {

      m_psimplelog->log_line(str, iLogTarget);

   }

}


void simple_log::log_line(string str)
{

   if (m_psimplelog != nullptr)
   {

      m_psimplelog->log_line(str, m_iLogTarget);

   }

}



