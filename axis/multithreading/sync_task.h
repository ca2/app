#pragma once


class CLASS_DECL_AURA sync_task :
   virtual public ::generic_object
{
public:


   manual_reset_event               m_event;
   __pointer(::generic_object)      m_pobjectRunnable;


   sync_task(::generic_object* pobjectRunnable);
   virtual ~sync_task();


   virtual ::estatus call() override;


};


template < typename PRED >
inline auto __sync_pred(PRED pred)
{

   return __new(sync_task(__task_procedure(pred)));

}

