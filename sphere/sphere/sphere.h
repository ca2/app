#pragma once



#include "aura/_.h"




#ifdef __SPHERE__LIBRARY
#define CLASS_DECL_SPHERE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SPHERE  CLASS_DECL_IMPORT
#endif


namespace sphere
{


   class application;


} // namespace sphere


#undef APP_TYPE
#define APP_TYPE ::sphere::application


#include "app/sphere/charguess/charguess.h"
#include "app/sphere/colorertake5/colorertake5.h"
//#include "app/sphere/net/mail/mail.h"
//#include "app/sphere/net/sockets/bsd/sip/"
//#include "app/sphere/pcre/pcre.h"


//#include "sphere_department.h"




#include "app/sphere/console/console.h"
#include "app/sphere/hi5/hi5.h"





#include "sphere_main_frame.h"


#include "sphere_application.h"


#include "sphere_library.h"











