#include "framework.h"


#include "acme/_operating_system.h"


#pragma warning(disable : 4074)
//#pragma init_seg(".CRT$XCA1")
#pragma init_seg(compiler)


class WindowsHeapAlloc
{
public:


   HANDLE                  m_handle;
   ::critical_section      m_criticalsection;


   WindowsHeapAlloc()
   {

      m_handle = ::HeapCreate(0, 0, 0);

   }


} g_windowsheapalloc;


void* operating_system_memory_allocate(memsize size)
{

   raw_critical_section_lock criticalsectionlock(&g_windowsheapalloc.m_criticalsection);

   return ::HeapAlloc(g_windowsheapalloc.m_handle, 0, size);

}


void* operating_system_memory_reallocate(void* p, memsize size)
{

   raw_critical_section_lock criticalsectionlock(&g_windowsheapalloc.m_criticalsection);

   return ::HeapReAlloc(g_windowsheapalloc.m_handle, 0, p, size);

}


void operating_system_memory_free(void* p)
{

   raw_critical_section_lock criticalsectionlock(&g_windowsheapalloc.m_criticalsection);

   if (!::HeapFree(g_windowsheapalloc.m_handle, 0, p))
   {

      DWORD dwError = ::GetLastError();

      ::information("system_heap_free : Failed to free memory");

   }

}


memsize operating_system_memory_size(void* p)
{

   raw_critical_section_lock criticalsectionlock(&g_windowsheapalloc.m_criticalsection);

   SIZE_T s = ::HeapSize(g_windowsheapalloc.m_handle, 0, p);

   if (s == (SIZE_T)-1)
   {

      ::information("os_impl_size : Failed to get memory size_i32");

   }

   return s;

}



