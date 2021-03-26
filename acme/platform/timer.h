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
   ::duration                       m_duration;
   string                           m_strDebugNote;


   timer();
   timer(uptr uEvent);
   timer(enum_timer etimer);
   virtual ~timer();


   virtual ::e_status finalize() override;


   const char* debug_note() const override;


};

