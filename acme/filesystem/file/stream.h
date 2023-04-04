#pragma once


#include "acme/primitive/primitive/particle_flags.h"


//#define __EXCHANGE(xxx) binary_stream < FILE >.stream_exchange(__STRING(xxx), m_##xxx)
//#define __TYPE_EXCHANGE(xxx) binary_stream < FILE >.stream_exchange(__STRING(xxx), t.m_##xxx)

//class payload_stream;


// Use cases:
// - Entry point_i32 convenience syntax sugar
// - syntax sugar
//template < typename TYPE >
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & binary_stream < FILE >, TYPE & t);
//
//template < typename TYPE >
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & binary_stream < FILE >, const TYPE & t);
//
//template < typename TYPE >
//inline payload_stream & operator >> (payload_stream & binary_stream < FILE >, TYPE & t);
//
//template < typename TYPE >
//inline payload_stream & operator << (payload_stream & binary_stream < FILE >, const TYPE & t);
//
//template < typename TYPE >
//inline text_stream & operator >> (text_stream & binary_stream < FILE >, TYPE & t);
//
//template < typename TYPE >
//inline text_stream & operator << (text_stream & binary_stream < FILE >, const TYPE & t);

//template < typename TYPE >
//inline ::file::file & operator >> (::file::file & file, TYPE & t);
//
//template < typename TYPE >
//inline ::file::file & operator << (::file::file & file, const TYPE & t);
//



 /*inline void __exchange(::binary_stream < FILE > & s, bool & b);


 inline void __exchange(::binary_stream < FILE > & s, i8 & i);
 inline void __exchange(::binary_stream < FILE > & s, i16 & i);
 inline void __exchange(::binary_stream < FILE > & s, i32 & i);
 inline void __exchange(::binary_stream < FILE > & s, i64 & i);
 inline void __exchange(::binary_stream < FILE > & s, u8 & u);
 inline void __exchange(::binary_stream < FILE > & s, u16 & u);
 inline void __exchange(::binary_stream < FILE > & s, u32 & u);
 inline void __exchange(::binary_stream < FILE > & s, u64 & u);


 inline void __exchange(::binary_stream < FILE > & s, long & l);


 inline void __exchange(::binary_stream < FILE > & s, float & f);
 inline void __exchange(::binary_stream < FILE > & s, double & d);
 inline void __exchange(::binary_stream < FILE > & s, ::earth::time & time);
 inline void __exchange(::binary_stream < FILE > & s, const ::scoped_string & scopedstr);
 inline void __exchange(::binary_stream < FILE > & s, string & str);
 inline void __exchange(::binary_stream < FILE > & s, ::file::path & path);
 inline void __exchange(::binary_stream < FILE > & s, ::atom & atom);
 inline void __exchange(::binary_stream < FILE > & s, ::payload & payload);
 inline void __exchange(::binary_stream < FILE > & s, ::property & property);
 inline void __exchange(::binary_stream < FILE > & s, ::matter & matter);


 inline void __exchange(::binary_stream < FILE > & s, RECTANGLE_I32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, RECTANGLE_I64 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, RECTANGLE_F32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, RECTANGLE_F64 & rectangle);


 inline void __exchange(::binary_stream < FILE > & s, SIZE_I32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, SIZE_I64 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, SIZE_F32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, SIZE_F64 & rectangle);


 inline void __exchange(::binary_stream < FILE > & s, POINT_I32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, POINT_I64 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, POINT_F32 & rectangle);
 inline void __exchange(::binary_stream < FILE > & s, POINT_F64 & rectangle);


template < typename OBJECT >
inline void __exchange(::binary_stream < FILE > & s, ::pointer<OBJECT>& pparticle)
{
   __exchange(s, __typed_defer_create(pparticle));
}


template < typename BLOCK_TYPE >
inline void __exchange(binary_stream < FILE > & s, memory_template < BLOCK_TYPE > & block);

template < typename ARRAY >
inline void __exchange_array(::binary_stream < FILE > & s, const ARRAY & array) { __exchange_array(s, (ARRAY &)array); }


inline void __exchange(::binary_stream < FILE > & s, const ::file::path_array & patha) { __exchange_array(s, patha); }

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array) { __exchange_array(s, (::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > &)array); }

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, const ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array) { __exchange_array(s, (::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > &)array); }

template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
inline void __exchange(::binary_stream < FILE > & s, const ::numeric_array < TYPE, m_etypeContainer > & array) { __exchange_array(s, (::numeric_array < TYPE, m_etypeContainer > &) array); }

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, const ::string_array_base < Type, RawType, m_etypeContainer > & array) { __exchange_array(s, (::string_array_base < Type, RawType, m_etypeContainer > &) array); }

template < typename ARRAY >
inline void __exchange_save_array(::binary_stream < FILE > & s, ARRAY & array);

template < typename ARRAY >
inline void __exchange_load_array(::binary_stream < FILE > & s, ARRAY & array);

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array);

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array);

template < typename TYPE, ::enum_type m_etypeContainer = e_type_element >
inline void __exchange(::binary_stream < FILE > & s, ::numeric_array < TYPE, m_etypeContainer > & array);

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline void __exchange(::binary_stream < FILE > & s, ::string_array_base < Type, RawType, m_etypeContainer > & array);*/


