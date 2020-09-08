#pragma once


#if defined(__cplusplus)
extern "C" {
#endif


#pragma pack(push, heap_memory, 1)

   struct heap_padding
   {

      char m_sz[16];

   };

   struct  heap_memory
   {


      short                   m_back;
      byte                    m_blockuse;
      byte                    m_align;
      memsize                 m_size;
      struct heap_padding     m_padding;

   };


#pragma pack(pop, heap_memory)


   inline static struct heap_memory * heap_memory_get(void * pmemory)
   {

      return (struct heap_memory *)(((iptr)pmemory) - sizeof(struct heap_memory));

   }


   inline static memsize heap_memory_aligned_provision_get_size(memsize size, int iAlignByteCount)
   {

      return size + sizeof(struct heap_memory) + sizeof(struct heap_padding) + iAlignByteCount - 1;

   }


   inline static memsize heap_memory_unaligned_provision_get_size(memsize size)
   {

      return size + sizeof(struct heap_memory) + sizeof(struct heap_padding);

   }


   inline static void * heap_memory_unaligned(void * pbase, memsize size, i32 blockuse)
   {

      void * pmemory = (void *)((iptr)pbase + sizeof(struct heap_memory));

      struct heap_memory * pheap = heap_memory_get(pmemory);

      pheap->m_back = (i32)(((iptr)pmemory) - ((iptr)pbase));

      pheap->m_blockuse = blockuse;

      pheap->m_align = 0;

      pheap->m_size = size;

      return pmemory;

   }


   inline static void * heap_memory_aligned(void * pbase, memsize size, i32 blockuse, int iAlignByteCount)
   {

      void * pmemory = (void *)((((iptr)pbase) + sizeof(struct heap_memory) + iAlignByteCount - 1) & ((~((iptr)iAlignByteCount - 1))));

      struct heap_memory * pheap = heap_memory_get(pmemory);

      pheap->m_back = (i32)(((iptr)pmemory) - ((iptr)pbase));

      pheap->m_blockuse = blockuse;

      pheap->m_align = iAlignByteCount;

      pheap->m_size = size;

      return pmemory;

   }


   inline static void * heap_memory_base_get(void * pmemory)
   {

      return (void *)(((iptr)pmemory) - heap_memory_get(pmemory)->m_back);

   }


   inline static i32 heap_memory_get_block_use(void * pmemory)
   {

      return heap_memory_get(pmemory)->m_blockuse;

   }


   inline static byte heap_memory_get_align(void * pmemory)
   {

      return heap_memory_get(pmemory)->m_align;

   }


   inline static memsize heap_memory_get_size(void * pmemory)
   {

      return heap_memory_get(pmemory)->m_size;

   }


   inline static void heap_memory_check_padding_after(struct heap_memory * pheapmemory)
   {

      struct heap_padding * ppadding = (struct heap_padding *)(((byte *)&pheapmemory->m_padding) + sizeof(struct heap_padding) + pheapmemory->m_size);

      for (int i = 0; i < sizeof(struct heap_padding); i++)
      {

         if (ppadding->m_sz[i] != 0)
         {

            //            ::output_debug_string("*&!@");

         }

      }

   }


   typedef void * MEMORY_ALLOC(memsize s);

   typedef MEMORY_ALLOC * PFN_MEMORY_ALLOC;



   typedef void * MEMORY_REALLOC(void * p, memsize s);

   typedef MEMORY_REALLOC * PFN_MEMORY_REALLOC;



   typedef void MEMORY_FREE(void * p);

   typedef MEMORY_FREE * PFN_MEMORY_FREE;



   typedef memsize MEMORY_SIZE(void *);

   typedef MEMORY_SIZE * PFN_MEMORY_SIZE;





   //CLASS_DECL_AQUA void * ace_memory_alloc(memsize s);
   //CLASS_DECL_AQUA void * ace_memory_realloc(void * p, memsize s);
   //CLASS_DECL_AQUA void    ace_memory_free(void * p);
   //CLASS_DECL_AQUA memsize  ace_memory_size(void * p);



   //CLASS_DECL_AQUA void  ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize);



   // CLASS_DECL_EXPORT void nodeos_set_cache_dir(const char * pszDir);

   // CLASS_DECL_EXPORT const char * nodeos_get_cache_dir(void);

   // CLASS_DECL_EXPORT void nodeos_set_home(const char * pszDir);

   // CLASS_DECL_EXPORT const char * nodeos_get_home(void);

   // CLASS_DECL_EXPORT void nodeos_set_temp(const char * pszDir);

   // CLASS_DECL_EXPORT const char * nodeos_get_temp(void);





#if defined(__cplusplus)
} // extern "C"
#endif


