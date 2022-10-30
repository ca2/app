//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:30
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once




//constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }

template < typename DERIVED, typename BASE >
concept is_derived_from =
::std::is_base_of < BASE, DERIVED >::value;


template < typename FILE >
class binary_stream;
template < typename RESULT >
class process;


template<class T>
class pointer;


template<class T>
class pointer_array;



template<class T>
class pointer;


template<class T>
class pointer_array;


using image_pointer = ::pointer<::image>;


namespace write_text
{


   using font_pointer = ::pointer<font>;


} // namespace write_text




template<typename Type, typename RawType = Type, ::enum_type m_etypeContainer = e_type_element >
class string_array_base;


template<typename CHAR_TYPE>
class string_base;



#define CONSIDER_AS(as, use) using use = as


using ansistring = string_base<ansichar>;
using wd16string = string_base<wd16char>;
using wd32string = string_base<wd32char>;
using widestring = string_base<widechar>;


template < typename POINT >
concept primitive_point = requires(POINT point)
{
   point.x;
   point.y;
};


template < typename POINT >
concept primitive_XY = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx;
   size.cy;
};


template < typename SIZE >
concept primitive_Dim = requires(SIZE size)
{
   size.Width;
   size.Height;
};


template < typename RECTANGLE >
concept primitive_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template < typename RECTANGLE >
concept primitive_XYDim = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


template < typename RECTANGLE >
concept primitive_xydim = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};


using string = string_base < ansichar >;
using wstring = string_base < widechar >;


typedef string_array_base < string, string, e_type_string_array > string_array;

template < typename TYPE_CHAR >
class string_natural_pointer;

using natural_ansistring = string_natural_pointer < ansichar >;
using natural_wd16string = string_natural_pointer < wd16char >;
using natural_wd32string = string_natural_pointer < wd32char >;
using natural_widestring = string_natural_pointer < widechar >;

typedef natural_ansistring natural_string;
typedef natural_widestring natural_wstring;





template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
struct if_else {};

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < true, TRUE_TYPE, ELSE_TYPE > { using type = TRUE_TYPE; };

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < false, TRUE_TYPE, ELSE_TYPE > { using type = ELSE_TYPE; };










template < typename FROM, typename TO_POINTER >
concept raw_pointer_castable =
::std::is_convertible < FROM, TO_POINTER * >::value ||
::std::is_convertible < FROM, const TO_POINTER * >::value;


template < typename T >
concept primitive_character =
std::is_same < T, ::ansichar >::value ||
std::is_same < T, ::wd16char >::value ||
std::is_same < T, ::wd32char >::value;


template < typename T >
concept const_c_string =
std::is_convertible < T, const ::ansichar * >::value ||
std::is_convertible < T, const ::wd16char * >::value ||
std::is_convertible < T, const ::wd32char * >::value;


template < typename T >
concept non_const_c_string =
std::is_convertible < T, ::ansichar * >::value ||
std::is_convertible < T, ::wd16char * >::value ||
std::is_convertible < T, ::wd32char * >::value;

template < typename T >
concept c_string =
const_c_string < T > ||
non_const_c_string < T >;

template < typename T >
struct base_const_c_string
{

   using type =
      typename if_else <
      std::is_convertible < T, const ansichar * >::value,
      const ansichar *,
      typename if_else <
      std::is_convertible < T, const wd16char * >::value,
      const wd16char *,
      typename if_else <
      std::is_convertible < T, const wd32char * >::value,
      const wd32char *,
      void *
      >::type
      >::type
      >::type;

};






class e_status;


template < typename T >
concept a_pointer = std::is_pointer < T >::value;

template < typename T >
concept non_pointer = !std::is_pointer < T >::value;

template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral = std::is_integral < T >::value || std::is_enum < T >::value || std::is_same < T, ::e_status >::value;

template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = (std::is_integral < T >::value || std::is_enum < T >::value) && std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned = (std::is_integral < T >::value || std::is_enum < T >::value) && !std::is_signed < T >::value;


template < typename T >
concept primitive_floating = std::is_floating_point < T >::value;

template < typename T >
concept primitive_number = std::is_integral < T >::value || std::is_enum < T >::value || std::is_floating_point < T >::value;







template < bool, typename T1, typename T2 >
struct boolean_type_selection { using type = T1; };

template < typename T1, typename T2 >
struct boolean_type_selection<false, T1, T2> { using type = T2; };


