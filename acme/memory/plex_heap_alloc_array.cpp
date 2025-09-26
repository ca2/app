#include "framework.h"
#include "allocator.h"
#include "align_byte_count.h"
#include "plex_heap_alloc.h"
#include "plex_heap_alloc_array.h"


plex_heap_alloc_array::plex_heap_alloc_array(heap::allocator * pallocator, ::heap::enum_memory ememory) :
   m_pallocator(pallocator),
   m_ememory(ememory)
{

   //disable_referencing_debugging();

   add(__raw_new plex_heap_alloc(m_pallocator, 32, 256));
   add(__raw_new plex_heap_alloc(m_pallocator, 64, 128));
   add(__raw_new plex_heap_alloc(m_pallocator, 128, 128));
   add(__raw_new plex_heap_alloc(m_pallocator, 256, 128));
   add(__raw_new plex_heap_alloc(m_pallocator, 512, 64));
   add(__raw_new plex_heap_alloc(m_pallocator, 1_KiB, 64));
   add(__raw_new plex_heap_alloc(m_pallocator, 2_KiB, 32));
   add(__raw_new plex_heap_alloc(m_pallocator, 4_KiB, 32));
   add(__raw_new plex_heap_alloc(m_pallocator, 8_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 16_KiB, 16));

#if !MOBILE_PLATFORM

   add(__raw_new plex_heap_alloc(m_pallocator, 24_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 32_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 48_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 64_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 128_KiB, 16));
   add(__raw_new plex_heap_alloc(m_pallocator, 256_KiB, 8));
   add(__raw_new plex_heap_alloc(m_pallocator, 512_KiB, 8));
   add(__raw_new plex_heap_alloc(m_pallocator, 1_MiB, 4));



#if OSBIT > 32

   add(__raw_new plex_heap_alloc(m_pallocator, 2_MiB, 2));
   add(__raw_new plex_heap_alloc(m_pallocator, 4_MiB, 2));
   add(__raw_new plex_heap_alloc(m_pallocator, 8_MiB, 2));
   add(__raw_new plex_heap_alloc(m_pallocator, 16_MiB, 2));

#endif

#endif

}


plex_heap_alloc_array::~plex_heap_alloc_array()
{

   pre_finalize();

   for (::collection::index i = this->get_upper_bound(); i >= 0; i--)
   {

      //::platform::allocator::__allocator_base_delete(m_pallocator, this->element_at(i));

      delete this->element_at(i);

   }

   erase_all();

   //if (g_pheap == this)
   //{

   //   g_pheap = nullptr;

   //}

}

void plex_heap_alloc_array::pre_finalize()
{

   for (::collection::index i = this->get_upper_bound(); i >= 0; i--)
   {

      this->element_at(i)->pre_finalize();

   }

}



void * plex_heap_alloc_array::alloc_debug(memsize size, memsize * psizeAllocated, int nBlockUse, const_char_pointer pszFileName, int iLine)
{

#if LAST_MEM_FILE_AND_LINE

   string str;

   str.formatf("%s(%d)", pszFileName, iLine);

   memsize nAllocSize = size + sizeof(memsize) + 128;

   plex_heap_alloc * palloc = find(nAllocSize);

   memsize * psize = nullptr;

   if (palloc != nullptr)
   {

      psize(memsize *) palloc->Alloc();

      psize[0] = nAllocSize;

   }
   else
   {

      psize = (memsize *) ::system_heap_alloc(nAllocSize);

      psize[0] = 0;

   }

   ansi_count_copy((char *)&psize1], str->Mid(maximum(0, str->get_length() - 124)), 124);

   return ((unsigned char *)&psize[1]) + 128;

#else

   return _alloc(size, psizeAllocated);

#endif

}


void plex_heap_alloc_array::free_debug(void * p, memsize size)
{

#if LAST_MEM_FILE_AND_LINE

   memsize * psize = &((memsize *)((unsigned char *)pvoid) - 128))[-1];

   if (*psize == 0)
   {

      return ::system_heap_free(psize);

   }

   plex_heap_alloc * palloc = find(*psize);

   if (palloc != nullptr)
   {

      return palloc->Free(psize);

   }
   else
   {

      return ::system_heap_free(psize);

   }

#else

   return _free(p, size);

#endif

}


void * plex_heap_alloc_array::realloc_debug(void * p, memsize size, memsize sizeOld, int align, int nBlockUse, const_char_pointer pszFileName, int iLine)
{

#if LAST_MEM_FILE_AND_LINE

   string str;

   str.formatf("%s(%d)", szFileName, iLine);

   memsize * psize = (memsize *)realloc(&((memsize *)(((unsigned char *)pvoidOld) - 128))[-1], ((memsize *)(((unsigned char *)pvoidOld) - 128))[-1], size + sizeof(memsize) + 128);

   psize[0] = size + sizeof(memsize) + 128;

   ansi_count_copy((char *)&psize1], str->Mid(maximum(0, str->get_length() - 124)), 124);

   return ((unsigned char *)&psize[1]) + 128;

