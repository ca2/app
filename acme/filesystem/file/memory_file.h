#pragma once


#include "acme/prototype/prototype/memory_container.h"
#include "file.h"

#pragma pack(push, custom__integers__, 1)

struct u24 { unsigned char m_u[3]; };

struct u40 { unsigned char m_u[5]; };

struct u48 { unsigned char m_u[6]; };

struct u56 { unsigned char m_u[7]; };

#pragma pack(pop, custom__integers__)

class memory_file;


typedef ::pointer<memory_file>memory_file_pointer;


inline void inline_byte_array_copy(unsigned char * target, const unsigned char * source, ::memsize s)
{

   switch (s)
   {
   case 1:
      *target = *source;
      break;
   case 2:
      *(unsigned short *)target = *(unsigned short *)source;
      break;
   case 3:
      *(::u24 *)target = *(::u24 *)source;
      break;
   case 4:
      *(unsigned int *)target = *(unsigned int *)source;
      break;
   case 5:
      *(::u40 *)target = *(::u40 *)source;
      break;
   case 6:
      *(::u48 *)target = *(::u48 *)source;
      break;
   case 7:
      *(::u56 *)target = *(::u56 *)source;
      break;
   case 8:
      *(huge_natural *)target = *(huge_natural *)source;
      break;
   default:
      ::memory_copy(target, source, s);
      break;
   }

}


class CLASS_DECL_ACME memory_file :
   virtual public ::file::file,
   virtual public memory_container
{
protected:


   memsize        m_position;


public:


   memory_file();
   memory_file(::file::e_open eopen);
   memory_file(memsize iSize);
   memory_file(const memory_file & file);
   memory_file(memory_file && file);
   memory_file(const void * pmemory, memsize dwSize);
   memory_file(const ::block & block);
   template < primitive_payload PAYLOAD >
   memory_file(PAYLOAD & payload, ::file::e_open eopen = e_null);
   memory_file(memory_base & memory, ::file::e_open eopen = e_null);
   memory_file(memory_base * pmemory, ::file::e_open eopen = e_null);
   template < typename MEMORY>
   memory_file(const ::pointer<MEMORY> & pmemory, ::file::e_open eopen = e_null) : memory_file((MEMORY *)pmemory.get(), eopen) {}
   ~memory_file() override;


   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;


   virtual bool is_valid() const override;
   memsize erase_begin(void * pdata, memsize uiCount);
   memsize erase_begin(memsize uiCount);


   void load_string(string & str);
   void translate(filesize offset, ::enum_seek eseek) override;
   filesize get_position() const override;
   virtual void raw_set_position(memsize memsize);


   ::file::path get_file_path() const override;


   void set_size(filesize dwNewLen) override;
   ::filesize size() const override;
   void clear();



   using ::file::file::read;
   virtual memsize read(void * p, ::memsize s) override;


   using ::file::file::write;
   void write(const void * p, ::memsize s) override;


   void write(::file::readable * pfileIn, memsize uiBufSize = 16_MiB) override;

   void put_byte_back(unsigned char uch) override;

   virtual void write_from_hex(const ::block & block) override;

   void flush() override;

   string as_string() const override;

   //virtual void full_load(::payload payloadFile);

   bool is_in_memory_file() const override { return true; }

   using ::file::file::full_data;
   unsigned char * full_data_begin() override;
   unsigned char * full_data_end() override;
   const unsigned char * full_data_begin() const override;
   const unsigned char * full_data_end() const override;
   unsigned char * data_begin() override;
   unsigned char * data_end() override;
   const unsigned char * data_begin() const override;
   const unsigned char * data_end() const override;

   using ::file::file::data;

   //virtual memsize get_internal_data_size() const override;
   bool full_data_set_size(memsize c) override;



   //virtual void to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) override;

   void copy_this(const memory_file & file);

   ::file::file_status get_status() const override;

   memory_file & operator = (const memory_file & file);

   inline memsize _get_left() { return m_pmemory->size() - m_position; }
   inline bool _is_end_of_file() const { return m_position >= m_pmemory->size(); }

   inline int _get_unsigned_char()
   {

      return _get_left() < 1 ? -1 : ((unsigned char *)m_pmemory.m_p->data())[m_position++];

   }

   inline unsigned char get_byte_unbounded()
   {

      return m_pbyte[m_position++];

   }


   inline int _get_unsigned_short()
   {

      if (_get_left() < 2)
      {

         return -1;

      }

      auto i = *(unsigned short *)&m_pmemory.m_p->data()[m_position];

      m_position += 2;

      return i;

   }


   inline unsigned short get_u16_unbounded()
   {

      auto u = *(unsigned short *)(m_pbyte + m_position);

      m_position += 2;

      return u;

   }


   inline bool _get_huge_natural(huge_natural & hn)
   {

      if (_get_left() < 8)
      {

         return false;

      }

      hn = *((huge_natural *)&(m_pmemory.m_p->data()[m_position]));

      m_position += 8;

      return true;

   }


   inline huge_natural get_u64_unbounded()
   {

      auto u = *(huge_natural *)(m_pbyte + m_position);

      m_position += 8;

      return u;

   }


   int get_unsigned_char() override;
   int get_unsigned_short() override;
   bool get_huge_natural(huge_natural & hn) override;
   bool is_end_of_file() const override;


   bool read_string(memory_base & memory) override;


   memsize read_inline(void * p, ::memsize s)
   {

      auto target = (unsigned char *)p;
      
      if(::is_null(m_pmemory))
      {
       
         return 0;
         
      }

      memsize left = m_pmemory->size() - m_position;

      if (s > left)
      {

         s = left;

      }

      if (s <= 0)
      {

         return 0;

      }

      auto source = m_pmemory->m_begin + m_position;

      inline_byte_array_copy(target, source, s);

      m_position += s;

      return s;

   }


   void write_inline(const void * p, ::memsize s)
   {

      auto source = (const unsigned char *)p;

      auto e = m_position + s;

      if (e <= 0)
      {

         return;

      }

      if (!m_pmemory || e > m_pmemory->size())
      {

         set_size(e);

      }

      auto target = m_pmemory->m_begin + m_position;

      inline_byte_array_copy(target, source, s);

      m_position = e;

   }


};


