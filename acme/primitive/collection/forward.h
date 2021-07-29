#pragma once


template < typename TYPE, enum_type t_etypePayload = e_type_element >
class unique_number_sort_array;


template < typename TYPE, enum_type t_etypePayload = e_type_element > 
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





