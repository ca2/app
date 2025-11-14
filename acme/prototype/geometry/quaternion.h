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


   inline quaternion_type slerp(const quaternion_type &q2, float t) const
   {
      const auto &q1 = *this;
      // Compute the cosine of the angle
      float dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

      quaternion_type q2c = q2;

      // If dot < 0, q2 is on the opposite hemisphere -> take the shorter path
      if (dot < 0.0f)
      {
         dot = -dot;
         q2c.w = -q2c.w;
         q2c.x = -q2c.x;
         q2c.y = -q2c.y;
         q2c.z = -q2c.z;
      }

      // If close, fall back to lerp
      const float EPS = 1e-6f;
      if (dot > 1.0f - EPS)
      {
         // Linear interpolation + renormalize
         quaternion_type result;
         result.w = q1.w + t * (q2c.w - q1.w);
         result.x = q1.x + t * (q2c.x - q1.x);
         result.y = q1.y + t * (q2c.y - q1.y);
         result.z = q1.z + t * (q2c.z - q1.z);

         // Normalize
         float invLen =
            1.0f / sqrtf(result.w * result.w + result.x * result.x + result.y * result.y + result.z * result.z);
         result.w *= invLen;
         result.x *= invLen;
         result.y *= invLen;
         result.z *= invLen;

         return result;
      }

      // Compute the angle θ
      float theta = acosf(dot);
      float sinTheta = sinf(theta);

      float w1 = sinf((1.0f - t) * theta) / sinTheta;
      float w2 = sinf(t * theta) / sinTheta;

      quaternion_type result;
      result.w = w1 * q1.w + w2 * q2c.w;
      result.x = w1 * q1.x + w2 * q2c.x;
      result.y = w1 * q1.y + w2 * q2c.y;
      result.z = w1 * q1.z + w2 * q2c.z;

      return result;
   }

};




using float_quaternion = quaternion_type<float>;
using double_quaternion = quaternion_type<double>;

