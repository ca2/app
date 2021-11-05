#pragma once


namespace acme
{


   class CLASS_DECL_ACME timer_array:
      virtual public timer_callback
   {
   public:


      typedef uptr_map < __pointer(::timer) > MAP;

      MAP                                       m_map;
      __pointer(::timer_callback)               m_pcallback;
      bool                                      m_bOk;


      timer_array();
      ~timer_array() override;



      virtual bool create_timer(::object * pobject, uptr uEvent, ::duration millisEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);
      virtual bool delete_timer(uptr uEvent);

      virtual bool set_timer(::object * pobject, uptr uEvent, ::duration millisEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);

      bool erase_timer(::timer * ptimer) override;


      ::e_status destroy() override;
      virtual void delete_all_timers();

      bool on_timer(::timer * ptimer) override;
      virtual void _001OnTimer(::timer * ptimer);

      virtual bool e_timer_is_ok() override;


   };


} // namespace acme



