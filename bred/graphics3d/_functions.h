// Created by camilo on 2024-11-117 19:02 <3ThomasBorregaardSørensen!!
#pragma once


namespace graphics3d
{

   /// from glm lookAtRH
   template < primitive_floating FLOATING >
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


} // namespace graphics3d




