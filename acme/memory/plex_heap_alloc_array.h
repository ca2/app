#pragma once


class plex_heap_alloc;


class CLASS_DECL_ACME plex_heap_alloc_array :
   public array_non_particle < plex_heap_alloc *, plex_heap_alloc *, ::typed::def < plex_heap_alloc*  >, ::heap::operating_system_typed_memory < plex_heap_alloc * > >
{
public:


   ::heap::allocator * m_pallocator;
   ::heap::enum_memory m_ememory;


   plex_heap_alloc_array(::heap::allocator * pallocator, ::heap::enum_memory ememory);
   ~plex_heap_alloc_array();


   plex_heap_alloc * find(memsize nAllocSize);


   void * _alloc(memsize size, memsize * psizeAllocated);
   void * _realloc(void * p, memsize nAllocSize, memsize nOldAllocSize, int align);
   void _free(void * p, memsize nAllocSize);

   void pre_finalize();

   void * alloc_debug(memsize nAllocSize, memsize * psizeAllocated, int nBlockUse, const_char_pointer  szFileName, int iLine);
   void * realloc_debug(void * p, memsize nAllocSize, memsize nOldAllocSize, int align, int nBlockUse, const_char_pointer  szFileName, int iLine);
   void free_debug(void * p, memsize nAllocSize);

   //static plex_heap_alloc_array * new_plex_heap_alloc_array(::heap::allocator * pallocator, ::heap::enum_memory ememory);

   //static void delete_plex_heap_alloc_array(plex_heap_alloc_array * p);


   //plex_heap_alloc * new_plex_heap_alloc(memsize nAllocSize, unsigned int nBlockSize = 64);
   //void delete_plex_heap_alloc(plex_heap_alloc * pplexheapalloc);


};