#else

   return _realloc(p, size, sizeOld, align);

#endif

}


void * plex_heap_alloc_array::_realloc(void * p, memsize size, memsize sizeOld, int align)
{

   plex_heap_alloc * pallocOld = find(sizeOld);

   plex_heap_alloc * pallocNew = find(size);

   char * pNew = nullptr;

   if (pallocOld == nullptr && pallocNew == nullptr && align == 0)
   {

      pNew = (char *)m_pallocator->reallocate(p, size);

      if (size > sizeOld)
      {

         auto pZero = pNew + sizeOld;

         memory_set(pZero, 0, size - sizeOld);

      }

   }
   else if (pallocOld != NULL && pallocOld == pallocNew)
   {

      pNew = (char *)p;

   }
   else
   {

      if (pallocNew != nullptr)
      {

         pNew = (char *)pallocNew->Alloc();

      }
      else
      {

         pNew = (char *)m_pallocator->allocate(size, nullptr);

      }

#if !MEMDLEAK
      if (align > 0)
      {

         memsize oldSize = sizeOld - heap_memory_aligned_provision_get_size(0, ALIGN_BYTE_COUNT);

         memsize newSize = size - heap_memory_aligned_provision_get_size(0, ALIGN_BYTE_COUNT);

         ::memory_copy(heap_memory_aligned(pNew, newSize, 0, ALIGN_BYTE_COUNT, m_ememory),
                heap_memory_aligned(p, oldSize, 0, ALIGN_BYTE_COUNT, m_ememory),
                minimum(oldSize, newSize));

      }
      else
#endif
      {

         ::memory_copy(pNew, p, minimum(sizeOld, size));

      }

      if (pallocOld != nullptr)
      {

         pallocOld->Free(p);

      }
      else
      {

         m_pallocator->free(p);

      }

   }

   return pNew;

}



//plex_heap_alloc * plex_heap_alloc_array::new_plex_heap_alloc(memsize nAllocSize, unsigned int nBlockSize)
//{
//
//   auto palloc = (plex_heap_alloc*) m_pallocator->øallocate plex_heap_alloc(nAllocSize, nBlockSize);
//
//   return palloc;
//
//}
//
//
//void plex_heap_alloc_array::delete_plex_heap_alloc(plex_heap_alloc * pplexheapalloc)
//{
//
//   pplexheapalloc->~plex_heap_alloc();
//
//   m_pallocator->free(pplexheapalloc);
//
//}



//plex_heap_alloc_array * plex_heap_alloc_array::new_plex_heap_alloc_array(::heap::allocator * pallocator, ::heap::enum_memory ememory)
//{
//
//   auto pallocarray = ::platform::raw_allocator::__allocator_base_allocate< plex_heap_alloc_array > (pallocator, pallocator, ememory);
//
//   //::new(pallocarray) ::plex_heap_alloc_array(pallocator, ememory);
//
//   //::task_on_after_new_particle(pallocarray);
//
//   return pallocarray;
//
//}
//
//void plex_heap_alloc_array::delete_plex_heap_alloc_array(plex_heap_alloc_array * p)
//{
//
//   auto pallocator = p->m_pallocator;
//
//   p->~plex_heap_alloc_array();
//
//   pallocator->free(p);
//
//}


plex_heap_alloc * plex_heap_alloc_array::find(memsize nAllocSize)
{

   for (auto p = m_begin; p < m_end; p++)
   {

      auto palloc = *p;

      if (nAllocSize <= palloc->m_iAllocSize)
      {

         if (palloc->m_iAllocSize == 16384)
         {

            //::informationf(".");

         }

         return palloc;

      }

   }

   return nullptr;

}


void * plex_heap_alloc_array::_alloc(memsize size, memsize * psizeAllocated)
{

   plex_heap_alloc * palloc = find(size);

   if (palloc != nullptr)
   {

      m_pallocator->m_pacme->heap()->on_plex_heap_alloc(palloc);

      auto p = palloc->Alloc();

      if (psizeAllocated)
      {

         *psizeAllocated = palloc->m_iAllocSize;

      }

      return p;

   }
   else
   {

      m_pallocator->m_pacme->heap()->on_system_heap_alloc(size);

      return m_pallocator->allocate(size, psizeAllocated);

   }

}


void free_foo();


void plex_heap_alloc_array::_free(void * p, memsize size)
{

   plex_heap_alloc * palloc = find(size);

   if (palloc != nullptr)
   {

      ASSERT(size <= palloc->m_iAllocSize);

      if (palloc->m_iAllocSize == 256)
      {

         free_foo();

      }

      return palloc->Free(p);

   }
   else
   {

      return m_pallocator->free(p);

   }

}




