#pragma once

#define CA2_PALACE_SAFE_ZONE_BORDER_SIZE 32

struct CLASS_DECL_ACME plex     // warning ::payload length structure
{
   plex*                            pNext;
   // ::u8 data[maxNum*elementSize];

   void * data() { return ((::u8*)(this+1)) + CA2_PALACE_SAFE_ZONE_BORDER_SIZE; }

   static plex* create(plex*& head, uptr nMax, uptr cbElement);
         // like 'calloc' but no zero fill
         // may throw ::exception( memory exceptions

   void FreeDataChain();       // free this one and links
};

