// Create by camilo on 2021-08-09 03:02 <3ThomasBorregaardSorensen!!
#pragma once


//#include "path.h"


class CLASS_DECL_ACME acme_file :
   virtual public ::particle
{
public:


   ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::acme_file *       m_pplatformfile;
   ::acme_directory *                                             m_pacmedirectory;
   ::acme_path *                                                  m_pacmepath;

   ::file::path                                                   m_pathExecutable;


   acme_file();
   ~acme_file() override;


   virtual void ensure_exists(const ::file::path & path);
   virtual void touch(const ::file::path & path);
   virtual void touch_app_cloud(const ::file::path & path, const char * pszContentIdentifier = nullptr);
   virtual void clear_read_only(const ::file::path & path);


   virtual void set_file_normal(const ::file::path & path);


   virtual bool is_equal(const ::file::path & path1, const ::file::path & path2);
   virtual void overwrite_if_different(const ::file::path & pathTarget, const ::file::path & pathSource);




   // executable path
   virtual ::file::path module();


   file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception = nullptr) override;

   virtual file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_read | ::file::e_open_binary, ::pointer < ::file::exception >* pfileexception = nullptr);
   
   virtual file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_read_write | ::file::e_open_binary | ::file::e_open_defer_create_directory, ::pointer < ::file::exception >* pfileexception = nullptr);

   //virtual string get_temp_name(const ::file::path & pathName, const ::scoped_string & scopedstrExtension);
   virtual void append_wait(const ::file::path & pathFile, const block & block, const class time & time);
   virtual void append(const ::file::path & pathFile, const block & block);

   virtual bool exists(const ::file::path & path);

   //virtual void put_contents(const ::file::path & path, const scoped_string & contents);
   virtual filesize get_size(const ::file::path & path);
   virtual filesize get_size_fd(int iFile);


   virtual void clear_application_data();


   virtual void find_replace(const ::file::path & path, const ::property_set & set);

   
   virtual void put_app_cloud_data(const ::file::path & path, const char * pszContentIdentifier, const ::block & block);
   
   virtual ::memory get_app_cloud_data(const ::file::path & path, const char * pszContentIdentifier);
   
   virtual void put_documents_cloud_data(const ::file::path & path, const ::block & block);
   
   virtual ::memory get_documents_cloud_data(const ::file::path & path);

   //virtual FILE * FILE_open(const ::file::path & path, const scoped_string & attrs, int iShare);
   //virtual i32 FILE_printf(FILE * fp, const scoped_string & s, ...);
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

   virtual bool is_true(const ::file::path & path);


   virtual void set_size(const ::file::path & pathName, filesize iSize);
   virtual void set_size(int iFileDescriptor, filesize iSize);


   virtual void transfer(const ::file::path & pathNewName, const ::file::path & pathOldName);

   virtual void erase(const ::file::path & path);
   virtual void defer_erase(const ::file::path& path);
   virtual bool safe_erase(const ::file::path& path);

   //virtual bool set_line(const ::file::path & path, ::collection::index iLine, const ::file::path & pathLine);

   virtual void copy(const ::file::path & pathDup, const ::file::path & pathSrc, bool bOverwrite);
   virtual void _copy(const ::file::path & pathDup, const ::file::path & pathSrc, bool bOverwrite);


   virtual bool text_is_different(const ::file::path & path1, const ::file::path & path2, ::string * pstr1 = nullptr, ::string * pstr2 = nullptr);
   virtual bool copy_if_text_is_different(const ::file::path & pathTarget, const ::file::path & pathSource, const ::procedure & procedureRunIfFilesAreDifferentAndAfterCopy = {});

   
   virtual bool _memory_map_file_copy(const ::file::path & pathNew, const ::file::path & pathSrc);
   
   virtual void _read_write_file_copy(const ::file::path & pathNew, const ::file::path & pathSrc, ::memsize buffer_size = 1_MiB);


   virtual class ::time modification_time(const ::file::path & path);
   virtual void set_modification_time(const ::file::path & path, const class ::time & time);
   virtual void synchronize(const ::file::path & path1, const ::file::path & path2);


   virtual void save_stra(const ::file::path & pathName, const string_array & stra);
   virtual void load_stra(const ::file::path & pathName, string_array & stra, bool bAddEmpty = true);


   virtual void put_contents(const ::file::path & path, const memory_base & memory);
   virtual void put_contents(const ::file::path & path, const scoped_string & contents);

   template < typename CONTAINER >
   inline void put_lines(const ::file::path & path, const CONTAINER & container)
   {

      ::string str;

      for (auto & line : container)
      {

         str += line;

#ifdef WINDOWS_DESKTOP

         str += "\r\n";

#else

         str += "\n";

#endif

      }

      put_block(path, str);

   }

   virtual void as_memory(memory_base & memory, const ::file::path & path, memsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   //virtual memsize as_memory(const ::file::path & path, void * p, memsize s);
   virtual memory as_memory(const ::file::path & path, strsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual memsize as_memory(const ::file::path & path, void * p, memsize s);
   virtual memory safe_get_memory(const file::path & path, strsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual string as_string(const ::file::path & path, strsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual string safe_get_string(const ::file::path & path, strsize iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);


   virtual void put_block(const ::file::path & path, const block & block);

   virtual void put_now(const ::file::path& path);
   virtual void put_time(const ::file::path& path, const ::earth::time & time);
   virtual ::earth::time as_time(const ::file::path& path);
   virtual ::earth::time safe_time(const ::file::path& path);


   virtual void as_block(block & block, const ::file::path & path);

   // acme/filesystem/file.h
   // partial excerpt of...
   // on 2021-08-10 00:46


   //virtual string_array file_as_lines(const ::file::path & path, strsize iReadAtMostByteCount = -1);
   virtual string first_line(const ::file::path & path);
   virtual string line(const ::file::path & path, ::collection::index iLine);
   virtual string_array lines(const ::file::path & path);
   virtual void set_line(const ::file::path & path, ::collection::index iLine, const ::scoped_string & scopedstrLine);
   //virtual string file_extension_dup(const ::file::path & path);
   virtual string get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension);

   virtual void get_temporary_file_name_template(char * szRet, strsize iBufferSize, const scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrTemplate);

   //virtual string file_path_final_extension(const ::file::path & path);
   //virtual string url_dir_name_for_relative(const ::file::path & path);
   //virtual string solve_relative(const ::string & str, bool * pbUrl = nullptr);
   //virtual bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
   //virtual string defer_solve_relative(const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstrCurrent);
   virtual void append(const ::string & strFile, const block & block);
   virtual void append_wait(const ::string & strFile, const block & block, const class time & timeWait = ::time::infinity());
   //virtual bool file_append_wait(const ::string & strFile, const ::scoped_string & scopedstr, strsize s, const class ::time & millisTimeout = ::time::infinite());

   //virtual void write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);


   virtual bool _exists(const ::file::path & path);
   virtual void _erase(const ::file::path & path);



   virtual ::file::path time_put_contents(const ::file::path& pathFolder, const ::string& strPrefix, const ::string& strExtension, const ::string& str);


   virtual ::pointer<::handle::ini>get_ini(const ::payload & payloadFile);


   virtual ::property_set parse_standard_configuration(const ::payload & payloadFile);


};



