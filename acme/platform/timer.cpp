#include "framework.h"
#include "acme/constant/timer.h"
#include "timer.h"


timer::timer()
{

   m_etimer = e_timer_none;
   m_bPeriodic = false;
   m_bHandling = false;
   m_bRet = false;

}


timer::timer(uptr uTimer) :
   m_uTimer(uTimer)
{

   m_bPeriodic = false;
   m_bHandling = false;
   m_bRet = false;

}



timer::timer(enum_timer etimer) :
   m_etimer(etimer)
{

   m_bPeriodic = false;
   m_bHandling = false;
   m_bRet = false;


}



timer::~timer()
{

}


void timer::destroy()
{

   m_ptimercallback.release();

   /*auto estatus =*/ ::particle::destroy();

   //return estatus;

}



const char* timer::debug_note() const
{

   return m_strDebugNote.c_str();

}




