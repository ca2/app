// From gpu/model_buffer.h by
// camilo on 2025-10-18 01:28 <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/prototype/prototype/poolable.h"
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


   template<typename VERTEX>
   class model_data
   {
   public:

      ::array_base<VERTEX> m_vertexes;
      ::array_base<unsigned int> m_indexes;


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
   };


} // namespace gpu



