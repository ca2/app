#include "console_common.h"


void process_main();



int main(int argc, TCHAR ** argv)
{

   process_set_args(argc, argv);

   process_main();

   return process_get_status();

}

#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/library.h"


#endif


#endif


#include "acme/_defer.h"



