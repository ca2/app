#pragma once


namespace apex
{


   class CLASS_DECL_APEX app_launcher : 
      virtual public ::object
   {
   public:


      string   m_strApp;
      string   m_strPlatform;

      __pointer(::launcher) m_plauncher;



      app_launcher();

      virtual ::e_status initialize_app_launcher(::object * pobject, string strPlatform, string strApp);


      virtual string get_executable_path();

      virtual string get_params();

      virtual ::e_status run();

   };




} // namespace apex



