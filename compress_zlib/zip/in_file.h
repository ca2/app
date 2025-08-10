#pragma once


namespace zip
{


   class file;


   class CLASS_DECL_ACME in_file:
      virtual public ::file::file,
      virtual public ::file::listing_provider
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


      void *                        m_punzfileinfo;
      string                        m_strFileName;
      unsigned long long                           m_iPosition;
      string_array_base                       m_straPath;
      pointer_array < ::zip::file >       m_filea;
      pointer_array < ::zip::in_file >    m_infilea;
      string_array_base                       m_straPrefix;
      e_mode                        m_emode;
      string                        m_strZipFile;


      in_file();
      ~in_file() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;




      virtual filesize get_position() const override;

      virtual bool zip_open(const_char_pointer ,unsigned int);
      virtual bool zip_open(::zip::file * pzfile,const ::file::path & path);


      virtual bool unzip_open(::file::file * pfile, const string_array_base & = {}, int iBufferLevel = 2, ::file::enum_type * petype = nullptr);
      virtual bool unzip_open(::zip::file * pzfile,const ::file::path & path);

      //virtual bool unzip_open(const_char_pointer ,::file::enum_type * petype = nullptr);

      virtual bool locate(const ::file::path & path);

      //virtual void add_file(const ::file::path & pathFolder,const ::file::path & pathRelative);

      virtual void add_file(const ::file::path & pathRelative, ::file::file * pfile);

      bool dump(file_pointer pfile);

      bool dump(memory & m);

      
      ::zip::file * get_zip_file();
      const ::zip::file * get_zip_file() const;

      
      filesize translate(filesize offset, ::enum_seek eseek) override;
      void set_size(filesize dwNewLen) override;
      filesize get_size() const override;


      using ::file::file::read;
      memsize read(void * pdata, memsize nCount) override;


      using ::file::file::write;
      void write(const void * pdata,memsize nCount) override;


      void flush() override;
      void close() override;

      virtual ::file::listing_base & ls(::file::listing_base & listing);
      virtual ::file::listing_base & ls_relative_name(::file::listing_base & listing);


      bool is_opened() const override;


      ::file::listing_base & perform_file_listing(::file::listing_base & listing) override;
      ::file::listing_base & perform_file_relative_name_listing(::file::listing_base & listing) override;


   };


} // namespace zip












