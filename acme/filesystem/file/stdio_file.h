#pragma once


class CLASS_DECL_ACME stdio_file:
   virtual public ::file::file
{
public:


   FILE *         m_pfile;
   string         m_strFileName;


   stdio_file();
   virtual ~stdio_file();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   virtual filesize get_position() const override;
   virtual bool get_status(::file::file_status& rStatus) const override;
   virtual ::file::path get_file_path() const override;


   virtual ::extended::status open(const ::file::path & pszFileName, const ::file::e_open & eopen) override;


   virtual filesize seek(filesize lOff,::file::e_seek  nFrom) override;
   virtual void set_size(filesize dwNewLen) override;
   virtual filesize get_size() const override;

   virtual void lock(filesize dwPos,filesize dwCount) override;
   virtual void unlock(filesize dwPos,filesize dwCount) override;

   virtual void flush() override;
   virtual void close() override;


   memsize read(void *pdata,memsize nCount) override;

   int get_character() override;
   int peek_character() override;
   int put_character_back(int iChar) override;

   void write(const void * pdata,memsize nCount) override;

   string get_location() const override;

   bool is_opened() const override;


};



