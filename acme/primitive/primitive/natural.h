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


   typedef meta_data < TYPE_DATA >     META;
   typedef TYPE_DATA                   DATA;


   interlocked_count                   m_countReference;
   memsize_storage                     m_memsize;
   memsize_storage                     m_datasize;
   DATA                                m_endofmetadata[1024];


   meta_data(): m_memsize(0),m_countReference (1) {}
   meta_data(enum_zero_init) : m_memsize(0), m_countReference(1), m_endofmetadata{} {}

   bool natural_is_shared() const { return m_countReference > 1; }

   auto natural_add_ref() { return ++m_countReference; }

   auto natural_dec_ref() { return --m_countReference; }

   inline static ::memsize natural_offset() { meta_data metadata; return (((byte*)&metadata.m_endofmetadata - (byte*)&metadata) + NATURAL_METADATA_ALIGN - 1) & (~(NATURAL_METADATA_ALIGN - 1)); }

   DATA * get_data() const { return (DATA *)(((byte *)this) + natural_offset()); }

   bool contains_data(const DATA* p) const { return (byte*)p >= (byte*)this && (byte *) p < ((byte*)get_data()) + m_memsize; }

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

   bool is_set() { return ::is_set(this->m_pdata); }


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

      return from_data(this->m_pdata);

   }


   inline natural_meta_data < BASE_META_DATA >* metadata() const
   {

      return from_data(this->m_pdata);

   }



};

using nullptr_t = std::nullptr_t;

#pragma pack(push,1)

template < typename BASE_META_DATA, typename ALLOCATOR = memory_allocator >
class natural_pointer :
   public ALLOCATOR
{
public:


   typedef natural_meta_data < BASE_META_DATA >       NATURAL_META_DATA;
   typedef typename BASE_META_DATA::META              META;
   typedef typename BASE_META_DATA::DATA              DATA;


   DATA *      m_pdata;


   inline natural_pointer(enum_no_initialize) { }

   inline natural_pointer(nullptr_t) { m_pdata = nullptr; }

   inline natural_pointer()
   {

      natural_pointer_default_construct();

   }

   ~natural_pointer()
   {

      if (::is_set(this->m_pdata))
      {

         this->_natural_release(NATURAL_META_DATA::from_data(this->m_pdata));

      }

   }


   void natural_pointer_default_construct()
   {

      m_pdata = default_construct_natural_pointer();

   }


   inline static DATA * default_construct_natural_pointer()
   {

      auto pnil = __nil< natural_meta_data < BASE_META_DATA > >();

      pnil->natural_add_ref();

      return pnil->get_data();

   }


   inline static auto create_meta_data(::memsize memsize)
   {

      auto pmetadata = (natural_meta_data < BASE_META_DATA > *) ALLOCATOR::allocate(memsize + BASE_META_DATA::natural_offset());

      pmetadata->m_countReference.construct();

      pmetadata->m_memsize = memsize;

      return pmetadata;

   }

   inline natural_meta_data < BASE_META_DATA > * metadata() const
   {

      return NATURAL_META_DATA::from_data(this->m_pdata);

   }


   inline void static natural_destroy(natural_meta_data < BASE_META_DATA >* pmetadata)
   {

      ALLOCATOR::free(pmetadata);

   }


   void assign_natural_pointer(const natural_pointer& pointer)
   {

      assign_natural_meta_data(NATURAL_META_DATA::from_data(pointer.m_pdata));

   }


   void create_assign_natural_meta_data(natural_meta_data < BASE_META_DATA > * pNew)
   {

      pNew->natural_add_ref();

      this->m_pdata = pNew->get_data();

   }


   void assign_natural_meta_data(natural_meta_data < BASE_META_DATA > * pNew)
   {

      auto pOld = NATURAL_META_DATA::from_data(this->m_pdata);

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

         this->m_pdata = pNew->get_data();

         natural_release(pOld);

      }

   }


   void natural_release()
   {

      auto pdata = this->m_pdata;

      m_pdata = default_construct_natural_pointer();

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
























