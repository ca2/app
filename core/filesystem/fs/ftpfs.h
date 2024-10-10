#pragma once


#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/collection/string_map.h"
#include "apex/filesystem/fs/data.h"


// ifs - implementation of file system interface - file.ca2.software

class ftpnet;

namespace ftp
{

   class client_socket;

}


class CLASS_DECL_CORE ftpfs :
   virtual public ::fs::data
{
public:


   class CLASS_DECL_CORE dir_listing :
      public ::file::listing
   {
   public:

      class ::time                      m_timeLast;

   };


   string                           m_strRoot;
   bool                             m_bInitialized;
   string                           m_strServer;

   string_array                     m_straFtpServer;

   ::pointer<ftpnet>             m_pftpnet;



   string_map < dir_listing >       m_map;


   //file_path_map < u32 >    m_mapdirTimeout;
   //file_path_map < u32 >    m_mapfileTimeout;
   //file_path_map < u32 >    m_maplsTimeout;
   //filepathmap(::file::path_array)    m_mapdirFile;
   //filepathmap(::file::path_array)    m_mapdirFolder;
   //filepathmap(::file::path_array)    m_mapdirFileName;
   //filepathmap(::file::path_array)    m_mapdirFolderName;
   //filepathmap(i64_array)      m_mapdirFileSize;
   //filepathmap(i64_array)      m_mapdirFolderSize; // by now, always store item count?
   //filepathmap(bool_array)       m_mapdirFileDir;
   //filepathmap(bool_array)       m_mapdirFolderDir; // by now, always store item count?


   ftpfs();
   ~ftpfs() override;


   virtual void initialize_ftpfs(::particle * pparticle, const ::string & pszRoot);


   virtual bool has_subdir(const ::file::path & pszPath) override;
   virtual bool fast_has_subdir(const ::file::path  & pszPath) override;
   virtual bool enumerate(::file::listing & listing) override;
   ::file::e_type file_type(const ::file::path & path) override;
   virtual ::file::listing & root_ones(::file::listing & listing) override;

   virtual void defer_initialize(::ftp::client_socket ** client, string strPath);

   //virtual string file_name(const ::string & pszPath);
   //virtual string dir_path(const ::string & psz1, const ::string & psz2);

   virtual bool file_move(const ::file::path & pszDst, const ::file::path & pszSrc) override;

   virtual file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception = nullptr) override;

   virtual bool file_exists(const ::file::path & pszPath) override;
   virtual ::payload file_length(const ::file::path & pszPath) override;

   virtual bool is_zero_latency(const ::file::path & psz) override;

};

