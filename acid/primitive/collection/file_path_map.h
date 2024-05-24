#pragma once


template < class PAYLOAD, typename ARG_VALUE = argument_of < PAYLOAD > >
using file_path_map = map < ::file::path, PAYLOAD, argument_of < ::file::path >, ARG_VALUE > ;

using file_path_to_intptr = file_path_map < iptr, iptr > ;

using file_path_to_int = file_path_map < int > ;

using file_path_to_ptr = file_path_map < void * > ;



