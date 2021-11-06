#include "framework.h"
#include "acme/operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


#ifdef LINUX
#include "acme/node/operating_system/ansi/_ansi.h"
#endif


//synchronization_result::synchronization_result(u32 value, ::count objectCount)
//{
//
//   switch ( value )
//   {
//   case WAIT_FAILED:
//
//      m_esynchronizationresult = e_synchronization_result_error;
//      break;
//
//   case WAIT_TIMEOUT:
//
//      m_esynchronizationresult = e_synchronization_result_timed_out;
//
//      break;
//
//   default:
//
//      if (value>=WAIT_ABANDONED_0 && value<=(WAIT_ABANDONED_0 + objectCount - 1))
//         m_iEvent = (::index)result_abandon0-((::index)value-WAIT_ABANDONED_0);
//      else if (/*value>=WAIT_OBJECT_0 &&*/ value<=(WAIT_OBJECT_0 + objectCount - 1))
//         m_iEvent = (::index)result_event0+((::index)value-WAIT_OBJECT_0);
//      break;
//
//   }
//
//}





