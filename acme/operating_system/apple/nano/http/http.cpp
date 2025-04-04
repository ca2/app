//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_http.h"


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
   
   pget->set_finished();
   
//
//   passynchronoushttpdata->m_response.m_set["http_status_code"] = http_status;
//   
//   passynchronoushttpdata->information() << "apple::nano::http response Finished with status "<< http_status << " going to set manual happening";
//   
//   passynchronoushttpdata->passynchronoushttpdata->m_happening.set_happening();
//
//   information() << "apple::nano::http response manual happening set";

   
   //passynchronoushttpdata->m_function(passynchronoushttpdata);
   
}




void http::perform(::nano::http::get * pget)
{
   
   //      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
   //      {                                s_http_response(pasynchronoushttpresponse);
   //      };
   
   pget->increment_reference_count();
   
   nano_asynchronous_http_get(pget->m_url.as_string().c_str(), &s_http_response, (::subparticle *) pget);
   
         }


      } // namespace http


   } // namespace nano


} // namespace apple

