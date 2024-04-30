//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//  Refactoring 2023-11-23 05:39 <3ThomasBorregaardSoerensen!!
//
#pragma once


//#include "counter.h"


class plex_heap_alloc;


namespace c { class malloc; }


namespace acme
{

   
   class acme;


} // namespace acme


namespace heap
{


   class allocator;
   class memory;



   class CLASS_DECL_ACME management
   {
   protected:
      
      
      friend class ::c::malloc;


      management();
      ~management();


   public:


      class memory * m_memorya[::heap::e_memory_count];
      bool              m_bDestroyIfEmpty;
      ::acme::acme *    m_pacmeDestroyOnDestroy;


      //inline static class allocator *  s_allocatora[::heap::e_allocator_count];


      class allocator * m_pallocator;
      
      
      //inline static class heap * s_heapa[::heap::e_heap_count];

      
      ::acme::acme * m_pacme;


      //::heap::counter < ::particle * > *     m_pcounterParticle;

         


      void initialize_memory_management(::acme::acme * pacme);
      void finalize_memory_management();


      virtual void start_management();

      void enable_particle_counter();
      void disable_particle_counter();

      void dump_particle_counters();

      inline class memory * memory(enum_memory ememory) { return m_memorya[ememory]; }



      //  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
      inline class memory * main_memory() { return memory(::heap::e_memory_main); }
      inline class memory * secondary_memory() { return memory(::heap::e_memory_secondary); }
      inline class memory * array_memory() { return memory(::heap::e_memory_array); }
      inline class memory * property_memory() { return memory(::heap::e_memory_property); }
      inline class memory * string_memory() { return memory(::heap::e_memory_string); }



      class memory * _new_memory(enum_memory ememory);
      class memory * new_memory(enum_memory ememory);



      //inline static class allocator * allocator(enum_allocator eallocator)
      //{

      //   return s_allocatora[eallocator];

      //}
      inline class allocator * allocator()
      {

         return m_pallocator;

      }


      //inline static class allocator * system_allocator() { return allocator(::heap::e_allocator_system); }
      //inline static class allocator * default_allocator() { return allocator(::heap::e_allocator_default); }
      //inline static class allocator * memory_allocator() { return allocator(::heap::e_allocator_memory);  }
      //inline static class allocator * malloc_allocator() { return allocator(::heap::e_allocator_malloc); }
      //inline static class allocator * a2_allocator() { return allocator(::heap::e_allocator_a2); }


      class allocator * _new_allocator(enum_allocator eallocator);
      class allocator * new_allocator(enum_allocator eallocator);


      void memdleak_dump();

      //inline static class heap * heap(enum_heap eheap) { return s_heapa[eheap]; }



      ////  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2023-11-23 16:42 <3ThomasBorregaardSorensen!!
      //inline static class heap * default_heap() { return heap(::heap::e_heap_default); }
      ////inline static class memory * secondary_memory() { return memory(::heap::e_memory_secondary); }
      ////inline static class memory * array_memory() { return memory(::heap::e_memory_array); }
      ////inline static class memory * property_memory() { return memory(::heap::e_memory_property); }
      ////inline static class memory * string_memory() { return memory(::heap::e_memory_string); }



      class heap * _new_heap(enum_heap eheap, ::heap::enum_memory ememory);
      class heap * new_heap(enum_heap eheap, ::heap::enum_memory ememory);


      void on_plex_heap_alloc(plex_heap_alloc * palloc);
      void on_system_heap_alloc(memsize memsize);



//      namespace secondary_memory_allocate_heap
//      {
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//      }
//
//
//      namespace array_memory_allocate_heap
//      {
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//      }
//
//
//
//      namespace property_memory_allocate_heap
//      {
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//      }
//
//
//      namespace string_memory_allocate_heap
//      {
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//      }



      virtual void on_plex_new_block(::u32 nAllocSize);
     
   };
   
   

//   class CLASS_DECL_ACME heap_base
//   {
//   public:
//
//
//      void *         m_p;
//      memsize       m_uiSize;
//
//
//      heap_base()
//      {
//
//         m_p         = nullptr;
//         m_uiSize    = 0;
//
//      }
//
//      heap_base(memsize uiSize)
//      {
//
//         m_p         = nullptr;
//         m_uiSize    = 0;
//
//         size_i32(uiSize);
//
//      }
//
//      virtual ~heap_base()
//      {
//
//         _free();
//
//      }
//
//      memsize size()
//      {
//
//         return m_uiSize;
//
//      }
//
//
//      void zero();
//
//
//      virtual memsize size(memsize uiSize)
//      {
//
//         if(m_p == nullptr)
//         {
//
//            m_p = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(uiSize);
//
//         }
//         else
//         {
//
//            m_p = memory_reallocate(m_p,uiSize);
//
//         }
//
//         if(m_p != nullptr)
//         {
//
//            m_uiSize = uiSize;
//
//         }
//
//         return m_uiSize;
//
//      }
//
//
//      void _free()
//      {
//
//         if(m_p != nullptr)
//         {
//
//            ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_p);
//
//            m_p = nullptr;
//
//         }
//
//      }
//
//
//   };
//

//   template < typename T >
//   class heap:
//      public heap_base
//   {
//   public:
//
//
//      heap() {   }
//
//      heap(memsize iCount): heap_base(iCount * sizeof(T)) {   }
//
//      operator T * () { return (T *)m_p; }
//      operator const T * () const { return (T *)m_p; }
//
//      memsize count() { return size() / sizeof(T); }
//
//      void stralloc(::raw::count cChar) { size_i32((cChar + 1) * sizeof(T)); }
//
//      string & to_string(string & str) const;
//
//   };
//

} // namespace heap



//typedef ::heap::heap < char > hstring_base;
//
//class CLASS_DECL_ACME hstring:
//   public hstring_base
//{
//public:
//
//   hstring() {}
//   hstring(memsize uiSize): hstring_base(uiSize) {}
//
//};


//typedef ::heap::heap < unichar > hwstring_base;
//
//class CLASS_DECL_ACME wstring:
//   public hwstring_base
//{
//public:
//
//   wstring() {}
//   wstring(memsize uiSize): hwstring_base(uiSize) {}
//
//};

