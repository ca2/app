#pragma once


//////#include "acme/primitive/primitive/object.h"
//#include "acme/filesystem/filesystem/path.h"
#include "streamable.h"


namespace file
{


   enum enum_buffer
   {

      e_buffer_read,
      e_buffer_write,
      e_buffer_commit,
      e_buffer_check

   };


   class exception;
   struct file_status;

   class file;


   class CLASS_DECL_ACME file :
      virtual public streamable
   {
   public:


      ::file::e_open             m_eopen;
      ::file::path               m_path;
      ::file::e_state            m_estate;
      class ::time               m_timeErrorBlockTimeout;


      file();
      explicit file(const ::file::path & path);
      ~file() override;


      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;


      virtual bool is_end_of_file() const;
      virtual void set_end_of_file();

      inline bool _is_end_of_file() const { return is_end_of_file(); }

      virtual bool is_in_memory_file() const;
      
      virtual ::u8 * full_data_begin();

      virtual ::u8 * full_data_end();

      virtual const ::u8 * full_data_begin() const;

      virtual const ::u8 * full_data_end() const;

      
      inline ::block full_data(memsize start = 0, memsize count = -1)
      { 
         
         return ::block(full_data_begin(), full_data_end())(start, count); 
      
      }


      inline ::block full_data(memsize start = 0, memsize count = -1) const
      {

         return ::block(full_data_begin(), full_data_end())(start, count);

      }


      inline memsize full_data_size() const { return full_data_end() - full_data_begin(); }

      inline bool full_data_is_set() const { return ::is_set(full_data_begin()); }


      virtual ::u8 * data_begin();

      virtual ::u8 * data_end();

      virtual const ::u8 * data_begin() const;

      virtual const ::u8 * data_end() const;

      
      inline ::block data(memsize start = 0, memsize count = -1)
      {

         return ::block(data_begin(), data_end())(start, count);

      }


      inline ::block data(memsize start = 0, memsize count = -1) const
      {

         return ::block(data_begin(), data_end())(start, count);

      }

      inline memsize data_size() const { return data_end() - data_begin(); }

      inline bool data_is_set() const { return ::is_set(data_begin()) && data_size() > 0; }


      //virtual const void* get_internal_data() const;
      //virtual memsize get_internal_data_size() const;
      
      /// @brief full_data is plain memory segment mapping entire file
      /// @param c size to set to
      /// @return true if full_data is supported
      virtual bool full_data_set_size(memsize c);


      /// @brief full_data is plain memory segment mapping entire file
      /// @param c size to grow by
      /// @return true if full_data is supported 
      virtual bool full_data_increase_size(memsize c);


      void translate(filesize offset, ::enum_seek eseek) override;
      virtual int getc();
      virtual int ungetc(int iChar);

      inline filesize get_remaining_byte_count() const { return size() - get_position(); }

      //memsize read(void* pdata, memsize nCount) override;

      using ::file::readable::read;
      memsize read(void * p, ::memsize s) override;


      virtual filesize find(const void* pFind, memsize size, const filesize* limit);

      ::filesize right_size() const override;


      template < typename TYPE >
      void write_as_block(const TYPE & t) { write({ e_as_block, t }); }


      using ::file::writable::write;
      void write(const void * p, memsize s) override;
      
      using ::file::writable::defer_write;
      memsize defer_write(const void * dataToWrite, memsize amountToWrite) override;
      
      
      virtual void write(::file::readable * preader, memsize uiBufferSize = 16_MiB);
      virtual void write_from_beginning(::file::streamable * preader, memsize uiBufSize = 16_MiB);

      //void write(const void* pdata, memsize nCount) override;

      //virtual void write(const void* pdata, memsize nCount, memsize* dwWritten);

      //virtual void from(::file::file * preader, memsize uiBufferSize = 16 * 1024);
      //virtual void from_begin(::file::file * preader, memsize uiBufSize = 16 * 1024);
      //virtual void to(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);


      ///virtual void read_file(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);


      ::file::file * get_file() override; 


      void abort() override;
      void flush() override;
      void close() override;


      virtual file & put(char ch);

      virtual file & getline(char* sz, strsize n);
      //virtual int get();
      //virtual int peek();
      virtual bool read(char * pch);
      virtual bool read(::u8 * puch);
      virtual bool peek(char * pch);
      virtual bool peek(::u8 * puch);
      //virtual int sgetc();
      //virtual int sbumpc();

      virtual int peek_byte(); // 0-255 - -1 if eof otherwise exception?
      virtual void put_byte_back(::u8 b);

      virtual int get_u8(); // 0-255 - -1 if eof otherwise exception?
      inline u8 get_u8_unbounded() { return get_u8(); }

      virtual int get_u16(); // 0-255 - -1 if eof otherwise exception?
      inline u16 get_u16_unbounded() { return get_u16(); }

      virtual bool get_u64(u64 & u64); // 0-255 - -1 if eof otherwise exception?
      inline u64 get_u64_unbounded() { ::u64 u64; get_u64(u64); return u64; }


      inline filesize _right_size() { return this->right_size(); }


      virtual bool read_string(string & str);
      virtual bool read_string(memory_base & mem);
      virtual bool read_block(block & block);
      
      //virtual ::memory right_memory();
      //virtual void right_memory(memory_base & memory);
      //virtual ::string right_string();
      //virtual void right_string(::string & str);

      virtual void print(const ::string & str);
      virtual void println(const ::string & str);
      virtual void printf(const char * format, ...);

      ///virtual void write(const string &);
      virtual bool full_read(const ::block & block);

      virtual void write_from_hex(const ::block & block);

      virtual void set_storing();
      virtual void set_loading();

      virtual bool has_write_mode();

      virtual file_status get_status() const;
      virtual ::file::path get_file_path() const;
      virtual void set_file_path(const ::file::path & path);

      
      virtual void open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr);
      
      
      inline void open_for_reading(const ::file::path& pszFileName, ::file::e_open eopen =
         ::file::e_open_binary, ::pointer < ::file::exception > * pfileexception = nullptr)
      {

         open(pszFileName, eopen | ::file::e_open_read); 

      }
      

      virtual void open_for_writing(const ::file::path& pszFileName, ::file::e_open eopen =
         ::file::e_open_binary | ::file::e_open_defer_create_directory, ::pointer < ::file::exception > * pfileexception = nullptr)
      {

         open(pszFileName, eopen | ::file::e_open_write);

      }


      ::file::fmtflags flags() const;

      ::file::fmtflags flags(::file::fmtflags flags);


      //virtual filesize seek_begin(filesize lPos = 0);
      void set_size(filesize dwNewLen) override;
      filesize size() const override;
      inline bool is_empty() const { return size() <= 0; }
      inline bool has_data() const { return size() > 0; }
      inline void clear() { set_size(0); }

      virtual void lock(filesize dwPos, filesize dwCount);
      virtual void unlock(filesize dwPos, filesize dwCount);


      virtual string get_location() const;


      virtual bool is_valid() const;
      virtual bool is_opened() const;


      virtual void put_lines(const string_array& stra);

      virtual class ::time modification_time();
      virtual void set_modification_time(const class ::time & time);


   };

   
   CLASS_DECL_ACME void set_no_cache(::payload& payload);


 } // namespace file



