


::application * get_acid_app();


#ifdef APP_TYPE


::application* get_acid_app()
{

   return new APP_TYPE();

}


#endif


#include "apex/inline/_app_impl.h"

