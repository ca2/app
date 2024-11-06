#pragma once


#include "map.h"


template < class PAYLOAD >
using int_map = map < int, PAYLOAD >;

template < class PAYLOAD >
using i64_map = map < huge_integer, PAYLOAD >;

template < class PAYLOAD >
using iptr_map = map < iptr, PAYLOAD >;

template < class PAYLOAD >
using index_map = map < ::collection::index, PAYLOAD >;

using int_to_int = int_map < int >;

using i64_to_huge_integer = i64_map < huge_integer >;

using int_to_string =  int_map < string > ;

using i64_to_string = i64_map < string >;

using iptr_to_iptr = iptr_map < iptr >;

using iptr_to_string =  iptr_map < string > ;

using index_to_index = index_map < ::collection::index >;

using index_to_string = index_map < string >;



