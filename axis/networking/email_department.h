#pragma once


#include "acme/platform/department.h"


namespace networking
{


   class CLASS_DECL_AXIS email_department :
      virtual public ::acme::department
   {
   public:


      email_department();


      bool utf8_mail(class ::networking::email * pemail);


      virtual bool syntax_is_valid(const ::scoped_string & scopedstrEmailAddress);

      virtual bool is_valid_public_address(const ::scoped_string & scopedstrEmailAddress);


   };


} // namespace net



