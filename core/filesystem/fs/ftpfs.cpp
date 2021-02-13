#include "framework.h"
#include "core/net/ftp/_.h"
#include "apex/filesystem/fs/_fs.h"
#include "ftp_net.h"
#include "ftp_file.h"



ftpfs::ftpfs()
{

}


::e_status ftpfs::initialize_ftpfs(::layered * pobjectContext, const char * pszRoot)
{

   auto estatus = ::fs::data::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   m_strRoot = pszRoot;
   m_bInitialized = false;

   m_straFtpServer.add("localhost");

   return estatus;

}


ftpfs::~ftpfs()
{

   //::acme::del(m_pftpnet);

}

//
//::e_status ftpfs::initialize(::layered * pobjectContext)
//{
//
//   auto estatus = __compose_new(this, m_pftpnet);
//
//   return estatus;
//
//}


bool ftpfs::fast_has_subdir(const ::file::path & path)
{

   synchronization_lock synchronizationlock(mutex());

   //   millis tickTimeout;

   dir_listing & dir = m_map[path];

   if (dir.m_millisLast.elapsed() < ::get_context_system()->m_millisFileListingCache)
   {

      return dir.get_count() > 0;

   }

   return true;

}


bool ftpfs::has_subdir(const ::file::path & path)
{

   {

      synchronization_lock synchronizationlock(mutex());

      dir_listing & dir = m_map[path];

      if (dir.m_millisLast.timeout(::get_context_system()->m_millisFileListingCache))
      {

         return dir.get_count() > 0;

      }

   }

   ::file::listing listing;

   listing.m_pathUser = path;

   ls(listing);

   return listing.get_count() > 0;

}


::file::listing & ftpfs::root_ones(::file::listing & listing)
{

   ::file::path path;

   path = "ftp://";

   listing.add(path);

   listing.m_straTitle.add("FTP sites");

   return listing;

}


::file::listing & ftpfs::ls(::file::listing & listing)
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

      return listing;

   }

   {

      synchronization_lock synchronizationlock(mutex());

      dir_listing & dir = m_map[listing.m_pathUser];

      if (dir.m_millisLast.timeout(::get_context_system()->m_millisFileListingCache))
      {

         listing = dir;

         return listing;

      }

   }

   listing.clear_results();


   //::file::patha  straDir;
   //::file::patha  straDirName;
   //::file::patha  straFile;
   //::file::patha  straFileName;
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

   //      __throw(string("uftpfs:// You have not logged in!"));

   //   }

   //   dir.m_uiLsTimeout= ::millis::now() + ((5000) * 4);

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

         return listing = ::error_failed;

      }

      iTry++;

      goto retry;

   }

   string strPath;

   strPath = System.url().get_object(listing.m_pathUser);

   if (!pclient->List(strPath, ptra, true))
   {

      if (iTry > 3)
      {

         return listing = ::error_failed;

      }

      pclient->m_estate = ::ftp::client_socket::e_state_initial;

      iTry++;

      goto retry;

   }

   for (auto pchild : ptra.ptra())
   {

      if (pchild->m_strAttributes.find_ci("d") < 0)
         continue;

      auto & path = listing.add_get(::file::path(listing.m_pathUser / pchild->m_strName, ::file::path_url));

      path.m_iDir = 1;

   }

   for (auto pchild : ptra.ptra())
   {

      if (pchild->m_strAttributes.find_ci("d") >= 0)
         continue;

      auto & path = listing.add_get(::file::path(listing.m_pathUser / pchild->m_strName, ::file::path_url));

      path.m_iSize = pchild->m_filesize;

      path.m_iDir = 0;

   }

   {

      synchronization_lock synchronizationlock(mutex());

      dir_listing & dir = m_map[listing.m_pathUser];

      ((::file::listing &)dir) = listing;

      dir.m_millisLast.Now();

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

   if (::str::begins_eat_ci(strPath, "ftp://"))
   {

      ::str::ends_eat(strPath, "/");

      if(m_straFtpServer.contains_ci(strPath))
      {

         return 1;

      }

   }


   //defer_initialize();


   //millis tickTimeout;

   synchronization_lock synchronizationlock(mutex());

   dir_listing & dir = m_map[path.folder()];

   if (dir.m_millisLast.elapsed() > ::get_context_system()->m_millisFileListingCache)
   {

      ::file::listing listing;

      listing.m_pathUser = path.folder();

      ls(listing);

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
   UNREFERENCED_PARAMETER(pszDst);
   UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


file_result ftpfs::get_file(const ::file::path & path, const ::file::e_open & eopen)
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

      ::file::path pathTemp = get_context()->file().time(get_context()->dir().time());

      string strRemoteFile = System.url().get_object(path);

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

      return get_context()->file().get_file(pathTemp, eopen);

   }
   else
   {

      ::ftp::client_socket * pclient = nullptr;

      defer_initialize(&pclient, path);

      file_pointer spfile;

      spfile = __new(ftpfs_file(this, pclient));

      auto result = spfile->open(path, eopen);

      if (!result)
      {

         return result;

      }

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

   plogon->Hostname() = System.url().get_server(strPath);
   //logon.Username() = System.url().get_username(listing.m_path);

   string strUrl = "ftp://" + plogon->Hostname() + "/";

   plogon->m_strToken = System.url().os_fspath(strUrl);

   __pointer(::ftp::client_socket) & pclient = m_pftpnet->m_mapClient[plogon->m_strToken];

   int iTry = 0;

   if (!pclient)
   {

      pclient = __new(::ftp::client_socket(m_pftpnet->m_sockethandler));

      __pointer(::ftp::output) & poutput = m_pftpnet->m_mapOutput[plogon->m_strToken];

      poutput = __new(::ftp::output());

      pclient->AttachObserver(poutput);

   }

   *ppclient = pclient.m_p;

   if (pclient->m_estate == ::ftp::client_socket::e_state_initial || !pclient->IsConnected())
   {

retry:

      Application.interactive_credentials(plogon);

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

      //Application.set_cred(strToken, logon.Username(), logon.Password());

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
