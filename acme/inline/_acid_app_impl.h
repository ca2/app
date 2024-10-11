


::acme::application * get_acid_app();


#ifdef APP_TYPE


::acme::application* get_acid_app()
{

   return __allocate APP_TYPE();

}


#endif


#include "acme/inline/_app_impl.h"

