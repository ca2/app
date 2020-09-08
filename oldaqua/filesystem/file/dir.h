#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{


   CLASS_DECL_AQUA string name(string path);
   CLASS_DECL_AQUA ::file::path install();
   CLASS_DECL_AQUA ::file::path default_install();
   CLASS_DECL_AQUA ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path beforeca2();
   CLASS_DECL_AQUA ::file::path module();
   CLASS_DECL_AQUA ::file::path relative(::file::path path);
   CLASS_DECL_AQUA ::file::path app_relative();
   CLASS_DECL_AQUA::file::path appdata(); // appdata
   CLASS_DECL_AQUA ::file::path archive();
   CLASS_DECL_AQUA ::file::path tool();
   CLASS_DECL_AQUA ::file::path public_system();
   CLASS_DECL_AQUA ::file::path system();
   CLASS_DECL_AQUA ::file::path config();
   CLASS_DECL_AQUA ::file::path local();
   CLASS_DECL_AQUA ::file::path sensitive();
   CLASS_DECL_AQUA ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   CLASS_DECL_AQUA ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   CLASS_DECL_AQUA ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   CLASS_DECL_AQUA ::file::path roaming();
   CLASS_DECL_AQUA ::file::path program_data();
   CLASS_DECL_AQUA ::file::path public_root(); // writable common root (non-bin, non-exe)
   CLASS_DECL_AQUA bool is(const ::file::path & path);
   CLASS_DECL_AQUA bool _is(const ::file::path & path);
   CLASS_DECL_AQUA bool mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_AQUA bool _mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_AQUA bool mkdir(const  ::file::path & path); // only creates if parent dir already exists
   CLASS_DECL_AQUA void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AQUA void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AQUA void ls_file(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AQUA void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AQUA void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AQUA ::file::path bookmark();
   CLASS_DECL_AQUA ::file::path home();
   CLASS_DECL_AQUA ::file::path ca2_module();
   CLASS_DECL_AQUA ::file::path base_module();
   CLASS_DECL_AQUA ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_AQUA ::file::path program_files_x86();
   CLASS_DECL_AQUA ::file::path program_files();
   CLASS_DECL_AQUA ::file::path program_data();
   CLASS_DECL_AQUA ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path sys_temp();


} // namespace dir



