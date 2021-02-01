#include "framework.h"
#include "acme/operating_system.h"


namespace windows
{


   critical_section::critical_section()
   {

      if (!::InitializeCriticalSectionEx(&m_criticalsection, 4000, 0))
      {

         __throw(resource_exception);

      }

   }


   critical_section::~critical_section()
   {
      
      ::DeleteCriticalSection(&m_criticalsection);

   }


   void critical_section::lock()
   {

      ::EnterCriticalSection(&m_criticalsection);

   }


   void critical_section::unlock()
   {

      ::LeaveCriticalSection(&m_criticalsection);

   }


} // namespace windows



