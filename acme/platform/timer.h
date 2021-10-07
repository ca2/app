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

   bool                             m_bPeriodic;
   bool                             m_bHandling;
   bool                             m_bRet;
   __pointer(::timer_callback)      m_ptimercallback;
   class ::wait                     m_wait;
   string                           m_strDebugNote;


   timer();
   timer(uptr uEvent);
   timer(enum_timer etimer);
   ~timer() override;


   //virtual ::e_status destroy() override;


   ::e_status destroy() override;


   const char* debug_note() const override;


};

