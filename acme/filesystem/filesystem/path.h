#pragma once


namespace file
{

   class path;

}


CLASS_DECL_ACME bool is_url(const char * pszCandidate);


CLASS_DECL_ACME bool __node_further_file_is_equal(const ::file::path & path1, const ::file::path & path2);


namespace file
{

   class path;
   class path_object;
   
   typedef CLASS_DECL_ACME string_array_base < ::file::path, string > patha;

   enum e_path
   {
      path_none,
      path_file,
      path_url,
      path_data
   };

   CLASS_DECL_ACME e_path get_path_type(const string & str, e_path epathForce = path_none);

   struct CLASS_DECL_ACME path_meta :
      public enumeration < ::file::enum_flag >
   {

      e_path                     m_epath;

      i64                        m_iSize; // if negative, not set/calculated/retrieved the file size_i32(for directories would be all contained elements total sum size_i32)
      int                        m_iDir; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)
      strsize                    m_iName; // if negative, not set/calculated/retrieved where name starts
      strsize                    m_iRelative; // if negative, not set/calculated/retrieved where relative starts - this information is very, very relative :-) much more than all own other ::file::path cached information (relative to which folders... not stored this information...)
      __pointer(::matter)        m_pmatterOsPath;


      path_meta(e_path epath = path_none, i64 iSize = -1, i32 iDir = -1, i64 iName = -1, strsize iRelative = -1, enumeration < ::file::enum_flag > eflag = ::file::e_flag_none)
      {

         m_epath                             = epath;
         m_iSize                             = iSize;
         m_iDir                              = iDir;
         m_iName                             = (strsize) iName;
         m_iRelative                         = iRelative;
         enumeration < ::file::enum_flag >::m_eenum   = eflag.enumeration < ::file::enum_flag >::m_eenum;

      }


