#pragma once


namespace uwp
{


   namespace axis
   {


      class CLASS_DECL_AXIS dir:
         virtual public ::_UWP::dir,
         virtual public ::file::dir::axis::system
      {
      public:




         //string      m_strCa2;


         dir(::object * pobject);


         //using ::file::system_dir::path;
         //virtual class ::file::path & path();
         //virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);

         //virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = nullptr);
         virtual ::file::listing &  ls(::aura::application *  papp, ::file::listing & listing);
//         virtual bool  ls_pattern(::aura::application *  papp,const char * lpcsz,const char * lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,bool_array * pbaIsDir = nullptr,i64_array * piaSize = nullptr);
         //       virtual bool  ls(::aura::application *  papp,const char * lpcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,bool_array * pbaIsDir = nullptr,i64_array * piaSize = nullptr);
         //     virtual bool  rls_pattern(::aura::application *  papp,const char * lpcsz,const char * lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,bool_array * pbaIsDir = nullptr,i64_array * piaSize = nullptr,e_extract eextract = extract_first);
         //   virtual bool  rls(::aura::application *  papp,const char * lpcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,e_extract eextract = extract_first);
         // virtual bool  rls_dir(::aura::application *  papp,const char * lpcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr);
         //      virtual bool  ls_dir(::aura::application *  papp,const char * lpcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
         //    virtual bool  ls_file(::aura::application *  papp,const char * lpcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
         virtual bool  is_impl(const ::file::path & lpcsz,::aura::application *  papp) override;
         //virtual bool  is(const string & str,::aura::application *  papp);
         virtual bool  name_is(const ::file::path & str,::aura::application *  papp) override;
         //virtual bool  has_subdir(::aura::application *  papp,const char * lpcsz);
         //virtual bool  is_inside(const char * lpcszDir,const char * lpcszPath,::aura::application *  papp);
         //virtual bool  is_inside_time(const char * lpcsz, ::aura::application *  papp);
         //virtual void root_ones(string_array & straPath, string_array & straTitle, ::aura::application *  papp);
         //virtual bool mk(const char * lpcsz, ::aura::application *  papp);
         //virtual bool rm(::aura::application *  papp, const char * psz, bool bRecursive = true);


         //virtual string name(const char * lpcsz);
         //virtual string name(const string & str);

         //virtual string warehouse(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string time(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string stage(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string stageapp(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string netseed(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //
         //// stage in ccwarehouse spalib
         //virtual string element(const char * lpcsz, const char * lpcsz2 = nullptr);
         //virtual string element();
         //virtual string element(const string & str);
         //virtual string element(const string & str, const string & str2);
         //virtual string element(const char * lpcsz, const string & str2);
         //virtual string element(const string & str, const char * lpcsz2);

         //virtual string module(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string ca2module(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual void time_square(string &str);
         //virtual string time_log(const char * pszId);


         //virtual string trash_that_is_not_trash(const char * psz);

         //virtual string appdata(const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);

         //virtual string usersystemappdata(::aura::application *  papp, const char * lpcszPrefix, const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string userappdata(::aura::application *  papp, const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string userdata(::aura::application *  papp, const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string userfolder(::aura::application *  papp, const char * lpcsz = nullptr, const char * lpcsz2 = nullptr);
         //virtual string default_os_user_path_prefix(::object * pobject);
         //virtual string default_userappdata(::aura::application *  papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = nullptr);
         //virtual string default_userdata(::aura::application *  papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
         //virtual string default_userfolder(::aura::application *  papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
         //virtual string userquicklaunch(::aura::application *  papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);
         //virtual string userprograms(::aura::application *  papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);

         //virtual string commonprograms(const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);

         //virtual string commonappdata();

         virtual bool initialize();
         //protected:
         //   class path     m_path;
         //   string         m_strTimeFolder;
         //   string         m_strNetSeedFolder;
      };


   } // namespace axis


} // namespace uwp