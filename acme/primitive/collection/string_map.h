#pragma once


template < class VALUE, class ARG_VALUE = typename argument_of < VALUE >::type, typename PAIR = pair < string, VALUE, typename argument_of < string >::type, ARG_VALUE > >
using string_map = map < string, VALUE, typename argument_of < string >::type, ARG_VALUE, PAIR >;


using string_to_intptr = string_map < iptr, iptr > ;


using string_to_int =  string_map < int, int > ;


using string_to_ptr =  string_map < void * > ;


#define strmap(T) string_map < T >


