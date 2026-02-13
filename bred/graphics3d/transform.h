//
// From point_light_render_system by camilo on 2025-08-19 <3ThomasBorregaardSorensen!!
// Created by camilo on 2025-12-04 22:45 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/graphics3d/rotation.h"


namespace graphics3d
{


   class CLASS_DECL_BRED transform
   {
   public:

      //::graphics3d::transform() = default;
      floating_sequence3 m_sequence3Position{};
      // floating_quaternion m_quaternionRotation{};
      ::graphics3d::floating_rotation m_rotation;
      // float_angle m_anglePitch;
      floating_sequence3 m_sequence3Scale{1.f};


      floating_matrix4 getMatrix() const;


      floating_matrix3 normalMatrix() const;
   };


} // namespace graphics3d



