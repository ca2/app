// Created by camilo on 2022-10-23 03:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "management.h"


namespace heap
{


   template < class TYPE >
   class operating_system_typed_memory
   {
   public:

      inline ::heap::allocator* allocator() { return ::acme::get()->m_pheapmanagement->m_pallocator; }


      inline TYPE* allocate(::collection::count c, ::collection::count * pcAllocated, const char* pszFile, int iLine)
      {

         memsize sizeAllocated = 0;

         auto p = (TYPE*)allocator()->allocate(sizeof(TYPE) * c, &sizeAllocated);

         if (pcAllocated)
         {

            *pcAllocated = sizeAllocated / sizeof(TYPE);

         }

         return p;

      }


      inline TYPE* allocate(::collection::count c, ::collection::count * pcAllocated)
      {

         memsize sizeAllocated = 0;

         auto p = (TYPE*)allocator()->allocate(sizeof(TYPE) * c, &sizeAllocated);

         if (pcAllocated)
         {

            *pcAllocated = sizeAllocated / sizeof(TYPE);

         }

         return p;

      }


      inline void free(TYPE* p)
      {

         allocator()->free((void*)p);

      }


   };



   template < class TYPE, enum_memory t_ememory >
   class typed_memory
   {
   public:

      
      inline ::heap::memory * memory() { return ::acme::get()->m_pheapmanagement->memory(t_ememory); }


      inline TYPE * allocate(::collection::count c, const char * pszFile, int iLine)
      {

         return (TYPE *)memory()->allocate_debug(sizeof(TYPE) * c, 0, pszFile, iLine);

      }


      inline TYPE * allocate(::collection::count c, ::collection::count * pcAllocated)
      {

         memsize sizeAllocated = 0;

         auto p = (TYPE *)memory()->allocate(sizeof(TYPE) * c, &sizeAllocated);

         if (pcAllocated)
         {

            *pcAllocated = sizeAllocated / sizeof(TYPE);

         }

         return p;

      }


      inline void free(TYPE * p)
      {

         memory()->free((void *)p);

      }


   };
//
//
//   //template < typename TYPE >
//   //class def :
//   //   public typed_allocator < TYPE>
//   //{
//
//   //};
//
//
//   //template < typename TYPE >
//   //class processor_cache_oriented : // would it help for data-orientation-assumation ??!?!
//   //   public typed_allocator < TYPE, processor_cache_oriented_memory_allocator >
//   //{
//
//
//   //};
//
//
//   //template < typename TYPE >
//   //class sys :
//   //   public allocator < TYPE, ::heap::system_memory_allocator>
//   //{
//
//   //};
//
//
//
} // namespace heap
//

namespace allocator
{


   template < typename TYPE >
   class allocator
   {
   public:

      //::heap::typed_allocator < TYPE > * m_ptypedallocator;

      inline  void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline  void construct_count(TYPE * p, ::collection::count c)
      {
         constructor::nodef< TYPE >::construct_count(p, c);

      }

      
      inline  void destruct(TYPE * p)
      {

         destructor::nodef < TYPE >::destruct(p);

      }


      inline  void destruct_count(TYPE * p, ::collection::count c)
      {

         destructor::nodef < TYPE >::destruct_count(p, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            copy(pdst, &src);

            pdst++;

            c--;

         }

      }

      
      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            copy(pdst, psrc);

            c--;

            pdst++;

