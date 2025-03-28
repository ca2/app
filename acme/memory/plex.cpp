#include "framework.h"
#include "plex.h"


plex* plex::create(plex*& pHead, uptr nMax, uptr cbElement, ::heap::allocator * pallocator)
{

   memsize size = sizeof(plex) + nMax * cbElement + CA2_PALACE_SAFE_ZONE_BORDER_SIZE * 2;
   plex* p = (plex*) pallocator->allocate(size, nullptr);
   // may throw ::exception( exception
   p->pNext = pHead;
   pHead = p;  // machine head (adds in reverse order for simplicity)
   return p;
}

void plex::FreeDataChain(::heap::allocator * pallocator)     // free this one and links
{
   try
   {
      //plex* pPrevious = nullptr;
      plex* p = this;
      while (p != nullptr)
      {
         unsigned char* bytes = (unsigned char*) p;
         plex* pNextLocal = p->pNext;
         pallocator->free(bytes);
         //pPrevious = p;
         p = pNextLocal;
      }
   }
   catch(...)
   {
   }
}


