#pragma once


CLASS_DECL_ACME void main_async_runnable(::generic * pobjectTask);
CLASS_DECL_ACME void main_sync_runnable(::generic * pobjectTask, ::duration durationTimeout = one_minute());


#define new AURA_NEW


template < typename PRED >
class __pred_procedure :
   virtual public ::generic
{
public:


   PRED                                m_pred;
   __pointer(::generic)         m_pobjectHold;


   __pred_procedure(PRED pred, ::generic * pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~__pred_procedure()
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






::estatus run_task(::generic * pobjectTask);


template < typename PRED >
inline auto __task_procedure(PRED pred, ::generic * pobjectHold)
{

   return __new(__pred_procedure < PRED >(pred, pobjectHold));

}



template < >
inline auto __task_procedure(nullptr_t, ::generic * pobjectHold)
{

   return nullptr;

}

class processor
{
public:

   virtual void schedule(::generic * pobjectTask, e_priority epriority = priority_normal) = 0;

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
//auto sync_pred(void (* pfnBranch )(::generic * pobjectTask, e_priority), PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal);









CLASS_DECL_ACME void main_branch(::generic * pobjectTask, e_priority epriority);







template < typename PRED >
inline void main_async(PRED pred, e_priority epriority = priority_normal)
{

   async_pred(&main_branch, pred, epriority);

}


template < typename PRED >
inline void main_sync(PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal)
{

   sync_pred(&main_branch, pred, durationTimeout, epriority);

}


template < typename TYPE >
inline auto __runnable_procedure(TYPE * p, void (TYPE:: * pprocedure)())
{

   return __runnable([p, pprocedure]
   {

      (p->*pprocedure)();

   });

}



