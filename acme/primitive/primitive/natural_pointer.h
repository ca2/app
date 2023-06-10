#pragma once


#include "acme/memory/memory_allocator.h"
#include "acme/primitive/primitive/interlocked_count.h"


template < typename NATURAL_DATA >
NATURAL_DATA* __nil() { return nullptr; }


#define NATURAL_METADATA_ALIGN 32


#pragma pack(push, meta_data, 1)


template < typename TYPE_DATA >
class meta_data
{
public:


   using META = meta_data < TYPE_DATA >;

   using DATA = non_const < TYPE_DATA >;


   interlocked_count                   m_countReference;
   memsize_storage                     m_sizeStorageInBytes;
   memsize_storage                     m_countData;


   meta_data(): m_countData(0), m_sizeStorageInBytes(0), m_countReference(1) {}
   meta_data(enum_zero_init) : m_countData(0), m_sizeStorageInBytes(0), m_countReference(1) {}

   
   bool natural_is_shared() const { return m_countReference > 1; }

   
   auto natural_increment_reference_count() { return ++m_countReference; }

   
   auto natural_decrement_reference_count() { return --m_countReference; }

   
   //constexpr static ::memsize natural_offset() { return (offsetof(meta_data, m_endofmetadata) + NATURAL_METADATA_ALIGN - 1) & (~(NATURAL_METADATA_ALIGN - 1)); }

   
   DATA * begin() const { return (DATA *)&(this[1]); }


   DATA * end() const { return (DATA *)(begin() + this->m_countData); }


   static meta_data * meta_data_from_data(const DATA * pdata) { return &((meta_data *) pdata)[-1]; }


};


#pragma pack(pop, meta_data)


template < typename BASE_META_DATA >
class natural_meta_data :
   public BASE_META_DATA
{
public:


   typedef typename BASE_META_DATA::META                    META;
   typedef typename BASE_META_DATA::DATA                    DATA;

   ::u8            m_data[sizeof(DATA)] = {};


   natural_meta_data() {}

   natural_meta_data(enum_zero_init) :BASE_META_DATA(e_zero_init){}

   
   bool is_set() { return ::is_set(this->m_begin); }

   
   bool is_null() { return !is_null(); }

   
   inline static natural_meta_data < BASE_META_DATA > * from_data(const DATA* pdata)
   {

      return ::is_set(pdata) ?
         (natural_meta_data < BASE_META_DATA >*)BASE_META_DATA::meta_data_from_data(pdata) :
         nullptr;

   }


   inline static DATA* to_data(const natural_meta_data < BASE_META_DATA >* pmetadata)
   {

      return (DATA *) pmetadata->get_data();

   }


   inline natural_meta_data < BASE_META_DATA >* metadata()
   {

      return from_data(this->m_begin);

   }


   inline natural_meta_data < BASE_META_DATA >* metadata() const
   {

      return from_data(this->m_begin);

   }


};


using nullptr_t = std::nullptr_t;


#pragma pack(push,1)


