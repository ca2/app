

int main(int argc, char * argv[])
{

   //class aura_aura aura_aura;

   //{

   //   ::aura_main_struct mainstruct;

   //   application_initialize(mainstruct);

   //   {

   //      auto psystem = __allocate ::aura::system();

   //      psystem->set_main_struct(&mainstruct);

   //      psystem->system_construct(argc, argv);

   //      return aura_run_system(psystem);

   //   }

   //}

   auto psystem = __allocate ::aura::system();

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::e_status estatus = os_application_system_run(psystem);

   int iErrorStatus = estatus.error_status();

   return iErrorStatus;


}



