#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{


   CLASS_DECL_APEX string name(string path);
   CLASS_DECL_APEX ::file::path install();
   CLASS_DECL_APEX ::file::path default_install();
   CLASS_DECL_APEX ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_APEX ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_APEX ::file::path beforeca2();
   CLASS_DECL_APEX ::file::path module();
   CLASS_DECL_APEX ::file::path relative(::file::path path);
   CLASS_DECL_APEX ::file::path app_relative();
   CLASS_DECL_APEX::file::path appdata(); // appdata
   CLASS_DECL_APEX ::file::path archive();
   CLASS_DECL_APEX ::file::path tool();
   CLASS_DECL_APEX ::file::path public_system();
   CLASS_DECL_APEX ::file::path system();
   CLASS_DECL_APEX ::file::path config();
   CLASS_DECL_APEX ::file::path local();
   CLASS_DECL_APEX ::file::path sensitive();
   CLASS_DECL_APEX ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   CLASS_DECL_APEX ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   CLASS_DECL_APEX ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   CLASS_DECL_APEX ::file::path roaming();
   CLASS_DECL_APEX ::file::path program_data();
   CLASS_DECL_APEX ::file::path public_root(); // writable common root (non-bin, non-exe)
   CLASS_DECL_APEX bool is(const ::file::path & path);
   CLASS_DECL_APEX bool _is(const ::file::path & path);
   CLASS_DECL_APEX bool mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_APEX bool _mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_APEX bool mkdir(const  ::file::path & path); // only creates if parent dir already exists
   CLASS_DECL_APEX void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_APEX void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_APEX void ls_file(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_APEX void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_APEX void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_APEX ::file::path bookmark();
   CLASS_DECL_APEX ::file::path home();
   CLASS_DECL_APEX ::file::path ca2_module();
   CLASS_DECL_APEX ::file::path base_module();
   CLASS_DECL_APEX ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_APEX ::file::path program_files_x86();
   CLASS_DECL_APEX ::file::path program_files();
   CLASS_DECL_APEX ::file::path program_data();
   CLASS_DECL_APEX ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_APEX ::file::path sys_temp();


} // namespace dir



