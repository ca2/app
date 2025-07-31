#include "framework.h"
#include "remote_native.h"
#include "remote_native_file.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


namespace fs
{


   remote_native::remote_native(const ::scoped_string & scopedstrRoot)
   {

      m_strRoot = scopedstrRoot;

   }


   remote_native::~remote_native()
   {

   }


   bool remote_native::fast_has_subdir(const ::file::path & pszPath)
   {

      return true;

   }


   bool remote_native::has_subdir(const ::file::path & pszPath)
   {

      defer_initialize();

      throw ::exception(todo, "xml");

      //xml::document doc;

      //string strUrl;

      //strUrl = "http://fs.veriwell.net/fs/ls?path=" + ::url::encode(scopedstrPath);

      //string strSource;

      //::property_set set;

      //strSource = http()->get(strUrl, set);

      //if(strSource.is_empty())
      //   return false;

      //if(!doc.load(strSource))
      //   return false;

      //if(doc.root()->get_name() != "folder")
      //   return false;

      //::pointer<::xml::node>pnode = doc.get_child("folder");

      //if(pnode == nullptr)
      //   return false;

      //if(pnode->get_children_count("folder") <= 0)
      //   return false;

      return true;

   }

   ::file::listing & remote_native::root_ones(::file::listing & listing)
   {

      ::file::path path;

      path.set_existent_folder();

      path = "fs://";

      listing.defer_add(path);

      listing.m_straTitle.add("Remote File psystem");

      return listing;

   }


   bool remote_native::enumerate(::file::listing & listing)
   {

      try
      {

         defer_initialize();

      }
      catch(string & str)
      {

         if(str == "You have not logged in! Exiting!")
         {

            throw ::exception(error_authorization, "uifs://You are not authorized!!");

         }

         return listing;

      }

      throw ::exception(todo, "xml");

      //xml::document doc;

      //string strUrl;

      //strUrl = "http://fs.veriwell.net/fs/ls?path=" + ::url::encode(purl->get_script(listing.m_pathUser))
      //         + "&server=" + ::url::encode(purl->get_server(listing.m_pathUser));

      //string strSource;

      //::property_set set;

      //strSource = http()->get(strUrl, set);

      //if(strSource.is_empty())
      //   return listing = ::error_failed;

      //if(!doc.load(strSource))
      //   return listing = ::error_failed;

      //if(doc.root()->get_name() != "folder")
      //   return listing = ::error_failed;

      //::pointer<::xml::node>pnode = doc.root()->get_child("folder");

      //if(pnode != nullptr)
      //{

      //   for(auto & pchild : pnode->children())
      //   {

      //      if(pchild->get_name() != "folder")
      //         continue;

      //      m_mapdirTimeout[listing.m_pathUser]= ::time::now() + (15 * 1000);

      //      m_mapfileTimeout.erase_key(listing.m_pathUser);

      //      auto & path = listing.add_child_get(pchild->attribute("name"));

      //      path.m_iSize = 0;

      //      path.m_iDir = 1;

      //   }
      //}

      //pnode = doc.root()->get_child("file");

      //if(pnode != nullptr)
      //{

      //   for(auto & pchild : pnode->children())
      //   {

      //      if(pchild->get_name() != "file")
      //         continue;

      //      m_mapfileTimeout[listing.m_pathUser]= ::time::now() + (15 * 1000);

      //      m_mapdirTimeout.erase_key(listing.m_pathUser);

      //      auto & path = listing.add_child_get(pchild->attribute("name"));

      //      path.m_iSize = pchild->attribute("int_size");

      //      path.m_iDir = 0;

      //   }
      //}

      return listing;

   }


   int remote_native::is_dir(const ::file::path & path)
   {

      if(path.is_empty())
      {
         
         return 1;

      }

      if(case_insensitive_ansi_compare(path, "fs://") == 0)
      {
         
         return 1;

      }

      ::url::url url(path);

      if(url.request().path().is_empty() || url.request().path() == "/")
      {
         
         return 1;

      }

      defer_initialize();

      class ::time millisLast;

      if(m_mapfileLast.lookup(path, millisLast))
      {

         if(millisLast.elapsed() > *system()->file_listing_cache_time())
         {
            
            ::file::listing listing;

            listing.set_listing(path);

            directory()->enumerate(listing);
            
         }
         else
         {
            
            return 0;
            
         }
         
      }

      if(m_mapdirLast.lookup(path, millisLast))
      {
         
         if(millisLast.elapsed() > system()->m_timeFileListingCache)
         {
            
            ::file::listing listing;

            listing.set_listing(path);

            directory()->enumerate(listing);

         }
         else
         {
            return 1;
         }
      }

      if(m_mapfileLast.lookup(path, millisLast))
      {

         if(millisLast.elapsed() > system()->m_timeFileListingCache)
         {
            return 0;
         }
         else
         {
            return 1;
         }
      }
      else
      {
         return 0;
      }



      /*string strUrl;

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + ::url::encode(scopedstrPath);

      string strSource;

      strSource = http()->get(strUrl);

      if(strSource.is_empty())
      return false;

      if(!node.load(strSource))
      return false;

      if(node.m_strName != "folder")
      return false;

      return true;*/

   }

   //string remote_native::file_name(const ::file::path & pszPath)
   //{

   //   string strPath(scopedstrPath);

   //   if(!strPath.case_insensitive_begins_eat("fs://"))
   //   {
   //      return "";
   //   }

   //   auto pFind = strPath.rear_find("/");

   //   if(::is_null(pFind))
   //      iFind = -1;

   //   return strPath(pFind + 1);

   //}

   bool remote_native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {
      __UNREFERENCED_PARAMETER(scopedstrDst);
      __UNREFERENCED_PARAMETER(scopedstrSrc);
      return true;
   }


   file_pointer remote_native::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      file_pointer pfile = __allocate remote_native_file(payloadFile);

      //auto result =
      pfile->open(payloadFile, eopen, ppfileexception);

      //if(!result)
      //{

      //   return result;

      //}

      return pfile;

   }


   bool remote_native::file_exists(const ::file::path & pszPath)
   {

      return ::fs::data::file_exists(scopedstrPath);

   }


   void remote_native::defer_initialize()
   {

      if(!m_bInitialized)
      {
         //http()->get("http://file.ca2.network/");
         m_bInitialized = true;
      }

   }

   bool remote_native::is_zero_latency(const  ::file::path & psz)
   {

      return false;

   }


} // namespace fs



