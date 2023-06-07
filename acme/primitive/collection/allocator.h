// Created by camilo on 2022-10-23 03:10 <3ThomasBorregaardSorensen!!
#pragma once



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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
public allocator < TYPE, ::heap::default_memory_allocator>
   {

   };


   template < typename TYPE >
   class processor_cache_oriented : // would it help for data-orientation-assumation ??!?!
      public allocator < TYPE, processor_cache_oriented_memory_allocator >
   {


   };


   template < typename TYPE >
   class sys :
      public allocator < TYPE, ::heap::system_memory_allocator>
   {

   };



} // namespace memory


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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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
      inline static TYPE * alloc(::count c, const ::scoped_string & scopedstrFile, int iLine)
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



