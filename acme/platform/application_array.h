#pragma once


#include "application.h"
//#include "acme/prototype/collection/pointer_array.h"


namespace platform
{


   class CLASS_DECL_ACME application_array :
      virtual public pointer_array < ::platform::application >
   {
   public:


      //application_array(::particle * pparticle);
      application_array();
      application_array(const application_array & a);
      application_array(application_array && a);
      virtual ~application_array();


      application_array & operator = (const application_array & a);
      application_array & operator = (application_array && a);

      ::platform::application * find_by_app_id(const ::string & strAppId);

      ::platform::application * find_running_defer_try_quit_damaged(const string & strAppid);

      bool lookup(const string & strAppId, ::pointer<::platform::application>& papp);


   };


} // namespace platform




