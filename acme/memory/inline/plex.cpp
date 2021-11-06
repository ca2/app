#include "framework.h"
#include "acme/operating_system.h"

//#include "plex_heap1.h"

//#include "plex_heap_impl1.h"
//#include "acme/platform/static_start.h"


#undef new



plex* plex::create(plex*& pHead, uptr nMax, uptr cbElement)
{

   memsize size = sizeof(plex) + nMax * cbElement + CA2_PALACE_SAFE_ZONE_BORDER_SIZE * 2;
   plex* p = (plex*) memory_allocate(size);
   // may __throw( exception
   p->pNext = pHead;
   pHead = p;  // machine head (adds in reverse order for simplicity)
   return p;
}

void plex::FreeDataChain()     // free this one and links
{
   try
   {
      //plex* pPrevious = nullptr;
      plex* p = this;
      while (p != nullptr)
      {
         byte* bytes = (byte*) p;
         plex* pNextLocal = p->pNext;
         memory_free(bytes);
         //pPrevious = p;
         p = pNextLocal;
      }
   }
   catch(...)
   {
   }
}


