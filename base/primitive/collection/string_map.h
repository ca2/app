#pragma once


template < class VALUE, class ARG_VALUE = const VALUE & >
using string_map = map < string,const string &, VALUE, ARG_VALUE > ;

using string_to_intptr = string_map < iptr,iptr > ;

using string_to_int =  string_map < int, int > ;

using string_to_ptr =  string_map < void *,void * > ;


#define strmap(T) string_map < T >


