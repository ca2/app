// From fs/raw_folder by camilo on 2025-03-10 20:24 <3ThomasBorregaardSorensen!!s
#include "framework.h"
#include "raw_folder.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/string/international.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "apex/platform/node.h"


namespace fs
{


   raw_folder::raw_folder()
   {

      m_bInstalled = false;
      m_bCalculatedInstalled = false;

   }


   raw_folder::~raw_folder()
   {


   }


   void raw_folder::on_initialize_particle()
   {

      ::fs::data::on_initialize_particle();

   }


   // optional if ls_dir is implemented
   bool raw_folder::has_subdir(const ::file::path & path)
   {

      return directory()->has_subdir(base_folder_path()/ path);

   }


   bool raw_folder::fast_has_subdir(const ::file::path & path)
   {
      
      return directory()->fast_has_subdir(raw_path(path));
      
   }


   void raw_folder::calculate_installed()
   {

      //return false;

   }


   bool raw_folder::is_installed()
   {

      if (!m_bCalculatedInstalled)
      {

         calculate_installed();

      }

      return m_bCalculatedInstalled && m_bInstalled;

   }


   ::file::path raw_folder::raw_path(const ::file::path & path)
   {

      return base_folder_path() / path;

   }


   ::file::path raw_folder::base_folder_path()
   {

      if (!is_installed())
      {

         throw ::exception(error_wrong_state);

      }

      return _base_folder_path();

   }


   ::file::path raw_folder::_base_folder_path()
   {

      return {};

   }


   bool raw_folder::enumerate(::file::listing_base & listing)
   {

      if (listing.m_pathFinal.is_empty())
      {

         if (listing.m_pathUser.has_character())
         {

            listing.m_pathFinal = raw_path(listing.m_pathUser);

         }

      }
      else
      {

         listing.m_pathFinal = raw_path(listing.m_pathFinal);

      }

      return directory()->enumerate(listing);

   }


   bool raw_folder::is_link(const ::file::path & path)
   {

      if(::fs::data::is_link(raw_path(path)))
      {

         return true;

      }

      if(m_papplication->os_is_alias(raw_path(path)))
      {

         return true;

      }

      return false;

   }



   /*::file::listing_base & raw_folder::ls_relative_name(::file::listing_base & listing)
   {

      directory()->ls_relative_name(listing);

      return listing;

   }*/



   int raw_folder::is_dir(const ::file::path & path)
   {

      return directory()->is(raw_path(path)) ? 1 : 0;

   }


   ::file::listing_base & raw_folder::root_ones(::file::listing_base & listing)
   {

      if (listing.m_pathFinal.is_empty())
      {

         if (listing.m_pathUser.has_character())
         {

            listing.m_pathFinal = raw_path(listing.m_pathUser);

         }

      }
      else
      {

         listing.m_pathFinal = raw_path(listing.m_pathFinal);

      }

      
      node()->root_ones(listing);

      return listing;

   }


   //void raw_folder::get_ascendants_path(const ::file::path & path,::file::path_array_base & stra)
   //{

   //   return file()->get_ascendants_path(scopedstrPath, stra);

   //}


   //void raw_folder::get_ascendants_name(const ::file::path & path,::file::path_array_base & straParam)

   //{

   //   return file()->get_ascendants_name(pcsz, straParam);


   //}


   //string raw_folder::eat_end_level(const ::file::path & path, int iCount)
   //{

   //   string strPath(scopedstrPath);

   //   while(iCount > 0)
   //   {

   //      strPath = directory()->name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string raw_folder::file_name(const ::file::path & path)
   //{

   //   return file()->name_(scopedstrPath);

   //}


   //string raw_folder::dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
   //{

   //   return ::file::path(scopedstr1) / ::file::path(scopedstr2);

   //}


   bool raw_folder::file_move(const ::file::path & pathTarget,const ::file::path & pathSource)
   {

      file()->transfer(raw_path(pathTarget), raw_path(pathSource));

      return true;

   }


   file_pointer raw_folder::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      file_pointer pfile;

      //if (eopen & ::file::e_open_text)
      //{

      //   pfile = __create_new<::stdio_file>();

      //}
      //else
      //{

         __øconstruct(pfile);

//      }

      //auto result =
         pfile->open(raw_path(payloadFile.as_file_path()), eopen, ppfileexception);

      //if(!result)
      //{

      //   return result;

      //}

      return pfile;

   }


   bool raw_folder::file_exists(const ::file::path & path)
   {

      return file()->exists(raw_path(path));

   }


} // namespace fs



