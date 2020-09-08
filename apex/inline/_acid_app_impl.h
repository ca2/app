


::aura::application * get_acid_app();


#ifdef APP_TYPE


::aura::application* get_acid_app()
{

   return new APP_TYPE();

}


#endif


#include "aura/inline/_app_impl.h"