#define FIRST_VERSION 0


enum enum_set_storing
{

   e_set_storing

};


enum enum_set_loading
{

   e_set_loading

};


#pragma pack(push, print_formatting, 1)


class print_formatting
{
public:


   ::file::fmtflags           m_fmtflags;
   ::i8                       m_width;
   ::i8                       m_precision;


   print_formatting & operator <<(::file::fmtflags e)
   {

      m_fmtflags = (::file::fmtflags)((((::i32)m_fmtflags)) | ((::i32)e));

      return *this;

   }


   filesize precision() const { return m_precision; }

   filesize precision(i8 prec) { return m_precision = prec; }

   filesize width() const { return m_width; }

   filesize width(i8 wide) { return m_width = wide; }


   ::file::fmtflags setf(::file::fmtflags flagsAdd)
   {

      return m_fmtflags = (::file::fmtflags)((((::i32)m_fmtflags)) | ((::i32)flagsAdd));

   }


   ::file::fmtflags setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
   {

      setf(flagsAdd);

      return m_fmtflags = (::file::fmtflags)((((::i32)m_fmtflags)) & (~(::i32)flagsAdd));

   }



};


#pragma pack(pop, print_formatting)


class stream_base :
   public PARTICLE_FLAGS,
   public print_formatting
//class CLASS_DECL_ACME stream_base
{
public:


   e_str_flag                 m_estrflag;
   ::file::e_iostate          m_iostate;
   memsize                    m_gcount;


   stream_base()
   {

      //m_bStoring = false;
      m_gcount = 0;
      m_iostate = ::file::goodbit;
      m_fmtflags = ::file::nofmtflags;
      m_precision = 0;
      //m_iVersion = FIRST_VERSION;

   }
   stream_base(const ::stream_base & meta) = delete;
   stream_base(::stream_base && meta) = delete;


   //virtual ::file::file * get_file() = 0;


   //bool bad() const
   //{
   //   return (m_iostate & ::file::badbit) != 0;
   //}

   //bool fail() const
   //{
   //   return ((int)m_iostate & ((int) ::file::badbit | (int) ::file::failbit)) != 0;
   //}

   //bool eof() const
   //{
   //   return (m_iostate & ::file::eofbit) != 0;
   //}

   //bool good() const
   //{
   //   return m_iostate == ::file::goodbit;
   //}

   //void setstate(int state)
   //{
   //   clear((::file::e_iostate) (rdstate() | state));
   //}

   //void set_fail_bit()
   //{
   //   setstate(::file::failbit);
   //}

   //void clear(int state = ::file::goodbit)
   //{
   //   m_iostate = (::file::e_iostate) state;
   //}



   //::file::e_iostate rdstate() const
   //{

   //   return m_iostate;

   //}


   //bool operator ! ()
   //{

   //   return fail();

   //}

};



