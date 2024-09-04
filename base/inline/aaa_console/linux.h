

int main(int argc, char* argv[])
{

   //class aura_aura aura_aura;

   //{

   //   ::aura_main_struct mainstruct;

   //   console_initialize(mainstruct);

   //   {

   //      auto psystem = ::place(new ::aura::system());

   //      psystem->system_construct(&mainstruct, argc, argv);

   //      return aura_run_system(psystem);

   //   }

   //}

   auto psystem = ::place(new ::aura::system());

   psystem->console_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::e_status estatus = (void) psystem->inline_init();

   if (::succeeded(estatus))
   {
    
      main();

      estatus = papp->m_estatus;

   }

   ::i32 iErrorStatus = estatus.error_status();

   psystem->inline_term();

   return iErrorStatus;

}



