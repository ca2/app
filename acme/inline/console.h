#include "console_common.h"


void stage();
void acme_system_init();
void acme_system_term();



int main(int argc, TCHAR ** argv)
{

   process_set_args(argc, argv);

   acme_system_init();

   stage();

   acme_system_term();

   return process_get_status();

}

#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/library.h"


#endif


#endif


#include "acme/_defer.h"



