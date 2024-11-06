// Refactored by camilo 2023-11-23 17:48 <3ThomasBorregaardSorensen!!
#pragma once



class CLASS_DECL_ACME plex_heap     // warning ::payload length structure
{
public:


   plex_heap *    m_pheapNext;
   unsigned char           m_data; // first data unsigned char of this ::payload length structure


   void * data() { return &m_data; }


   static plex_heap * create(plex_heap *& head, uptr nMax, uptr cbElement, ::heap::allocator * pallocator);


   void FreeDataChain(::heap::allocator * pallocator);


};


