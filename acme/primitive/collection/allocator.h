// Created by camilo on 2022-10-23 03:10 <3ThomasBorregaardSorensen!!
#pragma once


namespace allocator
{


   template < typename TYPE >
   class allocator
   {
   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct_count(p, c);

      }

      inline static void destruct(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef < TYPE >::destruct(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * p, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef < TYPE >::destruct_count(p, c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }

   };


   template < typename TYPE >
   class def
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct_count(p, c);
      }

      inline static void destruct(TYPE * pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * pointer, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct_count(pointer, c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }

#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };



   template < typename TYPE >
   class rawcopy
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct_count(p, c);
      }

      inline static void destruct(TYPE * pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * pointer, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct_count(pointer, c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         memmove(pdst, psrc, sizeof(TYPE));

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         memmove(pdst, psrc, sizeof(TYPE) * c);

      }


      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         /*   while (c > 0)
            {
               copy(pdst, &src);
               c--;
            }*/

         throw_exception(error_not_supported);

      }


#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }

#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };




   template < typename TYPE >
   class nodef
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct_count(p, c);

      }

      inline static void destruct(TYPE * pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * pointer, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct_count(pointer, c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };


   template < typename TYPE >
   class raw
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct_count(p, c);

      }

      inline static void destruct(TYPE * pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct(pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * pointer, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct_count(pointer, c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         memmove(pdst, psrc, sizeof(TYPE));

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         memmove(pdst, psrc, sizeof(TYPE) * c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };


   template < typename TYPE >
   class zero
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::zero< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::zero< TYPE >::construct_count(p, c);

      }

      inline static void destruct(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct(p  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * p, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::nodef< TYPE>::destruct_count(p, c  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < typename TYPE >
   class sys
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct_count(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct_count(p, c);

      }

      inline static void destruct(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }
      inline static void destruct_count(TYPE * p, ::count c OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS)
      {
         destructor::def< TYPE>::destruct_count(p, c  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
      }


      inline static void copy(TYPE * pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy_count(TYPE * pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy_count(pdst, psrc, c);

      }

      inline static void copy_construct_count(TYPE * pdst, ::count c, const TYPE & src)
      {

         while (c > 0)
         {
            copy(pdst, &src);
            c--;
         }

      }


#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::sys < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::sys < TYPE >::alloc(c);

      }
#endif

      inline static void _free(TYPE * p)
      {

         heap::sys < TYPE >::_free(p);

      }


   };


} // namespace allocator



