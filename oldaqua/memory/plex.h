#pragma once

#define CA2_PALACE_SAFE_ZONE_BORDER_SIZE 32

struct CLASS_DECL_AQUA plex     // warning var length structure
{
   plex*                            pNext;
   // BYTE data[maxNum*elementSize];

   void * data() { return ((byte*)(this+1)) + CA2_PALACE_SAFE_ZONE_BORDER_SIZE; }

   static plex* create(plex*& head, uptr nMax, uptr cbElement);
         // like 'calloc' but no zero fill
         // may __throw( memory exceptions

   void FreeDataChain();       // free this one and links
};

