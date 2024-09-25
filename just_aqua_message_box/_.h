#pragma once


#include "aqua/_.h"


#if defined(_app_just_aqua_message_box_project)
#define CLASS_DECL_APP_JUST_AQUA_MESSAGE_BOX_APP  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_JUST_AQUA_MESSAGE_BOX_APP  CLASS_DECL_IMPORT
#endif


namespace app_message_box
{

   class application;
   class window;

} // namespace flag


#undef APPLICATION_CLASS
#define APPLICATION_CLASS ::app_just_aqua_message_box::application


#include "application.h"



