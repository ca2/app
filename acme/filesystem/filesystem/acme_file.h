// Create by camilo on 2021-08-09 03:02 <3ThomasBorregaardS�rensen!!
#pragma once


class CLASS_DECL_ACME acme_file :
   virtual public ::matter
{
public:


   ::PLATFORM_NAMESPACE::acme_file *   m_pplatformfile;
   acme_dir *                          m_pacmedir;
   acme_path *                         m_pacmepath;

   ::file::path                        m_pathExecutable;


   acme_file();
   ~acme_file() override;


   virtual ::file::path executable();


   virtual file_transport open(const ::file::path & path, const ::file::e_open & eopen);


   virtual memory as_memory(const char * path, strsize iReadAtMostByteCount = -1);
   virtual memsize as_memory(const char * path, void * p, memsize s);
   virtual string as_string(const char * path, strsize iReadAtMostByteCount = -1);


   //virtual string get_temp_name(const char * lpszName, const char * pszExtension);
   virtual ::e_status write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);
   virtual ::e_status append_wait(const char * pszFile, const block & block, const ::duration & duration);
   virtual ::e_status append(const char * pszFile, const block & block);

   virtual bool exists(const char * path);

   virtual ::e_status put_contents(const char * path, const char * contents, strsize len);
   virtual filesize get_size(const char * path);
   virtual filesize get_size(FILE * pfile);
   virtual filesize get_size_fd(int iFile);

   //virtual FILE * FILE_open(const char * path, const char * attrs, int iShare);
   //virtual i32 FILE_printf(FILE * fp, const char * s, ...);
   //virtual i32 FILE_close(FILE * fp);
   //virtual i32 FILE_eof(FILE * fp);
   //virtual filesize FILE_seek(FILE * str, filesize offset, i32 origin);
   //virtual filesize FILE_tell(FILE * fp);
   //virtual filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
   //virtual filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
   //virtual char * FILE_gets(char * str, strsize n, FILE * s);
   //virtual i32 FILE_getc(FILE * s);
   //virtual i32 FILE_ungetc(i32 c, FILE * s);
   //virtual i32 FILE_error(FILE * s);
   //virtual i32 FILE_flush(FILE * s);

   //#ifdef WINDOWS
   //virtual FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
   //virtual i32 fwprintf_dup(FILE *fp, const unichar *s, ...);
   //virtual unichar *fgetws_dup(unichar *str, i32 n, FILE *s);
   //virtual wint_t fgetwc_dup(FILE *s);
   //virtual wint_t ungetwc_dup(wint_t w, FILE *s);
   //#endif


   //virtual filesize FILE_get_size(FILE * fp);

   virtual bool is_true(const char * path);


   virtual ::e_status set_size(const char * lpszName, filesize iSize);
   virtual ::e_status set_size(int iFileDescriptor, filesize iSize);
   virtual ::e_status set_size(FILE * pfile, filesize iSize);


   virtual ::e_status move(const char * pszNewName, const char * pszOldName);

   virtual ::e_status delete_file(const char * pszFileName);

   //virtual bool set_line(const char * pszPath, index iLine, const char * pszLine);

   virtual ::e_status copy(const char * pszDup, const char * pszSrc, bool bOverwrite);

   virtual ::e_status save_stra(const char * lpszName, const string_array & stra);
   virtual ::e_status load_stra(const char * lpszName, string_array & stra, bool bAddEmpty = true);


   virtual ::e_status put_contents(const char * path, const memory_base & memory);
   virtual ::e_status put_contents(const char * path, const char * contents);
   virtual ::e_status as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount = -1);
   //virtual memsize as_memory(const char * path, void * p, memsize s);


   virtual ::e_status put_block(const char * path, const block & block);


   virtual ::e_status as_block(block & block, const char * path);

   // acme/filesystem/file.h
   // partial excerpt of...
   // on 2021-08-10 00:46


   //virtual string_array file_as_lines(const char * path, strsize iReadAtMostByteCount = -1);
   virtual string first_line(const char * path);
   virtual string line(const char * path, index iLine);
   virtual string_array lines(const char * path);
   virtual ::e_status set_line(const char * path, index iLine, const char * pszLine);
   //virtual string file_extension_dup(const char * path);
   virtual string get_temporary_file_name(const char * lpszName, const char * pszExtension);

   virtual ::e_status get_temporary_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate);

   //virtual string file_final_extension_dup(const char * path);
   //virtual string url_dir_name_for_relative(const char * pszPath);
   //virtual string solve_relative(const ::string & str, bool * pbUrl = nullptr);
   //virtual bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
   //virtual string defer_solve_relative(const char * pszRelative, const char * pszCurrent);
   virtual ::e_status append(const ::string & strFile, const block & block);
   virtual ::e_status append_wait(const ::string & strFile, const block & block, const ::duration & duration = ::duration::infinite());
   //virtual bool file_append_wait(const ::string & strFile, const char * psz, strsize s, const ::millis & millisTimeout = ::millis::infinite());

   virtual ::e_status write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);


};