template < typename T1, typename T2 >
struct largest_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) > sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2 >
struct smaller_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) < sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2, typename T3 >
struct largest_type_of_3 {
   using largest_type_of_1_and_2 = typename largest_type < T1, T2 >::type;
   using type = typename ::boolean_type_selection < (sizeof(largest_type_of_1_and_2) > sizeof(T3)), largest_type_of_1_and_2, T3>::type;
};


template < typename TYPE, std::size_t SIZE >
using array_reference = TYPE(&)[SIZE];

namespace allocator
{


   template < typename TYPE >
   class def;

   template < typename TYPE >
   class nodef;

} // namespace allocator


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class array_base;


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class array;

template < typename FUNCTION >
class function;

template < class TYPE, class ARG_TYPE = const TYPE & >
class list;

template < typename ARGUMENT >
class argument_of
{
public:

   using type = typename smaller_type < ARGUMENT, const ARGUMENT & >::type;

};


template < >
class argument_of < ::string >
{
public:

   using type = ::block;

};


template < typename T, typename ARG_T = typename argument_of < T >::type >
class single;


template < class KEY, class ARG_KEY = typename argument_of < KEY >::type, class PAYLOAD = single < KEY, ARG_KEY > >
class set;


template < typename T1, typename T2, typename ARG_T1 = typename argument_of < T1 >::type, typename ARG_T2 = typename argument_of < T2 >::type >
class pair;


template < class KEY, class VALUE, class ARG_KEY = typename argument_of < KEY >::type, class ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE > >
class map;


template<class ENUM>
class flags;


template<class EENUM, EENUM edefault = (EENUM)0>
class base_enum;


template < typename PAYLOAD >
concept primitive_payload = ::std::is_base_of < ::PAYLOAD_TAG, PAYLOAD >::value;

//template < typename PROPERTY >
//concept primitive_property = is_derived_from < PROPERTY, ::PROPERTY_TAG >;

template < typename ATOM >
concept primitive_atom = ::std::is_base_of < ::ATOM_TAG, ATOM >::value;

template < typename STRING >
concept primitive_string = ::std::is_base_of < ::STRING_TAG, STRING >::value;

using item_pointer = ::pointer < ::item >;

using memory_pointer = ::pointer < ::memory >;



template < typename CONTAINER >
concept container_type = requires(CONTAINER container)
{

   {container.this_is_a_container()} -> std::same_as<void>;

};


template < container_type CONTAINERX, container_type CONTAINERY >
inline CONTAINERX operator +(CONTAINERX x, const CONTAINERY & y)
{

   x += y;

   return x;

}


template < typename ARRAY >
concept primitive_array = requires(ARRAY array, ::index i)
{
   array.get_count();
   array.element_at(i);
};

template<primitive_array ARRAY1, primitive_array ARRAY2>
bool operator==(const ARRAY1 &array1, const ARRAY2 &array2)
{

   if (array1.get_size() != array2.get_size())
   {

      return false;

   }

   for (::index i = 0; i < array1.get_size(); i++)
   {

      if (array1.element_at(i) != array2.element_at(i))
      {

         return false;

      }

   }

   return true;

}


template<primitive_array ARRAY1, primitive_array ARRAY2>
bool operator!=(const ARRAY1 &array1, const ARRAY2 &array2)
{

   return !operator==(array1, array2);

}


template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = array < TYPE, ARG_TYPE > >
class comparable_eq_array;


template < class TYPE, class ARG_TYPE = TYPE const &, class ARRAY_TYPE = comparable_eq_array < TYPE, ARG_TYPE > >
class comparable_array;


namespace allocator
{


   template < typename TYPE >
   class raw;


   template < typename TYPE >
   class zero;


} // namespace allocator

template < typename TYPE, typename ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::raw < TYPE >, ::enum_type m_etypeContainer = e_type_element >
class raw_array;


template < typename POINTER, class ARRAY_TYPE = comparable_array < POINTER, POINTER, comparable_eq_array < POINTER, POINTER, raw_array < POINTER, POINTER, ::allocator::zero < POINTER > > > > >
class address_array;



class exception;

using exception_array = ::array < ::exception >;



template < typename T >
concept has_string_getter = requires(T t, ::string & str)
{

   { t.as(str) } -> std::same_as < void >;

};

using element_array = pointer_array < element >;



//#include "acme/primitive/collection/string_map.h"


