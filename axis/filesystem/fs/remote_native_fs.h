#pragma once


namespace fs
{


   // fs::interface - file system interface access to remote file system through account proxy


   class CLASS_DECL_AURA remote_native :
      virtual public ::fs::data
   {
   public:


      string                              m_strRoot;
      bool                                m_bInitialized;


      file_path_map < tick >              m_mapdirTimeout;
      file_path_map < tick >              m_mapfileTimeout;


      remote_native(const char * pszRoot);
      virtual ~remote_native();


      virtual ::file::listing & ls(::file::listing & listing) override;


      virtual bool has_subdir(const ::file::path & pszPath) override;
      virtual bool fast_has_subdir(const ::file::path & pszPath) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing & root_ones(::file::listing & listing) override;

      //virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc) override;

      virtual file_result get_file(const ::file::path & path, UINT nOpenFlags) override;

      virtual bool file_exists(const ::file::path & pszPath) override;

      virtual void defer_initialize();

      virtual bool is_zero_latency(const ::file::path & psz) override;


   };


} // namespace fs






