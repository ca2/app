#pragma once


//class delay_thread :
//   virtual public thread
//{
//
//public:
//
//   
//   ::duration       m_durationSleep;
//
//
//   delay_thread(const ::duration & durationSleep = 1_s)
//   {
//
//      m_durationSleep = durationSleep;
//
//   }
//
//
//   void run()
//   {
//
//      while (true)
//      {
//
//         auto durationSleep = m_durationSleep;
//
//         if (durationSleep.is_null())
//         {
//
//            break;
//
//         }
//
//         m_durationSleep.Null();
//
//         if (!task_sleep(durationSleep))
//         {
//
//            return success_exit_thread;
//
//         }
//
//      }
//
//      do_delayed();
//
//      return ::success;
//
//   }
//
//
//   virtual void do_delayed()
//   {
//
//   }
//
//};
//
//
//template < typename PRED >
//class predicate_delay_thread :
//   virtual public delay_thread
//{
//public:
//
//   
//   PRED &      m_predicate;
//   
//   
//   predicate_delay_thread(::object * pobject, PRED pred, ::u32 dwSleep = 1000) :
//      m_predicate(pred),
//      delay_thread(dwSleep)
//   {
//      
//   }
//
//
//   virtual void do_delayed() override
//   {
//
//      m_predicate();
//
//   }
//   
//
//};
//
//
//template < typename PRED >
//delay_thread * predicate_delay(::object * pobject, ::duration tickDelay, PRED pred)
//{
//
//   auto pthread  = __new(predicate_delay_thread < PRED >(pobject, pred, tickDelay));
//
//   pthread->begin();
//
//   return pthread;
//
//}
//
//