template < typename POINTER_TYPE >
class raw_pointer < ::pointer<POINTER_TYPE >>
{
public:

   using RAW_POINTER = typename ::pointer<POINTER_TYPE>::RAW_POINTER;

};

//
//class CLASS_DECL_ACME property_set_stream :
//   virtual public matter
//{
//public:
//
//
//   property_set * m_ppropertyset;
//
//
//   property_set_stream() : m_ppropertyset(nullptr) { }
//   property_set_stream(property_set & set) : m_ppropertyset(&set) { }
//
//   virtual binary_stream < FILE > * branch(const ::atom & atom);
//
//};
//
//
//class CLASS_DECL_ACME payload_stream :
//   virtual public matter
//{
//public:
//
//
//   ::payload *          m_ppayload;
//
//
//   payload_stream() : m_ppayload(nullptr) { }
//   payload_stream(::payload & payload) : m_ppayload(&payload) { }
//
//   virtual binary_stream < FILE > * branch(const ::atom &);
//
//
//};


//class CLASS_DECL_ACME stream_stack
//{
//public:
//
//
//   ::pointer<binary_stream < FILE >>m_pstream;
//
//
//   stream_stack(binary_stream < FILE > * pstream, const ::atom & atom);
//
//
//   binary_stream < FILE > & binary_stream < FILE >() { return *m_pstream; }
//
//
//};
//

