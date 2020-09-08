#pragma once


namespace file
{


   class CLASS_DECL_ACME reference :
      virtual public ::file::file
   {
   public:



      file_pointer      m_pfile;


      reference();
      reference(file * pfile);
      virtual ~reference();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;



      virtual filesize get_position() const override;
      virtual bool get_status(file_status& rStatus) const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;



      virtual ::status::result open(const ::file::path & path, const efileopen  & eopen) override;




      virtual filesize seek(filesize lOff, ::file::e_seek  nFrom) override;
      virtual void set_size(filesize dwNewLen) override;
      virtual filesize get_size() const override;

      virtual void lock(filesize dwPos, filesize dwCount) override;
      virtual void unlock(filesize dwPos, filesize dwCount) override;

      virtual void flush() override;
      virtual void close() override;


      virtual memsize read(void *pdata, memsize nCount) override;

      virtual void write(const void * pdata, memsize nCount) override;

      virtual ::string get_location() const override;

      virtual bool is_opened() const override;


   };


} // namespace file


