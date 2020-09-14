#pragma once


namespace plugin
{


   class plugin;


   class CLASS_DECL_APEX system :
      virtual public ::apex::system
   {
   public:


      plugin * m_pplugin;


      system();


      virtual bool open_link(const string & pszLink, const string & pszTarget);

      virtual ::estatus os_native_bergedge_start();

      virtual ::estatus verb();

      virtual string get_host_location_url();

   };


} // namespace plugin


