

int main(int argc, char * argv[])
{

   string strAppId = executable_get_app_id();

   auto psystem = platform_create_system(strAppId);

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(argc, argv);
   
   auto estatus = os_application_system_run(psystem);

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;

}



