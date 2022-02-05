#pragma once


class CLASS_DECL_ACME stdio_file:
   virtual public ::file::file
{
public:

   
   enum enum_flag
   {
      
      flag_none = 0,
      flag_no_exception_if_not_found = 1,
      flag_file_not_found = 2,

   };

   using e_flag = enumeration < enum_flag >;


   FILE *                        m_pfile;
   string                        m_strFileName;
   e_flag                        m_eflag;


   stdio_file();
   explicit stdio_file(FILE * pfile);
   ~stdio_file() override;


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


   filesize get_position() const override;
   bool get_status(::file::file_status& rStatus) const override;
   ::file::path get_file_path() const override;


   void open(const ::file::path & path, const ::file::e_open & eopen) override;
   virtual void open(const ::file::path & path, const ::string & strAttributes, int iShare);

   
   filesize translate(filesize offset, ::enum_seek eseek) override;
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



