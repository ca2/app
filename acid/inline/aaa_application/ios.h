//#include "acid/platform/static_start.h"
//
//extern ::acid::acid g_ace;

extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);


int main(int argc, char * argv[])
{

   //class ace_ace ace_ace;
   //g_ace.ref();
   //::acid::acid acid;

   //{
      
      g_pfnfactoryexchangeDraw2d = &([a-z0-9_]+)_factory;
      
      g_pfnfactoryexchangeImaging = &([a-z0-9_]+)_factory;

      //::ace_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = __allocate< ::acid::system >();
         
         psystem->application_initialize();

         application_common(psystem);
   
         //psystem->set_main_struct(&mainstruct);

         psystem->system_construct(argc, argv);

         //return ace_run_system(psystem);
         
     ::e_status estatus=    os_application_system_run(psystem);
   
   ::i32 iErrorStatus = estatus.error_status();
   
   return iErrorStatus;

      //}

   //}

}



