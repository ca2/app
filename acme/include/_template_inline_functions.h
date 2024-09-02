// Created by camilo on 2022-11-08 23:10 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_number NUMBER1, primitive_number NUMBER2 >
void cast_copy(NUMBER1 & n1, NUMBER2 n2)
{
   
   n1 = (NUMBER1) n2;
   
}


template < typename A, typename B >
inline void swap(A & a, B & b)
{

   auto t = a;

   a = b;

   b = t;

}


template < typename TYPE >
constexpr memsize index_of(const TYPE * p, const TYPE * pBegin)
{

   return ::is_set(p) ? (::memsize)(p - pBegin) : -1;

}


template < primitive_character CHARACTER >
constexpr bool string_compare_prefix(::std::strong_ordering & ordering, const CHARACTER * pszA, const CHARACTER * pszB) noexcept
{

   if (::is_empty(pszA))
   {

      if (::is_empty(pszB))
      {

         ordering = ::std::strong_ordering::equal;

         return true;

      }
      else
      {

         ordering = ::std::strong_ordering::less;

         return true;

      }

   }
   else if (::is_empty(pszB))
   {

      ordering = ::std::strong_ordering::greater;

      return true;

   }

   return false;

}



/// initially for __utosz_internal and __utosz
/// by camilo on 2022-12-09 00:48 <3ThomasBorregaardSorensen!!
template < typename TYPE >
void reverse(TYPE * begin, TYPE * end)
{

   while (true)
   {

      end--;

      if (end <= begin) return;

      ::swap(*begin, *end);

      begin++;

   }

}

#include "acme/primitive/collection/pair.h"
//template < typename A, typename B >
//struct as_p
//{
//   A a; B b; };
//

//template<typename A, typename B>
//auto as_ab(A a, B b)
//{
//
//   return _as_ab<A, B>{a, b};
//
//}

//auto f() { return many{ string(),5.7, unmovable() }; };


template < primitive_signed SIGNED >
constexpr auto as_absolute_unsigned(SIGNED i)
{

   bool bNegative;

   return ::make_pair{ (typename std::make_unsigned<SIGNED>::type) ((bNegative = i < 0) ? -i : i), bNegative };

}
//::pair<int, int> ia;
//inline ::u64 make64_from32(::u32 l, ::u32 h)
//{
//
//   return ((::u64)l) | (((::u64)h) << 32);
//
//}
//
//
//inline bool is_memory_segment_ok(const void* p, memsize size, bool bReadWrite)
//{
//
//#ifdef DEEP_DEBUG
//
//   ::u8* pbyte = (::u8*)p;
//
//   if (bReadWrite)
//   {
//
//      for (::collection::index i = 0; i < size; i++)
//      {
//
//         ::u8& b = *pbyte;
//
//         b++; // tests read/write of ::u8 b
//
//         b--; // restablish it
//
//      }
//
//   }
//   else
//   {
//
//      ::i32 sum = 0;
//
//      for (::collection::index i = 0; i < size; i++)
//      {
//
//         ::u8& b = *pbyte;
//
//         sum += b; // tests read of ::u8 b
//
//      }
//
//   }
//
//#endif // DEEP_DEBUG
//
//   return ::is_set(p);
//
//}
//
//
//inline bool is_string_ok(const ::wide_character* pwsz, memsize nMaxLength)
//{
//
//   return ::is_memory_segment_ok(pwsz, nMaxLength);
//
//}
//
//
//inline bool is_string_ok(const ::scoped_string & scopedstr, memsize nMaxLength)
//{
//
//   return ::is_memory_segment_ok(psz, nMaxLength);
//
//}
//
//
//
//inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, strsize srclen)
//{
//
//   return (((::u8*)pszSrc) <= ((::u8*)pszDst) && ((::u8*)pszSrc) + srclen > ((::u8*)pszDst))
//      || (((::u8*)pszDst) <= ((::u8*)pszSrc) && ((::u8*)pszDst) + srclen > ((::u8*)pszSrc));
//
//}
//


//template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p)
//{
//
//   if (!p) p = ::place(new TYPE());
//
//   return p;
//
//}


