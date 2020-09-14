#include "framework.h"
//#include "apex/xml/_.h"
#include "apex/net/sockets/_.h"
#include "apex/filesystem/fs/_fs.h"
#include "ifs_file.h"


ifs::ifs(const char * pszRoot)
{

   m_strRoot = pszRoot;
   m_bInitialized = false;

}


bool ifs::fast_has_subdir(const ::file::path & path)
{

   sync_lock sl(get_mutex());

//   tick tickTimeout;

   dir_listing & dir = m_map[path];

   if(::get_tick() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return true;

}

bool ifs::has_subdir(const ::file::path & path)
{

   sync_lock sl(get_mutex());

//   tick tickTimeout;

   dir_listing & dir = m_map[path];

   if(::get_tick() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   ::file::listing listing(this);

   Context.dir().ls(listing, path);

   if(::get_tick() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return false;

}


::file::listing & ifs::root_ones(::file::listing & listing)
{

   ::file::path & path = listing[listing.add("uifs://")];

   path.m_iDir = 1;

   listing.m_straTitle.add("User Intelligent File System");



   return listing;

}


::file::listing & ifs::ls(::file::listing & listing)
{

   sync_lock sl(get_mutex());

//   tick tickTimeout;

   dir_listing & dir = m_map[listing.m_pathUser];

   if(::get_tick() < dir.m_uiLsTimeout)
   {

      listing = dir;

      return listing;

   }

   dir.clear_results();

   listing.clear_results();


   //::file::patha  straDir;
   //::file::patha  straDirName;
   //::file::patha  straFile;
   //::file::patha  straFileName;
   //i64_array    iaFileSize;
   //i64_array    iaFolderSize;
   //bool_array     baFileDir;
   //bool_array     baFolderDir;

   try
   {

      defer_initialize();

   }
   catch(string & str)
   {

      if(str == "You have not logged in! Exiting!")
      {

         __throw(::exception::exception("uifs:// You have not logged in!"));

      }

      dir.m_uiLsTimeout = (u32) (::get_tick() + ((5000) * 4));

      listing = ::error_failed;

      return listing;

   }

   __throw(todo("xml"));

   //xml::document doc;

   //string strUrl;

   //strUrl = "http://file.ca2.cc/ifs/ls?path=" + System.url().url_encode(listing.m_pathUser);

   //string strSource;

   //property_set set;

   //strSource = Context.http().get(strUrl, set);

   //if(strSource.is_empty())
   //{

   //   dir.m_uiLsTimeout = (u32) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //if(!doc.load(strSource))
   //{

   //   dir.m_uiLsTimeout = (u32) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //if(doc.root()->get_name() != "folder")
   //{

   //   dir.m_uiLsTimeout = (u32) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //__pointer(::xml::node) pnode = doc.root()->get_child("folder");

   //if(pnode != nullptr)
   //{

   //   for(auto pchild : pnode->children().ptra())
   //   {

   //      if(pchild->get_name() != "folder")
   //         continue;

   //      auto & path = dir.add_get(::file::path(listing.m_pathUser / pchild->attribute("name").get_string(),::file::path_url));

   //      path.m_iDir = 1;

   //   }

   //}

   //pnode = doc.root()->get_child("file");

   //if(pnode != nullptr)
   //{

   //   for(auto pchild : pnode->children().ptra())
   //   {

   //      if(pchild->get_name() != "file")
   //         continue;

   //      string strExtension = pchild->attribute("extension");

   //      auto & path = dir.add_get(::file::path(listing.m_pathUser / pchild->attribute("name").get_string(),::file::path_url));

   //      path.m_iSize = pchild->attribute("size");

   //      path.m_iDir = 0;

   //   }

   //}

   //dir.m_uiTimeout = (u32) (::get_tick() + ((1000) * 4));



   //listing = dir;

   ////   if(m_mapdirFolder[strDir].is_null())
   ////   m_mapdirFolder[strDir] = __new(string_array);
   ////if(m_mapdirFolderName[strDir].is_null())
   ////   m_mapdirFolderName[strDir] = __new(string_array);
   ////if(m_mapdirFile[strDir].is_null())
   ////   m_mapdirFile[strDir] = __new(string_array);
   ////if(m_mapdirFileName[strDir].is_null())
   ////   m_mapdirFileName[strDir] = __new(string_array);
   ////if (m_mapdirFileSize[strDir].is_null())
   ////   m_mapdirFileSize[strDir] = __new(i64_array);
   ////if (m_mapdirFolderSize[strDir].is_null())
   ////   m_mapdirFolderSize[strDir] = __new(i64_array);
   ////if(m_mapdirFileDir[strDir].is_null())
   ////   m_mapdirFileDir[strDir] = __new(bool_array);
   ////if(m_mapdirFolderDir[strDir].is_null())
   ////   m_mapdirFolderDir[strDir] = __new(bool_array);


   ////::file::patha  & straThisDir         = m_mapdirFolder[strDir];
   ////::file::patha  & straThisDirName     = m_mapdirFolderName[strDir];
   ////::file::patha  & straThisFile        = m_mapdirFile[strDir];
   ////::file::patha  & straThisFileName    = m_mapdirFileName[strDir];
   ////i64_array    & iaThisFileSize      = *m_mapdirFileSize[strDir];
   ////i64_array    & iaThisFolderSize    = *m_mapdirFolderSize[strDir];
   ////bool_array     & baThisFileDir       = *m_mapdirFileDir[strDir];
   ////bool_array     & baThisFolderDir     = *m_mapdirFolderDir[strDir];


   ////straThisDir          = straDir;
   ////straThisDirName      = straDirName;
   ////straThisFile         = straFile;
   ////straThisFileName     = straFileName;
   ////iaThisFileSize       = iaFileSize;
   ////iaThisFolderSize     = iaFolderSize;
   ////baThisFileDir        = baFileDir;
   ////baThisFolderDir      = baFolderDir;



   //dir.m_uiLsTimeout = (u32) (::get_tick() + ((1000) * 4));

   return listing;

}


int ifs::is_dir(const ::file::path & path)
{

   if(path.is_empty())
   {
      return 1;
   }

   if(ansi_compare_ci(path, "uifs://") == 0)
   {
      return 1;
   }
   if(ansi_compare_ci(path,"uifs:/") == 0)
   {
      return 1;
   }
   if(ansi_compare_ci(path,"uifs:") == 0)
   {
      return 1;
   }


   defer_initialize();


   //tick tickTimeout;

   sync_lock sl(get_mutex());

   dir_listing & dir = m_map[path.folder()];

   if(::get_tick() > dir.m_uiTimeout)
   {

      ::file::listing listing(this);

      Context.dir().ls(listing, path.folder());

   }

   auto iFind = dir.name_find_first_ci(path.name());

   if(iFind < 0)
   {

      return 0;

   }

   return dir[iFind].m_iDir;


}


bool ifs::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
{
   UNREFERENCED_PARAMETER(pszDst);
   UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


file_result ifs::get_file(const ::file::path & path, UINT nOpenFlags)
{

   auto pfile = __new(ifs_file( path));

   auto result = pfile->open(path,nOpenFlags);

   if(!result)
   {

      return result;

   }

   return pfile;

}


bool ifs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


var ifs::file_length(const ::file::path & pszPath)
{

   return ::fs::data::file_length(pszPath);

}


void ifs::defer_initialize()
{

   if(!m_bInitialized)
   {


      m_bInitialized = true;

   }

}

bool ifs::is_zero_latency(const ::file::path & psz)
{

   return false;

}