using regular_expression_pointer = ::pointer<::regular_expression::regular_expression>;


template < class T, typename C >
void std_string_assign(T & t, const C * psz);


template < class T >
void std_string_bassign(T & t, const u8 * psz, strsize nsize);





typedef address_array < const char * > const_char_ptra;

typedef address_array < void * > void_ptra;

//typedef address_array < matter * > simple_object_ptra;


using particle_address_array = address_array < particle * >;






using file_pointer = ::pointer<::file::file>;

using memory_file_pointer = ::pointer<::memory_file>;

using folder_pointer = ::pointer<::folder>;



template < typename T >
class c_number;


using wparam = c_number<iptr>;


template < typename T >
concept an_object = !std::is_pointer < T >::value
                    && !std::is_integral < T >::value
                    && !std::is_enum < T >::value
                    && !std::is_floating_point < T >::value;


template<typename T>
inline ::pointer < T > move_transfer(T * p);


#define __new(...) ::move_transfer( memory_new __VA_ARGS__ )


template < typename SEQUENCE >
class sequencer;


using handler_pointer = ::pointer<handler>;
using manager_pointer = ::pointer<manager>;
using context_pointer = ::pointer<context>;


using topic_pointer = ::pointer<topic>;
using extended_topic_pointer = ::pointer<extended_topic>;

template < typename SEQUENCE >
class sequencer;

template < typename SEQUENCE >
class sequence;


template < typename FUNCTION >
class function;

using procedure = ::function < void() >;


using procedure_list = ::list < ::procedure >;




template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
class unique_number_sort_array;


template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
class numeric_array;


using i8_array = numeric_array < i8 >;
using i16_array = numeric_array < i16 >;
using i32_array = numeric_array < i32 >;
using i64_array = numeric_array < i64 >;

using u8_array = numeric_array < u8 >;
using u16_array = numeric_array < u16 >;
using u32_array = numeric_array < u32 >;
using u64_array = numeric_array < u64 >;

using dword_array = u32_array;
using int_array = i32_array;


using index_array = numeric_array < ::index >;
using count_array = numeric_array < ::count >;


using u32_array = numeric_array < ::u32 >;


using unique_i32_sort_array = unique_number_sort_array < i32 >;
using unique_i64_sort_array = unique_number_sort_array < i64 >;


#ifdef OS64BIT


using iptr_array = i64_array;
using uptr_array = u64_array;

using unique_iptr_sort_array = unique_i64_sort_array;


#else


using iptr_array = i32_array;
using uptr_array = u32_array;

using unique_iptr_sort_array = unique_i32_sort_array;


#endif

using float_array = numeric_array < float  >;
using double_array = numeric_array < double  >;

using strsize_array = iptr_array;

//using strsize_ptr_array = ptr_array < strsize *  >;


using byte_array = u8_array;

using task_pointer = ::pointer < task >;

CLASS_DECL_ACME task_pointer fork(::particle * pparticle, const ::procedure & procedure);



namespace draw2d
{


   using graphics_pointer = ::pointer<graphics>;


} // namespace draw2d



template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline void copy(NUMBER1 * pnumber1, const NUMBER2 * pnumber2)
{

   *pnumber1 = (NUMBER1) *pnumber2;

}


template < primitive_string STRING, primitive_integral INTEGRAL >
inline void copy(STRING * pstring, const INTEGRAL * pnumber)
{

   pstring->format("%lld", (::i64) *pnumber);

}

template < primitive_string STRING, primitive_floating FLOATING >
inline void copy(STRING * pstring, const FLOATING * pnumber)
{

   pstring->format("%f", (::f64)*pnumber);

}


template < primitive_payload PAYLOAD >
inline void copy(string * pstring, const PAYLOAD * ppayload)
{

   *pstring = ppayload->string();

}


template < primitive_payload PAYLOAD, primitive_number NUMBER >
inline void copy(PAYLOAD * ppayload, const NUMBER* pnumber)
{

   *ppayload = *pnumber;

}


template < primitive_payload PAYLOAD, primitive_string STRING >
inline void copy(PAYLOAD * ppayload, const STRING * pstring)
{

   *ppayload = *pstring;

}


template < primitive_payload PAYLOAD1, primitive_payload PAYLOAD2 >
inline void copy(PAYLOAD1 * ppayload1, const PAYLOAD2 * ppayload2)
{

   *ppayload1 = *ppayload2;

}








