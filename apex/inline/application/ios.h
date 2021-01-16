//#include "apex/platform/static_start.h"
//
//extern ::apex::apex g_apex;

extern "C" void draw2d_factory_exchange();
extern "C" void imaging_factory_exchange();


int main(int argc, char * argv[])
{

   //class apex_apex apex_apex;
   //g_apex.ref();
   //::apex::apex apex;

   //{
      
      g_pfnfactoryexchangeDraw2d = &draw2d_factory_exchange;
      
      g_pfnfactoryexchangeImaging = &imaging_factory_exchange;

      //::apex_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = __new(::apex::system());
         
         //psystem->application_initialize();

         application_common(psystem);
   
         //psystem->set_main_struct(&mainstruct);

         psystem->system_construct(argc, argv);

         //return apex_run_system(psystem);
         
     ::e_status estatus=    os_application_system_run(psystem);
   
   ::i32 iErrorStatus = estatus.error_status();
   
   return iErrorStatus;

      //}

   //}

}



