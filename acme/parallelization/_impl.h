#pragma once







//inline thread_parameter::thread_parameter(const matter * psimpleobject)
//{
//
//   m_psimpleobject = (matter *)psimpleobject;
//
//   m_psimpleobject->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}




//template < typename PRED >
//auto sync_predicate(void (* pfnBranch )(::matter * pobjectTask, enum_priority), PRED pred, class ::time timeTimeout, enum_priority epriority)
//{
//
//   auto pobjectTask = __sync_predicate(pred);
//
//   pfnBranch(pobjectTask, epriority);
//
//   pobjectTask->m_event.wait(timeTimeout);
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


//inline class ::time wait::now() { return get_integral_millisecond(); }




//DEFINE_COMPARISON_WITH_TIME(inline, wait)


