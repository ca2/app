#pragma once


namespace apex
{


   class CLASS_DECL_APEX app_launcher : 
      virtual public ::object
   {
   public:


      string   m_strApp;
      string   m_strPlatform;

      ::pointer<::launcher>m_plauncher;



      app_launcher();

      virtual void initialize_app_launcher(::particle * pparticle, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrApp);


      virtual string get_executable_extension();

      virtual string get_executable_path();

      virtual string get_params();

      virtual void run();

   };




} // namespace apex



