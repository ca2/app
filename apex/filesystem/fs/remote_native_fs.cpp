#include "framework.h"
#include "apex/net/sockets/_sockets.h"
#include "apex/filesystem/fs/_fs.h"
#include "remote_native_file.h"


namespace fs
{


   remote_native::remote_native(const char * pszRoot)
   {

      m_strRoot = pszRoot;

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

      __throw(todo, "xml");

      //xml::document doc;

      //string strUrl;

      //strUrl = "http://fs.veriwell.net/fs/ls?path=" + purl->url_encode(pszPath);

      //string strSource;

      //property_set set;

      //strSource = m_pcontext->m_papexcontext->http().get(strUrl, set);

      //if(strSource.is_empty())
      //   return false;

      //if(!doc.load(strSource))
      //   return false;

      //if(doc.root()->get_name() != "folder")
      //   return false;

      //__pointer(::xml::node) pnode = doc.get_child("folder");

      //if(pnode == nullptr)
      //   return false;

      //if(pnode->get_children_count("folder") <= 0)
      //   return false;

      return true;

   }

   ::file::listing & remote_native::root_ones(::file::listing & listing)
   {

      ::file::path & path = listing[listing.add("fs://")];

      path.m_iDir = 1;

      listing.m_straTitle.add("Remote File psystem");

      return listing;

   }



   ::file::listing & remote_native::ls(::file::listing & listing)
   {

      try
      {

         defer_initialize();

      }
      catch(string & str)
      {

         if(str == "You have not logged in! Exiting!")
         {

            __throw(error_authorization, "uifs://You are not authorized!!");

         }

         return listing;

      }

      __throw(todo, "xml");

      //xml::document doc;

      //string strUrl;

      //strUrl = "http://fs.veriwell.net/fs/ls?path=" + purl->url_encode(purl->get_script(listing.m_pathUser))
      //         + "&server=" + purl->url_encode(purl->get_server(listing.m_pathUser));

      //string strSource;

      //property_set set;

      //strSource = m_pcontext->m_papexcontext->http().get(strUrl, set);

      //if(strSource.is_empty())
      //   return listing = ::error_failed;

      //if(!doc.load(strSource))
      //   return listing = ::error_failed;

      //if(doc.root()->get_name() != "folder")
      //   return listing = ::error_failed;

      //__pointer(::xml::node) pnode = doc.root()->get_child("folder");

      //if(pnode != nullptr)
      //{

      //   for(auto & pchild : pnode->children())
      //   {

      //      if(pchild->get_name() != "folder")
      //         continue;

      //      m_mapdirTimeout[listing.m_pathUser]= ::millis::now() + (15 * 1000);

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

      //      m_mapfileTimeout[listing.m_pathUser]= ::millis::now() + (15 * 1000);

      //      m_mapdirTimeout.erase_key(listing.m_pathUser);

      //      auto & path = listing.add_child_get(pchild->attribute("name"));

      //      path.m_iSize = pchild->attribute("size_i32");

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

      if(ansi_compare_ci(path, "fs://") == 0)
      {
         return 1;
      }

      auto psystem = m_psystem;

      auto purl = psystem->url();

      if(purl->get_script(path).is_empty() ||
         purl->get_script(path) == "/")
      {
         return 1;
      }

      defer_initialize();

      millis millisLast;

      if(m_mapfileLast.lookup(path, millisLast))
      {

         if(millisLast.elapsed() > psystem->m_millisFileListingCache)
         {
            
            ::file::listing l;

            m_pcontext->m_papexcontext->dir().ls(l, path);
            
         }
         else
         {
            
            return 0;
            
         }
         
      }

      if(m_mapdirLast.lookup(path, millisLast))
      {
         
         if(millisLast.elapsed() > psystem->m_millisFileListingCache)
         {
            
            ::file::listing l;

            m_pcontext->m_papexcontext->dir().ls(l, path);
         }
         else
         {
            return 1;
         }
      }

      if(m_mapfileLast.lookup(path, millisLast))
      {
         if(millisLast.elapsed() > psystem->m_millisFileListingCache)
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

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + purl->url_encode(pszPath);

      string strSource;

      strSource = m_pcontext->m_papexcontext->http().get(strUrl);

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

   //   string strPath(pszPath);

   //   if(!::str::begins_eat_ci(strPath, "fs://"))
   //   {
   //      return "";
   //   }

   //   strsize iFind = strPath.reverse_find("/");

   //   if(iFind < 0)
   //      iFind = -1;

   //   return strPath.Mid(iFind + 1);

   //}

   bool remote_native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return true;
   }


   file_result remote_native::get_file(const ::file::path & path, const ::file::e_open & eopen)
   {

      file_pointer pfile = __new(remote_native_file(path));

      auto result = pfile->open(path, eopen);

      if(!result)
      {

         return result;

      }

      return pfile;

   }


   bool remote_native::file_exists(const ::file::path & pszPath)
   {
      return ::fs::data::file_exists(pszPath);
   }


   void remote_native::defer_initialize()
   {

      if(!m_bInitialized)
      {
         //m_pcontext->m_papexcontext->http().get("http://file.ca2.software/");
         m_bInitialized = true;
      }

   }

   bool remote_native::is_zero_latency(const  ::file::path & psz)
   {

      return false;

   }


} // namespace fs



