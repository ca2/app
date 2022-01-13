//#include "aura/platform/static_start.h"
//
//extern ::aura::aura g_aura;

extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);


int main(int argc, char * argv[])
{

   //class aura_aura aura_aura;
   //g_aura.ref();
   //::aura::aura aura;

   //{
      
      g_pfnfactoryexchangeDraw2d = &([a-z0-9_]+)_factory;
      
      g_pfnfactoryexchangeImaging = &([a-z0-9_]+)_factory;

      //::aura_main_struct mainstruct;

      //application_initialize(mainstruct);

//      {

         auto psystem = __new(::aura::system());
         
         psystem->application_initialize();

         application_common(psystem);
   
         //psystem->set_main_struct(&mainstruct);

         psystem->system_construct(argc, argv);

         //return aura_run_system(psystem);
         
     ::e_status3 estatus=    os_application_system_run(psystem);
   
   ::i32 iErrorStatus = estatus.error_status();
   
   return iErrorStatus;

      //}

   //}

}



