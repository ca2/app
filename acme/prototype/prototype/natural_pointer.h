#pragma once


#include "acme/platform/acme.h"
#include "acme/memory/allocator.h"
#include "acme/memory/management.h"
#include "acme/prototype/prototype/interlocked_count.h"


template < typename NATURAL_DATA >
NATURAL_DATA* __nil() { return nullptr; }


#define NATURAL_METADATA_ALIGN 32


//#pragma pack(push, base_data, 1)


template < typename TYPE_DATA >
class base_data
{
public:


   using BASE_DATA_BASE = base_data < TYPE_DATA >;

   using DATA = non_const < TYPE_DATA >;


   interlocked_int                     m_countReference;
   memsize_storage                     m_sizeStorageInBytes;
   ::heap::enum_memory                 m_ememoryHeap;
   //memsize_storage                     m_countData;


   //heap_data(): m_countData(0), m_sizeStorageInBytes(0), m_countReference(1) {}
   //heap_data(enum_zero_init) : m_countData(0), m_sizeStorageInBytes(0), m_countReference(1) {}

   base_data() : m_sizeStorageInBytes(0), m_countReference(1) {}
   //heap_data(enum_zero_init) :  m_sizeStorageInBytes(0), m_countReference(1) {}

   bool base_data_is_shared() const { return m_countReference >= 2; }

   
   auto base_data_increment_reference_count() { return ++m_countReference; }

   
   auto base_data_decrement_reference_count() { return --m_countReference; }

   
   //constexpr static ::memsize base_dataoffset() { return (offsetof(base_data, m_endofmetadata) + NATURAL_METADATA_ALIGN - 1) & (~(NATURAL_METADATA_ALIGN - 1)); }

   
   DATA * data() const { return (DATA *)&(this[1]); }

   const DATA* c_data() const { return (const DATA*)&(this[1]); }


   //DATA * end() const { return (DATA *)(begin() + this->m_countData); }


   static base_data * base_data_from_data(const DATA * pdata) { return &((base_data *) pdata)[-1]; }


};


//#pragma pack(pop, base_data)


template < typename BASE_DATA_BASE >
class base_data :
   public BASE_DATA_BASE
{
public:


   using BASE_DATA         = typename BASE_DATA_BASE::BASE_DATA_BASE;
   using DATA              = typename BASE_DATA_BASE::DATA;

   unsigned char            m_data[sizeof(DATA)] = {};


   base_data() {}

   base_data(enum_zero_init) :BASE_DATA_BASE(e_zero_init){}

   
   /*bool is_set() { return ::is_set(this->m_begin); }

   
   bool is_null() { return !is_null(); }*/

   
   inline static base_data * base_data_from_data(const DATA* pdata)
   {

      //return ::is_set(pdata) ?
      //   (BASE_DATA*)BASE_DATA_BASE::base_data_from_data(pdata) :
      //   nullptr;
      return (base_data*) BASE_DATA_BASE::base_data_from_data(pdata);

   }


   inline static DATA* base_data_to_data(const BASE_DATA * pbasedata)
   {

      return (DATA *) pbasedata->data();

   }


   //inline BASE_DATA* metadata()
   //{

   //   return from_data(this->m_begin);

   //}


   //inline BASE_DATA* metadata() const
   //{

   //   return from_data(this->m_begin);

   //}


};


//#pragma pack(push,1)


