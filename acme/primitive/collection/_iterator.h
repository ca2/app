#pragma once


template < typename CONTAINER_TYPE >
struct container_iterator
{

   using CONTAINER = CONTAINER_TYPE;

   using TYPE = typename CONTAINER::BASE_TYPE;

   CONTAINER * m_pcontainer;

   container_iterator(CONTAINER * pcontainer = nullptr) : m_pcontainer(pcontainer) { }

   CONTAINER * container() const { return ((container_iterator *)this)->m_pcontainer; }

};


#define __declare_iterator_struct(container, item_type, item_member) \
   struct iterator_struct : container_iterator < container > \
   { \
      using CONTAINER = typename container_iterator::CONTAINER; \
      using ITEM_TYPE = item_type; \
      using container_iterator::container_iterator; \
      ITEM_TYPE item_member;  \
      ITEM_TYPE item_member ## Beg; \
      ITEM_TYPE item_member ## End;  \
      ITEM_TYPE & item () const { return ((iterator_struct *)this)->item_member; } \
      template < typename TYPE > \
      inline iterator_struct(const TYPE & t) { item_member = t.item(); m_pcontainer = t.container(); } \
   }; \
   struct const_iterator_struct : container_iterator < container > \
   { \
      using CONTAINER = typename container_iterator::CONTAINER; \
      using ITEM_TYPE = item_type; \
      using container_iterator::container_iterator; \
      ITEM_TYPE item_member;  \
      ITEM_TYPE item_member ## Beg; \
      ITEM_TYPE item_member ## End;  \
      ITEM_TYPE & item () const { return ((iterator_struct *)this)->item_member; } \
      template < typename TYPE > \
      inline iterator_struct(const TYPE & t) { item_member = t.item(); m_pcontainer = t.container(); } \
   }


#define __declare_iterator_struct_ok(container, item_type, item_member, ok_declaration) \
   struct iterator_struct : container_iterator < container > \
   { \
      using CONTAINER = typename container_iterator < container >::CONTAINER; \
      using ITEM_TYPE = item_type; \
      using container_iterator < container >::container_iterator; \
      ITEM_TYPE item_member;  \
      ITEM_TYPE item_member ## Beg; \
      ITEM_TYPE item_member ## End; \
      ITEM_TYPE & item () { return ((iterator_struct *)this)->item_member; } \
      const ITEM_TYPE & item () const { return ((iterator_struct *)this)->item_member; } \
      iterator_struct() {} \
      template < typename ITPTR > \
      inline iterator_struct(const ITPTR & t) { item_member = t.item(); this->m_pcontainer = t.container(); } \
   }; \
   struct const_iterator_struct : container_iterator < container > \
   { \
      using CONTAINER = typename container_iterator < container >::CONTAINER; \
      using ITEM_TYPE = const item_type; \
      using container_iterator < container >::container_iterator; \
      ITEM_TYPE item_member;  \
      ITEM_TYPE item_member ## Beg; \
      ITEM_TYPE item_member ## End; \
      ITEM_TYPE & item () { return ((const_iterator_struct *)this)->item_member; } \
      const ITEM_TYPE & item () const { return ((const_iterator_struct *)this)->item_member; } \
      const_iterator_struct() {} \
      template < typename ITPTR > \
      inline const_iterator_struct(const ITPTR & t) { item_member = t.item(); this->m_pcontainer = t.container(); } \
   }; \
   template < typename ITERATOR_STRUCT > struct iterator_common : ITERATOR_STRUCT \
   { \
      using CONTAINER = typename ITERATOR_STRUCT::CONTAINER; \
      bool ok() const { return ok_declaration; } \
      using ITEM_TYPE = typename ITERATOR_STRUCT::ITEM_TYPE; \
iterator_common() {} \
      void erase(ITEM_TYPE p) { this->m_pcontainer->erase(p); } \
   }





