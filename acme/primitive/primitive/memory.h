#pragma once


inline strsize safe_strlen(void * p, strsize n)
{

   if (p == nullptr)
   {

      return 0;

   }

   const char * psz = (const char *)p;

   strsize i = 0;

   for (; i < n; i++)
   {

      if (psz[i] == '\0')
      {

         break;

      }

   }

   return i;

}

inline memsize operator ""_kb(long double d)
{
   return (memsize)(1024.0 * d);
}

inline memsize operator ""_kb(unsigned long long i)
{
   return (memsize)(1024 * i);
}

inline memsize operator ""_mb(long double d)
{
   return (memsize)(1024.0 * 1024.0 * d);
}

inline memsize operator ""_mb(unsigned long long i)
{
   return (memsize) (1024 * 1024 * i);
}

inline memsize operator ""_gb(long double d)
{
   return (memsize) (1024.0 * 1024.0 * 1024.0 * d);
}

inline memsize operator ""_gb(unsigned long long i)
{
   return (memsize) (1024 * 1024 * 1024 * i);
}

class CLASS_DECL_ACME memory :
   public memory_base
{
public:


   typedef memory data_type;


   bool        m_bAligned;


   memory(::matter * pobject = nullptr) { m_memory.m_pprimitivememory = this; m_bAligned = false; }
   memory(enum_create_new, bool bAligned);
   memory(const ::std::initializer_list < int > & iaList);
   memory(const u8 *, memsize size);
   memory(const void *, memsize size);
   memory(enum_copy_clone, const memory_base & memorybase);
   memory(const memory_base & memorybase);
   memory(const memory & memory);
   memory(const char * psz);
   memory(const ::block & block);
   memory(memory_container * pcontainer, memsize size = 0, ::u32 uAllocFlags = 0);
   memory(memory_container * pcontainer, const void * pdata, memsize size);
   memory(manager * pmanager);
   memory(const memory & memory, manager * pmanager);
   memory(const memory * pmemory, manager * pmanager);
   memory(const u8 * pchSrc, strsize nLength, manager * pmanager);
   memory(memory && memory);
   virtual ~memory();


   virtual byte * impl_alloc(memsize dwAllocation) override;
   virtual byte * impl_realloc(void * pdata, memsize dwAllocation) override;
   virtual void impl_free(byte * pdata) override;

   memory & operator = (const memory & memory);

};

using memory_pointer = __pointer(memory);

inline memory_pointer create_memory() { return __create_new < ::memory >(); }

class get_memory
{
public:


   memory_base *        m_pmemory;
   block                m_block;


   get_memory(memory_base & memory) : m_pmemory(&memory) { }
   get_memory(memory_base * pmemory) : m_pmemory(pmemory) { }
   // block is const, its memory not!!!!
   get_memory(const block & block) : m_block(block), m_pmemory(nullptr) { }
   // VOID * NOT const!!
   get_memory(/* NOTTTT const!!!!! */ void * p, memsize s) : m_block(p, s), m_pmemory(nullptr) { }

   ~get_memory() {}

   /*bool write(void * pdata, memsize s)
   {

      if (::is_set(m_pmemory))
      {

         m_pmemory->assign(pdata, s);

         return true;

      }
      else if (s < m_block.get_size())
      {

         return false;

      }

      if (::is_null(m_block.get_data()))
      {

         return false;

      }

      ::memcpy_dup(m_block.get_data(), pdata, m_block.get_size());

      return true;

   }*/


   void * get(memsize s)
   {

      if (::is_set(m_pmemory))
      {

         m_pmemory->set_size(s);

         return m_pmemory->get_data();

      }
      else if (s < m_block.get_size())
      {

         return NULL;

      }

      if (::is_null(m_block.get_data()))
      {

         return NULL;

      }

      return m_block.get_data();

   }


   inline bool get_base64(const ::string & str);
   inline bool get(const void * pdata, memsize s)
   {

      if (::is_set(m_pmemory))
      {

         m_pmemory->assign(pdata, s);

         return true;

      }
      else if (s < m_block.get_size())
      {

         return false;

      }

      if (::is_null(pdata))
      {

         return false;

      }

      ::memcpy_dup(m_block.get_data(), pdata, minimum(s, m_block.get_size()));

      return true;

   }
   inline bool get(const memory_base & memory)
   {
      return get(memory.get_data(), memory.get_size());
   }
   inline bool get(const block & block)
   {
      return get(block.get_data(), (memsize) block.get_size());
   }

   inline u8 * get_data() const
   {
      if(::is_set(m_pmemory))
      {
         return m_pmemory->get_data();
      }
      else
      {
         return (u8 *) m_block.get_data();
      }
   }

   inline i64 get_size() const
   {
      if(::is_set(m_pmemory))
      {
         return m_pmemory->get_size();
      }
      else
      {
         return m_block.get_size();
      }
   }

};


inline memory_file_pointer create_memory_file_copy(const memory& memory) { return __new(::memory_file(__create_new < ::memory > (memory))); }