template < typename BASE_DATA_BASE, ::heap::enum_memory t_ememory >
class natural_pointer
//class natural_pointer :
  // public RANGE_TYPE
{
public:


   using BASE_DATA = base_data < BASE_DATA_BASE >;
   //using META_DATA = BASE_DATA_BASE;
   using BASE = BASE_DATA_BASE;
   using DATA = typename BASE_DATA::DATA;
   //using iterator = typename RANGE_TYPE::iterator;


   //inline natural_pointer() : RANGE_TYPE(no_initialize_t{}) { }
   //inline natural_pointer(nullptr_t) : RANGE_TYPE(nullptr) { }
   //inline natural_pointer(const natural_pointer & natural_pointer)
   //{

   //   natural_pointer.metadata()->base_data_increment_reference_count();

   //   RANGE_TYPE::operator = (natural_pointer);

   //}
   /*inline natural_pointer(natural_pointer && natural_pointer)
   {

      RANGE_TYPE::operator = (::transfer(natural_pointer));

   }
   inline natural_pointer() : natural_pointer(no_initialize_t{})
   {

      natural_pointer_default_construct();

   }*/
   /*~natural_pointer()
   {

      destroy();

   }*/

   inline static ::heap::memory * memory() { return ::acme::get()->m_pheapmanagement->memory(t_ememory); }

//   void base_data_destroy()
//   {
//
//      //if (this->is_natural_pointer() && ::is_set(this->begin()))
//      if (this->is_string() && ::is_set(this->begin()))
//      {
//
//         //if (this->is_string())
//         //{
//
//            this->base_data_release(base_data_from_data(this->begin()));
//
////            this->clear_string_flag();
//
//  //       }
//
//         this->m_begin = nullptr;
//
//         this->m_end = nullptr;
//
//      }
//
//   }


   //natural_pointer & operator = (const natural_pointer & natural_pointer)
   //{

   //   if (this != &natural_pointer)
   //   {

   //      if (natural_pointer.is_string())
   //      {

   //         natural_pointer.metadata()->natural_increment_reference_count();

   //      }

   //      destroy();

   //      RANGE_TYPE::operator = (natural_pointer);

   //   }

   //   return *this;

   //}

   
   inline static BASE_DATA * base_data_create(character_count n)
   {

      memsize sizeStorageInBytes = n * sizeof(DATA);

      auto p = memory()->allocate(sizeStorageInBytes + sizeof(BASE), &sizeStorageInBytes);

      auto pbasedata = __raw_new (p) BASE_DATA();

      pbasedata->m_sizeStorageInBytes = sizeStorageInBytes - sizeof(BASE);

      return pbasedata;

   }


   //natural_pointer & operator = (natural_pointer && natural_pointer) 
   //{ 

   //   if (this->begin() != natural_pointer.begin())
   //   {

   //      destroy();

   //      RANGE_TYPE::operator = (::transfer(natural_pointer));

   //   }
   //   
   //   return *this; 
   //
   //}


   //void base_data_default_data()
   //{

   //   auto p = this->default_construct_natural_pointer();

   //   this->m_begin = (iterator) p->begin();

   //   this->m_end = (iterator) p->end();

   //   this->set_string_flag();

   //}


   inline BASE_DATA * base_data_default_data()
   {

      auto pnil = __nil< BASE_DATA >();

      return pnil;

      //pnil->natural_increment_reference_count();

      //return pnil;

   }




   //inline BASE_DATA * metadata() const
   //{

   //   //return ::is_set(this) && ::is_set(this->m_begin) ? BASE_DATA::from_data(this->m_begin) : nullptr;
   //   return BASE_DATA::from_data(this->m_begin);

   //}


   inline static void base_data_destroy(BASE_DATA * pbasedata)
   {

      memory()->free(pbasedata);

   }


   //void assign_natural_pointer(const natural_pointer& pointer)
   //{

   //   assign_natural_base_data(BASE_DATA::from_data(pointer.m_begin));

   //}


   //void create_assign_natural_base_data(BASE_DATA * p)
   //{

   //   p->natural_increment_reference_count();

   //   this->m_begin = (iterator) p->begin();

   //   this->m_end = (iterator) p->end();
   //   
   //   this->set_string_flag();

   //}


   //void assign_natural_base_data(BASE_DATA * pNew)
   //{

   //   auto pOld = BASE_DATA::from_data(this->m_begin);

   //   if (pOld != pNew)
   //   {

   //      pNew->natural_increment_reference_count();

   //      this->m_begin = (iterator)pNew->begin();

   //      this->m_end = (iterator)pNew->end();

   //      this->set_string_flag();

   //      natural_release(pOld);

   //   }

   //}


   //void place_natural_base_data(BASE_DATA * pNew)
   //{

   //   auto pOld = BASE_DATA::from_data(this->m_begin);

   //   if (pOld != pNew)
   //   {

   //      this->m_begin = (iterator)pNew->begin();

   //      this->m_end = (iterator)pNew->end();

   //      this->set_string_flag();

   //      natural_release(pOld);

   //   }

   //}


   //void natural_release()
   //{

   //   DATA * pdataOld = nullptr;
   //   
   //   if (this->is_string())
   //   {

   //      pdataOld = (DATA *)this->m_begin;

   //   }

   //   auto p = default_construct_natural_pointer();

   //   this->m_begin = (iterator)p->begin();

   //   this->m_end = (iterator)p->end();

   //   this->set_string_flag();

   //   if (::is_set(pdataOld))
   //   {

   //      natural_release(pdataOld);

   //   }

   //}


   //static void natural_release(DATA * pdata)
   //{

   //   natural_release(BASE_DATA::from_data(pdata));

   //}

  /* static void base_data_release(BASE_DATA * pbasedata)
   {

      if (::is_null(pbasedata))
      {

         return;

      }

      _natural_release(pbasedata);

   }*/


   static void base_data_release(BASE_DATA * pbasedata)
   {

      if (pbasedata->base_data_decrement_reference_count() == 0)
      {

         base_data_destroy(pbasedata);

      }

   }


   static BASE_DATA* base_data_from_data(const DATA* pdata)
   {
      
      return BASE_DATA::base_data_from_data(pdata);
   
   }


};


//#pragma pack(pop)



