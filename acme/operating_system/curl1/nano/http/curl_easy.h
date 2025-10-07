//
// Created by camilo on 29/07/2023 21:18 <3ThomasBorregaardSorensen!!
// at kubuntu box at canada
//
#pragma once


#include "acme/nano/http/get.h"
#include <curl/curl.h>



class CLASS_DECL_ACME curl_easy :
virtual public ::particle
   {
   public:


//long m_lHttpStatusCode;


      CURL * m_pcurl;

   curl_easy();
   ~curl_easy() override;


   static size_t  s_write_function(void *contents, size_t size, size_t nmemb, void *userp);

      virtual void get(::nano::http::get * defer_get);



   };

