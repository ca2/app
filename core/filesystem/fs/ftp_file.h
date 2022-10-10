#pragma once


class CLASS_DECL_CORE ftpfs_file :
   virtual public ::file::file
{
public:


   ::pointer<ftpfs>                m_pftp;
   file_pointer                     m_pfile;
   ::payload                        m_payloadFile;
   ::file::path                     m_filepath;
   ::pointer<::ftp::client_socket> m_pclient;


   // Download false
   // Create temp file and upload file on destruction
   ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient);
   ~ftpfs_file() override;


   //::extended::status open(const ::file::path & path, const ::file::e_open & eopen) override;

   void open(const ::file::path& path, const ::file::e_open& eopen) override;

   memsize read(void *pdata, memsize nCount) override;

   void write(const void * pdata, memsize nCount) override;

   filesize translate(filesize offset, ::enum_seek eseek) override;

   filesize get_size() const override;

   void close() override;


};



