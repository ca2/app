#pragma once


#include "acme/prototype/collection/map.h"


template < class PAYLOAD >
using i32_map = map_base < ::i32, PAYLOAD >;

template < class PAYLOAD >
using i64_map = map_base < ::i64, PAYLOAD >;

template < class PAYLOAD >
using iptr_map = map_base < iptr, PAYLOAD >;

template < class PAYLOAD >
using index_map_base = map_base < ::collection::index, PAYLOAD >;

using int_to_int = i32_map < ::i32 >;

using i64_to_long_long = i64_map < ::i64 >;

using int_to_string =  i32_map < string > ;

using i64_to_string = i64_map < string >;

using iptr_to_iptr = iptr_map < iptr >;

using iptr_to_string =  iptr_map < string > ;

using index_to_index = index_map_base < ::collection::index >;

using index_to_string = index_map_base < string >;



