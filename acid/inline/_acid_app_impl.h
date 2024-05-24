


::acid::application * get_acid_app();


#ifdef APP_TYPE


::acid::application* get_acid_app()
{

   return __new< APP_TYPE >();

}


#endif


#include "acid/inline/_app_impl.h"

