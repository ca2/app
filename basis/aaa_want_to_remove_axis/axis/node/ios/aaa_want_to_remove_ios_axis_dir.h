#pragma once


namespace ios
{


   namespace axis
   {


      class CLASS_DECL_AXIS dir :
         virtual public ::file::dir::axis::system,
         virtual ::ios::dir
      {
      public:


         //      dir(::aura::application *   papp);
         //
         //
         //      virtual void  ls_pattern(::aura::application *   papp, const char * pcsz, const char * lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //      virtual void  ls(::aura::application *   papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //      virtual void  rls_pattern(::aura::application *   papp, const char * pcsz, const char * lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr, e_extract eextract = extract_first);
         //      virtual void  rls(::aura::application *   papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, e_extract eextract = extract_first);
         //      virtual void  rls_dir(::aura::application *   papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr);
         //      virtual void  ls_dir(::aura::application *   papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
         //      virtual bool  has_subdir(::aura::application *   papp, const char * pcsz);
         //      virtual void  ls_file(::aura::application *   papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
         //      virtual bool  is(const char * pcsz, ::aura::application *   papp);
         //      virtual bool  is(const string & str, ::aura::application *   papp);
         //      virtual bool  name_is(const string & str, ::aura::application *   papp);
         //      virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, ::aura::application *   papp);
         //      virtual bool  is_inside_time(const char * pcsz, ::aura::application *   papp);
         //      virtual void root_ones(string_array & stra, string_array & straTitle, ::aura::application *   papp);
         //      virtual bool mk(const char * pcsz, ::aura::application *   papp);
         //      virtual bool rm(::aura::application *   papp, const char * psz, bool bRecursive = true);
         //
         //
         //      virtual string name(const char * pcsz);
         //      virtual string name(const string & str);
         //
         //      virtual string warehouse(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string time(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string stage(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string stageapp(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string netseed(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //
         //      // stage in ccwarehouse spalib
         //      virtual string matter(const char * pcsz, const char * lpcsz2 = nullptr);
         //      virtual string matter();
         //      virtual string matter(const string & str);
         //      virtual string matter(const string & str, const string & str2);
         //      virtual string matter(const char * pcsz, const string & str2);
         //      virtual string matter(const string & str, const char * lpcsz2);
         //
         //      virtual string module(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string ca2module(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual void time_square(string &str);
         //      virtual string time_log(const char * pszId);
         //
         //
         //      virtual string trash_that_is_not_trash(const char * psz);
         //
         //      virtual string appdata(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string commonappdata(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //
         //      virtual string usersystemappdata(::aura::application *   papp, const char * lpcszPrefix, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string userappdata(::aura::application *   papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string userdata(::aura::application *   papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string userfolder(::aura::application *   papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string default_os_user_path_prefix(::aura::application *   papp);
         //      virtual string default_userappdata(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = nullptr);
         //      virtual string default_userdata(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
         //      virtual string default_userfolder(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
         //      virtual string userquicklaunch(::aura::application *   papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);
         //      virtual string userprograms(::aura::application *   papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);
         //
         //      virtual string commonprograms(const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);
         //
         //      virtual bool initialize();
         //   protected:
         //      class path     m_path;
         //      string         m_strTimeFolder;
         //      string         m_strNetSeedFolder;


         dir(::layered * pobjectContext);


         //virtual string relpath(const char * lpcszSource,const char * lpcszRelative,const char * lpcsz2 = nullptr);
         virtual ::file::listing & ls(::object * pobject, ::file::listing & ls);

         //virtual bool  is(const char * pcsz,::aura::application * papp);
         virtual bool  is(const ::file::path & str,::aura::application * papp);
         virtual bool  name_is(const ::file::path & str,::aura::application * papp);
         //virtual bool  is_inside(const char * lpcszDir,const char * lpcszPath,::aura::application * papp);
         //virtual bool  is_inside_time(const char * pcsz,::aura::application * papp);
         //virtual void root_ones(string_array & patha,string_array & straTitle,::aura::application * papp);
         //virtual bool mk(const char * pcsz,::aura::application * papp);
         //virtual bool rm(::object * pobject,const char * psz,bool bRecursive = true);


         //virtual string name(const char * pcsz);
         //virtual string name(const string & str);

         //virtual string time(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string stage(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string stageapp(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string netseed(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);

         //// stage in ca2os spalib
         //virtual string matter(const char * pcsz,const char * lpcsz2 = nullptr);
         //virtual string matter();
         //virtual string matter(const string & str);
         //virtual string matter(const string & str,const string & str2);
         //virtual string matter(const char * pcsz,const string & str2);
         //virtual string matter(const string & str,const char * lpcsz2);

         //virtual string module(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string ca2module(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual void time_square(string &str);
         //virtual string time_log(const char * pszId);


         //virtual string trash_that_is_not_trash(const char * psz);

         //virtual string appdata(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string commonappdata(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string element_commonappdata(const string & strElement,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);

         //virtual string usersystemappdata(::object * pobject,const char * lpcszPrefix,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string userappdata(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string userdata(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string userfolder(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
         //virtual string default_os_user_path_prefix(::layered * pobjectContext);
         //virtual string default_userappdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
         //virtual string default_userdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
         //virtual string default_userfolder(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
         //virtual string userquicklaunch(::object * pobject,const char * pszRelativePath = nullptr,const char * lpcsz2 = nullptr);
         //virtual string userprograms(::object * pobject,const char * pszRelativePath = nullptr,const char * lpcsz2 = nullptr);

         //virtual string commonprograms(const char * pszRelativePath = nullptr,const char * lpcsz2 = nullptr);

         virtual bool initialize();


      };


   } // namespace axis


} // namespace ios


