//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"


namespace apple
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


void http::s_http_response(long http_status, const void * data, long size, void * userdata)
{
   
   ::pointer < ::nano::http::get > pget (transfer_t{}, (::subparticle *) userdata);
   
   pget->set_response(http_status, data, size);
   
   pget->m_callbackAsync(pget);
   
//
//   passynchronoushttpdata->m_response.m_set["http_status_code"] = http_status;
//   
//   passynchronoushttpdata->information() << "apple::nano::http response Finished with status "<< http_status << " going to set manual event";
//   
//   passynchronoushttpdata->passynchronoushttpdata->m_event.SetEvent();
//
//   information() << "apple::nano::http response manual event set";

   
   //passynchronoushttpdata->m_function(passynchronoushttpdata);
   
}




void http::async(::nano::http::get * pget)
{
   
   //      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
   //      {                                s_http_response(pasynchronoushttpresponse);
   //      };
   
   pget->increment_reference_count();
   
   nano_asynchronous_http_get(pget->m_strUrl.c_str(), &s_http_response, (::subparticle *) pget);
   
         }


      } // namespace http


   } // namespace nano


} // namespace apple

