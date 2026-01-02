// From sequence.h by camilo on 2025-11-14 07:30 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/geometry2d/angle.h"


template<prototype_floating FLOATING_TYPE>
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

   template<prototype_number FLOATING1>
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


   sequence_type< FLOATING, 3 > euler_angles() const
   {
      auto q = this->normalized();
      return {q._pitch(), q._yaw(), q._roll()};
   }


   quaternion_type & set_euler_angles(const sequence_type <FLOATING, 3 > eulerAngles)
   {
      
      auto c = (eulerAngles * (FLOATING)(0.5)).cos();

      auto s = (eulerAngles * (FLOATING)(0.5)).sin();

      this->w = c.x * c.y * c.z + s.x * s.y * s.z;
      this->x = s.x * c.y * c.z - c.x * s.y * s.z;
      this->y = c.x * s.y * c.z + s.x * c.y * s.z;
      this->z = c.x * c.y * s.z - s.x * s.y * c.z;

      return *this;

   }


   	
   constexpr FLOATING dotted(const quaternion_type &q) const
   {
      
      return this->w * q.w + this->x * q.x + this->y * q.y + this->z * q.z;

   }


   constexpr FLOATING squared_modulus() const
   {
      
      return this->dotted(*this);

   }

   FLOATING modulus() const 
   { 
      
      return ::std::sqrt(this->squared_modulus()); 
   
   }


   quaternion_type normalized() const
   {
      
      auto modulus = this->modulus();
      
      if (modulus <= (FLOATING)0) // Problem
         return {(FLOATING)1, (FLOATING)0, (FLOATING)0, (FLOATING)0};

      auto inversedModulus = (FLOATING)1 / modulus;
      
      return {this->w * inversedModulus, this->x * inversedModulus, this->y * inversedModulus,
              this->z * inversedModulus};

   }


   quaternion_type crossed(const quaternion_type &q2) const
   {
      const auto &q1 = *this;
      return {
         q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z, q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
         q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z, q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x};
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


   //inline quaternion_type normalized() const
   //{

   //   FLOATING len = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

   //   // Avoid division by zero
   //   if (len == (FLOATING)0)
   //   {
   //      
   //      return {(FLOATING)1, (FLOATING)0, (FLOATING)0, (FLOATING)0}; // identity rotation

   //   }

   //   FLOATING inv = (FLOATING)1 / len;

   //   return {this->w * inv, this->x * inv, this->y * inv, this->z * inv};

   //}


   inline quaternion_type & normalize()
   {

      return *this = this->normalized();

   }


   //// this implementation assumes normalized quaternion
   //// converts to Euler angles in 3-2-1 sequence
   //EulerAngles ToEulerAngles(Quaternion q)
   //{
   //   EulerAngles angles;

   //   // roll (x-axis rotation)
   //   double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
   //   double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
   //   angles.roll = std::atan2(sinr_cosp, cosr_cosp);

   //   // pitch (y-axis rotation)
   //   double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
   //   double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
   //   angles.pitch = 2 * std::atan2(sinp, cosp) - M_PI / 2;

   //   // yaw (z-axis rotation)
   //   double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
   //   double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
   //   angles.yaw = std::atan2(siny_cosp, cosy_cosp);

   //   return angles;
   //}



   quaternion_type &set_yaw_and_pitch(const angle_type<FLOATING> &yaw, const angle_type<FLOATING> &pitch)
   {

      auto cosp = (pitch * (FLOATING)0.5).cos();
      auto sinp = (pitch * (FLOATING)0.5).sin();
      auto cosy = (yaw * (FLOATING)0.5).cos();
      auto siny = (yaw * (FLOATING)0.5).sin();

      this->w = cosp * cosy;
      this->x = sinp * cosy;
      this->y = cosp * siny;
      this->z = - sinp * siny;

      return *this;

   }


   // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
   quaternion_type &set_yaw__pitch_and_roll(const angle_type<FLOATING> &yaw, const angle_type<FLOATING> &pitch,
                                            const angle_type<FLOATING> &roll)
   {

   // Abbreviations for the various angular functions

      FLOATING half_yaw = yaw.m_fAngle * FLOATING(0.5);
      FLOATING half_pitch = pitch.m_fAngle * FLOATING(0.5);
      FLOATING half_roll = roll.m_fAngle * FLOATING(0.5);


   double cr = cos(half_roll);
      double sr = sin(half_roll);
   double cp = cos(half_pitch);
   double sp = sin(half_pitch);
   double cy = cos(half_yaw);
   double sy = sin(half_yaw);

   auto & q = *this;
   q.w = cr * cp * cy + sr * sp * sy;
   q.x = sr * cp * cy - cr * sp * sy;
   q.y = cr * sp * cy + sr * cp * sy;
   q.z = cr * cp * sy - sr * sp * cy;

   return q;

}


angle_type < FLOATING > _roll() const
{
   auto const y = (FLOATING)(2) * (this->x * this->y + this->w * this->z);
   auto const x = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;

   //if (all(equal(vec<2, T, Q>(x, y), vec<2, T, Q>(0), epsilon<T>()))) // avoid atan2(0,0) - handle singularity - Matiis
   if (::std::abs(x) < std::numeric_limits<FLOATING>::epsilon() &&
       ::std::abs(y) < std::numeric_limits<FLOATING>::epsilon())
      return ::radians((FLOATING) 0);

   return ::geometry::atan2(y, x);
}

   constexpr angle_type<FLOATING> roll() const 
   { return this->normalized()._roll(); 
   }
//
//template<typename T, qualifier Q>
//GLM_FUNC_QUALIFIER T pitch(qua<T, Q> const &q)
//{
//   // return T(atan(T(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
//   T const y = static_cast<T>(2) * (q.y * q.z + q.w * q.x);
//   T const x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
//
//   if (all(equal(vec<2, T, Q>(x, y), vec<2, T, Q>(0), epsilon<T>()))) // avoid atan2(0,0) - handle singularity - Matiis
//      return static_cast<T>(static_cast<T>(2) * atan(q.x, q.w));
//
//   return static_cast<T>(atan(y, x));
//}
   constexpr angle_type < FLOATING > _pitch() const
   {

      auto const y = (FLOATING)(2) * (this->y * this->z + this->w * this->x);
      auto const x = this->w * this->w - this->x * this->x 
         - this->y * this->y + this->z * this->z;

      if (::std::abs(x) < std::numeric_limits<FLOATING>::epsilon() &&
          ::std::abs(y) < std::numeric_limits<FLOATING>::epsilon())
         //all(equal(vec<2, T, Q>(x, y), vec<2, T, Q>(0),
           //         ()))) // avoid atan2(0,0) - handle singularity - Matiis
         return (FLOATING)(2) * ::geometry::atan2(this->x, this->w);

      return ::geometry::atan2(y, x);


      //auto &q = *this;
      //FLOATING a = (FLOATING)2 * (q.w * q.y - q.x * q.z);
      ////FLOATING sinp = std::sqrt((FLOATING)1 + a);
      ////FLOATING cosp = std::sqrt((FLOATING)1 - a);
      ////return ::radians((FLOATING)2 * std::atan2(sinp, cosp) - (FLOATING)π / (FLOATING)2);


      //return ::geometry::asin(a);

      //FLOATING sinp = (FLOATING)2 * (this->w * this->x - this->y * this->z);
      //
      //sinp = ::geometry::clamp(sinp, (FLOATING)-1, (FLOATING)1);

      //return ::geometry::asin(sinp);

   }


   constexpr angle_type<FLOATING> pitch() const 
   {
      
      return this->normalized()._pitch(); 
   
   }


   constexpr angle_type<FLOATING> _yaw() const
   {

      //// yaw (rotation around Y axis)
      //auto q = *this;

      ////   //   // yaw (z-axis rotation)
      //auto siny_cosp = (FLOATING)2 * (q.w * q.z + q.x * q.y);
      //auto cosy_cosp = (FLOATING)1 - (FLOATING)2 * (q.y * q.y + q.z * q.z);
      //////   angles.yaw = std::atan2(siny_cosp, cosy_cosp);

      ////
      //////auto siny_cosp = (FLOATING)2 * (this->w * this->y - this->z * this->x);
      //////
      //////auto cosy_cosp = (FLOATING)1 - (FLOATING)2 * (this->x * this->x + this->y * this->y);
      ////
      //auto yaw = ::geometry::atan2(siny_cosp, cosy_cosp);

      ////FLOATING sinr_cosy = (FLOATING)2 * (q.w * q.x + q.y * q.z);
      ////FLOATING cosr_cosy = (FLOATING)1 - (FLOATING)2 * (q.x * q.x + q.y * q.y);
      //////   angles.roll = std::atan2(sinr_cosp, cosr_cosp);
      ////auto yaw = ::geometry::atan2(sinr_cosy, cosr_cosy);

      return ::geometry::asin(
            (FLOATING)(-2) * (this->x * this->z - this->w * this->y));

   }


   constexpr angle_type<FLOATING> yaw() const
   {

      return this->normalized()._yaw();

   }


   quaternion_type & offset_yaw_and_pitch_with_constraints(
      const ::angle_type<FLOATING> & angleΔYaw,
      const ::angle_type<FLOATING> & angleΔPitch,
      const ::angle_type<FLOATING> & angleMinimumPitch,
      const ::angle_type<FLOATING> & angleMaximumPitch
   ) 
   {

      this->normalize();

      auto eulerAngles = this->euler_angles();

      eulerAngles.x += angleΔPitch.m_fAngle;

      eulerAngles.y += angleΔYaw.m_fAngle;

      eulerAngles.x = ::geometry::clamp(eulerAngles.x, angleMinimumPitch.m_fAngle, angleMaximumPitch.m_fAngle);

      this->set_euler_angles(eulerAngles);

      return *this;

   }


   constexpr sequence_type < FLOATING, 3 > front() const
   {
      
      sequence_type<FLOATING, 3> front;
      
      front.x = (FLOATING)2 * (this->x * this->z + this->w * this->y);
      front.y = (FLOATING)2 * (this->y * this->z - this->w * this->x);
      front.z = (FLOATING)1 - (FLOATING)2 * (this->x * this->x + this->y * this->y);

      front.normalize();
      
      return front;

   }

};


using float_quaternion = quaternion_type<float>;
using double_quaternion = quaternion_type<double>;




