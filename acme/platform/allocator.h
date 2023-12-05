// Created by camilo on 2023-11-27 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/memory/allocator_base.h"


namespace allocator
{


   CLASS_DECL_ACME void __on_start_construct(void * p, memsize s, bool bParticleAndHeapAllocation);

   CLASS_DECL_ACME::particle * task_get_top_track();

   CLASS_DECL_ACME void on_construct_particle(::particle * pparticle);

   CLASS_DECL_ACME void on_after_construct_particle(::particle * pparticle);

   CLASS_DECL_ACME void __on_after_construct();

   CLASS_DECL_ACME void on_destruct_particle(::particle * pparticle);

   CLASS_DECL_ACME void __on_after_construct_particle(::particle * pparticle);


   //template < typename ALLOCATOR_ACCESSOR, bool t_bDisableReferencingDebugging = false >
   class accessor
   {
   public:

      //using ACCESSOR = ALLOCATOR_ACCESSOR;

      template < typename T, typename ...Args >
      static T * __accessor_on_construct(void * data, Args &&... args)
      {

         auto p = ::new(data) T(::std::forward<Args>(args)...);

         return p;

      }


      template < typename T >
      static void __accessor_on_destruct(T * p)
      {

         p->~T();

      }


      template < a_particle PARTICLE, typename ...Args >
      static inline PARTICLE * __on_construct(void * data, memsize s, Args &&... args)
      {

         //__on_start_construct(data, s, t_bDisableReferencingDebugging, true);
         __on_start_construct(data, s, true);

#if REFERENCING_DEBUGGING

         auto p = __on_referencing_debugging_construct<PARTICLE>(data, s, ::std::forward<Args>(args)...);

         __on_after_construct_particle(p);

         return p;

#else

         return __on_normal_particle_construct<PARTICLE>(data, s, ::std::forward<Args>(args)...);

#endif

      }


      template < non_particle NON_PARTICLE, typename ...Args >
      inline static NON_PARTICLE * __on_construct(void * data, memsize s, Args &&... args)
      {

         __on_start_construct(data, s, false);

#if REFERENCING_DEBUGGING

         auto p = __on_referencing_debugging_construct<NON_PARTICLE>(data, s, ::std::forward<Args>(args)...);

         __on_after_construct();

         return p;

#else

         return __on_normal_construct<NON_PARTICLE>(data, s, ::std::forward<Args>(args)...);

#endif

      }


      template < a_particle PARTICLE, typename ...Args >
      inline static PARTICLE * __on_referencing_debugging_construct(void * data, memsize s, Args &&... args)
      {

         //auto p = ::new(data) PARTICLE(::std::forward<Args>(args)...);

         auto p = __accessor_on_construct<PARTICLE>(data, ::std::forward<Args>(args)...);

         //on_after_construct_particle(p);

         return p;

      }


      template < non_particle NON_PARTICLE, typename ...Args >
      inline static NON_PARTICLE * __on_referencing_debugging_construct(void * data, memsize s, Args &&... args)
      {

         //auto p = ::new(pdata) NON_PARTICLE(::std::forward<Args>(args)...);

         ::allocator::defer_erase_referer();

         auto p = __accessor_on_construct<NON_PARTICLE>(data, ::std::forward<Args>(args)...);

         return p;

      }


      //template < non_particle NON_PARTICLE, typename ...Args >
      //inline static NON_PARTICLE * __on_referencing_debugging_construct(void * data, memsize s, Args &&... args)
      //{

      //   //auto p = ::new(pdata) NON_PARTICLE(::std::forward<Args>(args)...);

      //   auto p = __accessor_on_construct<NON_PARTICLE>(data, ::std::forward<Args>(args)...);

      //   return p;

      //}


      template < a_particle PARTICLE, typename ...Args >
      inline static PARTICLE * __on_normal_construct(void * data, memsize s, Args &&... args)
      {

         //auto p = ::new(data) PARTICLE(::std::forward<Args>(args)...);

         auto p = __accessor_on_construct<PARTICLE>(data, ::std::forward<Args>(args)...);

         on_after_construct_particle(p);

         return p;

      }


      template < non_particle NON_PARTICLE, typename ...Args >
      inline static NON_PARTICLE * __on_normal_construct(void * data, memsize s, Args &&... args)
      {

         //auto p = ::new(pdata) NON_PARTICLE(::std::forward<Args>(args)...);

         auto p = __accessor_on_construct<NON_PARTICLE>(data, ::std::forward <Args>(args)...);

         return p;

      }


