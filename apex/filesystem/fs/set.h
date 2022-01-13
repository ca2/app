#pragma once


namespace fs
{


   class CLASS_DECL_APEX set :
      virtual public ::fs::data
   {
   public:


      __pointer_array(data)               m_spafsdata;
      string_map < __pointer(data) >      m_fsdatamap;


      set();
      virtual ~set();


      string_map < __pointer(data) > & fsmap();
      __pointer_array(data) & fsa();


      virtual __pointer(data) path_data(const ::file::path & psz)override;
      virtual __pointer(data) node_path_data(const ::file::path & psz)override;
      virtual ::file::listing & root_ones(::file::listing & listing)override;
      virtual ::file::listing & ls(::file::listing & listing)override;
      virtual ::file::listing & ls_relative_name(::file::listing & listing)override;
      virtual int is_dir(const ::file::path & psz)override;
      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc)override;
      virtual bool has_subdir(const ::file::path & psz)override;
      virtual bool tree_show_subdir(const ::file::path & psz)override;
      virtual bool fast_has_subdir(const ::file::path & psz)override;
      virtual bool is_link(const ::file::path & psz)override;

      virtual file_pointer get_file(const ::file::path & path, const ::file::e_open & eopen) override;

      virtual bool is_zero_latency(const ::file::path & psz)override;

      virtual void destroy() override;


   };


} // namespace fs