//class CLASS_DECL_ACME binary_stream < FILE > :
//   public stream_meta,
//   virtual public object
//{
//public:
//
//
//   ::payload * m_pvarOptions;
//
//
//   binary_stream < FILE >():m_pvarOptions(nullptr) {}
//   ~binary_stream < FILE >() override;
//
//   inline ::payload & options();
//
//
//   virtual ::file::path get_file_path() const;
//
//   virtual void close();
//
//   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
//
//   virtual string factory_id_to_text(const :: atom & atom);
//   virtual ::atom text_to_factory_id(string strText);
//
//   template < typename TYPE >
//   void default_exchange(TYPE & t);
//
//   template < typename TYPE >
//   void write_only(TYPE & t);
//
//   template < typename TYPE >
//   void stream_exchange(const ::atom & atom, TYPE & t);
//
//   inline void exchange(const ::atom & atom, void * pdata, memsize s);
//
//   void add_exception(const ::exception & e) override;
//   void on_catch_all_exception() override;
//
//   virtual void write_element(const ::atom & atom, ::particle * pparticle);
//
//   virtual ::pointer<::element>read_element(const ::atom & atom);
//
//
//   virtual bool is_open() const;
//
//
//   virtual bool is_stream_null() const;
//   virtual bool is_stream_set() const;
//
//   virtual void * get_internal_data();
//   virtual memsize get_internal_data_size() const;
//   virtual bool set_internal_data_size(memsize c);
//   virtual filesize get_position() const;
//
//
//   virtual void read(memory_base & m);
//   virtual void write(const memory_base & m);
//
//   virtual bool is_reader_null() const;
//   virtual bool is_reader_set() const;
//
//   virtual void read_to_hex(string & str, filesize iStart = -1, filesize iEnd = -1);
//
//   virtual void write_from_hex(const void *pdata, memsize nCount);
//
//   virtual void write(const void *pdata, memsize nCount);
//
//   virtual void write(const void *pdata, memsize nCount, memsize * dwWritten);
//
//   virtual bool is_writer_null();
//   virtual bool is_writer_set();
//
//   virtual void flush();
//
//   virtual void set_length(filesize len);
//
//   // This number represents a following binary_stream < FILE > of data with this length.
//   // So the extra bytes representing the variable length quantity are
//   // neglectable and worth due the very fast variable length encoding.
//   inline void write_buffer_length(::u64 u)
//   {
//
//      if (u < 255)
//      {
//
//         write((::u8) u);
//
//      }
//      else if (u < 65535)
//      {
//
//         write((::u8)255);
//         write((::u16)u);
//
//      }
//      else
//      {
//
//         write((::u8)255);
//         write((::u16)65535);
//         write((::u64)u);
//
//      }
//
//   }
//
//   inline void read_buffer_length(::u64 & u)
//   {
//
//      ::u8 uRead;
//
//      read(uRead);
//
//      if (uRead < 255)
//      {
//
//         u = uRead;
//
//      }
//      else
//      {
//
//         ::u16 uRead;
//
//         read(uRead);
//
//         if (uRead < 65535)
//         {
//
//            u = uRead;
//
//         }
//         else
//         {
//
//            read(u);
//
//         }
//
//      }
//
//   }
//
//
//   virtual void write(char ch) { raw_write(ch); }
//   virtual void write(uchar uch) { raw_write(uch); }
//   virtual void write(i8 i) { raw_write(i); }
//   virtual void write(i16 i) { raw_write(i); }
//   virtual void write(u16 u) { raw_write(u); }
//#ifdef WINDOWS
//   virtual void write(unichar wch) { raw_write(wch); }
//#endif
//   virtual void write(bool b) { write((::u8)b?1: 0); }
//   virtual void write(i32 i) { raw_write(i); }
//   virtual void write(u32 u) { raw_write(u); }
//   virtual void write(i64 i) { raw_write(i); }
//   virtual void write(::u64 u) { raw_write(u); }
//#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//   virtual void write(unsigned long ul) { raw_write(ul); }
//   virtual void write(long l) { raw_write(l); }
//   //inline void write (long long ll);
//#endif
//   virtual void write(float f) { raw_write(f); }
//   virtual void write(double d) { raw_write(d); }
//   //virtual void write(const POINT_I32 & point) { raw_write(point); }
//   //virtual void write(const SIZE_I32 & size) { raw_write(size); }
//   //virtual void write(const ::rectangle_i32 &crect) { raw_write(crect); }
//   virtual void write(const ::scoped_string & scopedstr);
//#ifdef WINDOWS
//   virtual void write(const unichar * wch) { write(string(wch)); }
//#endif
//   virtual void write(const atom & atom);
//   virtual void write(const ::payload & payload);
//   virtual void write(const property & property);
//   virtual void write(const ::string & str) ;
//   virtual void write(const ::particle * pparticle);
//   virtual void write(const ::matter & matter);
//   virtual void write(const property_set & set);
//   virtual void write(const block & block);
//
//   //::filesize tellp();
//   //virtual void seekp(filesize position) ;
//   //virtual void seekp(filesize offset, ::enum_seek eseek);
//   virtual void put(char ch);
//
//
//   template < typename TYPE >
//   inline auto read() { TYPE t; read(t); return t; }
//
//
//   virtual void read(bool & b);
//   virtual void read(char & ch);
//   virtual void read(uchar & uch);
//#ifdef WINDOWS
//   virtual void read(unichar & wch);
//   virtual void read(long & l);
//#elif defined(__APPLE__)  || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//   virtual void read(long & l);
//#endif
//   virtual void read(i8 & i);
//   virtual void read(i16 & i);
//   virtual void read(u16 & u);
//   virtual void read(i32 & i);
//   virtual void read(u32 & u);
//   virtual void read(i64 & i);
//   virtual void read(::u64 & u);
//#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//   virtual void read(unsigned long & u);
//   //inline void read (long long & u);
//#endif
//   virtual void read(float & f);
//   virtual void read(double & d);
//   //virtual void read(POINT_I32 & point);
//   //virtual void read(SIZE_I32 & size);
//   //virtual void read(RECTANGLE_I32 & rectangle);
//   virtual void read(atom & atom);
//   virtual void read(::payload & payload);
//   virtual void read_var_type(enum_type & etype);
//   virtual void read_var_body(::payload & payload, enum_type etype);
//   virtual void read(property & property);
//   virtual void read(string & str);
//   //virtual void read(::particle * pparticle);
//   virtual void read(::matter & matter);
//   virtual void read(::property_set & set);
//   virtual void read(block & block);
//
//   virtual void save_var_type(::enum_type etype);
//
//
//
//   virtual void exchange(const ::atom & atom, char & ch) { stream_exchange(atom, ch); }
//   virtual void exchange(const ::atom & atom, uchar & uch) { stream_exchange(atom, uch); }
//   virtual void exchange(const ::atom & atom, i8 & i) { stream_exchange(atom, i); }
//   virtual void exchange(const ::atom & atom, i16 & i) { stream_exchange(atom, i); }
//   virtual void exchange(const ::atom & atom, u16 & u) { stream_exchange(atom, u); }
//#ifdef WINDOWS
//   virtual void exchange(const ::atom & atom, unichar & wch) { stream_exchange(atom, wch); }
//#endif
//   virtual void exchange(const ::atom & atom, bool & b) { stream_exchange(atom, b); }
//   virtual void exchange(const ::atom & atom, i32 & i) { stream_exchange(atom, i); }
//   virtual void exchange(const ::atom & atom, u32 & u) { stream_exchange(atom, u); }
//   virtual void exchange(const ::atom & atom, i64 & i) { stream_exchange(atom, i); }
//   virtual void exchange(const ::atom & atom, ::u64 & u) { stream_exchange(atom, u); }
//#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBERRYPIOS)
//   virtual void exchange(const ::atom & atom, unsigned long & ul) { stream_exchange(atom, ul); }
//   virtual void exchange(const ::atom & atom, long & l) { stream_exchange(atom, l); }
//   //inline void exchange(const ::atom & atom, long long & ll);
//#endif
//   virtual void exchange(const ::atom & atom, float & f) { stream_exchange(atom, f); }
//   virtual void exchange(const ::atom & atom, double & d) { stream_exchange(atom, d); }
//   virtual void exchange(const ::atom & atom, POINT_I32 & point) { stream_exchange(atom, point); }
//   virtual void exchange(const ::atom & atom, SIZE_I32 & size) { stream_exchange(atom, size); }
//   virtual void exchange(const ::atom & atom, RECTANGLE_I32 & crect) { stream_exchange(atom, crect); }
//   virtual void exchange(const ::atom & atom, POINT_F64& point) { stream_exchange(atom, point); }
//   virtual void exchange(const ::atom & atom, SIZE_F64& size) { stream_exchange(atom, size); }
//   virtual void exchange(const ::atom & atom, RECTANGLE_F64& crect) { stream_exchange(atom, crect); }
//   virtual void exchange(const ::atom & atom, const ::scoped_string & scopedstr);
//#ifdef WINDOWS
//   virtual void exchange(const ::atom & atom, const unichar * wch);
//#endif
//   virtual void exchange(const ::atom & atom, ::atom & idExchange);
//   virtual void exchange(const ::atom & atom, ::payload & payload);
//   virtual void exchange(const ::atom & atom, property & property);
//   virtual void exchange(const ::atom & atom, string & str) ;
//   virtual void exchange(const ::atom & atom, ::particle * pparticle);
//   virtual void exchange(const ::atom & atom, ::matter & matter);
//   virtual void exchange(const ::atom & atom, property_set & set);
//   virtual void exchange(const ::atom & atom, block & block);
//
//
//   virtual void getline(char * sz, strsize n) ;
//   int get();
//   int peek();
//
////   filesize tellg() ;
////   virtual void seekg(filesize position);
////   virtual void seekg(filesize offset, ::enum_seek eseek);
//
//   ::filesize get_left() const;
//
//   //inline bool is_storing() const { return m_bStoring; }
//   //inline bool is_loading() const { return !m_bStoring; }
//
//
//   //virtual void write_file(const ::file::path & path, const ::matter & matter);
//   //virtual void read_file(const ::file::path & path, ::matter & matter);
//
//   //virtual void write_link(const ::string & strLink, ::pointer<::matter>& matter);
//   //virtual void read_link(const ::string & strLink, ::pointer<::matter>& matter);
//
//   //virtual void write_link(const ::matter * preference, const ::string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions = nullptr);
//
//   //virtual bool write_link(const ::matter * preference);
//   //virtual void read_link(::matter * preference);
//
//
//   //virtual bool get_object_link(const ::matter * preference, string & strLink, bool & bReadOnly);
//   //virtual void set_object_link(const ::matter * preference, const ::string & strLink, bool bReadOnly);
//
//
//   //virtual ::file::path get_link_path(string strLink);
//
//   bool is_version(index i);
//
//   template < typename BLOCK_TYPE >
//   inline void raw_write(const BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
//   {
//
//      write(&t, sizeof(t));
//
//   }
//
//
//   //template < typename BLOCK_TYPE >
//   //inline void raw_read(BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
//   //{
//
//   //   full_read(&t, sizeof(t));
//
//   //}
//
//
//   //inline void full_read(void * pdata, memsize nCount)
//   //{
//
//   //   if (!fail())
//   //   {
//
//   //      if (m_p->read(pdata, nCount) !=nCount)
//   //      {
//
//   //         set_fail_bit();
//
//   //      }
//
//   //   }
//
//   //}
//
//
//   //void xml_export(const ::xml::exportable & xmlexportable);
//
//   //void xml_import(::xml::importable & xmlimportable);
//
//
//   template < typename BASE_TYPE >
//   inline binary_stream < FILE > & save_object(const BASE_TYPE * pparticle);
//
//   template < typename BASE_TYPE >
//   inline ::pointer<BASE_TYPE>load_object();
//
//   virtual ::pointer<::matter>create_object_from_text(string strText);
//
//
//
//};


