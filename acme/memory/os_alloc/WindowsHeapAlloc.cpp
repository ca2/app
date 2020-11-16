




void * os_impl_alloc(size_t size)
{

   cslock csl(g_pmutexSystemHeap);

   return ::HeapAlloc(g_system_heap(), 0, size);

}


void * os_impl_realloc(void * p, size_t size)
{

   cslock lock(g_pmutexSystemHeap);

   return ::HeapReAlloc(g_system_heap(), 0, p, size);

}


void os_impl_free(void * p)
{

   cslock lock(g_pmutexSystemHeap);

   if (!::HeapFree(g_system_heap(), 0, p))
   {

      DWORD dwError = ::GetLastError();

      ::output_debug_string("system_heap_free : Failed to free memory");

   }

}

size_t os_impl_size(void * p)
{

   cslock lock(g_pmutexSystemHeap);

   SIZE_T s = ::HeapSize(g_system_heap(), 0, p);

   if(s == (SIZE_T) -1)
   {

      ::output_debug_string("os_impl_size : Failed to get memory size");

   }

   return s;

}




