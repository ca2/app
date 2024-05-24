//
// Created by camilo on 29/07/2023 21:20 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "curl_easy.h"
//#include "operating_system/windows/nano_http/http_get.h"


curl_easy::curl_easy()
{

   m_pcurl = curl_easy_init();

   //m_lHttpStatusCode = -1;
}


curl_easy::~curl_easy()
{

   curl_easy_cleanup(m_pcurl);

}

// write response data to the memory buffer.
size_t curl_easy::s_write_function(void *contents, size_t size, size_t nmemb, void *userp)
{

   auto pget = dynamic_cast< ::nano::http::get *>((::subparticle *)userp);

   size_t realsize = size * nmemb;

   pget->m_memory.append(contents, realsize);

   // return the size of content that is copied.
   return realsize;

}


void curl_easy::get(::nano::http::get * pget)
{


   ::string strUrl(pget->m_strUrl);


   //auto pfile = create_memory_file();
   // specify url, callback function to receive response, buffer to hold
   // response and lastly user agent for http request.
   curl_easy_setopt(m_pcurl, CURLOPT_URL, strUrl.c_str());
   curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);
   curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &curl_easy::s_write_function);
   curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, (void *)(::nano::http::get*)pget);
   curl_easy_setopt(m_pcurl, CURLOPT_USERAGENT, "nano_http");


   // make the http request.
   auto curl_code = curl_easy_perform(m_pcurl);

   if(curl_code != CURLE_ABORTED_BY_CALLBACK)
   {

      curl_easy_getinfo (m_pcurl, CURLINFO_RESPONSE_CODE, pget->m_setOut["http_status_code"].raw_pointer<long>());

   }
   else
   {

      throw ::exception(::error_failed);

   }


}

