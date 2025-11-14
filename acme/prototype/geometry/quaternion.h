// From sequence.h by camilo on 2025-11-14 07:30 <3ThomasBorregaardSørensen!!
#pragma once



template<primitive_floating FLOATING_TYPE>
struct quaternion_type
{


   using FLOATING = FLOATING_TYPE;
   static constexpr int DIMENSION = 4;


   union
   {
      struct
      {
         FLOATING w, x, y, z;
      };
      FLOATING m_coordinatea[4];
   };

   quaternion_type() : w(1), x(0), y(0), z(0) {}
   quaternion_type(FLOATING _w, FLOATING _x, FLOATING _y, FLOATING _z) : w(_w), x(_x), y(_y), z(_z) {}

   template<primitive_number FLOATING1>
   quaternion_type(const FLOATING1 *p) : // expects p to point to an array of at least 4 elements
       w((FLOATING)p[0]), x((FLOATING)p[1]), y((FLOATING)p[2]), z((FLOATING)p[3])
   {
   }

   // Construct quaternion from Euler XYZ rotation
   // rotation = (pitch, yaw, roll) in radians
   quaternion_type(const ::sequence_type<FLOATING, 3> &euler)
   {
      float cx = std::cos(euler.x * 0.5f);
      float sx = std::sin(euler.x * 0.5f);

      float cy = std::cos(euler.y * 0.5f);
      float sy = std::sin(euler.y * 0.5f);

      float cz = std::cos(euler.z * 0.5f);
      float sz = std::sin(euler.z * 0.5f);

      // GLM uses Z * Y * X intrinsic rotation order
      w = cx * cy * cz + sx * sy * sz;
      x = sx * cy * cz - cx * sy * sz;
      y = cx * sy * cz + sx * cy * sz;
      z = cx * cy * sz - sx * sy * cz;
   }


};




using float_quaternion = quaternion_type<float>;
using double_quaternion = quaternion_type<double>;

