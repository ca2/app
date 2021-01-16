#pragma once


//CLASS_DECL_ACME void main_async_runnable(::context_object * pobjectTask);
//CLASS_DECL_ACME void main_sync_runnable(::context_object * pobjectTask, ::duration durationTimeout = one_minute());


#define new ACME_NEW
//
//
//template < typename PRED >
//class pred_method :
//   virtual public ::matter
//{
//public:
//
//
//   PRED   m_pred;
//
//
//   pred_method(PRED pred) :
//      m_pred(pred)
//   {
//
//   }
//
//
//   virtual ~pred_method()
//   {
//
//
//   }
//
//
//   virtual ::e_status run() override
//   {
//
//      m_pred();
//
//      return ::success;
//
//   }
//
//
//   void receive_response(const ::payload&) override
//   {
//
//      __throw(interface_only_exception());
//
//   }
//
//
//
//};
//



template < typename PRED >
class pred_routine :
   virtual public ::matter
{
public:


   PRED m_pred;


   pred_routine(PRED pred) : m_pred(pred) { }
   virtual ~pred_routine() {}
   //method(const ::matter_pointer & pmatter) : matter_pointer(pmatter) { }
   //method(const ::method & method) : matter_pointer(method) { }


   //inline ::e_status operator()() const;

   virtual ::e_status run() override
   {

      m_pred();

      return ::success;

   }

   //template < typename PRED >
   //void pred(PRED pred);

   //inline method & operator = (const ::method & method) { m_pmatter = method.m_pmatter; return *this; }
   //method & operator = (const ::payload & payload);


};




template < typename PRED >
::promise::routine __routine(PRED pred)
{

   return __new(pred_routine<PRED>(pred));

}





::e_status run_task(::matter * pobjectTask);


class processor
{
public:

   virtual void schedule(::matter * pobjectTask, e_priority epriority = priority_normal) = 0;

};


template < typename PRED >
inline auto schedule(processor * pprocessor, PRED pred, e_priority epriority = priority_normal)
{

   auto pobjectTask = create_pred(pred);

   pprocessor->schedule(pobjectTask, epriority);

   return pobjectTask;

}

//
//template < typename PRED >
//auto sync_pred(void (* pfnBranch )(::object * pobjectTask, e_priority), PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal);









//CLASS_DECL_ACME void main_branch(::matter * pobjectTask, e_priority epriority);









template < typename TYPE >
inline auto __runnable_method(TYPE * p, void (TYPE:: * pmethod)())
{

   return __runnable([p, pmethod]
   {

      (p->*pmethod)();

   });

}



