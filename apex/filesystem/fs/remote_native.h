#pragma once


#include "data.h"
#include "acme/prototype/collection/strid_map.h"


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


      //virtual bool _enumerates(::file::listing_base & listing) override;
      bool enumerate(::file::listing_base & listing) override;


      virtual bool has_subdir(const ::file::path & path) override;
      virtual bool fast_has_subdir(const ::file::path & path) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing_base & root_ones(::file::listing_base & listing) override;

      //virtual string file_name(const ::file::path & path);
      //virtual string dir_path(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2);

      virtual bool file_move(const ::file::path & pathTarget,const ::file::path & pathSource) override;

      virtual file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;

      virtual bool file_exists(const ::file::path & path) override;

      virtual void defer_initialize();

      virtual bool is_zero_latency(const ::file::path & path) override;


   };


} // namespace fs






