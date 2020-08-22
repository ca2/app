#pragma once



namespace file
{


   class CLASS_DECL_AURA application_file:
      virtual public object
   {
   public:


      application_file();
      virtual ~application_file();


      virtual ::status::result copy(var varTarget, var varSource, bool bFailIfExists = false, e_extract eextract = extract_first);
      virtual ::status::result move(const ::file::path & pszNew,const ::file::path & psz);
      virtual ::status::result del(const ::file::path & psz);
      virtual ::status::result rename(const ::file::path & pszNew,const ::file::path & psz);


      virtual void trash_that_is_not_trash(const ::file::path & psz);
      virtual void trash_that_is_not_trash(::file::patha & stra);


      virtual ::status::result replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

      virtual bool exists(const ::file::path & pszPath);

      virtual bool is_file_or_dir(const ::file::path & pszPath, e_type * petype = nullptr);

      virtual var length(const ::file::path & pszPath);


      ::file::path time(const ::file::path & pszBasePath,i32 iDepth = 1,const string & pszPrefix = nullptr,const string & pszSuffix = nullptr);
      ::file::path time_square(const string & pszPrefix = nullptr,const string & pszSuffix = nullptr);
      ::file::path time_log(const string & pszId);


      virtual file_pointer time_square_file(const char * pszPrefix = nullptr, const char * pszSuffix = nullptr);
      virtual file_pointer get(const ::file::path & name);


      virtual var as_json(const var & varFile);
      virtual string as_string(const var & varFile);
      virtual bool as_memory(const var & varFile, memory_base & mem);

      inline ::memory as_primitive_memory(const var & varFile) { ::memory m; as_memory(varFile, m); return m; }
      inline ::memory as_memory(const var & varFile) { return as_primitive_memory(varFile); }


      template < class OBJECT >
      ::estatus put(const var & varFile, OBJECT & a)
      {

         auto writer = get_writer(varFile);

         writer << a;

         return writer.m_estatus;

      }


      template < class OBJECT >
      ::estatus as(OBJECT & a, const var & varFile)
      {

         auto reader = get_reader(varFile);

         reader >> a;

         return reader.m_estatus;

      }


      template < class ARRAY >
      bool to_array(ARRAY & a, const var & varFile)
      {

         auto pfile = get_reader(varFile);

         ::stream s(pfile);

         __exchange_array(a, s);

         return !s.fail();

      }


      virtual void lines(string_array & stra, const var & varFile);
      virtual void put_lines(const var & varFile, const string_array & stra);

      virtual bool put_contents(const var & varFile, const void * pvoidContents, ::count count);
      virtual bool put_contents(const var & varFile, const char * pcszContents);

      //virtual bool copy?(const var & varFile, const ::stream & stream);
      virtual bool put_contents(const var & varFile, memory & mem);
      virtual bool put_contents_utf8(const var & varFile, const char * pcszContents);


      virtual bool add_contents(const var & varFile,const char * pcszContents);


      string sys_temp(const char * lpszName, const char * pszExtension);


      virtual ::file_result get_file(const var & varFile, UINT nOpenFlags);


      virtual bool is_read_only(const path & psz);

      inline auto open_for_reading(const var & varFile, UINT nOpenFlags = ::file::type_binary)
      {

         return get_file(varFile, nOpenFlags | ::file::mode_read);

      }

      inline auto create_for_writing(const var & varFile, UINT nOpenFlags = ::file::type_binary | ::file::defer_create_directory)
      {

         return get_file(varFile, nOpenFlags | ::file::mode_create | ::file::mode_write);

      }


      // get a file and if there are exceptions, should show end user friendly messages
      virtual rp(::file::file) friendly_get_file(const var & varFile, UINT nOpenFlags);


      void dtf(const ::file::path & pszFile,const ::file::path & pszDir);
      void dtf(const ::file::path & pszFile,::file::patha & stra,::file::patha & straRelative);
      void ftd(const ::file::path & pszDir,const ::file::path & pszFile);


      virtual bool crypto_set(const var & varFile,const char * pszData,const char * pszSalt);
      virtual bool crypto_get(const var & varFile,string & str,const char * pszSalt);


      template < typename TYPE >
      bool save(const var & varFile, const TYPE & o)
      {

         return put(varFile, o);
      }


      template < typename TYPE >
      inline bool load(TYPE & o, const var & varFile)
      {

         return as(o, varFile);

      }


      virtual bool save_lines(const var & varFile,string_array & stra);
      virtual bool load_lines(string_array & stra,const var & varFile);


      template < class T >
      bool output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn);

      virtual bool transfer(::file::file * pfileOut, ::file::file * pfileIn);

      virtual bool touch(const ::file::path & path);

      virtual string md5(const var & varFile);

      virtual string nessie(const var & varFile);

      virtual ::file::path dropbox_info_json();

      virtual ::file::path onedrive_global_ini();

      virtual ::file::path onedrive_cid_ini();

   };


   typedef pointer < application_file > application_file_pointer;


} // namespace axis











