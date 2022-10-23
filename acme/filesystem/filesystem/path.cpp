// Created some path constructors by camilo on 2022-10-09 03:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "path.h"
#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/collection/numeric_array.h"


CLASS_DECL_ACME string url_decode(const string & str);

//CLASS_DECL_ACME::file::path __xxxnode_full_file_path(file::path path);



namespace file
{


   path::path(const ::payload & payload) :
      path(payload.file_path())
   {


   }


   path::path(const ::property & property) :
      path(property.file_path())
   {


   }


   path::path(const ::atom & atom) :
      path(atom.string())
   {


   }

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

   path::path(const path & path) :
      string((const string &)path),
      path_meta(path)
   {

   }


   path::path(const path_object & path) :
      ::file::path((const ::file::path &)path)
   {

   }


   path::path(const ::ansistring & str, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
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
   //      ::ansistring((const string &)path),
   //      path_meta((path_meta &)path),
   //      path_os((path_os &) path)
   //   {
   //
   //   }


   //   path::path(path && path) :
   //      string(::move(path)),
   //      path_meta((path_meta &) path),
   //      path_os(::move(path))
   //   {
   //
   //   }


   //   path::path(const char * psz, e_path epath, int iDir):
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

   path::~path() noexcept
   {


   }


   //   bool path::is_equal(const path & path) const
   //   {
   //
   //
   //#ifdef WINDOWS
   //
   //      if (((const string &)*this).compare_ci((const string &)path) == 0) // undoubtely eaqual...
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
   //            if(patha1[i].::ansistring::operator!=(patha2[i]))
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


   void path::split(string_array & patha) const
   {

      ascendants_name(patha);

   }


   path_array & path::ascendants_path(path_array & straParam, path_array * ppathaRelative) const
   {

      string_array stra;

      ascendants_name(stra);

      ::file::path str;

      if (stra.get_count() > 0)
      {
         str = stra[0];
         straParam.add(str);
         if (ppathaRelative != nullptr)
         {
            ppathaRelative->add(::file::path(stra.slice(1).implode("/")));
         }
      }

      for (i32 i = 1; i < stra.get_size(); i++)
      {
         str /= stra[i];
         straParam.add(str);
         if (ppathaRelative != nullptr)
         {
            ppathaRelative->add(::file::path(stra.slice(i + 1).implode("/")));
         }
      }

      return straParam;

   }


   string path::name(index i) const
   {

      string_array patha;

      ascendants_name(patha);

      if (i < 0)
      {

         i += patha.get_size();

      }


      if (i < 0)
      {

         return "";

      }

      if (i >= patha.get_size())
      {

         return "";

      }

      return patha[i];

   }


   string_array & path::ascendants_name(string_array & straParam) const
   {

      string strPath = *this;

      if (strPath == "/")
      {

         straParam.add("/");

         return straParam;

      }

      strsize iFirstColon = find(':');
      strsize iFirstSlash = find('/');
      strsize iSecondSlash = find('/', iFirstSlash + 1);

      if (iFirstColon > 0 && iFirstSlash == iFirstColon + 1 && iSecondSlash == iFirstSlash + 1)
      {

         ::file::path path = Left(iSecondSlash + 1);

         straParam.add(path);

         strPath = Mid(iSecondSlash + 1);

      }

      bool bWin1 = ::str().begins_eat_ci(strPath, "\\\\?\\");

      index iFind = 0;
      while (true)
      {

         index iFind1 = strPath.find('/', iFind);
         index iFind2 = strPath.find('\\', iFind);
         index iFind3 = minimum_non_negative(iFind1, iFind2);
         if (iFind3 < 0)
         {
            string str = strPath.Mid(iFind);
            straParam.add(str);
            break;
         }
         string str = strPath.Mid(iFind, iFind3 - iFind);
         straParam.add(str);
         iFind = iFind3 + 1;
      }


      if (bWin1)
      {
         straParam[0] = "\\\\?\\" + straParam[0];
      }
      else if (this->begins_ci("/"))
      {
         straParam[0] = "/" + straParam[0];
      }
      else if (this->begins_ci("\\\\"))
      {
         straParam[0] = "\\\\" + straParam[0];
      }

      return straParam;

   }


   path path::folder(int i) const
   {

      ::file::path path(*this);

      while (i > 0)
      {

         path = path.folder();

         i--;

      }

      return path;

   }


   path & path::ascend()
   {

      return *this = parent();

   }


   path & path::ascend(int i)
   {

      while (i > 0)
      {

         ascend();

         i--;

      }

      return *this;

   }


   path & path::operator += (const path & path)
   {

      string str = path;

      str.trim_left("\\/");

      string::operator += (str);

      return *this;

   }

   path & path::operator += (const ::ansistring & strParam)
   {

      string str = strParam;

      str.trim_left("\\/");

      string strThis = *this;

      string ::operator = (file_path_normalize(strThis + str, m_epath));

      return *this;

   }


   path_array path::operator / (const string_array & stra) const
   {

      path_array patha;

      for (auto str : stra)
      {

         patha.add(*this / str);

      }

      return patha;

   }


   path path::operator / (const path & path) const
   {

      string strPath;

      strPath = c_str();

      if (strPath.is_empty())
      {

         return path;

      }

      string str = path;

      bool bJustAfterProtocol = strPath.Right(3) == "://";

      if (bJustAfterProtocol || m_epath == e_path_url)
      {

         str.replace_with("/", "\\");

         //str.trim_left("/");

         if (bJustAfterProtocol)
         {

            return ::file::path(strPath + str, m_epath, path.m_iDir);

         }
         else
         {

            return ::file::path(strPath + "/" + str, m_epath, path.m_iDir);

         }

      }

      strPath += separator();

      str.trim_left("\\/");

      return ::file::path(strPath + str, m_epath, path.m_iDir);

   }


   path path::operator / (const ::ansistring & str) const
   {

      return operator /(::file::path(str));

   }


   path path::operator / (const char * psz) const
   {

      return operator /(::file::path(psz));

   }

   path & path::operator /= (const path & path)
   {

      string strPath;

      strPath = string(*this);

      string str = path;

      if (strPath.Right(3) == "://")
      {

         return operator = (::file::path(strPath + str, m_epath));

      }

      if (strPath.is_empty())
      {

         strPath = separator();

      }
      else if (strPath.get_length() == 1 && strPath[0] == separator())
      {

      }
      else
      {

         strPath += separator();

         str.trim_left("\\/");

      }

      return operator = (::file::path(strPath + str, m_epath));

   }

   path & path::operator /= (const ::ansistring & str)
   {

      return operator /=(::file::path(str));

   }

   path & path::operator /= (const char * psz)
   {

      return operator /=(::file::path(psz));

   }


   //::file::path path::replace_extension(const char * pszNewExtension, const char * pszOldExtension)
   //{

   //   string strNewExtension(pszNewExtension);

   //   ::str().begins_eat_ci(strNewExtension, ".");

   //   string strOldExtension(pszOldExtension);

   //   ::str().begins_eat_ci(strOldExtension, ".");

   //   ::file::path path(*this);

   //   ::str().ends_eat_ci(path, strOldExtension);

   //   path += strNewExtension;

   //   return path;

   //}


   void path::set_all_extensions(const ::ansistring & strNewExtension)
   {

      string strExtension(strNewExtension);

      strExtension.begins_eat_ci(".");

      auto iFind = find_all_extensions();

      if (iFind >= 1)
      {

         this->operator = (Left(iFind) + strExtension);

      }
      else
      {

         this->operator += ("." + strExtension);

      }

   }


   void path::set_final_extension(const ::ansistring & strNewExtension)
   {

      string strExtension(strNewExtension);

      strExtension.begins_eat_ci(".");

      auto iFind = find_final_extension();

      if (iFind >= 1)
      {

         this->operator = (Left(iFind) + strExtension);

      }
      else
      {

         this->operator += ("." + strExtension);

      }

   }


   ::file::path path::with_all_extensions(const ::ansistring & strNewExtension) const
   {

      ::file::path path(*this);

      path.set_all_extensions(strNewExtension);

      return ::move(path);

   }


   ::file::path path::with_final_extension(const ::ansistring & strNewExtension) const
   {

      ::file::path path(*this);

      path.set_final_extension(strNewExtension);

      return ::move(path);

   }


   void path::set_type(enum_path epath)
   {

      if (epath != m_epath)
      {

         m_epath = epath;

         ::ansistring ::operator = (file_path_normalize(*this, m_epath));

      }

   }





   path & path::operator = (const ::file::path & path)
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


   path & path::operator = (const ::ansistring & str)
   {

      *((path_meta *)this) = path_meta();

      m_epath = file_path_get_type(str);

      string ::operator  = (file_path_normalize(str, m_epath));

      return *this;

   }


   path path::operator + (const path & path) const
   {

      return ::file::path((const string &)*this + string((const string &)path), m_epath);

   }


   path path::operator + (const ::ansistring & str) const
   {

      return ::file::path((const string &)*this + (m_iDir > 0 ? separator_sz() : "") + string((const string &)str), m_epath);

   }


   path path::operator + (const char * psz) const
   {

      return operator + (string(psz));

   }



   path & path::operator = (const char * psz)
   {

      return operator = (string(psz));

   }


   path & path::operator += (const char * psz)
   {

      return operator += (string(psz));

   }

   path & path::operator = (const wstring & wstr)
   {

      return operator = (string(wstr));

   }

   path & path::operator += (const wstring & wstr) { return operator += (string(wstr)); }

   path & path::operator = (const widechar * psz) { return operator = (wstring(psz)); }
   path & path::operator += (const widechar * psz) { return operator += (wstring(psz)); }

   //void path::to_string(string & str) const
   //{
   //   
   //   str = *this;

   //}

   path path::operator * (const path & path) const
   {

      return sibling(path);

   }

   path path::operator * (const ::ansistring & str) const { return operator * (::file::path(str)); }
   path path::operator * (const char * psz) const { return operator * (::file::path(psz)); }

   path & path::operator *= (const path & path)
   {

      if (this != &path)
      {

         *this = sibling(path);

      }

      return *this;

   }

   path & path::operator *= (const ::ansistring & str) { return operator *= (::file::path(str)); }
   path & path::operator *= (const char * psz) { return operator *= (::file::path(psz)); }


   ::file::path path::title() const
   {

      return ::file_path_title(operator const char * ());

   }


   string path::name() const
   {

      return ::file_path_name(operator const char * ());

   }


   //void path::calc_name() const
   //{
   //   m_iName = find_file_name();
   //   m_strName = Mid(m_iName);
   //}





   index path::find_name() const
   {

      return maximum(0, reverse_find(separator()) + 1);

   }


   index path::find_final_extension() const
   {

      auto psz = file_path_final_extension(c_str());

      if (!psz)
      {

         return -1;

      }

      return psz - c_str() + 1;

   }


   index path::find_all_extensions() const
   {

      auto psz = file_path_all_extensions(c_str());

      if (!psz)
      {

         return -1;

      }

      return psz - c_str() + 1;

   }


   bool path::is_relative()
   {

      return file_path_is_relative(*this) != false;

   }


   path path::relative() const
   {

      return Mid(maximum(0, m_iBasePathLength));

   }


   path path::parent() const
   {

      return folder();

   }


   path path::ascendant(int i) const
   {

      return folder(i);

   }


   path & path::operator -= (int i)
   {

      return ascend(i);

   }


   bool path::is_empty() const
   {

      return ::ansistring::is_empty();

   }


   bool path::has_char() const
   {

      return !is_empty();

   }


   bool path::operator == (const ::ansistring & str) const
   {

      return operator == (path(str));

   }


   bool path::operator != (const ::ansistring & str) const
   {

      return operator != (path(str));

   }


} // namespace file



