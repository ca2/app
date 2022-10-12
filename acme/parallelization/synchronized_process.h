#pragma once


//class sync_future;
//
//
//inline ::pointer<sync_future>__sync_future();
//
//
//
//class CLASS_DECL_ACME sync_future : 
//   virtual public ::synchronization_object
//{
//protected:
//
//   friend ::pointer<sync_future>__sync_future();
//
//   sync_future()
//   {
//
//      m_peventCompletion = __new(manual_reset_event);
//
//   }
//public:
//
//
//   ::payload                                    m_var;
//   ::pointer<manual_reset_event>         m_peventCompletion;
//
//
//   virtual ~sync_future() {}
//
//
//   void operator()(const ::payload & payload) override
//   {
//
//      m_var = payload;
//
//      m_peventCompletion->SetEvent();
//
//   }
//
//   
//   ::e_status wait(const class ::wait& wait = duration::infinite()) override
//   {
//
//      return m_peventCompletion->wait(wait);
//
//   }
//
//
//};
//
//
//inline ::pointer<sync_future>__sync_future()
//{
//
//   return __new(sync_future);
//
//}
//
//
//
