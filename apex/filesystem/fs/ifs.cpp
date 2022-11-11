#include "framework.h"
#include "ifs.h"
#include "ifs_file.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/data/listener.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


ifs::ifs(const char * pszRoot)
{

   m_strRoot = pszRoot;
   m_bInitialized = false;

}


ifs::~ifs()
{


}


bool ifs::fast_has_subdir(const ::file::path & path)
{

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path];

   auto psystem = get_system()->m_papexsystem;

   if(dir.m_durationLast.elapsed() < psystem->m_durationFileListingCache)
   {

      return dir.get_count() > 0;

   }

   return true;

}

bool ifs::has_subdir(const ::file::path & path)
{

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path];

   auto psystem = acmesystem()->m_papexsystem;

   if (dir.m_durationLast.elapsed() < psystem->m_durationFileListingCache)
   {

      return dir.get_count() > 0;

   }

   synchronouslock.unlock();

   ::file::listing listing;

   listing.set_folder_listing(path);

   enumerate(listing);

   synchronouslock.lock();

   return dir.get_count() > 0;

}


::file::listing & ifs::root_ones(::file::listing & listing)
{

   ::file::path path;

   path = "uifs://";

   path.m_iDir = 1;

   listing.defer_add(path);

   listing.m_straTitle.add("User Intelligent File psystem");

   return listing;

}


bool ifs::enumerate(::file::listing & listing)
{

   synchronous_lock synchronouslock(this->synchronization());

   auto & dir = m_map[listing.m_pathUser];

   auto psystem = acmesystem()->m_papexsystem;

   if (dir.m_durationLast.elapsed() < psystem->m_durationFileListingCache)
   {

      listing = dir;

      return listing;

   }

   listing.clear_results();

   try
   {

      defer_initialize();

   }
   catch(string & str)
   {

      if(str == "You have not logged in! Exiting!")
      {

         throw ::exception(error_wrong_state, "uifs:// You have not logged in!");

      }

      dir.m_durationLast.now();

      throw ::exception(error_failed);

      return listing;

   }

   throw ::exception(todo, "xml");

   //xml::document doc;

   //string strUrl;

   //strUrl = "http://file.ca2.software/ifs/ls?path=" + purl->url_encode(listing.m_pathUser);

   //string strSource;

   //property_set set;

   //strSource = m_pcontext->m_papexcontext->http().get(strUrl, set);

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

   //::pointer<::xml::node>pnode = doc.root()->get_child("folder");

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

   //      path.m_iSize = pchild->attribute("size_i32");

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


   ////::file::path_array  & straThisDir         = m_mapdirFolder[strDir];
   ////::file::path_array  & straThisDirName     = m_mapdirFolderName[strDir];
   ////::file::path_array  & straThisFile        = m_mapdirFile[strDir];
   ////::file::path_array  & straThisFileName    = m_mapdirFileName[strDir];
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

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path.folder()];

   auto psystem = acmesystem()->m_papexsystem;

   if(dir.m_durationLast.timeout(psystem->m_durationFileListingCache))
   {

      ::file::listing listing;

      listing.set_listing(path.folder());

      ::particle::dir()->enumerate(listing);

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
   __UNREFERENCED_PARAMETER(pszDst);
   __UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


file_pointer ifs::get_file(const ::file::path & path, const ::file::e_open & eopen)
{

   auto pfile = __new(ifs_file( path));

   //auto result =
   
   pfile->open(path, eopen);

   //if(!result)
   //{

   //   return result;

   //}

   return pfile;

}


bool ifs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


::payload ifs::file_length(const ::file::path & pszPath)
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
