#include "framework.h"


//::estatus elemental::call(::trait & trait)
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
//::estatus elemental::run(::trait &)
//{
//
//   return ::success;
//
//}



//void elemental::notify(::u64 uId)
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
//::thread_pointer elemental::_fork_notify(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify(ptrait);
//
//}
//
//
//thread_spa elemental::_fork_notify_each(__pointer(::trait) ptrait)
//{
//
//   return m_ptraits->_fork_notify_each(ptrait);
//
//}
//
//
//void elemental::_notify(::trait * ptrait)
//{
//
//   m_ptraits->_notify(ptrait);
//
//}
//
//
//void elemental::_call_notify(::trait * ptrait)
//{
//
//   m_ptraits->_call_notify(ptrait);
//
//}
//

//void elemental::set_trait_result(::u64 uId, ::u64 uPromisse, ::elemental * preference)
//{
//
//   m_ptraits->set_result(uId, uPromisse, preference);
//
//}




