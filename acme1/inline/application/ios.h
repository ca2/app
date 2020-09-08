//#include "acme/platform/static_start.h"
//
//extern ::acme::acme g_ace;

extern "C" void draw2d_factory_exchange();
extern "C" void imaging_factory_exchange();


int main(int argc, char * argv[])
{

   //class ace_ace ace_ace;
   //g_ace.ref();
   //::acme::acme acme;

   //{
      
      g_pfnfactoryexchangeDraw2d = &draw2d_factory_exchange;
      
      g_pfnfactoryexchangeImaging = &imaging_factory_exchange;

      //::ace_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = __new(::acme::system());
         
         psystem->application_initialize();

         application_common(psystem);
   
         //psystem->set_main_struct(&mainstruct);

         psystem->system_construct(argc, argv);

         //return ace_run_system(psystem);
         
     ::estatus estatus=    os_application_system_run(psystem);
   
   ::i32 iErrorStatus = estatus.error_status();
   
   return iErrorStatus;

      //}

   //}

}