#define __declare_iterator(name, get_pointer_statement) \
   template < typename ITERATOR > \
   struct name##_base : ITERATOR \
   { \
      using CONTAINER = typename ITERATOR::CONTAINER; \
      using ITERATOR::ITERATOR; \
      name##_base () {} \
      auto get_pointer() { return get_pointer_statement; } \
      auto get_pointer() const { return (( name##_base * )this)->get_pointer(); } \
   }; \
   using name = make_iterator < wrap_iterator_base < name##_base < iterator_common < iterator_struct > > > >; \
   using const_##name = make_iterator < wrap_iterator_base < name##_base < iterator_common < const_iterator_struct > > > >; \
   using name##_range = make_iterator_range < name >; \
   using const_##name##_range = make_iterator_range < const_##name >;


namespace acme
{


   namespace iterator
   {


      template < typename CONTAINER, typename ITERATOR >
      ITERATOR erase(CONTAINER & container, ITERATOR it)
      {

         auto itnext = it;

         if(it)
         {

            itnext++;

            container.erase_item(it.item());

         }

         return itnext;

      }


   } // namespace iterator


} // namespace acme


// Range-based for loop support
// smart_pointer_range indirect/interpreted contribution from
/**
* pugixml parser - version 1.5
* --------------------------------------------------------
* Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
* Report bugs and download memory_new versions at http://pugixml.org/
*
* This library is distributed under the MIT License. See notice at the end
* of this file.
*
* This work is based on the pugxml parser, which is:
* Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
*/

template < typename ITERATOR >
struct make_iterator_range
{

   ITERATOR m_begin;
   ITERATOR m_end;

   make_iterator_range(ITERATOR begin, ITERATOR end) :
      m_begin(begin),
      m_end(end)
   {
   }

   ITERATOR begin()  const { return m_begin; }
   ITERATOR end()    const { return m_end; }

};



template < typename ITERATOR_BASE >
struct wrap_iterator_base :
   public ITERATOR_BASE
{

   using CONTAINER = typename ITERATOR_BASE::CONTAINER;

   using ITERATOR_BASE::ITERATOR_BASE;

   wrap_iterator_base() {}

   bool ended() const { return !this->ok(); }

   operator bool() const { return this->ok(); }

   auto operator -> () { return this->get_pointer(); }

   auto operator -> () const { return this->get_pointer(); }

   auto & operator * () { return *this->get_pointer(); }

   auto & operator * () const { return *this->get_pointer(); }

};

template < typename ITERATOR_STRUCT >
struct iterator_common :
   ITERATOR_STRUCT
{

   using ITEM_TYPE = typename ITERATOR_STRUCT::ITEM_TYPE;
   using ITERATOR_STRUCT::ITERATOR_STRUCT;

   iterator_common() {}

   void erase(ITEM_TYPE p) { this->m_pcontainer->erase(p); }

};


typedef CLASS_DECL_ACME numeric_array < index > index_array;
typedef CLASS_DECL_ACME numeric_array < count > count_array;



#ifdef LINUX
#include <initializer_list>
#endif

namespace constructor
{


   template < typename TYPE >
   class def
   {
   public:

      inline static void construct(void * p)
      {
         ::new(p) TYPE;
      }
      inline static void construct_count(void * p, ::count c)
      {
         while (c > 0)
         {
            ::new(p) TYPE;
            ((TYPE*&)p)++;
            c--;
         }
      }



   };


   template < typename TYPE >
   class zero
   {
   public:

      inline static void construct(void * p)
      {

         ::zero(p, sizeof(TYPE));

      }

      inline static void construct_count(void * p, ::count c)
      {

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            ((byte*&)p) += sizeof(TYPE);

            c--;

         }

      }



   };


   template < typename TYPE >
   class nodef
   {
   public:

      inline static void construct(void * p)
      {
         __UNREFERENCED_PARAMETER(p);
      }
      inline static void construct_count(void * p, ::count c)
      {
         __UNREFERENCED_PARAMETER(p);
         __UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor


template < typename TYPE >
inline void def_destruct(TYPE* pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
{

   pointer->~TYPE();

}

template < typename TYPE >
inline void def_destruct(::pointer<TYPE> pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
{

   pointer->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}

namespace destructor
{


   template < typename TYPE >
   class def
   {
   public:

      inline static void destruct(TYPE * pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {

         def_destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * pointer, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         while (c > 0)
         {
            def_destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
            pointer++;
            c--;
         }
      }



   };



   template < typename TYPE >
   class nodef
   {
   public:

      inline static void destruct(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         __UNREFERENCED_PARAMETER(p);
      }
      inline static void destruct_count(TYPE * p, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         __UNREFERENCED_PARAMETER(p);
         __UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace destructor


namespace copier
{


   template < typename TYPE >
   class def
   {
   public:

      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         *pdst = *psrc;

      }


      inline static void copy_count(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         while (c > 0)
         {

            *pdst = *psrc;
            pdst++;
            psrc++;
            c--;

         }

      }


   };


} // namespace copier


namespace heap
{

   template < class TYPE, class POOL >
   class allocator
   {
   public:

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         POOL::_free((void *)p);

      }


   };


   template < typename TYPE >
   class def :
      public allocator < TYPE, default_memory_allocator>
   {

   };


   template < typename TYPE >
   class processor_cache_oriented : // would it help for data-orientation-assumation ??!?!
      public allocator < TYPE, processor_cache_oriented_memory_allocator >
   {


   };


   template < typename TYPE >
   class sys :
      public allocator < TYPE, system_memory_allocator>
   {

   };



} // namespace memory


template < typename TYPE >
inline void copy_construct_count(TYPE * p, ::count c, const TYPE & t)
{

   while (c > 0)
   {

      new(p)TYPE(t);

      p++;

      c--;

   }

}




//#define memory_new ACME_NEW


#include "tiny_array.h"


//#include "array_base.h"
//#include "array.h"


