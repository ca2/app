


::platform::application * get_acid_app();


#ifdef APP_TYPE


::platform::application* get_acid_app()
{

   return øallocate APP_TYPE();

}


#endif


#include "acme/inline/_app_impl.h"

