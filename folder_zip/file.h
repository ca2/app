#pragma once


#include "acme/filesystem/file/file.h"
//#include "acme/prototype/collection/string_array.h"


namespace folder_zip
{


   class CLASS_DECL_FOLDER_ZIP file:
      virtual public ::file::file
   {
   public:


      enum e_mode
      {

         mode_undefined,
         mode_zip,
         mode_unzip

      };


      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };


      //void *                              m_punzfileinfo;
      string                              m_strFileName;
      unsigned long long                                 m_iPosition;
      string_array_base                        m_straPath;
      ::pointer<folder>                  m_pfolder;
      //pointer_array < ::file_container >   m_filea;
      //pointer_array < ::zip::in_file >     m_infilea;
      string_array_base                        m_straPrefix;
      e_mode                              m_emode;
      string                              m_strZipFile;


      file();
      ~file() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;




      virtual filesize get_position() const override;


      bool is_in_memory_file() const override { return true; }


      //virtual bool zip_open(const_char_pointer ,unsigned int);
      //virtual bool zip_open(::zip::file * pzfile,const ::file::path & path);


      //virtual bool unzip_open(::file::file * pfile, const string_array_base & = {}, int iBufferLevel = 2, ::file::enum_type * petype = nullptr);
      //virtual bool unzip_open(::zip::file * pzfile,const ::file::path & path);

      //virtual bool unzip_open(const_char_pointer ,::file::enum_type * petype = nullptr);

      //virtual bool locate(const ::file::path & path);

      //virtual void add_file(const ::file::path & pathFolder,const ::file::path & pathRelative);

      //bool dump(file_pointer pfile);

      //bool dump(memory & m);

      
      ::folder_zip::folder * get_folder();

      
      void translate(filesize offset, ::enum_seek eseek) override;
      void set_size(filesize dwNewLen) override;
      filesize size() const override;


      using ::file::file::read;
      memsize read(void * p, ::memsize s) override;


      using ::file::file::write;
      void write(const void * p, ::memsize s) override;


      void flush() override;
      void close() override;

      bool is_opened() const override;


   };


} // namespace folder_zip



