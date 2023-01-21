//
// Created by camilo on 23/12/22.
//
#pragma once


namespace file
{


//    inline path path::operator/(const path &path) const
//    {
//
//       return ::transfer(*this / ::scoped_string(path));
//
//    }


//    inline path path::operator/(const ::ansi_character *psz) const
//    {
//
//       return ::transfer(*this / ::scoped_string(psz));
//
//    }


//    inline path path::operator/(const ::string &str) const
//    {
//
//       return ::transfer(*this / ::scoped_string(str));
//
//    }


    inline path path::slashed_path(const ::scoped_string & scopedstr) const
    {

       string strPath;

       strPath = this->c_str();

       if (strPath.is_empty())
       {

          return scopedstr;

       }

       bool bJustAfterProtocol = scopedstr.ends("://") || scopedstr.ends(":/");

       if (bJustAfterProtocol || m_epath == e_path_url)
       {

          ::string str = scopedstr;

          str.find_replace("\\", "/");

          str.trim_left("/");

          if (bJustAfterProtocol)
          {

             return ::file::path(strPath + str, e_path_url);

          }
          else
          {

             return ::file::path(strPath + "/" + str, e_path_url);

          }

       }

       //strPath += separator();

       //str.trim_left("\\/");

       return ::file::path(strPath + "/" + scopedstr.skip_any_character_in("\\/"), e_path_file);

    }


} // namespace file







namespace file
{


    inline path_meta::path_meta(enum_path epath, i64 iSize, i32 iDir, i64 iName, strsize iBasePathLength, enumeration < ::file::enum_flag > eflag)
    {

       m_epath = epath;
       m_iSize = iSize;
       m_iDir = iDir;
       m_iName = (strsize)iName;
       m_iBasePathLength = iBasePathLength;
       m_flags = eflag;

    }


