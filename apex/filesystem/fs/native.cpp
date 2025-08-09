#include "framework.h"
#include "native.h"
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


   native::native()
   {

   }


   native::~native()
   {


   }


   // optional if ls_dir is implemented
   bool native::has_subdir(const ::file::path & path)
   {

      return directory()->has_subdir(path);

   }


   bool native::fast_has_subdir(const ::file::path & path)
   {
      
      return directory()->fast_has_subdir(path);
      
   }


   bool native::enumerate(::file::listing_base & listing)
   {

      return directory()->enumerate(listing);

   }


   bool native::is_link(const ::file::path & path)
   {

      if(::fs::data::is_link(path))
      {

         return true;

      }

      if(m_papplication->os_is_alias(path))
      {

         return true;

      }

      return false;

   }



   /*::file::listing_base & native::ls_relative_name(::file::listing_base & listing)
   {

      directory()->ls_relative_name(listing);

      return listing;

   }*/



   int native::is_dir(const ::file::path & path)
   {

      return directory()->is(path) ? 1 : 0;

   }


   ::file::listing_base & native::root_ones(::file::listing_base & listing)
   {
      
      node()->root_ones(listing);

      return listing;

   }


   //void native::get_ascendants_path(const ::file::path & path,::file::path_array_base & stra)
   //{

   //   return file()->get_ascendants_path(scopedstrPath, stra);

   //}


   //void native::get_ascendants_name(const ::file::path & path,::file::path_array_base & straParam)

   //{

   //   return file()->get_ascendants_name(pcsz, straParam);


   //}


   //string native::eat_end_level(const ::file::path & path, int iCount)
   //{

   //   string strPath(scopedstrPath);

   //   while(iCount > 0)
   //   {

   //      strPath = directory()->name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string native::file_name(const ::file::path & path)
   //{

   //   return file()->name_(scopedstrPath);

   //}


   //string native::dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
   //{

   //   return ::file::path(scopedstr1) / ::file::path(scopedstr2);

   //}


   bool native::file_move(const ::file::path & pathTarget,const ::file::path & pathSource)
   {

      file()->transfer(pathTarget, pathSource);

      return true;

   }


   file_pointer native::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
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
         pfile->open(payloadFile, eopen, ppfileexception);

      //if(!result)
      //{

      //   return result;

      //}

      return pfile;

   }


   bool native::file_exists(const ::file::path & path)
   {

      return file()->exists(path);

   }


} // namespace fs



