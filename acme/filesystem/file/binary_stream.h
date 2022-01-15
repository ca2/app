#pragma once


class CLASS_DECL_ACME binary_stream :
   virtual public stream
{
public:


   using RAW_POINTER = ::file::file *;


   ::file_pointer m_p;


   binary_stream() {}
   binary_stream(const ::file_pointer & p);
   binary_stream(const binary_stream & base);
   binary_stream(binary_stream & base);
   virtual ~binary_stream();

   inline ::payload & options();


   RAW_POINTER operator ->() { return m_p; }
   const RAW_POINTER operator ->() const { return m_p; }

   virtual ::file::path get_file_path() const override;

//   string fileName() { return GetFilePath(); }

   virtual void close() override;

   inline void defer_set_storing() { if (!is_storing()) set_storing(); }

   //inline void set_storing() { m_bStoring = true; }

   //inline void set_loading() { m_bStoring = false; }

   stream & operator = (const binary_stream & base) { m_p = base.m_p; return *this; }
   stream & operator = (binary_stream & base) { m_p = ::move(base.m_p); return *this; }

   //   FILE_POINTER & operator ->() { m_p; }

   virtual stream * branch(const ::id &) { return this; }

   ////inline auto seek_begin() { m_p->seek_begin(); }
   ////inline auto get_length() const { m_p->get_length(); }

   //template < typename TYPE >
   //void exchange(TYPE & t)
   //{
   //   if (is_storing())
   //   {
   //      write(t);
   //   }
   //   else
   //   {
   //      read(t);
   //   }
   //}

   //// streaming uses the ordering/sequence and versioning "to omit" the id
   //// reordering or adding/excluding members leads to new format
   //// up-to-date is the only readily-fastly-effortless safe one for streaming
   //// id-value pairs are safe about reordering/adding/excluding members at most? scenarios
   //template < typename TYPE >
   //void exchange(const ::id &, TYPE & t)
   //{

   //   __pointer(::stream) pstream = branch(this, id);

   //   t.exchange(*pstream);

   //}

   explicit operator ::file::file * ()  { return m_p; }


   virtual filesize translate(filesize offset, ::enum_seek eseek);


   string factory_id_to_text(const ::id & id) override;
   ::id text_to_factory_id(string strText) override;


   template < typename TYPE >
   stream & operator()(TYPE & t)
   {

      if (is_storing())
      {

         *this << t;

      }
      else
      {

         *this >> t;

      }

      return *this;

   }


   bool is_open() const override;


   virtual bool is_stream_null();
   virtual bool is_stream_set();

   void * get_internal_data() override;
   memsize get_internal_data_size() const override;
   bool set_internal_data_size(memsize c) override;
   filesize get_position() const override;


   inline memsize read(void * pdata, memsize nCount) { return m_gcount = m_p->read(pdata, nCount); }

   void read(memory_base & m) override;
   void write(const memory_base & m) override;

   virtual bool is_reader_null();
   virtual bool is_reader_set();

   void read_to_hex(string & str, filesize iStart = -1, filesize iEnd = -1) override;

   void write_from_hex(const void * pdata, memsize nCount) override;

   void write(const void * pdata, memsize nCount) override;

   void write(const void * pdata, memsize nCount, memsize * dwWritten) override;

   bool is_writer_null() override;
   bool is_writer_set() override;

   void flush() override;

   virtual void set_size(filesize len);

   // This number represents a following stream of data with this length.
   // So the extra bytes representing the variable length quantity are
   // neglectable and worth due the very fast variable length encoding.
   inline void write_length(::u64 u)
   {

      if (u < 255)
      {

         write((::u8) u);

      }
      else if (u < 65535)
      {

         write((::u8)255);
         write((::u16)u);

      }
      else
      {

         write((::u8)255);
         write((::u16)65535);
         write((::u64)u);

      }

   }


   inline void read_length(::u64 & u)
   {

      ::u8 uRead;

      read(uRead);

      //if (!fail())
      //{

         if (uRead < 255)
         {

            u = uRead;

         }
         else
         {

            ::u16 uRead;

            read(uRead);

            //if (!fail())
            //{

               if (uRead < 65535)
               {

                  u = uRead;

               }
               else
               {

                  read(u);

               }

            }

      //   }

      //}

   }


   virtual void write(char ch) override { raw_write(ch); }
   virtual void write(uchar uch) override { raw_write(uch); }
   virtual void write(i8 i) override { raw_write(i); }
   virtual void write(i16 i) override { raw_write(i); }
   virtual void write(u16 u) override { raw_write(u); }
#ifdef WINDOWS
   virtual void write(unichar wch) { raw_write(wch); }
#endif
   virtual void write(bool b) override { write((::u8)b ? 1 : 0); }
   virtual void write(i32 i) override { raw_write(i); }
   virtual void write(u32 u) override { raw_write(u); }
   virtual void write(i64 i) override { raw_write(i); }
   virtual void write(u64 u) override { raw_write(u); }
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   virtual void write(unsigned long u) override { raw_write(u); }
   virtual void write(long l) override { raw_write(l); }
   //inline void write (long long ll);
#endif
   virtual void write(float f) override { raw_write(f); }
   virtual void write(double d) override { raw_write(d); }
   //virtual void write(const POINT_I32 & point) { raw_write(point); }
   //virtual void write(const SIZE_I32 & size) { raw_write(size); }
   //virtual void write(const RECTANGLE_I32 & crect) { raw_write(crect); }
   virtual void write(const char * psz) override;
#ifdef WINDOWS
   virtual void write(const unichar * wch) { write(string(wch)); }
#endif
   virtual void write(const id & id) override;
   virtual void write(const ::payload & payload) override;
   virtual void write(const property & property) override;
   virtual void write(const ::string & str) override;
   virtual void write(const matter * pobject) override;
   virtual void write(const matter& matter) override;
   virtual void write(const property_set& set) override;
   virtual void write(const block & block) override;

   /*::filesize tellp();
   virtual void seekp(filesize position);
   virtual void seekp(filesize offset, ::enum_seek eseek);*/
   virtual void put(char ch) override;


   template < typename TYPE >
   inline auto read() { TYPE t; read(t); return t; }


   virtual void read(bool & b) override { auto byte = read<::byte>(); b = byte ? true : false; }
   virtual void read(char & ch) override { raw_read(ch); }
   virtual void read(uchar & uch) override { raw_read(uch); }
#ifdef WINDOWS
   virtual void read(unichar & wch) { raw_read(wch); }
#endif
   virtual void read(i8 & i) override { raw_read(i); }
   virtual void read(i16 & i) override { raw_read(i); }
   virtual void read(u16 & u) override { raw_read(u); }
   virtual void read(i32 & i) override { raw_read(i); }
   virtual void read(u32 & u) override { raw_read(u); }
   virtual void read(i64 & i) override { raw_read(i); }
   virtual void read(u64 & u) override { raw_read(u); }
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   virtual void read(unsigned long & u) override { raw_read(u); }
   virtual void read(long & l) override { raw_read(l); }
#endif
   virtual void read(float & f) override { raw_read(f); }
   virtual void read(double & d) override { raw_read(d); }
   //virtual void read(POINT_I32 & point) { raw_read(point); }
   //virtual void read(SIZE_I32 & size) { raw_read(size); }
   //virtual void read(RECTANGLE_I32 & rectangle) { raw_read(rectangle); }
   virtual void read(id & id) override;
   virtual void read(::payload & payload) override;
   virtual void read_var_type(enum_type & etype) override;
   virtual void read_var_body(::payload & payload, enum_type etype) override;
   virtual void read(property & property) override;
   virtual void read(string & str) override;
   //virtual void read(matter * pobject);
   virtual void read(matter& matter) override;
   virtual void read(property_set& set) override;
   virtual void read(block & block) override;

   virtual void save_var_type(::enum_type etype) override;

   virtual void getline(char * sz, strsize n) override;
   int get();
   int peek();

   virtual filesize get_position();
   //virtual filesize seek_from_begin(filesize position);
   //virtual void seek(filesize offset, ::enum_seek eseek);

   ::filesize get_left() const;

   //inline bool is_storing() const { return m_bStoring; }
   //inline bool is_loading() const { return !m_bStoring; }


   //virtual void write_file(const ::file::path & path, const ::matter & matter);
   //virtual void read_file(const ::file::path & path, ::matter & matter);

   //virtual void write_link(const ::string & strLink, __pointer(::matter) & matter);
   //virtual void read_link(const ::string & strLink, __pointer(::matter) & matter);

   //virtual void write_link(const ::matter * preference, const ::string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions = nullptr);

   //virtual bool write_link(const ::matter * preference) override;
   //virtual void read_link(::matter * preference) override;


   //virtual bool get_object_link(const ::matter * preference, string & strLink, bool & bReadOnly) override;
   //virtual void set_object_link(const ::matter * preference, const ::string & strLink, bool bReadOnly) override;


   //virtual ::file::path get_link_path(string strLink);

   bool is_version(index i);

   template < typename BLOCK_TYPE >
   inline void raw_write(const BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
   {

      write(&t, sizeof(t));

   }


   template < typename BLOCK_TYPE >
   inline void raw_read(BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
   {

      full_read(&t, sizeof(t));

   }


   inline void full_read(void * pdata, memsize nCount)
   {

      //if (!fail())
      //{

         m_gcount = m_p->read(pdata, nCount);

         if (m_gcount != nCount)
         {

            throw_status(error_premature_end_of_file);

         }

 /*     }*/

   }


   //void xml_export(const ::xml::exportable & xmlexportable);

   //void xml_import(::xml::importable & xmlimportable);


   template < typename BASE_TYPE >
   inline stream & save_object(const BASE_TYPE * pobject);

   template < typename BASE_TYPE >
   inline __pointer(BASE_TYPE) load_object();

   virtual __pointer(::matter) create_object_from_text(string strText) override;


};





