//
// macos/nano/_nano.cpp by camilo on 26/07/2023 22:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_nano_http.h"
#include "http.h"



void operating_system_initialize_nano_http(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::universal_windows::nano::http::http, ::nano::http::http>();

}



