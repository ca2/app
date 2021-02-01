#pragma once


#define __EXCHANGE(xxx) stream.stream_exchange(__STRING(xxx), m_##xxx)
#define __TYPE_EXCHANGE(xxx) stream.stream_exchange(__STRING(xxx), t.m_##xxx)

class var_stream;
class text_stream;

// Use cases:
// - Entry point_i32 convenience syntax sugar
// - syntax sugar
template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t);

template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t);

template < typename TYPE >
inline var_stream & operator >> (var_stream & stream, TYPE & t);

template < typename TYPE >
inline var_stream & operator << (var_stream & stream, const TYPE & t);

template < typename TYPE >
inline text_stream & operator >> (text_stream & stream, TYPE & t);

template < typename TYPE >
inline text_stream & operator << (text_stream & stream, const TYPE & t);

template < typename TYPE >
inline ::file::file & operator >> (::file::file & file, TYPE & t);

template < typename TYPE >
inline ::file::file & operator << (::file::file & file, const TYPE & t);




 inline void __exchange(::stream & s, bool & b);


 inline void __exchange(::stream & s, i8 & i);
 inline void __exchange(::stream & s, i16 & i);
 inline void __exchange(::stream & s, i32 & i);
 inline void __exchange(::stream & s, i64 & i);
 inline void __exchange(::stream & s, u8 & u);
 inline void __exchange(::stream & s, u16 & u);
 inline void __exchange(::stream & s, u32 & u);
 inline void __exchange(::stream & s, u64 & u);


 inline void __exchange(::stream & s, long & l);


 inline void __exchange(::stream & s, float & f);
 inline void __exchange(::stream & s, double & d);
 inline void __exchange(::stream & s, ::datetime::time & time);
 inline void __exchange(::stream & s, const char * psz);
 inline void __exchange(::stream & s, string & str);
 inline void __exchange(::stream & s, ::file::path & path);
 inline void __exchange(::stream & s, ::id & id);
 inline void __exchange(::stream & s, ::payload & payload);
 inline void __exchange(::stream & s, ::property & property);
 inline void __exchange(::stream & s, ::matter & matter);


 inline void __exchange(::stream & s, RECTANGLE_I32 & rectangle);
 inline void __exchange(::stream & s, RECTANGLE_I64 & rectangle);
 inline void __exchange(::stream & s, RECTANGLE_F32 & rectangle);
 inline void __exchange(::stream & s, RECTANGLE_F64 & rectangle);


 inline void __exchange(::stream & s, SIZE_I32 & rectangle);
 inline void __exchange(::stream & s, SIZE_I64 & rectangle);
 inline void __exchange(::stream & s, SIZE_F32 & rectangle);
 inline void __exchange(::stream & s, SIZE_F64 & rectangle);


 inline void __exchange(::stream & s, POINT_I32 & rectangle);
 inline void __exchange(::stream & s, POINT_I64 & rectangle);
 inline void __exchange(::stream & s, POINT_F32 & rectangle);
 inline void __exchange(::stream & s, POINT_F64 & rectangle);


template < typename OBJECT >
inline void __exchange(::stream & s, __pointer(OBJECT) & pobject)
{
   __exchange(s, __typed_defer_create(pobject));
}


template < typename BLOCK_TYPE >
inline void __exchange(stream & s, memory_template < BLOCK_TYPE > & block);

template < typename ARRAY >
inline void __exchange_array(::stream & s, const ARRAY & array) { __exchange_array(s, (ARRAY &)array); }


inline void __exchange(::stream & s, const ::file::patha & patha) { __exchange_array(s, patha); }

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & s, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array) { __exchange_array(s, (::array_base < TYPE, ARG_TYPE, ALLOCATOR > &)array); }

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & s, const ::raw_array < TYPE, ARG_TYPE, ALLOCATOR > & array) { __exchange_array(s, (::raw_array < TYPE, ARG_TYPE, ALLOCATOR > &)array); }

template < class TYPE >
inline void __exchange(::stream & s, const ::numeric_array < TYPE > & array) { __exchange_array(s, (::numeric_array < TYPE > &) array); }

template < typename Type, typename RawType >
inline void __exchange(::stream & s, const ::string_array_base < Type, RawType > & array) { __exchange_array(s, (::string_array_base < Type, RawType > &) array); }

template < typename ARRAY >
inline void __exchange_save_array(::stream & s, ARRAY & array);

template < typename ARRAY >
inline void __exchange_load_array(::stream & s, ARRAY & array);

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & s, ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & array);

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void __exchange(::stream & s, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR > & array);

