// Created by camilo on 2023-11-23 05:22 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "counter.h"
#include "heap.h"


namespace heap
{

   heap * new_std_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory);
//
//
//   class CLASS_DECL_ACME system_memory_allocator :
//      virtual public allocator
//   {
//   public:
//
//#if MEMDLEAK  || defined(__MCRTDBG)
//      void * alloc(memsize iSize, const_char_pointer  pszFile, int iLine)  override
//      {
//
//         return system_heap_alloc_debug(iSize, 725, pszFile, iLine);
//
//      }
//#else
//       void * allocate(memsize iSize) override
//      {
//
//         return system_heap_alloc(iSize);
//
//      }
//#endif
//
//
//       void free(void * p) override {
//
//         system_heap_free(p);
//
//      }
//
//
//   };


   class CLASS_DECL_ACME default_memory_allocator :
      virtual public allocator
   {
   public:


#if MEMDLEAK || defined(__MCRTDBG)

      void * alloc(memsize iSize, const_char_pointer  pszFile, int iLine, const_char_pointer  pszAnnotation = nullptr) override
      {

         return memory_allocate_debug(iSize, 724, pszFile, iLine, pszAnnotation);

      }

#else

      void * allocate(memsize iSize, memsize * psizeAllocated, const_char_pointer  pszAnnotation = nullptr) override
      {

         return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iSize, psizeAllocated, pszAnnotation);

      }

#endif


      void free(void * p) override
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(p);

      }


   };


   management::management()
   {

      m_pacme = nullptr;

      m_bDestroyIfEmpty = false;

      m_pacmeDestroyOnDestroy = nullptr;

      //m_pcounterParticle = nullptr;

   }


   management::~management()
   {


   }


   class allocator * management::new_allocator(enum_allocator eallocator)
   {

      auto p = _new_allocator(eallocator);

      p->initialize_allocator(m_pacme);

      return p;

   }


   void management::initialize_memory_management(::acme::acme * pacme)
   {

      m_pacme = pacme;

      m_pallocator = new_allocator(::heap::e_allocator_system);
      //s_allocatora[::heap::e_allocator_system] = _new_allocator(::heap::e_allocator_system);
//      s_allocatora[::heap::e_allocator_default] = _new_allocator(::heap::e_allocator_default);
  //    s_allocatora[::heap::e_allocator_memory] = _new_allocator(::heap::e_allocator_memory);
    //  s_allocatora[::heap::e_allocator_malloc] = _new_allocator(::heap::e_allocator_malloc);
      //s_allocatora[::heap::e_allocator_a2] = _new_allocator(::heap::e_allocator_a2);


      //m_pallocatorSystemMemory = __allocate system_memory_allocator();
      //m_pallocatorDefaultMemory = __allocate default_memory_allocator();

      for (::collection::index i = 0; i < ::heap::e_memory_count; i++)
      {

         m_memorya[i] = new_memory((::heap::enum_memory)i);

      }

      //s_memorya[::heap::e_memory_main] = new_memory(::heap::e_memory_main);
      //s_memorya[::heap::e_memory_secondary] = new_memory(::heap::e_memory_secondary);
      //s_memorya[::heap::e_memory_array] = new_memory(::heap::e_memory_array);
      //s_memorya[::heap::e_memory_property] = new_memory(::heap::e_memory_property);
      //s_memorya[::heap::e_memory_string] = new_memory(::heap::e_memory_string);

      //m_pmemoryallocateMain = __allocate < ::acme::get()->m_pheapmanagement->memory >(::heap::e_memory_main)->allocate);
      //m_pmemoryallocateSecondary = __allocate < ::acme::get()->m_pheapmanagement->memory >(::heap::e_memory_main)->allocate);
      //m_pmemoryallocateArray = __allocate < ::acme::get()->m_pheapmanagement->memory >(::heap::e_memory_main)->allocate);
      //m_pmemoryallocateProperty = __allocate < ::acme::get()->m_pheapmanagement->memory >(::heap::e_memory_main)->allocate);
      //m_pmemoryallocateString = __allocate < ::acme::get()->m_pheapmanagement->memory >(::heap::e_memory_main)->allocate);

   }


   void management::start_management()
   {

      for (::collection::index i = 0; i < ::heap::e_memory_count; i++)
      {

         m_memorya[i]->start_memory();

      }

   }


   void management::finalize_memory_management()
   {


   }


   void management::enable_particle_counter()
   {

      //if (!m_pcounterParticle)
      //{

      //   m_pcounterParticle = ___new ::heap::counter < ::particle * >();

      //}

      //m_pcounterParticle->m_bEnabled = true;

   }


   void management::disable_particle_counter()
   {

      //if (!m_pcounterParticle)
      //{

      //   return;

      //}

      //m_pcounterParticle->m_bEnabled = false;

   }


   void management::dump_particle_counters()
   {

      //if (!m_pcounterParticle)
      //{

      //   return;

      //}

      //auto & counter = *m_pcounterParticle;

   }


   heap * management::_new_heap(::heap::enum_heap eheap, ::heap::enum_memory ememory)
   {

      return new_std_heap(m_pallocator, ememory);

   }


   heap * management::new_heap(::heap::enum_heap eheap, ::heap::enum_memory ememory)
   {
      
      auto p = _new_heap(eheap, ememory);

      p->initialize_heap(m_pallocator, ememory);

      return p;

   }


   void management::memdleak_dump()
   {


      //main_memory_allocate_heap::memdleak_dump();
      //array_memory_allocate_heap::memdleak_dump();
      //property_memory_allocate_heap::memdleak_dump();
      //secondary_memory_allocate_heap::memdleak_dump();
      //string_memory_allocate_heap::memdleak_dump();


   }

   
   void management::on_plex_heap_alloc(plex_heap_alloc * palloc)
   {


   }


   void management::on_system_heap_alloc(memsize memsize)
   {


   }



   void management::on_plex_new_block(unsigned int nAllocSize)
   {


   }



} // namespace heap



