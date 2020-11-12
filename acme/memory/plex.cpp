#include "framework.h"

#include "plex_heap1.h"

#include "plex_heap_impl1.h"
#include "acme/platform/static_start.h"


#undef new



plex* plex::create(plex*& pHead, uptr nMax, uptr cbElement)
{

   memsize size = sizeof(plex) + nMax * cbElement + CA2_PALACE_SAFE_ZONE_BORDER_SIZE * 2;
   plex* point = (plex*) memory_alloc(size);
   // may __throw( exception
   point->pNext = pHead;
   pHead = point;  // change head (adds in reverse order for simplicity)
   return point;
}

void plex::FreeDataChain()     // free this one and links
{
   try
   {
      //plex* pPrevious = nullptr;
      plex* point = this;
      while (point != nullptr)
      {
         byte* bytes = (byte*) point;
         plex* pNextLocal = point->pNext;
         memory_free(bytes);
         //pPrevious = point;
         point = pNextLocal;
      }
   }
   catch(...)
   {
   }
}


