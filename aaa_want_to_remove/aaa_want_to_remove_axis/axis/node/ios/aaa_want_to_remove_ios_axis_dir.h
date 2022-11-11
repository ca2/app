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
         //      virtual void  ls_pattern(::aura::application *   papp, const ::string & pcsz, const ::string & lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //      virtual void  ls(::aura::application *   papp, const ::string & pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
         //      virtual void  rls_pattern(::aura::application *   papp, const ::string & pcsz, const ::string & lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr, enum_extract eextract = e_extract_first);
         //      virtual void  rls(::aura::application *   papp, const ::string & pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, enum_extract eextract = e_extract_first);
         //      virtual void  rls_dir(::aura::application *   papp, const ::string & pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr);
         //      virtual void  ls_dir(::aura::application *   papp, const ::string & pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
         //      virtual bool  has_subdir(::aura::application *   papp, const ::string & pcsz);
         //      virtual void  ls_file(::aura::application *   papp, const ::string & pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
         //      virtual bool  is(const ::string & pcsz, ::aura::application *   papp);
         //      virtual bool  is(const ::string & str, ::aura::application *   papp);
         //      virtual bool  name_is(const ::string & str, ::aura::application *   papp);
         //      virtual bool  is_inside(const ::string & lpcszDir, const ::string & lpcszPath, ::aura::application *   papp);
         //      virtual bool  is_inside_time(const ::string & pcsz, ::aura::application *   papp);
         //      virtual void root_ones(string_array & stra, string_array & straTitle, ::aura::application *   papp);
         //      virtual bool mk(const ::string & pcsz, ::aura::application *   papp);
         //      virtual bool rm(::aura::application *   papp, const ::string & psz, bool bRecursive = true);
         //
         //
         //      virtual string name(const ::string & pcsz);
         //      virtual string name(const ::string & str);
         //
         //      virtual string warehouse(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string time(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string stage(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string stageapp(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string netseed(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //
         //      // stage in ccwarehouse spalib
         //      virtual string matter(const ::string & pcsz, const ::string & lpcsz2 = nullptr);
         //      virtual string matter();
         //      virtual string matter(const ::string & str);
         //      virtual string matter(const ::string & str, const ::string & str2);
         //      virtual string matter(const ::string & pcsz, const ::string & str2);
         //      virtual string matter(const ::string & str, const ::string & lpcsz2);
         //
         //      virtual string module(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string ca2module(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual void time_square(string &str);
         //      virtual string time_log(const ::string & pszId);
         //
         //
         //      virtual string trash_that_is_not_trash(const ::string & psz);
         //
         //      virtual string appdata(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string commonappdata(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //
         //      virtual string usersystemappdata(::aura::application *   papp, const ::string & lpcszPrefix, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string userappdata(::aura::application *   papp, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string userdata(::aura::application *   papp, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string userfolder(::aura::application *   papp, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string default_os_user_path_prefix(::aura::application *   papp);
         //      virtual string default_userappdata(::aura::application *   papp, const ::string & lpcszPrefix, const ::string & lpcszLogin , const ::string & pszRelativePath = nullptr);
         //      virtual string default_userdata(::aura::application *   papp, const ::string & lpcszPrefix, const ::string & lpcszLogin, const ::string & pszRelativePath = nullptr);
         //      virtual string default_userfolder(::aura::application *   papp, const ::string & lpcszPrefix, const ::string & lpcszLogin, const ::string & pszRelativePath = nullptr);
         //      virtual string userquicklaunch(::aura::application *   papp, const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);
         //      virtual string userprograms(::aura::application *   papp, const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);
         //
         //      virtual string commonprograms(const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);
         //
         //      virtual bool initialize();
         //   protected:
         //      class path     m_path;
         //      string         m_strTimeFolder;
         //      string         m_strNetSeedFolder;


         dir(::particle * pparticle);


         //virtual string relpath(const ::string & lpcszSource, const ::string & lpcszRelative, const ::string & lpcsz2 = nullptr);
         virtual ::file::listing & ls(::particle * pparticle, ::file::listing & ls);

         //virtual bool  is(const ::string & pcsz,::aura::application * papp);
         virtual bool  is(const ::file::path & str,::aura::application * papp);
         virtual bool  name_is(const ::file::path & str,::aura::application * papp);
         //virtual bool  is_inside(const ::string & lpcszDir, const ::string & lpcszPath,::aura::application * papp);
         //virtual bool  is_inside_time(const ::string & pcsz,::aura::application * papp);
         //virtual void root_ones(string_array & patha,string_array & straTitle,::aura::application * papp);
         //virtual bool mk(const ::string & pcsz,::aura::application * papp);
         //virtual bool rm(::particle * pparticle, const ::string & psz,bool bRecursive = true);


         //virtual string name(const ::string & pcsz);
         //virtual string name(const ::string & str);

         //virtual string time(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string stage(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string stageapp(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string netseed(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);

         //// stage in ca2os spalib
         //virtual string matter(const ::string & pcsz, const ::string & lpcsz2 = nullptr);
         //virtual string matter();
         //virtual string matter(const ::string & str);
         //virtual string matter(const ::string & str, const ::string & str2);
         //virtual string matter(const ::string & pcsz, const ::string & str2);
         //virtual string matter(const ::string & str, const ::string & lpcsz2);

         //virtual string module(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string ca2module(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual void time_square(string &str);
         //virtual string time_log(const ::string & pszId);


         //virtual string trash_that_is_not_trash(const ::string & psz);

         //virtual string appdata(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string commonappdata(const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string element_commonappdata(const ::string & strElement, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);

         //virtual string usersystemappdata(::particle * pparticle, const ::string & lpcszPrefix, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string userappdata(::particle * pparticle, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string userdata(::particle * pparticle, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string userfolder(::particle * pparticle, const ::string & pcsz = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string default_os_user_path_prefix(::particle * pparticle);
         //virtual string default_userappdata(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin, const ::string & pszRelativePath = nullptr);
         //virtual string default_userdata(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin, const ::string & pszRelativePath = nullptr);
         //virtual string default_userfolder(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin, const ::string & pszRelativePath = nullptr);
         //virtual string userquicklaunch(::particle * pparticle, const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);
         //virtual string userprograms(::particle * pparticle, const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);

         //virtual string commonprograms(const ::string & pszRelativePath = nullptr, const ::string & lpcsz2 = nullptr);

         virtual bool initialize();


      };


   } // namespace axis


} // namespace ios


