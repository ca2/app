#pragma once


#include "acme/primitive/primitive/memory_container.h"


class memory_file;


typedef __pointer(memory_file) memory_file_pointer;


class CLASS_DECL_ACME memory_file :
   virtual public ::file::file,
   virtual public memory_container
{
protected:


   memsize      m_position;


public:


   memory_file();
   memory_file(const ::file::e_open & eopen);
   memory_file(memsize iSize);
   memory_file(const memory_file & file);
   memory_file(memory_file && file);
   memory_file(void * pMemory, memsize dwSize);
   memory_file(::payload & payload, const ::file::e_open & eopen = e_null);
   memory_file(memory_base & memory, const ::file::e_open & eopen = e_null);
   memory_file(memory_base * pmemory, const ::file::e_open & eopen = e_null);
   template < typename MEMORY>
   memory_file(const __pointer(MEMORY) & pmemory, const ::file::e_open & eopen = e_null) : memory_file((MEMORY *) pmemory.get(), eopen) {}
   virtual ~memory_file();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   virtual bool is_valid() const override;
   memsize erase_begin(void * pdata, memsize uiCount);


   void load_string(string & str);
   filesize translate(filesize offset, ::enum_seek eseek) override;
   filesize get_position() const override;


   ::file::path get_file_path() const override;


   void set_size(filesize dwNewLen) override;
   ::filesize get_size() const override;
   void clear();



   using ::file::file::read;
   virtual memsize read(void *pdata, memsize nCount) override;


   using ::file::file::write;
   virtual void write(const void * pdata, memsize nCount) override;


   virtual void write_from_hex(const void * pdata,memsize nCount) override;

   void flush() override;

   string to_string() const override;

   //virtual void full_load(::payload varFile);

   using ::file::file::get_internal_data;
   virtual void * get_internal_data() override;
   virtual memsize get_internal_data_size() const override;
   virtual bool set_internal_data_size(memsize c) override;

   virtual void to(::file::file * pfileOut, memsize uiBufferSize = 1024 * 1024) override;

   void copy_this(const memory_file & file);

   virtual bool get_status(::file::file_status & rStatus) const override;

   memory_file & operator = (const memory_file & file);

   memsize read_inline(void *pdata, memsize nCount)
   {

      memsize iDiff = m_pmemory.m_p->m_memory.m_cbStorage - m_position;

      if (iDiff <= 0)
         return 0;

      if (nCount > (memsize) iDiff)
         nCount = iDiff;

      if (nCount == 1)
      {

         *((byte*)pdata) = m_pmemory.m_p->m_memory.m_pdata[m_position];


      }
      else if (nCount == 2)
      {

         *((u16 *)pdata) = *((u16 *)&m_pmemory.m_p->m_memory.m_pdata[m_position]);


      }
      else if (nCount == 4)
      {

         *((u32*)pdata) = *((u32*)&m_pmemory.m_p->m_memory.m_pdata[m_position]);


      }
      else if (nCount == 8)
      {

         *((u64 *)pdata) = *((u64 *)&m_pmemory.m_p->m_memory.m_pdata[m_position]);


      }
      else
      {

         ::memcpy_dup(pdata, &m_pmemory.m_p->m_memory.m_pdata[m_position], (size_t)nCount);


      }

      m_position += nCount;

      return nCount;
   }


   void write_inline(const void * pdata, memsize nCount)
   {

      if (nCount <= 0)
         return;

      memsize iEndPosition = m_position + nCount;

      if (iEndPosition <= 0)
      {

         m_position = 0;

         return;

      }

      if (m_pmemory.is_null() || iEndPosition > m_pmemory->get_size())
      {

         set_size(iEndPosition);

      }

      byte * pb = get_data();


      //ASSERT(__is_valid_address(&(pb)[m_position], (uptr)nCount, true));


      ::memcpy_dup(&(pb)[m_position], pdata, (size_t)nCount);


      m_position = (memsize)iEndPosition;

   }

};


inline stream & operator << (stream & s, ::memory_file * pfile)
{

   s.write(&pfile->get_data()[pfile->get_position()], (memsize) pfile->get_remaining_byte_count());

   return s;

}


class CLASS_DECL_ACME memory_stream :
   public binary_stream
{
public:


   memory_stream() : binary_stream(__new(::memory_file)) {}
   memory_stream(::memory_base & memory) : binary_stream(__new(::memory_file(memory))) {}

   ::memory_file * operator ->() { return m_p.cast < ::memory_file >().m_p; }
   const ::memory_file * operator ->() const { return m_p.cast < ::memory_file >().m_p; }


};

//auto __create_memory_stream() { return ::memory_stream(; }

inline memory_file_pointer create_memory_file() { return __create_new < ::memory_file >(); }
inline memory_file_pointer create_memory_file(::memory_base & memory) { return __new(::memory_file(memory)); }
