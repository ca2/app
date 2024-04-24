#pragma once


#include "app/_.h"


#if defined(_app_message_box_project)
#define CLASS_DECL_APP_MESSAGE_BOX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_MESSAGE_BOX  CLASS_DECL_IMPORT
#endif


namespace app_message_box
{


   class application;
   class main_window;


} // namespace app_message_box


#undef APPLICATION_CLASS
#define APPLICATION_CLASS ::app_message_box::application




