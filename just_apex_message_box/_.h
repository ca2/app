#pragma once


#include "just_message_box/_.h"
#include "apex/_.h"


#if defined(_app_just_apex_message_box_project)
#define CLASS_DECL_APP_JUST_APEX_MESSAGE_BOX_APP  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_JUST_APEX_MESSAGE_BOX_APP  CLASS_DECL_IMPORT
#endif


namespace app_message_box
{

   class application;
   class window;

} // namespace flag


#undef APPLICATION_CLASS
#define APPLICATION_CLASS ::app_just_message_box::application


#include "application.h"



