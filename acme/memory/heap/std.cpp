#include "framework.h"


#if !defined(MCHECK) && !defined(_VLD) && !defined(__MCRTDBG) && !MEMDLEAK
#include "acme/memory/align_byte_count.h"
#include "acme/memory/c_malloc.h"
#include "acme/memory/plex_heap_alloc_array.h"
#include "acme/memory/heap.h"
#include "acme/memory/heap_memory.h"


namespace heap
{


   class std_heap :
      virtual public heap
   {
   protected:
      friend class ::c::malloc;
      std_heap() {}
      ~std_heap() {}
   public:


      plex_heap_alloc_array * m_pallocarray = nullptr;





      void initialize_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory) override
      {

         heap::heap::initialize_heap(pallocator, ememory);

      }


      void start_heap() override
      {

         m_pallocarray = ::platform::allocator::__allocator_base_new < plex_heap_alloc_array >(m_pallocator, m_pallocator, m_ememory);

      }


      void * aligned_allocate(memsize size, memsize align, const char * pszAnnotation = nullptr) override
      {

         if (size < 0)
         {

            throw_exception(::error_bad_argument, "Bad Argument: Negative amount of memory to allocate");

         }

         void * paligned;

         align = align <= 0 ? ALIGN_BYTE_COUNT : align;

         auto sizeProvision = heap_memory_aligned_provision_get_size(size, (int)align);

         if (m_pallocarray == nullptr)
         {

            //void * p = system_heap_alloc(sizeProvision);

            void * p = ::malloc(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            paligned = heap_memory_aligned(p, size, 128, (int)align, m_ememory, pszAnnotation);

         }
         else
         {

            void * p = m_pallocarray->_alloc(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            paligned = heap_memory_aligned(p, size, 0, (int)align, m_ememory, pszAnnotation);

         }

         return paligned;

      }


      void * unaligned_allocate(memsize size, const char * pszAnnotation = nullptr) override
      {

         void * punaligned;

#if defined(__APPLE__) || defined(LINUX)

         punaligned = aligned_allocate(size, ALIGN_BYTE_COUNT, pszAnnotation);

#else

         auto sizeProvision = heap_memory_unaligned_provision_get_size(size);

         if (m_pallocarray == nullptr)
         {

            //void* p = system_heap_alloc(sizeProvision);

            void * p = ::malloc(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            punaligned = heap_memory_unaligned(p, size, 129, m_ememory, pszAnnotation);

         }
         else
         {

            void * p = m_pallocarray->_alloc(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            punaligned = heap_memory_unaligned(p, size, 1, m_ememory, pszAnnotation);

         }

#endif

         return punaligned;

      }


      void * aligned_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align, const char * pszAnnotation = nullptr) override
      {

         void * paligned;

         UNREFERENCED_PARAMETER(nBlockUse);
         UNREFERENCED_PARAMETER(szFileName);
         UNREFERENCED_PARAMETER(nLine);

         align = align <= 0 ? ALIGN_BYTE_COUNT : align;

         auto sizeProvision = heap_memory_aligned_provision_get_size(size, (int)align);

         //TODO: to do the dbg version
         //::u8 * p = (::u8 *) _system_heap_alloc_debug(nSize + ALIGN_BYTE_COUNT + 32, nBlockUse, szFileName, nLine);
         if (m_pallocarray == nullptr)
         {

            void * p = m_pallocator->allocate(sizeProvision, pszAnnotation);

            if (p == nullptr)
            {

               return nullptr;

            }

            paligned = heap_memory_aligned(p, size, 130, (int)align, m_ememory, pszAnnotation);

            memory_set(paligned, 0, size);

         }
         else
         {

            void * p = m_pallocarray->alloc_debug(sizeProvision, nBlockUse, szFileName, nLine);

            if (p == nullptr)
            {

               return nullptr;

            }

            paligned = heap_memory_aligned(p, size, 2, (int)align, m_ememory, pszAnnotation);

         }

         return paligned;

      }


      void * unaligned_allocate_debug(memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation = nullptr) override
      {

         void * punaligned;

#if defined(__APPLE__) || defined(LINUX)

         punaligned = aligned_allocate(size, ALIGN_BYTE_COUNT, pszAnnotation);

#else

         auto sizeProvision = heap_memory_unaligned_provision_get_size(size);

         if (m_pallocarray == nullptr)
         {

            void * p = m_pallocator->allocate(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            punaligned = heap_memory_unaligned(p, size, 131, m_ememory, pszAnnotation);

         }
         else
         {

            void * p = m_pallocarray->_alloc(sizeProvision);

            if (p == nullptr)
            {

               return nullptr;

            }

            punaligned = heap_memory_unaligned(p, size, 3, m_ememory, pszAnnotation);

         }

#endif

         return punaligned;


      }


      //#undef ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate


      void * allocate(memsize size, const char * pszAnnotation = nullptr) override
      {

         return aligned_allocate(size, ALIGN_BYTE_COUNT, pszAnnotation);

      }


      void * allocate_no_track(memsize size)
      {

         //#if defined(__APPLE__) || defined(RASPBERRYPIOS)

         return aligned_allocate(size, ALIGN_BYTE_COUNT);

         //#else

         //   return unaligned_memory_allocate(size);

         //#endif

      }


      void * count_allocate(memsize size, memsize bytes, const char * pszAnnotation = nullptr) override
      {

         return allocate(size * bytes, pszAnnotation);

      }


      void * allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation = nullptr) override
      {

         // return unaligned_memory_allocate_debug(nSize, nBlockUse, szFileName, nLine);

         return aligned_allocate_debug(nSize, nBlockUse, szFileName, nLine, ALIGN_BYTE_COUNT, pszAnnotation);

      }


      void * reallocate(void * pmemory, memsize nSize, const char * pszAnnotation = nullptr) override
      {

         return reallocate_debug(pmemory, nSize, 0, nullptr, -1, pszAnnotation);

      }


      void * reallocate_debug(void * pmemory, memsize size, i32 nBlockUse, const char * szFileName, i32 nLine, const char * pszAnnotation = nullptr) override
      {

         if (pmemory == nullptr)
         {

            return allocate_debug(size, nBlockUse, szFileName, nLine, pszAnnotation);

         }

         heap_memory * pheapmemory = heap_memory_get(pmemory);

         if (pheapmemory->m_ememory != m_ememory)
         {

            throw "todo";

            //return manage_memory_reallocate(pheapmemory->m_ememory, pmemory, size);

         }

         ::u8 blockuse = pheapmemory->m_blockuse;

         memsize sizeOld = pheapmemory->m_size;

         ::u8 align = pheapmemory->m_align;

         void * p = heap_memory_base_get(pmemory);

         if (blockuse == 0) // aligned
         {

            p = m_pallocarray->_realloc(
               p,
               heap_memory_aligned_provision_get_size(size, align),
               heap_memory_aligned_provision_get_size(sizeOld, align),
               align);

         }
         else if (blockuse == 1) // unaligned
         {

            //TODO: to do the dbg version

            p = m_pallocarray->_realloc(
               p,
               heap_memory_unaligned_provision_get_size(size),
               heap_memory_unaligned_provision_get_size(sizeOld),
               0);

         }
         else if (blockuse == 128) // aligned
         {

            //p = system_heap_realloc(
              // p,
               //(size_t)heap_memory_aligned_provision_get_size(size, align));
            p = ::realloc(
                  p,
                  (size_t)heap_memory_aligned_provision_get_size(size, align));

         }
         else if (blockuse == 129) // unaligned
         {

            //TODO: to do the dbg version

            //p = system_heap_realloc(
            //   p,
            //   (size_t)heap_memory_unaligned_provision_get_size(size));
            p = ::realloc(
               p,
               (size_t)heap_memory_unaligned_provision_get_size(size));

         }
         else if (blockuse == 2) // aligned
         {

            p = m_pallocarray->realloc_debug(
               p,
               heap_memory_aligned_provision_get_size(size, align),
               heap_memory_aligned_provision_get_size(sizeOld, align),
               align, nBlockUse, szFileName, nLine);

         }
         else if (blockuse == 3) // unaligned
         {

            //TODO: to do the dbg version

            p = m_pallocarray->realloc_debug(
               p,
               heap_memory_unaligned_provision_get_size(size),
               heap_memory_unaligned_provision_get_size(sizeOld),
               0, nBlockUse, szFileName, nLine);

         }
         else if (blockuse == 130) // aligned
         {

            p = m_pallocator->reallocate(
               p,
               (size_t)heap_memory_aligned_provision_get_size(size, align));

         }
         else if (blockuse == 131) // unaligned
         {

            //TODO: to do the dbg version

            p = m_pallocator->reallocate(
               p,
               (size_t)heap_memory_unaligned_provision_get_size(size));

         }
         else
         {

            throw_exception(error_exception);

         }

         if (p == nullptr)
         {

            return nullptr;

         }

         if (blockuse == 0 || blockuse == 2 || blockuse == 128 || blockuse == 130) // aligned
         {

            return heap_memory_aligned(p, size, blockuse, align, m_ememory);

         }
         else if (blockuse == 1 || blockuse == 3 || blockuse == 129 || blockuse == 131) // unaligned
         {

            return heap_memory_unaligned(p, size, blockuse, m_ememory);

         }
         else
         {

            throw_exception(error_exception);

         }

         return nullptr;

      }


      void free(void * pmemory) override
      {

         return free_debug(pmemory, 0);

      }


      void free_debug(void * pmemory, i32 iBlockType) override
      {

         if ((iptr)pmemory < 1024)
         {

            return;

         }

         heap_memory * pheapmemory = heap_memory_get(pmemory);

         if (pheapmemory->m_ememory != m_ememory)
         {

            //throw "todo";
            //manage_memory_free(pheapmemory->m_ememory, pmemory);

            ::acme::get()->m_pheapmanagement->memory(
               pheapmemory->m_ememory)->m_pheap->free_debug(pmemory, iBlockType);

            return;

         }

         void * p = (void *)(((iptr)pmemory) - pheapmemory->m_back);

#ifdef __DEBUG

         heap_memory_check_padding_after(pheapmemory);

#endif // !__DEBUG

         if (pheapmemory->m_blockuse == 0)
         {

            memsize iAlignedSize = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);

            if (m_pallocarray)
            {

               m_pallocarray->_free(p, iAlignedSize);

            }

         }
         else if (pheapmemory->m_blockuse == 1)
         {

            //TODO: to do the dbg version

            if (m_pallocarray)
            {

               m_pallocarray->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));

            }

         }
         else if (pheapmemory->m_blockuse == 128)
         {

            //system_heap_free(p);

            ::free(p);

         }
         else if (pheapmemory->m_blockuse == 129)
         {

            //TODO: to do the dbg version

            //system_heap_free(p);

            ::free(p);

         }
         else if (pheapmemory->m_blockuse == 2)
         {

            memsize sizeProvision = heap_memory_aligned_provision_get_size(pheapmemory->m_size, pheapmemory->m_align);

            m_pallocarray->free_debug(p, sizeProvision);

         }
         else if (pheapmemory->m_blockuse == 3)
         {

            //TODO: to do the dbg version

            m_pallocarray->free_debug(p, heap_memory_unaligned_provision_get_size(pheapmemory->m_size));

         }
         else
         {

            m_pallocator->free(p);

         }

      }


      memsize size(void * pmemory) override
      {

         return size_debug(pmemory, _NORMAL_BLOCK);

      }


      memsize size_debug(void * pmemory, i32 iBlockType) override
      {

         if (pmemory == nullptr)
         {

            return 0;

         }

         return heap_memory_get_size(pmemory);

      }


   };


   ::heap::heap * new_std_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory)
   {

      return ::c::malloc::create < ::heap::std_heap >();

   }


} // namespace heap


#endif



