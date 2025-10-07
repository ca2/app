#pragma once


#include "data.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/collection/string_map.h"


// ifs - implementation of file system interface - file.ca2.network

class CLASS_DECL_APEX ifs :
   virtual public ::fs::data
{
public:


   string         m_strRoot;
   bool           m_bInitialized;
   string         m_strServer;


   class CLASS_DECL_APEX dir_listing :
      public ::file::listing_base
   {
   public:

      class ::time       m_timeLast;

   };


   string_map_base < dir_listing >    m_map;


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


   ifs( const ::scoped_string & scopedstrRoot);
   ~ifs() override;


   virtual bool has_subdir(const ::file::path & path) override;
   virtual bool fast_has_subdir(const ::file::path  & pszPath) override;
   //virtual bool _enumerates(::file::listing_base & listing) override;
   virtual bool enumerate(::file::listing_base & listing) override;
   virtual int is_dir(const ::file::path & path) override;
   virtual ::file::listing_base & root_ones(::file::listing_base & listing) override;

   //virtual string file_name(const ::file::path & path);
   //virtual string dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2);

   virtual bool file_move(const ::file::path & pathTarget,const ::file::path & pathSource) override;

   ::file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;

   virtual bool file_exists(const ::file::path & path) override;
   virtual ::payload file_length(const ::file::path & path) override;

   virtual void defer_initialize();

   virtual bool is_zero_latency(const ::file::path & path) override;


};



