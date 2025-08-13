#pragma once


#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/collection/string_map.h"
#include "apex/filesystem/fs/data.h"


// ifs - implementation of file system interface - file.ca2.network

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
      public ::file::listing_base
   {
   public:

      class ::time                      m_timeLast;

   };


   string                           m_strRoot;
   bool                             m_bInitialized;
   string                           m_strServer;

   string_array_base                     m_straFtpServer;

   ::pointer<ftpnet>             m_pftpnet;



   string_map_base < dir_listing >       m_map;


   //file_path_map < unsigned int >    m_mapdirTimeout;
   //file_path_map < unsigned int >    m_mapfileTimeout;
   //file_path_map < unsigned int >    m_maplsTimeout;
   //filepathmap(::file::path_array_base)    m_mapdirFile;
   //filepathmap(::file::path_array_base)    m_mapdirFolder;
   //filepathmap(::file::path_array_base)    m_mapdirFileName;
   //filepathmap(::file::path_array_base)    m_mapdirFolderName;
   //filepathmap(long_long_array_base)      m_mapdirFileSize;
   //filepathmap(long_long_array_base)      m_mapdirFolderSize; // by now, always store item count?
   //filepathmap(bool_array)       m_mapdirFileDir;
   //filepathmap(bool_array)       m_mapdirFolderDir; // by now, always store item count?


   ftpfs();
   ~ftpfs() override;


   virtual void initialize_ftpfs(::particle * pparticle, const ::scoped_string & scopedstrRoot);


   virtual bool has_subdir(const ::file::path & path) override;
   virtual bool fast_has_subdir(const ::file::path  & pszPath) override;
   virtual bool enumerate(::file::listing_base & listing) override;
   ::file::e_type file_type(const ::file::path & path) override;
   virtual ::file::listing_base & root_ones(::file::listing_base & listing) override;

   virtual void defer_initialize(::ftp::client_socket ** client, const ::scoped_string & scopedstrPath);

   //virtual string file_name(const ::scoped_string & scopedstrPath);
   //virtual string dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2);

   virtual bool file_move(const ::file::path & pathTarget, const ::file::path & pathSource) override;

   virtual file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception = nullptr) override;

   virtual bool file_exists(const ::file::path & path) override;
   virtual ::payload file_length(const ::file::path & path) override;

   virtual bool is_zero_latency(const ::file::path & path) override;

};

