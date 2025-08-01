#pragma once


//#include "acme/prototype/prototype/matter.h"


class CLASS_DECL_ACME timer :
   virtual public ::particle
{
public:


   union
   {

      uptr                          m_uTimer;
      enum_timer                    m_etimer;

   };

   timer_task *                     m_pTimerTask;
   bool                             m_bPeriodic;
   bool                             m_bHandling;
   bool                             m_bRet;
   ::pointer<::timer_callback>      m_ptimercallback;
   class ::time                     m_timeWait;
   string                           m_strDebugNote;


   timer();
   timer(uptr uEvent);
   timer(enum_timer etimer);
   ~timer() override;


   //virtual void destroy() override;


   void destroy() override;


   const_char_pointer  debug_note() const override;


};

