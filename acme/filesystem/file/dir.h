#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{


   CLASS_DECL_ACME string name(const char * pszPath);
   //CLASS_DECL_ACME bool mk(const string & strPath);
   CLASS_DECL_ACME bool _mk(const  ::file::path& path); // makes a directory path (all intermediates too)
   CLASS_DECL_ACME bool is(const ::file::path& path);
   CLASS_DECL_ACME bool _is(const ::file::path& path);
   CLASS_DECL_ACME bool mk(const  ::file::path& path); // makes a directory path (all intermediates too)
   CLASS_DECL_ACME bool mkdir(const  ::file::path& path); // only creates if parent dir already exists
   CLASS_DECL_ACME void ls(::file::patha& patha, const ::file::path& path);
   CLASS_DECL_ACME void ls_dir(::file::patha& patha, const ::file::path& path);
   CLASS_DECL_ACME void ls_file(::file::patha& patha, const ::file::path& path);
   CLASS_DECL_ACME void rls(::file::patha& patha, const ::file::path& path);
   CLASS_DECL_ACME void rls_dir(::file::patha& patha, const ::file::path& path);


   CLASS_DECL_ACME::file::path ca2_module();
   CLASS_DECL_ACME::file::path base_module();


} // namespace dir



