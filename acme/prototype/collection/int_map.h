#pragma once


#include "acme/prototype/collection/map.h"


template < class PAYLOAD >
using int_map = map_base < int, PAYLOAD >;

template < class PAYLOAD >
using i64_map = map_base < long long, PAYLOAD >;

template < class PAYLOAD >
using iptr_map = map_base < iptr, PAYLOAD >;

template < class PAYLOAD >
using index_map_base = map_base < ::collection::index, PAYLOAD >;

using int_to_int = int_map < int >;

using i64_to_long_long = i64_map < long long >;

using int_to_string =  int_map < string > ;

using i64_to_string = i64_map < string >;

using iptr_to_iptr = iptr_map < iptr >;

using iptr_to_string =  iptr_map < string > ;

using index_to_index = index_map_base < ::collection::index >;

using index_to_string = index_map_base < string >;



