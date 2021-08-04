#pragma once


namespace hotplugin
{


   class CLASS_DECL_BASE container_launcher :
      virtual public ::launcher
   {
   public:


      string      m_strChannel;
      string      m_strPlatform;

      container_launcher(string strPlatform, const ::string & pszChannel);

      virtual bool ensure_executable() { return true; }

      string get_params();

      virtual string get_executable_path();

   };


} // namespace ca2plugin_container


