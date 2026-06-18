//#include "apex/platform/static_start.h"
//
//extern ::apex::apex g_apex;

extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);


::i32 main(::i32 argc, char_pointer argv[])
{

   //class apex_apex apex_apex;
   //g_apex.ref();
   //::apex::apex apex;

   //{
      
      g_pfnfactoryexchangeDraw2d = &([a-z0-9_]+)_factory;
      
      g_pfnfactoryexchangeImaging = &([a-z0-9_]+)_factory;

      //::apex_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = allocateø ::apex::system();
         
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



