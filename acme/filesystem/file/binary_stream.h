#pragma once




class CLASS_DECL_ACME binary_stream :
   virtual public stream_base
{
public:


   using RAW_POINTER = ::file::file *;


   ::file_pointer m_p;


   binary_stream() {}
   binary_stream(const ::file_pointer & p);
   binary_stream(const binary_stream & base);
   binary_stream(binary_stream & base);
   ~binary_stream();



   inline bool is_end_of_file() const { return m_p->is_end_of_file(); }


   inline ::payload & options();


   void write_buffer_length(::u64 u);
   ::u64 read_buffer_length();



   RAW_POINTER operator ->() { return m_p; }
   const RAW_POINTER operator ->() const { return m_p; }

   ///virtual ::file::path get_file_path() const;

//   string fileName() { return GetFilePath(); }

   //virtual void close() ;

   inline void defer_set_storing() { if (!is_storing()) set_storing(); }

   //inline void set_storing() { m_bStoring = true; }

   //inline void set_loading() { m_bStoring = false; }

   //stream & operator = (const binary_stream & base) { m_p = base.m_p; return *this; }
   //stream & operator = (binary_stream & base) { m_p = ::move(base.m_p); return *this; }

   //   FILE_POINTER & operator ->() { m_p; }

   //virtual stream * branch(const ::atom &) { return this; }

   ////inline auto seek_begin() { m_p->seek_begin(); }
   ////inline auto get_length() const { m_p->get_length(); }



   ::atom text_to_factory_id(const ::string & str);


   ::string factory_id_to_text(const ::atom & atom);


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

   //// streaming uses the ordering/sequence and versioning "to omit" the atom
   //// reordering or adding/excluding members leads to memory_new format
   //// up-to-date is the only readily-fastly-effortless safe one for streaming
   //// atom-value pairs are safe about reordering/adding/excluding members at most? scenarios
   //template < typename TYPE >
   //void exchange(const ::atom &, TYPE & t)
   //{

   //   ::pointer<::stream>pstream = branch(this, atom);

   //   t.exchange(*pstream);

   //}

   //explicit operator ::file::file * ()  { return m_p; }


   //virtual filesize translate(filesize offset, ::enum_seek eseek);


   //string factory_id_to_text(const ::atom & atom) ;
   //::atom text_to_factory_id(string strText) ;


   //template < typename TYPE >
   //stream & operator()(TYPE & t)
   //{

   //   if (is_storing())
   //   {

   //      *this << t;

   //   }
   //   else
   //   {

   //      *this >> t;

   //   }

   //   return *this;

   //}


   //bool is_open() const ;


   //virtual bool is_stream_null();
   //virtual bool is_stream_set();

   //void * get_internal_data() ;
   //memsize get_internal_data_size() const ;
   //bool set_internal_data_size(memsize c) ;
   //filesize get_position() const ;


   //inline memsize read(void * pdata, memsize nCount) { return m_gcount = m_p->read(pdata, nCount); }

   binary_stream & operator >>(memory_base & m);
   binary_stream & operator <<(const memory_base & m);

   //virtual bool is_reader_null();
   //virtual bool is_reader_set();

   virtual void read_to_hex(string & str, filesize iStart = -1, filesize iEnd = -1);

   virtual void write_from_hex(const void * pdata, memsize nCount);

   virtual void write(const void * pdata, memsize nCount);

   virtual void write(const void * pdata, memsize nCount, memsize * dwWritten);

   //bool is_writer_null() ;
   //bool is_writer_set() ;

   //void flush() ;

   //virtual void set_size(filesize len);

   // This number represents a following stream of data with this length.
   // So the extra bytes representing the variable length quantity are
   // neglectable and worth due the very fast variable length encoding.
   inline void write_length(::u64 u)
   {

      if (u < 255)
      {

         operator <<((::u8)u);

      }
      else if (u < 65535)
      {

         operator <<((::u8)255);
         operator <<((::u16)u);

      }
      else
      {

         operator <<((::u8)255);
         operator <<((::u16)65535);
         operator <<((::u64)u);

      }

   }


   inline void read_length(::u64 & u)
   {

      ::u8 uRead;

      operator >>(uRead);

      //if (!fail())
      //{

      if (uRead < 255)
      {

         u = uRead;

      }
      else
      {

         ::u16 uRead;

         operator >>(uRead);

         //if (!fail())
         //{

         if (uRead < 65535)
         {

            u = uRead;

         }
         else
         {

            operator >>(u);

         }

      }

      //   }

      //}

   }


   binary_stream & operator <<(char ch) { raw_write(ch); return *this; }
   binary_stream & operator <<(uchar uch) {
      raw_write(uch);  return *this;
   }
   binary_stream & operator <<(i8 i) {
      raw_write(i);  return *this;
   }
   binary_stream & operator <<(i16 i) {
      raw_write(i);  return *this;
   }
   binary_stream & operator <<(u16 u) {
      raw_write(u); return *this;
   }
#ifdef WINDOWS
   binary_stream & operator <<(unichar wch) {
      raw_write(wch);  return *this;
   }
#endif
   binary_stream & operator <<(bool b) { return operator <<((::u8)b ? 1 : 0); }
   binary_stream & operator <<(i32 i) {
      raw_write(i);  return *this;
   }
   binary_stream & operator <<(u32 u) {
      raw_write(u);  return *this;
   }
   binary_stream & operator <<(i64 i) {
      raw_write(i); return *this;
   }
   binary_stream & operator <<(u64 u) {
      raw_write(u); return *this;
   }
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   binary_stream & operator <<(unsigned long u) {
      raw_write(u); return *this;
   }
   binary_stream & operator <<(long l) {
      raw_write(l);  return *this;
   }
   //inline void write (long long ll);
#endif
   binary_stream & operator <<(float f) {
      raw_write(f); return *this;
   }
   binary_stream & operator <<(double d) {
      raw_write(d); return *this;
   }
   //virtual void write(const POINT_I32 & point) { raw_write(point); }
   //virtual void write(const SIZE_I32 & size) { raw_write(size); }
   //virtual void write(const RECTANGLE_I32 & crect) { raw_write(crect); }
   binary_stream & operator <<(const char * psz);
#ifdef WINDOWS
   binary_stream & operator <<(const unichar * wch) {
      operator <<(string(wch)); return *this;
   }
#endif
   binary_stream & operator <<(const atom & atom);
   binary_stream & operator <<(const ::payload & payload);
   binary_stream & operator <<(const property & property);
   binary_stream & operator <<(const ::string & str);
   //binary_stream & operator <<(const matter * pobject) ;
   //binary_stream & operator <<(const matter& matter) ;
   //binary_stream & operator <<(const property_set & set);
   binary_stream & operator <<(const block & block);
   binary_stream & operator <<(const element & element);

   /*::filesize tellp();
   virtual void seekp(filesize position);
   virtual void seekp(filesize offset, ::enum_seek eseek);*/
   virtual void put(char ch);




   binary_stream & operator >>(bool & b) { byte byte; raw_read(byte); b = byte ? true : false; return *this; }
   binary_stream & operator >>(char & ch) {
      raw_read(ch); return *this;
   }
   binary_stream & operator >>(uchar & uch) {
      raw_read(uch); return *this;
   }
#ifdef WINDOWS
   binary_stream & operator >>(unichar & wch) {
      raw_read(wch); return *this;
   }
#endif
   binary_stream & operator >>(i8 & i) {
      raw_read(i); return *this;
   }
   binary_stream & operator >>(i16 & i) {
      raw_read(i); return *this;
   }
   binary_stream & operator >>(u16 & u) {
      raw_read(u); return *this;
   }
   binary_stream & operator >>(i32 & i) {
      raw_read(i); return *this;
   }
   binary_stream & operator >>(u32 & u) {
      raw_read(u); return *this;
   }
   binary_stream & operator >>(i64 & i) {
      raw_read(i); return *this;
   }
   binary_stream & operator >>(u64 & u) {
      raw_read(u); return *this;
   }
#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
   binary_stream & operator >>(unsigned long & u) {
      raw_read(u); return *this;
   }
   binary_stream & operator >>(long & l) {
      raw_read(l); return *this;
   }
#endif
   binary_stream & operator >>(float & f) {
      raw_read(f); return *this;
   }
   binary_stream & operator >>(double & d) {
      raw_read(d); return *this;
   }
   //virtual void read(POINT_I32 & point) { raw_read(point); }
   //virtual void read(SIZE_I32 & size) { raw_read(size); }
   //virtual void read(RECTANGLE_I32 & rectangle) { raw_read(rectangle); }
   binary_stream & operator >>(atom & atom);
   binary_stream & operator >>(::payload & payload);
   virtual void read_var_type(enum_type & etype);
   virtual void read_var_body(::payload & payload, enum_type etype);
   binary_stream & operator >>(property & property);
   binary_stream & operator >>(string & str);
   //virtual void read(matter * pobject);
   //binary_stream & operator >>(matter& matter) ;
   //binary_stream & operator >>(property_set & set);
   binary_stream & operator >>(block & block);
   binary_stream & operator >>(element & element);

   virtual void save_var_type(::enum_type etype);

   virtual void getline(char * sz, strsize n);
   ::byte get_byte();
   ::byte peek_byte();

   //virtual filesize get_position();
   //virtual filesize seek_from_begin(filesize position);
   //virtual void seek(filesize offset, ::enum_seek eseek);

   //::filesize get_left() const;

   //inline bool is_storing() const { return m_bStoring; }
   //inline bool is_loading() const { return !m_bStoring; }


   //virtual void write_file(const ::file::path & path, const ::matter & matter);
   //virtual void read_file(const ::file::path & path, ::matter & matter);

   //virtual void write_link(const ::string & strLink, ::pointer<::matter>& matter);
   //virtual void read_link(const ::string & strLink, ::pointer<::matter>& matter);

   //virtual void write_link(const ::matter * preference, const ::string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions = nullptr);

   //virtual bool write_link(const ::matter * preference) ;
   //virtual void read_link(::matter * preference) ;


   //virtual bool get_object_link(const ::matter * preference, string & strLink, bool & bReadOnly) ;
   //virtual void set_object_link(const ::matter * preference, const ::string & strLink, bool bReadOnly) ;


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

      read(&t, sizeof(t));

   }


   virtual void read(void * pdata, memsize nCount);


   //void xml_export(const ::xml::exportable & xmlexportable);

   //void xml_import(::xml::importable & xmlimportable);


   //template < typename BASE_TYPE >
   //inline stream & save_object(const BASE_TYPE * pobject);

   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE>load_object();

   virtual ::pointer<::matter>create_object_from_text(string strText);


   template < typename BLOCK >
   inline binary_stream & operator << (const memory_template < BLOCK > & mem) { write(mem.get_data(), mem.get_size()); return *this; }
   template < typename BLOCK >
   inline binary_stream & operator >> (memory_template < BLOCK > & mem) { read(mem.get_data(), mem.get_size()); return *this; }



   template < typename TYPE >
   inline binary_stream & operator <<(const TYPE * p) { *this << *p;  return *this; }

   template < typename TYPE >
   inline binary_stream & operator >>(TYPE * p) { *this >> *p; return *this; }

   template < typename TYPE >
   inline binary_stream & operator <<(const ::pointer<TYPE>& p) { *this << *p;  return *this; }

   template < typename TYPE >
   inline binary_stream & operator >>(::pointer<TYPE>& p) { *this >> *p; return *this; }



   template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, enum_type t_etypePayload >
   inline binary_stream & operator <<(const ::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & a)
   {

      ::count c = a.get_count();
      *this << c;
      for (auto & element : a)
      {
         *this << element;
         if (nok())
         {
            break;

         }
      }

      return *this;

   }

   template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, enum_type t_etypePayload >
   inline binary_stream & operator >>(::array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > & a)
   {

      ::count c;
      *this >> c;
      if (is_ok())
      {
         auto i = c;
         while (i > 0)
         {
            auto & t = a.add_new();
            *this >> t;
            if (nok())
            {

               a.erase_last();

               break;

            }
            i--;
         }

      }

      return *this;

   }


   template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
   inline binary_stream & operator <<(const map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > & m)
   {


      ::count c = m.get_count();

      *this << c;

      for (auto & pair : m)
      {

         *this << pair.element1();

         //if (s.fail())
           // break;

         *this << pair.element2();

         //if (s.fail())
           // break;

      }

      return *this;

   }


   template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
   inline binary_stream & operator >>(map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > & m)
   {

      ::count c = 0;

      *this >> c;

      auto i = c;

      while (i > 0)
      {

         i--;
         typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::BASE_KEY element1;
         //typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::BASE_VALUE element2;
         *this >> element1;
         //if (s.fail())
           // break;
         *this >> m[element1];
         //if (s.fail())
           // break;
         //m.set_at(element1, element2);
      }

      return *this;

   }


};



