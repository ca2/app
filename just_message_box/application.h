#pragma once



#include "acme/platform/application.h"


namespace app_just_message_box
{


   class CLASS_DECL_APP_JUST_MESSAGE_BOX_APP application :
      virtual public ::platform::application
   {
   public:


      application();

      __DECLARE_APPLICATION_RELEASE_TIME();



      void on_request(::request * prequest) override;


      virtual void show_message_box();


   };


} // namespace app_just_acme_message_box