template < class TYPE >
inline void __exchange(::stream & s, ::numeric_array < TYPE > & array);

template < typename Type, typename RawType >
inline void __exchange(::stream & s, ::string_array_base < Type, RawType > & array);


#define FIRST_VERSION 0


enum e_set_storing
{

   set_storing

};


enum e_set_loading
{

   set_loading

};


struct CLASS_DECL_ACME stream_meta
{


   e_str_flag                 m_estrflag;
   ::file::e_iostate          m_iostate;
   ::file::fmtflags           m_fmtflags;
   filesize                   m_width;
   filesize                   m_precision;
   memsize                    m_gcount;


   stream_meta()
   {

      //m_bStoring = false;
      m_gcount = 0;
      m_iostate = ::file::goodbit;
      m_fmtflags = ::file::nofmtflags;
      m_precision = 0;
      //m_iVersion = FIRST_VERSION;

   }
   stream_meta(const ::stream_meta & meta) = default;
   stream_meta(::stream_meta && meta) = default;




   bool bad() const
   {
      return (m_iostate & ::file::badbit) != 0;
   }

   bool fail() const
   {
      return ((int)m_iostate & ((int) ::file::badbit | (int) ::file::failbit)) != 0;
   }

   bool eof() const
   {
      return (m_iostate & ::file::eofbit) != 0;
   }

   bool good() const
   {
      return m_iostate == ::file::goodbit;
   }

   void setstate(int state)
   {
      clear((::file::e_iostate) (rdstate() | state));
   }

   void set_fail_bit()
   {
      setstate(::file::failbit);
   }

   void clear(int state = ::file::goodbit)
   {
      m_iostate = (::file::e_iostate) state;
   }



   ::file::e_iostate rdstate() const
   {

      return m_iostate;

   }


   bool operator ! ()
   {

      return fail();

   }

   filesize precision() const;

   filesize precision(filesize prec);

   filesize width() const;

   filesize width(filesize wide);


   ::file::fmtflags setf(::file::fmtflags flagsAdd);
   ::file::fmtflags setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove);

};



template < typename POINTER_TYPE >
class raw_pointer < __pointer(POINTER_TYPE) >
{
public:

   using RAW_POINTER = typename __pointer(POINTER_TYPE)::RAW_POINTER;

};

//
//class CLASS_DECL_ACME property_set_stream :
//   virtual public matter
//{
//public:
//
//
//   property_set * m_pset;
//
//
//   property_set_stream() : m_pset(nullptr) { }
//   property_set_stream(property_set & set) : m_pset(&set) { }
//
//   virtual stream * branch(const ::id & id);
//
//};
//
//
//class CLASS_DECL_ACME var_stream :
//   virtual public matter
//{
//public:
//
//
//   ::payload *          m_pvar;
//
//
//   var_stream() : m_pvar(nullptr) { }
//   var_stream(::payload & payload) : m_pvar(&payload) { }
//
//   virtual stream * branch(const ::id &);
//
//
//};


//class CLASS_DECL_ACME stream_stack
//{
//public:
//
//
//   __pointer(stream) m_pstream;
//
//
//   stream_stack(stream * pstream, const ::id & id);
//
//
//   stream & stream() { return *m_pstream; }
//
//
//};
//

