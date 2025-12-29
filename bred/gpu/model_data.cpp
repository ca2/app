// Recreated by
// camilo on 2025-12-22 19:09 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "bred/gpu/model_data.h"

namespace gpu
{


   model_data_base::model_data_base() {}

   model_data_base::~model_data_base() {}


   ::gpu::property * model_data_base::gpu_properties() const
   {

      return (::gpu::property *) m_ppropertyProperties;

   }

   ::block model_data_base::vertex_data()
   {
      throw interface_only();
      return {};
   }
   ::block model_data_base::index_data()
   {
      throw interface_only();
      return {};
   }

   const ::block model_data_base::vertex_data() const
   {
      throw interface_only();
      return {};
   
   }
   const ::block model_data_base::index_data() const
   {
      throw interface_only();
      return {};
   }
   bool model_data_base::is_empty() const
   {

      if (m_bDummy)
      {

         return m_iVertexCount > 0;

      }
      else
      {

         return vertex_count() > 0;

      }

   }

   void model_data_base::update()
   {


   }

   bool model_data_base::has_data() const
   {

      return !this->is_empty();

   }
   void model_data_base::set_vertex_count(int iVertexCount)
   { throw interface_only(); 

         }
   void model_data_base::set_index_count(int iIndexCount)
   {

      throw interface_only(); 

    }

      void model_data_base::_set_vertex_array_base(const void *p ) {
      
         throw ::interface_only();
      }
   void model_data_base::_set_index_array_base(const void* p) { throw interface_only(); }

   ::platform::type model_data_base::vertex_type() const
   {

      throw ::interface_only();

      return {};

   }

   ::platform::type model_data_base::index_type() const
   {

      throw ::interface_only();

      return {};
   }


} // namespace gpu


