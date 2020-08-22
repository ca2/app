#pragma once


template < class VALUE, class ARG_VALUE = const VALUE & >
using int_map = map < i32,i32, VALUE, ARG_VALUE >;

template < class VALUE, class ARG_VALUE = const VALUE & >
using i64_map = map < i64, i64, VALUE, ARG_VALUE >;


template < class VALUE,class ARG_VALUE = const VALUE & >
using int_ptr_map = map < iptr,iptr, VALUE, ARG_VALUE >;

template < class VALUE, class ARG_VALUE = const VALUE & >
using index_map = map < index, index, VALUE, ARG_VALUE >;

using int_to_int = int_map < int >;
using i64_to_i64 = i64_map < i64 >;

using int_to_string =  int_map < string, const string & > ;
using i64_to_string = i64_map < string, const string & >;

using int_ptr_to_int_ptr= int_ptr_map < iptr,iptr >;

using int_ptr_to_string =  int_ptr_map < string, const string & > ;

using index_to_index = index_map < index, index >;

using index_to_string = index_map < string, const string & >;