class CLASS_DECL_ACME stream :
   public stream_meta,
   virtual public ::context_object
{
public:


   ::payload * m_pvarOptions;


   stream():m_pvarOptions(nullptr) {}
   virtual ~stream();

   inline ::payload & options();


   virtual ::file::path get_file_path() const;

   virtual void close();

   inline void defer_set_storing() { if (!is_storing()) set_storing(); }

   virtual string factory_id_to_text(const :: id & id);
   virtual ::id text_to_factory_id(string strText);

   template < typename TYPE >
   void default_exchange(TYPE & t);

   template < typename TYPE >
   void write_only(TYPE & t);

   template < typename TYPE >
   void stream_exchange(const ::id & id, TYPE & t);

   inline void exchange(const ::id & id, void * pdata, memsize s);

   virtual void add_exception(::exception::exception * pexception);
   virtual void on_catch_all_exception();

   virtual void write_object(const ::id & id, ::matter * pobject);

   virtual __pointer(::matter) read_object(const ::id & id);


   virtual bool is_open() const;


   virtual bool is_stream_null() const;
   virtual bool is_stream_set() const;

   virtual void * get_internal_data();
   virtual memsize get_internal_data_size() const;
   virtual bool set_internal_data_size(memsize c);
   virtual filesize get_position() const;


   virtual void read(memory_base & m);
   virtual void write(const memory_base & m);

   virtual bool is_reader_null() const;
   virtual bool is_reader_set() const;

   virtual void read_to_hex(string & str, filesize iStart = -1, filesize iEnd = -1);

   virtual void write_from_hex(const void *pdata, memsize nCount);

   virtual void write(const void *pdata, memsize nCount);

   virtual void write(const void *pdata, memsize nCount, memsize * dwWritten);

   virtual bool is_writer_null();
   virtual bool is_writer_set();

   virtual void flush();

   virtual void set_length(filesize len);

   // This number represents a following stream of data with this length.
   // So the extra bytes representing the variable length quantity are
   // neglectable and worth due the very fast variable length encoding.
   inline void write_buffer_length(::u64 u)
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

   inline void read_buffer_length(::u64 & u)
   {

      ::u8 uRead;

      read(uRead);

      if (!fail())
      {

         if (uRead < 255)
         {

            u = uRead;

         }
         else
         {

            ::u16 uRead;

            read(uRead);

            if (!fail())
            {

               if (uRead < 65535)
               {

                  u = uRead;

               }
               else
               {

                  read(u);

               }

            }

         }

      }

   }


   virtual void write(char ch) { raw_write(ch); }
   virtual void write(uchar uch) { raw_write(uch); }
   virtual void write(i8 i) { raw_write(i); }
   virtual void write(i16 i) { raw_write(i); }
   virtual void write(u16 u) { raw_write(u); }
#ifdef WINDOWS
   virtual void write(unichar wch) { raw_write(wch); }
#endif
   virtual void write(bool b) { write((::u8)b?1: 0); }
   virtual void write(i32 i) { raw_write(i); }
   virtual void write(u32 u) { raw_write(u); }
   virtual void write(i64 i) { raw_write(i); }
   virtual void write(::u64 u) { raw_write(u); }
#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)
   virtual void write(unsigned long ul) { raw_write(ul); }
   virtual void write(long l) { raw_write(l); }
   //inline void write (long long ll);
#endif
   virtual void write(float f) { raw_write(f); }
   virtual void write(double d) { raw_write(d); }
   //virtual void write(const POINT_I32 & point) { raw_write(point); }
   //virtual void write(const SIZE_I32 & size) { raw_write(size); }
   //virtual void write(const RECTANGLE_I32 & crect) { raw_write(crect); }
   virtual void write(const char * psz);
#ifdef WINDOWS
   virtual void write(const unichar * wch) { write(string(wch)); }
#endif
   virtual void write(const id & id);
   virtual void write(const ::payload & payload);
   virtual void write(const property & property);
   virtual void write(const string & str) ;
   virtual void write(const ::matter * pobject);
   virtual void write(const ::matter & matter);
   virtual void write(const property_set & set);
   virtual void write(const block & block);

   //::filesize tellp();
   //virtual void seekp(filesize position) ;
   //virtual void seekp(filesize offset, ::file::e_seek eseek);
   virtual void put(char ch);


   template < typename TYPE >
   inline auto read() { TYPE t; read(t); return t; }


   virtual void read(bool & b);
   virtual void read(char & ch);
   virtual void read(uchar & uch);
#ifdef WINDOWS
   virtual void read(unichar & wch);
   virtual void read(long & l);
#elif defined(__APPLE__)  || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)
   virtual void read(long & l);
#endif
   virtual void read(i8 & i);
   virtual void read(i16 & i);
   virtual void read(u16 & u);
   virtual void read(i32 & i);
   virtual void read(u32 & u);
   virtual void read(i64 & i);
   virtual void read(::u64 & u);
#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)
   virtual void read(unsigned long & u);
   //inline void read (long long & u);
#endif
   virtual void read(float & f);
   virtual void read(double & d);
   //virtual void read(POINT_I32 & point);
   //virtual void read(SIZE_I32 & size);
   //virtual void read(RECTANGLE_I32 & rectangle);
   virtual void read(id & id);
   virtual void read(::payload & payload);
   virtual void read_var_type(enum_type & etype);
   virtual void read_var_body(::payload & payload, enum_type etype);
   virtual void read(property & property);
   virtual void read(string & str);
   //virtual void read(::matter * pobject);
   virtual void read(::matter & matter);
   virtual void read(::property_set & set);
   virtual void read(block & block);

   virtual void save_var_type(::enum_type etype);



   virtual void exchange(const ::id & id, char & ch) { stream_exchange(id, ch); }
   virtual void exchange(const ::id & id, uchar & uch) { stream_exchange(id, uch); }
   virtual void exchange(const ::id & id, i8 & i) { stream_exchange(id, i); }
   virtual void exchange(const ::id & id, i16 & i) { stream_exchange(id, i); }
   virtual void exchange(const ::id & id, u16 & u) { stream_exchange(id, u); }
#ifdef WINDOWS
   virtual void exchange(const ::id & id, unichar & wch) { stream_exchange(id, wch); }
#endif
   virtual void exchange(const ::id & id, bool & b) { stream_exchange(id, b); }
   virtual void exchange(const ::id & id, i32 & i) { stream_exchange(id, i); }
   virtual void exchange(const ::id & id, u32 & u) { stream_exchange(id, u); }
   virtual void exchange(const ::id & id, i64 & i) { stream_exchange(id, i); }
   virtual void exchange(const ::id & id, ::u64 & u) { stream_exchange(id, u); }
#if defined(__APPLE__) || defined(ANDROID) || defined(WINDOWS) || defined(RASPBIAN)
   virtual void exchange(const ::id & id, unsigned long & ul) { stream_exchange(id, ul); }
   virtual void exchange(const ::id & id, long & l) { stream_exchange(id, l); }
   //inline void exchange(const ::id & id, long long & ll);
#endif
   virtual void exchange(const ::id & id, float & f) { stream_exchange(id, f); }
   virtual void exchange(const ::id & id, double & d) { stream_exchange(id, d); }
   virtual void exchange(const ::id & id, POINT_I32 & point) { stream_exchange(id, point); }
   virtual void exchange(const ::id & id, SIZE_I32 & size) { stream_exchange(id, size); }
   virtual void exchange(const ::id & id, RECTANGLE_I32 & crect) { stream_exchange(id, crect); }
   virtual void exchange(const ::id & id, POINT_F64& point) { stream_exchange(id, point); }
   virtual void exchange(const ::id & id, SIZE_F64& size) { stream_exchange(id, size); }
   virtual void exchange(const ::id & id, RECTANGLE_F64& crect) { stream_exchange(id, crect); }
   virtual void exchange(const ::id & id, const char * psz);
#ifdef WINDOWS
   virtual void exchange(const ::id & id, const unichar * wch);
#endif
   virtual void exchange(const ::id & id, ::id & idExchange);
   virtual void exchange(const ::id & id, ::payload & payload);
   virtual void exchange(const ::id & id, property & property);
   virtual void exchange(const ::id & id, string & str) ;
   virtual void exchange(const ::id & id, ::matter * pobject);
   virtual void exchange(const ::id & id, ::matter & matter);
   virtual void exchange(const ::id & id, property_set & set);
   virtual void exchange(const ::id & id, block & block);


   virtual void getline(char * sz, strsize n) ;
   int get();
   int peek();

//   filesize tellg() ;
//   virtual void seekg(filesize position);
//   virtual void seekg(filesize offset, ::file::e_seek eseek);

   ::filesize get_left() const;

   //inline bool is_storing() const { return m_bStoring; }
   //inline bool is_loading() const { return !m_bStoring; }


   //virtual void write_file(const ::file::path & path, const ::matter & matter);
   //virtual void read_file(const ::file::path & path, ::matter & matter);

   //virtual void write_link(const string & strLink, __pointer(::matter) & matter);
   //virtual void read_link(const string & strLink, __pointer(::matter) & matter);

   //virtual void write_link(const ::matter * preference, const string & strLink, bool bReadOnly, ::matter * pobjectSaveOptions = nullptr);

   //virtual bool write_link(const ::matter * preference);
   //virtual void read_link(::matter * preference);


   //virtual bool get_object_link(const ::matter * preference, string & strLink, bool & bReadOnly);
   //virtual void set_object_link(const ::matter * preference, const string & strLink, bool bReadOnly);


   //virtual ::file::path get_link_path(string strLink);

   bool is_version(index i);

   template < typename BLOCK_TYPE >
   inline void raw_write(const BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
   {

      write(&t, sizeof(t));

   }


   //template < typename BLOCK_TYPE >
   //inline void raw_read(BLOCK_TYPE & t) // must be POD type // block transfer // classes/structures with no virtual members
   //{

   //   full_read(&t, sizeof(t));

   //}


   //inline void full_read(void * pdata, memsize nCount)
   //{

   //   if (!fail())
   //   {

   //      if (m_p->read(pdata, nCount) !=nCount)
   //      {

   //         set_fail_bit();

   //      }

   //   }

   //}


   //void xml_export(const ::xml::exportable & xmlexportable);

   //void xml_import(::xml::importable & xmlimportable);


   template < typename BASE_TYPE >
   inline stream & save_object(const BASE_TYPE * pobject);

   template < typename BASE_TYPE >
   inline __pointer(BASE_TYPE) load_object();

   virtual __pointer(::matter) create_object_from_text(string strText);



};


//stream_stack::stream_stack(stream * pstreamStack, const ::id & id)
//{
//
//   m_pstream = pstreamStack->branch(id);
//
//}


template < typename BASE_TYPE >
__pointer(BASE_TYPE) __load_object(stream & stream);



//
//inline stream & operator << (stream & os, stream & (*pfnSimpleOutput)(stream &))
//{
//
//   (*pfnSimpleOutput)(os);
//
//}


namespace std
{


   inline stream & endl(stream & os)
   {

      os.put('\n');

      os.flush();

      return os;

   }


} // namespace std



//
//
//inline stream & operator >> (stream & s, i32 & i) { s.read(i); return s; }
//
//inline stream & operator >> (stream & s, u32 & u) { s.read(u); return s; }
//
//inline stream & operator >> (stream & s, i64 & i) { s.read(i); return s; }
//
//inline stream & operator >> (stream & s, u64 & u) { s.read(u); return s; }
//
//#ifdef __APPLE__
//
//inline stream & operator >> (stream & s, unsigned long & u) { s.read(u); return s; }
//
//#endif
//
//inline stream & operator >> (stream & s, float & f) { s.read(f); return s; }
//
//inline stream & operator >> (stream & s, double & d) { s.read(d); return s; }
//
//inline stream & operator >> (stream & s, POINT_I32 & point) { s.read(point); return s; }
//
//inline stream & operator >> (stream & s, SIZE_I32 & size) { s.read(size); return s; }
//
//inline stream & operator >> (stream & s, RECTANGLE_I32 & rectangle) { s.read(rectangle); return s; }
//
//inline stream & operator >> (stream & s, ::id & id) { s.read(id); return s; }
//
//inline stream & operator >> (stream & s, ::payload & payload) { s.read(payload); return s; }
//
//inline stream & operator >> (stream & s, property & property) { s.read(property); return s; }
//
//inline stream & operator >> (stream & s, string & str) { s.read(str); return s; }
//
//inline stream & operator >> (stream & s, block & block) { s.read(block); return s; }
//
/////template < typename BLOCK >
//template < typename BLOCK >
//inline stream & operator >> (stream & s, memory_template < BLOCK > & mem) { s.read(mem.get_data(), mem.get_size()); return s; }
//
//inline stream & operator >> (stream & s, bool & b) { s.read(b); return s; }
//
//inline stream & operator >> (stream & s, char & ch) { s.read(ch); return s; }
//
//inline stream & operator >> (stream & s, uchar & uch) { s.read(uch); return s; }
//
//#if defined(WINDOWS)
//
//inline stream & operator >> (stream & s, wd16char & wch) { s.read(wch); return s; }
//
//#else
//
//inline stream & operator >> (stream & s, wd32char & wch) { s.read(wch); return s; }
//
//#endif
//
//inline stream & operator >> (stream & s, i8 & i) { s.read(i); return s; }
//
//inline stream & operator >> (stream & s, i16 & i) { s.read(i); return s; }
//
//inline stream & operator >> (stream & s, u16 & u) { s.read(u); return s; }
//
//inline stream & operator >> (stream & s, e_set_loading) { s->set_loading(); return s; }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
//inline stream & operator >>(stream & s, map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & m);
//
//template <  typename TYPE >
//inline stream & operator >>(stream & s, __pointer_array(TYPE) & a);
//
//inline stream & operator >> (stream & s, ::file::path & path);
//
//inline stream & operator >> (stream & s, ::millis & millis);
//
//inline stream & operator << (stream & s, const ::file::path & path);
//
//inline stream & operator << (stream & s, const string & str) { s.write(str); return s; }
//
//inline stream & operator << (stream & s, e_set_storing) { s->set_storing(); s; }
//
//inline stream & operator << (stream & s, char ch) { s.write(ch); return s; }
//
//inline stream & operator << (stream & s, uchar uch) { s.write(uch); return s; }
//
//inline stream & operator << (stream & s, i8 sh) { s.write(sh); return s; }
//
//inline stream & operator << (stream & s, i16 sh) { s.write(sh); return s; }
//
//inline stream & operator << (stream & s, u16 u) { s.write(u); return s; }
//
//#ifdef WINDOWS
//
//inline stream & operator << (stream & s, unichar wch) { s.write(wch); return s; }
//
//#endif
//
//inline stream & operator << (stream & s, bool b) { s.write(b); return s; }
//
//inline stream & operator << (stream & s, i32 i) { s.write(i); return s; }
//
//inline stream & operator << (stream & s, u32 u) { s.write(u); return s; }
//
//inline stream & operator << (stream & s, i64 i) { s.write(i); return s; }
//
//inline stream & operator << (stream & s, u64 u) { s.write(u); return s; }
//
//#if defined(__APPLE__)
//
//inline stream & operator << (stream & s, const unsigned long u) { s.write(u); return s; }
//
//#endif
//
//inline stream & operator << (stream & s, float f) { s.write(f); return s; }
//
//inline stream & operator << (stream & s, double d) { s.write(d); return s; }
//
//template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECT_BASE_TYPE >
//inline stream & operator << (stream & s, const point_type < BASE_TYPE, SIZE_BASE_TYPE, RECT_BASE_TYPE > & point)
//{
//   s << point.x;
//   s << point.y;
//   return s;
//}
//
//inline stream & operator << (stream & s, const POINT_I32 & point) { s.write(point); return s; }
//
//inline stream & operator << (stream & s, const RECTANGLE_I32 & rectangle) { s.write(rectangle); return s; }
//
//inline stream & operator << (stream & s, const SIZE_I32 & size) { s.write(size); return s; }
//
//inline stream & operator << (stream & s, const char * psz) { s.write(psz); return s; }
//
//inline stream & operator << (stream & s, const id & id) { s.write(id); return s; }
//
//inline stream & operator << (stream & s, const ::payload & payload) { s.write(payload); return s; }
//
//inline stream & operator << (stream & s, const property & property) { s.write(property); return s; }
//
//inline stream & operator << (stream & s, const ::matter * pobject) { s.write(pobject); return s; }
//
//inline stream & operator << (stream & s, const ::matter & matter) { s.write(matter); return s; }
//
//inline stream & operator << (stream & s, const block & block) { s.write(block); return s; }
//
//inline stream & operator << (stream & s, e_str_flag eflag) { s.m_estrflag = (e_str_flag)((int)s.m_estrflag | (int)eflag); return s; }
//
//inline stream & operator << (stream & s, const ::file::set_width & w) { s.width(w.m_width); return s; }
//
//template < typename BLOCK >
//inline stream & operator << (stream & s, const memory_template < BLOCK > & mem) { s.write(mem.get_data(), mem.get_size()); return s; }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
//inline stream & operator <<(stream & s, const map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & m);
//
//template < typename TYPE >
//inline stream & operator <<(stream & s, const __pointer_array(TYPE) & a);
//
//inline stream & operator <<(stream & s, const ::millis & millis);
//
////template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE > >
////inline stream & operator <<(stream & s, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
////{
////
////   ::count c = a.get_count();
////   s << c;
////   for (auto & matter : a)
////   {
////      s << matter;
////      if (s.fail())
////         break;
////   }
////
////   return s;
////
////}
//
//
//
//inline stream & operator << (stream & s, ::file::file * pfile);
//
//
//
//inline stream & operator << (stream & s, ::file_result & pfile)
//{
//
//   operator << (s, pfile.m_p);
//
//}
//
//
//
//
//inline stream & operator <<(stream & s, const ::datetime::time & time);
//
//
//inline stream & operator >>(stream & s, ::datetime::time & time);
//
//
//
//
//inline stream & operator >>(stream & s, ::datetime::zonetime & z);
//
//
//
//inline stream & operator <<(stream & s, const ::datetime::zonetime & z);
//
////
////inline stream & operator >>(stream & s, ::datetime::department::time_zone & z);
////
////
////
////
////inline stream & operator <<(stream & s, const ::datetime::department::time_zone & z);
//
//
//
//template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECT_BASE_TYPE >
//inline stream & operator >> (stream & s, point_type < BASE_TYPE, SIZE_BASE_TYPE, RECT_BASE_TYPE > & point)
//{
//   s >> point.x;
//   s >> point.y;
//   return s;
//}
//