inline const ::particle * context_trace_object() { return general_trace_object(); }


#ifdef CPP17

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
{
   return (bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);

}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
{
   return !(bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);

}

#endif

//
//
//inline const ::particle* trace_object(const ::particle* pparticle) { return pparticle; }
//
//
//inline bool failed(const ::payload& payload) { return !::succeeded(payload); }
//
//
//
//inline int read_char(u8*& pdata, memsize& s, char* pch)
//{
//
//   if (s < 1)
//   {
//
//      return 0;
//
//   }
//
//   *pch = (char)*pdata;
//
//   pdata++;
//
//   s--;
//
//   return 1;
//
//}
//




template < typename TYPE >
inline bool is_reference_null(const TYPE& t)
{

   return is_null(&t);

}


template < typename TYPE >
inline bool is_reference_set(const TYPE& t)
{

   return is_set(&t);

}

//
//
//inline bool is_impact_group(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 1000; }
//
//
//inline bool is_impact_subgroup(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 100; }
//
//
//inline bool is_file_or_folder(const ::file::enum_type& etype)
//{
//
//   return (etype & ::file::e_type_file_or_folder) > ::file::e_type_exists;
//
//}
//
//
//inline bool exists(const ::file::enum_type& etype)
//{
//
//   return etype & ::file::e_type_exists;
//
//}
//

template < class T >
inline void __dynamic_cast(T*& ptarget, T* psource)
{

   ptarget = psource;

}


template < class T , typename T2 >
inline void __dynamic_cast(T * & ptarget, T2 * psource)
{

   ptarget = dynamic_cast < T * >(psource);

}


template < typename T1, typename T2 >
inline bool __sort(T1& t1, T2& t2)
{

   if (t2 >= t1)
   {

      return false;

   }

   auto t = t2;

   t2 = t1;

   t1 = t;

   return true;

}


//
//
//
//
//
//inline i64 ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
//{
//
//   return strtoll(psz, (::ansi_character **) ppszEnd, iBase);
//
//}
//
//inline u64 ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
//{
//
//   return strtoull(psz, (::ansi_character **) ppszEnd, iBase);
//
//}
//
//
//inline i32 ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
//{
//
//#ifdef WINDOWS
//
//   return strtol(psz, (::ansi_character **) ppszEnd, iBase);
//
//#else
//
//   long l = strtol(psz, (::ansi_character **) ppszEnd, iBase);
//
//   if(l > INT_MAX)
//   {
//
//      errno = ERANGE;
//
//      return INT_MAX;
//
//   }
//   else if(l < INT_MIN)
//   {
//
//      errno = ERANGE;
//
//      return INT_MIN;
//
//   }
//
//   return (::i32) l;
//
//#endif
//
//}
//
//
//inline u32 ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
//{
//
//#ifdef WINDOWS
//
//   return strtoul(psz, (::ansi_character **) ppszEnd, iBase);
//
//#else
//
//   unsigned long ul = strtoul(psz, (::ansi_character **) ppszEnd, iBase);
//
//   if(ul > UINT_MAX)
//   {
//
//      errno = ERANGE;
//
//      return UINT_MAX;
//
//   }
//
//   return (::u32) ul;
//
//#endif
//
//}
//
//

template < primitive_integral SECOND, primitive_integral NANOSECOND >
constexpr void normalize_second_nanosecond(SECOND & second, NANOSECOND & nanosecond)
{

   auto extrasecond = nanosecond > 0 ? (nanosecond / 1'000'000'000) : ((nanosecond / 1'000'000'000) - 1);

   second += extrasecond;

   nanosecond -= extrasecond * 1'000'000'000;

}



template < primitive_integral SECOND1, primitive_integral NANOSECOND1, primitive_integral SECOND2, primitive_integral NANOSECOND2 >
constexpr void add_second_nanosecond(SECOND1 & second1, NANOSECOND1 & nanosecond1, const SECOND2 & second2, const NANOSECOND2 & nanosecond2)
{

   auto nanos = nanosecond1 + nanosecond2;

   auto extrasecond = nanos > 0 ? (nanos / 1'000'000'000) : ((nanos / 1'000'000'000) - 1);

   second1 = second1 + second2 + extrasecond;

   nanosecond1 = nanos - extrasecond * 1'000'000'000;

}



