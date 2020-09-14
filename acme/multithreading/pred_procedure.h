#pragma once


#define new ACME_NEW


template < typename PRED >
class __pred_procedure :
   virtual public ::generic
{
public:


   PRED                                m_pred;
   __pointer(::generic)         m_pobjectHold;


   __pred_procedure(PRED pred, ::generic* pobjectHold = nullptr) :
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






::estatus run_task(::generic* pobjectTask);


template < typename PRED >
inline __pointer(::generic) __task_procedure(PRED pred)
{

   return __new(__pred_procedure < PRED >(pred));

}



template < >
inline __pointer(::generic) __task_procedure(nullptr_t)
{

   return nullptr;

}


class CLASS_DECL_ACME processor
{
public:

   virtual void schedule(::generic* pobjectTask, e_priority epriority = priority_normal) = 0;

};


template < typename PRED >
inline auto schedule(processor* pprocessor, PRED pred, e_priority epriority = priority_normal)
{

   auto pobjectTask = create_pred(pred);

   pprocessor->schedule(pobjectTask, epriority);

   return pobjectTask;

}

//
//template < typename PRED >
//auto sync_pred(void (* pfnBranch )(::generic * pobjectTask, e_priority), PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal);




template < typename TYPE >
inline auto __runnable_procedure(TYPE* p, void (TYPE::* pprocedure)())
{

   return __runnable([p, pprocedure]
      {

         (p->*pprocedure)();

      });

}



