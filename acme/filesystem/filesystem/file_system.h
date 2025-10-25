// Create by camilo on 2021-08-09 03:02 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "acme/filesystem/filesystem/file_system_interface.h"


class CLASS_DECL_ACME file_system :
   virtual public ::acme::department,
   virtual public ::file_system_interface
{
public:



   //::file::path         m_pathCa2Module;
   ::file::path         m_pathModule;
   ::string_array       m_straFileSystemItemSlot;


   ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::file_system *     m_pplatformfile;
   ::directory_system *                                           m_pdirectorysystem;
   ::path_system *                                                m_ppathsystem;

   ::file::path                                                   m_pathExecutable;

   ::pointer < ::mutex >                                          m_pmutexFileSystemItem;
   string_map_base < ::pointer < ::file_system_item > >           m_mapFileSystemItem;


   file_system();
   ~file_system() override;


   virtual void initialize(::particle* pparticle) override;

   virtual void init_system();

   virtual int file_system_item_slot_index(const ::scoped_string& scopedstrSlotName);


   virtual void ensure_exists(const ::file::path & path);
   virtual void touch(const ::file::path & path);
   virtual void touch_app_cloud(const ::file::path & path, const_char_pointer pszContentIdentifier = nullptr);
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
   virtual ::filesize size(const ::file::path & pathFile);
   virtual ::memory slice(const ::file::path & pathFile, memsize start, memsize count);
   virtual ::memory beginning(const ::file::path & pathFile, memsize len);
   virtual ::memory ending(const ::file::path & pathFile, memsize len);
   virtual bool append_unique_line(const ::file::path & pathFile, const ::scoped_string & scopedstrLine);
   virtual ::collection::count find_and_erase(const ::file::path & pathFile, const block & block);

   virtual bool exists(const ::file::path & path);
   virtual bool __exists(const ::file::path& path);

   //virtual void put_contents(const ::file::path & path, const scoped_string & contents);
   virtual filesize get_size(const ::file::path & path);
   virtual filesize get_size_fd(int iFile);


   virtual void clear_application_data();


   virtual void find_replace(const ::file::path & path, const ::property_set & set);

   
   virtual void put_app_cloud_data(const ::file::path & path, const_char_pointer pszContentIdentifier, const ::block & block);
   
   virtual ::memory get_app_cloud_data(const ::file::path & path, const_char_pointer pszContentIdentifier);
   
   virtual void put_documents_cloud_data(const ::file::path & path, const ::block & block);
   
   virtual ::memory get_documents_cloud_data(const ::file::path & path);

   //virtual FILE * FILE_open(const ::file::path & path, const scoped_string & attrs, int iShare);
   //virtual int FILE_printf(FILE * fp, const scoped_string & s, ...);
   //virtual int FILE_close(FILE * fp);
   //virtual int FILE_eof(FILE * fp);
   //virtual filesize FILE_seek(FILE * str, filesize offset, int origin);
   //virtual filesize FILE_tell(FILE * fp);
   //virtual filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
   //virtual filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
   //virtual char * FILE_gets(char * str, character_count n, FILE * s);
   //virtual int FILE_getc(FILE * s);
   //virtual int FILE_ungetc(int c, FILE * s);
   //virtual int FILE_error(FILE * s);
   //virtual int FILE_flush(FILE * s);

   //#ifdef WINDOWS
   //virtual FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
   //virtual int fwprintf_dup(FILE *fp, const unichar *s, ...);
   //virtual unichar *fgetws_dup(unichar *str, int n, FILE *s);
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


   virtual void save_stra(const ::file::path & pathName, const string_array_base & stra);
   virtual void load_stra(const ::file::path & pathName, string_array_base & stra, bool bAddEmpty = true);


   virtual void put_contents(const ::file::path & path, const block & block);
   // virtual void put_contents(const ::file::path& path, const scoped_string& contents);

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
   virtual memory as_memory(const ::file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual memsize as_memory(const ::file::path & path, void * p, memsize s);
   virtual memory safe_get_memory(const file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual memory __safe_get_memory(const file::path& path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual memsize __safe_find_string(const ::file::path& path, const_char_pointer psz);
   virtual string as_string(const ::file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual string safe_get_string(const ::file::path & path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);
   virtual string __safe_get_string(const ::file::path& path, character_count iReadAtMostByteCount = -1, bool bNoExceptionOnOpen = true);


   virtual void put_block(const ::file::path & path, const block & block);

   virtual void put_now(const ::file::path& path);
   virtual void put_time(const ::file::path& path, const ::earth::time & time);
   virtual ::earth::time as_time(const ::file::path& path);
   virtual ::earth::time safe_time(const ::file::path& path);


   virtual void as_block(block & block, const ::file::path & path);

   // acme/filesystem/file.h
   // partial excerpt of...
   // on 2021-08-10 00:46


   //virtual string_array_base file_as_lines(const ::file::path & path, character_count iReadAtMostByteCount = -1);
   virtual string first_line(const ::file::path & path);
   virtual string line(const ::file::path & path, ::collection::index iLine);
   virtual string_array_base lines(const ::file::path & path);
   virtual void set_line(const ::file::path & path, ::collection::index iLine, const ::scoped_string & scopedstrLine);
   //virtual string file_extension_dup(const ::file::path & path);
   virtual string get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension);

   virtual void get_temporary_file_name_template(char * szRet, character_count iBufferSize, const scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrTemplate);

   //virtual string file_path_final_extension(const ::file::path & path);
   //virtual string url_dir_name_for_relative(const ::file::path & path);
   //virtual string solve_relative(const ::scoped_string & scopedstr, bool * pbUrl = nullptr);
   //virtual bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, character_count * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
   //virtual string defer_solve_relative(const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstrCurrent);
   virtual void append(const ::scoped_string & scopedstrFile, const block & block);
   virtual void append_wait(const ::scoped_string & scopedstrFile, const block & block, const class time & timeWait = ::time::infinity());
   //virtual bool file_append_wait(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstr, character_count s, const class ::time & millisTimeout = ::time::infinite());

   //virtual void write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten);


   virtual bool _exists(const ::file::path & path);
   virtual void _erase(const ::file::path & path);



   virtual ::file::path time_put_contents(const ::file::path& pathFolder, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstr);





   //virtual void update_module_path();


   //virtual ::file::path get_last_run_application_path_file(const ::scoped_string & scopedstrAppId);
   //virtual ::file::path get_last_run_application_path(const ::scoped_string & scopedstrAppId);
   //virtual bool set_last_run_application_path(const ::scoped_string & scopedstrAppId);

   
   //bool _file_system_file_exists(const ::file_system_cache_item & pfilesystemcacheitem) override;
   //bool _file_system_is_folder(const ::file_system_cache_item & pfilesystemcacheitem) override;
   bool _file_system_has_script(const ::file_system_cache_item & pfilesystemcacheitem) override;
   ::string _file_system_expanded_md5(const ::file_system_cache_item & pfilesystemcacheitem) override;


   ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface* pfilesystemrealpathinterface) override;

   ::file_system_item * get_file_system_item(const ::scoped_string& scopedstrName, ::file_system_real_path_interface * pfilesystemrealpathinterface) override;


};



