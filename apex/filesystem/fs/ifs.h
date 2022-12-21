#pragma once


#include "data.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/collection/string_map.h"


// ifs - implementation of file system interface - file.ca2.software

class CLASS_DECL_APEX ifs :
   virtual public ::fs::data
{
public:


   string         m_strRoot;
   bool           m_bInitialized;
   string         m_strServer;


   class CLASS_DECL_APEX dir_listing :
      public ::file::listing
   {
   public:

      class ::time       m_timeLast;

   };


   string_map < dir_listing >    m_map;


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


   ifs( const ::scoped_string & scopedstrRoot);
   ~ifs() override;


   virtual bool has_subdir(const ::file::path & pszPath) override;
   virtual bool fast_has_subdir(const ::file::path  & pszPath) override;
   //virtual bool _enumerates(::file::listing & listing) override;
   virtual bool enumerate(::file::listing & listing) override;
   virtual int is_dir(const ::file::path & path) override;
   virtual ::file::listing & root_ones(::file::listing & listing) override;

   //virtual string file_name(const ::file::path & path);
   //virtual string dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2);

   virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc) override;

   virtual file_pointer get_file(const ::file::path & path, const ::file::e_open & eopen) override;

   virtual bool file_exists(const ::file::path & pszPath) override;
   virtual ::payload file_length(const ::file::path & pszPath) override;

   virtual void defer_initialize();

   virtual bool is_zero_latency(const ::file::path & psz) override;


};



