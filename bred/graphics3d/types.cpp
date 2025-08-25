// Created by camilo on 2025-08-23 21:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "types.h"


BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_uv)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
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


namespace graphics3d
{


   glm::mat4 transform::getMatrix() const
   {
      // 1) Translation
      glm::mat4 T = glm::translate(glm::mat4(1.0f), m_vec3Translation);
      // 2) Rotation
      glm::mat4 R = glm::rotate(glm::mat4(1.0f), m_vec3Rotation.x, glm::vec3(1, 0, 0));
      R = glm::rotate(R, m_vec3Rotation.y, glm::vec3(0, 1, 0));
      R = glm::rotate(R, m_vec3Rotation.z, glm::vec3(0, 0, 1));
      // 3) Scale
      glm::mat4 S = glm::scale(glm::mat4(1.0f), m_vec3Scale);

      // Compose: T * R * S
      return T * R * S;
   }
   glm::mat3 transform::normalMatrix() const
   {
      // Build RS (ignore m_vec3Translation)
      glm::mat4 R = glm::rotate(glm::mat4(1.0f), m_vec3Rotation.y, glm::vec3(0, 1, 0));
      R = glm::rotate(R, m_vec3Rotation.x, glm::vec3(1, 0, 0));
      R = glm::rotate(R, m_vec3Rotation.z, glm::vec3(0, 0, 1));

      glm::mat4 RS = R * glm::scale(glm::mat4(1.0f), m_vec3Scale);

      // Normal matrix = inverse-transpose of the 3x3 upper-left
      return glm::transpose(glm::inverse(glm::mat3(RS)));
   }


} // namespace graphics3d
