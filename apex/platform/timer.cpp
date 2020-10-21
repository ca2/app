#include "framework.h"
#include "acme/const/timer.h"


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



void timer::finalize()
{

   m_ptimercallback.release(OBJ_REF_DBG_THIS);

}



const char* timer::debug_note() const
{

   return m_strDebugNote;

}




