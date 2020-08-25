﻿#pragma once


namespace plugin
{


   class plugin;


   class CLASS_DECL_BASE system :
      virtual public ::aura::system
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


