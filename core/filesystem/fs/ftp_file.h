#pragma once


#include "acme/filesystem/file/file.h"


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

   void open(const ::file::path & pszFileName, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;

   
   using ::file::file::read;
   memsize read(void * p, ::memsize s) override;

   
   using ::file::file::write;
   void write(const void * p, ::memsize s) override;


   void translate(filesize offset, ::enum_seek eseek) override;

   filesize size() const override;

   void close() override;


};



