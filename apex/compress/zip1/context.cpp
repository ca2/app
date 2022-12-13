#include "framework.h"
#include "_.h"
//#include "acme/compress/zip/unzip.h"


namespace str
{

   ::index case_insensitive_begins_eat(string & str,string_array & stra)
   {

      for(index i = 0; i < stra.get_count(); i++)
      {

         if(str.case_insensitive_begins_eat(stra[i]))
            return i;

      }

      return -1;

   }


   ::index begins_eat(string & str,string_array & stra)
   {

      for(index i = 0; i < stra.get_count(); i++)
      {

         if(str.begins_eat(stra[i]))
            return i;

      }

      return -1;

   }



} // namespace str


//namespace zip
//{


   zip_context::zip_context(::particle * pparticle) 
   {

      initialize(pparticle);

   }


   zip_context::~zip_context()
   {

   }


   bool zip_context::ls(::file::listing & listing)
   {

      string strZip;

      string strRemain;

      string strLastZip;

      if(string_ends_ci(listing.m_pathUser, ".zip"))
      {

         listing.m_pathFinal = m_pcontext->m_papexcontext->defer_process_path(listing.m_pathUser);

         strZip = listing.m_pathFinal;

         strLastZip = strZip;

         strZip += ":";

      }
      else if(::str().find_file_extension("zip:", listing.m_pathUser) >= 0)
      {

         listing.m_pathFinal = m_pcontext->m_papexcontext->defer_process_path(listing.m_pathUser);

         strZip = listing.m_pathFinal;

         strRemain = strZip.Mid(strZip.rear_find(".zip:") + strlen(".zip:"));

         strLastZip = strZip.Left(strZip.rear_find(".zip:") + strlen(".zip"));

      }
      else
      {

         return false;

      }

      compress_context compress(this);

      ::file::path pathZip;

      string_array straPath;

      if (!compress.get_patha(pathZip, straPath, strZip))
      {

         return false;

      }

      auto pfile = file()->get_reader(pathZip);

      if (!pfile)
      {

         return false;

      }

      zip_context zip(this);

      auto pinfile = zip.get_in_file(pfile, straPath);

      if(!pinfile)
      {

         return false;

      }

      void * pf = pinfile->get_zip_file()->m_pfUnzip;

      string str;

      string wstrFolder;

      string_array wstraFolder;

      strRemain.replace("\\", "/");

      strRemain.begins_eat("/");

      if(strRemain.has_char())
      {

         if(!string_ends(strRemain,"/"))
         {

            strRemain += "/";

         }

      }

      unz_file_info fi;

      if(pf != nullptr)
      {

         int iLastZip;

         iLastZip = int( ::file::path(strLastZip + ":").length());

         while(true)
         {

            char szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
            pf,
            &fi,
            szTitle,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);

            string strTitle(szTitle);

            if(strRemain != strTitle && ((strRemain.is_empty() &&
                                          (strTitle.find("/") < 0  || strTitle.find("/") == (strTitle.get_length() - 1)))
                                         || (strRemain.has_char() && strTitle.case_insensitive_begins_eat(strRemain))))
            {

               if(listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
               {

                  listing.add(::file::path(strLastZip + ":" + strRemain + strTitle));
                  listing.last().m_iRelative = iLastZip;
                  listing.last().m_iDir = string_ends(szTitle, "/") || string_ends(szTitle, "\\") || string_ends(szTitle, ".zip");
                  listing.last().m_iSize = fi.uncompressed_size;

               }

            }

            if(unzGoToNextFile(pf) != UNZ_OK)
            {

               break;

            }

         }

      }

      return true;

   }


   bool zip_context::has_sub_folder(const char * pszFileName)
   {

      string strZip;

      string strRemain;

      string strLastZip;

      string strPath(pszFileName);

      ::file::path pathFinal;

      if (string_ends_ci(strPath, ".zip"))
      {

         pathFinal = m_pcontext->m_papexcontext->defer_process_path(strPath);

         strZip = strPath;

         strLastZip = strZip;

         strZip += ":";

      }
      else if (::str().find_file_extension("zip:", strPath) >= 0)
      {

         pathFinal = m_pcontext->m_papexcontext->defer_process_path(strPath);

         strZip = strPath;

         strRemain = strZip.Mid(strZip.rear_find(".zip:") + strlen(".zip:"));

         strLastZip = strZip.Left(strZip.rear_find(".zip:") + strlen(".zip"));

      }
      else
      {

         return false;


      }

      compress_context compress(this);

      ::file::path pathZip;

      string_array straPath;

      if (!compress.get_patha(pathZip, straPath, strZip))
      {

         return false;

      }

      auto pfile = file()->get_reader(pathZip);

      if (!pfile)
      {

         return false;

      }

      zip_context zip(this);

      auto pinfile = zip.get_in_file(pfile, straPath);

      return pinfile;

   }


   bool zip_context::is_file_or_dir(::file::file * pfile, const string_array & straPath, ::file::enum_type * petype)
   {

      auto pinfile = get_in_file(pfile, straPath, petype);

      return pinfile;

   }


   ::pointer<::zip::in_file>zip_context::get_in_file(::file::file * pfile, const string_array & straPath, ::file::enum_type * petype)
   {

      ::pointer<::zip::in_file>pinfile;

      __construct_new(pinfile);

      if (!pinfile->unzip_open(pfile, straPath, 2, petype))
      {

         return ::error_failed;

      }

      return pinfile;

   }


   bool zip_context::extract(memory & m, ::file::file * pfile, const string_array & straPath, ::file::enum_type * petype)
   {

      auto pinfile = get_in_file(pfile, straPath, petype);

      if (!pinfile)
      {

         return false;

      }

      return pinfile->dump(m);

   }


   bool zip_context::e_extract_all(const char * pszDir,::payload payloadFile, ::file::path_array * ppatha, string_array * pstraFilter, bool_array * pbaBeginsFilterEat)
   {

      auto pfile = file()->get_file(payloadFile,::file::e_open_binary | ::file::e_open_read);

      if (!pfile)
      {

         return false;

      }

      auto pinfile = get_in_file(pfile, {});

      if(!pinfile)
      {

         return false;

      }

      unzFile pf = pinfile->get_zip_file()->m_pfUnzip;

      string str;

      string wstrFolder;

      string_array wstraFolder;

      unz_file_info fi;

      if(pf != nullptr)
      {

         while(true)
         {

            char szTitle[_MAX_PATH];

            unzGetCurrentFileInfo(
            pf,
            &fi,
            szTitle,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);
            string strTitle(szTitle);
            if(string_ends(szTitle, "/") || string_ends(szTitle, "\\"))
            {

            }
            else if(pinfile->locate(strTitle) && (pstraFilter == nullptr || strTitle.case_insensitive_begins_eat(*pstraFilter) >= 0))
            {

               string strRelative(strTitle);

               ::file::path path = ::file::path(pszDir) / strRelative;

               file_pointer spfile = file()->get_file(
                                path,
                                ::file::e_open_create | ::file::e_open_write | ::file::e_open_defer_create_directory);


               if(spfile.is_set())
               {
                  pinfile->to(spfile);
                  if (::is_set(ppatha))
                  {
                     ppatha->add(path);

                  }
               }
               else
               {
                  //   return false;
               }
            }
            if(unzGoToNextFile(pf) != UNZ_OK)
            {
               break;
            }
         }
      }

      return true;

   }


   bool zip_context::is_unzippable(const char * pszFileName)
   {

      string str(pszFileName);

      if(str.get_length() < 4)
      {
         
         return false;
         
      }
      
      if(str.Right(4) != ".zip")
      {
         
         return false;
         
      }
      
      auto pfile = file()->get_reader(pszFileName);
      
      if(!pfile)
      {
         
         return false;
         
      }

      ::zip::file file;

      return file.unzip_open(pfile);

   }
//
//} // namespace zip
//
