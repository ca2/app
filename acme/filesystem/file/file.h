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
      virtual void* get_internal_data();
      virtual const void* get_internal_data() const;
      virtual memsize get_internal_data_size() const;
      virtual bool set_internal_data_size(memsize c);
      virtual bool increase_internal_data_size(memsize c);

      virtual bool is_seekable();

      inline translatable & position() {return *this;}
      virtual filesize get_position() const;
      virtual void set_position(filesize position);
      virtual void increment_position(filesize offset = 1);
      virtual void decrement_position(filesize offset = 1);
      virtual void seek_to_begin();
      virtual void seek_to_end();
      virtual void seek_from_end(filesize offset);
      void translate(filesize offset, ::enum_seek eseek) override;
      virtual int getc();
      virtual int ungetc(int iChar);

      inline filesize get_remaining_byte_count() const { return size() - get_position(); }

      memsize read(void* pdata, memsize nCount) override;

      virtual filesize find(const void* pFind, memsize size, const filesize* limit);

      virtual ::filesize get_left() const;

      virtual string as_string() const;

      virtual void as_memory(memory_base & memory) const;

      virtual void write(const ::block & block);

      void write(const void* pdata, memsize nCount) override;

      virtual void write(const void* pdata, memsize nCount, memsize* dwWritten);

      virtual void from(::file::file * preader, memsize uiBufferSize = 16 * 1024);
      virtual void from_begin(::file::file * preader, memsize uiBufSize = 16 * 1024);
      virtual void to(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);


      virtual void write_file(::file::file * preader, memsize uiBufferSize = 16 * 1024);
      virtual void write_file_from_begin(::file::file * preader, memsize uiBufSize = 16 * 1024);
      virtual void read_file(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);


      void abort() override;
      void flush() override;
      void close() override;


      virtual file & put(char ch);

      virtual file & getline(char* sz, strsize n);
      //virtual int get();
      //virtual int peek();
      virtual bool read(char * pch);
      virtual bool read(byte * puch);
      virtual bool peek(char * pch);
      virtual bool peek(byte * puch);
      //virtual int sgetc();
      //virtual int sbumpc();

      virtual int peek_byte(); // 0-255 - -1 if eof otherwise exception?
      virtual void put_byte_back(::byte b);

      virtual int get_u8(); // 0-255 - -1 if eof otherwise exception?
      inline u8 get_u8_unbounded() { return get_u8(); }

      virtual int get_u16(); // 0-255 - -1 if eof otherwise exception?
      inline u16 get_u16_unbounded() { return get_u16(); }

      virtual bool get_u64(u64 & u64); // 0-255 - -1 if eof otherwise exception?
      inline u64 get_u64_unbounded() { ::u64 u64; get_u64(u64); return u64; }


      inline filesize _get_left() { return get_left(); }


      virtual bool read_string(string & str);
      virtual bool read_string(memory_base & mem);
      virtual bool read_block(block & block);
      virtual ::memory as_memory();
      virtual void as(memory_base & memory);
      virtual ::string as_string();
      virtual void as(::string & str);

      virtual void print(const ::string & str);
      virtual void println(const ::string & str);
      virtual void printf(const char * format, ...);

      ///virtual void write(const string &);
      virtual bool full_read(void * pdata, memsize nCount);

      virtual void write_from_hex(const void * pdata, memsize nCount);

      virtual void set_storing();
      virtual void set_loading();

      virtual bool has_write_mode();

      virtual bool get_status(file_status& rStatus) const;
      virtual ::file::path get_file_path() const;
      virtual void set_file_path(const ::file::path & path);

      virtual void open(const ::file::path& pszFileName, const ::file::e_open & eopen);
      inline void open_for_reading(const ::file::path& pszFileName, const ::file::e_open & eopen =
         ::file::e_open_binary)
      {
        open(pszFileName, eopen | ::file::e_open_read); 

         //open(psz)

      }
      
      virtual void open_for_writing(const ::file::path& pszFileName, const ::file::e_open & eopen =
         ::file::e_open_binary | ::file::e_open_defer_create_directory)
      {
         /*return open(pszFileName, eopen | ::file::e_open_write)*/;

         open(pszFileName, eopen);

      }

      ::file::fmtflags flags() const;

      ::file::fmtflags flags(::file::fmtflags flags);


      //virtual filesize seek_begin(filesize lPos = 0);
      void set_size(filesize dwNewLen) override;
      filesize size() const override;
      inline bool is_empty() const { return size() <= 0; }
      inline void clear() { set_size(0); }

      virtual void lock(filesize dwPos, filesize dwCount);
      virtual void unlock(filesize dwPos, filesize dwCount);


      virtual string get_location() const;


      virtual bool is_valid() const;
      virtual bool is_opened() const;


      virtual void put_lines(const string_array& stra);


   };

   
   CLASS_DECL_ACME void set_no_cache(::payload& payload);


 } // namespace file



