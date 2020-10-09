#include "framework.h"


//::estatus element::call(::trait & trait)
//{
//
//   ::estatus estatus = error_failed;
//
//   try
//   {
//
//      estatus = run(trait);
//
//   }
//   catch (::exception_pointer e)
//   {
//
//      estatus = e->m_estatus;
//
//   }
//   catch (...)
//   {
//
//      estatus = error_exception;
//
//   }
//
//   return estatus;
//
//}
//
//
//::estatus element::run(::trait &)
//{
//
//   return ::success;
//
//}



//void element::notify(::u64 uId)
//{
//
//   if (m_ptraits)
//   {
//
//      m_ptraits->notify(uId);
//
//   }
//   else
//   {
//
//      m_uid |= uId;
//
//   }
//
//}
//
//
//::thread_pointer element::_fork_notify(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify(ptrait);
//
//}
//
//
//thread_spa element::_fork_notify_each(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify_each(ptrait);
//
//}
//
//
//void element::_notify(::trait * ptrait)
//{
//
//   m_ptraits->_notify(ptrait);
//
//}
//
//
//void element::_call_notify(::trait * ptrait)
//{
//
//   m_ptraits->_call_notify(ptrait);
//
//}
//

//void element::set_trait_result(::u64 uId, ::u64 uPromisse, ::element * preference)
//{
//
//   m_ptraits->set_result(uId, uPromisse, preference);
//
//}




