#pragma once


#include "data.h"
#include "acme/primitive/collection/strid_map.h"


namespace fs
{


   // fs::interface - file system interface access to remote file system through account proxy


   class CLASS_DECL_APEX remote_native :
      virtual public ::fs::data
   {
   public:


      string                              m_strRoot;
      bool                                m_bInitialized;


      string_map < class ::time >              m_mapdirLast;
      string_map < class ::time >              m_mapfileLast;


      remote_native(const ::scoped_string & scopedstrRoot);
      ~remote_native() override;


      //virtual bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing & listing) override;


      virtual bool has_subdir(const ::file::path & pszPath) override;
      virtual bool fast_has_subdir(const ::file::path & pszPath) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing & root_ones(::file::listing & listing) override;

      //virtual string file_name(const ::file::path & path);
      //virtual string dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2);

      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc) override;

      virtual file_pointer get_file(const ::file::path & path, ::file::e_open eopen) override;

      virtual bool file_exists(const ::file::path & pszPath) override;

      virtual void defer_initialize();

      virtual bool is_zero_latency(const ::file::path & psz) override;


   };


} // namespace fs






