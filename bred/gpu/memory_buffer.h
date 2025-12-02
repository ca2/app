// From gpu_vulkan/memory_buffer.h by
// camilo on 2025-07-01 12:37 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/poolable.h"


namespace gpu
{

   
   class frame_storage;


   class CLASS_DECL_BRED memory_buffer :
      virtual public ::poolable < memory_buffer >
   {
   public:


      enum enum_type
      {

         e_type_none,
         e_type_vertex_buffer,
         e_type_index_buffer,
         e_type_constant_buffer,
         e_type_shared_dynamic_vertex_buffer,

      };


      enum_type m_etype;
      
      ::gpu::model_buffer* m_pmodelbuffer;
      ::gpu::context* m_pcontext;
      ::gpu::frame_storage* m_pframestorage;
      //VkDeviceMemory m_vkdevicememory;
      //VkBuffer m_vkbuffer;
      memsize m_size;
      void* m_pMap;
      bool m_bDynamic;

      int m_iBufferOffset;
      int m_iSizeMapped;


      memory_buffer();
      ~memory_buffer();


      virtual void initialize_memory_buffer_with_context(::gpu::context* pcontext, memsize size, ::gpu::memory_buffer::enum_type etype);

      virtual void initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, memsize size, ::gpu::memory_buffer::enum_type etype, bool bDynamic = false);

      virtual void static_initialize_memory_buffer_with_context(::gpu::context* pcontext, const void * data, memsize size, ::gpu::memory_buffer::enum_type etype);

      virtual void static_initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, const void * data, memsize size, ::gpu::memory_buffer::enum_type etype);

      virtual void on_initialize_memory_buffer(const void * dataStatic = nullptr, memsize sizeStatic = 0);

      virtual void on_set_memory_buffer(const void* dataStatic = nullptr, memsize sizeStatic = 0);

      virtual void _on_set_memory_buffer(const void* dataStatic = nullptr, memsize sizeStatic = 0);

      virtual bool is_initialized() const;


      virtual memsize total_size_in_bytes() const;
      virtual memsize type_size() const;


      virtual void assign(const void* pData, memsize size);
      virtual void assign(const ::block& block);
      virtual void _assign(const void* pData, memsize size);
      virtual void _assign(const ::block& block);

      virtual void* map();
      virtual void* map(memsize start, memsize count);
      virtual void unmap();
      virtual void* _map(memsize start, memsize count);
      virtual void _unmap();
      //virtual void* __map(memsize start, memsize count);
      //virtual void __unmap();


      virtual void bind();
      virtual void unbind();


      virtual void _complete_map_allocate(::gpu::memory_buffer* pmemorybufferSource, ::gpu::frame_storage * pgpuframestorage, int size);


   };


   template < typename MAPPER, typename TYPE >
   class memory_map
   {
   public:

      MAPPER* m_pMapper;
      TYPE* m_p;

      memory_map(MAPPER* pmapper, TYPE* p) :
         m_pMapper(pmapper)
      {

         m_p = (TYPE*)m_pMapper->map(0, -1);

      }

      ~memory_map()
      {

         m_pMapper->unmap();

      }

      operator TYPE* ()
      {

         return m_p;

      }


      TYPE* operator -> ()
      {

         return m_p;

      }

      template < prototype_integral INTEGRAL >
      TYPE& operator[](INTEGRAL i)
      {

         return m_p[i];

      }

      void assign(const ::block& block)
      {

         memcpy(m_p, block.data(), block.size());

      }


   };


} // namespace gpu


