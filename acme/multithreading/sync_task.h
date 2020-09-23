#pragma once


class CLASS_DECL_ACME sync_task :
   virtual public ::generic
{
public:


   manual_reset_event               m_event;
   __pointer(::generic)      m_pobjectRunnable;


   sync_task(::generic* pobjectRunnable);
   virtual ~sync_task();


   virtual ::estatus call() override;


};


template < typename PRED >
inline auto __sync_pred(PRED pred)
{

   return __new(sync_task(__pred_method(pred)));

}

