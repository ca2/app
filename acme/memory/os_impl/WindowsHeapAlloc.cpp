extern HANDLE g_handleSystemHeap;

namespace acme
{

   class acme;

   extern acme* g_p;


} // namespace acme


void * os_impl_alloc(size_t size)
{

   critical_section_lock csl(::acme::g_p->system_heap_critical_section());

   return ::HeapAlloc(g_handleSystemHeap, 0, size);

}


void * os_impl_realloc(void * p, size_t size)
{

   critical_section_lock lock(::acme::g_p->system_heap_critical_section());

   return ::HeapReAlloc(g_handleSystemHeap, 0, p, size);

}


void os_impl_free(void * p)
{

   critical_section_lock lock(::acme::g_p->system_heap_critical_section());

   if (!::HeapFree(g_handleSystemHeap, 0, p))
   {

      DWORD dwError = ::GetLastError();

      ::output_debug_string("system_heap_free : Failed to free memory");

   }

}

size_t os_impl_size(void * p)
{

   critical_section_lock lock(::acme::g_p->system_heap_critical_section());

   SIZE_T s = ::HeapSize(g_handleSystemHeap, 0, p);

   if(s == (SIZE_T) -1)
   {

      ::output_debug_string("os_impl_size : Failed to get memory size_i32");

   }

   return s;

}



