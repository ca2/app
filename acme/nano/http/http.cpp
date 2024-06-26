//
//  nano_http.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "http.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/primitive/primitive/factory.h"


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


      void http::sync(::nano::http::get* pget)
      {

         auto pevent = __create_new < ::manual_reset_event >();

         pget->m_functionOnFinished = [pevent](auto)
            {

               pevent->SetEvent();

            };

         if (!pget->m_transferprogressfunction)
         {

            pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];

         }

         async(pget);

         if (!pevent->wait(pget->m_timeSyncTimeout))
         {

            throw ::exception(error_timeout);

         }

      }


      void http::async(::nano::http::get* pget)
      {

         ::pointer < ::nano::http::get > pgetHold(pget);

         if (!pget->m_transferprogressfunction)
         {

            pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];

         }

         fork([this, pgetHold]()
            {

               sync(pgetHold);

               pgetHold->set_finished();

            });

      }


      ::string http::get_effective_url(const ::scoped_string& scopedstr)
      {

         ::string strUrl(scopedstr);

         int iRedirectLimit = 30;

         for(int iRedirect = 0; iRedirect < iRedirectLimit; iRedirect++)
         {

            auto pget = __create_new < ::nano::http::get>();

            pget->m_strUrl = strUrl;

            pget->m_setIn["only_headers"] = true;
            
            pget->m_timeSyncTimeout = 5_min;

            sync(pget);

            auto strLocation = pget->m_setOut["location"];

            if (strLocation.is_empty())
            {

               return strUrl;

            }
            else
            {

               strUrl = strLocation;

            }

         }

         throw ::exception(error_failed, "redirection limiti reached");

         return {};

      }


      bool http::check_url_ok(const ::scoped_string& scopedstrUrl)
      {

         ::string strUrl(get_effective_url(scopedstrUrl));

         auto pget = __create_new < ::nano::http::get>();

         pget->m_strUrl = strUrl;

         pget->m_setIn["only_headers"] = true;

         pget->m_timeSyncTimeout = 5_min;

         sync(pget);

         auto iHttpStatusCode = pget->m_setOut["http_status_code"].as_i32();

         return iHttpStatusCode == 200;

      }



      ::string http::get(const ::scoped_string & scopedstrUrl)
      {

         ::string strUrl(get_effective_url(scopedstrUrl));

         auto pget = __create_new < ::nano::http::get>();

         pget->m_strUrl = strUrl;

         pget->m_timeSyncTimeout = 5_min;

         sync(pget);

         auto iHttpStatusCode = pget->m_setOut["http_status_code"].as_i32();

         ::string strOutput;

         strOutput = pget->m_memory.as_utf8();

         return strOutput;

      }


      void http::download(const ::file::path & path, const ::scoped_string & scopedstrUrl)
      {

         ::string strUrl(get_effective_url(scopedstrUrl));

         auto pget = __create_new < ::nano::http::get>();

         pget->m_strUrl = strUrl;

         pget->m_timeSyncTimeout = 2_hour;

         sync(pget);

         auto iHttpStatusCode = pget->m_setOut["http_status_code"].as_i32();

         acmefile()->put_block(path, pget->m_memory);

      }


   } // namespace http

} // namespace nano

//
// void operating_system_initialize_nano_http(::factory::factory* pfactory);
//
//
// bool g_bNanoInitializeHttp = false;
//
//
// CLASS_DECL_ACME void initialize_nano_http(::factory::factory* pfactory)
// {
//
//    if (g_bNanoInitializeHttp)
//    {
//
//       return;
//
//    }
//
//    operating_system_initialize_nano_http(pfactory);
//
//    g_bNanoInitializeHttp = true;
//
// }
//