      template < typename T >
      inline static void __on_destruct(T * p)
      {

         //p->~T();

         __accessor_on_destruct<T>(p);

      }


      template < typename T, typename ...Args >
      static ::pointer < T > __allocator_base_allocate(::heap::allocator_base * pallocatorbase, Args &&... args)
      {

         auto preferer = ::allocator::get_referer();

         auto p = __allocator_base_new< T >(pallocatorbase, ::std::forward < Args >(args)...);

         pointer < T > pointer{ transfer_t{}, p };

         if (!p->is_referencing_debugging_enabled())
         {

            pointer.m_preferer = nullptr;

         }
         else
         {

            pointer.m_preferer = preferer;

         }
 
         return ::transfer(pointer);

      }


      template < typename T, typename ...Args >
      inline static T * __allocator_base_new(::heap::allocator_base * pallocatorbase, Args &&... args)
      {

         auto s = sizeof(T);

         auto data = pallocatorbase->allocate(s);

         auto p = __on_construct< T >(data, s, ::std::forward < Args >(args)...);

         return p;

      }


      template < typename T >
      inline static T * __allocator_base_new_array(::heap::allocator_base * pallocatorbase, ::count c)
      {

         constexpr auto sElement = sizeof(T);

         auto s = sElement * c;

         auto * data = pallocatorbase->allocate(s);

         auto p = (::u8*)data;

         for (::index i = 0; i < c; i++)
         {

            __on_construct < T >(data, sElement);

            p += sElement;

         }

         return (T *)data;

      }


      template < typename T >
      inline static void __allocator_base_delete(::heap::allocator_base * pallocatorbase, T * p)
      {

         __on_destruct(p);

         pallocatorbase->free(p);

      }


      template < typename T, typename ...Args >
      static ::pointer < T > __memory_allocate(::heap::enum_memory ememory, Args &&... args)
      {

         auto p = ::transfer(__allocator_base_allocate< T >(
            ::acme::get()->m_pheapmanagement->memory(ememory),
            ::std::forward<Args>(args)...));

         return ::transfer(p);

      }


      template < typename T, typename ...Args >
      inline static T * __memory_new(::heap::enum_memory ememory, Args &&... args)
      {

         auto p = __allocator_base_new < T >(
            ::acme::get()->m_pheapmanagement->memory(ememory),
            ::std::forward < Args >(args)...);

         return p;

      }


      template < typename T >
      inline static T * __memory_new_array(::heap::enum_memory ememory, ::count c)
      {

         auto p = __allocator_base_new_array < T >(
            ::acme::get()->m_pheapmanagement->memory(ememory),
            c);

         return p;

      }


      template < typename T >
      static void __memory_delete(::heap::enum_memory ememory, T * p)
      {

         __allocator_base_delete< T >(
            ::acme::get()->m_pheapmanagement->memory(ememory),
            p);

      }


      template < typename T, typename ...Args >
      ::pointer < T > static __call__allocate(Args &&... args)
      {

         auto p = ::transfer(__memory_allocate< T >(
            ::heap::e_memory_main,
            ::std::forward<Args>(args)...));

         return ::transfer(p);

      }


      //accessor < ALLOCATOR_ACCESSOR, t_bDisableReferencingDebugging > * __call__add_referer(const ::reference_referer & referer) const
      accessor * __call__add_referer(const ::reference_referer & referer) const
      {

         ::allocator::add_referer(referer);
      
         return (accessor *) this;

      }


      template < typename T, typename ...Args >
      inline static T * __call__new(Args &&... args)
      {

         auto p = __memory_new < T >(
            ::heap::e_memory_main,
            ::std::forward < Args >(args)...);

         return p;

      }


      template < typename T >
      inline static T * __new_array(::count c)
      {

         auto p = __memory_new_array < T >(
            ::heap::e_memory_main,
            c);

         return p;

      }


      template < typename T >
      static void __delete(T * p)
      {

         __memory_delete< T >(
            ::heap::e_memory_main,
            p);

      }

   };


   CLASS_DECL_ACME extern ::allocator::accessor * g_pacessorDefault;


} // namespace allocator


namespace platform
{


   using allocator = ::allocator::accessor;

   //using raw_allocator = ::allocator::accessor < default_t, true >;


} // namespace platform


template < typename T, typename ...Args >
::pointer < T > __call__allocate(Args &&... args)
{

   auto p = ::transfer(
      ::platform::allocator::__call__allocate< T >(
         ::std::forward<Args>(args)...));

   return ::transfer(p);

}



