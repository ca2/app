// Created by camilo on 2025-12-04 22:45 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "bred/graphics3d/transform.h"


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



