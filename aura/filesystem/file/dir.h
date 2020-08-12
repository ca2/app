#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{


   CLASS_DECL_AURA string name(string path);
   CLASS_DECL_AURA ::file::path install();
   CLASS_DECL_AURA ::file::path default_install();
   CLASS_DECL_AURA ::file::path inplace_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AURA ::file::path inplace_matter_install(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AURA ::file::path beforeca2();
   CLASS_DECL_AURA ::file::path module();
   CLASS_DECL_AURA ::file::path relative(::file::path path);
   CLASS_DECL_AURA ::file::path app_relative();
   CLASS_DECL_AURA::file::path appdata(); // appdata
   CLASS_DECL_AURA ::file::path archive();
   CLASS_DECL_AURA ::file::path tool();
   CLASS_DECL_AURA ::file::path public_system();
   CLASS_DECL_AURA ::file::path system();
   CLASS_DECL_AURA ::file::path config();
   CLASS_DECL_AURA ::file::path local();
   CLASS_DECL_AURA ::file::path sensitive();
   CLASS_DECL_AURA ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   CLASS_DECL_AURA ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   CLASS_DECL_AURA ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   CLASS_DECL_AURA ::file::path roaming();
   CLASS_DECL_AURA ::file::path program_data();
   CLASS_DECL_AURA ::file::path public_root(); // writable common root (non-bin, non-exe)
   CLASS_DECL_AURA bool is(const ::file::path & path);
   CLASS_DECL_AURA bool _is(const ::file::path & path);
   CLASS_DECL_AURA bool mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_AURA bool _mk(const  ::file::path & path); // makes a directory path (all intermediates too)
   CLASS_DECL_AURA bool mkdir(const  ::file::path & path); // only creates if parent dir already exists
   CLASS_DECL_AURA void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void ls_file(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA ::file::path bookmark();
   CLASS_DECL_AURA ::file::path home();
   CLASS_DECL_AURA ::file::path ca2_module();
   CLASS_DECL_AURA ::file::path base_module();
   CLASS_DECL_AURA ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_AURA ::file::path program_files_x86();
   CLASS_DECL_AURA ::file::path program_files();
   CLASS_DECL_AURA ::file::path program_data();
   CLASS_DECL_AURA ::file::path stage(string strAppId, string strPlatform, string strConfiguration);
   CLASS_DECL_AURA ::file::path sys_temp();


} // namespace dir



