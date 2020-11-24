#pragma once


class text_stream;


template < typename TYPE >
inline void __string_exchange(text_stream & s, TYPE & t);


inline void __string_exchange(stream & s, payload & payload);

inline void __string_exchange(text_stream & s, ansichar & ansich);
inline void __string_exchange(text_stream & s, widechar & widech);
inline void __string_exchange(text_stream & s, i8 & i);
inline void __string_exchange(text_stream & s, i16 & i);
inline void __string_exchange(text_stream & s, i32 & i);
inline void __string_exchange(text_stream & s, i64 & i);
inline void __string_exchange(text_stream & s, u8 & u);
inline void __string_exchange(text_stream & s, u16 & u);
inline void __string_exchange(text_stream & s, u32 & u);
inline void __string_exchange(text_stream & s, u64 & u);
inline void __string_exchange(text_stream & s, float & f);
inline void __string_exchange(text_stream & s, double & d);
inline void __string_exchange(text_stream & s, ::datetime::time & time);
inline void __string_exchange(text_stream & s, const char * psz);
inline void __string_exchange(text_stream & s, char * sz);
inline void __string_exchange(text_stream & s, string & str);
inline void __string_exchange(text_stream & s, ::file::path & path);
inline void __string_exchange(text_stream & s, ::id & id);
inline void __string_exchange(text_stream & s, void * & p);
inline void __string_exchange(text_stream & s, oswindow & oswindow);
inline void __string_exchange(text_stream & s, wchar_t sz[]);
//inline void __string_exchange(text_stream & s, ::matter & matter);

//inline void __string_exchange(text_stream & s, ::rect & r);



template < typename STRINGABLE >
inline void __exchange_as_string(stream & s, STRINGABLE & stringable);

class CLASS_DECL_ACME text_stream :
   public stream
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
   virtual ~text_stream();

   virtual void finalize() override;

   virtual void to_string(const string_exchange & str) const override;

   template < typename TYPE >
   void number_read(TYPE & t)
   {

      string str;

      m_p->read_string(str);

      ::str::to(t, str);

   }


   template < typename TYPE >
   void number_write(const TYPE & t)
   {

      string str;

      ::str::from(str, t);

      m_p->println(str);

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

      ::str::to(t, str);

   }


   template < typename TYPE >
   void string_write(const TYPE & t)
   {

      string str;

      ::str::from(str, t);

      m_p->print(str);

   }


   template < typename TYPE >
   void string_exchange(TYPE & t)
   {

      is_loading() ? string_read(t) : string_write(t);

   }


   template < typename TYPE >
   void json_exchange(TYPE & t);


   template < typename TYPE >
   void write_only(TYPE & t) { is_loading() ? set_fail_bit() : write(t); }

   template < typename TYPE >
   void exchange(const ::id & id, TYPE & t) { ::__string_exchange(*this, t); }


   //virtual void exchange(const ::id &, i8 & i) { default_exchange(i); }
   //virtual void exchange(const ::id &, i16 & i) { default_exchange(i); }
   //virtual void exchange(const ::id &, i32 & i) { default_exchange(i); }
   //virtual void exchange(const ::id &, i64 & i) { default_exchange(i); }
   //virtual void exchange(const ::id &, u8 & u) { default_exchange(u); }
   //virtual void exchange(const ::id &, u16 & u) { default_exchange(u); }
   //virtual void exchange(const ::id &, u32 & u) { default_exchange(u); }
   //virtual void exchange(const ::id &, u64 & u) { default_exchange(u); }
   //virtual void exchange(const ::id &, float & f) { default_exchange(f); }
   //virtual void exchange(const ::id &, double & d) { default_exchange(d); }
   //virtual void exchange(const ::id &, ::datetime::time & time) { default_exchange(time.m_time); }
   //virtual void exchange(const ::id &, const char * psz) { write_only(psz); }
   //virtual void exchange(const ::id &, string & str) { default_exchange(str); }
   //virtual void exchange(const ::id &, ::file::path & path) { default_exchange(path); }
   //virtual void exchange(const ::id &, ::id & id) { default_exchange(id); }

   virtual bool is_stream_null();
   virtual bool is_stream_set();

   virtual void close() override;

   virtual void write (bool b) override;
   virtual void write (char ch)  override;
   virtual void write (uchar uch)  override;
#ifdef WINDOWS
   virtual void write (unichar wch)  override;
#endif
   virtual void write (i16 sh)  override;
   virtual void write (u16 u)  override;
   virtual void write (i32 i)  override;
   virtual void write (u32 u)  override;
   virtual void write (i64 i)  override;
   virtual void write (u64 u)  override;
   virtual void write (float f)  override;
   virtual void write (double d)  override;
   //virtual void write(const POINT32 & point) override;
   //virtual void write(const SIZE32 & size) override;
   //virtual void write(const RECT32 & rect) override;

   virtual void write (const char * psz) override;
   virtual void write(const ::id & id) override;
   virtual void write(const ::string & str) override;
   virtual void write(const property_set& set) override;
   template < typename TYPE >
   void json_write(const TYPE & t);

   //virtual void json_write(const ::matter & matter);


   virtual void raw_print(const string & str);
   virtual void print_number(const string & str);

   virtual ::string get_location() const;

   virtual ::filesize get_position() const override { return m_p->get_position(); }
   virtual void write(const void * psz, strsize s) override { m_p->write(psz, s); }

   operator void * () { return this; }

   virtual void read (bool & b) override;
   virtual void read (char & ch) override;
   virtual void read (uchar & uch) override;
#ifdef WINDOWS
   virtual void read (unichar & wch) ;
#endif
   virtual void read(i8 & i) override;
   virtual void read (i16 & sh) override;
   virtual void read (u16 & u) override;
   virtual void read (i32 & i) override;
   virtual void read (u32 & u) override;
   virtual void read (i64 & i) override;
   virtual void read (u64 & u) override;
   virtual void read (float & f) override;
   virtual void read (double & d) override;
   virtual void read(string & str) override;
   virtual void read(property_set& set) override;
   virtual void read(::id & id) override;

   template < typename TYPE >
   void json_read(TYPE & matter);


};


using std_string_stream = ::text_stream;


class CLASS_DECL_ACME string_stream :
   public text_stream
{
public:


   string_stream() : text_stream(new string_file()) { }
   string_stream(string_file * pfile) : text_stream(pfile) { }


   operator string & () {return m_p.cast < string_file>()->m_str; }


};


namespace str
{


   CLASS_DECL_ACME void from(string & str, const text_stream & strstream);

   CLASS_DECL_ACME void from(string & str, const string_stream & strstream);


} // namespace str