//stream_stack::stream_stack(binary_stream < FILE > * pstreamStack, const ::atom & atom)
//{
//
//   m_pstream = pstreamStack->branch(atom);
//
//}

//
//template < typename BASE_TYPE >
//::pointer<BASE_TYPE>__load_object(binary_stream < FILE > & binary_stream < FILE >);
//


//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & os, binary_stream < FILE > & (*pfnSimpleOutput)(binary_stream < FILE > &))
//{
//
//   (*pfnSimpleOutput)(os);
//
//}


//namespace std
//{
//
//
//   inline binary_stream < FILE > & endl(binary_stream < FILE > & os)
//   {
//
//      os.put('\n');
//
//      os.flush();
//
//      return os;
//
//   }
//
//
//} // namespace std
//
//

//
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, i32 & i) { s.read(i); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, u32 & u) { s.read(u); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, i64 & i) { s.read(i); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, u64 & u) { s.read(u); return s; }
//
//#ifdef __APPLE__
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, unsigned long & u) { s.read(u); return s; }
//
//#endif
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, float & f) { s.read(f); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, double & d) { s.read(d); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, POINT_I32 & point) { s.read(point); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, SIZE_I32 & size) { s.read(size); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, RECTANGLE_I32 & rectangle) { s.read(rectangle); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::atom & atom) { s.read(atom); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::payload & payload) { s.read(payload); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, property & property) { s.read(property); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, string & str) { s.read(str); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, block & block) { s.read(block); return s; }
//
/////template < typename BLOCK >

