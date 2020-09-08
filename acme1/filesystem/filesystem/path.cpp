#include "framework.h"


CLASS_DECL_ACME string url_decode(const ::string & str);

CLASS_DECL_ACME::file::path __node_full_file_path(file::path path);

CLASS_DECL_ACME ::file::path node_full_file_path(file::path path)
{

   ::file::path pathFull = __node_full_file_path(path);

   if (pathFull.is_empty())
   {

      return path;

   }

   return pathFull;

}


namespace file
{


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


//   path::path(const unichar * pwsz, strsize iCount, e_path epath, int iDir, bool bNormalizePath, i64 iSize) :
//      string(pwsz, iCount),
//      path_meta(epath, iSize, iDir)
//   {
//
//      if (m_epath == path_none)
//      {
//
//         m_epath = get_path_type(*this, epath);
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

   path::path(const string & str, e_path epath, int iDir, bool bNormalizePath, i64 iSize) :
      string(str)
   {

      m_iSize = iSize;

      if (epath == path_none)
      {

         m_epath = get_path_type(str, epath);

      }
      else
      {

         m_epath = epath;

      }

      if (bNormalizePath)
      {

         bool bCertainlySyntathicallyDir = normalize_path_inline(*this, m_epath);

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


//   path::path(const id & id,e_path epath, int iDir) :
//      path(string(id), epath, iDir)
//   {
//
//   }


//   path::path(const var & var, e_path epath, int iDir) :
//      path(var.get_string(), epath, iDir)
//   {
//
//
//   }


//   path::path(const path & path) :
//      ::string((const string &)path),
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
//      ::file::patha patha1;
//
//      split(patha1);
//
//      ::file::patha patha2;
//
//      path.split(patha2);
//
//      if(patha1.get_size() == patha2.get_size())
//      {
//
//         for(index i = 0; i < patha1.get_size(); i++)
//         {
//
//            if(patha1[i].::string::operator!=(patha2[i]))
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


   patha & path::ascendants_path(patha & straParam, patha * ppathaRelative) const
   {

      string_array stra;

      ascendants_name(stra);

      ::file::path str;

      if(stra.get_count() > 0)
      {
         str = stra[0];
         straParam.add(str);
         if(ppathaRelative != nullptr)
         {
            ppathaRelative->add(::file::path(stra.slice(1).implode("/")));
         }
      }

      for(i32 i = 1; i < stra.get_size(); i++)
      {
         str /= stra[i];
         straParam.add(str);
         if(ppathaRelative != nullptr)
         {
            ppathaRelative->add(::file::path(stra.slice(i+1).implode("/")));
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

      if(strPath == "/")
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

      bool bWin1 = ::str::begins_eat_ci(strPath, "\\\\?\\");

      index iFind = 0;
      while (true)
      {

         index iFind1 = strPath.find('/', iFind);
         index iFind2 = strPath.find('\\', iFind);
         index iFind3 = min_non_neg(iFind1, iFind2);
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
      else if(strPath.begins_ci("/"))
      {
         straParam[0] = "/" + straParam[0];
      }
      else if(strPath.begins_ci("\\\\"))
      {
         straParam[0] = "\\\\" + straParam[0];
      }

      return straParam;

   }


   path path::folder(int i) const
   {

      ::file::path path(*this);

      while(i > 0)
      {

         path = path.folder();

         i--;

      }

      return path;

   }


   path & path::go_up()
   {

      return *this = folder();

   }


   path & path::go_up(int i)
   {

      while(i > 0)
      {

         go_up();

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

   path & path::operator += (const string & strParam)
   {

      string str = strParam;

      str.trim_left("\\/");

      string strThis = *this;

      string ::operator = (normalize_path(strThis + str, m_epath));

      return *this;

   }


   patha path::operator / (const string_array & stra) const
   {

      patha patha;

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

      if (m_epath == path_url || strPath.Right(3) == "://")
      {

         str.replace("\\", "/");

         str.trim_left("/");

         return ::file::path(strPath + "/" + str, m_epath, path.m_iDir);

      }

      strPath += sep();

      str.trim_left("\\/");

      return ::file::path(strPath + str, m_epath, path.m_iDir);

   }


   path path::operator / (const string & str) const
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

      if(strPath.is_empty())
      {

         strPath = sep();

      }
      else if(strPath.get_length() == 1 && strPath[0] == sep())
      {

      }
      else
      {

         strPath += sep();

         str.trim_left("\\/");

      }

      return operator = (::file::path(strPath + str, m_epath));

   }

   path & path::operator /= (const string & str)
   {

      return operator /=(::file::path(str));

   }

   path & path::operator /= (const char * psz)
   {

      return operator /=(::file::path(psz));

   }


   ::file::path path::replace_file_extension(const char * pszNewExtension, const char * pszOldExtension)
   {

      string strNewExtension(pszNewExtension);

      ::str::begins_eat_ci(strNewExtension, ".");

      string strOldExtension(pszOldExtension);

      ::str::begins_eat_ci(strOldExtension, ".");

      ::file::path path(*this);

      ::str::ends_eat_ci(path, strOldExtension);

      path += strNewExtension;

      return path;

   }


   ::file::path path::replace_file_extension(const char * pszNewExtension)
   {

      string strNewExtension(pszNewExtension);

      ::str::begins_eat_ci(strNewExtension, ".");

      ::file::path pathFolder = folder();

      string strTitle = title();

      string strName = strTitle + "." + strNewExtension;

      return pathFolder / strName;

   }


   void path::set_type(e_path epath)
   {

      if(epath != m_epath)
      {

         m_epath = epath;

         ::string ::operator = (normalize_path(*this, m_epath));

      }

   }





   path & path::operator = (const ::file::path & path)
   {

      if(&path != this)
      {

         string::operator  = ((const string &) path);
         *((path_meta *)this) = (const path_meta &)path;
#ifdef WINDOWS_DESKTOP
         m_idlist = path.m_idlist;
#endif

      }

      return *this;


   }


   path & path::operator = (const string & str)
   {

      *((path_meta*)this) = path_meta();

      m_epath = get_path_type(str);

      string ::operator  = (normalize_path(str, m_epath));

      return *this;

   }


   path path::operator + (const path & path) const
   {

      return ::file::path((const string &)*this  + string((const string &)path), m_epath);

   }


   path path::operator + (const string & str) const
   {

      return ::file::path((const string &)*this + (m_iDir > 0 ? string(sep()) : "" ) + string((const string &)str),m_epath);

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

   void path::to_string(string & str) const
   {
      str = *this;
   }

   path path::operator * (const path & path) const
   {

      return sibling(path);

   }

   path path::operator * (const string & str) const { return operator * (::file::path(str)); }
   path path::operator * (const char * psz) const { return operator * (::file::path(psz)); }

   path & path::operator *= (const path & path)
   {

      if(this != &path)
      {

         *this = sibling(path);

      }

      return *this;

   }

   path & path::operator *= (const string & str) { return operator *= (::file::path(str)); }
   path & path::operator *= (const char * psz) { return operator *= (::file::path(psz)); }


   ::file::path path::title() const
   {

      return ::file_title_dup(operator const char*());

   }


   string path::name() const
   {

      return ::file_name_dup(operator const char*());

   }


   //void path::calc_name() const
   //{
   //   m_iName = find_file_name();
   //   m_strName = Mid(m_iName);
   //}





   index path::find_file_name() const
   {
      return MAX(0, reverse_find(sep()) + 1);
   }

   string path::ext() const
   {
      return extension();
   }

   bool path::is_relative()
   {
      return file_path_is_relative_dup(*this) != FALSE;
   }

   path path::relative() const
   {

      return Mid(MAX(0,m_iRelative));

   }


   path path::up() const
   {

      return folder();

   }


   path path::up(int i) const
   {

      return folder(i);

   }


   path & path::operator -= (int i)
   {

      return go_up(i);

   }





   e_path get_path_type(const string & str, e_path epathForce)
   {

      if(epathForce != path_none)
      {

         return epathForce;

      }
      else if (str.begins_ci("data:"))
      {

         return path_data;

      }
      else if(is_url_dup(str))
      {

         return path_url;

      }
      else
      {

         return path_file;

      }

   }

   string normalize_path(string strPath, e_path epath)
   {

      normalize_path_inline(strPath, epath);

      return strPath;

   }

   bool normalize_path_inline(string & strPath, e_path & epath)
   {

      bool bUrl;

      bool bOnlyNativeFileSep;

      strsize iaSlash[512];

      int iSlashCount;

      if (epath == path_data)
      {

         return true;

      }

#ifdef WINDOWS

      if (strPath.get_length() > 3
            && strPath[2] == ':'
            && ::str::begins_eat(strPath, "/"))
      {

         //strPath = strPath.Mid(1);

      }

#endif

      bool bCertainlySyntathicallyDir = solve_relative_inline(strPath, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

      if(bUrl && strPath.begins_ci("file:///"))
      {

         bUrl = false;

         //strPath = ::file::path(::get_context_system()->url().url_decode(strPath.Mid(7)));
         strPath = ::file::path(url_decode(strPath.Mid(7)));

         return bCertainlySyntathicallyDir;

      }

      if(bUrl)
      {

         epath = path_url;

         strPath.replace("\\", "/");

      }
      else
      {

         epath = path_file;

      }

#ifdef WINDOWS
      if(!bOnlyNativeFileSep && epath == path_file)
#else
      if(!bOnlyNativeFileSep)
#endif
      {

#ifdef WINDOWS
         if(strPath == "\\\\" || strPath == "\\")
         {

         }
         else
#endif
            if (strPath.has_char())
            {

               char * psz = strPath.get_string_buffer();

               char chSep = path_sep(epath);

               for(int i = 0; i < iSlashCount; i++)
               {

                  psz[iaSlash[i]] = chSep;

               }

               strPath.release_string_buffer();

            }

      }

      return bCertainlySyntathicallyDir;

   }


   CLASS_DECL_ACME bool begins_eat_ci(string & str, const char * pcszPrefix)

   {

      ::file::path path(pcszPrefix);


      if (path.is_empty())
      {

         return true;

      }

      if (str.is_empty())
      {

         return false;

      }


      string strPath;

      strPath = path;

      if(is_url_dup(strPath))
      {

         strPath += "/";

      }
      else
      {

         strPath += path_sep(path_file);

      }

      if(str == path || str == strPath)
      {

         str.Empty();

         return true;

      }
      else if(::str::begins_eat_ci(str, strPath))
      {

         return true;

      }
      else
      {

         string strFull;

         strFull = node_full_file_path(str);

         string strFullPath;

         strFullPath = node_full_file_path(strPath);

         if(::str::begins_eat_ci(strFull, strFullPath))
         {

            str = strFull;

            return true;

         }

      }

      return false;

   }

   bool path::is_empty() const
   {

      return ::string::is_empty()

#ifdef WINDOWS_DESKTOP

             && m_idlist.is_empty();
#else
             ;

#endif

   }


   bool path::has_char() const
   {

      return !is_empty();

   }



} // namespace file



