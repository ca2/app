#pragma once


class text_stream;


//template < typename TYPE >
//inline void __string_exchange(text_stream & s, TYPE & t);
//
//
//inline void __string_exchange(stream & s, ::payload & payload);
//
//inline void __string_exchange(text_stream & s, ansichar & ansich);
//inline void __string_exchange(text_stream & s, widechar & widech);
//inline void __string_exchange(text_stream & s, i8 & i);
//inline void __string_exchange(text_stream & s, i16 & i);
//inline void __string_exchange(text_stream & s, i32 & i);
//inline void __string_exchange(text_stream & s, i64 & i);
//inline void __string_exchange(text_stream & s, u8 & u);
//inline void __string_exchange(text_stream & s, u16 & u);
//inline void __string_exchange(text_stream & s, u32 & u);
//inline void __string_exchange(text_stream & s, u64 & u);
//inline void __string_exchange(text_stream & s, float & f);
//inline void __string_exchange(text_stream & s, double & d);
//inline void __string_exchange(text_stream & s, ::earth::time & time);
//inline void __string_exchange(text_stream & s, const char * psz);
//inline void __string_exchange(text_stream & s, char * sz);
//inline void __string_exchange(text_stream & s, string & str);
//inline void __string_exchange(text_stream & s, ::file::path & path);
//inline void __string_exchange(text_stream & s, ::atom & atom);
//inline void __string_exchange(text_stream & s, void * & p);
////inline void __string_exchange(text_stream & s, oswindow & oswindow);
//inline void __string_exchange(text_stream & s, wchar_t sz[]);
////inline void __string_exchange(text_stream & s, ::matter & matter);
//
////inline void __string_exchange(text_stream & s, ::rectangle_i32 & r);
//
//

//template < typename STRINGABLE >
//inline void __exchange_as_string(stream & s, STRINGABLE & stringable);

