#pragma once


#include "application.h"
//#include "acid/primitive/collection/pointer_array.h"


namespace acid
{


   class CLASS_DECL_ACID application_array :
      virtual public pointer_array < ::acid::application >
   {
   public:


      //application_array(::particle * pparticle);
      application_array();
      application_array(const application_array & a);
      application_array(application_array && a);
      virtual ~application_array();


      application_array & operator = (const application_array & a);
      application_array & operator = (application_array && a);

      ::acid::application * find_by_app_id(const ::string & strAppId);

      ::acid::application * find_running_defer_try_quit_damaged(const string & strAppid);

      bool lookup(const string & strAppId, ::pointer<::acid::application>& papp);


   };


} // namespace apex