//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, bool & b) { s.read(b); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, char & ch) { s.read(ch); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, uchar & uch) { s.read(uch); return s; }
//
//#if defined(WINDOWS)
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::wd16_character & wch) { s.read(wch); return s; }
//
//#else
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::wd32_character & wch) { s.read(wch); return s; }
//
//#endif
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, i8 & i) { s.read(i); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, i16 & i) { s.read(i); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, u16 & u) { s.read(u); return s; }
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, e_set_loading) { s->set_loading(); return s; }
//
//template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class PAIR >
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR > & m);
//
//template <  typename TYPE >
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, pointer_array < TYPE > & a);
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::file::path & path);
//
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, class ::time & class ::time);
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::file::path & path);
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::string & str) { s.write(str); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, e_set_storing) { s->set_storing(); s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, char ch) { s.write(ch); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, uchar uch) { s.write(uch); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, i8 sh) { s.write(sh); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, i16 sh) { s.write(sh); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, u16 u) { s.write(u); return s; }
//
//#ifdef WINDOWS
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, unichar wch) { s.write(wch); return s; }
//
//#endif
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, bool b) { s.write(b); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, i32 i) { s.write(i); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, u32 u) { s.write(u); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, i64 i) { s.write(i); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, u64 u) { s.write(u); return s; }
//
//#if defined(__APPLE__)
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const unsigned long u) { s.write(u); return s; }
//
//#endif
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, float f) { s.write(f); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, double d) { s.write(d); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const POINT_I32 & point) { s.write(point); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::rectangle_i32 &rectangle) { s.write(rectangle); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const SIZE_I32 & size) { s.write(size); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::scoped_string & scopedstr) { s.write(psz); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const atom & atom) { s.write(atom); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::payload & payload) { s.write(payload); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const property & property) { s.write(property); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::particle * pparticle) { s.write(pparticle); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::matter & matter) { s.write(matter); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const block & block) { s.write(block); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, e_str_flag eflag) { s.m_estrflag = (e_str_flag)((int)s.m_estrflag | (int)eflag); return s; }
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::file::set_width & w) { s.width(w.m_width); return s; }
//


