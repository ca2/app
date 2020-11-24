#include "framework.h"


machine::machine()
{

   m_iUpdateSerial = -1;
   m_bFork = false;

}


machine::~machine()
{

}


::estatus machine::start_task()
{

   return ::success_none;

}


void machine::set_up_to_date(::manager * pupdate)
{

   m_iUpdateSerial = pupdate->m_iUpdateSerial;

}



