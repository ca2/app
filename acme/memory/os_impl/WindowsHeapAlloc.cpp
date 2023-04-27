extern HANDLE g_handleSystemHeap;


::critical_section* critical_section_system_heap()
{

   static ::critical_section g_criticalsectionSystemHeap;

   return &g_criticalsectionSystemHeap;

}


void * os_impl_alloc(size_t size)
{

   critical_section_lock criticalsectionlock(critical_section_system_heap());

   return ::HeapAlloc(g_handleSystemHeap, 0, size);

}


void * os_impl_realloc(void * p, size_t size)
{

   critical_section_lock criticalsectionlock(critical_section_system_heap());

   return ::HeapReAlloc(g_handleSystemHeap, 0, p, size);

}


void os_impl_free(void * p)
{

   critical_section_lock criticalsectionlock(critical_section_system_heap());

   if (!::HeapFree(g_handleSystemHeap, 0, p))
   {

      DWORD dwError = ::GetLastError();

      ::output_debug_string("system_heap_free : Failed to free memory");

   }

}

size_t os_impl_size(void * p)
{

   critical_section_lock criticalsectionlock(critical_section_system_heap());

   SIZE_T s = ::HeapSize(g_handleSystemHeap, 0, p);

   if(s == (SIZE_T) -1)
   {

      ::output_debug_string("os_impl_size : Failed to get memory size_i32");

   }

   return s;

}



