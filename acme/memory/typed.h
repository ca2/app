// Created by camilo on 2022-10-23 12:25 <3ThomasBorregaardSorensen!!
#pragma once


template < typename TYPE >
inline void def_destruct(TYPE * pointer)
{

   pointer->~TYPE();

}


template < typename TYPE >
inline void def_destruct(::pointer<TYPE> pointer)
{

   pointer->release();

}


template < typename TYPE >
inline void copy_construct_count(TYPE * p, ::collection::count c, const TYPE & t)
{

   while (c > 0)
   {

      new(p)TYPE(t);

      p++;

      c--;

   }

}


template < typename TYPE >
inline void copy_construct_count(TYPE * p, ::collection::count c, const TYPE * psource)
{

   while (c > 0)
   {

      new(p)TYPE(*psource);

      p++;

      psource++;

      c--;

   }

}


namespace constructor
{


   template < typename TYPE >
   class def
   {
   public:

      inline  void construct(void * p)
      {
         ::new(p) TYPE;
      }
      inline  void construct_count(void * p, ::collection::count c)
      {
         while (c > 0)
         {
            ::new(p) TYPE;
            ((TYPE *&)p)++;
            c--;
         }
      }



   };


   template < typename TYPE >
   class zero
   {
   public:

      inline  void construct(void * p)
      {

         ::zero(p, sizeof(TYPE));

      }

      inline  void construct_count(void * p, ::collection::count c)
      {

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            ((::u8 *&)p) += sizeof(TYPE);

            c--;

         }

      }



   };


   template < typename TYPE >
   class nodef
   {
   public:

      inline  void construct(void * p)
      {
         __UNREFERENCED_PARAMETER(p);
      }
      inline  void construct_count(void * p, ::collection::count c)
      {
         __UNREFERENCED_PARAMETER(p);
         __UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor


namespace destructor
{


   template < typename TYPE >
   class def
   {
   public:

      
      inline void destruct(TYPE * pointer)
      {

         def_destruct(pointer);

      }


      inline void destruct_count(TYPE * pointer, ::collection::count c)
      {

         while (c > 0)
         {

            def_destruct(pointer);

            pointer++;

            c--;

         }

      }


   };


   template < typename TYPE >
   class nodef
   {
   public:

      inline  void destruct(TYPE * p)
      {
         __UNREFERENCED_PARAMETER(p);
      }
      inline  void destruct_count(TYPE * p, ::collection::count c)
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

      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         *pdst = *psrc;

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
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





// Created by camilo on 2022-10-23 12:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "typed.h"


namespace typed
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

      
      inline void destruct(TYPE * p)
      {
         
         destructor::nodef < TYPE >::destruct(p);

      }


      inline void destruct_count(TYPE * p, ::collection::count c)
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


      inline void destruct(TYPE * pointer)
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


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {

            ::new (pdst) TYPE(src);

            pdst++;

            c--;

         }

      }


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            ::new (pdst) TYPE(*psrc);

            c--;

            pdst++;

            psrc++;

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
      public destructor::def< TYPE >
   {
   public:


      inline void construct(TYPE * p)
      {

         constructor::def< TYPE >::construct(p);

      }


      inline  void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::def< TYPE >::construct_count(p, c);

      }


      inline void destruct(TYPE * pointer)
      {

         destructor::def< TYPE >::destruct(pointer);

      }


      inline void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::def< TYPE >::destruct_count(pointer, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE));

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE) * c);

      }


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE & src)
      {

         while (c > 0)
         {
            
            memory_copy(pdst, &src, sizeof(TYPE));

            pdst++;
            
            c--;

         }

      }


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         memory_copy(pdst, psrc, sizeof(TYPE) * c);

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
   class nodef :
      public constructor::nodef< TYPE >,
      public destructor::nodef< TYPE >,
      public copier::def< TYPE >
   {
   public:


      inline  void construct(TYPE * p)
      {

         constructor::nodef< TYPE >::construct(p);

      }


      inline  void construct_count(TYPE * p, ::collection::count c)
      {

         constructor::nodef< TYPE >::construct_count(p, c);

      }


      inline  void destruct(TYPE * pointer)
      {

         destructor::nodef< TYPE>::destruct(pointer);

      }


      inline  void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(pointer, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
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


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {

            copy(pdst, psrc);

            c--;

            pdst++;

            psrc++;

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
   class raw :
      public constructor::nodef< TYPE >,
      public destructor::nodef< TYPE>
   {

   public:

      inline  void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline  void construct_count(TYPE * p, ::collection::count c)
      {
         constructor::nodef< TYPE >::construct_count(p, c);

      }


      inline  void destruct(TYPE * pointer)
      {

         destructor::nodef< TYPE>::destruct(pointer);

      }


      inline  void destruct_count(TYPE * pointer, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(pointer, c);

      }


      inline  void copy(TYPE * pdst, const TYPE * psrc)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE));

      }


      inline  void copy_count(TYPE * pdst, const TYPE * psrc, ::collection::count c)
      {

         memory_transfer(pdst, psrc, sizeof(TYPE) * c);

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

      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {
            copy(pdst, psrc);
            c--;
            pdst++;
            psrc++;
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
      public constructor::nodef< TYPE >,
      public copier::def< TYPE >
   {
   public:


      inline  void construct(TYPE * p)
      {
         constructor::zero< TYPE >::construct(p);
      }

      inline  void construct_count(TYPE * p, ::collection::count c)
      {
         constructor::zero< TYPE >::construct_count(p, c);

      }

      
      inline  void destruct(TYPE * p)
      {

         destructor::nodef< TYPE>::destruct(p);

      }


      inline  void destruct_count(TYPE * p, ::collection::count c)
      {

         destructor::nodef< TYPE>::destruct_count(p, c);

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


      inline  void copy_construct_count(TYPE * pdst, ::collection::count c, const TYPE * psrc)
      {

         while (c > 0)
         {
            
            copy(pdst, psrc);

            pdst++;

            c--;

            psrc++;

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


} // namespace typed



