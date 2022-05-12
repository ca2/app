#include "application_common.h"
#include "__apps.inl"


#include "acme/platform/system_setup.h"


#include "_main_hold.h"


APPLICATION::application g_app;


__embed_resource(g_app)



#if !defined(CUBE)


#include "_new_impl.h"


#include "acme/library.h"


#endif


#include "acme/_defer.h"



