//
// macos/nano/_nano.cpp by camilo on 26/07/2023 22:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_http.h"
#include "http.h"



void nano_http_wininet_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::windows::nano::http::http, ::nano::http::http>();

}



