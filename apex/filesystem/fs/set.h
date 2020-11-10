#pragma once


namespace fs
{


   class CLASS_DECL_APEX set :
      virtual public ::fs::data
   {
   public:


      __pointer_array(data)              m_spafsdata;
      strsp(data)                   m_fsdatamap;


      set();
      virtual ~set();


      strsp(data) &                 fsmap();
      __pointer_array(data) &                   fsa();


      virtual __pointer(data) path_data(const ::file::path & psz);
      virtual __pointer(data) node_path_data(const ::file::path & psz);
      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual ::file::listing & ls(::file::listing & listing);
      virtual ::file::listing & ls_relative_name(::file::listing & listing);
      virtual int is_dir(const ::file::path & psz);
      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);
      virtual bool has_subdir(const ::file::path & psz);
      virtual bool tree_show_subdir(const ::file::path & psz);
      virtual bool fast_has_subdir(const ::file::path & psz);
      virtual bool is_link(const ::file::path & psz);

      virtual file_result get_file(const ::file::path & path, ::u32 nOpenFlags);

      virtual bool is_zero_latency(const ::file::path & psz);

      virtual void finalize() override;


   };


} // namespace fs


