

int main(int argc, char * argv[])
{

   string strAppId = executable_get_app_id();

   auto psystem = platform_create_system(strAppId);

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(argc, argv);

   ::e_status estatus = psystem->os_application_system_run();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const char * br_init_get_symbol()
{

    return s_pszBinRelocInitGetSymbol;

}



