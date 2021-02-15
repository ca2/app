#include "console_common.h"
#include "acme/operating_system.h"


void stage();
void acme_system_init();
void acme_system_term();


CLASS_DECL_ACME void process_set_args(int argc, platform_char ** argv);


int main(int argc, platform_char ** argv)
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



