#pragma once


//CLASS_DECL_ACME void main_async_runnable(::context_object * pobjectTask);
//CLASS_DECL_ACME void main_sync_runnable(::context_object * pobjectTask, ::duration durationTimeout = one_minute());


#define new ACME_NEW


template < typename PRED >
class ___method :
   virtual public ::matter
{
public:


   PRED                                m_pred;
   __pointer(::matter)         m_pobjectHold;


   ___method(PRED pred, ::matter * pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~___method()
   {


   }


   virtual ::estatus run() override
   {

      m_pred();

      return ::success;

   }


   void receive_response(const ::var&) override
   {

      __throw(interface_only_exception());

   }



};






::estatus run_task(::matter * pobjectTask);


template < typename PRED >
inline __pointer(matter) __method(PRED pred)
{

   return __new(___method < PRED >(pred));

}


template < typename PRED >
inline __pointer(matter) __method(PRED pred, ::matter * pobjectHold)
{

   return __new(___method < PRED >(pred, pobjectHold));

}



template < >
inline __pointer(matter) __method(nullptr_t, ::matter * pobjectHold)
{

   return nullptr;

}

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



