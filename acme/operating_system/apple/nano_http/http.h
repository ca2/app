//
// Created by camilo on 26/07/2023 23:20 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/nano_http.h"


namespace apple
{


   class CLASS_DECL_ACME nano_http :
      virtual public ::nano::http
   {
   public:
      
      
      nano_http();
      ~nano_http() override;
      
      
      
      virtual void asynchronous_memory(const ::scoped_string & scopedstrUrl, const ::property_set & set,
                                       const ::function < void(int iStatus, const ::memory & memory ) > & function);

   
   };


} // namespace apple





