#pragma once


template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using i32_map = map < i32, VALUE, typename argument_of < i32 >::type, ARG_VALUE >;

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using i64_map = map < i64, VALUE, typename argument_of < i64 >::type, ARG_VALUE >;

template < class VALUE,typename ARG_VALUE = typename argument_of < VALUE >::type >
using iptr_map = map < iptr, VALUE, typename argument_of < iptr >::type, ARG_VALUE >;

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using index_map = map < index, VALUE, typename argument_of < index >::type, ARG_VALUE >;

using int_to_int = i32_map < int >;

using i64_to_i64 = i64_map < i64 >;

using int_to_string =  i32_map < string > ;

using i64_to_string = i64_map < string >;

using iptr_to_iptr = iptr_map < iptr >;

using iptr_to_string =  iptr_map < string > ;

using index_to_index = index_map < index >;

using index_to_string = index_map < string >;



