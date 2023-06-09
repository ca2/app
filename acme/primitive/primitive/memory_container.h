#pragma once


#include "memory_base.h"
////#include "acme/primitive/primitive/object.h"
#include "memory.h"


class shared_memory;
class paged_memory;


class CLASS_DECL_ACME memory_container :
   virtual public ::object
{
protected:


   ::pointer<memory_base>                       m_pmemory;


public:

   
   byte *                                       m_pbyte;
   memsize                                      m_memsize;


   memory_container(memsize size = 0);
   memory_container(const memory_container & container);
   memory_container(const void * pdata, memsize size);
   template < primitive_payload PAYLOAD >
   memory_container(PAYLOAD & payload);
   memory_container(memory_base & memory);
   memory_container(memory_base * pmemory);
   template < typename MEMORY>
   memory_container(const ::pointer<MEMORY> pmemory, ::file::e_open eopen = e_null) : memory_container((MEMORY*)pmemory.get(), eopen) {}
   virtual ~memory_container();

   virtual void create_default_memory();

   inline void defer_create_default_memory() {  if (!m_pmemory) create_default_memory(); }

   void allocate_add_up(memsize dwAddUp);
   void set_size(memsize dwNewLength);
   void allocate_internal(memsize dwNewLength);

   virtual ::pointer<memory_base>create_memory(const void * p = nullptr, memsize s = 0);
   ::pointer<memory_base>get_memory();
   void set_memory(::pointer<memory_base>pmemory);


   inline memory_base & memory() { return *get_memory(); }

   memsize size() const { return m_pmemory->size(); }

   memsize storage_size() const { return m_pmemory->storage_size(); }

   void from_string(const ::wide_character * pwsz);
   void from_string(const ::scoped_string & scopedstr);
   void from_string(const ::string & str);
   template < primitive_payload PAYLOAD >
   void from_string(const PAYLOAD & payload);
   ::string as_string() const override;
   virtual ::memory as_memory() const;

   void read(memory_base *pmemorystorage);

   //virtual stream & write(::stream & stream) const override;
   //virtual stream & read(::stream & stream) override;

   byte * data() { return ::is_set(m_pmemory)?m_pmemory->data():nullptr; }
   const byte * data() const { return ::is_set(m_pmemory) ? m_pmemory->data() : nullptr; }

   byte * begin() { return data(); }
   const byte * begin() const { return data(); }

   byte * end() { return ::is_set(m_pmemory) ? m_pmemory->end() : nullptr; }
   const byte * end() const { return ::is_set(m_pmemory) ? m_pmemory->end() : nullptr; }

   //byte * get_data_raw();
   //const byte * get_data_raw() const;

   virtual bool is_valid() const;

   void copy_this(const memory_container & container);

   memory_container & operator =(const memory_container &container);

   bool attach(memory_base *pstorage);

   memory_base * detach();

   virtual class memory *          get_primitive_memory();
#if !defined(UNIVERSAL_WINDOWS)
   virtual shared_memory *   get_shared_memory();
#endif
   paged_memory *  get_virtual_memory();


   //string as_string() const;
   void set_string(const ::string & str);


};


//inline byte * memory_container::get_data_raw()
//{
//
//   return m_pmemory->get_data();
//
//}
//
//inline const byte * memory_container::get_data_raw() const
//{
//
//   return m_pmemory->get_data();
//
//}
//
//inline memsize memory_container::get_size_raw() const
//{
//   return m_pmemory->get_size();
//}
//
//
//inline byte * memory_container ::get_data()
//{
//
//   return m_pmemory.is_null() ? 0 : get_data_raw();
//
//}
//
//inline const byte * memory_container ::get_data() const
//{
//
//   return m_pmemory.is_null() ? 0 : get_data_raw();
//
//}
//
//inline memsize memory_container ::get_size() const
//{
//   return m_pmemory.is_null() ? 0 : get_size_raw();
//}
//

inline void memory_container ::from_string(const ::wide_character * pwsz)
{

   if(m_pmemory.is_null())
      m_pmemory = create_memory();

   m_pmemory->from_string(pwsz);

}


inline void memory_container ::from_string(const ::scoped_string & scopedstr)
{

   if(m_pmemory.is_null())
      m_pmemory = create_memory();

   m_pmemory->from_string(scopedstr);

}

inline void memory_container ::from_string(const ::string & str)
{

   if(m_pmemory.is_null())
      m_pmemory = create_memory();

   m_pmemory->from_string(str);

}


template < primitive_payload PAYLOAD >
inline void memory_container ::from_string(const PAYLOAD & payload)
{

   if(m_pmemory.is_null())
      m_pmemory = create_memory();

   m_pmemory->from_string(payload);

}


//inline string memory_container::as_string() const
//{
//
//   if (!m_pmemory)
//   {
//
//      return "";
//
//   }
//
//   return m_pmemory->as_string();
//
//}


inline ::string memory_container::as_string() const
{

   return { (const ::ansi_character * ) data(), size() };

}


inline ::memory memory_container::as_memory() const
{

   return { data(), size() };

}


template < primitive_payload PAYLOAD >
memory_container::memory_container(PAYLOAD & payload)
{

   m_pmemory = &payload.memory_reference();
   m_pbyte = m_pmemory->data();
   m_memsize = m_pmemory->size();

}
