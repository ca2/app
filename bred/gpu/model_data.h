// From gpu/model_buffer.h by
// camilo on 2025-10-18 01:28 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/properties.h"
//#include "bred/gpu/context.h"
//#include "bred/gpu/context_object.h"
//#include "bred/gpu/frame.h"
//#include "bred/gpu/memory_buffer.h"
//#include "bred/graphics3d/types.h"
//// #include "bred/graphics3d/model.h"
//// #include "bred/graphics3d/model.h"
//#include "bred/graphics3d/renderable.h"


namespace gpu
{

   struct dummy_t
   {
   };

   class CLASS_DECL_BRED model_data_base :
      virtual public ::particle
   {
   protected:

            ::gpu::property *m_ppropertyProperties;


      int m_iVertexCount;
      int m_iVertexByteSize;
      int m_iVertexTypeSize;
      int m_iIndexCount;
      int m_iIndexByteSize;
      int m_iIndexTypeSize;
      bool m_bDummy = false;


      virtual void _set_vertex_array_base(const void * p);
      virtual void _set_index_array_base(const void *p);

   public:



      model_data_base();
      model_data_base(dummy_t, int iVertexCount, int iIndexCount = -1)
      {

         m_bDummy = true;
         m_iIndexTypeSize = -1;
         m_iIndexByteSize = -1;
         m_iVertexTypeSize = -1;
         m_iVertexByteSize = -1;
         m_iVertexCount = iVertexCount;
         m_iIndexCount = iIndexCount;

      }
      ~model_data_base() override;


      virtual ::block vertex_data();
      virtual ::block index_data() ;
      virtual const ::block vertex_data() const;
      virtual const ::block  index_data() const;
      virtual ::platform::type vertex_type() const;
      virtual ::platform::type index_type() const;

      template < typename VERTEX>
      void set_vertexes(const ::array_base<VERTEX> & vertexes)
      {
         if (typeid(VERTEX) != this->vertex_type())
         {

            throw ::exception(error_wrong_state);

         }
         _set_vertex_array_base(&vertexes);

      }

            template<typename INDEX>
      void set_indexes(const ::array_base<INDEX> &indexes)
      {
         if (typeid(INDEX) != this->index_type())
         {

            throw ::exception(error_wrong_state);
         }
         _set_index_array_base(&indexes);
      }
      template<typename INDEX>
      void set_index_type_and_count(int iIndexCount)
      {
         if (typeid(INDEX) != this->index_type())
         {

            throw ::exception(error_wrong_state);
         }
         set_index_count(iIndexCount);
      }
      int index_count() const { return m_iIndexCount; }
      int vertex_count() const { return m_iVertexCount; }
      int index_type_size() const { return m_iIndexTypeSize; }
      int vertex_type_size() const { return m_iVertexTypeSize; }
      int index_bytes() const { return m_iIndexByteSize; }
      int vertex_bytes() const { return m_iVertexByteSize; };
      ::gpu::property *properties() const { return (::gpu::property *) m_ppropertyProperties; };
      virtual void set_vertex_count(int iVertexCount);
      virtual void set_index_count(int iIndexCount);
      virtual bool is_empty() const;
      virtual bool has_data() const;
      bool is_dummy() const
      { return m_bDummy;

      }
   };