      using enumeration < ::file::enum_flag >::operator -=;


   };


   CLASS_DECL_ACME string normalize_path(string strPath, e_path epath = path_none);

   CLASS_DECL_ACME bool normalize_path_inline(string & strPath, e_path & epath);

   inline char path_sep(e_path epath);

   inline const char * path_sepsz(e_path epath);

   inline char path_osep(e_path epath);

   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_ACME path :
      public string,
      public path_meta
   {
   public:

      path() { m_epath = path_file; }
      path(nullptr_t) {}
      path(e_path epath) { m_epath = epath; }
      path(const string & str, e_path epath = path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const path& path);
      path(const path_object& path);

      template < typename TYPE >
      inline path(const TYPE & t, e_path epath = path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
         path(__str(t), epath, iDir, bNormalize, iSize)
      {

      }

      ~path() noexcept;


      void set_type(e_path epath);

      ::file::path replace_file_extension(const char * pszNewExtension, const char * pszOldExtension);
      ::file::path replace_file_extension(const char * pszNewExtension);

      inline char sep() const
      {

         return path_sep(m_epath);

      }

      inline const char* sepsz() const
      {

         return path_sepsz(m_epath);

      }

      inline char osep() const
      {

         return path_osep(m_epath);

      }


      path & operator = (const ::file::path & path);

      path & operator = (const string & str);

      bool is_equal_full(const path & path) const
      {

#ifdef WINDOWS

         if (_stricmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#else

         if (strcmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#endif

         return __node_further_file_is_equal(*this, path);

      }

      bool is_equal_fast(const path & path) const
      {

#ifdef WINDOWS

         if (_stricmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#else

         if (strcmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
            return true;

#endif

         return false;

      }


      bool operator == (const path & path) const
      {

         return is_equal_fast(path);

      }

      bool operator == (const string & str) const
      {

         return operator == (path(str));

      }


      bool operator == (const char * psz) const
      {

         return operator == (string(psz));

      }


      bool operator != (const path & path) const
      {

         return !operator==(path);

      }


      bool operator != (const string & str) const
      {

         return operator != (path(str));

      }


      bool operator != (const char * psz) const
      {

         return operator != (string(psz));

      }
      //      bool operator == (const path & path) const;

      //      bool operator == (const string & str) const;
      //      bool operator == (const char * psz) const;
      bool operator == (const ::payload & payload) const;

      //      bool operator != (const path & path) const;

      //      bool operator != (const string & str) const;
      //      bool operator != (const char * psz) const;
      bool operator != (const ::payload & payload) const;

      path operator + (const path & path) const;


      path operator + (const string & str) const;

      path operator + (const char * psz) const;
      path operator + (const ::payload & payload) const;
      path operator + (const property & property) const;
      path operator + (const id & id) const;

      path & operator += (const path & path);
      path & operator += (const string & str);
      path operator / (const path & path) const;
      path operator / (const string & str) const;
      path operator / (const char * psz) const;
      path operator / (const ::payload & payload) const;
      path operator / (const property & property) const;
      patha operator / (const string_array & path) const;

      path & operator /= (const path & path);
      path & operator /= (const string & str);
      path & operator /= (const char * psz);


      bool is_empty() const;
      bool has_char() const;




      //::file::path & file_cat(const string & str) { return *this + str; }

      //::file::path & operator | (const string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const string & str) const { return ((const string &)*this) + str; }

      //string operator << (const string & str) const { return arg(str); }

      path & operator = (const char * psz);
      path & operator += (const char * psz);

      path & operator = (const ::payload & payload);
      path & operator += (const ::payload & payload);

      path & operator = (const property & property);
      path & operator += (const property & property);

      path & operator = (const wstring & wstr);
      path & operator += (const wstring & wstr);

      path & operator = (const widechar * psz);
      path & operator += (const widechar * psz);

      //path operator * () const;

      //path operator -- () const;
      //path operator -- (int) const { return operator --(); }


      void to_string(string & str) const;

      path sibling(const path & path) const;
      path sibling(const string & str) const;
      path sibling(const char * psz) const;

      path operator * (const path & path) const;

      path operator * (const string & str) const;
      path operator * (const char * psz) const;
      path operator * (const property & property) const;

      path & operator *= (const path & path);

      path & operator *= (const string & str);
      path & operator *= (const char * psz);
      path & operator *= (const property & property);

      ::file::path title() const;

      string name() const;

      string name(index i /* = -1 */) const;

      index find_file_name() const;

      //      bool is_equal(const ::file::path & path2) const;

      string extension() const;

      string ext() const;

      string final_extension() const;

      void split(string_array & patha) const;
      bool is_relative();

      patha & ascendants_path(patha & pathaFolder, patha * ppathaRelative = nullptr) const;
      string_array & ascendants_name(string_array & namea) const;
      patha ascendants_path() const;
      string_array ascendants_name() const;

      path relative() const;


      path folder() const;
      path folder(int i) const;
      path up() const;
      path up(int i) const;
      path & go_up();
      path & go_up(int i);
      path & operator -= (int i);
      using path_meta::operator -=;

      inline path operator | (enum_flag e) const { path path(*this); path |= e; return path; }

   };


   CLASS_DECL_ACME e_path get_path_type(const string & str, e_path epathForce);


   inline char path_sep(e_path epath)
   {

#ifdef WINDOWS

      if (epath == path_file)
      {

         return '\\';

      }

#endif

      return '/';

   }

   inline const char * path_sepsz(e_path epath)
   {

#ifdef WINDOWS

      if (epath == path_file)
      {

         return "\\";

      }

#endif

      return "/";

   }

   inline char path_osep(e_path epath)
   {

#ifdef WINDOWS

      if (epath == path_file)
      {

         return '/';

      }

#endif

      return '\\';

   }

   CLASS_DECL_ACME bool begins_eat_ci(string & str, const char * pcszPrefix);




} // namespace file


inline const char * FormatArgument(const ::file::path & value) noexcept;


template<>
inline uptr uptr_hash < const ::file::path & >(const ::file::path & key);


CLASS_DECL_ACME ::file::path node_full_file_path(file::path path);


CLASS_DECL_ACME ::file::path __node_full_file_path(file::path path);


inline ::file::path CLASS_DECL_ACME operator / (const ansichar * psz, const ::file::path & pathConcat)
{

   string str(psz);

   ::file::path path(str);

   return path / pathConcat;

}

