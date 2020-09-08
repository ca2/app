#include "framework.h"


memory_container::memory_container(memsize size)
{

   //m_pvppa = nullptr;

   set_size(size);

}


memory_container ::memory_container(void * pdata, memsize size)
{

   //m_pvppa = nullptr;

   m_pmemory = __new(class memory(this, pdata, size));

}


memory_container::memory_container(var & var)
{

   //m_pvppa = nullptr;

   m_pmemory = &var.memory();

}


memory_container::memory_container(memory_base & memory)
{

   m_pmemory = &memory;

}


memory_container::memory_container(memory_base * pmemory)
{

   m_pmemory = pmemory;

}


memory_container ::memory_container(const memory_container & container)
{

   operator = (container);

}


memory_container ::   ~memory_container()
{
   //if(m_pvppa != nullptr)
   //{
      //delete m_pvppa;
     // m_pvppa = nullptr;

   //}
}


void memory_container ::allocate_add_up(memsize dwAddUp)
{

   set_size(this->get_size() + dwAddUp);

}


void memory_container::set_size(memsize dwNewLength)
{

   if(dwNewLength <= 0)
   {

      if(m_pmemory.is_set())
      {

         if(!m_pmemory->set_size(dwNewLength))
         {

            __throw(memory_exception());

         }

      }

      return;
   }

   defer_create_default_memory();

   if(!m_pmemory->set_size(dwNewLength))
   {

      __throw(memory_exception());

   }

}


void memory_container::create_default_memory()
{

   create_memory();

   if (!m_pmemory)
   {

      __throw(memory_exception());

   }

}


void memory_container ::allocate_internal(memsize dwNewLength)
{

   defer_create_default_memory();

   m_pmemory->allocate_internal(dwNewLength);

}


__pointer(memory_base) memory_container::get_memory()
{

   if(m_pmemory.is_null())
   {

      m_pmemory = create_memory();

   }

   return m_pmemory;

}


void memory_container::set_memory(__pointer(memory_base) pmemory)
{

   if (m_pmemory == pmemory)
   {

      return;

   }

   m_pmemory = pmemory;

   //::acme::del(m_pvppa);

}


__pointer(memory_base) memory_container::create_memory(const void * p, memsize s)
{

   return __new(class memory(this, p, s));

}




void memory_container ::read(memory_base * pmemory)
{

   defer_create_default_memory();

   m_pmemory->copy_from(pmemory);

}


//stream & memory_container ::write(::stream & stream) const
//{
//
//   if (!m_pmemory)
//   {
//
//      stream.write_buffer_length(0);
//
//   }
//   else
//   {
//
//      stream << *m_pmemory;
//
//   }
//
//   return stream;
//
//}
//
//
//stream & memory_container::read(::stream & stream)
//{
//
//   defer_create_default_memory();
//
//   stream >> *m_pmemory;
//
//   return stream;
//
//}


//void memory_container ::keep_pointer(void **ppvoid)
//{
//
//   //vppa().add(ppvoid);
//
//}
//
//
//void memory_container ::offset_kept_pointers(memsize iOffset)
//{
//
//   if (m_pvppa == nullptr)
//   {
//
//      return;
//
//   }
//
//   for(i32 i = 0; i < m_pvppa->get_size(); i++)
//   {
//
//      *m_pvppa->element_at(i) = ((byte *)*m_pvppa->element_at(i)) + iOffset;
//
//   }
//
//}


bool memory_container ::is_valid() const
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

   //if (m_pvppa != nullptr)
   //{

   //   delete m_pvppa;

   //   m_pvppa = nullptr;

   //}

   m_pmemory->copy_from(container.m_pmemory);

}


memory_container & memory_container ::operator =(const memory_container &container)
{

   if (&container == this)
   {

      return *this;

   }

   memory_container::copy_this(container);

   return *this;

}


bool memory_container ::attach(memory_base * pstorage)
{

   m_pmemory = pstorage;

   return true;

}


memory_base * memory_container::detach()
{

   return m_pmemory.detach();

}


memory * memory_container::get_primitive_memory()
{


   defer_create_default_memory();

   return m_pmemory->m_memory.m_pprimitivememory;

}


#if !defined(_UWP)
shared_memory *   memory_container::get_shared_memory()
{
   return m_pmemory->m_memory.m_psharedmemory;
}
#endif

virtual_memory *  memory_container::get_virtual_memory()
{
   return m_pmemory->m_memory.m_pvirtualmemory;
}


//memory *          memory_container::detach_primitive_memory()
//{
//   memory_base * pmemorybase = m_pmemory.detach();
//   if(pmemorybase != nullptr)
//      return nullptr;
//   memory * pmemory = pmemorybase->m_pprimitivememory;
//   if(pmemory != nullptr)
//   {
//      return pmemory;
//   }
//   pmemory = new memory(*pmemorybase);
//   delete pmemorybase;
//   return pmemory;
//}

//#if !defined(_UWP)
//   shared_memory *   memory_container::detach_shared_memory()
//   {
//      memory_base * pmemorybase = m_pmemory.detach();
//      if(pmemorybase != nullptr)
//         return nullptr;
//      shared_memory * psharedmemory = pmemorybase->m_psharedmemory;
//      if(psharedmemory != nullptr)
//      {
//         return psharedmemory;
//      }
//      psharedmemory = new shared_memory(*pmemorybase);
//      delete pmemorybase;
//      return psharedmemory;
//   }
//#endif
//
//   virtual_memory *  memory_container::detach_virtual_memory()
//   {
//      memory_base * pmemorybase = m_pmemory.detach();
//      if(pmemorybase != nullptr)
//         return nullptr;
//      virtual_memory * pvirtualmemory = pmemorybase->m_pvirtualmemory;
//      if(pvirtualmemory != nullptr)
//      {
//         return pvirtualmemory;
//      }
//      pvirtualmemory = new virtual_memory(*pmemorybase);
//      delete pmemorybase;
//      return pvirtualmemory;
//   }


//   byte * memory_container::detach_primitive_storage()
//   {
//      __pointer(memory) pmemory = detach_primitive_memory();
//      return pmemory->detach();
//   }
//
//
//   byte * memory_container::detach_virtual_storage()
//   {
//      __pointer(virtual_memory) pvirtualmemory = detach_virtual_memory();
//      return pvirtualmemory->detach();
//   }
//
//
//#if !defined(_UWP)
//   HGLOBAL memory_container::detach_shared_storage()
//   {
//      __pointer(shared_memory) psharedmemory = detach_shared_memory();
//      return psharedmemory->detach_shared_memory();
//   }
//#endif


void memory_container::str(const string & str)
{

   set_size(str.get_length());

   ::memcpy_dup(get_data(), str, get_size());

}


//address_array < void ** > & memory_container::vppa()
//{
//
//   if(m_pvppa == nullptr)
//   {
//
//      m_pvppa = new address_array < void ** > ();
//
//   }
//
//   return *m_pvppa;
//
//}