template < a_pointer POINTER >
inline bool is_null(POINTER p)
{

   return ((size_t)p <= 65536);

}


template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }

inline bool is_empty(const ansichar * p) { return is_string_empty(p); }
inline bool is_empty(const wd16char * p) { return is_string_empty(p); }
inline bool is_empty(const wd32char * p) { return is_string_empty(p); }


inline bool has_char(const ansichar * p) { return !is_empty(p); }
inline bool has_char(const wd16char * p) { return !is_empty(p); }
inline bool has_char(const wd32char * p) { return !is_empty(p); }


template < a_pointer POINTER >
inline bool is_set(POINTER p)
{

   return !is_null(p);

}


template<typename TYPE>
inline bool is_ref_set(const TYPE & t)
{

   return is_set(&t);

}


template<typename TYPE>
inline bool is_ok(const TYPE * p)
{

   return ::is_set(p) && p->is_ok();

}


template<typename TYPE>
inline bool is_ok(const ::pointer<TYPE> & p)
{

   return ::is_ok(p.m_p);

}


template<typename TYPE>
inline bool nok(TYPE & t)
{

   return !::is_ok(t);

}






template < typename TYPE, std::size_t SIZE >
inline std::size_t item_count(array_reference < TYPE, SIZE > &) { return SIZE; }


template < typename T >
inline byte byte_clip(const T & t) { return ((byte)(((t) < (byte)0) ? (byte)0 : (((t) > (byte)255) ? (byte)255 : (byte)t))); }


template < typename A, typename B >
void __swap(A & a, B & b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}



typedef pointer_array < ::particle > particle_array;


