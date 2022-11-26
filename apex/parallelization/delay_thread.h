#pragma once


//class delay_thread :
//   virtual public thread
//{
//
//public:
//
//   
//   class ::time       m_timeSleep;
//
//
//   delay_thread(const class time & timeSleep = 1_s)
//   {
//
//      m_timeSleep = timeSleep;
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
//         auto timeSleep = m_timeSleep;
//
//         if (timeSleep.is_null())
//         {
//
//            break;
//
//         }
//
//         m_timeSleep.Null();
//
//         if (!task_sleep(timeSleep))
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
//   predicate_delay_thread(::particle * pparticle, PRED pred, ::u32 dwSleep = 1000) :
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
//delay_thread * predicate_delay(::particle * pparticle, class ::time tickDelay, PRED pred)
//{
//
//   auto pthread  = __new(predicate_delay_thread < PRED >(pparticle, pred, tickDelay));
//
//   pthread->begin();
//
//   return pthread;
//
//}
//
//

