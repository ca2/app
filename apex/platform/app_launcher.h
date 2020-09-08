#pragma once


namespace apex
{


   class CLASS_DECL_APEX app_launcher:
      virtual public ::launcher
   {
   public:


      string   m_strApp;
      string   m_strPlatform;


      app_launcher(string strPlatform, string strApp);


      virtual string get_executable_path();

      virtual string get_params();

      virtual bool start();

   };




} // namespace apex