template < primitive_XYDim XYDim, typename X, typename Y, typename W, typename H >
inline XYDim & set_dim(XYDim & rectTarget, X x, Y y, W w, H h)
{

   rectTarget.X = (decltype(rectTarget.X))x;
   rectTarget.Y = (decltype(rectTarget.Y))y;
   rectTarget.Width = (decltype(rectTarget.Width))w;
   rectTarget.Height = (decltype(rectTarget.Height))h;

   return rectTarget;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
void copy(RECT_TYPE1 * prect1, const RECT_TYPE2 * prect2)
{

   prect1->eft = (decltype(RECT_TYPE1::left))prect2->left;
   prect1->op = (decltype(RECT_TYPE1::top))prect2->top;
   prect1->ight = (decltype(RECT_TYPE1::right))prect2->right;
   prect1->ottom = (decltype(RECT_TYPE1::bottom))prect2->bottom;

}


template < primitive_rectangle RECTANGLE, primitive_XYDim XYDim >
void copy(RECTANGLE * prectangle, const XYDim * pxydim)
{

   prectangle->eft = (decltype(RECTANGLE::left))pxydim->X;
   prectangle->op = (decltype(RECTANGLE::top))pxydim->Y;
   prectangle->ight = (decltype(RECTANGLE::right))(pxydim->X + pxydim->Width);
   prectangle->ottom = (decltype(RECTANGLE::bottom))(pxydim->Y + pxydim->Height);

}


template < primitive_rectangle RECTANGLE, primitive_xydim XYDIM >
void copy(RECTANGLE * prect1, const XYDIM  * pxydim)
{

   prect1->left = (decltype(RECTANGLE::left))pxydim->x;
   prect1->top = (decltype(RECTANGLE::top))pxydim->y;
   prect1->right = (decltype(RECTANGLE::right))(pxydim->x + pxydim->width);
   prect1->bottom = (decltype(RECTANGLE::bottom))(pxydim->y + pxydim->height);

}


template < primitive_XY POINT1, primitive_point POINT2 >
void copy(POINT1 * ppoint1, const POINT2 * ppoint2)
{

   ppoint1->X = (decltype(POINT1::X))ppoint2->x;
   ppoint1->Y = (decltype(POINT1::Y))ppoint2->y;

}


template < primitive_point POINT1, primitive_XY POINT2 >
void copy(POINT1 * ppoint1, const POINT2 * ppoint2)
{

   ppoint1->x = (decltype(POINT1::x))ppoint2->X;
   ppoint1->y = (decltype(POINT1::y))ppoint2->Y;

}


template < primitive_XYDim XYDim, primitive_rectangle RECTANGLE >
void copy(XYDim * pxydim, const RECTANGLE * prectangle)
{

   pxydim->X = (decltype(XYDim::X))prectangle->left;
   pxydim->Y = (decltype(XYDim::Y))prectangle->top;
   pxydim->Width = (decltype(XYDim::Width))(prectangle->right - prectangle->left);
   pxydim->Height = (decltype(XYDim::Height))(prectangle->bottom - prectangle->top);

}


template < primitive_xydim XYDIM, primitive_rectangle RECTANGLE >
void copy(XYDIM * pxydim, const RECTANGLE * prectangle)
{

   pxydim->x = (decltype(XYDIM::X))prectangle->left;
   pxydim->y = (decltype(XYDIM::Y))prectangle->top;
   pxydim->width = (decltype(XYDIM::Width))(prectangle->right - prectangle->left);
   pxydim->height = (decltype(XYDIM::Height))(prectangle->bottom - prectangle->top);

}


template < primitive_XYDim XYDim1, primitive_XYDim XYDim2 >
void copy(XYDim1 * pxydim1, const XYDim2 * pxydim2)
{

   pxydim1->X = (decltype(XYDim1::X))pxydim2->X;
   pxydim1->Y = (decltype(XYDim1::Y))pxydim2->Y;
   pxydim1->Width = (decltype(XYDim1::Width))pxydim2->Width;
   pxydim1->Height = (decltype(XYDim1::Height))pxydim2->Height;

}


template < primitive_point POINT1, primitive_point POINT2 >
void copy(POINT1 * ppoint1, const POINT2  * ppoint2)
{

   ppoint1->x = (decltype(POINT1::x))ppoint2->x;
   ppoint1->y = (decltype(POINT1::y))ppoint2->y;

}


template < primitive_point POINT, primitive_size SIZE >
void copy(POINT * ppoint, const SIZE  * psize)
{

   ppoint->x = (decltype(POINT::x))psize->cx;
   ppoint->y = (decltype(POINT::y))psize->cy;

}


template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
void copy(SIZE_TYPE1 * psize1, const SIZE_TYPE2 * psize2)
{

   psize1->cx = (decltype(SIZE_TYPE1::cx))psize2->cx;
   psize1->cy = (decltype(SIZE_TYPE1::cy))psize2->cy;

}


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto width(RECTANGLE_TYPE & rectangle) { return rectangle.right - rectangle.left; }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto height(RECTANGLE_TYPE & rectangle) { return rectangle.bottom - rectangle.top; }


template < typename W, typename H >
constexpr H area(W w, H h) { return (w <= (W)0 || h <= (H)0) ? 0 : (H)(w * h); }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto area(RECTANGLE_TYPE & rectangle) { return area(width(rectangle), height(rectangle)); }


template < primitive_rectangle RECTANGLE_TYPE >
bool is_null(const RECTANGLE_TYPE & rectangle)
{

   return rectangle.left == (decltype(RECTANGLE_TYPE::left))0
          && rectangle.top == (decltype(RECTANGLE_TYPE::top))0
          && rectangle.right == (decltype(RECTANGLE_TYPE::right))0
          && rectangle.bottom == (decltype(RECTANGLE_TYPE::bottom))0;

}


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_empty(RECTANGLE_TYPE & rectangle) { return ::is_null(rectangle) || rectangle.right <= rectangle.left || rectangle.bottom <= rectangle.top; }


template < primitive_rectangle RECTANGLE_TYPE >
constexpr auto is_set(RECTANGLE_TYPE & rectangle) { return !::is_empty(rectangle); }


template < primitive_size SIZE_TYPE >
bool is_null(const SIZE_TYPE & size)
{

   return size.cx == (decltype(SIZE_TYPE::cx))0
          && size.cy == (decltype(SIZE_TYPE::cy))0;

}


template < primitive_point POINT_TYPE >
bool is_null(const POINT_TYPE & point)
{

   return point.x == (decltype(POINT_TYPE::cx))0 && point.y == (decltype(POINT_TYPE::cy))0;

}





template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_offset(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + x);

   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_offset(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + y);

   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + y);

   return rectangle;

}



template < primitive_rectangle RECTANGLE_TYPE, typename X >
inline RECTANGLE_TYPE & x_subtract(RECTANGLE_TYPE & rectangle, X x)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - x);

   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - x);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, typename Y >
inline RECTANGLE_TYPE & y_subtract(RECTANGLE_TYPE & rectangle, Y y)
{

   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - y);

   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - y);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_offset(rectangle, x);

   y_offset(rectangle, y);

   return rectangle;

}


