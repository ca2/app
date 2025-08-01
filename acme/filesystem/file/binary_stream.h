#pragma once


#include "file.h"
#include "stream.h"
#include "acme/prototype/prototype/memory.h"


//// template < typename FILE >
class CLASS_DECL_ACME binary_stream :
    virtual public stream_base
{
public:


   ::file_pointer          m_pfile;
   ::payload               m_payloadOptions;


   binary_stream();
   binary_stream(const ::file_pointer & pfile);
   ~binary_stream() override;


   virtual bool is_end_of_file() const;


   virtual ::payload & options();


   //void write_buffer_length(unsigned long long u);
   //unsigned long long read_buffer_length();



   //RAW_POINTER operator ->() { return m_pfile; }
   //const RAW_POINTER operator ->() const { return m_pfile; }

   /// ::file::path get_file_path() const;

//   string fileName() { return GetFilePath(); }

   // void close() ;

   //inline void defer_set_storing_flag() { if (!has_storing_flag()) set_storing_flag(); }

   //inline void set_storing() { m_bStoring = true; }

   //inline void set_loading() { m_bStoring = false; }

   //stream & operator = (const binary_stream & base) { m_pfile = base.m_pfile; return *this; }
   //stream & operator = (binary_stream & base) { m_pfile = ::transfer(base.m_pfile); return *this; }

   //   FILE_POINTER & operator ->() { m_pfile; }

   // stream * branch(const ::atom &) { return this; }

   ////inline auto seek_begin() { m_pfile->seek_begin(); }
   ////inline auto get_length() const { m_pfile->get_length(); }



   //::atom text_to_factory_id(const ::scoped_string & scopedstr);


   //::string factory_id_to_text(const ::atom & atom);


   //template < typename TYPE >
   //void exchange(TYPE & t)
   //{
   //   if (has_storing_flag())
   //   {
   //      write(t);
   //   }
   //   else
   //   {
   //      read(t);
   //   }
   //}

   //// streaming uses the ordering/sequence and versioning "to omit" the atom
   //// reordering or adding/excluding members leads to ___new format
   //// up-to-date is the only readily-fastly-effortless safe one for streaming
   //// atom-value pairs are safe about reordering/adding/excluding members at most? scenarios
   //template < typename TYPE >
   //void exchange(const ::atom &, TYPE & t)
   //{

   //   ::pointer<::stream>pstream = branch(this, atom);

   //   t.exchange(*pstream);

   //}

   //explicit operator ::file::file * ()  { return m_pfile; }


   // filesize translate(filesize offset, ::enum_seek eseek);


   //string factory_id_to_text(const ::atom & atom) ;
   //::atom text_to_factory_id(const ::scoped_string & scopedstrText) ;


   //template < typename TYPE >
   //stream & operator()(TYPE & t)
   //{

   //   if (has_storing_flag())
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


   // bool is_stream_null();
   // bool is_stream_set();

   //void * get_internal_data() ;
   //memsize get_internal_data_size() const ;
   //bool set_internal_data_size(memsize c) ;
   //filesize get_position() const ;


   //inline memsize read(void * pdata, memsize nCount) { return m_gcount = m_pfile->read(pdata, nCount); }

   //binary_stream & operator >>(memory_base & m);
   //binary_stream & operator <<(const memory_base & m);

   // bool is_reader_null();
   // bool is_reader_set();

    //void read_to_hex(string & str, filesize iStart = -1, filesize iEnd = -1);

    //void write_from_hex(const void * pdata, memsize nCount);

    //void write(const void * pdata, memsize nCount);

    //void write(const void * pdata, memsize nCount, memsize * dwWritten);

   //bool is_writer_null() ;
   //bool is_writer_set() ;

   //void flush() ;

   // void set_size(filesize len);

   // This number represents a following stream of data with this length.
   // So the extra bytes representing the variable length quantity are
   // neglectable and worth due the very fast variable length encoding.
   inline void write_length(unsigned long long u)
   {

      if (u < 255)
      {

         operator <<((unsigned char)u);

      }
      else if (u < 65535)
      {

         operator <<((unsigned char)255);
         operator <<((unsigned short)u);

      }
      else
      {

         operator <<((unsigned char)255);
         operator <<((unsigned short)65535);
         operator <<((unsigned long long)u);

      }

   }


   inline void read_length(unsigned long long & u)
   {

      unsigned char uRead;

      operator >>(uRead);

      //if (!fail())
      //{

      if (uRead < 255)
      {

         u = uRead;

      }
      else
      {

         unsigned short uRead;

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
   binary_stream & operator <<(unsigned char uch) { raw_write(uch);  return *this; }
   binary_stream & operator <<(short sh) { raw_write(sh);  return *this; }
   binary_stream & operator <<(unsigned short ush) { raw_write(ush); return *this; }
#ifdef WINDOWS
   binary_stream & operator <<(unichar wch) {
      raw_write(wch);  return *this;
   }
#endif
   binary_stream & operator <<(bool b) { return operator <<((unsigned char)b ? 1 : 0); }
   binary_stream & operator <<(int i) { raw_write(i); return *this; }
   binary_stream & operator <<(unsigned int ui) { raw_write(ui); return *this; }
   binary_stream & operator <<(long long hi) { raw_write(hi); return *this; }
   binary_stream & operator <<(unsigned long long hn) { raw_write(hn); return *this; }
#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
   binary_stream & operator <<(unsigned long u) { raw_write(u); return *this; }
   binary_stream & operator <<(long l) { raw_write(l);  return *this; }
#endif
   binary_stream & operator <<(float f) { raw_write(f); return *this; }
   binary_stream & operator <<(double d) { raw_write(d); return *this; }
   // void write(const ::int_point & point) { raw_write(point); }
   // void write(const ::int_size & size) { raw_write(size); }
   // void write(const ::int_rectangle &crect) { raw_write(crect); }
   //binary_stream & operator <<(const ::scoped_string & scopedstr);
#ifdef WINDOWS
   binary_stream & operator <<(const unichar * wch) {
      operator <<(string(wch)); return *this;
   }
#endif
   //binary_stream & operator <<(const atom & atom);
   //binary_stream & operator <<(const ::payload & payload);
   //binary_stream & operator <<(const property & property);
   //binary_stream & operator <<(const ::scoped_string & scopedstr);
   ////binary_stream & operator <<(const ::particle * pparticle) ;
   ////binary_stream & operator <<(const matter& matter) ;
   ////binary_stream & operator <<(const ::property_set & set);
   //binary_stream & operator <<(const block & block);
   //binary_stream & operator <<(const element & element);

   /*::filesize tellp();
    void seekp(filesize position);
    void seekp(filesize offset, ::enum_seek eseek);*/
    //void put(char ch);




   binary_stream & operator >>(bool & b) { unsigned char uch; raw_read(uch); b = uch ? true : false; return *this; }
   //binary_stream & operator >>(char & ch) { raw_read(ch); return *this; }
   //binary_stream & operator >>(unsigned char & uch) { raw_read(uch); return *this; }
#ifdef WINDOWS
   binary_stream & operator >>(unichar & wch) { raw_read(wch); return *this; }
#endif


#define NUMBER_TYPE_OPERATION(NUMBER_TYPE, NUMBER_NAME, NUMBER_SHORT_NAME, UPPER_CASE_NAME) \
   binary_stream & operator >>(NUMBER_TYPE & NUMBER_SHORT_NAME) { raw_read(NUMBER_SHORT_NAME); return *this; }
   DO_FOR_NUMBER_TYPES(NUMBER_TYPE_OPERATION)
#undef NUMBER_TYPE_OPERATION


   //binary_stream & operator >>(short & sh) { raw_read(sh); return *this; }
   //binary_stream & operator >>(unsigned short & ush) { raw_read(ush); return *this; }
   //binary_stream & operator >>(int & i) { raw_read(i); return *this; }
   //binary_stream & operator >>(unsigned int & ui) {raw_read(ui); return *this; }
   //binary_stream & operator >>(long long & hi) { raw_read(hi); return *this; }
   //binary_stream & operator >>(unsigned long long & hn) { raw_read(unsigned long long); return *this; }
//#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
//   binary_stream & operator >>(unsigned long & u) {
//      raw_read(u); return *this;
//   }
//   binary_stream & operator >>(long & l) {
//      raw_read(l); return *this;
//   }
//#endif
   //binary_stream & operator >>(float & f) { raw_read(f); return *this; }
   //binary_stream & operator >>(double & d) { raw_read(d); return *this; }
   // void read(::int_point & point) { raw_read(point); }
   //// void read(::int_size & size) { raw_read(size); }
   //// void read(::int_rectangle & rectangle) { raw_read(rectangle); }
   //binary_stream & operator >>(atom & atom);
   //binary_stream & operator >>(::payload & payload);
   // void read_var_type(enum_type & etype);
   // void read_var_body(::payload & payload, enum_type etype);
   //binary_stream & operator >>(property & property);
   //binary_stream & operator >>(string & str);
   //// void read(::particle * pparticle);
   ////binary_stream & operator >>(matter& matter) ;
   ////binary_stream & operator >>(::property_set & set);
   //binary_stream & operator >>(block & block);
   //binary_stream & operator >>(element & element);

   // void save_var_type(::enum_type etype);

   /* void getline(char * sz, character_count n);
   unsigned char get_byte();
   unsigned char peek_byte();*/

   // filesize get_position();
   // filesize seek_from_begin(filesize position);
   // void seek(filesize offset, ::enum_seek eseek);

   //::filesize get_left() const;

   //inline bool has_storing_flag() const { return m_bStoring; }
   //inline bool is_loading() const { return !m_bStoring; }


   // void write_file(const ::file::path & path, const ::matter & matter);
   // void read_file(const ::file::path & path, ::matter & matter);

   // void write_link(const ::scoped_string & scopedstrLink, ::pointer<::matter>& matter);
   // void read_link(const ::scoped_string & scopedstrLink, ::pointer<::matter>& matter);

   // void write_link(const ::matter * preference, const ::scoped_string & scopedstrLink, bool bReadOnly, ::matter * pobjectSaveOptions = nullptr);

   // bool write_link(const ::matter * preference) ;
   // void read_link(::matter * preference) ;


   // bool get_object_link(const ::matter * preference, string & strLink, bool & bReadOnly) ;
   // void set_object_link(const ::matter * preference, const ::scoped_string & scopedstrLink, bool bReadOnly) ;


   // ::file::path get_link_path(const ::scoped_string & scopedstrLink);

   //bool is_version(::collection::index i);

   template < typename BLOCK_TYPE >
   inline void raw_write(const BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no  members
   {

      write({ e_as_block, t });

   }


   template < typename BLOCK_TYPE >
   inline void raw_read(BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no  members
   {

      read({ e_as_block, t });

   }


    //void read(void * pdata, memsize nCount);


   //void xml_export(const ::xml::exportable & xmlexportable);

   //void xml_import(::xml::importable & xmlimportable);


   //template < typename BASE_TYPE >
   //inline stream & save_object(const BASE_TYPE * pparticle);

   //template < typename BASE_TYPE >
   //inline ::pointer<BASE_TYPE>load_object();

    //::pointer<::matter>create_object_from_text(const ::scoped_string & scopedstrText);


   template < typename BLOCK >
   inline binary_stream & operator << (const raw_block < BLOCK > & rawblock) { write(rawblock.block()); return *this; }
   template < typename BLOCK >
   inline binary_stream & operator >> (raw_block < BLOCK > & rawblock) { read(rawblock.block()); return *this; }



   //template < typename TYPE >
   //inline binary_stream & operator <<(const TYPE * p) { *this << *p;  return *this; }

   //template < typename TYPE >
   //inline binary_stream & operator >>(TYPE * p) { *this >> *p; return *this; }

   //template < typename TYPE >
   //inline binary_stream & operator <<(const ::pointer<TYPE>& p) { *this << *p;  return *this; }

   //template < typename TYPE >
   //inline binary_stream & operator >>(::pointer<TYPE>& p) { *this >> *p; return *this; }



   //binary_stream(const ::file_pointer & p) :
   //   m_pfile(p)
   //{

   //   set_ok_flag();

   //   if (m_pfile->m_eopen & ::file::e_open_write)
   //   {

   //      defer_set_storing_flag();

   //   }

   //}


   //binary_stream(const binary_stream & base) :
   //   m_pfile(base.m_pfile)
   //{

   //   //set_ok_flag();

   //   //if (m_pfile->m_eopen & ::file::e_open_write)
   //   //{

   //   //   defer_set_storing_flag();

   //   //}

   //}


   //binary_stream(binary_stream & base) :
   //   m_pfile(::transfer(base.m_pfile))
   //{

   //   set_ok_flag();

   //   if (m_pfile->m_eopen & ::file::e_open_write)
   //   {

   //      defer_set_storing_flag();

   //   }

   //}


   // This number represents a following stream of data with this length.
   // So the extra bytes representing the variable length quantity are
   // neglectable and worth due the very fast variable length encoding.
   void write_buffer_length(unsigned long long u)
   {

      if (u < 255)
      {

         operator <<((unsigned char)u);

      }
      else if (u < 65535)
      {

         operator <<((unsigned char)255);
         operator <<((unsigned short)u);

      }
      else
      {

         operator <<((unsigned char)255);
         operator <<((unsigned short)65535);
         operator <<((unsigned long long)u);

      }

   }

   
   inline unsigned long long read_buffer_length_unbounded_part2()
   {

      unsigned short ush;

      ush = m_pfile->get_u16_unbounded();

      if (ush < 65535)
      {

         return ush;

      }
      else
      {

         unsigned long long ull;

         ull = m_pfile->get_u64_unbounded();

         return ull;

      }

   }


   inline unsigned long long read_buffer_length_unbounded()
   {

      unsigned char uch = m_pfile->get_byte_unbounded();

      return uch < 255 ? uch : read_buffer_length_unbounded_part2();

   }


   virtual unsigned long long read_buffer_length();


   virtual string factory_id_to_text(const ::atom & atom);


   virtual ::atom text_to_factory_id(const ::scoped_string & scopedstr);


   //bool is_open() const
   //{
   //
   //   if (m_pfile.is_null())
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   if (!m_pfile->is_opened())
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   return true;
   //
   //}
   //
   //
   //void close()
   //{
   //
   //   m_pfile.release();
   //
   //}
   //
   //
   //::file::path get_file_path() const
   //{
   //
   //   return m_pfile->get_file_path();
   //
   //}


   //filesize translate(filesize offset, ::enum_seek eseek)
   //{
   //
   //   return m_pfile->translate(offset, eseek);
   //
   //}
   //
   //
   //
   //
   //bool is_stream_null()
   //{
   //   //return is_writer_null() && is_reader_null();
   //   return m_pfile.is_null();
   //}


   //bool is_stream_set()
   //{
   //   //return is_writer_set() || is_reader_set();
   //   return m_pfile.is_set();
   //}


   virtual void write_from_hex(const void * pdata, memsize nCount);


   virtual void write(const ::block & block);


   virtual memsize defer_write(const ::block & block);


   //void write(const ::block & block)
   //{

   //   m_pfile->write(block);

   //}



   //binary_stream & operator <<(const ::property_set & set)
   //{
   //
   //   throw ::exception(todo);
   //
   //   //__exchange_save_array(*this, (::property_set &) set);
   //
   //   return *this;
   //
   //}
   //


   //void flush()
   //{
   //
   //   if (m_pfile.is_set())
   //   {
   //
   //      m_pfile->flush();
   //
   //   }
   //
   //}


   //bool is_writer_null()
   //{
   //
   //   return m_pfile.is_null();
   //
   //}

   //
   //bool is_writer_set()
   //{
   //
   //   return m_pfile.is_set();
   //
   //}


   binary_stream & operator <<(const_char_pointer psz);


   virtual binary_stream & operator <<(const ::range < const_char_pointer >& str);


   //binary_stream & operator <<(const ::particle * pparticle)
   //{
   //
   //   pparticle->write(*this);
   //
   //   return * this;
   //
   //}
   //
   //
   //binary_stream & operator <<(const matter& matter)
   //{
   //
   //   matter.write(*this);
   //
   //   return * this;
   //
   //}


   virtual binary_stream & operator <<(const block & block);

   //binary_stream & operator <<(const ::element & element)
   //{

   //   element.write(*this);

   //   return *this;

   //}


   //void set_size(filesize len)
   //{
   //
   //   m_pfile->set_size(len);
   //
   //}


   void put(char ch)
   {

      operator <<(ch);

      return;

   }


   virtual binary_stream & operator >>(memory_base & m);


   virtual binary_stream & operator <<(const memory_base & m);


   virtual binary_stream & operator >>(atom & atom);

   //void write_file(const ::file::path & path, const ::matter & matter)
   //{
   //
   //   if (path.is_empty())
   //   {
   //
   //      throw io_exception("link path is empty");
   //
   //   }
   //
   //   ::stream stream(e_create_new, this, FIRST_VERSION);
   //
   //   ::file::e_open nOpenFlags;
   //
   //   nOpenFlags = ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_truncate | ::file::e_open_defer_create_directory | ::file::e_open_share_exclusive;
   //
   //   stream.m_pfile = m_pfilecontext->m_pfileapexcontext->file()->get_file(path, nOpenFlags);
   //
   //   matter.write(*this);
   //
   //   return;
   //
   //}
   //
   //
   //void read_file(const ::file::path & path, ::matter & matter)
   //{
   //
   //   if (path.is_empty())
   //   {
   //
   //      throw io_exception("link path is empty");
   //
   //   }
   //
   //   ::stream stream(e_create_new, this, FIRST_VERSION);
   //
   //   stream.m_pfile = m_pfilecontext->m_pfileapexcontext->file()->get_reader(path, ::file::e_open_share_deny_write);
   //
   //   matter.read(*this);
   //
   //   return;
   //
   //}


   //void write_link(const ::scoped_string & scopedstrLink, const ::matter & matter)
   //{
   //
   //   ::file::path path = get_link_path(matter);
   //
   //   if (path.is_empty())
   //   {
   //
   //      throw ::exception(error_io);
   //
   //      return;
   //
   //   }
   //
   //   try
   //   {
   //
   //      write_file(path, matter);
   //
   //   }
   //   catch (...)
   //   {
   //
   //      throw ::exception(error_io);
   //
   //   }
   //
   //   return;
   //
   //}
   //
   //
   //void read_link(const ::scoped_string & scopedstrLink, ::matter & matter)
   //{
   //
   //   ::file::path path = get_link_path(strLink);
   //
   //   if (path.is_empty())
   //   {
   //
   //      throw ::exception(error_io);
   //
   //      return;
   //
   //   }
   //
   //   try
   //   {
   //
   //      read_file(path, matter);
   //
   //   }
   //   catch (...)
   //   {
   //
   //      throw ::exception(error_io);
   //
   //   }
   //
   //   return;
   //
   //}
   //
   //
   //bool get_object_link(const ::matter & matter, string & strLink, bool & bLink)
   //{
   //
   //   return false;
   //
   //}
   //
   //
   //void set_object_link(const ::matter & matter, const ::scoped_string & scopedstrLink, bool bReadOnly)
   //{
   //
   //}
   //
   //
   //void write_link(const ::matter & matter)
   //{
   //
   //   string strLink;
   //
   //   bool bReadOnly;
   //
   //   if (get_object_link(matter, strLink, bReadOnly))
   //   {
   //
   //      write_link(matter, strLink, bReadOnly);
   //
   //   }
   //
   //   return;
   //
   //}
   //
   //
   //void write_link(const ::matter & matter, const ::scoped_string & scopedstrLink, bool bReadOnly)
   //{
   //
   //   write(bReadOnly);
   //
   //   write(strLink);
   //
   //   if (bReadOnly)
   //   {
   //
   //      return;
   //
   //   }
   //
   //   if (strLink.has_character())
   //   {
   //
   //      write_link(strLink, matter);
   //
   //   }
   //
   //   return;
   //
   //}
   //
   //void read_link(::matter & matter)
   //{
   //
   //   string strLink;
   //
   //   bool bReadOnly;
   //
   //   read(bReadOnly);
   //
   //   read(strLink);
   //
   //   //if (bReadOnly)
   //   //{
   //
   //   //   matter["read_only_link"] = strLink;
   //
   //   //}
   //   //else
   //   //{
   //
   //   //   matter["link"] = strLink;
   //
   //   //}
   //
   //   set_object_link(matter, strLink, bReadOnly);
   //
   //
   //   if (strLink.has_character())
   //   {
   //
   //      read_link(strLink, matter);
   //
   //   }
   //
   //   return;
   //
   //}


   //bool get_object_link(const ::matter * preference, string & strLink, bool & bLink)
   //{
   //
   //   return false;
   //
   //}


   //void set_object_link(const ::matter * preference, const ::scoped_string & scopedstrLink, bool bReadOnly)
   //{
   //
   //}


   //bool write_link(const ::particle * pparticle)
   //{
   //
   //   string strLink;
   //
   //   bool bReadOnly;
   //
   //   if (!get_object_link(pparticle, strLink, bReadOnly))
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   write_link(pparticle, strLink, bReadOnly);
   //
   //   return true;
   //
   //}


   //void write_link(const ::matter * preference, const ::scoped_string & scopedstrLink, bool bReadOnly, ::matter * pobjectSaveOptions)
   //{
   //
   //   write(bReadOnly);
   //
   //   write(strLink);
   //
   //   if (bReadOnly)
   //   {
   //
   //      return;
   //
   //   }
   //
   //   if (strLink.has_character())
   //   {
   //
   //      m_pfilecontext->m_pfileapexcontext->save_to_file(strLink, m_pfilevarOptions, preference);
   //
   //   }
   //
   //   return;
   //
   //}


   //void read_link(::matter * preference)
   //{
   //
   //   string strLink;
   //
   //   bool bReadOnly;
   //
   //   read(bReadOnly);
   //
   //   read(strLink);
   //
   //   //if (bReadOnly)
   //   //{
   //
   //   //   matter["read_only_link"] = strLink;
   //
   //   //}
   //   //else
   //   //{
   //
   //   //   matter["link"] = strLink;
   //
   //   //}
   //
   //   set_object_link(preference, strLink, bReadOnly);
   //
   //   if (strLink.has_character())
   //   {
   //
   //      m_pfilecontext->m_pfileapexcontext->load_from_file(preference, strLink);
   //
   //   }
   //
   //   return;
   //
   //}


 

   virtual void read_payload_type(enum_type & etype);


   virtual void save_payload_type(enum_type etype);

   virtual void read_payload_body(::payload & payload, enum_type etype);
   

   virtual  binary_stream & operator >>(string & str);



   //filesize get_position()
   //{
   //
   //   return m_pfile->get_position();
   //
   //}
   //

   //binary_stream & operator >>(matter & matter)
   //{
   //
   //   matter.read(*this);
   //
   //   return * this;
   //
   //}
   //

   //binary_stream & operator >>(::property_set & set)
   //{
   //
   //   throw ::exception(todo);
   //
   //   //__exchange_load_array(*this, set);
   //
   //   return *this;
   //
   //}


   virtual binary_stream & operator >>(block & block);


   //binary_stream & operator >>(::element & element)
   //{

   //   element.read(*this);

   //   return *this;

   //}


   //void * get_internal_data()
   //{
   //
   //   return m_pfile->get_internal_data();
   //
   //}



   //
   //memsize get_internal_data_size() const
   //{
   //
   //   return m_pfile->get_internal_data_size();
   //
   //}


   //
   //
   //bool set_internal_data_size(memsize c)
   //{
   //
   //   return m_pfile->set_internal_data_size(c);
   //
   //}
   //
   //

   //
   //filesize get_position() const
   //{
   //
   //   return m_pfile->get_position();
   //
   //}


   unsigned char get_byte()
   {
      unsigned char b = 0;
      if (m_pfile->read(&b, 1) != 1)
      {

         throw_exception(error_end_of_file);

      }
      return b;
   }


   unsigned char peek_byte()
   {

      return m_pfile->peek_byte();

   }


   virtual void getline(char * sz, character_count n);



   //::memsize gcount()
   //{
   //
   //   return m_pfile->gcount();
   //
   //}



   //filesize seek_from_begin(filesize position)
   //{
   //
   //   return m_pfile->seek(position);
   //
   //}










   //::filesize get_left() const
   //{
   //
   //   return m_pfile->get_left();
   //
   //}




   //bool is_reader_null()
   //{
   //
   //   return m_pfile.is_null() || !(m_pfile->m_eopen & ::file::e_open_read);
   //
   //}
   //
   //
   //
   //
   //bool is_reader_set()
   //{
   //
   //   return m_pfile.is_set() && (m_pfile->m_eopen & ::file::e_open_read);
   //
   //}




   virtual void read_to_hex(string & str, filesize tickStart, filesize tickEnd);

   virtual ::pointer<::matter>create_object_from_text(::particle * pparticle, const ::scoped_string & scopedstrText);




   //
   //
   //::atom text_to_factory_id(const ::scoped_string & scopedstr)
   //{
   //
   //   return str;
   //
   //}
   //
   //
   //::string factory_id_to_text(const ::atom & atom)
   //{
   //
   //   return atom;
   //
   //}


   void read(const ::block & block)
   {

      //if (!fail())
      //{

      m_gcount = m_pfile->read(block);

      if (m_gcount != block.size())
      {

         set_nok();

      }

      /*     }*/

   }


   virtual ::pointer < ::subparticle > read_particle();
   virtual void write_particle(const ::subparticle * pparticle);

};


//// template < typename FILE >
//inline auto __binary_stream(FILE * pfile)
//{
//
//   return binary_stream(pfile);
//
//}


//// template < typename FILE >
//inline auto __binary_stream(const ::pointer<FILE> & pfile)
//{
//
//   return __binary_stream(pfile.m_p);
//
//}



CLASS_DECL_ACME binary_stream& operator <<(binary_stream& stream,const atom& atom);

CLASS_DECL_ACME binary_stream& operator <<(binary_stream& stream,const ::payload& payload);

CLASS_DECL_ACME binary_stream& operator <<(binary_stream& stream, const ::property& property);



CLASS_DECL_ACME binary_stream& operator >>(binary_stream& stream,property& property);

CLASS_DECL_ACME binary_stream& operator >>(binary_stream& stream,::payload& payload);

