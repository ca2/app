#pragma once


//CLASS_DECL_ACME void main_async_runnable(::object * pobjectTask);
//CLASS_DECL_ACME void main_sync_runnable(::object * pobjectTask, ::duration durationTimeout = one_minute());


#define new ACME_NEW
//
//
//template < typename PRED >
//class predicate_method :
//   virtual public ::matter
//{
//public:
//
//
//   PRED   m_predicate;
//
//
//   predicate_method(PRED pred) :
//      m_predicate(pred)
//   {
//
//   }
//
//
//   virtual ~predicate_method()
//   {
//
//
//   }
//
//
//   virtual ::e_status run() override
//   {
//
//      m_predicate();
//
//      return ::success;
//
//   }
//
//
//   void receive_response(const ::payload&) override
//   {
//
//      throw ::interface_only_exception();
//
//   }
//
//
//
//};
//



template < typename PREDICATE >
class predicate_routine :
   virtual public ::matter
{
public:


   PREDICATE      m_predicate;
   ::duration     m_durationTimeout = DURATION{64,0};



   predicate_routine(PREDICATE predicate) : m_predicate(predicate) { }
   predicate_routine(const ::duration & duration, PREDICATE predicate) : m_durationTimeout(duration), m_predicate(predicate) { }
   ~predicate_routine() override {}
   //method(const ::matter_pointer & pmatter) : matter_pointer(pmatter) { }
   //method(const ::method & method) : matter_pointer(method) { }


   //inline ::e_status operator()() const;

   DURATION timeout() const override { return m_durationTimeout; }


   virtual ::e_status run() override
   {

      m_predicate();

      return ::success;

   }

   //template < typename PRED >
   //void pred(PRED pred);

   //inline method & operator = (const ::method & method) { m_pmatter = method.m_pmatter; return *this; }
   //method & operator = (const ::payload & payload);


};




template < typename PRED >
::routine __routine(PRED pred)
{

   return __new(predicate_routine<PRED>(pred));

}


template < typename PRED >
::routine __routine(const ::duration & duration, PRED pred)
{

   return __new(predicate_routine<PRED>(duration, pred));

}


::e_status run_task(::matter * pobjectTask);


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

//
//template < typename PRED >
//auto sync_predicate(void (* pfnBranch )(::object * pobjectTask, enum_priority), PRED pred, ::duration durationTimeout = one_minute(), enum_priority epriority = e_priority_normal);









//CLASS_DECL_ACME void main_branch(::matter * pobjectTask, enum_priority epriority);









template < typename TYPE >
inline auto __runnable_method(TYPE * p, void (TYPE:: * pmethod)())
{

   return __runnable([p, pmethod]
   {

      (p->*pmethod)();

   });

}



template < typename PREDICATE, typename PAYLOAD >
auto __payload_routine(PREDICATE predicate, PAYLOAD & payload)
{

   return __routine([predicate, &payload]()
                    {

                       predicate(payload);

                    });

}


