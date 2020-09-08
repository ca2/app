

int main(int argc, char * argv[])
{

   //class ace_ace ace_ace;

   //{

   //   ::ace_main_struct mainstruct;

   //   application_initialize(mainstruct);

   //   {

   //      auto psystem = __new(::acme::system());

   //      psystem->set_main_struct(&mainstruct);

   //      psystem->system_construct(argc, argv);

   //      return ace_run_system(psystem);

   //   }

   //}

   auto psystem = platform_create_system(nullptr);

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::estatus estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


}



