#pragma once


namespace file
{


   struct CLASS_DECL_ACME path_meta :
      public enumeration < ::file::enum_flag >,
      public file_time_set
   {

      enum_path                  m_epath;

      i64                        m_iSize; // if negative, not set/calculated/retrieved the file size_i32(for directories would be all contained elements total sum size_i32)
      int                        m_iDir; // if negative, not set/calculated/retrieved whether is a directory/folder/(file/folder/(...) container)
      strsize                    m_iName; // if negative, not set/calculated/retrieved where name starts
      strsize                    m_iBasePathLength; // if negative, not set/calculated/retrieved base path length in the path
      __pointer(::matter)        m_pmatterOsPath;


      path_meta(enum_path epath = e_path_none, i64 iSize = -1, i32 iDir = -1, i64 iName = -1, strsize iBasePathLength = -1, enumeration < ::file::enum_flag > eflag = ::file::e_flag_none)
      {

         m_epath                             = epath;
         m_iSize                             = iSize;
         m_iDir                              = iDir;
         m_iName                             = (strsize) iName;
         m_iBasePathLength                   = iBasePathLength;
         enumeration < ::file::enum_flag >::m_eenum   = eflag.enumeration < ::file::enum_flag >::m_eenum;

      }


      using enumeration < ::file::enum_flag >::operator -=;


   };


   
   
   // not rigorous at all file::path ... more "ryg"orous with performance and like you should know what are you doing
   class CLASS_DECL_ACME path :
      public string,
      public path_meta
   {
   public:

      path() { m_epath = e_path_file; }
      path(nullptr_t) {}
      path(enum_path epath) { m_epath = epath; }
      path(const ::string & str, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1);
      path(const path& path);
      path(const path_object& path);

      template < typename TYPE >
      inline path(const TYPE & t, enum_path epath = e_path_none, int iDir = -1, bool bNormalize = true, i64 iSize = -1) :
         path(__string(t), epath, iDir, bNormalize, iSize)
      {

      }

      ~path() noexcept;


      void set_type(enum_path epath);

      //::file::path replace_extension(const char * pszNewExtension, const char * pszOldExtension);
      void set_all_extensions(const ::string & strNewExtension);
      void set_final_extension(const ::string & strNewExtension);

      ::file::path with_all_extensions(const ::string & strNewExtension) const;
      ::file::path with_final_extension(const ::string & strNewExtension) const;

      inline char separator() const
      {

         return file_path_separator(m_epath);

      }

      inline const char* separator_sz() const
      {

         return file_path_separator_sz(m_epath);

      }

      inline char other_separator() const
      {

         return file_path_other_separator(m_epath);

      }


      path & operator = (const ::file::path & path);

      path & operator = (const ::string & str);

//      bool is_equal_full(const path & path) const
//      {
//
//#ifdef WINDOWS
//
//         if (_stricmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
//            return true;
//
//#else
//
//         if (strcmp(c_str(), path.c_str()) == 0) // undoubtely eaqual...
//            return true;
//
//#endif
//
//         return __node_further_file_is_equal(*this, path);
//
//      }


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

      bool operator == (const ::string & str) const
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


      bool operator != (const ::string & str) const
      {

         return operator != (path(str));

      }


      bool operator != (const char * psz) const
      {

         return operator != (string(psz));

      }
      //      bool operator == (const path & path) const;

      //      bool operator == (const ::string & str) const;
      //      bool operator == (const char * psz) const;
      bool operator == (const ::payload & payload) const;

      //      bool operator != (const path & path) const;

      //      bool operator != (const ::string & str) const;
      //      bool operator != (const char * psz) const;
      bool operator != (const ::payload & payload) const;

      path operator + (const path & path) const;


      path operator + (const ::string & str) const;

      path operator + (const char * psz) const;
      path operator + (const ::payload & payload) const;
      path operator + (const property & property) const;
      path operator + (const atom & atom) const;

      path & operator += (const path & path);
      path & operator += (const ::string & str);
      path operator / (const path & path) const;
      path operator / (const ::string & str) const;
      path operator / (const char * psz) const;
      path operator / (const ::payload & payload) const;
      path operator / (const property & property) const;
      path_array operator / (const string_array & path) const;

      path & operator /= (const path & path);
      path & operator /= (const ::string & str);
      path & operator /= (const char * psz);


      bool is_empty() const;
      bool has_char() const;




      //::file::path & file_cat(const ::string & str) { return *this + str; }

      //::file::path & operator | (const ::string & str) { return file_cat(str); } // what is good here is the operator precedence

      //string arg(const ::string & str) const { return ((const string &)*this) + str; }

      //string operator << (const ::string & str) const { return arg(str); }

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


//      void to_string(string & str) const;

      path sibling(const path & path) const;
      path sibling(const ::string & str) const;
      path sibling(const char * psz) const;

      path operator * (const path & path) const;

      path operator * (const ::string & str) const;
      path operator * (const char * psz) const;
      path operator * (const property & property) const;

      path & operator *= (const path & path);

      path & operator *= (const ::string & str);
      path & operator *= (const char * psz);
      path & operator *= (const property & property);

      ::file::path title() const;

      string name() const;

      string name(index i /* = -1 */) const;

      /// return index pointing to beginning of name
      index find_name() const;

      /// return index just after first dot in file name
      /// -1 if not found
      index find_all_extensions() const;

      /// return index just after last dot in file name
      /// -1 if not found
      index find_final_extension() const;

      //      bool is_equal(const ::file::path & path2) const;

      string all_extensions() const;

      //string ext() const;

      string final_extension() const;

      void split(string_array & patha) const;
      bool is_relative();

      path_array & ascendants_path(path_array & pathaFolder, path_array * ppathaRelative = nullptr) const;
      string_array & ascendants_name(string_array & namea) const;
      path_array ascendants_path() const;
      string_array ascendants_name() const;

      path relative() const;


      path folder() const;
      path folder(int i) const;
      path up() const;
      path up(int i) const;
      path & go_up();
      path & go_up(int i);
      path operator - (int i) const { return this->up(i); }
      path & operator -= (int i);
      using path_meta::operator -=;

      inline path operator | (enum_flag e) const { path path(*this); path |= e; return path; }


      ::file::path & patch_base_path(const ::file::path & pathBase)
      {

         auto iBasePathLength = m_iBasePathLength;

         if (iBasePathLength < 0)
         {

            iBasePathLength = 0;

         }

         auto pszRelative = c_str() + iBasePathLength;

         *this = pathBase / pszRelative;

         m_iBasePathLength = pathBase.length() + 1;

         return *this;

      }


   };


   //CLASS_DECL_ACME e_path file_path_get_type(const ::string & str, e_path epathForce);


   CLASS_DECL_ACME bool begins_eat_ci(string & str, const char * pcszPrefix);




} // namespace file


inline const char * FormatArgument(const ::file::path & value) noexcept;


template<>
inline uptr uptr_hash < const ::file::path & >(const ::file::path & key);


//CLASS_DECL_ACME ::file::path node_full_file_path(file::path path);


//CLASS_DECL_ACME ::file::path __xxxnode_full_file_path(file::path path);


inline ::file::path CLASS_DECL_ACME operator / (const ansichar * psz, const ::file::path & pathConcat)
{

   string str(psz);

   ::file::path path(str);

   return path / pathConcat;

}

