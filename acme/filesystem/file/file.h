#pragma once




namespace file
{


   enum e_buffer
   {
      buffer_read,
      buffer_write,
      buffer_commit,
      buffer_check
   };




   class exception;
   struct file_status;

   class file;






   class CLASS_DECL_ACME file :
      virtual public ::object,
      virtual public streamable
   {
   public:


      ::file::e_open             m_eopen;
      ::file::path               m_path;
      ::file::e_state            m_estate;
      ::millis                   m_millisErrorBlockTimeout;


      file();
      explicit file(const ::file::path & path);
      ~file() override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void* get_internal_data();
      virtual const void* get_internal_data() const;
      virtual memsize get_internal_data_size() const;
      virtual bool set_internal_data_size(memsize c);
      virtual bool increase_internal_data_size(memsize c);

      virtual bool is_seekable();

      inline translatable & position() {return *this;}
      virtual filesize get_position() const;
      virtual filesize set_position(filesize position);
      virtual filesize increment_position(filesize offset = 1);
      virtual filesize decrement_position(filesize offset = 1);
      virtual filesize seek_to_begin();
      virtual filesize seek_to_end();
      virtual filesize seek_from_end(filesize offset);
      //virtual filesize seek(filesize offset, ::enum_seek eseek);
      ::index translate(::count c, ::enum_seek eseek) override;
      virtual int getc();
      virtual int ungetc(int iChar);

      inline filesize get_remaining_byte_count() const { return get_size() - get_position(); }

      virtual memsize read(void* pdata, memsize nCount);

      virtual filesize find(const void* pFind, memsize size, const filesize* limit);

      virtual ::filesize get_left() const;

      string to_string() const override;

      virtual void as_memory(memory_base & memory) const;

      virtual void write(const memory_base & memory);

      virtual void write(const void* pdata, memsize nCount);

      virtual void write(const void* pdata, memsize nCount, memsize* dwWritten);

      virtual void from(::file::file * preader, memsize uiBufferSize = 16 * 1024);
      virtual void from_begin(::file::file * preader, memsize uiBufSize = 16 * 1024);
      virtual void to(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);


      virtual void write_file(::file::file * preader, memsize uiBufferSize = 16 * 1024);
      virtual void write_file_from_begin(::file::file * preader, memsize uiBufSize = 16 * 1024);
      virtual void read_file(::file::file * pwriter, memsize uiBufferSize = 1024 * 1024);



      virtual void close();

      virtual void flush();

      virtual file & put(char ch);

      virtual file & getline(char* sz, strsize n);
      virtual int get();
      virtual int peek();
      virtual bool read(char * pch);
      virtual bool read(uchar * puch);
      virtual bool peek(char * pch);
      virtual bool peek(uchar * puch);
      //virtual int sgetc();
      //virtual int sbumpc();

      virtual int peek_character();
      virtual int get_character();
      virtual int put_character_back(int iCharacter);

      virtual bool read_string(string & str);
      virtual bool read_string(memory_base & mem);
      virtual bool read_block(const block & block);
      virtual bool full_read(memory_base & memory);
      virtual bool full_read_string(string & str);

      virtual void print(const ::string & str);
      virtual void println(const ::string & str);
      virtual void printf(const char * format, ...);

      virtual void write(const string &);
      virtual bool full_read(void * pdata, memsize nCount);

      virtual void write_from_hex(const void * pdata, memsize nCount);

      virtual void set_storing();
      virtual void set_loading();

      virtual bool has_write_mode();

      virtual bool get_status(file_status& rStatus) const;
      virtual ::file::path get_file_path() const;
      virtual void set_file_path(const ::file::path & path);

      virtual ::extended::status open(const ::file::path& pszFileName, const ::file::e_open & eopen);
      inline ::extended::status open_for_reading(const ::file::path& pszFileName, const ::file::e_open & eopen =
         ::file::e_open_binary)
      {
         return open(pszFileName, eopen | ::file::e_open_read);

      }
      virtual ::extended::status open_for_writing(const ::file::path& pszFileName, const ::file::e_open & eopen =
         ::file::e_open_binary | ::file::e_open_defer_create_directory)
      {
         return open(pszFileName, eopen | ::file::e_open_write);

      }

      ::file::fmtflags flags() const;

      ::file::fmtflags flags(::file::fmtflags flags);


      //virtual filesize seek_begin(filesize lPos = 0);
      virtual void set_size(filesize dwNewLen);
      virtual filesize get_size() const;
      inline bool is_empty() const { return get_size() <= 0; }
      inline void clear() { set_size(0); }

      virtual void lock(filesize dwPos, filesize dwCount);
      virtual void unlock(filesize dwPos, filesize dwCount);


      virtual string get_location() const;


      virtual bool is_valid() const;
      virtual bool is_opened() const;


   };

   
   CLASS_DECL_ACME void set_no_cache(::payload& payload);


 } // namespace file






//}