template < typename RECTANGLE_TYPE, typename X, typename Y >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   x_subtract(rectangle, x);

   y_subtract(rectangle, y);

   return rectangle;

}


template < typename RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & offset(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return offset(rectangle, point.x, point.y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return subtract(rectangle, point.x, point.y);

}


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
inline RECTANGLE1 & subtract(RECTANGLE1 & rectangle, const RECTANGLE2 & rectangle2)
{

   rectangle.left = (decltype(rectangle.left))(rectangle.left - rectangle2.left);
   rectangle.top = (decltype(rectangle.top))(rectangle.top - rectangle2.top);
   rectangle.right = (decltype(rectangle.right))(rectangle.right - rectangle2.right);
   rectangle.bottom = (decltype(rectangle.bottom))(rectangle.bottom - rectangle2.bottom);

   return rectangle;

}


//template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT >
//inline RECTANGLE_TYPE & subtract(RECTANGLE_TYPE & rectangle, const POINT & point) { return subtract(rectangle, point); }


template < primitive_point POINT, typename X, typename Y >
inline POINT & offset(POINT & point, X x, Y y)
{

   point.x = (decltype(POINT::x))(point.x + x);
   point.y = (decltype(POINT::y))(point.y + y);

   return point;

}


template < primitive_point POINT, primitive_point POINT2 >
inline POINT & offset(POINT & point, const POINT2 & point2)
{

   return offset(point, point2.x, point2.y);

}


template < primitive_point POINT, primitive_point POINT2 >
inline POINT & add(POINT & point, const POINT2 & point2) { return offset(point, point2); }


template < primitive_point POINT_TYPE, typename X, typename Y >
inline POINT_TYPE & subtract(POINT_TYPE & point, X x, Y y)
{

   point.x = (decltype(POINT_TYPE::x))(point.x - x);
   point.y = (decltype(POINT_TYPE::y))(point.y - y);

   return point;

}


template < primitive_point POINT_TYPE, primitive_point POINT_TYPE2 >
inline POINT_TYPE & subtract(POINT_TYPE & point, const POINT_TYPE2 & point2)
{

   return subtract(point, point2.x, point2.y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_point POINT_TYPE >
inline RECTANGLE_TYPE & add(RECTANGLE_TYPE & rectangle, const POINT_TYPE & point)
{

   return offset(rectangle, point);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   bool bIntersect = right > left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.left = left;

      rectangle.right = right;

   }

   return bIntersect;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   return right > left;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   bool bIntersect = bottom > top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.top = top;

      rectangle.bottom = bottom;

   }

   return bIntersect;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   return bottom > top;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_intersect(rectangle, rect1, rect2) && y_intersect(rectangle, rect1, rect2))
   {

      return true;

   }

   if (::is_set(rectangle))
   {

      null(rectangle);

   }

   return false;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool intersects(const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   return x_intersects(rect1, rect2) && y_intersects(rect1, rect2);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto left = maximum(rect1.left, rect2.left);

   auto right = minimum(rect1.right, rect2.right);

   bool bIntersect = right >= left;

   if (!bIntersect)
   {

      left = 0; right = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.left = left;

      rectangle.right = right;

   }

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   auto top = maximum(rect1.top, rect2.top);

   auto bottom = minimum(rect1.bottom, rect2.bottom);

   bool bIntersect = bottom >= top;

   if (!bIntersect)
   {

      top = 0; bottom = 0;

   }

   if (::is_set(rectangle))
   {

      rectangle.top = top;

      rectangle.bottom = bottom;

   }

   return bIntersect;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_null_intersect(rectangle, rect1, rect2) && y_null_intersect(rectangle, rect1, rect2))
   {

      return true;

   }

   if (::is_set(rectangle))
   {

      null(rectangle);

   }

   return false;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool x_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.left = maximum(rect1.left, rect2.left);

   rectangle.right = minimum(rect1.right, rect2.right);

   return rectangle.right > rectangle.left || (rectangle.right == rectangle.left && rect1.left == rect2.left);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool y_top_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   rectangle.top = maximum(rect1.top, rect2.top);

   rectangle.bottom = minimum(rect1.bottom, rect2.bottom);

   return rectangle.top < rectangle.bottom || (rectangle.top == rectangle.bottom && rect1.top == rect2.top);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
bool top_left_null_intersect(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (x_left_null_intersect(rectangle, rect1, rect2) && y_top_null_intersect(rectangle, rect1, rect2))
   {

      return true;

   }
   else
   {

      null(rectangle);

      return false;

   }

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECTANGLE_TYPE & unite(RECTANGLE_TYPE & rectangle, const RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (is_empty(rect1))
   {

      if (is_empty(rect2))
      {

         null(rectangle);

      }
      else
      {

         copy(rectangle, rect2);

      }

   }
   else if (is_empty(rect1))
   {

      copy(rectangle, rect1);

   }
   else
   {

      rectangle.left = (decltype(RECTANGLE_TYPE::left))minimum(rect1.left, rect2.left);
      rectangle.top = (decltype(RECTANGLE_TYPE::top))minimum(rect1.top, rect2.top);
      rectangle.right = (decltype(RECTANGLE_TYPE::right))maximum(rect1.right, rect2.right);
      rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))maximum(rect1.bottom, rect2.bottom);

   }

   return rectangle;

}