class CLASS_DECL_ACME text_stream :
   virtual public stream_base
{
public:


   using RAW_POINTER = ::file::file *;

   ::file_pointer    m_p;

   text_stream() {}
   text_stream(::file::file * pfile) : m_p(pfile) { }
   text_stream(const text_stream & base) :
      m_p(base.m_p)
   {

   }
   text_stream(text_stream & base) :
      m_p(::move(base.m_p))
   {

   }
   ~text_stream() ;

   //virtual void destroy() ;

   void destroy() override;

   string as_string() const override;


   ::file::file * get_file() override { return m_p; }



   template < typename TYPE >
   void number_read(TYPE & t)
   {

      string str;

      m_p->read_string(str);

      ::from_string(t, str);

   }


   template < typename TYPE >
   void number_write(const TYPE & t)
   {

      string str;

      str = __string(t);

      m_p->print(str);

   }


   template < typename TYPE >
   void number_exchange(TYPE & t)
   {

      is_loading() ? number_read(t) : number_write(t);

   }


   template < typename TYPE >
   void string_read(TYPE & t)
   {

      string str;

      m_p->read_string(str);

      ::from_string(t, str);

   }


   template < typename TYPE >
   void string_write(const TYPE & t)
   {

      string str;

      str = __string(t);

      m_p->print(str);

   }


   template < typename TYPE >
   void string_exchange(TYPE & t)
   {

      is_loading() ? string_read(t) : string_write(t);

   }


   template < typename TYPE >
   void network_payload_exchange(TYPE & t);


   /*template < typename TYPE >
   void write_only(TYPE & t) { is_loading() ? throw ::exception(error_io) : operator <<(t); }

   template < typename TYPE >
   void exchange(const ::atom & atom, TYPE & t) { ::__string_exchange(*this, t); }*/


   //virtual void exchange(const ::atom &, i8 & i) { default_exchange(i); }
   //virtual void exchange(const ::atom &, i16 & i) { default_exchange(i); }
   //virtual void exchange(const ::atom &, i32 & i) { default_exchange(i); }
   //virtual void exchange(const ::atom &, i64 & i) { default_exchange(i); }
   //virtual void exchange(const ::atom &, u8 & u) { default_exchange(u); }
   //virtual void exchange(const ::atom &, u16 & u) { default_exchange(u); }
   //virtual void exchange(const ::atom &, u32 & u) { default_exchange(u); }
   //virtual void exchange(const ::atom &, u64 & u) { default_exchange(u); }
   //virtual void exchange(const ::atom &, float & f) { default_exchange(f); }
   //virtual void exchange(const ::atom &, double & d) { default_exchange(d); }
   //virtual void exchange(const ::atom &, ::earth::time & time) { default_exchange(time.m_time); }
   //virtual void exchange(const ::atom &, const char * psz) { write_only(psz); }
   //virtual void exchange(const ::atom &, string & str) { default_exchange(str); }
   //virtual void exchange(const ::atom &, ::file::path & path) { default_exchange(path); }
   //virtual void exchange(const ::atom &, ::atom & atom) { default_exchange(atom); }

   virtual bool is_stream_null();
   virtual bool is_stream_set();

   virtual void close() ;

   text_stream & operator <<(bool b) ;
   text_stream & operator <<(char ch)  ;
   text_stream & operator <<(uchar uch)  ;
#ifdef WINDOWS
   text_stream & operator <<(unichar wch)  ;
#endif
   text_stream & operator <<(i16 sh)  ;
   text_stream & operator <<(u16 u)  ;
   text_stream & operator <<(i32 i)  ;
   text_stream & operator <<(u32 u)  ;
   text_stream & operator <<(i64 i)  ;
   text_stream & operator <<(u64 u)  ;
   text_stream & operator <<(float f)  ;
   text_stream & operator <<(double d)  ;
   //virtual void write(const POINT_I32 & point) ;
   //virtual void write(const SIZE_I32 & size) ;
   //virtual void write(const ::rectangle_i32 &rectangle) ;

   text_stream & operator <<(const char * psz) ;
   text_stream & operator <<(const ::atom & atom) ;
   text_stream & operator <<(const ::string & str) ;
   text_stream & operator <<(const property_set& set) ;
   template < typename TYPE >
   void network_payload_write(const TYPE & t);

   //virtual void network_payload_write(const ::matter & matter);


   virtual void raw_print(const ::string & str);
   virtual void print_number(const ::string & str);

   virtual ::string get_location() const;

   virtual ::filesize get_position() const ;
   virtual void write(const void * psz, strsize s) ;

   operator void * () { return this; }

   text_stream & operator >>(bool & b) ;
   text_stream & operator >>(char & ch) ;
   text_stream & operator >>(uchar & uch) ;
#ifdef WINDOWS
   text_stream & operator >>(unichar & wch) ;
#endif
   text_stream & operator >>(i8 & i) ;
   text_stream & operator >>(i16 & sh) ;
   text_stream & operator >>(u16 & u) ;
   text_stream & operator >>(i32 & i) ;
   text_stream & operator >>(u32 & u) ;
   text_stream & operator >>(i64 & i) ;
   text_stream & operator >>(u64 & u) ;
   text_stream & operator >>(float & f) ;
   text_stream & operator >>(double & d) ;
   text_stream & operator >>(string & str) ;
   text_stream & operator >>(property_set& set) ;
   text_stream & operator >>(::atom & atom) ;

   template < typename TYPE >
   void network_payload_read(TYPE & matter);


};


using std_string_stream = ::text_stream;


class CLASS_DECL_ACME string_stream :
   public text_stream
{
public:


   string_stream() : text_stream(memory_new string_buffer()) { }
   string_stream(string_buffer * pfile) : text_stream(pfile) { }


   operator string & () {return m_p.cast < string_buffer>()->m_str; }


};


// namespace str
// {


   CLASS_DECL_ACME ::string __string(const text_stream & strstream);

   CLASS_DECL_ACME ::string __string(const string_stream & strstream);


// } // namespace str



