#pragma once


class CLASS_DECL_ACME sync_task :
   virtual public ::matter
{
public:


   manual_reset_event               m_event;
   __pointer(::matter)      m_pobjectRunnable;


   sync_task(::matter* pobjectRunnable);
   virtual ~sync_task();


   virtual ::estatus call() override;


};


template < typename PRED >
inline auto __sync_pred(PRED pred)
{

   return __new(sync_task(__method(pred)));

}