template < primitive_rectangle RECT_TYPE1, primitive_rectangle RECT_TYPE2 >
RECT_TYPE1 & unite(RECT_TYPE1 & rect1, const RECT_TYPE2 & rect2)
{

   if (is_empty(rect1))
   {

      if (is_empty(rect2))
      {

         null(rect1);

      }
      else
      {

         copy(rect1, rect2);

      }

   }
   else if (is_set(rect2))
   {

      rect1.left = (decltype(RECT_TYPE1::left))minimum(rect1.left, rect2.left);
      rect1.top = (decltype(RECT_TYPE1::top))minimum(rect1.top, rect2.top);
      rect1.right = (decltype(RECT_TYPE1::right))maximum(rect1.right, rect2.right);
      rect1.bottom = (decltype(RECT_TYPE1::bottom))maximum(rect1.bottom, rect2.bottom);

   }

   return rect1;

}


template < typename X, typename Y >
auto get_dimension(enum_orientation eorientation, X x, Y y);


template < typename X, typename Y >
auto get_normal_dimension(enum_orientation eorientation, X x, Y y);


template < primitive_rectangle RECTANGLE1, primitive_rectangle RECTANGLE2 >
bool is_equal(const RECTANGLE1 & rectangle1, const RECTANGLE2 & rectangle2)
{

   return rectangle1.left == rectangle2.left && rectangle1.top == rectangle2.top
          && rectangle1.right == rectangle2.right && rectangle1.bottom == rectangle2.bottom;

}


template < primitive_point POINT1, primitive_point POINT2 >
bool is_equal(const POINT1 & point1, const POINT2 & point2)
{

   return point1.x == point2.x && point1.y == point2.y;

}


template < primitive_size SIZE_TYPE1, primitive_size SIZE_TYPE2 >
bool is_equal(const SIZE_TYPE1 & size1, const SIZE_TYPE2 & size2)
{

   return size1.cx == size2.cx && size1.cy == size2.cy;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
RECTANGLE_TYPE & assign(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))l;
   rectangle.top = (decltype(RECTANGLE_TYPE::top))t;
   rectangle.right = (decltype(RECTANGLE_TYPE::right))r;
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))b;

   return rectangle;

}


template < primitive_rectangle RECTANGLE, primitive_number L, primitive_number T, primitive_number W, primitive_number H >
RECTANGLE & set_dimension(RECTANGLE & rectangle, L l, T t, W w, H h)
{

   rectangle.left = (decltype(RECTANGLE::left))l;
   rectangle.top = (decltype(RECTANGLE::top))t;
   rectangle.right = (decltype(RECTANGLE::right))(l + w);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(t + h);

   return rectangle;

}

//template < primitive_rectangle RECTANGLE,  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE &r, L l, T t, W w, H h) { return set_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_I64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F32 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }
//template <  typename L, typename T, typename W, typename H >
//inline auto _001SetRectDim(RECTANGLE_F64 * p, L l, T t, W w, H h) { return set_rect_dim(p, l, t, w, h); }


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & set_bottom_right(RECTANGLE & rectangle, const SIZE & size)
{

   rectangle.right = (decltype(RECTANGLE::right))(rectangle.left + size.cx);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(rectangle.top + size.cy);

   return rectangle;

}


