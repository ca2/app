#pragma once


#include "apex/primitive/data/_.h"


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_APEX data :
      virtual public ::object,
      virtual public ::data::data,
      virtual public ::file::listing_provider
   {
   public:


      data();


      virtual void assert_valid() const;
      virtual void dump(dump_context& dumpcontext) const;


      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath);
      virtual ::file::listing & ls(::file::listing & listing);
      virtual ::file::listing & ls_relative_name(::file::listing & listing);
      virtual int is_dir(const ::file::path & pszPath);
      virtual ::file::listing & root_ones(::file::listing & listing);


      virtual bool tree_show_subdir(const ::file::path & pszPath);


      virtual bool file_exists(const ::file::path & pszPath);
      virtual var file_length(const ::file::path & pszPath);


      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

      virtual file_result get_file(const ::file::path & path, UINT nOpenFlags);


      virtual bool fast_has_subdir(const ::file::path & pszPath);

      virtual __pointer(data) path_data(const ::file::path & psz);
      virtual __pointer(data) node_path_data(const ::file::path & psz);


      virtual bool is_link(const ::file::path & psz);

      virtual bool is_zero_latency(const ::file::path & psz);


      virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
      virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;


   };


} // namespace fs








