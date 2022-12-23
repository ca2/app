#pragma once


#include "acme/primitive/collection/map.h"
//// #include "acme/primitive/string/string.h"


template < class VALUE, class ARG_VALUE = typename argument_of < VALUE >::type, typename PAIR = pair < string, VALUE, typename argument_of < string >::type, ARG_VALUE > >
using string_map = map < string, VALUE, typename argument_of < string >::type, ARG_VALUE, PAIR >;

using string_to_intptr = string_map < iptr, iptr > ;

using string_to_int =  string_map < int, int > ;

using string_to_ptr =  string_map < void * > ;

using int_ptr_to_string = map < iptr, iptr, string, const string & >;

using int_ptr_to_int_ptr_to_string = map < iptr, iptr, int_ptr_to_string, const int_ptr_to_string & >;

using index_string = map < index, string >;

using index_to_index_to_string = map < index, index_string >;

using base_string_to_string = string_map < string,const string & > ;

using string_to_string  =  base_string_to_string;

using string_table = string_map < ::pointer < string_to_string > >;


#define strmap(T) string_map < T >