template < primitive_rectangle RECTANGLE, primitive_point POINT, primitive_size SIZE >
RECTANGLE & assign(RECTANGLE & rectangle, const POINT & point, const SIZE & size)
{

   rectangle.left = (decltype(RECTANGLE::left))point.x;
   rectangle.top = (decltype(RECTANGLE::top))point.y;
   rectangle.right = (decltype(RECTANGLE::right))(point.x + size.cx);
   rectangle.bottom = (decltype(RECTANGLE::bottom))(point.y + size.cy);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE >
RECTANGLE_TYPE & null(RECTANGLE_TYPE & rectangle)
{

   return ::assign(rectangle, 0, 0, 0, 0);

}



template < primitive_rectangle RECTANGLE, primitive_number X >
inline bool contains_x(const RECTANGLE & rectangle, X x)
{

   return x >= rectangle.left && x <= rectangle.right;

}


template < primitive_rectangle RECTANGLE, primitive_number Y >
inline bool contains_y(const RECTANGLE & rectangle, Y y)
{

   return y >= rectangle.top && y <= rectangle.bottom;

}


template < typename RECTANGLE, primitive_number X, primitive_number Y >
inline bool contains(const RECTANGLE & rectangle, X x, Y y)
{

   return contains_x(rectangle, x) && contains_y(rectangle, y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left - l);
   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top - t);
   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right + r);
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom + b);

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return inflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & multiply_inline(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   rectangle.left *= rect2.left;
   rectangle.top *= rect2.top;
   rectangle.right *= rect2.right;
   rectangle.bottom *= rect2.bottom;

   return rectangle;

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number L, primitive_number T, primitive_number R, primitive_number B >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, L l, T t, R r, B b)
{

   rectangle.left = (decltype(RECTANGLE_TYPE::left))(rectangle.left + l);
   rectangle.top = (decltype(RECTANGLE_TYPE::top))(rectangle.top + t);
   rectangle.right = (decltype(RECTANGLE_TYPE::right))(rectangle.right - r);
   rectangle.bottom = (decltype(RECTANGLE_TYPE::bottom))(rectangle.bottom - b);

   return rectangle;

}


template < typename RECTANGLE_TYPE, primitive_rectangle RECT_TYPE2 >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, const RECT_TYPE2 & rect2)
{

   return deflate(rectangle, rect2.left, rect2.top, rect2.right, rect2.bottom);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return inflate(rectangle, x, y, x, y);

}

template < primitive_rectangle RECTANGLE_TYPE, primitive_number X, primitive_number Y >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, X x, Y y)
{

   return deflate(rectangle, x, y, x, y);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & inflate(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return inflate(rectangle, u, u);

}


template < primitive_rectangle RECTANGLE_TYPE, primitive_number UNIT >
inline RECTANGLE_TYPE & deflate(RECTANGLE_TYPE & rectangle, UNIT u)
{

   return deflate(rectangle, u, u);

}


template < primitive_rectangle RECTANGLE_TYPE >
inline RECTANGLE_TYPE & swap_left_right(RECTANGLE_TYPE & rectangle) { __swap(rectangle.left, rectangle.right); return rectangle; }



template < primitive_point POINT1, primitive_point POINT2 >
inline bool polygon_contains(const POINT1 * ppPolygon, i32 iCount, const POINT2 & point)
{

   int i, j = iCount - 1;

   auto x = point.x;

   auto y = point.y;

   bool oddNodes = false;

   for (i = 0; i < iCount; i++)
   {

      if (((ppPolygon[i].y < y && ppPolygon[j].y >= y) || (ppPolygon[j].y < y && ppPolygon[i].y >= y)) && (ppPolygon[i].x <= x || ppPolygon[j].x <= x))
      {

         oddNodes ^= (ppPolygon[i].x + (y - ppPolygon[i].y) / (ppPolygon[j].y - ppPolygon[i].y) * (ppPolygon[j].x - ppPolygon[i].x) < x);

      }

      j = i;

   }

   return oddNodes;

}




template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator -= (POINT & point, const POINT2 & pointOffset) { ::subtract(point, pointOffset); return point; }

template < primitive_point POINT, primitive_point POINT2 >
inline POINT & operator += (POINT & point, const POINT2 & pointOffset) { ::add(point, pointOffset); return point; }



template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator -= (RECTANGLE & rectangle, const POINT & point) { ::subtract(rectangle, point); return rectangle; }

template < primitive_rectangle RECTANGLE, primitive_point POINT >
inline RECTANGLE & operator += (RECTANGLE & rectangle, const POINT & point) { ::add(rectangle, point); return rectangle; }




