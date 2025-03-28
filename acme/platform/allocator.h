// Created by camilo on 2023-11-27 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/memory/allocator_base.h"
#include "acme/platform/acme.h"
#include "acme/prototype/string/c/strdup.h"


namespace allocator
{


#if REFERENCING_DEBUGGING


   CLASS_DECL_ACME void __on_start_construct(void * p, memsize s, bool bParticleAndHeapAllocation);

   CLASS_DECL_ACME void __on_after_construct_subparticle(::subparticle* psubparticle);

   CLASS_DECL_ACME void __on_after_construct_non_subparticle();

   CLASS_DECL_ACME void start_referencing_debugging_suppression();

   CLASS_DECL_ACME void stop_suppressing_referencing_debugging();

   CLASS_DECL_ACME ::subparticle * task_get_top_track();

   CLASS_DECL_ACME void on_construct_subparticle(::subparticle* psubparticle);

   CLASS_DECL_ACME void on_after_construct_subparticle(::subparticle* psubparticle);

   CLASS_DECL_ACME void __on_after_construct();

   CLASS_DECL_ACME void on_destruct_subparticle(::subparticle* psubparticle);

   CLASS_DECL_ACME void __on_after_construct_subparticle(::subparticle* psubparticle);

   CLASS_DECL_ACME void __on_after_construct_non_subparticle();


#endif


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
#if REFERENCING_DEBUGGING
         __on_start_construct(data, s, true);
#endif
#if REFERENCING_DEBUGGING

         auto p = __on_referencing_debugging_construct<PARTICLE>(data, s, ::std::forward<Args>(args)...);

         __on_after_construct_subparticle(p);

#else

         auto p = __on_normal_construct<PARTICLE>(data, s, ::std::forward<Args>(args)...);

#endif

         //p->m_pAllocation = data;

         return p;

      }


      template < non_particle NON_PARTICLE, typename ...Args >
      inline static NON_PARTICLE * __on_construct(void * data, memsize s, Args &&... args)
      {
#if REFERENCING_DEBUGGING

         __on_start_construct(data, s, false);
#endif
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
#if REFERENCING_DEBUGGING

         ::allocator::defer_erase_referer();
#endif
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

#if REFERENCING_DEBUGGING
         on_after_construct_particle(p);
#endif

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

#if REFERENCING_DEBUGGING

         auto preferer = ::allocator::get_top_referer();

#endif

         auto p = __allocator_base_new< T >(pallocatorbase, ::std::forward < Args >(args)...);

         pointer < T > pointer{ transfer_t{}, p };

#if REFERENCING_DEBUGGING

         if (!p->is_referencing_debugging_enabled())
         {

            pointer.m_preferer = nullptr;

         }
         else
         {

            pointer.m_preferer = preferer;

         }

#endif

         return ::transfer(pointer);

      }


