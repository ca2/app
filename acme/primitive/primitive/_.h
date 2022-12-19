#pragma once


#include "acme/user/user/_constant_key.h"


#if OBJECT_REFERENCE_COUNT_DEBUG


template < typename TYPE, typename T >
void assign(::pointer<TYPE>& ptr, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < typename TYPE >
void release(::pointer<TYPE>& ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < typename TYPE >
void release(TYPE *& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


#endif


namespace acme
{

   CLASS_DECL_ACME void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace acme



// Created by camilo on 2021-04-07 15:00 BRT <3TBS_!!
#pragma once


//#include "url_c.h"
//#include "url_domain.h"
//#include "url_department.h"


#define NETWORK_PAYLOAD_DEFAULT_EXTENSION ".\x6ason"







// Created by camilo on 2022-11-07 22:00 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME bool is_url(const scoped_string & strCandidate, const char** ppszRequest = nullptr);

CLASS_DECL_ACME bool is_like_url_protocol(const scoped_string & str);


namespace url
{


   CLASS_DECL_ACME string encode(const ::block& block);


   CLASS_DECL_ACME string decode(const ::block& block);


   CLASS_DECL_ACME bool query_get_param(string& strParam, const scoped_string & strKey, const scoped_string & strUrl);


} // namespace url


#if defined(__APPLE__)

CLASS_DECL_ACME void openURL(const string& url_str);

#endif




