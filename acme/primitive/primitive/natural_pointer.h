#pragma once


#include "acme/memory/memory_allocator.h"
#include "acme/primitive/primitive/interlocked_count.h"


template < typename NATURAL_DATA >
NATURAL_DATA* __nil() { return nullptr; }


#define NATURAL_METADATA_ALIGN 32


template < typename TYPE_DATA >
class meta_data
{
public:


   using META = meta_data < TYPE_DATA >;

   using DATA = non_const < TYPE_DATA >;


   interlocked_count                   m_countReference;
   memsize_storage                     m_memsize;
   memsize_storage                     m_datasize;
   DATA                                m_endofmetadata[1024];


   meta_data(): m_memsize(0),m_countReference (1) {}
   meta_data(enum_zero_init) : m_memsize(0), m_countReference(1), m_endofmetadata{} {}

   bool natural_is_shared() const { return m_countReference > 1; }

   auto natural_add_ref() { return ++m_countReference; }

   auto natural_dec_ref() { return --m_countReference; }

   consteval static ::memsize natural_offset() { return (offsetof(meta_data, m_endofmetadata) + NATURAL_METADATA_ALIGN - 1) & (~(NATURAL_METADATA_ALIGN - 1)); }

   DATA * begin() const { return (DATA *)(((byte *)this) + natural_offset()); }
   DATA * end() const { return (DATA *)(begin() + this->m_datasize); }


};


template < typename BASE_META_DATA >
class natural_meta_data :
   public BASE_META_DATA
{
public:


   typedef typename BASE_META_DATA::META                    META;
   typedef typename BASE_META_DATA::DATA                    DATA;


   natural_meta_data() {}

   natural_meta_data(enum_zero_init) :BASE_META_DATA(e_zero_init){}

   bool is_set() { return ::is_set(this->m_begin); }


   bool is_null() { return !is_null(); }


   inline static natural_meta_data < BASE_META_DATA > * from_data(const DATA* pdata)
   {

      return (natural_meta_data < BASE_META_DATA >*)(void*)((byte*)(void*)pdata - BASE_META_DATA::natural_offset());

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
   using META = BASE_META_DATA::META;
   using DATA = BASE_META_DATA::DATA;
   using iterator = RANGE_TYPE::iterator;


   inline natural_pointer(enum_no_initialize) : RANGE_TYPE(e_no_initialize) { }
   inline natural_pointer(const natural_pointer & natural_pointer)
   {

      natural_pointer.metadata()->natural_add_ref();

      RANGE_TYPE::operator = (natural_pointer);

   }
   inline natural_pointer(natural_pointer && natural_pointer)
   {

      RANGE_TYPE::operator = (::move(natural_pointer));

   }
   inline natural_pointer() : natural_pointer(e_no_initialize)
   {

      natural_pointer_default_construct();

   }
   ~natural_pointer()
   {

      defer_destroy();

   }


   void defer_destroy()
   {

      if (::is_set(this->begin()))
      {

         this->_natural_release(NATURAL_META_DATA::from_data(this->begin()));

      }

   }


   natural_pointer & operator = (const natural_pointer & natural_pointer)
   {

      if (this != &natural_pointer)
      {
      
         natural_pointer.metadata()->natural_add_ref();

         defer_destroy();

         RANGE_TYPE::operator = (natural_pointer);

      }

      return *this;

   }


   natural_pointer & operator = (natural_pointer && natural_pointer) 
   { 

      if (this != &natural_pointer)
      {

         defer_destroy();

         RANGE_TYPE::operator = (::move(natural_pointer));

      }
      
      return *this; 
   
   }


   void natural_pointer_default_construct()
   {

      auto p = default_construct_natural_pointer();

      this->m_begin = (iterator) p->begin();

      this->m_end = (iterator) p->end();

   }


   inline static NATURAL_META_DATA * default_construct_natural_pointer()
   {

      auto pnil = __nil< natural_meta_data < BASE_META_DATA > >();

      pnil->natural_add_ref();

      return pnil;

   }


   inline static NATURAL_META_DATA * create_meta_data(::memsize memsize)
   {

      auto pmetadata = (natural_meta_data < BASE_META_DATA > *) ALLOCATOR::allocate(memsize + BASE_META_DATA::natural_offset());

      pmetadata->m_countReference.construct();

      pmetadata->m_memsize = memsize;

      return pmetadata;

   }


   inline NATURAL_META_DATA * metadata() const
   {

      return NATURAL_META_DATA::from_data(this->m_begin);

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

      p->natural_add_ref();

      this->m_begin = (iterator) p->begin();

      this->m_end = (iterator) p->end();

   }


   void assign_natural_meta_data(natural_meta_data < BASE_META_DATA > * pNew)
   {

      auto pOld = NATURAL_META_DATA::from_data(this->m_begin);

      if (pOld != pNew)
      {

         if (::is_set(pNew))
         {

            auto i = pNew->natural_add_ref();

            if (i <= 0)
            {

               //output_debug_string("");

            }

         }

         this->m_begin = (iterator)pNew->begin();

         this->m_end = (iterator)pNew->end();

         natural_release(pOld);

      }

   }


   void natural_release()
   {

      DATA * pdata = (DATA *) this->m_begin;

      auto p = default_construct_natural_pointer();

      this->m_begin = (iterator)p->begin();

      this->m_end = (iterator)p->end();

      natural_release(pdata);

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

      if (pmetadata->natural_dec_ref() == 0)
      {

         natural_destroy(pmetadata);

      }

   }


};


#pragma pack(pop)



