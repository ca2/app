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
      floating_matrix4 T = floating_matrix4(1.0f);
      T.translate(m_sequence3Position);


      // 2) Rotation
      floating_matrix4 R = floating_matrix4(1.0f);
      R.rotate(radians(m_sequence3Rotation.x), floating_sequence3(1, 0, 0));
      R.rotate(radians(m_sequence3Rotation.y), floating_sequence3(0, 1, 0));
      R.rotate(radians(m_sequence3Rotation.z), floating_sequence3(0, 0, 1));


      // 3) Scale
      floating_matrix4 S = floating_matrix4(1.0f);
      S.scale(m_sequence3Scale);


      // Compose: T * R * S
      return T * R * S;

   }


   floating_matrix3 transform::normalMatrix() const
   {
      
      // Build RS (ignore m_sequence3Position)
      floating_matrix4 R = floating_matrix4(1.0f);
      R.rotate(radians(m_sequence3Rotation.y), floating_sequence3(0, 1, 0));
      R.rotate(radians(m_sequence3Rotation.x), floating_sequence3(1, 0, 0));
      R.rotate(radians(m_sequence3Rotation.z), floating_sequence3(0, 0, 1));

      floating_matrix4 RS = floating_matrix4(1.0f);
      RS.scale(m_sequence3Scale);

      // Normal matrix = inverse-transpose of the 3x3 upper-left
      return floating_matrix3(RS).inversed().transposed();

   }


} // namespace graphics3d
