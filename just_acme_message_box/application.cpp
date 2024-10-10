#include "framework.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_just_acme_message_box);


namespace app_just_acme_message_box
{


   application::application()
   {

      m_strAppId = "app/just_acme_message_box";

      m_strAppName = "Just Acme Message Box";

      m_bNetworking = false;

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use nano_user icon?

   }


} // namespace app_just_acme_message_box



