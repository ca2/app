

int main(int argc, char* argv[])
{

   //class apex_apex apex_apex;

   //{

   //   ::apex_main_struct mainstruct;

   //   console_initialize(mainstruct);

   //   {

   //      auto psystem = __new(::apex::system());

   //      psystem->system_construct(&mainstruct, argc, argv);

   //      return apex_run_system(psystem);

   //   }

   //}

   auto psystem = __new(::apex::system());

   psystem->console_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::estatus estatus = (::estatus) psystem->inline_init();

   if (::succeeded(estatus))
   {
    
      main();

      estatus = Application.m_estatus;

   }

   ::i32 iErrorStatus = estatus.error_status();

   psystem->inline_term();

   return iErrorStatus;

}



