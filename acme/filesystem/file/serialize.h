#pragma once

//#include "file_stream.h"

namespace file
{

   class exception;
   class file;

} // namespace

enum e_set_version
{

   set_version,

};


//class CLASS_DECL_ACME stream :
//   virtual public stream
//{
//public:
//
//
//   bool              m_b64bit;
//
//
//   stream(stream & stream);
//   stream(e_set_version = set_version, ::collection::index iVersion = FIRST_VERSION);
//   stream(::file::file * pfile, ::collection::index iVersion = FIRST_VERSION);
//   stream(e_create_new, ::particle * pparticle, ::collection::index iVersion = FIRST_VERSION);
//   virtual ~stream();
//
//
//   //stream & operator = (const stream & stream);
//
//   virtual bool is_stream_null();
//   virtual bool is_stream_set();
//
//   virtual void close();
//
//   virtual filesize get_position() const;
//
////      void read(int & i);
////      void read(unsigned int & u);
////      void read(long long & i);
////      void read(unsigned long long & u);
//
//   using stream::read;
//   virtual stream & read (bool & b) override;
//   virtual stream & read (char & ch) override;
//   virtual stream & read (unsigned char & uch) override;
//#ifdef WINDOWS
//   virtual stream & read (unichar & wch) override;
//#endif
//   virtual stream & read(char & I) override;
//   virtual stream & read (short & sh) override;
//   virtual stream & read (unsigned short & u) override;
//   virtual stream & read (int & i) override;
//   virtual stream & read (unsigned int & u) override;
//   virtual stream & read (long long & i) override;
//   virtual stream & read (unsigned long long & u) override;
//   virtual stream & read (float & f) override;
//   virtual stream & read (double & d) override;
//   virtual stream & read(::int_point * ppoint) ;
//   virtual stream & read(::int_size * psize) ;
//   virtual stream & read (::int_rectangle * prectangle) ;
//
//   virtual stream & read (string & str) override;
//
//   virtual string get_location() const;
//
//   void full_load(string & str);
//
//   using stream::write;
//   virtual stream & write(char ch) override;
//   virtual stream & write(uchar uch) override;
//   virtual stream & write(char i) override;
//   virtual stream & write (short sh) override;
//   virtual stream & write (unsigned short u) override;
//#ifdef WINDOWS
//   virtual stream & write (unichar wch) override;
//#endif
//   virtual stream & write (bool b) override;
//   virtual stream & write (int i) override;
//   virtual stream & write (unsigned int u) override;
//   virtual stream & write (long long i) override;
//   virtual stream & write (unsigned long long u) override;
//   virtual stream & write (float f) override;
//   virtual stream & write (double d) override;
//   virtual stream & write(const ::int_point * ppoint);
//   virtual stream & write(const ::int_size * psize) ;
//   virtual stream & write (const ::int_rectangle * prectangle) ;
//   virtual stream & write (const ::scoped_string & scopedstr) override;
//   virtual stream & write (const ::string & str) override;
//
//   virtual void write_from_hex(const ::scoped_string & scopedstr, character_count iLen = -1);
//   virtual void write_from_hex(const ::string & str);
//
//};








//class CLASS_DECL_ACME reader :
//   virtual public stream
//{
//public:
//
//
//   reader(reader && reader);
//   reader(::particle * pparticle, ::collection::index iVersion = FIRST_VERSION);
//   reader(::file::file * pfile, ::collection::index iVersion = FIRST_VERSION);
//   virtual ~reader();
//
//
//   virtual bool is_storing();
//
//
//};
//
//
//class CLASS_DECL_ACME writer :
//   virtual public stream
//{
//public:
//
//
//   writer(writer && writer);
//   writer(::particle * pparticle, ::collection::index iVersion = FIRST_VERSION);
//   writer(::file::file * pfile, ::collection::index iVersion = FIRST_VERSION);
//   virtual ~writer();
//
//
//   virtual bool is_storing();
//
//
//};


//class CLASS_DECL_ACME memory_reader :
//   virtual public reader
//{
//public:
//
//
//   memory_reader(memory_reader && reader);
//   memory_reader(::particle * pparticle, ::collection::index iVersion = FIRST_VERSION);
//   virtual ~memory_reader();
//
//
//   memory & get_memory();
//
//
//};


//class CLASS_DECL_ACME memory_writer :
//   virtual public writer
//{
//public:
//
//
//   memory_writer(memory_writer && writer);
//   memory_writer(::particle * pparticle, ::collection::index iVersion = FIRST_VERSION);
//   virtual ~memory_writer();
//
//
//   memory & get_memory();
//
//
//};