//      template < typename T, typename ...Args >
//      inline static T * __allocator_base_new(::heap::allocator_base * pallocatorbase, Args &&... args)
//      {
//
//         auto s = sizeof(T);
//
//         char * pszAnnotation = nullptr;
//
//#if MEMORY_ANNOTATION
//
//         pszAnnotation = ::c::strdup(typeid(T).name());
//
//#endif
//
//         auto data = pallocatorbase->allocate(s, nullptr,  pszAnnotation);
//
//         auto p = __on_construct< T >(data, s, ::std::forward < Args >(args)...);
//
//         return p;
//
//      }
//
//
//      template < typename T >
//      inline static T * __allocator_base_new_array(::heap::allocator_base * pallocatorbase, ::collection::count c)
//      {
//
//         constexpr auto sElement = sizeof(T);
//
//         auto s = sElement * c;
//
//         char * pszAnnotation = nullptr;
//
//#if MEMORY_ANNOTATION
//
//         pszAnnotation = ::c::strdup2("array of ", typeid(T).name());
//
//#endif
//
//         auto * data = pallocatorbase->allocate(s, pszAnnotation);
//
//         auto p = (unsigned char*)data;
//
//         for (::collection::index i = 0; i < c; i++)
//         {
//
//            __on_construct < T >(data, sElement);
//
//            p += sElement;
//
//         }
//
//         return (T *)data;
//
//      }
//
//
//      template < typename T >
//      inline static void __allocator_base_delete(::heap::allocator_base * pallocatorbase, T * p)
//      {
//
//         __on_destruct(p);
//
//         pallocatorbase->free(p);
//
//      }
//
//
//      template < typename T >
//      inline static void __allocator_base_delete(::heap::allocator_base * pallocatorbase, T* p, void * pAllocation)
//      {
//
//         __on_destruct(p);
//
//         pallocatorbase->free(pAllocation);
//
//      }


      template < typename T, typename ...Args >
      static ::pointer < T > __memory_allocate(::heap::enum_memory ememory, Args &&... args)
      {

         auto pheapmanagement = ::acme::get()->m_pheapmanagement;

         auto & pmemory = pheapmanagement->m_memorya[ememory];

         auto p = ::transfer(__allocator_base_allocate< T >(
            pmemory,
            ::std::forward<Args>(args)...));

         return ::transfer(p);

      }


      template < typename T, typename ...Args >
      inline static T * __memory_new(::heap::enum_memory ememory, Args &&... args)
      {

         auto pheapmanagement = ::acme::get()->m_pheapmanagement;

         auto & pmemory = pheapmanagement->m_memorya[ememory];

         auto p = __allocator_base_new < T >(
            pmemory,
            ::std::forward < Args >(args)...);

         return p;

      }


      template < typename T >
      inline static T * __memory_new_array(::heap::enum_memory ememory, ::collection::count c)
      {

         auto pheapmanagement = ::acme::get()->m_pheapmanagement;

         auto & pmemory = pheapmanagement->m_memorya[ememory];

         auto p = __allocator_base_new_array < T >(
            pmemory,
            c);

         return p;

      }


      template < typename T >
      static void __memory_delete(::heap::enum_memory ememory, T * p)
      {

        auto pheapmanagement = ::acme::get()->m_pheapmanagement;

        auto & pmemory = pheapmanagement->m_memorya[ememory];

        __allocator_base_delete< T >(
           pmemory,
           p);

      }


      template < typename T >
      static void __memory_delete(::heap::enum_memory ememory, T* p, void * pAllocation)
      {

        auto pheapmanagement = ::acme::get()->m_pheapmanagement;

        auto & pmemory = pheapmanagement->m_memorya[ememory];

        __allocator_base_delete< T >(
           pmemory,
           p,
           pAllocation);

      }


      template < typename T, typename ...Args >
      ::pointer < T > static __call__allocate(Args &&... args)
      {

         auto p = ::transfer(__memory_allocate< T >(
            ::heap::e_memory_main,
            ::std::forward<Args>(args)...));

         return ::transfer(p);

      }


#if REFERENCING_DEBUGGING

      //accessor < ALLOCATOR_ACCESSOR, t_bDisableReferencingDebugging > * __call__add_referer(const ::reference_referer & referer) const
      accessor * __call__add_referer(const ::reference_referer & referer) const
      {

#if REFERENCING_DEBUGGING

         ::allocator::push_referer(referer);

#endif

         return (accessor *) this;

      }

#endif


      template < typename T, typename ...Args >
      inline static T * __call__allocate(Args &&... args)
      {

         auto p = __memory_new < T >(
            ::heap::e_memory_main,
            ::std::forward < Args >(args)...);

         return p;

      }


      template < typename T >
      inline static T * __allocate_array(::collection::count c)
      {

         auto p = __memory_new_array < T >(
            ::heap::e_memory_main,
            c);

         return p;

      }


      template < typename T >
      static void __call__delete(T * p)
      {

        __memory_delete< T >(
           ::heap::e_memory_main,
           p);

      }


      template < typename T >
      static void __call__delete(T* p, void * pAllocation)
      {

        __memory_delete< T >(
           ::heap::e_memory_main,
           p, pAllocation);

      }

   };


   CLASS_DECL_ACME extern ::allocator::accessor * g_pacessorDefault;


} // namespace allocator


namespace platform
{


   using allocator = ::allocator::accessor;

   //using raw_allocator = ::allocator::accessor < default_t, true >;


} // namespace platform


//template < typename T, typename ...Args >
//::pointer < T > __call__allocate(Args &&... args)
//{
//
//   auto p = ::transfer(
//      ::platform::allocator::__call__allocate< T >(
//         ::std::forward<Args>(args)...));
//
//   return ::transfer(p);
//
//}
//


