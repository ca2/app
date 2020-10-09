#pragma once


//CLASS_DECL_ACME void main_async_runnable(::context_object * pobjectTask);
//CLASS_DECL_ACME void main_sync_runnable(::context_object * pobjectTask, ::duration durationTimeout = one_minute());


#define new ACME_NEW


template < typename PRED >
class ___pred_method :
   virtual public ::element
{
public:


   PRED                                m_pred;
   __pointer(::element)         m_pobjectHold;


   ___pred_method(PRED pred, ::element * pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~___pred_method()
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






::estatus run_task(::element * pobjectTask);


template < typename PRED >
inline __pointer(element) __pred_method(PRED pred)
{

   return __new(___pred_method < PRED >(pred));

}


template < typename PRED >
inline __pointer(element) __pred_method(PRED pred, ::element * pobjectHold)
{

   return __new(___pred_method < PRED >(pred, pobjectHold));

}



template < >
inline __pointer(element) __pred_method(nullptr_t, ::element * pobjectHold)
{

   return nullptr;

}

class processor
{
public:

   virtual void schedule(::element * pobjectTask, e_priority epriority = priority_normal) = 0;

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









//CLASS_DECL_ACME void main_branch(::element * pobjectTask, e_priority epriority);









template < typename TYPE >
inline auto __runnable_method(TYPE * p, void (TYPE:: * pmethod)())
{

   return __runnable([p, pmethod]
   {

      (p->*pmethod)();

   });

}



