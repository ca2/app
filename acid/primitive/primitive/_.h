#pragma once


#include "acid/user/user/_constant.h"




namespace acid
{

   CLASS_DECL_ACID void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACID void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACID void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace acid


// Created by camilo on 2021-04-07 15:00 BRT <3TBS_!!


//#include "url_c.h"
//#include "url_domain.h"
//#include "url_department.h"


#define NETWORK_PAYLOAD_DEFAULT_EXTENSION ".\x6ason"


// Created by camilo on 2022-11-07 22:00 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACID bool is_url(const ::scoped_string & scopedstrCandidate, const char** ppszRequest = nullptr);

CLASS_DECL_ACID bool is_like_url_protocol(const ::scoped_string & scopedstr);


namespace url
{


   CLASS_DECL_ACID string encode(const ::scoped_string & scopedstr);


   CLASS_DECL_ACID string decode(const ::scoped_string & scopedstr);


   CLASS_DECL_ACID bool query_get_param(string& strParam, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrUrl);


} // namespace url


#if defined(__APPLE__)

CLASS_DECL_ACID void openURL(const string& url_str);

#endif


#include "unit.h"


class action_context;



