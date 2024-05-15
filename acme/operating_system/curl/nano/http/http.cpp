//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"
#include "curl_easy.h"


namespace curl
{


   namespace nano
   {
      namespace http
      {
         http::http()
         {

            curl_global_init(CURL_GLOBAL_ALL);

         }
        
                          
         http::~http()
         {

            curl_global_cleanup();

         }
      

         //   void nano_http::s_http_response(long http_status, const void * data, long size, void * userdata)
         //   {
         //
         //      ::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *) userdata);
         //
         //      passynchronoushttpdata->m_data.m_memory.assign(data, size);
         //
         //      passynchronoushttpdata->m_data.m_set["http_status_code"] = http_status;
         //
         //      passynchronoushttpdata->m_event.SetEvent();
         //
         //      //passynchronoushttpdata->m_function(passynchronoushttpdata);
         //
         //   }


         void http::async(::nano::http::get * pget)
         {

            auto pgetHold = ::as_pointer(pget);

            //      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
            //      {                                s_http_response(pasynchronoushttpresponse);
            //      };

            //::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *) userdata);
            fork([this,pgetHold]()
            {

               auto pcurleasy = __create_new < curl_easy >();

               pcurleasy->get(pgetHold);

               pgetHold->set_finished();

              //pasynchronoushttpresponse->m_event.SetEvent();
              //pasynchronoushttpresponse->m_function(pasynchronoushttpresponse);
            });

            //nano_asynchronous_http_memory(scopedstrUrl.c_str(), s_http_response, pasynchronoushttpresponse.detach_particle());

         }


      } // namespace nano


   } // namespace http


} // namespace curl



//
//
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//char *url = NULL;
//
//// struct for holding http response.
//struct memory_struct{
//   char   *buffer;
//   size_t size;
//};
//
//
//void http_get(char *url, struct memory_struct *mem){
//   CURL *curl_handle;
//   CURLcode res;
//
//   mem->buffer = malloc(1);
//   mem->size   = 0;
//
//
//
//
//   // make the http request.
//   res = curl_easy_perform(curl_handle);
//
//   // check for errors.
//   if(res != CURLE_OK){
//      fprintf(stderr, "curl_easy_perform() failed: %s\n",
//              curl_easy_strerror(res));
//   }
//
//   // cleanup
//   curl_easy_cleanup(curl_handle);
//}
//
//int main(int argc, char** args){
//   // check number of arguments.
//   if(argc < 2){
//      printf("need url to make http request.\n");
//      return 0;
//   }
//
//   url = args[1];
//
//   printf("trying to make http request to: %s\n", url);
//   struct memory_struct m;
//   http_get(url, &m);
//   printf("\nresponse:\n%s", m.buffer);
//   return 0;