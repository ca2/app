// Created by camilo on 2025-11-19 15:42 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/graphics3d/_functions.h"


namespace graphics3d
{


   template<primitive_floating FLOATING>
   class rotation_type
   {
   public:

      ::angle_type<FLOATING> m_angleYaw;
      ::angle_type<FLOATING> m_anglePitch;


      rotation_type() {}
      rotation_type(const ::angle_type<FLOATING> &angleYaw, const ::angle_type<FLOATING> &anglePitch) :
          m_angleYaw(angleYaw), m_anglePitch(anglePitch)
      {
      }

      rotation_type(const rotation_type &rotation) : rotation_type(rotation.m_angleYaw, rotation.m_anglePitch) {}


      rotation_type &offset(const ::angle_type<FLOATING> &angleΔYaw, const ::angle_type<FLOATING> &angleΔPitch,
                            const ::angle_type<FLOATING> &angleMinimumPitch,
                            const ::angle_type<FLOATING> &angleMaximumPitch)
      {

         m_angleYaw += angleΔYaw;
         m_anglePitch += angleΔPitch;

         m_angleYaw.m_fAngle = std::fmod(m_angleYaw, (FLOATING)_2πl);
         m_anglePitch = ::geometry::clamp(m_anglePitch, angleMinimumPitch, angleMaximumPitch);

      }


      rotation_type &operator=(const rotation_type &rotation)
      {

         m_angleYaw = rotation.m_angleYaw;
         m_anglePitch = rotation.m_anglePitch;

         return *this;
      }


      matrix_type<FLOATING, 4> as_rotation_matrix() const
      {

         return ::graphics3d ::rotation_from_yaw_and_pitch(m_angleYaw, m_anglePitch);

      }


      rotation_type &set(const ::angle_type<FLOATING> &angleYaw, const ::angle_type<FLOATING> &anglePitch)
      {

         m_angleYaw = angleYaw;
         m_anglePitch = anglePitch;

         return *this;
      }


   };


   using float_rotation = rotation_type<float>;
   using double_rotation = rotation_type<double>;

   using floating_rotation = float_rotation;


} // namespace graphics3d
 



