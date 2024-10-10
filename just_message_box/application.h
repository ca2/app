#pragma once



#include "acme/platform/application.h"


namespace app_just_message_box
{


   class CLASS_DECL_APP_JUST_MESSAGE_BOX_APP application :
      virtual public ::acme::application
   {
   public:


      application();


      void on_request(::request * prequest) override;


      virtual void show_message_box();


   };


} // namespace app_just_acme_message_box



