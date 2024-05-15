//
// Created by camilo on 20/08/2023 02:22 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{


   class http_connect :
      public hinternet
   {
   public:


      http_connect(http_session & session, const ::scoped_string & scopedstrHost);
      ~http_connect() override;

   };


} // namespace windows