    inline path::path(const ::ansi_string & str, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            string(str)
    {

       m_iSize = iSize;

       if (epath == e_path_none)
       {

          m_epath = file_path_get_type(str, epath);

       }
       else
       {

          m_epath = epath;

       }

       if (bNormalizePath)
       {

          bool bCertainlySyntathicallyDir = file_path_normalize_inline(*this, m_epath);

          if (bCertainlySyntathicallyDir)
          {

             m_iDir = 1;

          }
          else
          {

             m_iDir = iDir;

          }

       }
       else
       {

          m_iDir = iDir;

       }

    }


    inline path::path(const ::wd16_string & wd16str, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::string(wd16str), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path::path(const ::wd32_string & wd32str, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::string(wd32str), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path::path(const ::ansi_character * pansisz, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::ansi_string(pansisz), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path::path(const ::wd16_character * pwd16sz, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::wd16_string(pwd16sz), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path::path(const ::wd32_character * pwd32sz, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::wd32_string(pwd32sz), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path_meta::~path_meta()
    {


    }


    //inline path::path(const ::payload& payload) :
    //   path(payload.file_path())
    //{


    //}


    //inline path::path(const ::property& property) :
    //   path(property.file_path())
    //{


    //}


    //inline path::path(const ::atom& atom) :
    //   path(atom.string())
    //{


    //}

    //   path::path(nullptr_t)
    //   {
    //
    //      m_epath = path_file;
    //
    //   }


    //   path::path(e_path epath)
    //   {
    //
    //      m_epath = epath;
    //
    //   }
    //namespace file
    //{

    //inline path::path(const path& path) :
    //   string((const string&)path),
    //   path_meta(path)
    //{

    //}


    //inline path::path(const path_object& path) :
    //   ::file::path((const ::file::path&)path)
    //{

    //}


    //
    //} // namespace file
    //


    //   path::path(const unichar * pwsz, strsize iCount, e_path epath, int iDir, bool bNormalizePath, i64 iSize) :
    //      string(pwsz, iCount),
    //      path_meta(epath, iSize, iDir)
    //   {
    //
    //      if (m_epath == path_none)
    //      {
    //
    //         m_epath = file_path_get_type(*this, epath);
    //
    //      }
    //
    //      if (bNormalizePath)
    //      {
    //
    //         bool bCertainlySyntathicallyDir = normalize_path_inline(*this, m_epath);
    //
    //         if (bCertainlySyntathicallyDir)
    //         {
    //
    //            m_iDir = 1;
    //
    //         }
    //         else
    //         {
    //
    //            m_iDir = iDir;
    //
    //         }
    //
    //      }
    //
    //   }



    //   path::path(const atom & atom,e_path epath, int iDir) :
    //      path(string(atom), epath, iDir)
    //   {
    //
    //   }


    //   path::path(const ::payload & payload, e_path epath, int iDir) :
    //      path(payload.get_string(), epath, iDir)
    //   {
    //
    //
    //   }


    //   path::path(const path & path) :
    //      ::ansi_string((const string &)path),
    //      path_meta((path_meta &)path),
    //      path_os((path_os &) path)
    //   {
    //
    //   }


    //   path::path(path && path) :
    //      string(::transfer(path)),
    //      path_meta((path_meta &) path),
    //      path_os(::transfer(path))
    //   {
    //
    //   }


    //   path::path(const ::scoped_string & scopedstr, e_path epath, int iDir):
    //      path(string(psz), epath, iDir)
    //   {
    //
    //   }

    //   path::path(const unichar * psz, e_path epath, int iDir) :
    //      path(string(psz), epath, iDir)
    //   {
    //
    //   }


    //   path::path(const wstring & wstr, e_path epath, int iDir):
    //      path(string(wstr), epath, iDir)
    //   {
    //
    //   }

    inline path::~path() noexcept
    {


    }


    //   bool path::is_equal(const path & path) const
    //   {
    //
    //
    //#ifdef WINDOWS
    //
    //      if (((const string &)*this).case_insensitive_order((const string &)path) == 0) // undoubtely eaqual...
    //         return true;
    //
    //#else
    //
    //      if (((const string &)*this).operator == ((const string &)path)) // undoubtely eaqual...
    //         return true;
    //
    //#endif
    //
    //      return false;
    //
    //      // find extend equalitys..
    //
    //      ::file::path_array patha1;
    //
    //      split(patha1);
    //
    //      ::file::path_array patha2;
    //
    //      path.split(patha2);
    //
    //      if(patha1.get_size() == patha2.get_size())
    //      {
    //
    //         for(index i = 0; i < patha1.get_size(); i++)
    //         {
    //
    //            if(patha1[i].::ansi_string::operator!=(patha2[i]))
    //            {
    //
    //               goto there_s_difference_in_this_step_1;
    //
    //            }
    //
    //         }
    //
    //         return true;
    //
    //      }
    //
    //      there_s_difference_in_this_step_1:
    //
    //
    //      return false;
    //
    //   }


    //inline void path::split(string_array& patha) const
    //{

    //   ascendants_name(patha);

    //}




    //inline string path::name(index i) const
    //{


    //   string_array patha;

    //   ascendants_name(patha);

    //   if (i < 0)
    //   {

    //      i += patha.get_size();

    //   }


    //   if (i < 0)
    //   {

    //      return "";

    //   }

    //   if (i >= patha.get_size())
    //   {

    //      return "";

    //   }

    //   return patha[i];

    //}


    //inline string_array& path::ascendants_name(string_array& straParam) const
    //{

    //   string strPath = *this;

    //   if (strPath == "/")
    //   {

    //      straParam.add("/");

    //      return straParam;

    //   }

    //   strsize iFirstColon = find(':');
    //   strsize iFirstSlash = find('/');
    //   strsize iSecondSlash = find('/', iFirstSlash + 1);

    //   if (iFirstColon > 0 && iFirstSlash == iFirstColon + 1 && iSecondSlash == iFirstSlash + 1)
    //   {

    //      ::file::path path = Left(iSecondSlash + 1);

    //      straParam.add(path);

    //      strPath = Mid(iSecondSlash + 1);

    //   }

    //   bool bWin1 = strPath.begins_eat("\\\\?\\");

    //   auto pFind = 0;
    //   while (true)
    //   {

    //      index iFind1 = strPath.find('/', iFind);
    //      index iFind2 = strPath.find('\\', iFind);
    //      index iFind3 = minimum_non_negative(iFind1, iFind2);
    //      if (iFind3 < 0)
    //      {
    //         string str = strPath(pFind);
    //         straParam.add(str);
    //         break;
    //      }
    //      string str = strPath.substr(iFind, iFind3 - iFind);
    //      straParam.add(str);
    //      iFind = iFind3 + 1;
    //   }


    //   if (bWin1)
    //   {
    //      straParam[0] = "\\\\?\\" + straParam[0];
    //   }
    //   else if (this->case_insensitive_begins("/"))
    //   {
    //      straParam[0] = "/" + straParam[0];
    //   }
    //   else if (this->case_insensitive_begins("\\\\"))
    //   {
    //      straParam[0] = "\\\\" + straParam[0];
    //   }

    //   return straParam;

    //}


    inline path path::folder(int i) const
    {

       ::file::path path(*this);

       while (i > 0)
       {

          path = path.folder();

          i--;

       }

       return path;

    }


    inline path& path::ascend()
    {

       return *this = parent();

    }


    inline path& path::ascend(int i)
    {

       while (i > 0)
       {

          ascend();

          i--;

       }

       return *this;

    }


//   inline path& path::operator += (const path& path)
//   {
//
//      string str = path;
//
//      str.trim_left("\\/");
//
//      string::operator += (str);
//
//      return *this;
//
//   }


    //inline path& path::operator += (const ::const_ansi_range & range)
    //{

    //   string str(range);

    //   str.trim_left("\\/");

    //   string strThis = *this;

    //   string ::operator = (file_path_normalize(strThis + str, m_epath));

    //   return *this;

    //}


    inline path & path::operator += (const ::string & str)
    {

       auto pathThis = *this;

       ::string::operator = (file_path_normalize(pathThis + str, this->m_epath));

       return *this;

    }



    //   path_array path::operator / (const string_array & stra) const
    //   {
    //
    //      path_array patha;
    //
    //      for (auto str : stra)
    //      {
    //
    //         patha.add(*this / str);
    //
    //      }
    //
    //      return patha;
    //
    //   }




//   inline path path::operator / (const ::ansi_string& str) const
//   {
//
//      return operator /(::file::path(str));
//
//   }
//

    //template < primitive_atom ATOM >
    //inline path path::operator / (const ATOM & atom) const
    //{

    //   return operator /(::file::path(atom));

    //}


//   inline path path::operator / (const ::scoped_string & scopedstr) const
//   {
//
//      return slashed_path(scopedstr);
//
//   }

//   inline path& path::operator /= (const path& path)
//   {
//
//      string strPath;
//
//      strPath = string(*this);
//
//      string str = path;
//
//      if (strPath.right(3) == "://")
//      {
//
//         return operator = (::file::path(strPath + str, m_epath));
//
//      }
//
//      if (strPath.is_empty())
//      {
//
//         strPath = separator();
//
//      }
//      else if (strPath.size() == 1 && strPath[0] == separator())
//      {
//
//      }
//      else
//      {
//
//         strPath += separator();
//
//         str.trim_left("\\/");
//
//      }
//
//      return operator = (::file::path(strPath + str, m_epath));
//
//   }


//   inline path& path::operator /= (const ::ansi_string& str)
//   {
//
//      return operator /=(::file::path(str));
//
//   }
//
//
//   inline path & path::operator /= (const ::inline_number_string & inlinenumberstring)
//   {
//
//      return operator /=(::file::path(::string(inlinenumberstring)));
//
//   }
//
//
//   inline path& path::operator /= (const ::atom & atom)
//   {
//
//      return operator /=(::file::path(atom));
//
//   }




    //::file::path path::replace_extension(const ::scoped_string & scopedstrNewExtension, const ::scoped_string & scopedstrOldExtension)
    //{

    //   string strNewExtension(pszNewExtension);

    //   strNewExtension.case_insensitive_begins_eat(".");

    //   string strOldExtension(pszOldExtension);

    //   strOldExtension.case_insensitive_begins_eat(".");

    //   ::file::path path(*this);

    //   path.case_insensitive_ends_eat(strOldExtension);

    //   path += strNewExtension;

    //   return path;

    //}


    inline void path::set_all_extensions(const ::ansi_string& strNewExtension)
    {

       string strExtension(strNewExtension);

       strExtension.case_insensitive_begins_eat(".");

       auto range = find_all_extensions();

       if (range.begin() >= this->begin() + 1)
       {

          this->operator = ((*this)(0, range.begin()) + strExtension);

       }
       else
       {

          this->operator += ("." + strExtension);

       }

    }


    inline void path::set_final_extension(const ::ansi_string& strNewExtension)
    {

       string strExtension(strNewExtension);

       strExtension.case_insensitive_begins_eat(".");

       auto range = find_final_extension();

       if (range.begin() >= this->begin() + 1)
       {

          this->operator = ((*this)(0, range.begin()) + strExtension);

       }
       else
       {

          this->operator += ("." + strExtension);

       }

    }


    inline ::file::path path::with_all_extensions(const ::ansi_string& strNewExtension) const
    {

       ::file::path path(*this);

       path.set_all_extensions(strNewExtension);

       return ::transfer(path);

    }


    inline ::file::path path::with_final_extension(const ::ansi_string& strNewExtension) const
    {

       ::file::path path(*this);

       path.set_final_extension(strNewExtension);

       return ::transfer(path);

    }


    inline void path::set_type(enum_path epath)
    {

       if (epath != m_epath)
       {

          m_epath = epath;

          ::ansi_string ::operator = (file_path_normalize(*this, m_epath));

       }

    }





    inline path& path::operator = (const ::file::path& path)
    {

       if (&path != this)
       {

          string::operator  = ((const string&)path);
          *((path_meta*)this) = (const path_meta&)path;
          //#ifdef WINDOWS_DESKTOP
          //         m_idlist = path.m_idlist;
          //#endif

       }

       return *this;


    }


//   inline path& path::operator = (const ::ansi_string& str)
//   {
//
//      *((path_meta*)this) = path_meta();
//
//      m_epath = file_path_get_type(str);
//
//      string ::operator  = (file_path_normalize(str, m_epath));
//
//      return *this;
//
//   }


    //inline path path::operator + (const path& path) const
    //{

    //   return ::file::path((const string&)*this + string((const string&)path), m_epath);

    //}


    //inline path path::operator + (const ::ansi_string& str) const
    //{

    //   return ::file::path((const string&)*this + (m_iDir > 0 ? separator_sz() : "") + string((const string&)str), m_epath);

    //}


    //inline path path::operator + (const ::scoped_string & scopedstr) const
    //{

    //   return operator + (string(psz));

    //}



//   inline path& path::operator = (const ::scoped_string & scopedstr)
//   {
//
//      return operator = (string(psz));
//
//   }


    //inline path& path::operator += (const ::scoped_string & scopedstr)
    //{

    //   return operator += (string(psz));

    //}

//   inline path& path::operator = (const wstring& wstr)
//   {
//
//      return operator = (string(wstr));
//
//   }

    //inline path& path::operator += (const wstring& wstr) { return operator += (string(wstr)); }

    ////inline path& path::operator = (const ::wide_character* psz) { return operator = (wstring(psz)); }
    //inline path& path::operator += (const ::wide_character* psz) { return operator += (wstring(psz)); }

    //void path::to_string(string & str) const
    //{
    //
    //   str = *this;

    //}

    inline path path::operator * (const path& path) const
    {

       return sibling(path);

    }

    inline path path::operator * (const ::ansi_string& str) const { return operator * (::file::path(str)); }

    inline path& path::operator *= (const path& path)
    {

       if (this != &path)
       {

          *this = sibling(path);

       }

       return *this;

    }

    inline path& path::operator *= (const ::ansi_string& str) { return operator *= (::file::path(str)); }


    inline ::file::path path::title() const
    {

       return ::file_path_title(c_str());

    }


    inline string path::name() const
    {

       return ::file_path_name(c_str());

    }


    inline path::const_iterator path::find_name() const
    {

       return maximum(this->begin(), rear_find(separator()) + 1);

    }


    inline ::scoped_string path::find_final_extension() const
    {

       return ::file_path_final_extension(*this);

    }


    inline ::scoped_string path::find_all_extensions() const
    {

       return file_path_all_extensions(*this);

    }


    inline bool path::is_relative()
    {

       return file_path_is_relative(*this) != false;

    }


    inline path path::relative() const
    {

       return substr(maximum(0, m_iBasePathLength));

    }


    inline path path::parent() const
    {

       return folder();

    }


    inline path path::ascendant(int i) const
    {

       return folder(i);

    }


    inline path& path::operator -= (int i)
    {

       return ascend(i);

    }


    inline bool path::is_empty() const
    {

       return ::ansi_string::is_empty();

    }


    inline bool path::has_char() const
    {

       return !is_empty();

    }


    inline bool path::operator == (const ::string & str) const
    {

       return operator == (path(str));

    }


    inline bool path::operator != (const ::ansi_string& str) const
    {

       return operator != (path(str));

    }


    inline path path::operator / (const ::scoped_string & scopedstr) const
    {

       return ::transfer(slashed_path(scopedstr));

    }


    inline ::file::path & path::patch_base_path(const ::file::path & pathBase)
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


    inline bool path::operator != (const path & path) const
    {

       return !operator==(path);

    }




} // namespace file


//inline ::file::path operator+(const ::file::path & path1, const ::file::path & path2)
//{
//
//   return ::transfer(::file::path(((const::string &)path1) + ((const ::string&)path2)));
//
//}


// For MSVC, but not for GCC?
//inline ::file::path operator+(const ::file::path & path, const ::string & str)
//{
//
//   return ((const::string &)path) + str;
//}


//inline ::file::path operator+ (const ::file::path & path, const ::scoped_string & scopedstr)
//{
//
//   return ((const::string &)path) + scopedstr;
//}


//inline ::file::path operator+ (const ::file::path & path, const ::atom & atom)
//{
//
//   return ((const::string &)path) + atom;
//
//}
//
//
//inline ::file::path operator+(const ::file::path & path, const ::file::path::RANGE & range)
//{
//
//   return ((const::string &)path) + ::string(range);
//
//}



//template < strsize m_sizeMaximumLength >
//inline ::file::path operator +(const ::file::path & path, const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
//{
//
//   return ((const ::string &)path) + ::string(inlinestring);
//
//}
//
//
//template < strsize c >
//inline ::file::path operator +(const ::file::path & path, const ::ansi_character(&cha)[c])
//{
//
//   return ((const ::string &)path) + ::string(cha);
//
//}
//
//
//inline ::file::path operator+(const ::string & str, const ::file::path & path)
//{
//
//   return str + ((const::string &)path);
//}
//
//
//inline ::file::path operator+(const ::const_ansi_range & range, const ::file::path & path)
//{
//
//   return ::string(range) + ((const::string &)path);
//
//}
//
//
//
//template < ::count c >
//inline ::file::path operator +(const char(&sz)[c], const ::file::path & path)
//{
//
//   return ::string(sz) + ((const::string &)path);
//
//}


//namespace file
//{
//
//    //   inline path::path(const ::payload & payload,e_path epath): path(payload.get_file_path(),epath){}
//    //   inline path::path(const property & property,e_path epath, int iDir): path(property.get_file_path(),epath, iDir) {}
//    //inline path & path::operator = (const ::payload & payload) { return operator = (payload.get_string()); }
//    //inline path & path::operator += (const ::payload & payload) { return operator += (payload.get_string()); }
//    //inline path & path::operator = (const property & property) { return operator = ((const ::payload &)property); }
//    //inline path & path::operator += (const property & property) { return operator += ((const ::payload &) property); }
//    //inline path path::operator + (const ::payload & payload) const { return operator + (payload.get_string()); }
//    //inline path path::operator + (const property & property) const { return operator + (property.get_string()); }
//    //inline path path::operator + (const atom & atom) const { return operator + (atom.str()); }
//    //inline path path::operator / (const ::payload & payload) const { return operator /(::file::path(payload)); }
//    //inline path path::operator / (const property & property) const { return operator /(::file::path(property)); }
//    //inline path path::operator * (const property & property) const { return operator *(::file::path(property)); }
//    //inline path & path::operator *= (const property & property) { return operator *=(::file::path(property)); }
//    inline path path::folder() const { return { ::file_path_folder(*this), m_epath }; }
//    inline path path::sibling(const path & path) const { return { ::file_path_folder(*this) + ::string(this->separator()) + ::string(::sz::trim_left_path_sep(path)), m_epath }; }
//    inline path path::sibling(const ::string & str) const { return { ::file_path_folder(*this) + ::string(this->separator()) + ::string(::sz::trim_left_path_sep(str)), m_epath }; }
//    //inline path path::sibling(const ::string & psz) const { return { ::file_path_folder(*this) + sep() + ::sz::trim_left_path_sep(psz), m_epath }; }
//    //inline string path::extension() const { return &m_pdata[find_skip_or_length('.', rear_find(sep()) + 1)]; }
//    inline string path::final_extension() const { return file_path_final_extension(operator const char * ()); }
//    //inline patha path::ascendants_path() const { patha patha; return ascendants_path(patha); }
//    //inline string_array path::ascendants_name() const { string_array patha; return ascendants_name(patha); }
//    //   inline path path::folder() const { return ::file_path_folder(*this); }
//    //inline bool path::operator == (const ::payload & payload) const { return operator == (string(payload)); }
//    //inline bool path::operator != (const ::payload & payload) const { return operator != (string(payload)); }
//
//} // namespace file
//


