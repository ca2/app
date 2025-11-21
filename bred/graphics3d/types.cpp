// Created by camilo on 2025-08-23 21:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "types.h"
#include "bred/graphics3d/_functions.h"

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
      auto T = m_sequence3Position.as_translation_matrix();


      // 2) Rotation
      auto R = m_rotation.as_rotation_matrix();


      // 3) Scale
      auto S = m_sequence3Scale.as_scaling_matrix();


      // Compose: T * R * S
      return T * R * S;

   }


   floating_matrix3 transform::normalMatrix() const
   {
      
      // Build RS (ignore m_sequence3Position)
      auto R = m_rotation.as_rotation_matrix();

      auto S = m_sequence3Scale.as_scaling_matrix();
      
      auto RS = R * S;

      // Normal matrix = inverse-transpose of the 3x3 upper-left
      return RS.inversed().transposed();

   }


} // namespace graphics3d
