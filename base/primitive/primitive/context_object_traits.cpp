#include "framework.h"


//::estatus context_object::call(::trait & trait)
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
//::estatus context_object::run(::trait &)
//{
//
//   return ::success;
//
//}



//void context_object::notify(::u64 uId)
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
//::thread_pointer context_object::_fork_notify(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify(ptrait);
//
//}
//
//
//thread_spa context_object::_fork_notify_each(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify_each(ptrait);
//
//}
//
//
//void context_object::_notify(::trait * ptrait)
//{
//
//   m_ptraits->_notify(ptrait);
//
//}
//
//
//void context_object::_call_notify(::trait * ptrait)
//{
//
//   m_ptraits->_call_notify(ptrait);
//
//}
//

//void context_object::set_trait_result(::u64 uId, ::u64 uPromisse, ::context_object * preference)
//{
//
//   m_ptraits->set_result(uId, uPromisse, preference);
//
//}