//inline stream & operator << (stream & s, ::memory_file * pfile)
//{
//
//   s.write(&pfile->data()[pfile->get_position()], (memsize) pfile->get_remaining_byte_count());
//
//   return s;
//
//}


//class CLASS_DECL_ACME memory_stream :
//   public binary_stream
//{
//public:
//
//
//   memory_stream() : binary_stream(__initialize_new ::memory_file())) {}
//   memory_stream(::memory_base & memory) : binary_stream(::as(___new ::memory_file(memory))) {}
//
//   ::memory_file * operator ->() { return m_p.cast < ::memory_file >().m_p; }
//   const ::memory_file * operator ->() const { return m_p.cast < ::memory_file >().m_p; }
//
//
//};

//auto __create_memory_stream() { return ::memory_stream(; }

//CLASS_DECL_ACME memory_file_pointer create_memory_file(;
//CLASS_DECL_ACME memory_file_pointer create_memory_file(::memory_base & memory);
//CLASS_DECL_ACME memory_file_pointer create_memory_file(const ::block & block);
//CLASS_DECL_ACME memory_file_pointer create_memory_file_as_copy(const memory & memory);
//CLASS_DECL_ACME memory_file_pointer create_memory_file_by_reading(::file::file * pfile);
//



template < primitive_payload PAYLOAD >
memory_file::memory_file(PAYLOAD & payload, ::file::e_open eopen) :
   memory_container(payload)
{

   m_eopen = eopen;
   m_position = 0;
   m_estatus = ::success;

}

