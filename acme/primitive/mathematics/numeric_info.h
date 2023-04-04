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

      static constexpr TYPE maximum()
      {
         return (TYPE) 0;
      }
      static constexpr TYPE minimum()
      {
         return (TYPE) 0;
      }
      static constexpr TYPE null()
      {
         return (TYPE) 0;
      }
      static constexpr TYPE unitary()
      {
         return (TYPE) 1;
      }
      static inline TYPE allset()
      {
         TYPE t;
         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t, 0xff, sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = true;

   };


   template < >
   class CLASS_DECL_ACME numeric_info < ::u32 > :
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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t, 0xff, sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };

#if !defined(LINUX) && !defined(FREEBSD)

   template < >
   class CLASS_DECL_ACME numeric_info < ::i64 > :
      public numeric_integer_base
   {
   public:

      typedef i64 TYPE;
      typedef i64 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)LLONG_MAX;
      }
      static consteval TYPE minimum()
      {
         return (TYPE)LLONG_MIN;
      }
      static consteval TYPE null()
      {
         return (TYPE)0;
      }
      static consteval TYPE unitary()
      {
         return (TYPE)1;
      }
      //static consteval TYPE allset()
      //{
      //   TYPE t;
      //   memory_set(&t,0xff,sizeof(TYPE));
      //   return t;
      //}

      static const bool is_signed = true;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < u64 >:
      public numeric_integer_base
   {
   public:

      typedef u64 TYPE;
      typedef i64 OFFSET_TYPE;

      static consteval TYPE maximum()
      {
         return (TYPE)ULLONG_MAX;
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
      /*static consteval TYPE allset()
      {
         TYPE t;
         memory_set(&t,0xff,sizeof(TYPE));
         return t;
      }*/

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
//         memory_set(&t,0xff,sizeof(TYPE));
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
//         memory_set(&t,0xff,sizeof(TYPE));
//         return t;
//      }

      static const bool is_signed = false;

   };

   template < >
   class CLASS_DECL_ACME numeric_info < std::strong_ordering > 
   {
   public:

      using INTERNAL_TYPE = std::strong_ordering;

      using INTERNAL_INFO = std::strong_ordering;

      static consteval auto null()
      {
         return nullptr;
      }
      //static consteval auto unitary()
      //{
      //   return INTERNAL_INFO::unitary();
      //}
      //static consteval auto allset()
      //{
      //   return INTERNAL_INFO::allset();
      //}
      //static consteval auto minimum()
      //{
      //   return ;
      //}
      //static consteval auto maximum()
      //{
      //   return 1;
      //}
      //template < typename T2 >
      //static consteval auto natural(const T2 & t2)
      //{
      //   return minimum(maximum(), maximum(null(), (T)t2));
      //}

   };

} // namespace numeric_info_internal

template <typename T>
struct remove_const {
   using type =  T;
};

template <typename T>
struct remove_const< const T > {
   using type = T;
};

template <typename T>
struct remove_reference {
   using type = T;
};

template <typename T>
struct remove_reference< T & > {
   using type = T;
};

template <typename T>
struct remove_reference< T&& > {
   using type = T;
};


template < typename T >
class numeric_info
{
public:

   using INTERNAL_TYPE = typename remove_reference < typename remove_const < T >::type >::type;

   using INTERNAL_INFO = numeric_info_internal::numeric_info < INTERNAL_TYPE > ;

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
   static consteval auto natural(const T2 & t2)
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



