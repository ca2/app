#pragma once


class CLASS_DECL_ACME sync_task :
   virtual public ::element
{
public:


   manual_reset_event               m_event;
   __pointer(::element)      m_pobjectRunnable;


   sync_task(::element* pobjectRunnable);
   virtual ~sync_task();


   virtual ::estatus call() override;


};


template < typename PRED >
inline auto __sync_pred(PRED pred)
{

   return __new(sync_task(__pred_method(pred)));

}

