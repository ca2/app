// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once


template<class T>
class ___pointer;


template<class T>
class pointer_array;


//#define __composite(TYPE) ::reference < TYPE >


#define __pointer(TYPE) ::___pointer < TYPE >
#define __pointer_array(TYPE) ::pointer_array < TYPE >
#define __address_array(TYPE) ::comparable_array < TYPE * >


#define __throw(...) throw_exception(__VA_ARGS__)



template < class root_derived >
inline i64 increment_reference_count(root_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < class root_derived >
inline i64 release(root_derived *& pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


CLASS_DECL_ACME void output_debug_string(const ansichar * psz);
CLASS_DECL_ACME void output_debug_string(const wd16char * psz);
CLASS_DECL_ACME void output_debug_string(const wd32char * psz);



