#include "framework.h"
#include "ifs.h"
#include "ifs_file.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


ifs::ifs(const ::scoped_string & scopedstrRoot)
{

   m_strRoot = scopedstrRoot;
   m_bInitialized = false;

}


ifs::~ifs()
{


}


bool ifs::fast_has_subdir(const ::file::path & path)
{

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path];

   auto psystem = system();

   if(dir.m_timeLast.elapsed() < *psystem->file_listing_cache_time())
   {

      return dir.get_count() > 0;

   }

   return true;

}

bool ifs::has_subdir(const ::file::path & path)
{

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path];

   auto psystem = system();

   if (dir.m_timeLast.elapsed() < *psystem->file_listing_cache_time())
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

   path.set_existent_folder();

   listing.defer_add(path);

   listing.m_straTitle.add("User Intelligent File psystem");

   return listing;

}


bool ifs::enumerate(::file::listing & listing)
{

   synchronous_lock synchronouslock(this->synchronization());

   auto & dir = m_map[listing.m_pathUser];

   auto psystem = system();

   if (dir.m_timeLast.elapsed() < *psystem->file_listing_cache_time())
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

      dir.m_timeLast.Now();

      throw ::exception(error_failed);

      return listing;

   }

   throw ::exception(todo, "xml");

   //xml::document doc;

   //string strUrl;

   //strUrl = "http://file.ca2.network/ifs/ls?path=" + ::url::encode(listing.m_pathUser);

   //string strSource;

   //::property_set set;

   //strSource = http()->get(strUrl, set);

   //if(strSource.is_empty())
   //{

   //   dir.m_uiLsTimeout = (unsigned int) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //if(!doc.load(strSource))
   //{

   //   dir.m_uiLsTimeout = (unsigned int) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //if(doc.root()->get_name() != "folder")
   //{

   //   dir.m_uiLsTimeout = (unsigned int) (::get_tick() + ((5000) * 4));

   //   return listing = ::error_failed;

   //}

   //::pointer<::xml::node>pnode = doc.root()->get_child("folder");

   //if(pnode != nullptr)
   //{

   //   for(auto pchild : pnode->children().ptra())
   //   {

   //      if(pchild->get_name() != "folder")
   //         continue;

   //      auto & path = dir.add_get(::file::path(listing.m_pathUser / pchild->attribute("name").as_string(),::file::path_url));

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

   //      auto & path = dir.add_get(::file::path(listing.m_pathUser / pchild->attribute("name").as_string(),::file::path_url));

   //      path.m_iSize = pchild->attribute("int_size");

   //      path.m_iDir = 0;

   //   }

   //}

   //dir.m_uiTimeout = (unsigned int) (::get_tick() + ((1000) * 4));



   //listing = dir;

   ////   if(m_mapdirFolder[strDir].is_null())
   ////   m_mapdirFolder[strDir] = __allocate string_array();
   ////if(m_mapdirFolderName[strDir].is_null())
   ////   m_mapdirFolderName[strDir] = __allocate string_array();
   ////if(m_mapdirFile[strDir].is_null())
   ////   m_mapdirFile[strDir] = __allocate string_array();
   ////if(m_mapdirFileName[strDir].is_null())
   ////   m_mapdirFileName[strDir] = __allocate string_array();
   ////if (m_mapdirFileSize[strDir].is_null())
   ////   m_mapdirFileSize[strDir] = __allocate long_long_array();
   ////if (m_mapdirFolderSize[strDir].is_null())
   ////   m_mapdirFolderSize[strDir] = __allocate long_long_array();
   ////if(m_mapdirFileDir[strDir].is_null())
   ////   m_mapdirFileDir[strDir] = __allocate bool_array();
   ////if(m_mapdirFolderDir[strDir].is_null())
   ////   m_mapdirFolderDir[strDir] = __allocate bool_array();


   ////::file::path_array  & straThisDir         = m_mapdirFolder[strDir];
   ////::file::path_array  & straThisDirName     = m_mapdirFolderName[strDir];
   ////::file::path_array  & straThisFile        = m_mapdirFile[strDir];
   ////::file::path_array  & straThisFileName    = m_mapdirFileName[strDir];
   ////long_long_array    & iaThisFileSize      = *m_mapdirFileSize[strDir];
   ////long_long_array    & iaThisFolderSize    = *m_mapdirFolderSize[strDir];
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



   //dir.m_uiLsTimeout = (unsigned int) (::get_tick() + ((1000) * 4));

   return listing;

}


int ifs::is_dir(const ::file::path & path)
{

   if(path.is_empty())
   {

      return 1;

   }

   if(case_insensitive_ansi_compare(path, "uifs://") == 0)
   {

      return 1;

   }

   if(case_insensitive_ansi_compare(path,"uifs:/") == 0)
   {

      return 1;

   }

   if(case_insensitive_ansi_compare(path,"uifs:") == 0)
   {

      return 1;

   }

   defer_initialize();

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path.folder()];

   auto psystem = system();

   if(dir.m_timeLast.timeout(psystem->m_timeFileListingCache))
   {

      ::file::listing listing;

      listing.set_listing(path.folder());

      ::particle::directory()->enumerate(listing);

   }

   auto iFind = dir.case_insensitive_name_find_first(path.name());

   if(::not_found(iFind))
   {

      return 0;

   }

   return dir[iFind].m_etype & ::file::e_type_folder2;

}


bool ifs::file_move(const ::file::path & pathTarget,const ::file::path & pathSource)
{
   __UNREFERENCED_PARAMETER(pathTarget);
   __UNREFERENCED_PARAMETER(pathSource);
   return true;
}


file_pointer ifs::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
{

   auto pfile = __allocate ifs_file( payloadFile);

   //auto result =
   
   pfile->open(payloadFile, eopen, ppfileexception);

   //if(!result)
   //{

   //   return result;

   //}

   return pfile;

}


bool ifs::file_exists(const ::file::path & path)
{

   return ::fs::data::file_exists(path);

}


::payload ifs::file_length(const ::file::path & path)
{

   return ::fs::data::file_length(path);

}


void ifs::defer_initialize()
{

   if(!m_bInitialized)
   {


      m_bInitialized = true;

   }

}

bool ifs::is_zero_latency(const ::file::path & path)
{

   return false;

}
