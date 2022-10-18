#pragma once


inline ::payload& task_property(const ::atom& atom) { return ::get_task()->payload(atom); }


template < typename PRED >
inline bool predicate_Sleep(int iTime, PRED pred)
{

   if(iTime < 100)
   {

      preempt(100_ms);

   }
   else
   {

      iTime += 99;

      iTime /= 100;

      for(index i = 0; i < iTime; i++)
      {

         preempt(100_ms);

         if(!::task_get_run() || !pred())
         {

            break;

         }

      }

   }

   return ::task_get_run();

}






//inline thread_parameter::thread_parameter(const matter * psimpleobject)
//{
//
//   m_psimpleobject = (matter *)psimpleobject;
//
//   m_psimpleobject->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}




//template < typename PRED >
//auto sync_predicate(void (* pfnBranch )(::matter * pobjectTask, enum_priority), PRED pred, ::duration durationTimeout, enum_priority epriority)
//{
//
//   auto pobjectTask = __sync_predicate(pred);
//
//   pfnBranch(pobjectTask, epriority);
//
//   pobjectTask->m_event.wait(durationTimeout);
//
//   return pobjectTask;
//
//}
//

//template < typename PRED >
//::thread * fork(PRED pred)
//{
//
//   return ::fork(::get_task(), pred);
//
//}





template < typename PRED >
void async_predicate(void (* pfnBranch )(::matter * pobjectTask, enum_priority), PRED pred, enum_priority epriority)
{

   auto pobjectTask = __routine(pred);

   pfnBranch(pobjectTask, epriority);

}

//
//inline ::thread* get_task(itask_t idthread)
//{
//
//   return (::thread*) get_system()->get_task(idthread);
//
//}
//


//inline class ::wait wait::now() { return get_integral_millisecond(); }


inline void preempt()
{

   if (!::task_get_run())
   {

      auto ptask = ::get_task();

      throw ::exit_exception(ptask);

   }

}


//DEFINE_COMPARISON_WITH_DURATION(wait)


inline time::time(const class duration & duration) : time(duration.time()) {}
inline time::time(const ::INTEGRAL_NANOSECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_NANOSECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MICROSECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MICROSECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MILLISECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MILLISECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_SECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_SECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MINUTE & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MINUTE & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_HOUR & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_HOUR & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_DAY & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_DAY & floating) : time((const ::duration &)floating) {}
