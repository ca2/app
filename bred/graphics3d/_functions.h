// Created by camilo on 2024-11-117 19:02 <3ThomasBorregaardSørensen!!
#pragma once


namespace geometry3d
{

   /// from glm lookAtRH
   template < primitive_floating FLOATING >
   matrix_type<FLOATING, 4> lookAt(const sequence_type<FLOATING, 3> &eye, const sequence_type<FLOATING, 3> &center,
                                   const sequence_type<FLOATING, 3> &worldUp)
   {


      const auto front = (center - eye).normalized();
      const auto right = f.crossed(worldUp).normalized();
      const auto up = right.crossed(front);

      matrix_type<FLOATING, 4> Result((FLOATING)1);

      Result[0][0] = s.x;
      Result[1][0] = s.y;
      Result[2][0] = s.z;
      Result[0][1] = u.x;
      Result[1][1] = u.y;
      Result[2][1] = u.z;
      Result[0][2] = -f.x;
      Result[1][2] = -f.y;
      Result[2][2] = -f.z;
      Result[3][0] = -dot(s, eye);
      Result[3][1] = -dot(u, eye);
      Result[3][2] = dot(f, eye);

      return Result;

   }

} // namespace geometry3d




