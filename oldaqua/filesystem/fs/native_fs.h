#pragma once


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_AQUA native :
      virtual public ::fs::data
   {
   public:


      native();
      virtual ~native();


      virtual ::file::listing & ls(::file::listing & listing) override;
      virtual ::file::listing & ls_relative_name(::file::listing & listing) override;


      virtual bool is_link(const ::file::path & path) override;

      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing & root_ones(::file::listing & listing) override;

      virtual bool file_exists(const ::file::path & pszPath) override;

      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc) override;

      virtual file_result get_file(const ::file::path & path, UINT nOpenFlags) override;


   };


} // namespace fs



