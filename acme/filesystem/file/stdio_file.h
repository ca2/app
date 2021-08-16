#pragma once


class CLASS_DECL_ACME stdio_file:
   virtual public ::file::file
{
public:


   FILE *         m_pfile;
   string         m_strFileName;


   stdio_file();
   explicit stdio_file(FILE * pfile);
   ~stdio_file() override;


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;


   filesize get_position() const override;
   bool get_status(::file::file_status& rStatus) const override;
   ::file::path get_file_path() const override;


   ::extended::status open(const ::file::path & path, const ::file::e_open & eopen) override;
   virtual ::e_status open(const ::file::path & path, const ::string & strAttributes, int iShare);


   ::index translate(::count c, ::enum_seek eseek) override;
   void set_size(filesize dwNewLen) override;
   filesize get_size() const override;

   void lock(filesize dwPos,filesize dwCount) override;
   void unlock(filesize dwPos,filesize dwCount) override;

   void flush() override;
   void close() override;


   memsize read(void *pdata,memsize nCount) override;

   int get_character() override;
   int peek_character() override;
   int put_character_back(int iChar) override;

   using ::file::file::write;
   void write(const void * pdata,memsize nCount) override;

   string get_location() const override;

   bool is_opened() const override;


};



