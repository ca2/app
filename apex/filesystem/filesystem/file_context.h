#pragma once


#include "acme/primitive/primitive/memory.h"
#include "acme/filesystem/file/plain_text_file_options.h"
////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/collection/string_array.h"


class CLASS_DECL_APEX file_context :
   virtual public object
{
public:


   ::pointer<::folder>           m_pfolderResource;
   bool                          m_bFolderResourceCalculated;
   bool                          m_bMainResourceMemoryCalculated;
   ::memory                      m_memoryMainResource;


   file_context();
   ~file_context() override;

   
   void initialize(::particle * pparticle) override;


   virtual void init_system();
   virtual void init_context();

   
   //virtual void update_module_path();


   virtual void calculate_main_resource_memory();


   virtual ::block get_main_resource_block();

   
   virtual ::folder* resource_folder();
   virtual ::memory_file_pointer create_resource_file(const ::file::path & path);
   virtual ::memory get_resource_memory(const ::file::path & path);
   virtual ::file::enum_type resource_get_type(const ::file::path & path);


   virtual void copy(::payload varTarget, ::payload varSource, bool bFailIfExists = false, enum_extract eextract = e_extract_first);
   virtual void transfer(const ::file::path & pathNew, const ::file::path & path);
   virtual void erase(const ::file::path & path);
   virtual ::file::path duplicate(const ::file::path & path);
   virtual ::file::path paste(const ::file::path & pathLocation, const ::file::path & path);
   virtual void rename(const ::file::path & pathNew, const ::file::path & path);


   virtual void trash_that_is_not_trash(const ::file::path & path);
   virtual void trash_that_is_not_trash(::file::path_array & patha);


   virtual void get_status(::file::file_status & status, const ::file::path & path);
   virtual void set_status(const ::file::path & path, const ::file::file_status & status);


   virtual void replace_with(const ::file::path & pszContext, const string & pszNew, const string & pszOld);


   virtual ::file::enum_type get_type(const ::file::path & path, ::payload * pvarQuery);
   virtual ::file::enum_type get_type(const ::file::path & path);


   virtual ::payload length(const ::file::path & path);


   virtual ::payload length(const ::file::path & path, ::payload * pvarQuery);


   virtual ::file::path module();

   
   ::file::path time(const ::file::path & pathBasePath, i32 iDepth = 0, const ::string & strPrefix = nullptr, const ::string & strSuffix = nullptr, bool bTryDelete = false);
   ::file::path time_square(const ::string & strPrefix = nullptr, const ::string & strSuffix = nullptr);
   ::file::path time_log(const ::string & str);


   virtual file_pointer time_square_file(const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);
   virtual file_pointer get(const ::file::path & name);

   virtual file_pointer get_temporary_upload_file(const ::file::path & pathCurrent);


   //template < class T >
   //string time_square(T * p, bool (T:: * pfnOutput)(::stream &, const ::file::path &), const ::file::path & pszSource)
   //{

   //   string strTime = time_square(p);

   //   if (strTime.has_char())
   //   {

   //      if (!output(strTime, p, pfnOutput, pszSource))
   //      {

   //         return "";

   //      }

   //   }

   //   return strTime;

   //}


   //template < typename TYPE >
   //inline void binary_get(const ::payload & payloadFile, TYPE & t)
   //{

   //   auto preader = get_reader(payloadFile);

   //   binary_stream < FILE > stream(preader);

   //   stream.defer_set_loading();

   //   stream >> t;

   //   //return stream.fail() ? ::error_failed : ::success;

   //}


   //template < typename TYPE >
   //inline void binary_set(const ::payload & payloadFile, const TYPE & t)
   //{

   //   auto pwriter = get_writer(payloadFile);

   //   binary_stream < FILE > stream(pwriter);

   //   stream.defer_set_storing();

   //   stream << t;

   //   //return stream.fail() ? ::error_failed : ::success;

   //}


   virtual i32 filterex_time_square(const ::scoped_string & scopedstrPrefix, ::file::path_array & stra);
   virtual bool try_create_file(const ::file::path & path, bool bTryDelete);


   virtual ::payload as_network_payload(const ::payload & payloadFile);
   virtual ::payload safe_get_network_payload(const ::payload & payloadFile);
   virtual string as_string(const ::payload & payloadFile);
   virtual string safe_get_string(const ::payload & payloadFile, ::e_status * pestatus = nullptr);
   virtual void as_memory(const ::payload & payloadFile, memory_base & mem);
   virtual void safe_get_memory(const ::payload & payloadFile, memory_base & mem, ::e_status * pestatus = nullptr);
   virtual ::memory as_memory(const ::payload & payloadFile);
   virtual ::memory safe_get_memory(const ::payload & payloadFile);
   virtual memsize read(const ::payload& payloadFile, void * p, filesize position, memsize size, bool bNoExceptionOnFail = true);
   virtual memsize read_beginning(const ::payload& payloadFile, void * p, memsize size, bool bNoExceptionOnFail = true);
   virtual memory beginning(const ::payload& payloadFile, memsize size, bool bNoExceptionOnFail = true);


   inline string_array lines(const ::payload & payloadFile, bool bAddEmpty = true, bool bNoExceptionOnFail = true)
   {

       string_array straLines;

       get_lines(straLines, payloadFile, bAddEmpty, bNoExceptionOnFail);

       return ::transfer(straLines);

   }


   virtual void get_lines(string_array & stra, const ::payload & payloadFile, bool bAddEmpty = true, bool bNoExceptionOnFail = true);
   virtual void put_lines(const ::payload& payloadFile, const string_array& stra, const plain_text_file_options& options = {});
   //virtual void put_lines_utf8(const ::payload & payloadFile, const string_array & stra);
   

   virtual void put_memory(const ::payload & payloadFile, ::file::file * pfile);
   virtual void put_memory(const ::payload & payloadFile, const ::block & block);
   virtual void put_text(const ::payload& payloadFile, const ::scoped_string & scopedstr);
   virtual void put_text_utf8(const ::payload & payloadFile, const ::scoped_string & scopedstr);


   //virtual void add_contents(const ::payload & payloadFile, const void * pvoidContents, ::count count);
   virtual void add_contents(const ::payload & payloadFile, const ::scoped_string & scopedstrContents);


   virtual bool is_read_only(const ::file::path & psz);

   virtual file_pointer resource_get_file(const ::file::path & path);

   virtual ::file::path sys_temp(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension);
   virtual ::file::path sys_temp_unique(const ::file::path & lpszName);


   virtual ::file::path replace_with_extension(const ::string & strExtension,  const ::file::path & pszFile);
   virtual void set_extension(::file::path & str, const ::scoped_string & scopedstrExtension);


   virtual void normalize(string & str);
   virtual ::std::strong_ordering cmp(const ::file::path & psz1, const ::file::path & psz2);

   virtual string get_hash(const ::payload& payloadFile, enum_hash ehash);

   //virtual string md5(::file::file * pfile);
   virtual string md5(const ::payload & payloadFile);

   //virtual string nessie(::file::file * pfile);
   virtual string nessie(const ::payload & payloadFile);

   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path);

   virtual bool is_link(const ::file::path & path);

   virtual void get_last_write_time(file_time_t * pfile_time, const ::string & strFilename);

   //virtual void dtf(const ::file::path & pszFile, const ::file::path & pszDir);

   //virtual void dtf(const ::file::path & pszFile, ::file::path_array & stra);

   //virtual void ftd(const ::file::path & pszDir, const ::file::path & pszFile);

   // 'n' (natural) terminated ascii number, example: 245765487n
   // pmd5ctx = openssl/md5.h's MD5_CTX
   //virtual void write_n_number(::file::file * pfile, void * pmd5ctx, i64 iNumber);
   //virtual void read_n_number(::file::file * pfile, void * pmd5ctx, i64 & iNumber);

   //virtual void write_gen_string(::file::file * pfile, void * pmd5ctx, string & str);
   //virtual void read_gen_string(::file::file * pfile, void * pmd5ctx, string & str);

   virtual ::file_pointer file_get_file(::file::path path, const ::file::e_open & eopen);

   virtual ::file_pointer data_get_file(string strData, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::folder_pointer get_folder(::file::file * pfile, const ::scoped_string & scopedstrImplementation, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_pointer http_get_file(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_pointer get_file(const ::payload & payloadFile, const ::file::e_open & eopen, ::pointer < ::file::exception > * ppfileexception = nullptr) override;

   virtual ::file_pointer create_native_file(const ::file::path & path, const ::file::e_open & eopen, ::pointer < ::file::exception > * ppfileexception = nullptr);

   virtual ::file_pointer get_reader(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_pointer shared_reader(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);

   virtual ::file_pointer get_writer(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory | ::file::e_open_binary);

   virtual void post_output(const ::file::path & pathOut, const ::file::path & pathDownloading);

   template < typename T >
   bool output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn);

   //virtual bool transfer(::file::file * pfileOut, ::file::file * pfileIn);

   virtual void transfer(::file::file* pfileOut, ::file::file* pfileIn);

   virtual ::file::path dropbox_info_network_payload();


   virtual ::file::path onedrive_global_ini();
   virtual ::file::path onedrive_cid_ini();

//   virtual ::extended::status copy(::payload varTarget, ::payload varSource, bool bFailIfExists = false, enum_extract eextract = e_extract_first);
   //virtual ::extended::status transfer(const ::file::path & pszNew, const ::file::path & psz);
   //virtual ::extended::status del(const ::file::path & psz);
   //virtual ::extended::status rename(const ::file::path & pszNew, const ::file::path & psz);


   //virtual void trash_that_is_not_trash(const ::file::path & psz);
   //virtual void trash_that_is_not_trash(::file::path_array & stra);


   //virtual ::extended::status replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

  virtual bool exists(const ::file::path & pszPath);


  // virtual ::payload length(const ::file::path & pszPath);


   //::file::path time(const ::file::path & pszBasePath, i32 iDepth = 1, const string & pszPrefix = nullptr, const string & pszSuffix = nullptr);


   //virtual file_pointer time_square_file(const ::scoped_string & scopedstrPrefix = nullptr, const ::scoped_string & scopedstrSuffix = nullptr);
   //virtual file_pointer get(const ::file::path & name);



//   inline ::memory as_primitive_memory(const ::payload & payloadFile) { ::memory m; as_memory(payloadFile, m); return m; }
//   inline ::memory as_memory(const ::payload & payloadFile) { return as_primitive_memory(payloadFile); }


   template < class OBJECT >
   void put(const ::payload & payloadFile, OBJECT & a)
   {

      auto writer = get_writer(payloadFile);

      *writer << a;

   }


   void set(const ::payload & payloadFile, const ::memory_base & memory);


   template < class OBJECT >
   void as(OBJECT & a, const ::payload & payloadFile)
   {

      auto reader = get_reader(payloadFile);

      *reader >> a;

   }


   //template < class ARRAY >
   //void to_array(ARRAY & a, const ::payload & payloadFile)
   //{

   //   auto pfile = get_reader(payloadFile);

   //   ::binary_stream < FILE > s(pfile);

   //   __exchange_array(a, s);

   //   //return !s.fail();

   //}


   //virtual void lines(string_array & stra, const ::payload & payloadFile);
   //virtual void put_lines(const ::payload & payloadFile, const string_array & stra);

   //virtual bool put_contents(const ::payload & payloadFile, const void * pvoidContents, ::count count);
   //virtual bool put_contents(const ::payload & payloadFile, const ::scoped_string & scopedstrContents);

   //virtual bool copy?(const ::payload & payloadFile, const ::stream & stream);
   //virtual bool put_contents(const ::payload & payloadFile, memory & mem);
   //virtual bool put_text_utf8(const ::payload & payloadFile, const ::scoped_string & scopedstrContents);


   //virtual bool add_contents(const ::payload & payloadFile, const ::scoped_string & scopedstrContents);


   string sys_temp(const char * lpszName, const ::scoped_string & scopedstrExtension);


   //virtual ::file_pointer get_file(const ::payload & payloadFile, ::u32 nOpenFlags);


   //virtual bool is_read_only(const ::file::path & psz);

   inline auto open_for_reading(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_binary)
   {

      return get_file(payloadFile, eopen | ::file::e_open_read);

   }

   inline auto create_for_writing(const ::payload & payloadFile, const ::file::e_open & eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory)
   {

      return get_file(payloadFile, eopen | ::file::e_open_create | ::file::e_open_write);

   }


   // get a file and if there are exceptions, should show end user friendly messages
   virtual ::file_pointer friendly_get_file(const ::payload & payloadFile, const ::file::e_open & eopen);


   //void dtf(const ::file::path & pszFile, const ::file::path & pszDir);
   void dtf(const ::file::path & pszFile, ::file::path_array & stra, ::file::path_array & straRelative);
   //void ftd(const ::file::path & pszDir, const ::file::path & pszFile);


   virtual void crypto_set(const ::payload & payloadFile, const ::scoped_string & scopedstrData, const ::scoped_string & scopedstrSalt);
   virtual void crypto_get(const ::payload & payloadFile, string & str, const ::scoped_string & scopedstrSalt);


   template < typename TYPE >
   bool save(const ::payload & payloadFile, const TYPE & o)
   {

      return put(payloadFile, o);
   }


   template < typename TYPE >
   inline bool load(TYPE & o, const ::payload & payloadFile)
   {

      return as(o, payloadFile);

   }


   virtual void save_lines(const ::payload & payloadFile, string_array & stra);
   virtual void load_lines(string_array & stra, const ::payload & payloadFile);



   virtual void touch(const ::file::path & path);

   //virtual string md5(const ::payload & payloadFile);

   //virtual string nessie(const ::payload & payloadFile);

   //virtual ::file::path dropbox_info_network_payload();

   //virtual ::file::path onedrive_global_ini();

   //virtual ::file::path onedrive_cid_ini();


};



CLASS_DECL_APEX void set_bypass_cache_if_empty(::payload & payloadFile);
CLASS_DECL_APEX bool get_bypass_cache_if_empty(const ::payload & payloadFile);








template < class T >
bool file_context::output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
{

   ::file::path pathDownloading;

   try
   {

      //stream outputstream(pparticle, FIRST_VERSION);

      //if (!prepare_output(pparticle, outputstream, pathDownloading, os))
      //{

      //   return false;

      //}

      //stream inputstream(pparticle, FIRST_VERSION);

      //if (!prepare_input(pparticle, inputstream, is))
      //{

      //   return false;

      //}

      if (!(p->*pfnOuput)(pfileOut, pfileIn))
      {

         return false;

      }

   }
   catch (...)
   {

      return false;

   }

   //try
   //{

   //   if (!post_output(pparticle, os.m_pfile->GetFilePath(), pathDownloading))
   //   {

   //      return false;

   //   }

   //}
   //catch (...)
   //{

   //   return false;

   //}

   return true;

}

