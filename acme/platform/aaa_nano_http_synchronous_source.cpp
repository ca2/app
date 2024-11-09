//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"


namespace apple
{


   nano_http::nano_http()
   {


   }


   nano_http::~nano_http()
   {

   }


   void nano_http::s_http_response(long http_status, const void * data, long size, void * userdata)
   {

      ::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *)userdata);

      passynchronoushttpdata->m_data.m_memory.assign(data, size);

      passynchronoushttpdata->m_data.m_set["http_status_code"] = http_status;

      passynchronoushttpdata->m_happening.SetEvent();

      //passynchronoushttpdata->m_function(passynchronoushttpdata);

   }


   void nano_http::asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
   {

      //      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
      //      {                                s_http_response(pasynchronoushttpresponse);
      //      };

      nano_asynchronous_http_memory(scopedstrUrl.c_str(), s_http_response, pasynchronoushttpresponse.detach_particle());

   }


} // namespace apple





