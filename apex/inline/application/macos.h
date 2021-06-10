

int main(int argc, char * argv[], char ** envp)
{
   
   string strAppId;
   
#ifdef _APP_ID

   strAppId = _APP_ID;
   
#endif

   auto psystem = platform_create_system(strAppId);

   if (!psystem)
   {

      return -1;

   }

   psystem->m_bConsole = false;

   application_common(psystem);

   psystem->system_construct(argc, argv, envp);

   //psystem->set_current_handles();

//   auto estatus = psystem->system_main();
//
//   if (!estatus)
//   {
//
//      ::i32 iErrorStatus = estatus.error_status();
//
//      return iErrorStatus;
//
//   }
   
   auto estatus = psystem->init_system();
   
   if(!estatus)
   {
      
      return estatus.error_status();
      
   }
   
   auto pnode = psystem->node();

   estatus = pnode->main();

   auto estatusEnd = psystem->end();
   
   if(!estatusEnd)
   {
      
      output_debug_string("error(s) while finishing system");
      
      
   }

   ::i32 iErrorStatus = estatus.error_status();

   return iErrorStatus;


//   string strAppId = executable_get_app_id();
//
//   auto psystem = platform_create_system(strAppId);
//
//   psystem->m_bConsole = false;
//
//   application_common(psystem);
//
//   psystem->system_construct(argc, argv);
//
//   auto estatus = os_application_system_run(psystem);
//
//   ::i32 iErrorStatus = estatus.error_status();
//
//   return iErrorStatus;

}



