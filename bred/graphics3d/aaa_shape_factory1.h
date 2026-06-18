// Changed on by camilo on 2025-12-04 21:07 <3ThomasBorregaardSorensen!!s
#pragma once


#include "acme/prototype/mathematics/mathematics.h"
#include "bred/gpu/model_buffer.h"
#include "bred/graphics3d/model.h"


namespace graphics3d
{



   class shape_factory :
      virtual public ::particle
   {
   public:


      struct Vertex
      {
         ::floating_sequence3 m_position;
         ::floating_sequence3 m_color;
         ::floating_sequence3 m_uv;
      };

      using shape_data = ::gpu::model_data<Vertex>;

      // Generate a graphics3d with position, color, texture coordinates, and normals
      virtual shape_data create_cube(::f32 size);

      // Generate a plane (XZ plane by default) with position, texture coords, and normals
      virtual shape_data create_plane(::f32 width, ::f32 depth);

      // Generate a wall (XY plane by default) with position, texture coords, and normals
      virtual shape_data create_wall(::f32 width, ::f32 height);

      virtual shape_data create_sphere(::f32 radius, ::u32 sectorCount, ::u32 stackCount);

      // Generate a ray with a specified length
      virtual shape_data create_ray(::f32 length);
      

   };


} // namespace graphics3d


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::shape_factory::Vertex)




