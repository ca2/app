// Changed on by camilo on 2025-12-04 21:07 <3ThomasBorregaardSorensen!!s
#pragma once


#include "bred/gpu/model_buffer.h"
#include "bred/graphics3d/renderable.h"


namespace graphics3d
{



   class CLASS_DECL_BRED shape_factory :
      virtual public ::particle
   {
   public:

      //const virtual inline auto π = ::mathematics::mathematics::πf();

      struct Vertex
      {

         ::floating_sequence3    m_position;
         ::floating_sequence3    m_normal;
         ::floating_sequence2    m_uv;

         /*Vertex() {}

         Vertex(
            const ::floating_sequence3& position,
            const ::floating_sequence3& color,
            const ::floating_sequence3& uv
         ) :
            m_position(position),
            m_color(color),
            m_uv(uv)
         {}*/

      };

      using shape = ::gpu::model_data < Vertex >;
      //struct shape {
      //   ::array<float> vertexes;  // Positions, colors, texture coordinates, and normals
      //   ::array<unsigned int> indexes;
      //};

      shape_factory();
      ~shape_factory() override;

      // Generate a graphics3d with position, color, texture coordinates, and normals
      virtual ::pointer<::graphics3d::renderable> create_cube_001(::gpu::context * pgpucontext, float size);
      virtual ::pointer<::graphics3d::renderable> create_cube_002(::gpu::context *pgpucontext, float size);
      // Generate a plane (XZ plane by default) with position, texture coords, and normals
      virtual ::pointer<::graphics3d::renderable> create_plane(::gpu::context * pgpucontext, float width, float depth);
      // Generate a wall (XY plane by default) with position, texture coords, and normals
      virtual ::pointer<::graphics3d::renderable> create_wall(::gpu::context * pgpucontext, float width, float height);

      virtual ::pointer<::graphics3d::renderable> create_sphere(::gpu::context * pgpucontext, float radius, unsigned int sectorCount,
                                                                      unsigned int stackCount);

      //// Generate a ray with a specified length
      //virtual shape CreateRay(float length);

         virtual ::pointer<::graphics3d::renderable> create_renderable_from_model_data(::gpu::context *pgpucontext,
                                                                            ::gpu::model_data_base *pmodeldata);

      };


} // namespace graphics3d


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::shape_factory::Vertex)




