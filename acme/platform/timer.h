#pragma once


class CLASS_DECL_ACME timer :
   virtual public ::matter
{
public:


   union
   {

      uptr                          m_uEvent;
      enum_timer                    m_etimer;

   };

   timer_task *                     m_pTimerTask;
   bool                             m_bPeriodic;
   bool                             m_bHandling;
   bool                             m_bRet;
   ::pointer<::timer_callback>     m_ptimercallback;
   class ::wait                     m_wait;
   string                           m_strDebugNote;


   timer();
   timer(uptr uEvent);
   timer(enum_timer etimer);
   ~timer() override;


   //virtual void destroy() override;


   void destroy() override;


   const char* debug_note() const override;


};

