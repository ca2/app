#pragma once


CLASS_DECL_ACME void main_async_runnable(::matter * pobjectTask);
CLASS_DECL_ACME void main_sync_runnable(::matter * pobjectTask, ::duration durationTimeout = one_minute());
CLASS_DECL_ACME void main_branch(::matter* pobjectTask, enum_priority epriority);


::e_status run_task(::matter * pobjectTask);








template < typename PRED >
inline void main_async(PRED pred, enum_priority epriority = e_priority_normal)
{

   async_predicate(&main_branch, pred, epriority);

}


template < typename PRED >
inline void main_sync(PRED pred, ::duration durationTimeout = one_minute(), enum_priority epriority = e_priority_normal)
{

   sync_predicate(&main_branch, pred, durationTimeout, epriority);

}



