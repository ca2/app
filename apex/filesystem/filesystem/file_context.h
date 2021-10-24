#pragma once


class CLASS_DECL_APEX file_context :
   virtual public object
{
public:


   file_context();
   virtual ~file_context();

   
   virtual ::e_status initialize(::object * pobject) override;


   virtual ::e_status init_system();
   virtual ::e_status init_context();

   
   virtual ::e_status update_module_path();


   virtual ::extended::status copy(::payload varTarget, ::payload varSource, bool bFailIfExists = false, e_extract eextract = extract_first);
   virtual ::extended::status move(const ::file::path & pathNew, const ::file::path & path);
   virtual ::extended::status del(const ::file::path & path);
   virtual ::file::path duplicate(const ::file::path & path);
   virtual ::file::path paste(const ::file::path & pathLocation, const ::file::path & path);
   virtual ::extended::status rename(const ::file::path & pathNew, const ::file::path & path);


   virtual void trash_that_is_not_trash(const ::file::path & path);
   virtual void trash_that_is_not_trash(::file::patha & patha);


   virtual bool get_status(const ::file::path & path, ::file::file_status & status);
   virtual ::extended::status set_status(const ::file::path & path, const ::file::file_status & status);


   virtual ::extended::status replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);


   virtual bool is_file_or_dir(const ::file::path & path, ::payload * pvarQuery, ::file::enum_type * petype);
   virtual bool is_file_or_dir(const ::file::path & pszPath, ::file::enum_type * petype = nullptr);


   virtual ::payload length(const ::file::path & path);


   virtual ::payload length(const ::file::path & path, ::payload * pvarQuery);


   virtual ::file::path module();

   virtual ::file::path ca2module();

   
   ::file::path time(const ::file::path & pathBasePath, i32 iDepth = 0, const ::string & strPrefix = nullptr, const ::string & strSuffix = nullptr, bool bTryDelete = false);
   ::file::path time_square(const ::string & strPrefix = nullptr, const ::string & strSuffix = nullptr);
   ::file::path time_log(const ::string & str);


   virtual file_pointer time_square_file(const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);
   virtual file_pointer get(const ::file::path & name);


   template < class T >
   string time_square(T * p, bool (T:: * pfnOutput)(::stream &, const ::file::path &), const ::file::path & pszSource)
   {

      string strTime = time_square(p);

      if (strTime.has_char())
      {

         if (!output(strTime, p, pfnOutput, pszSource))
         {

            return "";

         }

      }

      return strTime;

   }


   template < typename TYPE >
   inline ::e_status binary_get(const ::payload & varFile, TYPE & t)
   {

      auto preader = get_reader(varFile);

      if (!preader)
      {

         return preader.m_estatus;

      }

      binary_stream stream(preader);

      stream.defer_set_loading();

      stream.exchange(::id::e_type_null, t);

      return stream.fail() ? ::error_failed : ::success;

   }


   template < typename TYPE >
   inline ::e_status binary_set(const ::payload & varFile, const TYPE & t)
   {

      auto pwriter = get_writer(varFile);

      if (!pwriter)
      {

         return pwriter.m_estatus;

      }

      binary_stream stream(pwriter);

      stream.defer_set_storing();

      stream.exchange(::id::e_type_null, t);

      return stream.fail() ? ::error_failed : ::success;

   }


   virtual i32 filterex_time_square(const char * pszPrefix, ::file::patha & stra);
   virtual bool try_create_file(const ::file::path & path, bool bTryDelete);


   virtual ::payload as_json(const ::payload & varFile);
   virtual string as_string(const ::payload & varFile);
   virtual bool as_memory(const ::payload & varFile, memory_base & mem);


   inline string_array lines(const ::payload & varFile, bool bAddEmpty = true)
   {

       string_array straLines;

       lines(straLines, varFile, bAddEmpty);

       return ::move(straLines);

   }

   virtual ::e_status lines(string_array & stra, const ::payload & varFile, bool bAddEmpty = false);
   virtual void put_lines(const ::payload & varFile, const string_array & stra);
   virtual void put_lines_utf8(const ::payload & varFile, const string_array & stra);
   virtual void _put_lines(::file::file * pfile, const string_array & stra);

   virtual bool put_contents(const ::payload & varFile, const void * pvoidContents, ::count count);
   virtual bool put_contents(const ::payload & varFile, const char * pcszContents);

   virtual bool put_contents(const ::payload & varFile, ::file::file * pfile);
   virtual bool put_contents(const ::payload & varFile, memory & mem);
   virtual bool put_contents_utf8(const ::payload & varFile, const char * pcszContents);


   virtual bool add_contents(const ::payload & varFile, const void * pvoidContents, ::count count);
   virtual bool add_contents(const ::payload & varFile, const char * pcszContents);


   virtual bool is_read_only(const ::file::path & psz);

   virtual ::extended::transport < ::file::file > resource_get_file(const ::file::path & path);

   virtual ::file::path sys_temp(const ::file::path & lpszName, const char * pszExtension);
   virtual ::file::path sys_temp_unique(const ::file::path & lpszName);


   virtual ::file::path replace_extension(const ::file::path & pszFile, const char * pszExtension);
   virtual void set_extension(::file::path & str, const char * pszExtension);


   virtual void normalize(string & str);
   virtual i32 cmp(const ::file::path & psz1, const ::file::path & psz2);

   virtual string get_hash(const ::payload& varFile, enum_hash ehash);

   //virtual string md5(::file::file * pfile);
   virtual string md5(const ::payload & varFile);

   //virtual string nessie(::file::file * pfile);
   virtual string nessie(const ::payload & varFile);

   virtual bool resolve_link(::file::path & pathTarget, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr);

   virtual bool is_link(string strPath);

   virtual bool get_last_write_time(filetime_t * pfiletime, const ::string & strFilename);

   //virtual void dtf(const ::file::path & pszFile, const ::file::path & pszDir);

   //virtual void dtf(const ::file::path & pszFile, ::file::patha & stra);

   //virtual void ftd(const ::file::path & pszDir, const ::file::path & pszFile);

   // 'n' (natural) terminated ascii number, example: 245765487n
   // pmd5ctx = openssl/md5.h's MD5_CTX
   //virtual void write_n_number(::file::file * pfile, void * pmd5ctx, i64 iNumber);
   //virtual void read_n_number(::file::file * pfile, void * pmd5ctx, i64 & iNumber);

   //virtual void write_gen_string(::file::file * pfile, void * pmd5ctx, string & str);
   //virtual void read_gen_string(::file::file * pfile, void * pmd5ctx, string & str);

   virtual ::file_transport file_get_file(::file::path path, const ::file::e_open & eopen);

   virtual ::file_transport data_get_file(string strData, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_transport zip_get_file(::file::file * pfile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_transport http_get_file(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_transport get_file(const ::payload & varFile, const ::file::e_open & eopen) override;

   virtual ::file_transport get_reader(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_transport shared_reader(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_transport get_writer(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_write | ::file::e_open_create | ::file::e_open_no_truncate | ::file::e_open_defer_create_directory | ::file::e_open_binary);

   virtual bool post_output(::file::path pathOut, ::file::path pathDownloading);

   template < typename T >
   bool output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn);

   virtual bool transfer(::file::file * pfileOut, ::file::file * pfileIn);

   virtual ::file::path dropbox_info_json();


   virtual ::file::path onedrive_global_ini();
   virtual ::file::path onedrive_cid_ini();

//   virtual ::extended::status copy(::payload varTarget, ::payload varSource, bool bFailIfExists = false, e_extract eextract = extract_first);
   //virtual ::extended::status move(const ::file::path & pszNew, const ::file::path & psz);
   //virtual ::extended::status del(const ::file::path & psz);
   //virtual ::extended::status rename(const ::file::path & pszNew, const ::file::path & psz);


   //virtual void trash_that_is_not_trash(const ::file::path & psz);
   //virtual void trash_that_is_not_trash(::file::patha & stra);


   //virtual ::extended::status replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

  virtual bool exists(const ::file::path & pszPath);


  // virtual ::payload length(const ::file::path & pszPath);


   //::file::path time(const ::file::path & pszBasePath, i32 iDepth = 1, const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);


   //virtual file_pointer time_square_file(const char * pszPrefix = nullptr, const char * pszSuffix = nullptr);
   //virtual file_pointer get(const ::file::path & name);



   inline ::memory as_primitive_memory(const ::payload & varFile) { ::memory m; as_memory(varFile, m); return m; }
   inline ::memory as_memory(const ::payload & varFile) { return as_primitive_memory(varFile); }


   template < class OBJECT >
   ::e_status put(const ::payload & varFile, OBJECT & a)
   {

      auto writer = get_writer(varFile);

      if(!writer)
      {

         return writer.m_estatus;

      }

      *writer << a;

      return writer.m_estatus;

   }


   ::e_status set(const ::payload & varFile, const ::memory_base & memory)
   {

      auto writer = get_writer(varFile);

      writer->write(memory.get_data(), memory.get_size());

      return writer.m_estatus;

   }


   template < class OBJECT >
   ::e_status as(OBJECT & a, const ::payload & varFile)
   {

      auto reader = get_reader(varFile);

      *reader >> a;

      return reader.m_estatus;

   }


   template < class ARRAY >
   bool to_array(ARRAY & a, const ::payload & varFile)
   {

      auto pfile = get_reader(varFile);

      ::binary_stream s(pfile);

      __exchange_array(a, s);

      return !s.fail();

   }


   //virtual void lines(string_array & stra, const ::payload & varFile);
   //virtual void put_lines(const ::payload & varFile, const string_array & stra);

   //virtual bool put_contents(const ::payload & varFile, const void * pvoidContents, ::count count);
   //virtual bool put_contents(const ::payload & varFile, const char * pcszContents);

   //virtual bool copy?(const ::payload & varFile, const ::stream & stream);
   //virtual bool put_contents(const ::payload & varFile, memory & mem);
   //virtual bool put_contents_utf8(const ::payload & varFile, const char * pcszContents);


   //virtual bool add_contents(const ::payload & varFile, const char * pcszContents);


   string sys_temp(const char * lpszName, const char * pszExtension);


   //virtual ::file_transport get_file(const ::payload & varFile, ::u32 nOpenFlags);


   //virtual bool is_read_only(const ::file::path & psz);

   inline auto open_for_reading(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_binary)
   {

      return get_file(varFile, eopen | ::file::e_open_read);

   }

   inline auto create_for_writing(const ::payload & varFile, const ::file::e_open & eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory)
   {

      return get_file(varFile, eopen | ::file::e_open_create | ::file::e_open_write);

   }


   // get a file and if there are exceptions, should show end user friendly messages
   virtual ::extended::transport < ::file::file > friendly_get_file(const ::payload & varFile, const ::file::e_open & eopen);


   //void dtf(const ::file::path & pszFile, const ::file::path & pszDir);
   void dtf(const ::file::path & pszFile, ::file::patha & stra, ::file::patha & straRelative);
   //void ftd(const ::file::path & pszDir, const ::file::path & pszFile);


   virtual bool crypto_set(const ::payload & varFile, const char * pszData, const char * pszSalt);
   virtual bool crypto_get(const ::payload & varFile, string & str, const char * pszSalt);


   template < typename TYPE >
   bool save(const ::payload & varFile, const TYPE & o)
   {

      return put(varFile, o);
   }


   template < typename TYPE >
   inline bool load(TYPE & o, const ::payload & varFile)
   {

      return as(o, varFile);

   }


   virtual bool save_lines(const ::payload & varFile, string_array & stra);
   virtual bool load_lines(string_array & stra, const ::payload & varFile);



   virtual bool touch(const ::file::path & path);

   //virtual string md5(const ::payload & varFile);

   //virtual string nessie(const ::payload & varFile);

   //virtual ::file::path dropbox_info_json();

   //virtual ::file::path onedrive_global_ini();

   //virtual ::file::path onedrive_cid_ini();


};



CLASS_DECL_APEX void set_bypass_cache_if_empty(::payload & varFile);
CLASS_DECL_APEX bool get_bypass_cache_if_empty(const ::payload & varFile);






