// From sequence.h by camilo on 2025-11-14 07:30 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/geometry2d/angle.h"


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
      FLOATING cx = std::cos(euler.x * 0.5f);
      FLOATING sx = std::sin(euler.x * 0.5f);

      FLOATING cy = std::cos(euler.y * 0.5f);
      FLOATING sy = std::sin(euler.y * 0.5f);

      FLOATING cz = std::cos(euler.z * 0.5f);
      FLOATING sz = std::sin(euler.z * 0.5f);

      // GLM uses Z * Y * X intrinsic rotation order
      w = cx * cy * cz + sx * sy * sz;
      x = sx * cy * cz - cx * sy * sz;
      y = cx * sy * cz + sx * cy * sz;
      z = cx * cy * sz - sx * sy * cz;
   }


   inline quaternion_type slerp(const quaternion_type &q2, FLOATING t) const
   {
      const auto &q1 = *this;
      // Compute the cosine of the angle
      FLOATING dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

      quaternion_type q2c = q2;

      // If dot < 0, q2 is on the opposite hemisphere -> take the shorter path
      if (dot < (FLOATING)0)
      {
         dot = -dot;
         q2c.w = -q2c.w;
         q2c.x = -q2c.x;
         q2c.y = -q2c.y;
         q2c.z = -q2c.z;
      }

      // If close, fall back to lerp
      const FLOATING EPS = 1e-6f;
      if (dot > (FLOATING)1 - EPS)
      {
         // Linear interpolation + renormalize
         quaternion_type result;
         result.w = q1.w + t * (q2c.w - q1.w);
         result.x = q1.x + t * (q2c.x - q1.x);
         result.y = q1.y + t * (q2c.y - q1.y);
         result.z = q1.z + t * (q2c.z - q1.z);

         // Normalize
         FLOATING invLen =
            (FLOATING)1 / sqrtf(result.w * result.w + result.x * result.x + result.y * result.y + result.z * result.z);
         result.w *= invLen;
         result.x *= invLen;
         result.y *= invLen;
         result.z *= invLen;

         return result;
      }

      // Compute the angle θ
      FLOATING theta = acosf(dot);
      FLOATING sinTheta = sinf(theta);

      FLOATING w1 = sinf(((FLOATING)1 - t) * theta) / sinTheta;
      FLOATING w2 = sinf(t * theta) / sinTheta;

      quaternion_type result;
      result.w = w1 * q1.w + w2 * q2c.w;
      result.x = w1 * q1.x + w2 * q2c.x;
      result.y = w1 * q1.y + w2 * q2c.y;
      result.z = w1 * q1.z + w2 * q2c.z;

      return result;
   }

   inline quaternion_type normalized() const
   {
      FLOATING len = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

      // Avoid division by zero
      if (len == (FLOATING)0)
         return {(FLOATING)1, (FLOATING)0, (FLOATING)0, (FLOATING)0}; // identity rotation

      FLOATING inv = (FLOATING)1 / len;

      return {this->w * inv, this->x * inv, this->y * inv, this->z * inv};
   }


   quaternion_type & set_yaw_and_pitch(const angle_type<FLOATING> &yaw, const angle_type<FLOATING> &pitch)
   {

      // half-angles
      FLOATING hy = yaw * (FLOATING) 0.5;
      FLOATING hp = pitch * (FLOATING) 0.5;

      FLOATING cy = cos(hy);
      FLOATING sy = sin(hy);

      FLOATING cp = cos(hp);
      FLOATING sp = sin(hp);

      // yaw around Y: (cy, 0, sy, 0)
      // pitch around X: (cp, sp, 0, 0)

      auto &  q = *this;

      q.w = cy * cp - sy * sp * (FLOATING)0.0; // simplified, no roll term
      q.x = sp * cy;
      q.y = sy * cp;
      q.z = sy * sp * (FLOATING)0.0; // zero because no roll

      // Full combined formula:
      q.w = cy * cp;
      q.x = cp * sp;
      q.y = sy * cp;
      q.z = sy * sp;

   }


   constexpr angle_type < FLOATING > pitch() const
   {

      // pitch (rotation around X axis)

      auto sinp = (FLOATING) 2 * (this->w * this->x + this->y * this->z);
      
      auto pitch = ::geometry::asin(::geometry::clamp(sinp, (FLOATING) - 1.0, (FLOATING) 1.0));

      return pitch;

   }


   constexpr angle_type<FLOATING> yaw() const
   {

      // yaw (rotation around Y axis)
      
      auto siny_cosp = (FLOATING)2 * (this->w * this->y - this->z * this->x);
      
      auto cosy_cosp = (FLOATING)1 - (FLOATING)2 * (this->x * this->x + this->y * this->y);
      
      auto yaw = ::geometry::atan2(siny_cosp, cosy_cosp);

      return yaw;

   }


   quaternion_type & offset_yaw_and_pitch_with_constraints(
      const ::angle_type<FLOATING> & angleΔYaw,
      const ::angle_type<FLOATING> & angleΔPitch,
      const ::angle_type<FLOATING> & angleMinimumPitch,
      const ::angle_type<FLOATING> & angleMaximumPitch
   ) 
   {

      auto angleYaw = this->yaw();

      auto anglePitch = this->pitch();

      angleYaw += angleΔYaw;

      anglePitch += angleΔPitch;

      anglePitch = ::geometry::clamp(anglePitch, angleMinimumPitch, angleMinimumPitch);

      set_yaw_and_pitch(angleYaw, anglePitch);

      return *this;

   }


   constexpr sequence_type < FLOATING, 3 > front() const
   {
      
      sequence_type<FLOATING, 3> front;
      
      front.x = (FLOATING)2 * (this->x * this->z + this->w * this->y);
      front.y = (FLOATING)2 * (this->y * this->z - this->w * this->x);
      front.z = (FLOATING)1 - (FLOATING)2 * (this->x * this->x + this->y * this->y);
      
      return front;

   }

};


using float_quaternion = quaternion_type<float>;
using double_quaternion = quaternion_type<double>;




