#include "framework.h"
#include "get_memory.h"
#include "memory_base.h"
#include "acme/prototype/string/base64.h"


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
   m_block((unsigned char *)p, ((unsigned char *)p) + s), m_pmemory(nullptr)
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
   else if (s < m_block.size())
   {

      return false;

   }

   if (::is_null(m_block.data()))
   {

      return false;

   }

   ::memory_copy(m_block.data(), pdata, m_block.size());

   return true;

}*/


void * get_memory::get(memsize s)
{

   if (::is_set(m_pmemory))
   {

      m_pmemory->set_size(s);

      return m_pmemory->data();

   }
   else if (s < m_block.size())
   {

      return NULL;

   }

   if (::is_null(m_block.data()))
   {

      return NULL;

   }

   return m_block.data();

}


bool get_memory::get_base64(const ::scoped_string & scopedstr)
{

   if (::is_set(m_pmemory))
   {

      m_pmemory->from_base64(scopedstr);

      return true;

   }
   else
   {

      ::base64 base64;

      return base64.decode(m_block, scopedstr);

   }

}


bool get_memory::get(const void * pdata, memsize s)
{

   if (::is_set(m_pmemory))
   {

      m_pmemory->assign(pdata, s);

      return true;

   }
   else if (s < m_block.size())
   {

      return false;

   }

   if (::is_null(pdata))
   {

      return false;

   }

   ::memory_copy(m_block.data(), pdata, minimum(s, m_block.size()));

   return true;

}
bool get_memory::get(const memory_base & memory)
{
   return get(memory.data(), memory.size());
}
bool get_memory::get(const block & block)
{
   return get(block.data(), (memsize)block.size());
}

unsigned char * get_memory::data() const
{
   if (::is_set(m_pmemory))
   {
      return m_pmemory->data();
   }
   else
   {
      return (unsigned char *)m_block.data();
   }
}


memsize get_memory::size() const
{

   if (::is_set(m_pmemory))
   {

      return m_pmemory->size();

   }
   else
   {

      return m_block.size();

   }

}
