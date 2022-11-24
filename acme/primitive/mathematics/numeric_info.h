#pragma once


#include <limits.h>
#include <memory.h>
#include <float.h>

namespace numeric_info_internal
{

   class numeric_info_base
   {
   public:

      static const bool is_signed = false;
      static const bool is_integer = false;

   };


   template < typename T >
   class numeric_info:
      public numeric_info_base
   {
   public:

      typedef T TYPE;
      typedef T OFFSET_TYPE;

      static inline TYPE maximum()
      {
         return (TYPE) 0;
      }
      static inline TYPE minimum()
      {
         return (TYPE) 0;
      }
      static inline TYPE null()
      {
         return (TYPE) 0;
      }
      static inline TYPE unitary()
      {
         return (TYPE) 1;
      }
      static inline TYPE allset()
      {
         TYPE t;
         __memset(&t,0xff,sizeof(TYPE));
         return t;
      }



   };


   class numeric_integer_base:
      public numeric_info_base
   {
   public:

      static const bool is_integer = true;

   };


   class numeric_floating_base:
      public numeric_info_base
   {
   public:

      static const bool is_integer = false;

   };


   template < >
   class CLASS_DECL_ACME numeric_info < i8 > :
      public numeric_integer_base
   {
   public:

      typedef i8 TYPE;
      typedef i8 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)INT8_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)INT8_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static inline TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < u8 > :
      public numeric_integer_base
   {
   public:

      typedef u8 TYPE;
      typedef i8 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)UINT8_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)0;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };
   template < >
   class CLASS_DECL_ACME numeric_info < i16 > :
      public numeric_integer_base
   {
   public:

      typedef i16 TYPE;
      typedef i16 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)INT16_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)INT16_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < u16 > :
      public numeric_integer_base
   {
   public:

      typedef u16 TYPE;
      typedef i16 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)UINT16_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)0;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static inline TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < i32 > :
      public numeric_integer_base
   {
   public:

      typedef i32 TYPE;
      typedef i32 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)INT32_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)INT32_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = true;

   };


   template < >
   class CLASS_DECL_ACME numeric_info < long > :
      public numeric_integer_base
   {
   public:

      typedef long TYPE;
      typedef long OFFSET_TYPE;

      static consteval TYPE maximum()
      {
#ifdef __LP64__
         return (TYPE)LLONG_MAX;
#else
         return (TYPE)LONG_MAX;
#endif
      }
      static consteval TYPE minimum()
      {
#ifdef __LP64__
         return (TYPE)LLONG_MIN;
#else
         return (TYPE)LONG_MIN;
#endif
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t, 0xff, sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = true;

   };


   template < >
   class CLASS_DECL_ACME numeric_info < u32 > :
      public numeric_integer_base
   {
   public:

      typedef u32 TYPE;
      typedef i32 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)UINT32_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)0;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };


   template < >
   class CLASS_DECL_ACME numeric_info < unsigned long > :
      public numeric_integer_base
   {
   public:

      typedef u32 TYPE;
      typedef i32 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)ULONG_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)0;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t, 0xff, sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };

#if !defined(LINUX) && !defined(FREEBSD)

   template < >
   class CLASS_DECL_ACME numeric_info < i64 > :
      public numeric_integer_base
   {
   public:

      typedef i64 TYPE;
      typedef i64 OFFSET_TYPE;

      static inline TYPE maximum()
      {
         return (TYPE)LLONG_MAX;
      }
      static inline TYPE minimum()
      {
         return (TYPE)LLONG_MIN;
      }
      static inline TYPE null()
      {
         return (TYPE)0;
      }
      static inline TYPE unitary()
      {
         return (TYPE)1;
      }
      static inline TYPE allset()
      {
         TYPE t;
         __memset(&t,0xff,sizeof(TYPE));
         return t;
      }

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < u64 >:
      public numeric_integer_base
   {
   public:

      typedef u64 TYPE;
      typedef i64 OFFSET_TYPE;

      static inline TYPE maximum()
      {
         return (TYPE)ULLONG_MAX;
      }
      static inline TYPE minimum()
      {
         return (TYPE)0;
      }
      static inline TYPE null()
      {
         return (TYPE)0;
      }
      static inline TYPE unitary()
      {
         return (TYPE)1;
      }
      static inline TYPE allset()
      {
         TYPE t;
         __memset(&t,0xff,sizeof(TYPE));
         return t;
      }

      static const bool is_signed = false;

   };


#endif


   template < >
   class CLASS_DECL_ACME numeric_info < float >:
      public numeric_floating_base
   {
   public:

      typedef float TYPE;
      typedef float OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)FLT_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)FLT_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0.f;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1.f;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

   };



   template < >
   class CLASS_DECL_ACME numeric_info < double >:
      public numeric_floating_base
   {
   public:

      typedef double TYPE;
      typedef double OFFSET_TYPE;


      static consteval TYPE maximum()
      {
         return (TYPE)DBL_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)DBL_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0.0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1.0;
      }
//      static consteval TYPE allset()
//      {
//         TYPE t;
//         __memset(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };


} // namespace numeric_info_internal



template < typename T >
class numeric_info:
   public numeric_info_internal::numeric_info < T >
{
public:

   typedef numeric_info_internal::numeric_info < T > INTERNAL_INFO;

   static consteval auto null()
   {
      return INTERNAL_INFO::null();
   }
   static consteval auto unitary()
   {
      return INTERNAL_INFO::unitary();
   }
   static consteval auto allset()
   {
      return INTERNAL_INFO::allset();
   }
   static consteval auto minimum()
   {
      return INTERNAL_INFO::minimum();
   }
   static consteval auto maximum()
   {
      return INTERNAL_INFO::maximum();
   }
   template < typename T2 >
   static constexpr auto natural(const T2 & t2)
   {
      return minimum(maximum(), maximum(null(), (T) t2));
   }

};


//template < typename T, typename T2 >
//inline T clip_assign(T & t, const T2 & t2)
//{
//   t = minimum(::numeric_info < T >::maximum(),maximum(::numeric_info < T >::minimum(),(T)t2));
//}

template < typename T,typename T2 >
inline T natural_assign(T & t,const T2 & t2)
{
   t = minimum(::numeric_info < T >::maximum(),maximum(::numeric_info < T >::null(),(T)t2));
}

template < typename T >
T & minimum(T & t)
{

   return t = numeric_info<T>::minimum();

}



