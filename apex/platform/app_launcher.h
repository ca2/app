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

      virtual void initialize_app_launcher(::object * pobject, string strPlatform, string strApp);

      virtual string get_executable_path();

      virtual string get_params();

      virtual void run();

   };




} // namespace apex