template < primitive_integral SECOND1, primitive_integral NANOSECOND1, primitive_integral SECOND2, primitive_integral NANOSECOND2 >
constexpr void subtract_second_nanosecond(SECOND1 & second1, NANOSECOND1 & nanosecond1, const SECOND2 & second2, const NANOSECOND2 & nanosecond2)
{

   auto nanos = nanosecond1 - nanosecond2;

   auto extrasecond = nanos > 0 ? (nanos / 1'000'000'000) : ((nanos / 1'000'000'000) - 1);

   second1 = second1 - second2 + extrasecond;

   nanosecond1 = nanos - extrasecond * 1'000'000'000;

}


template < typename TYPE >
constexpr TYPE * find_first_null_character(TYPE * p)
{

   TYPE t{};

   while (*p != t)
   {

      p++;

   }

   return p;

}


template < typename TYPE, ::comparison::equality < TYPE > EQUALITY >
constexpr const TYPE * find_first_null_character(const TYPE * p, EQUALITY equality)
{

   TYPE t{};

   while (!equality.equals(*p, t))
   {

      p++;

   }

   return p;

}


template < primitive_fundamental INTEGRAL >
constexpr ::collection::count count_until_zero_item_type(const INTEGRAL * p)
{

   ::collection::count c = 0;

   while (*p)
   {

      p++;

      c++;

   }

   return c;

}



template < primitive_character CHARACTER >
constexpr void null_terminate(CHARACTER * & p)
{

   *p = (CHARACTER)0;

}


template < primitive_character CHARACTER >
constexpr void append_and_step_if_true(bool b, CHARACTER *& p, CHARACTER character)
{

   if (b) *p++ = character;

}



template < primitive_iterator ITERATOR, primitive_iterator BEGIN >
constexpr bool iterator_is_before_begin(ITERATOR p, BEGIN)
{

   return p.is_null();

}



template < primitive_iterator ITERATOR, primitive_iterator END >
constexpr bool iterator_is_end(ITERATOR p, END)
{

   return p.is_null();

}


template < primitive_iterator ITERATOR, primitive_iterator BEGIN, primitive_iterator END >
constexpr bool iterator_is_ok(ITERATOR p, BEGIN, END)
{

   return p.is_ok();

}


template < typename TYPE, typename BEGIN >
constexpr bool iterator_is_before_begin(const TYPE * p, const BEGIN * begin)
{

   return p < begin;

}


template < typename TYPE, typename END >
constexpr bool iterator_is_end(const TYPE * p, const END * end)
{

   return p >= end;

}


template < typename TYPE, typename BEGIN, typename END >
constexpr bool iterator_is_ok(const TYPE * p, const BEGIN * begin, const END * end)
{

   return p >= begin && p < end;

}


template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
bool is_empty(const ITEM * p, EQUALITY equality)
{

   return ::is_null(p) || equality.equals(*p, 0);

}


template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool _initialize_null_terminated_contains_null_terminated(bool & b, const ITEM * pz, const ITEM * pzPrefix, EQUALITY equality)
{

   if (::is_empty(pzPrefix, equality))
   {

      b = true;

      return true;

   }

   if (::is_empty(pz, equality))
   {

      b = false;

      return true;

   }


   return false;

}


template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool _null_terminated_begins_null_terminated(const ITEM * pz, const ITEM * pzPrefix, EQUALITY equality)
{

   do
   {

      if (!equality.equals(*pz, *pzPrefix))
      {

         return false;

      }

      pz++;

      pzPrefix++;

   } while (!equality.equals(*pz,0) && !equality.equals(*pzPrefix, 0));

   return equality.equals(*pzPrefix, 0);

}


template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool null_terminated_begins_null_terminated(const ITEM * pz, const ITEM * pzPrefix, EQUALITY equality)
{

   bool b;

   if (_initialize_null_terminated_contains_null_terminated(b, pz, pzPrefix, equality))
   {

      return b;

   }

   return _null_terminated_begins_null_terminated(pz, pzPrefix, equality);

}


