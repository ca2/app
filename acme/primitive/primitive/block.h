#pragma once


struct CLASS_DECL_ACME block
{

   
   byte *                     m_pdata;
   memsize_storage            m_iSize;


   block(const void * pdata = nullptr, i64 iSize = 0) : m_pdata((byte *) pdata), m_iSize(iSize) {}
   block(const memory_base & memory);
   block(const memory_base * pmemory);
   block(const block & block) : ::block(block.m_pdata, block.m_iSize) {}


   block & operator = (const block & block) { if (this != &block) { m_pdata = block.m_pdata; m_iSize = block.m_iSize; } return *this; }

   void * get_data() const { return m_pdata; }
   memsize get_size() const { return (memsize_cast) m_iSize; }
   memsize size() const { return (memsize)m_iSize; }

#ifdef _UWP
   
   ::Windows::Storage::Streams::IBuffer^ get_os_buffer(memsize pos = 0, memsize size = -1) const;
   Array < uchar, 1U >^ get_os_bytes(memsize pos, memsize size) const;

#endif

   block & from_base64(const char * psz, strsize iSize) const;
   string to_base64() const;

   bool operator == (const block & block) const
   {

      if (block.get_size() != get_size())
      {

         return false;

      }

      return __memcmp(block.get_data(), get_data(), (size_t) get_size()) == 0;

   }

};

namespace acme
{


   template < typename T >
   inline void memory_free(T * & point);

}


struct CLASS_DECL_ACME fork_block :
   public block
{

   fork_block(void * pdata = nullptr, memsize iSize = 0) : block(memory_alloc(iSize), iSize) { memcpy_dup(m_pdata, pdata, (size_t) iSize); }
   fork_block(const block & block) : fork_block(block.get_data(), block.get_size()) {}
   fork_block(block && block) : fork_block(block.get_data(), block.get_size()) { block.m_pdata = NULL; block.m_iSize = 0; }
   fork_block(const memory_base & memory);
   ~fork_block() { destroy(); }

   fork_block & from_base64(const char * psz, strsize iSize);

   void destroy();

   fork_block & operator = (const block & block);

   fork_block & operator = (const fork_block & block);


   void assign(const void * pdata, i64 iSize);


   fork_block & operator = (block && block);


};


namespace hex
{


   inline CLASS_DECL_ACME string lower_from(const block & block)
   {
      
      return lower_from(block.get_data(), block.get_size());

   }

   inline CLASS_DECL_ACME string upper_from(const block & block)
   {
      
      return upper_from(block.get_data(), block.get_size());

   }


} // namespace hex


