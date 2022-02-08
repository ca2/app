#include "framework.h"
#include "acme/operating_system/_c.h"
#include "acme/operating_system/_os.h"


#ifdef LINUX
#include "acme/operating_system/ansi/_ansi.h"
#endif


synchronization_result::synchronization_result(u32 value, ::count objectCount)
{

   switch ( value )
   {
   case WAIT_FAILED:

      m_eresult = result_error;
      break;

   case WAIT_TIMEOUT:

      m_eresult = result_timeout;

      break;

   default:

      if (value>=WAIT_ABANDONED_0 && value<=(WAIT_ABANDONED_0 + objectCount - 1))
         m_iEvent = (::index)result_abandon0-((::index)value-WAIT_ABANDONED_0);
      else if (/*value>=WAIT_OBJECT_0 &&*/ value<=(WAIT_OBJECT_0 + objectCount - 1))
         m_iEvent = (::index)result_event0+((::index)value-WAIT_OBJECT_0);
      break;

   }

}





