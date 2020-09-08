#include "framework.h"


namespace zip
{

   class Util;

}


namespace file
{



      application_dir::application_dir()
      {
      }


      application_dir::~application_dir()
      {

      }


      //string_array application_dir::locale_schema_matter(string & strLocale, const string & strStyle)
      //{

      //   return get_context_application()->get_context_system()->m_spdir->locale_schema_matter(get_context_application(), strLocale, strStyle);

      //}


      //string_array application_dir::locale_schema_matter(string & strLocale, const string & strStyle, const string & pathRoot, const ::file::path & pathDomain)
      //{

      //   return get_context_application()->get_context_system()->m_spdir->locale_schema_matter(get_context_application(), strLocale, strStyle, pathRoot, pathDomain);

      //}


      string application_dir::matter(const ::file::patha & patha, bool bDir)
      {

         return get_context_application()->get_context_system()->m_spdir->matter(get_context_application(), patha, bDir);

      }


      string application_dir::matter(const ::file::path & path, bool bDir)
      {

         return get_context_application()->get_context_system()->m_spdir->matter(get_context_application(), path, bDir);

      }


      void application_dir::matter_ls(const ::file::path & str,::file::patha & stra)
      {
         get_context_application()->get_context_system()->m_spdir->matter_ls(get_context_application(), str, stra);
      }

      void application_dir::matter_ls_file(const ::file::path & str,::file::patha & stra)
      {
         get_context_application()->get_context_system()->m_spdir->matter_ls_file(get_context_application(), str, stra);
      }


      ::file::path application_dir::matter_file(const ::file::path & pcsz,  bool bDir)

      {

         string strPath = get_context_application()->get_context_system()->m_spdir->matter(get_context_application(), pcsz, bDir);


         return strPath;

      }


      ::file::path application_dir::userquicklaunch()
      {

         return get_context_application()->get_context_system()->m_spdir->userquicklaunch(get_object());

      }


      ::file::path application_dir::userprograms()
      {

         return get_context_application()->get_context_system()->m_spdir->userprograms(get_object());

      }


      ::file::listing & application_dir::ls(listing & listing)
      {

         return get_context_application()->get_context_system()->m_spdir.m_p->ls(get_context_application(), listing);

      }

      ::file::listing & application_dir::ls_relative_name(listing & listing)
      {

         return get_context_application()->get_context_system()->m_spdir.m_p->ls_relative_name(get_context_application(), listing);

      }


      bool application_dir::has_subdir(const ::file::path & pcsz)

      {

         return get_context_application()->get_context_system()->m_spdir.m_p->has_subdir(get_context_application(), pcsz);


      }


      bool application_dir::is(const ::file::path & pcsz)

      {

         return get_context_application()->get_context_system()->m_spdir.m_p->is(pcsz, get_context_application());


      }


      bool application_dir::is_inside(const ::file::path & pcszDir,const ::file::path & lpcszPath)

      {

         return get_context_application()->get_context_system()->m_spdir.m_p->is_inside(pcszDir, lpcszPath, get_context_application());


      }


      bool application_dir::is_inside_time(const ::file::path & pcsz)

      {
         return get_context_application()->get_context_system()->m_spdir.m_p->is_inside_time(pcsz, get_context_application());

      }


      ::file::listing & application_dir::root_ones(::file::listing & listing)
      {
         return get_context_application()->get_context_system()->m_spdir.m_p->root_ones(listing, get_context_application());
      }


      bool application_dir::mk(const ::file::path & path)
      {

         if (path.is_empty())
         {

            return true;

         }

         return get_context_application()->get_context_system()->m_spdir.m_p->mk(path, get_context_application());

      }


      bool application_dir::rm(const ::file::path & path,bool bRecursive)
      {

         return get_context_application()->get_context_system()->m_spdir.m_p->rm(get_context_application(), path, bRecursive);

      }


      ::file::path application_dir::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
      {

         return get_context_application()->get_context_system()->m_spdir->pathfind(pszEnv, pszTopic, pszMode, get_context_application());

      }


      ::file::path application_dir::dropbox()
      {

         return get_context_application()->get_context_system()->m_spdir->dropbox(get_context_application());

      }

      
      ::file::path application_dir::onedrive()
      {
         
         return get_context_application()->get_context_system()->m_spdir->onedrive(get_context_application());
         
      }



} // namespace file


