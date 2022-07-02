#include "application_common.h"
#include "__apps.inl"


#include "acme/platform/system_setup.h"


#include "_main_hold.h"


//__FACTORY_IMPORT void IDENTIFIER_CONCATENATE(APPLICATION, _factory)(::factory::factory *);


//app_factory g_appfactory(&::IDENTIFIER_CONCATENATE(APPLICATION, _factory));



//__embed_resource(g_app)



#if !defined(CUBE)


#include "_new_impl.h"


#include "acme/library.h"


#endif


#include "acme/_defer.h"

#ifdef WINDOWS
#else
int main(int argc, char * argv[], char * envp[])
#endif
{

   main_hold mainhold;

   auto papp = __new(APPLICATION::application);

   papp->set_args(argc, argv, envp);

#if defined(LINUX) || defined(FREEBSD)

   papp->m_pchar_binary__matter_zip_start = embed_resource::get_start();

   papp->m_pchar_binary__matter_zip_end = embed_resource::get_end();

#endif

   int iExitCode = papp->main_loop();

   return iExitCode;

}



