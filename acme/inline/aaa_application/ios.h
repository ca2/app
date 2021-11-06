//#include "acme/platform/static_start.h"
//
//extern ::acme::acme g_acme;

extern "C" void draw2d_factory_exchange(::factory_map * pfactorymap);
extern "C" void imaging_factory_exchange(::factory_map * pfactorymap);


int main(int argc, char * argv[])
{

   //class acme_acme acme_acme;
   //g_acme.ref();
   //::acme::acme acme;

   //{
      
      g_pfnfactoryexchangeDraw2d = &draw2d_factory_exchange;
      
      g_pfnfactoryexchangeImaging = &imaging_factory_exchange;

      //::acme_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = __new(class ::system());
         
         psystem->application_initialize();

         application_common(psystem);
   
         //psystem->set_main_struct(&mainstruct);

         psystem->system_construct(argc, argv);

         //return acme_run_system(psystem);
         
     ::e_status estatus=    os_application_system_run(psystem);
   
   ::i32 iErrorStatus = estatus.error_status();
   
   return iErrorStatus;

      //}

   //}

}



