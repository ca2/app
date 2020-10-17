#include "framework.h"


change::change()
{

   m_iUpdateSerial = -1;
   m_bFork = false;

}


change::~change()
{

}


::estatus change::start_task()
{

   return ::success_none;

}


void change::set_up_to_date(::update * pupdate)
{

   m_iUpdateSerial = pupdate->m_iUpdateSerial;

}



