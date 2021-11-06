

int main(int argc, char * argv[])
{

   auto psystem = __new(::aura::system());

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::e_status estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const char * br_init_get_symbol()
{

    return s_pszBinRelocInitGetSymbol;

}



