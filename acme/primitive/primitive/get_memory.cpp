#include "framework.h"
#include "get_memory.h"
#include "memory_base.h"
#include "acme/primitive/string/base64.h"


get_memory::get_memory(memory_base & memory) :
   m_pmemory(&memory)
{

}


get_memory::get_memory(memory_base * pmemory) :
   m_pmemory(pmemory) 
{ 

}
// block is const, its memory not!!!!
get_memory::get_memory(const block & block) :
   m_block(block), m_pmemory(nullptr) 
{

}

// VOID * NOT const!!
get_memory::get_memory(/* NOTTTT const!!!!! */ void * p, memsize s) : 
   m_block(p, s), m_pmemory(nullptr) 
{ 

}

get_memory::~get_memory() 
{

}

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


void * get_memory::get(memsize s)
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


bool get_memory::get_base64(const ::string & str)
{

   if (::is_set(m_pmemory))
   {

      m_pmemory->from_base64(str);

      return true;

   }
   else
   {

      ::base64 base64;

      return base64.decode(m_block, str);

   }

}




inline bool get_memory::get(const void * pdata, memsize s)
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
bool get_memory::get(const memory_base & memory)
{
   return get(memory.get_data(), memory.get_size());
}
bool get_memory::get(const block & block)
{
   return get(block.get_data(), (memsize)block.get_size());
}

u8 * get_memory::get_data() const
{
   if (::is_set(m_pmemory))
   {
      return m_pmemory->get_data();
   }
   else
   {
      return (u8 *)m_block.get_data();
   }
}


memsize get_memory::get_size() const
{

   if (::is_set(m_pmemory))
   {

      return m_pmemory->get_size();

   }
   else
   {

      return m_block.get_size();

   }

}
