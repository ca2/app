#pragma once


template < class VALUE,class ARG_VALUE = const VALUE & >
using file_path_map =map < ::file::path,const ::file::path &,VALUE,ARG_VALUE > ;

using file_path_to_intptr = string_map < iptr,iptr > ;

using file_path_to_int =  string_map < int,int > ;

using file_path_to_ptr =  string_map < void *,void * > ;

#define filepathmap(T) file_path_map < T >


