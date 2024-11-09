#pragma once


//class sync_future;
//
//
//inline ::pointer<sync_future>__sync_future();
//
//
//
//class CLASS_DECL_ACME sync_future : 
//   virtual public ::synchronization//{
//protected:
//
//   friend ::pointer<sync_future>__sync_future();
//
//   sync_future()
//   {
//
//      m_phappeningCompletion = __allocate manual_reset_happening();
//
//   }
//public:
//
//
//   ::payload                                    m_var;
//   ::pointer<manual_reset_happening>         m_phappeningCompletion;
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
//      m_phappeningCompletion->SetEvent();
//
//   }
//
//   
//   ::e_status wait(const class ::time& wait = time::infinite()) override
//   {
//
//      return m_phappeningCompletion->wait(wait);
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
//   return __allocate sync_future();
//
//}
//
//
//
