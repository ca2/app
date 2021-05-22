

int main(int argc, char * argv[], char * envp[])
{

   set_main_thread();

   string strAppId = executable_get_app_id();

   auto psystem = platform_create_system(strAppId);

   auto papplicationStartup = psystem->new_application(strAppId);

   psystem->__refer(psystem->m_papplicationStartup, papplicationStartup);

   psystem->set_main_struct(*psystem->m_papplicationStartup);

//   ::e_status estatus = ::success;

//   if(psystem->m_bUser || psystem->m_bUser.undefined())
//   {
//
//      estatus = psystem->defer_low_initialize_user();
//
//      if(!estatus)
//      {
//
//         return -1;
//
//      }
//
//   }

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(argc, argv, envp);

//   auto estatus = psystem->system_main();
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   return iErrorStatus;

   auto estatus = psystem->init_system();

   if(!estatus)
   {

      return estatus.error_status();

   }

   auto pnode = psystem->node();

   estatus = pnode->main();

   auto estatusEnd = psystem->end();

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const char * br_init_get_symbol()
{

    return s_pszBinRelocInitGetSymbol;

}



