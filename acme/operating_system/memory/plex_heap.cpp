// Refactored by camilo 2023-11-23 17:48 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "plex_heap.h"

iptr g_iMonitor = 0;


CLASS_DECL_ACME void monitor_pointer(void * p)
{

   g_iMonitor = (iptr)p;

}




plex_heap * plex_heap::create(plex_heap *& pheapHead, uptr nMax, uptr cbElement, ::heap::allocator * pallocator)
{

   ASSERT(nMax > 0 && cbElement > 0);

   if (nMax == 0 || cbElement == 0)
   {

      throw_exception(error_bad_argument);

   }

   auto pheap = (plex_heap *)pallocator->allocate(sizeof(plex_heap) + nMax * cbElement, nullptr);

   if ((iptr)pheap > g_iMonitor - 8192 && (iptr)pheap < g_iMonitor + 8192)
   {

      output_debug_string("MAKING FREE");

   }

#ifdef XXDEBUG

   Alloc_check_pointer_in_cpp(pheap);

#endif // XXDEBUG

   pheap->m_pheapNext = pheapHead;

   pheapHead = pheap;

   return pheap;

}


void plex_heap::FreeDataChain(::heap::allocator * pallocator)     // free this one and links
{

   plex_heap * pheap = this;

   while (::is_set(pheap))
   {

      ::u8 * pbytes = (::u8 *)pheap;

      auto pheapNext = pheap->m_pheapNext;

      pallocator->free(pbytes);

      pheap = pheapNext;

   }

}



