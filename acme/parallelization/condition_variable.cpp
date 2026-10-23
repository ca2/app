#include "platform.h"
#include "condition_variable.h"
#include "acme/_operating_system.h"


#ifdef WINDOWS

#ifdef __REACTOS__

struct condition_variable::state
{
   struct waiter
   {
      HANDLE event;
      waiter * next;
   };

   CRITICAL_SECTION lock;
   waiter * first;
};

condition_variable::condition_variable()
{
   m_pstate = static_cast<state *>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(state)));
   if (!m_pstate)
      throw ::exception(error_resource);

   if (!InitializeCriticalSectionAndSpinCount(&m_pstate->lock, 0))
   {
      HeapFree(GetProcessHeap(), 0, m_pstate);
      throw ::exception(error_resource);
   }
}

condition_variable::~condition_variable()
{
   // As with native condition variables, all waiters must finish before destruction.
   DeleteCriticalSection(&m_pstate->lock);
   HeapFree(GetProcessHeap(), 0, m_pstate);
}

bool condition_variable::wake_all()
{
   bool succeeded = true;
   EnterCriticalSection(&m_pstate->lock);
   for (auto waiter = m_pstate->first; waiter; waiter = waiter->next)
      if (!SetEvent(waiter->event))
         succeeded = false;
   LeaveCriticalSection(&m_pstate->lock);
   return succeeded;
}

bool condition_variable::wait(unsigned long timeout)
{
   state::waiter waiter{CreateEventW(nullptr, FALSE, FALSE, nullptr), nullptr};
   if (!waiter.event)
      return false;

   EnterCriticalSection(&m_pstate->lock);
   waiter.next = m_pstate->first;
   m_pstate->first = &waiter;
   LeaveCriticalSection(&m_pstate->lock);

   const auto result = WaitForSingleObject(waiter.event, timeout);
   const auto error = result == WAIT_TIMEOUT ? ERROR_TIMEOUT : GetLastError();

   // Unregister under the broadcast lock before closing the event or leaving scope.
   EnterCriticalSection(&m_pstate->lock);
   auto link = &m_pstate->first;
   while (*link != &waiter)
      link = &(*link)->next;
   *link = waiter.next;
   LeaveCriticalSection(&m_pstate->lock);
   CloseHandle(waiter.event);

   if (result != WAIT_OBJECT_0)
      SetLastError(error);
   return result == WAIT_OBJECT_0;
}

#else


//condition_variable

condition_variable::construct * condition_variable::s_pconstruct = (condition_variable::construct *)&::InitializeConditionVariable;
//static destruct * s_pdestruct;

#endif


#endif



