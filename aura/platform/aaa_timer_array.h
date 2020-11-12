#pragma once


namespace aura
{


   class CLASS_DECL_AURA timer_array:
      virtual public timer_callback
   {
   public:


      typedef uptr_map < __pointer(::timer) > MAP;

      MAP                                       m_map;
      __pointer(::timer_callback)               m_pcallback;
      bool                                      m_bOk;


      timer_array();
      virtual ~timer_array();



      virtual bool create_timer(uptr uEvent, ::u32 nEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);
      virtual bool delete_timer(uptr uEvent);

      virtual bool set_timer(uptr uEvent, ::u32 nEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);


      virtual bool remove_timer(::timer * ptimer);


      virtual void finalize() override;
      virtual void delete_all_timers();

      virtual bool on_timer(::timer * ptimer) override;
      virtual void _001OnTimer(::timer * ptimer);

      virtual bool e_timer_is_ok() override;


   };


} // namespace aura



