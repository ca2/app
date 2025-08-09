#pragma once


#include "data.h"
#include "acme/filesystem/filesystem/enumerator.h"
#include "acme/prototype/collection/string_map.h"


namespace fs
{


   class CLASS_DECL_APEX set :
      virtual public ::fs::data,
      virtual public ::file::enumerator
   {
   public:


      pointer_array < data >               m_spafsdata;
      string_map < ::pointer<data >>     m_fsdatamap;


      set();
      ~set() override;


      string_map < ::pointer<data >>& fsmap();
      pointer_array < data > & fsa();


      virtual ::pointer<data>path_data(const ::payload & payloadFile)override;
      virtual ::pointer<data>node_path_data(const ::file::path & path)override;
      virtual ::file::listing_base & root_ones(::file::listing_base & listing)override;
      //virtual bool _enumerates(::file::listing_base & listing)override;
      virtual bool enumerate(::file::listing_base & listing)override;
      //virtual ::file::listing_base & ls_relative_name(::file::listing_base & listing)override;
      virtual int is_dir(const ::file::path & path)override;
      virtual ::file::e_type file_type(const ::file::path& path)override;
      virtual bool file_move(const ::file::path & pathTarget,const ::file::path & pathSource)override;
      virtual bool has_subdir(const ::file::path & path)override;
      virtual bool tree_show_subdir(const ::file::path & path)override;
      virtual bool fast_has_subdir(const ::file::path & path)override;
      virtual bool is_link(const ::file::path & path)override;

      virtual file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;

      virtual bool is_zero_latency(const ::file::path & path)override;

      virtual void destroy() override;


   };


} // namespace fs


