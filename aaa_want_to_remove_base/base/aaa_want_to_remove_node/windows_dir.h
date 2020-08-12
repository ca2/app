#pragma once


namespace windows
{


   class CLASS_DECL_BASE path :
      virtual public ::file::path
   {
   public:


      path(::object * pobject);
      virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);


   };


   class CLASS_DECL_BASE dir :
      virtual public ::file::system_dir
   {
   public:

      class path        m_path;
      string            m_strTimeFolder;
      string            m_strNetSeedFolder;

      string            m_strCa2;
      //string          m_strCommonAppData;
      string            m_strProfile;
      string            m_strAppData;
      string            m_strPrograms;
      string            m_strCommonPrograms;


      dir(::object * pobject);


      using ::file::system_dir::path;
      virtual class ::file::path & path();
      virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);

      virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = nullptr);
      virtual void  ls_pattern(__pointer(::aura::application) papp, const char * pcsz, const char * lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
      virtual void  ls(__pointer(::aura::application) papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr);
      virtual void  rls_pattern(__pointer(::aura::application) papp, const char * pcsz, const char * lpcszPattern, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, bool_array * pbaIsDir = nullptr, i64_array * piaSize = nullptr, e_extract eextract = extract_first);
      virtual void  rls(__pointer(::aura::application) papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr, e_extract eextract = extract_first);
      virtual void  rls_dir(__pointer(::aura::application) papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr, string_array * pstraRelative = nullptr);
      virtual void  ls_dir(__pointer(::aura::application) papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
      virtual bool  has_subdir(__pointer(::aura::application) papp, const char * pcsz);
      virtual void  ls_file(__pointer(::aura::application) papp, const char * pcsz, string_array * pstraPath = nullptr, string_array * pstraTitle = nullptr);
      virtual bool  is(const char * pcsz, __pointer(::aura::application) papp);
      virtual bool  is(const string & str, __pointer(::aura::application) papp);
      virtual bool  name_is(const string & str, __pointer(::aura::application) papp);
      virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, __pointer(::aura::application) papp);
      virtual bool  is_inside_time(const char * pcsz, __pointer(::aura::application) papp);
      virtual void root_ones(string_array & straPath, string_array & straTitle, __pointer(::aura::application) papp);
      virtual bool mk(const char * pcsz, __pointer(::aura::application) papp);
      virtual bool rm(__pointer(::aura::application) papp, const char * psz, bool bRecursive = true);


      virtual string name(const char * pcsz);
      virtual string name(const string & str);

      virtual string time(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string stage(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string stageapp(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string netseed(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);

      // stage in ca2os spalib
      virtual string element(const char * pcsz, const char * lpcsz2 = nullptr);
      virtual string element();
      virtual string element(const string & str);
      virtual string element(const string & str, const string & str2);
      virtual string element(const char * pcsz, const string & str2);
      virtual string element(const string & str, const char * lpcsz2);

      virtual string module(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string ca2module(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual void time_square(string &str);
      virtual string time_log(const char * pszId);


      virtual string trash_that_is_not_trash(const char * psz);

      virtual string appdata(const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string commonappdata(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);

      virtual string usersystemappdata(__pointer(::aura::application) papp, const char * lpcszPrefix, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string userappdata(__pointer(::aura::application) papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string userdata(__pointer(::aura::application) papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string userfolder(__pointer(::aura::application) papp, const char * pcsz = nullptr, const char * lpcsz2 = nullptr);
      virtual string default_os_user_path_prefix(::object * pobject);
      virtual string default_userappdata(__pointer(::aura::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
      virtual string default_userdata(__pointer(::aura::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
      virtual string default_userfolder(__pointer(::aura::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = nullptr);
      virtual string userquicklaunch(__pointer(::aura::application) papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);
      virtual string userprograms(__pointer(::aura::application) papp, const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);

      virtual string commonprograms(const char * pszRelativePath = nullptr, const char * lpcsz2 = nullptr);

      virtual bool initialize();


   };


} // namespace windows




