#pragma once


#include "acme/primitive/collection/map.h"


template < class PAYLOAD, typename PAIR = pair < string, PAYLOAD > >
using string_map = map < string, PAYLOAD, PAIR >;

using string_to_intptr = string_map < iptr > ;

using string_to_int =  string_map < int > ;

using string_to_ptr =  string_map < void * > ;

using int_ptr_to_string = map < iptr, string >;

using int_ptr_to_int_ptr_to_string = map < iptr, int_ptr_to_string >;

using index_string = map < index, string >;

using index_to_index_to_string = map < index, index_string >;

using base_string_to_string = string_map < string > ;

using string_to_string  =  base_string_to_string;

using string_table = string_map < ::pointer < string_to_string > >;


#define strmap(T) string_map < T >



