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

      
      void http::perform(::nano::http::get * pget)
      {


      }


      //void http::sync(::nano::http::get* pget)
      //{

      //   auto pevent = __create_new < ::manual_reset_happening >();

      //   pget->m_functionOnFinished = [pevent](auto)
      //      {

      //         pevent->set_happening();

      //      };

      //   if (!pget->m_transferprogressfunction)
      //   {

      //      pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];

      //   }

      //   async(pget);

      //   if (!pevent->wait(pget->m_timeSyncTimeout))
      //   {

      //      throw ::exception(error_timeout);

      //   }

      //}


      //void http::async(::nano::http::get* pget)
      //{

      //   ::pointer < ::nano::http::get > pgetHold(pget);

      //   if (!pget->m_transferprogressfunction)
      //   {

      //      pget->m_transferprogressfunction = pget->m_setIn["transfer_progress_function"];

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

            auto pget = __create_new < ::nano::http::get>();

            pget->m_url = strUrl;

            pget->payload("only_headers") = true;
            
            pget->m_timeSyncTimeout = 5_min;

            pget->send();

            auto strLocation = pget->payload("location").as_string();

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

         auto pget = __create_new < ::nano::http::get>();

         pget->m_url = strUrl;

         pget->payload("only_headers") = true;

         pget->m_timeSyncTimeout = 5_min;

         pget->send();

         auto iHttpStatusCode = pget->payload("http_status_code").as_int();

         return iHttpStatusCode == 200;

      }



      ::string http::get(const ::url::url & url)
      {

         auto urlEffetive = get_effective_url(url);

         auto pget = __create_new < ::nano::http::get>();

         pget->m_url = urlEffetive;

         pget->m_timeSyncTimeout = 5_min;

         pget->send();

         auto iHttpStatusCode = pget->payload("http_status_code").as_int();

         ::string strOutput;

         strOutput = pget->get_memory_response()->as_utf8();

         return strOutput;

      }


      void http::download(const ::file::path & path, const ::url::url & url)
      {

         auto urlEffective = get_effective_url(url);

         auto pget = __create_new < ::nano::http::get>();

         pget->m_url = urlEffective;

         pget->m_timeSyncTimeout = 2_hour;

         pget->send();

         auto iHttpStatusCode = pget->payload("http_status_code").as_int();

         file_system()->put_block(path, *pget->get_memory_response());

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
