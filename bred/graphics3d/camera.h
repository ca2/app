// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#pragma once 


#include "acme/prototype/geometry2d/angle.h"
#include "bred/graphics3d/types.h"


namespace graphics3d
{


	class CLASS_DECL_BRED camera :
		virtual public ::particle
	{
	public:


		::pointer < ::graphics3d::engine > m_pengine;
      ::floating_sequence3 m_sequence3Position;
      //::floating_quaternion m_quaternionRotation;
      floating_rotation m_rotation;
      //      void calculateMouseOffset(::f32 xoffset, ::f32 yoffset);
      // private:
      floating_matrix4 m_matrixProjection{1.f};
      floating_matrix4 m_matrixImpact{1.f};
      floating_matrix4 m_matrixInversedImpact{1.f};

      // ::f32 m_LastX; // Last mouse x position
      // ::f32 m_LastY; // Last mouse y position
      ::f32 m_angleCursorPixel = 0.1_f_degree; // Sensitivity factor for mouse input
      // Deadzone
      ::f32 m_MouseDeadZone;
      // Inertia
      floating_sequence3 m_sequence3Velocity;
      // Camera attributes
      //floating_sequence3 m_locationPosition;
      floating_sequence3 m_sequence3Front{0.0f, 0.0f, -1.0f}; // Camera direction (forward vector)
      floating_sequence3 m_sequence3Up{0.0f, 1.0f, 0.0f}; // Up vector
      floating_sequence3 m_sequence3Right{1.0f, 0.0f, 0.0f}; // Right vector (cross product)
      floating_sequence3 m_sequence3WorldUp;

      // Euler angles
      //f32_angle m_angleYaw = 0.0_degree;
      //f32_angle m_anglePitch = -90.0_degree;

      // Camera options
      //::f32 m_fZoom;
      ::f32                m_fMovementSpeed; // Added movement speed
      
      f32_angle          m_angleFovY;
      ::f32                m_fAspectRatio;
      ::f32                m_fNearZ;
      ::f32                m_fFarZ;



		camera();
		~camera() override;


      virtual void initialize_camera(const ::floating_sequence3 &position,
                                     const ::graphics3d::floating_rotation &rotation = {-90_degree, 0_degree},
                                     const floating_angle &zoom = 60_f_degree);
      


      inline const floating_sequence3 & position() const { return m_sequence3Position; }
      inline const floating_rotation & rotation() const { return m_rotation; }
//      inline const floating_angle & pitch() const { return m_anglePitch; }


      inline const floating_sequence3 & front() const { return m_sequence3Front; }
      inline const floating_sequence3 & right() const { return m_sequence3Right; }
      inline const floating_sequence3 & up() const { return m_sequence3Up; }
      inline const floating_sequence3 & world_up() const { return m_sequence3WorldUp; }

      //inline f32_angle yaw() const { return m_quaternionRotation.yaw(); }
      //inline f32_angle pitch() const { return m_quaternionRotation.pitch(); }


      inline const floating_matrix4 & projection() const { return m_matrixProjection; }
      inline const floating_matrix4 & impact() const { return m_matrixImpact; }
      inline const floating_matrix4 & inversed_impact() const { return m_matrixInversedImpact; }


      virtual void update_vectors();

      virtual void update();


      virtual void calculate_impact(::floating_matrix4 &matrixImpact);

      virtual void calculate_projection(::floating_matrix4 &matrixProjection);


	};


} // namespace graphics3d