   template<typename VERTEX, typename INDEX>
   class model_data :
      virtual public model_data_base
   {
   protected:
      ::array_base<VERTEX> m_vertexes;
      ::array_base<INDEX> m_indexes;

      void update()
      {

         update_vertexes();
         update_indexes();

      }

      void update_vertexes()
      {
         this->m_ppropertyProperties = ::gpu_properties<VERTEX>();
         this->m_iVertexCount = m_vertexes.get_size();
         this->m_iVertexTypeSize = sizeof(VERTEX);
         this->m_iVertexByteSize = this->m_iVertexTypeSize * this->m_iIndexCount;
      }
      void update_indexes()
      {
         this->m_iIndexCount = m_indexes.get_size();
         this->m_iIndexTypeSize = sizeof(INDEX);
         this->m_iIndexByteSize = this->m_iIndexTypeSize * this->m_iIndexCount;
      }

      void _set_vertex_array_base( const void *p) override
      {
         auto pvertexes = (const ::array_base<VERTEX> *)p;
         m_vertexes = *pvertexes;
         update_vertexes();
      }

      void _set_index_array_base(const void *p) override
      {
         auto pindexes = (const ::array_base<INDEX> *)p;
         m_indexes = *pindexes;
         update_indexes();
      }

   public:




      model_data() {}
      model_data(int iVertexCount, int iIndexCount)
      { m_vertexes.set_size(iVertexCount);
         m_indexes.set_size(iIndexCount);
         update();

      }
      model_data(const model_data & data) :
         m_vertexes(data.m_vertexes),
         m_indexes(data.m_indexes) { update();
      }
      model_data(model_data &&data) : 
         m_vertexes(::transfer(data.m_vertexes)),
         m_indexes(::transfer(data.m_indexes)) {
         update();
      }

      bool is_empty() const
      {

         return m_vertexes.is_empty() && m_indexes.is_empty();

      }

      bool has_data() const
      {

         return !this->is_empty();

      }


      ::platform::type vertex_type() const override
      {

         return ::type<VERTEX>();

      }


      ::platform::type index_type() const override
      
      { return ::type<INDEX>(); }




      void set_vertex_count(int iVertexCount) override
      { m_vertexes.set_size(iVertexCount);
         update_vertexes();
      }
      void set_index_count(int iIndexCount) override
      { m_indexes.set_size(iIndexCount);
         update_indexes();


      }


      void set_vertexes(const ::array_base<VERTEX> &vertexes)
      {
         ::gpu::model_data_base::set_vertexes<VERTEX>(vertexes);
      }

      
      void set_indexes(const ::array_base<INDEX> & indexes)
      {

         ::gpu::model_data_base::set_indexes<INDEX>(indexes);

      }
      //::pointer <::graphics3d::model> create_model(
      //   ::gpu::renderer* prenderer)
      //{

      //   auto pmodel = prenderer->øcreate < ::graphics3d::model >();

      //   pmodel->initialize_model(
      //      prenderer,
      //      m_vertexes.as_block(),
      //      m_indexes.as_block());

      //   auto pgpucontext = prenderer->m_pgpucontext;

      //   auto pinputlayout = pgpucontext->input_layout(::gpu_properties< VERTEX >());

      //   pmodel->defer_set_input_layout(pinputlayout);

      //   return pmodel;

      //}


      model_data & operator=(const model_data & modeldata)
      {

         if (this != &modeldata)
         {

            this->m_vertexes = modeldata.m_vertexes;
            this->m_indexes = modeldata.m_indexes;

         }

         return *this;

      }


      model_data &operator=(model_data &&modeldata)
      {

         if (this != &modeldata)
         {

            this->m_vertexes = ::transfer(modeldata.m_vertexes);
            this->m_indexes = ::transfer(modeldata.m_indexes);
         }

         return *this;
      }


      virtual ::block vertex_data()
      {

         return {m_vertexes.data(), m_vertexes.get_size_in_bytes()};

            }
      virtual ::block index_data()
      {

         return {m_indexes.data(), m_indexes.get_size_in_bytes()};

      }

      virtual const ::block vertex_data()const { return {m_vertexes.data(), m_vertexes.get_size_in_bytes()}; }
      virtual const ::block index_data() const { return {m_indexes.data(), m_indexes.get_size_in_bytes()}; }

      const ::array_base<VERTEX> & vertexes() const
      {

         return m_vertexes;

      }
      const ::array_base<INDEX> &indexes() const { return m_indexes; }

   };


} // namespace gpu



