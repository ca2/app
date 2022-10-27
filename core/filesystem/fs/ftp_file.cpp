#include "framework.h"
//#include "core/networking/ftp/_.h"
#include "ftp_file.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "core/networking/ftp/client_socket.h"
#include "ftpfs.h"



ftpfs_file::ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient) 
{

   m_pftp = pftp;

   m_pclient = pclient;

   m_payloadFile = m_pclient->m_pcontext->m_papexcontext->file().time(m_pclient->m_pcontext->m_papexcontext->dir().time());

}


void ftpfs_file::close()
{

   try
   {

      m_pfile->close();

   }
   catch(...)
   {


   }

   m_pfile.release();

   ::ftp::client_socket * pclient = m_pclient;

   int iTry = 0;

retry:

   if (iTry > 0)
   {

      m_pftp->defer_initialize(&pclient, m_filepath);

   }

   if (pclient->m_estate != ::ftp::client_socket::state_logged)
   {

      if (iTry > 3)
      {

         return;

      }

      iTry++;

      goto retry;

   }

   auto psystem = acmesystem()->m_papexsystem;

   auto purl = psystem->url();

   string strRemoteFile = purl->get_object(m_filepath);

   if (!pclient->UploadFile(m_payloadFile, strRemoteFile))
   {

      if (iTry > 3)
      {

         return;

      }

      pclient->m_estate = ::ftp::client_socket::e_state_initial;

      iTry++;

      goto retry;

   }


}

ftpfs_file::~ftpfs_file()
{


}


void ftpfs_file::open(const ::file::path & filepath, const ::file::e_open & eopen)
{

   m_filepath = filepath;

   return m_pfile->open(m_payloadFile, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_read_write | ::file::e_open_defer_create_directory);

}


memsize ftpfs_file::read(void *pdata, memsize nCount)

{

   return m_pfile->read(pdata, nCount);


}


void ftpfs_file::write(const void * pdata, memsize nCount)

{

   m_pfile->write(pdata, nCount);


}


filesize ftpfs_file::get_size() const
{

   return m_pfile->get_size();

}


filesize ftpfs_file::translate(filesize offset, ::enum_seek eseek)
{

   return m_pfile->translate(offset, eseek);

}


