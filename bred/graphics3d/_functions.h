// Created by camilo on 2024-11-117 19:02 <3ThomasBorregaardSørensen!!
#pragma once


namespace graphics3d
{


   /// from glm lookAtRH
   template < prototype_floating FLOATING >
   matrix_type<FLOATING, 4> lookAt(const sequence_type<FLOATING, 3> &eye, const sequence_type<FLOATING, 3> &center,
                                   const sequence_type<FLOATING, 3> &worldUp)
   {


      const auto front = (center - eye).normalized();
      const auto right = front.crossed(worldUp).normalized();
      const auto up = right.crossed(front);

      matrix_type<FLOATING, 4> Result((FLOATING)1);

      Result[0][0] = right.x;
      Result[1][0] = right.y;
      Result[2][0] = right.z;
      Result[0][1] = up.x;
      Result[1][1] = up.y;
      Result[2][1] = up.z;
      Result[0][2] = -front.x;
      Result[1][2] = -front.y;
      Result[2][2] = -front.z;
      Result[3][0] = -right.dotted(eye);
      Result[3][1] = -up.dotted(eye);
      Result[3][2] = front.dotted(eye);

      return Result;

   }


   inline floating_matrix4 rotation_from_yaw_and_pitch(const float_angle & angleYaw, const float_angle & anglePitch)
   {
      // === 1. direction vectors ===

      float cy = angleYaw.cos();
      float sy = angleYaw.sin();
      float cp = anglePitch.cos();
      float sp = anglePitch.sin();

      // front vector
      floating_sequence3 front(cp * cy, sp, cp * sy);
      front.normalize();

      // world up
      floating_sequence3 worldUp(0.f, 1.f, 0.f);

      // right and up
      floating_sequence3 right = front.crossed(worldUp).normalized();
      floating_sequence3 up = right.crossed(front).normalized();

      // === 2. build 4×4 rotation matrix ===
      // Column-major (OpenGL convention)

      floating_matrix4 m;

      m[0][0] = right.x;
      m[1][0] = right.y;
      m[2][0] = right.z;
      m[3][0] = 0.f;

      m[0][1] = up.x;
      m[1][1] = up.y;
      m[2][1] = up.z;
      m[3][1] = 0.f;

      m[0][2] = -front.x; // note the minus (OpenGL forward = −Z)
      m[1][2] = -front.y;
      m[2][2] = -front.z;
      m[3][2] = 0.f;

      m[0][3] = 0.f;
      m[1][3] = 0.f;
      m[2][3] = 0.f;
      m[3][3] = 1.f;

      return m;
   }


} // namespace graphics3d




