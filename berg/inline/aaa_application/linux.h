

::i32 main(::i32 argc, char_pointer argv[])
{

   auto psystem = allocateø ::aura::system();

   psystem->application_initialize();

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::e_status estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


static const_char_pointer s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const_char_pointer br_init_get_symbol()
{

    return s_pszBinRelocInitGetSymbol;

}



