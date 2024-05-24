#pragma once





void run_task(::matter * pobjectTask);


class processor
{
public:


   virtual void schedule(::matter * pobjectTask, enum_priority epriority = e_priority_normal) = 0;


};



template < typename PRED >
inline auto schedule(processor * pprocessor, PRED pred, enum_priority epriority = e_priority_normal)
{

   auto pobjectTask = create_predicate(pred);

   pprocessor->schedule(pobjectTask, epriority);

   return pobjectTask;

}



