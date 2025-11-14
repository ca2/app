// Created by camilo on 2025-08-23 21:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "types.h"


BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_uv)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()

BEGIN_GPU_PROPERTIES(::gpu::position3)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
END_GPU_PROPERTIES()

BEGIN_GPU_PROPERTIES(::graphics3d::sequence3_color)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_color)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::graphics3d::Vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq3)
GPU_PROPERTY("normal", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()

BEGIN_GPU_PROPERTIES(::gpu::position2_uv)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()

namespace graphics3d
{


   floating_matrix4 transform::getMatrix() const
   {
      // 1) Translation
      floating_matrix4 T = geometry::translate(floating_matrix4(1.0f), m_vec3Position);
      // 2) Rotation
      floating_matrix4 R = geometry::rotate(floating_matrix4(1.0f), m_vec3Rotation.x, floating_sequence3(1, 0, 0));
      R = geometry::rotate(R, m_vec3Rotation.y, floating_sequence3(0, 1, 0));
      R = geometry::rotate(R, m_vec3Rotation.z, floating_sequence3(0, 0, 1));
      // 3) Scale
      floating_matrix4 S = geometry::scale(floating_matrix4(1.0f), m_vec3Scale);

      // Compose: T * R * S
      return T * R * S;
   }
   floating_matrix3 transform::normalMatrix() const
   {
      // Build RS (ignore m_vec3Position)
      floating_matrix4 R = geometry::rotate(floating_matrix4(1.0f), m_vec3Rotation.y, floating_sequence3(0, 1, 0));
      R = geometry::rotate(R, m_vec3Rotation.x, floating_sequence3(1, 0, 0));
      R = geometry::rotate(R, m_vec3Rotation.z, floating_sequence3(0, 0, 1));

      floating_matrix4 RS = R * geometry::scale(floating_matrix4(1.0f), m_vec3Scale);

      // Normal matrix = inverse-transpose of the 3x3 upper-left
      return geometry::transpose(geometry::inverse(floating_matrix3(RS)));


   }


} // namespace graphics3d
