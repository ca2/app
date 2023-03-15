#pragma once


#include "file.h"


namespace file
{


   class CLASS_DECL_ACME reference :
      virtual public ::file::file
   {
   public:



      file_pointer      m_pfile;


      reference();
      reference(file * pfile);
      ~reference() override;


      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;



      filesize get_position() const override;
      bool get_status(file_status& rStatus) const override;
      ::file::path get_file_path() const override;
      void set_file_path(const ::file::path & path) override;

      
      void open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception) override;


      void translate(filesize offset, ::enum_seek eseek) override;
      void set_size(filesize dwNewLen) override;
      filesize size() const override;


      void lock(filesize dwPos, filesize dwCount) override;
      void unlock(filesize dwPos, filesize dwCount) override;


      void abort() override;
      void flush() override;
      void close() override;


      memsize read(const ::block & block) override;

      void write(const ::block & block) override;

      ::string get_location() const override;

      bool is_opened() const override;


   };


} // namespace file


