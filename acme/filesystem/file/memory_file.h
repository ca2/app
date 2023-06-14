#pragma once


#include "acme/primitive/primitive/memory_container.h"
#include "file.h"

#pragma pack(push, custom__integers__, 1)

struct u24 { ::u8 m_u[3]; };

struct u40 { ::u8 m_u[5]; };

struct u48 { ::u8 m_u[6]; };

struct u56 { ::u8 m_u[7]; };

#pragma pack(pop, custom__integers__)

class memory_file;


typedef ::pointer<memory_file>memory_file_pointer;


inline void inline_byte_array_copy(::u8 * target, const ::u8 * source, ::memsize s)
{

   switch (s)
   {
   case 1:
      *target = *source;
      break;
   case 2:
      *(::u16 *)target = *(::u16 *)source;
      break;
   case 3:
      *(::u24 *)target = *(::u24 *)source;
      break;
   case 4:
      *(::u32 *)target = *(::u32 *)source;
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
      *(::u64 *)target = *(::u64 *)source;
      break;
   default:
      ::memcpy(target, source, s);
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

   void put_byte_back(::u8 u8) override;

   virtual void write_from_hex(const ::block & block) override;

   void flush() override;

   string as_string() const override;

   //virtual void full_load(::payload payloadFile);

   bool is_in_memory_file() const override { return true; }

   using ::file::file::full_data;
   ::u8 * full_data_begin() override;
   ::u8 * full_data_end() override;
   const ::u8 * full_data_begin() const override;
   const ::u8 * full_data_end() const override;
   ::u8 * data_begin() override;
   ::u8 * data_end() override;
   const ::u8 * data_begin() const override;
   const ::u8 * data_end() const override;

   using ::file::file::data;

   //virtual memsize get_internal_data_size() const override;
   bool full_data_set_size(memsize c) override;



   //virtual void to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) override;

   void copy_this(const memory_file & file);

   ::file::file_status get_status() const override;

   memory_file & operator = (const memory_file & file);

   inline memsize _get_left() { return m_memsize - m_position; }
   inline bool _is_end_of_file() const { return m_position >= m_memsize; }

   inline int _get_u8()
   {

      return _get_left() < 1 ? -1 : ((u8 *)m_pmemory.m_p->data())[m_position++];

   }

   inline u8 get_u8_unbounded()
   {

      return m_pbyte[m_position++];

   }


   inline int _get_u16()
   {

      if (_get_left() < 2)
      {

         return -1;

      }

      auto i = *(u16 *)&m_pmemory.m_p->data()[m_position];

      m_position += 2;

      return i;

   }


   inline u16 get_u16_unbounded()
   {

      auto u = *(u16 *)(m_pbyte + m_position);

      m_position += 2;

      return u;

   }


   inline bool _get_u64(::u64 & u64)
   {

      if (_get_left() < 8)
      {

         return false;

      }

      u64 = *((::u64 *)&(m_pmemory.m_p->data()[m_position]));

      m_position += 8;

      return true;

   }


   inline u64 get_u64_unbounded()
   {

      auto u = *(u64 *)(m_pbyte + m_position);

      m_position += 8;

      return u;

   }


   int get_u8() override;
   int get_u16() override;
   bool get_u64(::u64 & u64) override;
   bool is_end_of_file() const override;


   bool read_string(memory_base & memory) override;


   memsize read_inline(void * p, ::memsize s)
   {

      auto target = (::u8 *)p;

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

      auto source = (const ::u8 *)p;

      auto e = m_position + s;

      if (e <= 0)
      {

         return;

      }

      if (e > m_pmemory->size())
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
//   public binary_stream < FILE >
//{
//public:
//
//
//   memory_stream() : binary_stream < FILE >(__new(::memory_file)) {}
//   memory_stream(::memory_base & memory) : binary_stream < FILE >(__new(::memory_file(memory))) {}
//
//   ::memory_file * operator ->() { return m_p.cast < ::memory_file >().m_p; }
//   const ::memory_file * operator ->() const { return m_p.cast < ::memory_file >().m_p; }
//
//
//};

//auto __create_memory_stream() { return ::memory_stream(; }

CLASS_DECL_ACME memory_file_pointer create_memory_file();
CLASS_DECL_ACME memory_file_pointer create_memory_file(::memory_base & memory);
CLASS_DECL_ACME memory_file_pointer create_memory_file(const ::block & block);
CLASS_DECL_ACME memory_file_pointer create_memory_file_as_copy(const memory & memory);
CLASS_DECL_ACME memory_file_pointer create_memory_file_by_reading(::file::file * pfile);




template < primitive_payload PAYLOAD >
memory_file::memory_file(PAYLOAD & payload, ::file::e_open eopen) :
   memory_container(payload)
{

   m_eopen = eopen;
   m_position = 0;
   m_estatus = ::success;

}