#include "acme/primitive/mathematics/_.h"


template < typename TYPE >
TYPE * clipped_add(TYPE * p, ::collection::count c, const non_const<TYPE> * begin, const non_const<TYPE> * end)
{

   if (c > 0)
   {

      p = minimum(p + c, end);

   }
   else
   {

      p = maximum(p + c, begin - 1);

   }

   return p;

}





template < primitive_iterator ITERATOR, typename T1, typename T2 >
ITERATOR clipped_add(ITERATOR p, ::collection::count c, T1, T2)
{

   if (c > 0)
   {

      while (p.is_set() && c > 0)
      {

         p = p.next();

         c--;

      }


   }
   else
   {

      while (p.is_set() && c < 0)
      {

         p = p.back();

         c++;

      }


   }

   return p;

}



template < primitive_signed SIGNED >
bool found(SIGNED s)
{

   return s >= 0;

}


template < typename T >
bool found(const T * p)
{

   return ::is_set(p);

}


template < primitive_signed SIGNED >
bool not_found(SIGNED s)
{

   return !found(s);

}


template < typename T >
bool not_found(const T * p)
{

   return !found(p);

}


//template < primitive_floating FLOATING, int len >
//inline ::string as_string(FLOATING f, const ::ansi_character * pszFormat = "%f");


template < typename BOOLEAN, typename ASSIGNED, typename ASSIGNEE >
inline void set_if_different(BOOLEAN& bSetIfChanged, ASSIGNED& left, const ASSIGNEE& right)
{

   if (left != right)
   {

      bSetIfChanged = true;

      left = right;

   }

}



template < primitive_XYDim XYDim, typename X, typename Y, typename W, typename H >
inline XYDim & set_dim(XYDim & rectTarget, X x, Y y, W w, H h)
{

   cast_copy(rectTarget.X, x);
   cast_copy(rectTarget.Y, y);
   cast_copy(rectTarget.Width, w);
   cast_copy(rectTarget.Height, h);

   return rectTarget;

}


//template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
//void copy(RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
//{
//
//   cast_copy(rectangle1.left()    , rectangle2.left()    );
//   cast_copy(rectangle1.top()     , rectangle2.top()     );
//   cast_copy(rectangle1.right()   , rectangle2.right()   );
//   cast_copy(rectangle1.bottom()  , rectangle2.bottom()  );
//
//}


template < primitive_rectangle RECTANGLE, primitive_xydim XYDIM >
void copy(RECTANGLE & rectangle, const XYDIM  & xydim)
{

   cast_copy(rectangle.left()     , xydim.x);
   cast_copy(rectangle.top()      , xydim.y);
   cast_copy(rectangle.right()    , xydim.x + xydim.width);
   cast_copy(rectangle.bottom()   , xydim.y + xydim.height);

}


template < primitive_origin_size ORIGIN_SIZE, primitive_rectangle RECTANGLE >
void copy(ORIGIN_SIZE & originsize, const RECTANGLE & rectangle)
{

   cast_copy(originsize.origin.x      , rectangle.left());
   cast_copy(originsize.origin.y      , rectangle.top());
   cast_copy(originsize.size.width    , rectangle.right() - rectangle.left());
   cast_copy(originsize.size.height   , rectangle.bottom() - rectangle.top());

}


template < primitive_rectangle RECTANGLE1, primitive_origin_size RECTANGLE2 >
void copy(RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   cast_copy(rectangle1.left()    , rectangle2.origin.x);
   cast_copy(rectangle1.top()     , rectangle2.origin.y);
   cast_copy(rectangle1.right()   , rectangle2.origin.x + rectangle2.size.width);
   cast_copy(rectangle1.bottom()  , rectangle2.origin.y + rectangle2.size.height);

}


// template < primitive_rectangle RECTANGLE, origin_size ORIGIN_SIZE >
// constexpr void copy(RECTANGLE& rectangle, const ORIGIN_SIZE& origin_size)
// {