template < typename RANGE_TYPE, typename BASE_META_DATA, typename ALLOCATOR = memory_allocator >
class natural_pointer :
   public RANGE_TYPE
{
public:


   using NATURAL_META_DATA = natural_meta_data < BASE_META_DATA >;
   using META = typename BASE_META_DATA::META;
   using DATA = typename BASE_META_DATA::DATA;
   using iterator = typename RANGE_TYPE::iterator;


   inline natural_pointer(enum_no_initialize) : RANGE_TYPE(e_no_initialize) { }
   inline natural_pointer(enum_zero_initialize) : RANGE_TYPE(e_zero_initialize) { }
   inline natural_pointer(const natural_pointer & natural_pointer)
   {

      natural_pointer.metadata()->natural_increment_reference_count();

      RANGE_TYPE::operator = (natural_pointer);

   }
   inline natural_pointer(natural_pointer && natural_pointer)
   {

      RANGE_TYPE::operator = (::transfer(natural_pointer));

   }
   inline natural_pointer() : natural_pointer(e_no_initialize)
   {

      natural_pointer_default_construct();

   }
   ~natural_pointer()
   {

      destroy();

   }


   void destroy()
   {

      //if (this->is_natural_pointer() && ::is_set(this->begin()))
      if (this->is_string() && ::is_set(this->begin()))
      {

         //if (this->is_string())
         //{

            this->_natural_release(NATURAL_META_DATA::from_data(this->begin()));

//            this->clear_string_flag();

  //       }

         this->m_begin = nullptr;

         this->m_end = nullptr;

      }

   }


   natural_pointer & operator = (const natural_pointer & natural_pointer)
   {

      if (this != &natural_pointer)
      {

         if (natural_pointer.is_string())
         {

            natural_pointer.metadata()->natural_increment_reference_count();

         }

         destroy();

         RANGE_TYPE::operator = (natural_pointer);

      }

      return *this;

   }


   natural_pointer & operator = (natural_pointer && natural_pointer) 
   { 

      if (this->begin() != natural_pointer.begin())
      {

         destroy();

         RANGE_TYPE::operator = (::transfer(natural_pointer));

      }
      
      return *this; 
   
   }


   void natural_pointer_default_construct()
   {

      auto p = this->default_construct_natural_pointer();

      this->m_begin = (iterator) p->begin();

      this->m_end = (iterator) p->end();

      this->set_string_flag();

   }


   inline static NATURAL_META_DATA * default_construct_natural_pointer()
   {

      auto pnil = __nil< natural_meta_data < BASE_META_DATA > >();

      pnil->natural_increment_reference_count();

      return pnil;

   }


   inline static NATURAL_META_DATA * create_meta_data(::memsize sizeStorageInBytes)
   {

      auto pmetadata = (natural_meta_data < BASE_META_DATA > *) ALLOCATOR::allocate(sizeStorageInBytes + sizeof(BASE_META_DATA));

      pmetadata->m_countReference.construct();

      pmetadata->m_sizeStorageInBytes = sizeStorageInBytes;

      return pmetadata;

   }


   inline NATURAL_META_DATA * metadata() const
   {

      return ::is_set(this) && ::is_set(this->m_begin) ? NATURAL_META_DATA::from_data(this->m_begin) : nullptr;

   }


   inline void static natural_destroy(NATURAL_META_DATA * pmetadata)
   {

      ALLOCATOR::free(pmetadata);

   }


   void assign_natural_pointer(const natural_pointer& pointer)
   {

      assign_natural_meta_data(NATURAL_META_DATA::from_data(pointer.m_begin));

   }


   void create_assign_natural_meta_data(NATURAL_META_DATA * p)
   {

      p->natural_increment_reference_count();

      this->m_begin = (iterator) p->begin();

      this->m_end = (iterator) p->end();
      
      this->set_string_flag();

   }


   void assign_natural_meta_data(natural_meta_data < BASE_META_DATA > * pNew)
   {

      auto pOld = NATURAL_META_DATA::from_data(this->m_begin);

      if (pOld != pNew)
      {

         pNew->natural_increment_reference_count();

         this->m_begin = (iterator)pNew->begin();

         this->m_end = (iterator)pNew->end();

         this->set_string_flag();

         natural_release(pOld);

      }

   }


   void natural_release()
   {

      DATA * pdataOld = nullptr;
      
      if (this->is_string())
      {

         pdataOld = (DATA *)this->m_begin;

      }

      auto p = default_construct_natural_pointer();

      this->m_begin = (iterator)p->begin();

      this->m_end = (iterator)p->end();

      this->set_string_flag();

      if (::is_set(pdataOld))
      {

         natural_release(pdataOld);

      }

   }


   static void natural_release(DATA * pdata)
   {

      natural_release(NATURAL_META_DATA::from_data(pdata));

   }

   static void natural_release(natural_meta_data < BASE_META_DATA > * pmetadata)
   {

      if (::is_null(pmetadata))
      {

         return;

      }

      _natural_release(pmetadata);

   }


   static void _natural_release(natural_meta_data < BASE_META_DATA > * pmetadata)
   {

      if (pmetadata->natural_decrement_reference_count() == 0)
      {

         natural_destroy(pmetadata);

      }

   }


};


#pragma pack(pop)



