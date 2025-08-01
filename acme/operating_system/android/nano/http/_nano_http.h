//
// From macos/nano/_nano.h by camilo on 26/07/2022 22:14 <3ThomasBorregaardSorensen!!
//
#pragma once



typedef void NANO_HTTP_RESPONSE(long http_status, const void * data, long size, void * userdata);

using PFN_NANO_HTTP_RESPONSE = NANO_HTTP_RESPONSE *;


void nano_asynchronous_http_memory(const_char_pointer  pszUrl, PFN_NANO_HTTP_RESPONSE pfn, void * userdata);


