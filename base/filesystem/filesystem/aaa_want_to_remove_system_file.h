#pragma once


namespace file
{


   class CLASS_DECL_AURA system_file :
      virtual public object
   {
   public:

      
      path         m_pathCa2Module;
      path         m_pathModule;


      system_file();
      virtual ~system_file();


      virtual ::status::result copy(var varTarget, var varSource,bool bFailIfExists,e_extract eextract,::object * pobject);
      virtual ::status::result move(const path & pszNew,const path & psz,::object * pobject);
      virtual ::status::result del(const path & psz,::object * pobject);
      virtual path duplicate(const path & psz,::object * pobject);
      virtual path paste(const path & pszLocation,const path & path,::object * pobject);
      virtual ::status::result rename(const path & pszNew,const path & psz,::object * pobject);

      virtual void trash_that_is_not_trash(const path & psz,::object * pobject);
      virtual void trash_that_is_not_trash(patha & stra, ::object * pobject);

      virtual bool get_status(const path & path,file_status & status,::object * pobject);
      virtual ::status::result set_status(const path & path,const file_status & status,::object * pobject);

      virtual ::status::result replace(const path & pszContext,const string & pszFind,const string & pszReplace,::object * pobject);

      virtual bool exists(path path, ::object * pobject);

      virtual bool is_file_or_dir(path path, var * pvarQuery, e_type * petype, ::object * pobject);

      virtual var length(const path & path,::object * pobject);

      virtual var length(const path & path,var * pvarQuery,::object * pobject);

      virtual path module();

      virtual path ca2module();

      virtual bool update_module_path();

      path time(::object * pobject,const path & pszBasePath,i32 iDepth,const string & pszPrefix = nullptr,const string & pszSuffix = nullptr, bool bTryDelete = false);
      path time_square(::object * pobject,const string & pszPrefix = nullptr,const string & pszSuffix = nullptr);
      path time_log(::object * pobject,const string & pszId);

      virtual file_pointer time_square_file(::object * pobject, const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);
      virtual file_pointer get(const path & name,::object * pobject);

      template < class T >
      string time_square(::object * pobject,T * point,bool (T::*pfnOutput)(::stream &,const path &),const path & pszSource)

      {
         string strTime = time_square(pobject);
         if(strTime.has_char())
            if(!output(strTime, point, pfnOutput, pszSource))

               return "";
         return strTime;
      }




      virtual i32 filterex_time_square(const char * pszPrefix,patha & stra);
      virtual bool try_create_file(const ::file::path & path, bool bTryDelete);

      virtual var as_json(::object * pobject, const var & varFile);
      virtual string as_string(::object * pobject, const var & varFile);
      virtual bool as_memory(::object * pobject, const var & varFile, memory_base & mem);

      virtual void lines(string_array & stra, const var & varFile, ::object * pobject);
      virtual void put_lines(const var & varFile, const string_array & stra, ::object * pobject);
      virtual void put_lines_utf8(const var & varFile, const string_array & stra, ::object * pobject);
      virtual void _put_lines(::file::file * pfile, const string_array & stra);

      virtual bool put_contents(const var & varFile,const void * pvoidContents,::count count,::object * pobject);
      virtual bool put_contents(const var & varFile,const char * pcszContents,::object * pobject);

      virtual bool put_contents(const var & varFile, ::file::file * pfile, ::object * pobject);
      virtual bool put_contents(const var & varFile, memory & mem, ::object * pobject);
      virtual bool put_contents_utf8(const var & varFile, const char * pcszContents, ::object * pobject);


      virtual bool add_contents(const var & varFile,const void * pvoidContents,::count count,::object * pobject);
      virtual bool add_contents(const var & varFile,const char * pcszContents,::object * pobject);


      virtual bool is_read_only(const path & psz, ::object * pobject);

      virtual path sys_temp(const path & lpszName,const char * pszExtension,::object * pobject);
      virtual path sys_temp_unique(const path & lpszName);


      virtual path replace_extension(const path & pszFile,const char * pszExtension);
      virtual void set_extension(path & str,const char * pszExtension);


      virtual void normalize(string & str);
      virtual i32 cmp(const path & psz1,const path & psz2);


      virtual string md5(file * pfile);
      virtual string md5(const var & varFile, ::object * pobject);

      virtual string nessie(file *  pfile);
      virtual string nessie(const var & varFile, ::object * pobject);

      virtual bool resolve_link(::object * pobject, ::file::path & pathTarget, const string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr, ::user::primitive * puiMessageParentOptional = nullptr);

      virtual bool is_link(string strPath);

      virtual bool get_last_write_time(FILETIME * pfiletime,const string & strFilename);

      virtual void dtf(const path & pszFile,const path & pszDir,::object * pobject);

      virtual void dtf(const path & pszFile,patha & stra,::object * pobject);

      virtual void ftd(const path & pszDir,const path & pszFile,::object * pobject);

      // 'n' (natural) terminated ascii number, example: 245765487n
      // pmd5ctx = openssl/md5.h's MD5_CTX
      virtual void write_n_number(file *  pfile, void * pmd5ctx, i64 iNumber);
      virtual void read_n_number(file *  pfile, void * pmd5ctx, i64 & iNumber);

      virtual void write_gen_string(file *  pfile, void * pmd5ctx, string & str);
      virtual void read_gen_string(file *  pfile, void * pmd5ctx, string & str);

      virtual ::estatus initialize(::object * pobjectContext) override;


      virtual ::file_result file_get_file(::object * pobject, ::file::path path, const efileopen & eopen);

      virtual ::file_result data_get_file(::object * pobject, string strData, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

      virtual ::file_result zip_get_file(::object * pobject, ::file::path path, const efileopen & eopen = ::file::mode_read | ::file::type_binary);
      
      virtual ::file_result http_get_file(::object * pobject, const var & varFile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

      virtual ::file_result get_file(::object * pobject, const var & varFile, const efileopen & eopen);

      virtual ::file_result get_reader(::object* pobject, const var& varFile, const efileopen & eopen = ::file::mode_read | ::file::type_binary);

      virtual ::file_result get_writer(::object* pobject, const var& varFile, const efileopen & eopen = ::file::mode_write | ::file::type_binary);

      virtual bool post_output(::object * pobject, path pathOut, path pathDownloading);

      template < typename T >
      bool output(::object * pobject, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn);

      virtual bool transfer(::object * pobject, ::file::file* pfileOut, ::file::file* pfileIn);

      virtual bool transfer(::file::file * pfileOut, ::file::file * pfileIn);

      
      virtual ::file::path dropbox_info_json(::object * pobject);
      
      
      virtual ::file::path onedrive_global_ini(::object * pobject);
      virtual ::file::path onedrive_cid_ini(::object * pobject);


   };


   typedef pointer < system_file > system_file_pointer;


} // namespace file





