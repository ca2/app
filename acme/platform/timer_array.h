#pragma once


#include "acme/primitive/collection/map.h"
#include "timer_callback.h"


namespace acme
{


   class CLASS_DECL_ACME timer_array:
      virtual public timer_callback
   {
   public:


      typedef uptr_map < ::pointer<::timer >>MAP;

      MAP                                       m_map;
      ::pointer<::timer_callback>              m_pcallback;
      bool                                      m_bOk;


      timer_array();
      ~timer_array() override;



      virtual bool create_timer(::particle * pparticle, uptr uEvent, const class ::time & millisEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);
      virtual bool delete_timer(uptr uEvent);

      virtual bool set_timer(::particle * pparticle, uptr uEvent, const class ::time& millisEllapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pvoidData = nullptr);

      void erase_timer(::timer * ptimer) override;


      void destroy() override;
      virtual void delete_all_timers();

      void on_timer(::timer * ptimer) override;
      virtual void _001OnTimer(::timer * ptimer);

      bool e_timer_is_ok() override;


   };


} // namespace acme



