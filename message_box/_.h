#pragma once


#include "app/_.h"


#ifdef _APP_MESSAGE_BOX_LIBRARY
#define CLASS_DECL_APP_MESSAGE_BOX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_MESSAGE_BOX  CLASS_DECL_IMPORT
#endif


namespace app_message_box
{


   class application;
   class main_window;


} // namespace app_message_box