//
//template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class PAIR >
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR > & m);
//
//template < typename TYPE >
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const pointer_array < TYPE > & a);
//
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const class time & time);
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, class ::time & time);



//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, ::file::file * pfile);
//
//
//
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, ::file_pointer & pfile)
//{
//
//   operator << (s, pfile.m_p);
//
//}
//
//
//
//
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::earth::time & time);
////
////
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::earth::time & time);
//
//
//
//
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::earth::zonetime & z);
//
//
//
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::earth::zonetime & z);
//
//
//
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::earth::time_shift & z);
//
//
//
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::earth::time_shift & z);
//
//
//
//inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::datetime::time_zone & z);
//
//
//
//
//inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::datetime::time_zone & z);
//
//
//template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const point_type < BASE_TYPE, SIZE_BASE_TYPE, RECTANGLE_BASE_TYPE > & point)
//{
//
//   s << point.x;
//   s << point.y;
//
//   return s;
//
//}
//
//
//
//template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, point_type < BASE_TYPE, SIZE_BASE_TYPE, RECTANGLE_BASE_TYPE > & point)
//{
//   s >> point.x;
//   s >> point.y;
//   return s;
//}
//
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE > & size)
//{
//
//   s << size.cx;
//   s << size.cy;
//
//   return s;
//
//}
//
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, size_type < BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE > & size)
//{
//   s >> size.cx;
//   s >> size.cy;
//   return s;
//}
//
//
////binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::color::hls & hls);
//
////binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::color::hls & hls);
//
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
//inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > & rectangle)
//{
//   
//   s << rectangle.left;
//   s << rectangle.top;
//   s << rectangle.right;
//   s << rectangle.bottom;
//
//   return s;
//
//}
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
//inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > & rectangle)
//{
//
//   s >> rectangle.left;
//   s >> rectangle.top;
//   s >> rectangle.right;
//   s >> rectangle.bottom;
//
//   return s;
//
//}
//
//
//
