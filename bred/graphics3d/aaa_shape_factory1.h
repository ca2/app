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
      virtual shape_data create_cube(float size);

      // Generate a plane (XZ plane by default) with position, texture coords, and normals
      virtual shape_data create_plane(float width, float depth);

      // Generate a wall (XY plane by default) with position, texture coords, and normals
      virtual shape_data create_wall(float width, float height);

      virtual shape_data create_sphere(float radius, unsigned int sectorCount, unsigned int stackCount);

      // Generate a ray with a specified length
      virtual shape_data create_ray(float length);
      

   };


} // namespace graphics3d


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::shape_factory::Vertex)




