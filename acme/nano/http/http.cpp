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
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/prototype/factory.h"


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


      }


      //void http::sync(::nano::http::get* defer_get)
      //{

      //   auto phappening = øcreate_new < ::manual_reset_happening >();

      //   defer_get->m_functionOnFinished = [phappening](auto)
      //      {

      //         phappening->set_happening();

      //      };

      //   if (!defer_get->m_transferprogressfunction)
      //   {

      //      defer_get->m_transferprogressfunction = defer_get->m_setIn["transfer_progress_function"];

      //   }

      //   async(defer_get);

      //   if (!phappening->wait(defer_get->m_timeSyncTimeout))
      //   {

      //      throw ::exception(error_timeout);

      //   }

      //}


      //void http::async(::nano::http::get* defer_get)
      //{

      //   ::pointer < ::nano::http::get > pgetHold(defer_get);

      //   if (!defer_get->m_transferprogressfunction)
      //   {

      //      defer_get->m_transferprogressfunction = defer_get->m_setIn["transfer_progress_function"];

      //   }

      //   fork([this, pgetHold]()
      //      {

      //         sync(pgetHold);

      //         pgetHold->set_finished();

      //      });

      //}


      ::url::url http::get_effective_url(const ::url::url & url)
      {

         ::string strUrl(url.as_string());

         int iRedirectLimit = 30;

         for(int iRedirect = 0; iRedirect < iRedirectLimit; iRedirect++)
         {

            auto defer_get = øcreate_new < ::nano::http::get>();

            defer_get->m_url = strUrl;

            defer_get->payload("only_headers") = true;
            
            defer_get->m_timeSyncTimeout = 5_min;

            defer_get->send();

            auto strLocation = defer_get->payload("location").as_string();

            if (strLocation.is_empty())
            {

               return strUrl;

            }
            else
            {

               strLocation.trim();

               strUrl = strLocation;

            }

         }

         throw ::exception(error_failed, "redirection limiti reached");

         return {};

      }


      bool http::check_url_ok(const ::url::url& url)
      {

         ::string strUrl(get_effective_url(url).as_string());

         auto defer_get = øcreate_new < ::nano::http::get>();

         defer_get->m_url = strUrl;

         defer_get->payload("only_headers") = true;

         defer_get->m_timeSyncTimeout = 5_min;

         defer_get->send();

         auto iHttpStatusCode = defer_get->payload("http_status_code").as_int();

         return iHttpStatusCode == 200;

      }



      ::string http::get(const ::url::url & url)
      {

         auto urlEffetive = get_effective_url(url);

         auto defer_get = øcreate_new < ::nano::http::get>();

         defer_get->m_url = urlEffetive;

         defer_get->m_timeSyncTimeout = 5_min;

         defer_get->send();

         auto iHttpStatusCode = defer_get->payload("http_status_code").as_int();

         ::string strOutput;

         strOutput = defer_get->get_memory_response()->as_utf8();

         return strOutput;

      }


      void http::download(const ::file::path & path, const ::url::url & url)
      {

         auto urlEffective = get_effective_url(url);

         auto defer_get = øcreate_new < ::nano::http::get>();

         defer_get->m_url = urlEffective;

         defer_get->m_timeSyncTimeout = 2_hour;

         defer_get->send();

         auto iHttpStatusCode = defer_get->payload("http_status_code").as_int();

         file_system()->put_block(path, *defer_get->get_memory_response());

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
