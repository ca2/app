#pragma once


#include "acid/operating_system/environment.h"


namespace ace_posix
{


   class CLASS_DECL_ACID environment :
      virtual public ::operating_system::environment
   {
   public:


      ::status < ::string > lookup(const ::scoped_string & scopedstrKey) override;


   };


} // namespace ace_posix



