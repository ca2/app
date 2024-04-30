#pragma once


#include "map.h"


template < class PAYLOAD >
using i32_map = map < i32, PAYLOAD >;

template < class PAYLOAD >
using i64_map = map < i64, PAYLOAD >;

template < class PAYLOAD >
using iptr_map = map < iptr, PAYLOAD >;

template < class PAYLOAD >
using index_map = map < ::raw::index, PAYLOAD >;

using int_to_int = i32_map < int >;

using i64_to_i64 = i64_map < i64 >;

using int_to_string =  i32_map < string > ;

using i64_to_string = i64_map < string >;

using iptr_to_iptr = iptr_map < iptr >;

using iptr_to_string =  iptr_map < string > ;

using index_to_index = index_map < ::raw::index >;

using index_to_string = index_map < string >;



