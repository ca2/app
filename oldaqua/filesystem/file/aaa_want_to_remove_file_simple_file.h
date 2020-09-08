#pragma once

//
//namespace file
//{
//
//
//   class exception;
//   struct file_status;
//
//
//   class CLASS_DECL_AQUA simple_file :
//      virtual public ::file::file
//   {
//   public:
//
//
//      FILE *         m_pfile;
//      string         m_strFileName;
//
//
//      simple_file(::object * pobject);
//      virtual ~simple_file();
//
//
//      virtual void assert_valid() const override;
//      virtual void dump(dump_context & dumpcontext) const override;
//
//
//
//      virtual filesize get_position() const override;
//      virtual bool GetStatus(file_status& rStatus) const override;
//      virtual string GetFileName() const override;
//      virtual string GetFileTitle() const override;
//      virtual string GetFilePath() const override;
//      virtual void SetFilePath(const char * pszNewName) override;

//
//
//      // Operations
//      virtual bool open(const ::file::path & pszFileName,UINT nOpenFlags, ::status::result * pres = NULL) override;

//
//      //virtual void Rename(const char * pszOldName, const char * pszNewName);

//      //virtual void remove(const char * pszFileName);

//      //virtual bool GetStatus(const char * pszFileName, file_status& rStatus);

//      //virtual void SetStatus(const char * pszFileName, const file_status& status);

//
//
//      // Overridables
//      virtual file_pointer  Duplicate() const override;
//
//      virtual filesize seek(filesize lOff, ::file::e_seek  nFrom) override;
//      virtual void set_length(filesize dwNewLen) override;
//      virtual filesize get_length() const override;
//
//      virtual void LockRange(filesize dwPos, filesize dwCount) override;
//      virtual void UnlockRange(filesize dwPos, filesize dwCount) override;
//
//      virtual void Abort() override;
//      virtual void flush() override;
//      virtual void close() override;
//
//
//      // io_stream
//      virtual memsize read(void *pdata, memsize nCount) override;

//      virtual void write(const void * pdata, memsize nCount) override;

//      virtual string get_location() const override;
//
//
//      virtual bool IsOpened() override;
//
//      //virtual u64 GetBufferPtr(UINT nCommand, u64 nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);
//
//
//
//      using ::file::file::write;
//      void write(stream & ostream);
//
//
//      using ::file::file::read;
//      void read(stream & istream);
//
//
//      //virtual bool read_string(string & str);
//
//      virtual void write_string(const char * psz);

//      virtual LPTSTR read_string(LPTSTR psz, UINT nMax);

//      virtual bool read_string(string & rString) override;
//
//   };
//
//
//   void CLASS_DECL_AQUA throw_exception(::object * pobject, ::estatus cause,LONG lOsError,const char * pszFileName = NULL);

//
//} // namespace file
//
//
//
//
//
//
