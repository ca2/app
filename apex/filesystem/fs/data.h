#pragma once


#include "acme/primitive/data/data.h"
#include "acme/filesystem/filesystem/enumerator.h"


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_APEX data :
      virtual public ::data::data,
      virtual public ::file::enumerator
   {
   public:


      data();


      // void assert_ok() const override;
      // virtual void dump(dump_context& dumpcontext) const override;


      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath);
      //virtual bool _enumerates(::file::listing & listing) override;
      virtual bool enumerate(::file::listing & listing) override;
      //virtual ::file::listing & ls_relative_name(::file::listing & listing);
      virtual int is_dir(const ::file::path & pszPath);
      virtual ::file::listing & root_ones(::file::listing & listing);


      virtual bool tree_show_subdir(const ::file::path & pszPath);


      virtual bool file_exists(const ::file::path & pszPath);
      virtual ::payload file_length(const ::file::path & pszPath);


      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

      virtual file_pointer get_file(const ::file::path & path, const ::file::e_open & eopen);


      virtual bool fast_has_subdir(const ::file::path & pszPath);

      virtual ::pointer<data>path_data(const ::file::path & psz);
      virtual ::pointer<data>node_path_data(const ::file::path & psz);


      virtual bool is_link(const ::file::path & psz);

      virtual bool is_zero_latency(const ::file::path & psz);


      //bool _enumerate(::file::listing & listing) override;
      //virtual bool perform_file_relative_name_listing(::file::listing & listing) override;


   };


} // namespace fs








