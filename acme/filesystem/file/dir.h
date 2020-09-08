#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{


   CLASS_DECL_ACME string name(string path);
   CLASS_DECL_ACME ::file::path install();
   CLASS_DECL_ACME ::file::path default_install();
   CLASS_DECL_ACME ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path beforeca2();
   CLASS_DECL_ACME ::file::path module();
   CLASS_DECL_ACME ::file::path relative(::file::path path);
   CLASS_DECL_ACME ::file::path app_relative();
   CLASS_DECL_ACME::file::path appdata(); // appdata
   CLASS_DECL_ACME ::file::path archive();
   CLASS_DECL_ACME ::file::path tool();
   CLASS_DECL_ACME ::file::path public_system();
   CLASS_DECL_ACME ::file::path system();
   CLASS_DECL_ACME ::file::path config();
   CLASS_DECL_ACME ::file::path local();
   CLASS_DECL_ACME ::file::path sensitive();
   CLASS_DECL_ACME ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   CLASS_DECL_ACME ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   CLASS_DECL_ACME ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   CLASS_DECL_ACME ::file::path roaming();
   CLASS_DECL_ACME ::file::path program_data();
   CLASS_DECL_ACME ::file::path public_root(); // writable common root (non-bin, non-exe)
   CLASS_DECL_ACME bool is(const ::file::path & path);
   CLASS_DECL_ACME bool _is(const ::file::path & path);
   CLASS_DECL_ACME bool mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_ACME bool _mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_ACME bool mkdir(const  ::file::path & path); // only creates if parent dir already exists
   CLASS_DECL_ACME void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACME void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACME void ls_file(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACME void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACME void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACME ::file::path bookmark();
   CLASS_DECL_ACME ::file::path home();
   CLASS_DECL_ACME ::file::path ca2_module();
   CLASS_DECL_ACME ::file::path base_module();
   CLASS_DECL_ACME ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_ACME ::file::path program_files_x86();
   CLASS_DECL_ACME ::file::path program_files();
   CLASS_DECL_ACME ::file::path program_data();
   CLASS_DECL_ACME ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path sys_temp();


} // namespace dir