            psrc++;

         }

      }

      
      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {
            
            c--;

            copy(pdst, psrc + c);

            pdst++;

         }

      }


      //inline TYPE * alloc(::collection::count c)
      //{

      //   return m_ptypedallocator->allocate(c);

      //}


      //inline void _free(TYPE * p)
      //{

      //   m_ptypedallocator->free(p);

      //}

   };


   template < typename TYPE >
   class def :
      protected constructor::def<TYPE>,
      protected copier::def<TYPE>,
      protected destructor::def<TYPE>
   {
   public:


      inline  void construct(TYPE * p)
      {

         constructor::def< TYPE >::construct(p);

      }


      inline  void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::def< TYPE >::construct_count(p, c);

      }


      inline  void destruct(TYPE * pointer)
      {

         destructor::def< TYPE>::destruct(pointer);

      }


      inline  void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::def< TYPE>::destruct_count(pointer, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            ::new (pdst) TYPE(src);

            pdst++;

            c--;

         }

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            ::new (pdst) TYPE(*psrc);

            c--;

            pdst++;

            psrc++;
         }

      }


      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            c--;

            ::new (pdst) TYPE(psrc[c]);

            pdst++;

         }

      }


      //inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
      //{

      //   return m_ptypedallocator->allocate(c, pszFile, iLine);

      //}
      //inline  TYPE * alloc(::collection::count c)
      //{

      //   return m_ptypedallocator->allocate(c);

      //}



      //inline  void free(TYPE * p)
      //{

      //   m_ptypedallocator->free(p);

      //}


   };



   template < typename TYPE >
   class rawcopy :
      public constructor::def< TYPE >,
      public destructor::def< TYPE>
   {

   public:

      inline  void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline  void construct_count(TYPE * p, ::collection::count c)
      {
         constructor::def< TYPE >::construct_count(p, c);
      }


      inline void destruct(TYPE * pointer)
      {

         destructor::def< TYPE>::destruct(pointer);

      }


      inline void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::def< TYPE>::destruct_count(pointer, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE));

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE) * c);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         /*   while (c > 0)
            {
               copy(pdst, &src);
               c--;
            }*/

         throw_exception(error_not_supported);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         /*   while (c > 0)
            {
               copy(pdst, &src);
               c--;
          psrc++;
            }*/

         throw_exception(error_not_supported);

      }


      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         /*   while (c > 0)
            {
               copy(pdst, &src);
               c--;
          psrc++;
            }*/

         throw_exception(error_not_supported);

      }


      //inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
      //{

      //   m_ptypedallocator->alloc(c, pszFile, iLine);

      //}
      //inline  TYPE * alloc(::collection::count c)
      //{

      //   m_ptypedallocator->alloc(c);

      //}


      //inline  void free(TYPE * p)
      //{

      //   m_ptypedallocator->free(p);

      //}


   };


   template < typename TYPE >
   class nodef
   {
   public:


      inline  void construct(TYPE * p)
      {

         constructor::nodef< TYPE >::construct(p);

      }


      inline void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::nodef< TYPE >::construct_count(p, c);

      }


      inline void destruct(TYPE * pointer)
      {

         destructor::nodef< TYPE>::destruct(pointer);

      }


      inline  void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(pointer, c);

      }


      inline void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            copy(pdst, &src);

            pdst++;

            c--;

         }

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            copy(pdst, psrc);

            c--;

            pdst++;

            psrc++;

         }

      }

      
      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            c--;

            copy(pdst, psrc + c);

            pdst++;

         }

      }

      
      
  /*    inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
      {

         return m_ptypedallocator->alloc(c, pszFile, iLine);

      }
      inline  TYPE * alloc(::collection::count c)
      {

         m_ptypedallocator->alloc(c);

      }


      inline  void _free(TYPE * p)
      {

         m_ptypedallocator->free(p);

      }
*/

   };


   template < typename TYPE >
   class raw
   {
   public:


      inline void construct(TYPE * p)
      {

         constructor::nodef< TYPE >::construct(p);

      }


      inline void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::nodef< TYPE >::construct_count(p, c);

      }


      inline void destruct(TYPE * pointer)
      {

         destructor::nodef< TYPE>::destruct(pointer);

      }


      inline void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(pointer, c);

      }


      inline void copy(TYPE * pdst, const TYPE * psrc)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE));

      }


      inline void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE) * c);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            copy(pdst, &src);

            pdst++;

            c--;

         }

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            copy(pdst, psrc);

            c--;

            pdst++;

            psrc++;

         }

      }

      
      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            c--;

            copy(pdst, psrc + c);

            pdst++;

         }

      }


      //inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
      //{

      //   return m_ptypedallocator->alloc(c, pszFile, iLine);

      //}
      //inline  TYPE * alloc(::collection::count c)
      //{

      //   m_ptypedallocator->alloc(c);

      //}


      //inline  void free(TYPE * p)
      //{

      //   m_ptypedallocator->free(p);

      //}


   };


   template < typename TYPE >
   class zero :
      public constructor::zero< TYPE >,
      public destructor::nodef< TYPE>,
      public copier::def< TYPE >
   {
   public:


      inline void construct(TYPE * p)
      {

         constructor::zero< TYPE >::construct(p);

      }


      inline void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::zero< TYPE >::construct_count(p, c);

      }


      inline  void destruct(TYPE * p)
      {

         destructor::nodef< TYPE>::destruct(p);

      }


      inline void destruct_count(TYPE * p, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(p, c);

      }


      inline void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }


      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            copy(pdst, &src);

            pdst++;

            c--;

         }

      }

      
      inline void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            copy(pdst, psrc);

            pdst++;

            c--;

            psrc++;

         }

      }

      
      inline void rear_copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            c--;
            
            copy(pdst, psrc + c);

            pdst++;

         }

      }


      //inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
      //{

      //   return m_ptypedallocator->alloc(c, pszFile, iLine);

      //}
      //inline  TYPE * alloc(::collection::count c)
      //{

      //   return m_ptypedallocator->alloc(c);

      //}


      //inline  void free(TYPE * p)
      //{

      //   m_ptypedallocator->free(p);

      //}


   };
//
//   template < typename TYPE >
//   class sys
//   {
//
//   public:
//
//      inline  void construct(TYPE * p)
//      {
//         constructor::def< TYPE >::construct(p);
//      }
//
//      inline  void construct_count(TYPE * p, ::collection::count c)
//      {
//         constructor::def< TYPE >::construct_count(p, c);
//
//      }
//
//      inline  void destruct(TYPE * p)
//      {
//         destructor::def< TYPE>::destruct(p);
//      }
//      inline  void destruct_count(TYPE * p, ::collection::count c)
//      {
//         destructor::def< TYPE>::destruct_count(p, c );
//      }
//
//
//      inline  void copy(TYPE * pdst, const TYPE * psrc)
//      {
//
//         copier::def< TYPE >::copy(pdst, psrc);
//
//      }
//
//
//      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
//      {
//
//         copier::def< TYPE >::copy_count(pdst, psrc, c);
//
//      }
//
//      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
//      {
//
//         while (c > 0)
//         {
//            copy(pdst, &src);
//            pdst++;
//            c--;
//         }
//
//      }
//
//      
//      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
//      {
//
//         while (c > 0)
//         {
//            copy(pdst, psrc);
//            c--;
//            pdst++;
//            psrc++;
//         }
//
//      }
//
//
//#if MEMDLEAK || defined(__MCRTDBG)
//      inline  TYPE * alloc(::collection::count c, const char * pszFile, int iLine)
//      {
//
//         return heap::sys < TYPE >::alloc(c, pszFile, iLine);
//
//      }
//#else
//      inline  TYPE * alloc(::collection::count c)
//      {
//
//         return heap::sys < TYPE >::alloc(c);
//
//      }
//#endif
//
//      inline  void _free(TYPE * p)
//      {
//
//         heap::sys < TYPE >::_free(p);
//
//      }
//
//
//   };


} // namespace allocator



