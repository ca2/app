//
//  nano_http.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 22:01
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "http.h"

#include "acme/prototype/datetime/datetime.h"

#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
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

      
      void http::perform(::nano::http::get * pnanohttpget)
      {

         throw ::interface_only();

      }


      //void http::sync(::nano::http::get* defer_get)
      //{

      //   auto phappening = create_newø < ::manual_reset_happening >();

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


      ::url::url http::get_effective_url(const ::url::url & url, ::property_set & set)
      {

         ::string strUrl(url.as_string());

         int iRedirectLimit = 30;

         for(int iRedirect = 0; iRedirect < iRedirectLimit; iRedirect++)
         {

            auto pnanohttpget = create_newø < ::nano::http::get>();

            pnanohttpget->m_url = strUrl;

            pnanohttpget->m_ppropertyset = &set;

            pnanohttpget->payload("only_headers") = true;
            
            pnanohttpget->m_timeSyncTimeout = 5_min;

            send(pnanohttpget);

            auto strLocation = pnanohttpget->payload("out_headers")["location"].as_string();

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


      bool http::check_url_ok(const ::url::url& url, ::property_set & set)
      {

         auto urlEffective = get_effective_url(url, set);

         auto pnanohttpget = create_newø < ::nano::http::get>();

         pnanohttpget->m_url = urlEffective;

         pnanohttpget->m_ppropertyset = &set;

         pnanohttpget->payload("only_headers") = true;

         pnanohttpget->m_timeSyncTimeout = 5_min;

         send(pnanohttpget);

         auto iHttpStatusCode = pnanohttpget->payload("out_attributes")["http_status_code"].as_int();

         return iHttpStatusCode == 200;

      }


      ::string http::get(const ::url::url & url, ::property_set & set)
      {

         auto memoryOutput = ::transfer(as_memory(url, set));

         ::string strOutput = memoryOutput.as_utf8();

         return strOutput;

      }


      ::memory http::as_memory(const ::url::url & url, ::property_set & set)
      {

         auto urlEffetive = get_effective_url(url, set);

         auto pnanohttpget = create_newø < ::nano::http::get>();

         pnanohttpget->m_url = urlEffetive;

         pnanohttpget->m_ppropertyset = &set;

         pnanohttpget->m_timeSyncTimeout = 5_min;

         pnanohttpget->want_memory_response();

         send(pnanohttpget);

         auto iHttpStatusCode = pnanohttpget->payload("out_attributes")["http_status_code"].as_int();

         return *pnanohttpget->get_memory_response();

      }


      void http::download(const ::payload& payloadFile, const ::url::url& url, ::property_set & set,
                   const class ::time& timeTimeout)
      {

         auto pfile = file_system()->get_writer(payloadFile,
            ::file::e_open_create
            | ::file::e_open_defer_create_directory);

         class ::time time;

         time.Now();

         ::string strFileName = (datetime()->date_text_for_file() + "." + ::as_string(time.m_iNanosecond));

         ::file::path pathTime = directory()->home() / "Downloads/Time!!" / strFileName;

         download(pathTime, url, set);

         file()->copy(pfile, pathTime);

      }


      void http::download(const ::file::path & path, const ::url::url & url, ::property_set & set)
      {

         auto urlEffective = get_effective_url(url, set);

         auto pnanohttpget = create_newø < ::nano::http::get>();

         pnanohttpget->m_url = urlEffective;

         pnanohttpget->m_ppropertyset = &set;

         pnanohttpget->m_timeSyncTimeout = 2_hour;

         send(pnanohttpget);

         auto iHttpStatusCode = pnanohttpget->payload("out_attributes")["http_status_code"].as_int();

         file_system()->put_block(path, *pnanohttpget->get_memory_response());

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
