// Recreated by
// camilo on 2025-12-22 19:09 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "bred/gpu/model_data.h"

namespace gpu
{


   model_data_base::model_data_base() {}

   model_data_base::~model_data_base() {}

   ::block model_data_base::vertex_data() { throw interface_only(); }
   ::block model_data_base::index_data() { throw interface_only(); }


   void model_data_base::set_vertex_count(int iVertexCount)
   { throw interface_only(); 

         }
   void model_data_base::set_index_count(int iIndexCount)
   {

      throw interface_only(); 

    }





} // namespace gpu


