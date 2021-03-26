#pragma once


class CLASS_DECL_CORE ftpfs_file :
   virtual public ::file::file
{
public:


   __pointer(ftpfs)                 m_pftp;
   file_pointer                     m_pfile;
   ::payload                        m_varFile;
   ::file::path                     m_filepath;
   __pointer(::ftp::client_socket)  m_pclient;


   // Download false
   // Create temp file and upload file on destruction
   ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient);
   virtual ~ftpfs_file();


   virtual ::extended::status open(const ::file::path & pszFileName, const ::file::e_open & eopen) override;


   virtual memsize read(void *pdata, memsize nCount) override;

   virtual void write(const void * pdata, memsize nCount) override;


   filesize seek(filesize lOff, ::file::e_seek  nFrom) override;

   virtual filesize get_size() const override;

   virtual void close() override;

};


