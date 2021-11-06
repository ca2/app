#pragma once


template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using file_path_map = map < ::file::path, VALUE, typename argument_of < ::file::path >::type, ARG_VALUE > ;

using file_path_to_intptr = file_path_map < iptr, iptr > ;

using file_path_to_int = file_path_map < int > ;

using file_path_to_ptr = file_path_map < void * > ;



