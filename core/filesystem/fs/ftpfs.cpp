#include "framework.h"
#include "ftpnet.h"
#include "ftp_file.h"
#include "ftpfs.h"
#include "acme/primitive/primitive/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/data/listener.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
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


void ftpfs::initialize_ftpfs(::particle * pparticle, const ::string & pszRoot)
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

   auto psystem = acmesystem()->m_pcoresystem;

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

      auto psystem = acmesystem();

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

   path.m_iDir = 1;

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

         path.m_iDir = 1;

         listing.m_straTitle.add(strUrl);

      }

      return true;

   }

   {

      synchronous_lock synchronouslock(this->synchronization());

      dir_listing & dir = m_map[listing.m_pathUser];

      auto psystem = acmesystem()->m_paurasystem;

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
   //i64_array    iaFileSize;
   //i64_array    iaFolderSize;
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

   auto psystem = acmesystem()->m_paurasystem;

   auto purl = psystem->url();

   strPath = purl->get_object(listing.m_pathUser);

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

   for (auto pchild : ptra.ptra())
   {

      if (pchild->m_strAttributes.case_insensitive_find("d") < 0)
         continue;

      auto & path = listing.add_get(::file::path(listing.m_pathUser / pchild->m_strName, ::e_path_url));

      path.m_iDir = 1;

   }

   for (auto pchild : ptra.ptra())
   {

      if (pchild->m_strAttributes.case_insensitive_find("d") >= 0)
         continue;

      auto & path = listing.add_get(::file::path(listing.m_pathUser / pchild->m_strName, ::e_path_url));

      path.m_iSize = pchild->m_filesize;

      path.m_iDir = 0;

   }

   {

      synchronous_lock synchronouslock(this->synchronization());

      dir_listing & dir = m_map[listing.m_pathUser];

      ((::file::listing &)dir) = listing;

      dir.m_timeLast.Now();

   }

   return listing;

}


int ftpfs::is_dir(const ::file::path & path)
{

   if (path.is_empty())
   {

      return 1;

   }

   if (ansi_compare_ci(path, "ftp://") == 0)
   {

      return 1;

   }

   if (ansi_compare_ci(path, "ftp:/") == 0)
   {

      return 1;

   }

   if (ansi_compare_ci(path, "ftp:") == 0)
   {

      return 1;

   }

   string strPath = path;

   if (strPath.case_insensitive_begins_eat("ftp://"))
   {

      strPath.ends_eat("/");

      if(m_straFtpServer.contains_ci(strPath))
      {

         return 1;

      }

   }


   //defer_initialize();


   //::time tickTimeout;

   synchronous_lock synchronouslock(this->synchronization());

   dir_listing & dir = m_map[path.folder()];

   auto psystem = acmesystem()->m_pcoresystem;

   if (dir.m_timeLast.elapsed() > psystem->m_timeFileListingCache)
   {

      ::file::listing listing;

      listing.set_listing(path.folder());

      enumerate(listing);

   }

   auto iFind = dir.name_find_first_ci(path.name());

   if (iFind < 0)
   {

      return 0;

   }

   return dir[iFind].m_iDir;


}


bool ftpfs::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
{
   __UNREFERENCED_PARAMETER(pszDst);
   __UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


file_pointer ftpfs::get_file(const ::file::path & path, const ::file::e_open & eopen)
{

   if (is_dir(path))
   {

      return nullptr;

   }

   if (eopen & ::file::e_open_read && !(eopen & ::file::e_open_write))
   {

      ::ftp::client_socket * pclient = nullptr;

      int iTry = 0;

retry:

      defer_initialize(&pclient, path);

      if (pclient->m_estate != ::ftp::client_socket::state_logged)
      {

         if (iTry > 3)
         {

            return nullptr;

         }

         iTry++;

         goto retry;

      }

      ::file::path pathTemp = file()->time(dir()->time());

      auto psystem = acmesystem()->m_papexsystem;

      auto purl = psystem->url();

      string strRemoteFile = purl->get_object(path);

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

      defer_initialize(&pclient, path);

      file_pointer spfile;

      spfile = __new(ftpfs_file(this, pclient));

      //auto result = 
      
      spfile->open(path, eopen);

      //if (!result)
      //{

      //   return result;

      //}

      return spfile;

   }

}


bool ftpfs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


::payload ftpfs::file_length(const ::file::path & pszPath)
{

   return ::fs::data::file_length(pszPath);

}


void ftpfs::defer_initialize(::ftp::client_socket ** ppclient, string strPath)
{

   auto plogon = __new(::ftp::logon);

   auto psystem = acmesystem()->m_pcoresystem;

   auto purl = psystem->url();

   plogon->Hostname() = purl->get_server(strPath);
   //logon.Username() = purl->get_username(listing.m_path);

   string strUrl = "ftp://" + plogon->Hostname() + "/";

   plogon->m_strToken = purl->os_fspath(strUrl);

   ::pointer<::ftp::client_socket>& pclient = m_pftpnet->m_mapClient[plogon->m_strToken];

   int iTry = 0;

   auto papp = m_pcontext->m_pacmeapplication->m_pcoreapplication;

   if (!pclient)
   {

      pclient = __new(::ftp::client_socket);

      pclient->initialize_socket(m_pftpnet->m_psockethandler);

      ::pointer<::ftp::output>& poutput = m_pftpnet->m_mapOutput[plogon->m_strToken];

      poutput = __new(::ftp::output());

      pclient->AttachObserver(poutput);

   }

   *ppclient = pclient.m_p;

   if (pclient->m_estate == ::ftp::client_socket::e_state_initial || !pclient->IsConnected())
   {

retry:

      papp->interactive_credentials(plogon);

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
