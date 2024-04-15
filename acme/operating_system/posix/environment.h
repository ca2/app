#pragma once


#include "acme/operating_system/environment.h"


namespace acme_posix
{


   class CLASS_DECL_ACME environment :
      virtual public ::operating_system::environment
   {
   public:


      ::status < ::string > lookup(const ::scoped_string & scopedstrKey) override;


   };


} // namespace acme_posix



