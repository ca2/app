//
// Created by camilo on 23/12/22.
//
#pragma once


#include "acme/filesystem/filesystem/windows_path.h"


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

      bool bJustAfterProtocol1 = this->ends(":/");

      bool bJustAfterProtocol2 = this->ends("://");

      if (bJustAfterProtocol1 || bJustAfterProtocol2 || m_epath == e_path_url)
      {

         ::string str = scopedstr;

         str.find_replace("\\", "/");

         str.trim_left("/");

         if (bJustAfterProtocol2)
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


   inline path_meta::path_meta(enum_path epath, long long iSize, e_type etype, long long iName, character_count iBasePathLength, enumeration < ::file::enum_flag > eflag)
   {

      m_epath = epath;
      m_iSize = iSize;
      m_etype = etype;
      m_iName = (character_count)iName;
      m_iBasePathLength = iBasePathLength;
      m_flags = eflag;

   }


   //template < typename ITERATOR_TYPE, int t_size >
   //inline path::path(const const_string_range_static_array < ITERATOR_TYPE, t_size >& a, enum_path epath, e_type etype, bool bNormalize, long long iSize) :
   //   path((const ::ansi_string&)a, epath, etype, bNormalize, iSize)
   //{


   //}




   //inline path::path(const ::wd16_string & wd16str, enum_path epath, e_type etype, bool bNormalizePath, long long iSize) :
   //   path(::string(wd16str), epath, etype, bNormalizePath, iSize)
   //{


   //}


   //template < typename ITERATOR_TYPE >
   //inline path::path(const ::range < ITERATOR_TYPE > & range, enum_path epath, e_type etype, bool bNormalizePath, long long iSize) :
   //   path(::string(range), epath, etype, bNormalizePath, iSize)
   //{


   //}


   //inline path::path(const ::ansi_character * pansisz, enum_path epath, e_type etype, bool bNormalizePath, long long iSize) :
   //   path(::ansi_string(pansisz), epath, etype, bNormalizePath, iSize)
   //{


   //}


   //inline path::path(const ::wd16_character * pwd16sz, enum_path epath, e_type etype, bool bNormalizePath, long long iSize) :
   //   path(::string(pwd16sz), epath, etype, bNormalizePath, iSize)
   //{


   //}


   //inline path::path(const ::wd32_character * pwd32sz, enum_path epath, e_type etype, bool bNormalizePath, long long iSize) :
   //   path(::string(pwd32sz), epath, etype, bNormalizePath, iSize)
   //{


   //}


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


   //   path::path(const unichar * pwsz, character_count iCount, e_path epath, e_type etype, bool bNormalizePath, long long iSize) :
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



   //   path::path(const atom & atom,e_path epath, e_type etype) :
   //      path(string(atom), epath, iDir)
   //   {
   //
   //   }


   //   path::path(const ::payload & payload, e_path epath, e_type etype) :
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


   //   path::path(const ::scoped_string & scopedstr, e_path epath, e_type etype):
   //      path(string(psz), epath, iDir)
   //   {
   //
   //   }

   //   path::path(const unichar * psz, e_path epath, e_type etype) :
   //      path(string(psz), epath, iDir)
   //   {
   //
   //   }


   //   path::path(const wstring & wstr, e_path epath, e_type etype):
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
   //         for(::collection::index i = 0; i < patha1.get_size(); i++)
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




   //inline string path::name(::collection::index i) const
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

   //   character_count iFirstColon = find(':');
   //   character_count iFirstSlash = find('/');
   //   character_count iSecondSlash = find('/', iFirstSlash + 1);

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


   inline path & path::ascend()
   {

      return *this = parent();

   }


   inline path & path::ascend(int i)
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

      ::string::operator = (file_path_normalize(((const ::string &)pathThis) + str, this->m_epath));

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


   // inline path path::operator / (const ::atom & atom)
   // {
   //
   //    return operator /(::file::path(atom));
   //
   // }




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


   inline void path::set_all_extensions(const ::scoped_string & scopedstrExtension)
   {

      string strExtension(scopedstrExtension);

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


   inline void path::set_final_extension(const ::scoped_string & scopedstrExtension)
   {

      string strExtension(scopedstrExtension);

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


   inline void path::set_extension_if_no_extension(const ::scoped_string & scopedstrExtension)
   {

      if (this->final_extension().is_empty())
      {

         auto p = scopedstrExtension.skip('.');

         if (::has_character(p))
         {

            this->operator = (((::ansi_string &)*this) + "." + scopedstrExtension(p));

         }

      }

   }


   inline void path::defer_set_extension(const ::scoped_string& scopedstrExtension)
   {

      ::string str(*this);

      str.case_insensitive_ends_eat("." + scopedstrExtension);

      str += "." + scopedstrExtension;

      this->operator =(str);

   }


   inline ::file::path path::with_all_extensions(const ::scoped_string & scopedstrExtension) const
   {

      ::file::path path(*this);

      path.set_all_extensions(scopedstrExtension);

      return ::transfer(path);

   }


   inline ::file::path path::with_final_extension(const ::scoped_string & scopedstrExtension) const
   {

      ::file::path path(*this);

      path.set_final_extension(scopedstrExtension);

      return ::transfer(path);

   }


   inline ::file::path path::with_extension_if_no_extension(const ::scoped_string & scopedstrExtension) const
   {

      ::file::path path(*this);

      path.set_extension_if_no_extension(scopedstrExtension);

      return ::transfer(path);

   }


   inline ::file::path path::with_deferred_extension(const ::scoped_string& scopedstrExtension) const
   {

      ::file::path path(*this);

      path.defer_set_extension(scopedstrExtension);

      return ::transfer(path);

   }


   inline ::windows_path path::windows_path() const
   {

      return *this;

   }


   inline void path::set_type(enum_path epath)
   {

      if (epath != m_epath)
      {

         m_epath = epath;

         ::ansi_string ::operator = (file_path_normalize(*this, m_epath));

      }

   }


   inline path & path::set_file_path(const ::scoped_string & scopedstrFile)
   {

      operator = (scopedstrFile);

      set_file_path();

      return *this;

   }


   inline path & path::set_folder_path(const ::scoped_string & scopedstrFolder)
   {

      operator = (scopedstrFolder);

      folder();

      return *this;

   }


   inline path & path::set_file_path()
   {

      m_etype = (enum_type) ((m_etype | e_type_file2) & ~e_type_folder2);

      return *this;

   }


   inline path & path::set_folder_path()
   {

      m_etype = (enum_type) ((m_etype | e_type_folder2) & ~e_type_file2);

      return *this;

   }


   inline path& path::set_existent_file()
   {

      set_file_path();

      set_existent();

      return *this;

   }


   inline path& path::set_existent()
   {

      m_etype = (enum_type)((m_etype | e_type_exists) & ~e_type_doesnt_exist);

      return *this;

   }


   inline path& path::set_existent_folder()
   {

      set_folder_path();

      set_existent();

      return *this;

   }


   inline path & path::operator = (const ::file::path & path)
   {

      if (&path != this)
      {

         string::operator  = ((const string &)path);
         *((path_meta *)this) = (const path_meta &)path;
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

//   inline path path::operator * (const path & path) const
//   {
//
//      return sibling(path);
//
//   }

//   inline path path::operator * (const ::ansi_string & str) const { return operator * (::file::path(str)); }
//
//   inline path & path::operator *= (const path & path)
//   {
//
//      if (this != &path)
//      {
//
//         *this = sibling(path);
//
//      }
//
//      return *this;
//
//   }
//
//   inline path & path::operator *= (const ::ansi_string & str) { return operator *= (::file::path(str)); }


   inline ::const_ansi_range path::title() const
   {

      auto rangeName = this->name();

      auto end = rangeName.find('.');

      if (::is_null(end))
      {

         return rangeName;

      }

      return rangeName(0, end);

   }


   inline ::const_ansi_range path::name() const
   {

      auto p = rear_find_first_character_in("\\/");

      if (::is_null(p))
      {

         return *this;

      }

      return { p + 1, this->end() };

   }


   inline path::const_iterator path::find_name() const
   {

      return maximum(this->begin(), rear_find('/') + 1);

   }


   inline ::const_ansi_range path::find_final_extension() const
   {

      auto rangeName = this->name();

      auto last_dot = rangeName.rear_find('.');

      if (!last_dot)
      {

         return {};

      }

      return { last_dot + 1, this->end() };

   }


   inline ::const_ansi_range path::find_all_extensions() const
   {

      auto rangeName = this->name();

      auto name_first_dot = rangeName.find('.');

      if (!name_first_dot)
      {

         return {};

      }

      return { name_first_dot + 1, this->end() };
   }


   inline bool path::is_relative()
   {

      return file_path_is_relative(*this) != false;

   }


   //inline path path::relative() const
   //{

   //   return this->substr(maximum(0, m_iBasePathLength));

   //}


   inline path path::parent() const
   {

      return folder();

   }


   inline path path::ascendant(int i) const
   {

      return folder(i);

   }


   inline path & path::operator -= (int i)
   {

      return ascend(i);

   }


   inline bool path::is_empty() const
   {

      return ::ansi_string::is_empty();

   }


   inline bool path::has_character() const
   {

      return !is_empty();

   }


   inline bool path::operator == (const ::string & str) const
   {

      return operator == (path(str));

   }


   inline bool path::operator != (const ::ansi_string & str) const
   {

      return operator != (path(str));

   }


   // inline path path::operator / (const ::scoped_string & scopedstr) const
   // {
   //
   //    return ::transfer(slashed_path(scopedstr));
   //
   // }


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


//inline ::file::path operator +(const ::file::path & path1, const ::file::path & path2)
//{
//
//   return ::transfer(::file::path(((const::string &)path1) + ((const ::string&)path2)));
//
//}


// For MSVC, but not for GCC?
//inline ::file::path operator +(const ::file::path & path, const ::string & str)
//{
//
//   return ((const::string &)path) + str;
//}


//inline ::file::path operator + (const ::file::path & path, const ::scoped_string & scopedstr)
//{
//
//   return ((const::string &)path) + scopedstr;
//}


//inline ::file::path operator + (const ::file::path & path, const ::atom & atom)
//{
//
//   return ((const::string &)path) + atom;
//
//}
//
//
//inline ::file::path operator +(const ::file::path & path, const ::file::path::RANGE & range)
//{
//
//   return ((const::string &)path) + ::string(range);
//
//}



//template < character_count m_sizeMaximumLength >
//inline ::file::path operator +(const ::file::path & path, const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
//{
//
//   return ((const ::string &)path) + ::string(inlinestring);
//
//}
//
//
//template < character_count c >
//inline ::file::path operator +(const ::file::path & path, const ::ansi_character(&cha)[c])
//{
//
//   return ((const ::string &)path) + ::string(cha);
//
//}
//
//
//inline ::file::path operator +(const ::string & str, const ::file::path & path)
//{
//
//   return str + ((const::string &)path);
//}
//
//
//inline ::file::path operator +(const ::const_ansi_range & range, const ::file::path & path)
//{
//
//   return ::string(range) + ((const::string &)path);
//
//}
//
//
//
//template < ::collection::count c >
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
//    //   inline path::path(const property & property,e_path epath, e_type etype): path(property.get_file_path(),epath, iDir) {}
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





//namespace url
//{
//
//
//   inline url::url(const ::file::path& path) :
//      url((const ::scoped_string &) (const ::string&)path)
//   {
//
//
//   }
//
//
//
//} //  namespace url




namespace file
{


   inline ::url::url path::as_url() const
   {

      if (::url::is(*this))
      {

         return (const ::scoped_string &)*this;

      }
      else
      {

         ::string str("file://");

         str += *this;

         return (const ::scoped_string&) str;

      }

   }


inline const_ansi_range path::_get_count_parts_from_beginning(::collection::count cPathPartCountToConsume) const
{
   
   return ::string::_get_count_parts_from_beginning(cPathPartCountToConsume, '/');

}


inline const_ansi_range path::get_count_parts_from_beginning(::collection::count cPathPartCountToConsume) const
{
   
   return ::string::_get_count_parts_from_beginning(cPathPartCountToConsume, '/');

}

// bool path::has_count_parts_from_beginning_eat(::collection::count cPathPartCountToConsume)
//{
//    
//    auto range = this->get_count_parts_from_beginning(cPathPartCountToConsume);
//    
//    if(::is_null(range.m_begin))
//    {
//       
//       return false;
//       
//    }
//
//    return this->_assign(range.m_begin, range.size());
//   
//}


} // namespace file





template < character_range RANGE1, character_range RANGE2 >
::file::path operator / (const RANGE1& range1, const RANGE2& range2)
{

   return ::transfer(::file::path(range1).slashed_path(range2));

}



template < character_pointer CHARACTER_POINTER, character_range RANGE >
::file::path operator / (CHARACTER_POINTER p, const RANGE& range)
{

   return ::transfer(::file::path(p) / ::string(range));

}




template < character_range RANGE, character_count n >
::file::path operator / (const typename RANGE::CHARACTER(&sz)[n], const RANGE& range)
{

   return ::transfer(::file::path(sz) / ::string(range));

}



template < primitive_character ITERATOR_TYPE2, int t_size, character_range RANGE >
::file::path operator / (const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a, const RANGE& range)
{

   return ::transfer(::file::path(a) / ::string(range));

}


template < character_range RANGE, character_pointer CHARACTER_POINTER >
::file::path operator / (const RANGE& range, CHARACTER_POINTER p)
{

   return ::transfer(::file::path(range) / ::file::path(p));

}


template < character_range RANGE, typename ITERATOR_TYPE2, int t_size >
::file::path operator / (const RANGE& range, const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a)
{

   return ::transfer(::file::path(range) / ::file::path(a));

}


template < typename ITERATOR_TYPE2, character_count n, int t_size >
::file::path operator / (const ::erase_pointer < non_const <ITERATOR_TYPE2>>(&sz)[n], const const_string_range_static_array <ITERATOR_TYPE2, t_size >& a)
{

   return ::transfer(::file::path(sz) / ::string(a));

}


