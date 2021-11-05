#pragma once


#include "helloaxis/helloaxis.h"
#include "base/base/base.h"


#ifdef _APP_HELLO_BASE_LIBRARY
#define CLASS_DECL_APP_HELLO_BASE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_HELLO_BASE  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace hellobase
{

   class application;
   class document;
   class impact;

} // namespace flag


#define APP_TYPE ::hellobase::application


#include "hellobase_render.h"

#include "hellobase_document.h"
#include "hellobase_view_base.h"
#include "hellobase_view.h"
#include "hellobase_main_frame.h"

#include "hellobase_application.h"

