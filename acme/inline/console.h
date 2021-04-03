#include "console_common.h"
#include "acme/operating_system.h"
#ifdef WINDOWS
#include "acme/primitive/collection/strdup_array.h"
#endif

//void stage();
void acme_system_init();
void acme_system_term();


CLASS_DECL_ACME void process_set_args(int argc, platform_char ** argv);

#ifdef WINDOWS
int main(int argc, platform_char ** argv)
#else
int main(int argc, platform_char ** argv, platform_char ** envp)
#endif
{

   process_set_args(argc, argv);

   acme_system_init();

   {

#ifdef WINDOWS

      wcsdup_array wcsdupa;

      auto envp = wcsdupa.windows_get_envp();

#endif

      implement(argc, argv, envp);

   }

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



