﻿#include "framework.h"
#include "acme/constant/timer.h"


timer::timer()
{

   m_etimer = e_timer_none;
   m_bPeriodic = false;
   m_bHandling = false;
   m_bRet = false;

}


timer::timer(uptr uEvent) :
   m_uEvent(uEvent)
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


::e_status timer::destroy()
{

   m_ptimercallback.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   auto estatus = ::matter::destroy();

   return estatus;

}



const char* timer::debug_note() const
{

   return m_strDebugNote;

}