//    rectangle.left() = (decltype(rectangle.left()))origin_size.origin.x();
//    rectangle.top() = (decltype(rectangle.top()))origin_size.origin.y();
//    rectangle.right() = (decltype(rectangle.right()))(origin_size.origin.x() + origin_size.size.width);
//    rectangle.bottom() = (decltype(rectangle.bottom()))(origin_size.origin.y() + origin_size.size.height);

// }


// template < origin_size ORIGIN_SIZE, primitive_rectangle RECTANGLE >
// constexpr void copy(ORIGIN_SIZE& origin_size, const RECTANGLE& rectangle)
// {

//    origin_size.origin.x() = (decltype(origin_size.origin.x()))rectangle.left();
//    origin_size.origin.y() = (decltype(origin_size.origin.y()))rectangle.top();
//    origin_size.size.width = (decltype(origin_size.size.width))(rectangle.right() - rectangle.left());
//    origin_size.size.height = (decltype(origin_size.size.height))(rectangle.bottom() - rectangle.top());

// }







template < primitive_XY POINT1, primitive_point POINT2 >
void copy(POINT1 point1, const POINT2 & point2)
{

   cast_copy(point1.X, point2.x());
   cast_copy(point1.Y, point2.y());

}


template < primitive_point POINT1, primitive_XY POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   cast_copy(point1.x(), point2.X);
   cast_copy(point1.y(), point2.Y);

}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
void copy(RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   cast_copy(rectangle1.left(), rectangle2.left());
   cast_copy(rectangle1.top(), rectangle2.top());
   cast_copy(rectangle1.right(), rectangle2.right());
   cast_copy(rectangle1.bottom(), rectangle2.bottom());

}


template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
void copy(XYDim & xydim, const RECTANGLE & rectangle)
{

   cast_copy(xydim.X, rectangle.left());
   cast_copy(xydim.Y, rectangle.top());
   cast_copy(xydim.Width, rectangle.right() - rectangle.left());
   cast_copy(xydim.Height, rectangle.bottom() - rectangle.top());

}


template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
void copy(RECTANGLE & rectangle, const XYDim & xydim)
{

   cast_copy(rectangle.left(), xydim.X);
   cast_copy(rectangle.top(), xydim.Y);
   cast_copy(rectangle.right(), xydim.X + xydim.Width);
   cast_copy(rectangle.bottom(), xydim.Y + xydim.Height);

}


template < primitive_xydim XYDIM, primitive_rectangle RECTANGLE >
void copy(XYDIM & xydim, const RECTANGLE & rectangle)
{

   cast_copy(xydim.x, rectangle.left());
   cast_copy(xydim.y, rectangle.top());
   cast_copy(xydim.width, rectangle.right() - rectangle.left());
   cast_copy(xydim.height, rectangle.bottom() - rectangle.top());

}


template < primitive_XYDim XYDim1, primitive_XYDim XYDim2 >
void copy(XYDim1 & xydim1, const XYDim2 & xydim2)
{

   cast_copy(xydim1.X, xydim2.X);
   cast_copy(xydim1.Y, xydim2.Y);
   cast_copy(xydim1.Width, xydim2.Width);
   cast_copy(xydim1.Height, xydim2.Height);

}


template < primitive_point POINT1, primitive_point POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   cast_copy(point1.x(), point2.x());
   cast_copy(point1.y(), point2.y());

}


template < primitive_point POINT1, raw_primitive_point POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   cast_copy(point1.x(), point2.x());
   cast_copy(point1.y(), point2.y());

}


template < raw_primitive_point POINT1, primitive_point POINT2 >
void copy(POINT1 & point1, const POINT2 & point2)
{

   cast_copy(point1.x, point2.x());
   cast_copy(point1.y, point2.y());

}


template < primitive_point POINT, primitive_size SIZE >
void copy(POINT & point, const SIZE & size)
{

   cast_copy(point.x(), size.cx());
   cast_copy(point.y(), size.cy());

}


template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
void copy(SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
{

   cast_copy(size1.cx(), size2.cx());
   cast_copy(size1.cy(), size2.cy());

}


template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }



