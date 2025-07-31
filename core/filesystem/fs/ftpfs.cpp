#include "framework.h"
#include "ftpnet.h"
#include "ftp_file.h"
#include "ftpfs.h"
#include "acme/prototype/prototype/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "core/platform/system.h"
#include "core/networking/ftp/file_status.h"
#include "core/networking/ftp/client_socket.h"
#include "core/networking/ftp/output.h"
#include "core/platform/application.h"


ftpfs::ftpfs()
{

}


ftpfs::~ftpfs()
{

   //::acme::del(m_pftpnet);

}


void ftpfs::initialize_ftpfs(::particle * pparticle, const ::scoped_string & scopedstrRoot)
{

   //auto estatus = 
   
   ::fs::data::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_strRoot = pszRoot;
   m_bInitialized = false;

   m_straFtpServer.add("localhost");

   //return estatus;

}


//
//void ftpfs::initialize(::particle * pparticle)
//{
//
//   auto estatus = __construct_new(this, m_pftpnet);
//
//   return estatus;
//
//}


bool ftpfs::fast_has_subdir(const ::file::path & path)
{

   synchronous_lock synchronouslock(this->synchronization());

   //   ::time tickTimeout;

   dir_listing & dir = m_map[path];

   auto psystem = system();

   if (dir.m_timeLast.elapsed() < psystem->m_timeFileListingCache)
   {

      return dir.get_count() > 0;

   }

   return true;

}


bool ftpfs::has_subdir(const ::file::path & path)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      dir_listing & dir = m_map[path];

      auto psystem = system();

      if (dir.m_timeLast.timeout(psystem->m_timeFileListingCache))
      {

         return dir.get_count() > 0;

      }

   }

   ::file::listing listing;

   listing.set_listing(path);

   enumerate(listing);

   return listing.get_count() > 0;

}


::file::listing & ftpfs::root_ones(::file::listing & listing)
{

   ::file::path path;

   path = "ftp://";

   path.set_existent_folder();

   listing.defer_add(path);

   listing.m_straTitle.add("FTP sites");

   return listing;

}


bool ftpfs::enumerate(::file::listing & listing)
{

   if (listing.m_pathUser == "ftp://")
   {

      for (auto strServer : m_straFtpServer)
      {

         string strUrl;

         strUrl = "ftp://" + strServer;

         ::file::path pathUrl;

         pathUrl = strUrl;

         auto & path = listing.add_get(pathUrl);

         path.set_existent_folder();

         listing.m_straTitle.add(strUrl);

      }

      return true;

   }

   {

      synchronous_lock synchronouslock(this->synchronization());

      dir_listing & dir = m_map[listing.m_pathUser];

      auto psystem = system();

      if (dir.m_timeLast.timeout(psystem->m_timeFileListingCache))
      {

         listing = dir;

         return true;

      }

   }

   listing.clear_results();


   //::file::path_array  straDir;
   //::file::path_array  straDirName;
   //::file::path_array  straFile;
   //::file::path_array  straFileName;
   //long_long_array    iaFileSize;
   //long_long_array    iaFolderSize;
   //bool_array     baFileDir;
   //bool_array     baFolderDir;

   //try
   //{

   //   defer_initialize();

   //}
   //catch (string & str)
   //{

   //   if (str == "You have not logged in! Exiting!")
   //   {

   //      throw ::exception(string("uftpfs:// You have not logged in!"));

   //   }

   //   dir.m_uiLsTimeout= ::time::now() + ((5000) * 4);

   //   listing = failure;

   //   return listing;

   //}

   ::ftp::file_status_ptra ptra;

   ::ftp::client_socket * pclient = nullptr;

   int iTry = 0;

retry:

   defer_initialize(&pclient, listing.m_pathUser);

   if (pclient->m_estate != ::ftp::client_socket::state_logged)
   {

      if (iTry > 3)
      {

         return listing;

      }

      iTry++;

      goto retry;

   }

   string strPath;

   auto psystem = system();

   auto purl = psystem->url();

   strPath = purl->get_string(listing.m_pathUser);

   if (!pclient->List(strPath, ptra, true))
   {

      if (iTry > 3)
      {

         return listing;

      }

      pclient->m_estate = ::ftp::client_socket::e_state_initial;

      iTry++;

      goto retry;

   }

   for (auto pchild : ptra)
   {

      if (!pchild->m_strAttributes.case_insensitive_contains("d"))
         continue;

      auto & path = listing.add_get(::file::path(::string(listing.m_pathUser / pchild->m_strName), ::e_path_url));

      path.set_existent_folder();

   }

   for (auto pchild : ptra)
   {

      if(!pchild->m_strAttributes.case_insensitive_contains("d"))
         continue;

      auto & path = listing.add_get(::file::path(::string(listing.m_pathUser / pchild->m_strName), ::e_path_url));

      path.m_iSize = pchild->m_filesize;

      path.set_existent_file();

   }

   {

      synchronous_lock synchronouslock(this->synchronization());

      dir_listing & dir = m_map[listing.m_pathUser];

      ((::file::listing &)dir) = listing;

      dir.m_timeLast.Now();

   }

   return listing;

}


::file::e_type ftpfs::file_type(const ::file::path & path)
{

   if (path.is_empty())
   {

      return ::file::e_type_existent_folder;

   }

   if (case_insensitive_ansi_compare(path, "ftp://") == 0)
   {

      return ::file::e_type_existent_folder;

   }

   if (case_insensitive_ansi_compare(path, "ftp:/") == 0)
   {

      return ::file::e_type_existent_folder;

   }

   if (case_insensitive_ansi_compare(path, "ftp:") == 0)
   {

      return ::file::e_type_existent_folder;

   }

   string strPath = path;

   if (strPath.case_insensitive_begins_eat("ftp://"))
   {

      strPath.ends_eat("/");

      if(m_straFtpServer.case_insensitive_contains(strPath))
      {

         return ::file::e_type_existent_folder;

      }

   }


   //defer_initialize();


   //::time tickTimeout;

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path.folder()];

   auto psystem = system();

   if (dir.m_timeLast.elapsed() > psystem->m_timeFileListingCache)
   {

      ::file::listing listing;

      listing.set_listing(path.folder());

      enumerate(listing);

   }

   auto iFind = dir.case_insensitive_name_find_first(path.name());

   if (::not_found(iFind))
   {

      return ::file::e_type_doesnt_exist;

   }

   return dir[iFind].type();


}


bool ftpfs::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
{
   __UNREFERENCED_PARAMETER(scopedstrDst);
   __UNREFERENCED_PARAMETER(scopedstrSrc);
   return true;
}


file_pointer ftpfs::get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception)
{

   if (is_dir(payloadFile))
   {

      return nullptr;

   }

   if (eopen & ::file::e_open_read && !(eopen & ::file::e_open_write))
   {

      ::ftp::client_socket * pclient = nullptr;

      int iTry = 0;

retry:

      defer_initialize(&pclient, payloadFile);

      if (pclient->m_estate != ::ftp::client_socket::state_logged)
      {

         if (iTry > 3)
         {

            return nullptr;

         }

         iTry++;

         goto retry;

      }

      ::file::path pathTemp = file()->time(directory()->time());

      auto psystem = system();

      auto purl = psystem->url();

      string strRemoteFile = purl->get_string(payloadFile);

      if (!pclient->DownloadFile(strRemoteFile, pathTemp))
      {

         if (iTry > 3)
         {

            return nullptr;

         }

         pclient->m_estate = ::ftp::client_socket::e_state_initial;

         iTry++;

         goto retry;

      }

      return file()->get_file(pathTemp, eopen);

   }
   else
   {

      ::ftp::client_socket * pclient = nullptr;

      defer_initialize(&pclient, payloadFile);

      file_pointer spfile;

      spfile = __allocate ftpfs_file(this, pclient);

      //auto result = 
      
      spfile->open(payloadFile, eopen);

      //if (!result)
      //{

      //   return result;

      //}

      return spfile;

   }

}


bool ftpfs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(scopedstrPath);

}


::payload ftpfs::file_length(const ::file::path & pszPath)
{

   return ::fs::data::file_length(scopedstrPath);

}


void ftpfs::defer_initialize(::ftp::client_socket ** ppclient, string strPath)
{

   auto plogon = __allocate ::ftp::logon();

   auto psystem = system();

   auto purl = psystem->url();

   plogon->Hostname() = ::url::get_host(strPath);
   //logon.Username() = purl->get_username(listing.m_path);

   string strUrl = "ftp://" + plogon->Hostname() + "/";

   //plogon->m_strToken = purl->os_fspath(strUrl);

   ::pointer<::ftp::client_socket>& pclient = m_pftpnet->m_mapClient[plogon->m_strToken];

   int iTry = 0;

   auto papp = m_papplication->m_papplication;

   if (!pclient)
   {

      pclient = __allocate ::ftp::client_socket();

      //pclient->initialize_socket(m_pftpnet->m_psockethandler);

      ::pointer<::ftp::output>& poutput = m_pftpnet->m_mapOutput[plogon->m_strToken];

      poutput = __allocate ::ftp::output();

      pclient->AttachObserver(poutput);

      m_pftpnet->m_psockethandler->add(pclient);

   }

   *ppclient = pclient.m_p;

   if (pclient->m_estate == ::ftp::client_socket::e_state_initial || !pclient->IsConnected())
   {

retry:

      ::cast < ::account::interactive > paccountinteractive = papp;

      paccountinteractive->interactive_credentials(plogon);

retry_login:

      if (!pclient->Login(plogon))
      {

         if (plogon->m_bFailedBecauseOfSecurityLevelCanUpgrade)
         {

            goto retry_login;

         }

         plogon->save_to_storage();

         if (iTry > 3)
         {

            pclient->m_estate = ::ftp::client_socket::e_state_initial;

            return;

         }

         iTry++;

         goto retry;

      }

      //papp->set_cred(strToken, logon.Username(), logon.Password());

      plogon->save_status_to_storage(::success);

   }

   pclient->m_estate = ::ftp::client_socket::state_logged;

   //  \
   //   \
   //    }=====> Elegant code.
   //   /
   //  /

}

bool ftpfs::is_zero_latency(const ::file::path & psz)
{

   return false;

}
