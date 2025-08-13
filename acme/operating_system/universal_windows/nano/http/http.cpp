//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_http.h"
#include "acme/_operating_system.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
//#include <winsock2.h>
#include <Winhttp.h>
//      //#include <urlmon.h>
//#include <windows.h>
//#include <iostream>
//#include <fstream>
#pragma comment(lib, "Winhttp.lib")

namespace universal_windows
{


   namespace nano
   {


      namespace http
      {
         
         
         
         http::http()
         {


         }
         http::~http()
         {


         }


         void http::perform(::nano::http::get * defer_get)
         {


            auto hinternet = WinHttpOpen(nullptr, 0, nullptr, nullptr, 0);

         }



      }// namespace http

   } // namespace nano

} // namespace universal_windows






