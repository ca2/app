void * CreateDispatchQueue();

void CancelDispatchSource(void * p);

void * CreateDispatchTimer(u64 interval, u64 leeway, void * queue, void(*timer)(void * p), void * p);
void * ResetDispatchTimer(void * timer, u64 interval, u64 leeway);

void ReleaseDispatch(void * p);

void apex_timer(void * p);

//
//void timer::impl_init()
//{
//
////   m_queue = nullptr;
////   m_timer = nullptr;
//
//}
//
//bool timer::impl_start()
//{
//
////   if(m_queue == nullptr)
////   {
////
////      m_queue = CreateDispatchQueue();
////
////      if (m_queue == nullptr)
////      {
////
////         return false;
////
////      }
////
////   }
////
////   m_timer = CreateDispatchTimer(m_dwMillis, MAX(1, m_dwMillis / 20), m_queue, apex_timer, this);
////
////   if (m_timer == nullptr)
////   {
////
////      return false;
////
////   }
//
//   return true;
//
//}
//
//void timer::impl_term()
//{
//
////   if (m_queue != nullptr)
////   {
////
////      ReleaseDispatch(m_queue);
////
////      m_queue = nullptr;
////
////   }
//
//}
//
//
//
//void timer::impl_stop()
//{
//
////   if (m_timer != nullptr)
////   {
////
////      CancelDispatchSource(m_timer);
////
////      ReleaseDispatch(m_timer);
////
////      m_timer = nullptr;
////
////   }
//
//}
//
//
//
//
//bool timer::impl_restart()
//{
//
//
////   m_timer = ResetDispatchTimer(m_timer, m_dwMillis, MAX(1, m_dwMillis / 20));
////
////   if (m_timer == nullptr)
////   {
////
////      return false;
////
////   }
//
//   return true;
//
//}
//
//
//


//
//void apex_timer(void * p)
//{
//
//   ::timer * ptimer = (::timer *)p;
//
//   ptimer->call_on_timer();
//
//}



