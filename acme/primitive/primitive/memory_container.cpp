#include "framework.h"
#include "memory.h"
#include "memory_container.h"
////#include "acme/exception/exception.h"
//#include "acme/primitive/primitive/payload.h"


memory_container::memory_container(memsize size)
{

   set_size(size);

}


memory_container::memory_container(const void * pdata, memsize size)
{

   m_pmemory = __new(class memory(this, pdata, size));
   m_pbyte = (byte *) pdata;
   m_memsize = size;

}




memory_container::memory_container(memory_base & memory)
{

   m_pmemory = &memory;
   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


memory_container::memory_container(memory_base * pmemory)
{

   m_pmemory = pmemory;
   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


memory_container::memory_container(const memory_container & container)
{

   operator = (container);

}


memory_container::~memory_container()
{

}


void memory_container::allocate_add_up(memsize dwAddUp)
{

   set_size(this->size() + dwAddUp);

}


void memory_container::set_size(memsize dwNewLength)
{

   if(dwNewLength <= 0)
   {

      if(m_pmemory.is_set())
      {

         m_pmemory->set_size(dwNewLength);
         m_pbyte = m_pmemory->data();
         m_memsize = m_pmemory->storage_size();

      }

      return;

   }

   defer_create_default_memory();

   m_pmemory->set_size(dwNewLength);
   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


void memory_container::create_default_memory()
{

   create_memory();

   if (!m_pmemory)
   {

      throw ::exception(error_no_memory);

   }

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


void memory_container::allocate_internal(memsize dwNewLength)
{

   defer_create_default_memory();

   m_pmemory->allocate_internal(dwNewLength);

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


::pointer<memory_base>memory_container::get_memory()
{

   if(m_pmemory.is_null())
   {

      m_pmemory = create_memory();

   }

   return m_pmemory;

}


void memory_container::set_memory(::pointer<memory_base>pmemory)
{

   if (m_pmemory == pmemory)
   {

      return;

   }

   m_pmemory = pmemory;

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


::pointer<memory_base>memory_container::create_memory(const void * p, memsize s)
{

   return __new(class memory(this, p, s));

}


void memory_container::read(memory_base * pmemory)
{

   defer_create_default_memory();

   m_pmemory->copy_from(pmemory);

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


bool memory_container::is_valid() const
{

   return true;

}


void memory_container::copy_this(const memory_container & container)
{

   if (container.m_pmemory.is_null())
   {

      m_pmemory.release();

   }
   else
   {

      defer_create_default_memory();

   }

   m_pmemory->copy_from(container.m_pmemory);

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

}


memory_container & memory_container::operator =(const memory_container &container)
{

   if (&container == this)
   {

      return *this;

   }

   memory_container::copy_this(container);

   return *this;

}


bool memory_container::attach(memory_base * pstorage)
{

   m_pmemory = pstorage;

   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->storage_size();

   return true;

}


memory_base * memory_container::detach()
{

   return m_pmemory.detach();

}


memory * memory_container::get_primitive_memory()
{

   defer_create_default_memory();

   return m_pmemory->m_pprimitivememory;

}


#if !defined(UNIVERSAL_WINDOWS)


shared_memory * memory_container::get_shared_memory()
{

   return m_pmemory->m_psharedmemory;

}


#endif


paged_memory * memory_container::get_virtual_memory()
{

   return m_pmemory->m_pvirtualmemory;

}


void memory_container::set_string(const ::string & str)
{

   memory().assign(str);

}



