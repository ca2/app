#pragma once

//
//namespace zip
//{
//
//
//   class file;
//
//
//   class CLASS_DECL_APEX in_file:
//      virtual public ::file::file,
//      virtual public ::file::listing_provider
//   {
//   public:
//
//
//      enum e_mode
//      {
//
//         mode_undefined,
//         mode_zip,
//         mode_unzip
//
//      };
//
//      enum BufferCommand
//      {
//
//         bufferRead,
//         bufferWrite,
//         bufferCommit,
//         bufferCheck
//
//      };
//
//
//      void *                        m_punzfileinfo;
//      string                        m_strFileName;
//      u64                           m_iPosition;
//      string_array                       m_straPath;
//      __pointer_array(::zip::file)       m_filea;
//      __pointer_array(::zip::in_file)    m_infilea;
//      string_array                       m_straPrefix;
//      e_mode                        m_emode;
//      string                        m_strZipFile;
//
//
//      in_file();
//      virtual ~in_file();
//
//
//      virtual void assert_valid() const override;
//      virtual void dump(dump_context & dumpcontext) const override;
//
//
//
//
//      virtual filesize get_position() const override;
//
//      virtual bool zip_open(const char *,UINT);
//      virtual bool zip_open(::zip::file * pzfile,const char * pcszFileName);
//
//
//      virtual bool unzip_open(::file::file * pfile, const string_array & = {}, int iBufferLevel = 2, ::file::e_type * petype = nullptr);
//      virtual bool unzip_open(::zip::file * pzfile,const char * pcszFileName);
//
//      //virtual bool unzip_open(const char *, ::file::e_type * petype = nullptr);
//
//      virtual bool locate(const char * pszFileName);
//
//      virtual void add_file(const ::file::path & pszDir,const ::file::path & pszRelative);
//
//      bool dump(file_pointer pfile);
//
//      bool dump(memory & m);
//
//      ::zip::file * get_zip_file();
//      const ::zip::file * get_zip_file() const;
//
//      virtual filesize seek(filesize lOff,::file::e_seek nFrom) override;
//      virtual void set_size(filesize dwNewLen) override;
//      virtual filesize get_size() const override;
//
//      using ::file::file::read;
//      virtual memsize read(void * pdata,memsize nCount) override;
//
//
//      using ::file::file::write;
//      virtual void write(const void * pdata,memsize nCount) override;
//
//
//      //virtual void lock(filesize dwPos,filesize dwCount) override;
//      //virtual void unlock(filesize dwPos,filesize dwCount) override;
//
//      virtual void flush() override;
//      virtual void close() override;
//
//      virtual ::file::listing & ls(::file::listing & listing);
//      virtual ::file::listing & ls_relative_name(::file::listing & listing);
//
//
//      virtual bool is_opened() const override;
//
//
//      virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
//      virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;
//
//
//   };
//
//
//} // namespace zip
//
//
//
//
//
//
//
//
//
//
//
//
