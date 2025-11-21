// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#pragma once 


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
      //      void calculateMouseOffset(float xoffset, float yoffset);
      // private:
      floating_matrix4 m_matrixProjection{1.f};
      floating_matrix4 m_matrixImpact{1.f};
      floating_matrix4 m_matrixInversedImpact{1.f};

      // float m_LastX; // Last mouse x position
      // float m_LastY; // Last mouse y position
      float m_angleCursorPixel = 0.1f_degree; // Sensitivity factor for mouse input
      // Deadzone
      float m_MouseDeadZone;
      // Inertia
      floating_sequence3 m_sequence3Velocity;
      // Camera attributes
      floating_sequence3 m_locationPosition;
      floating_sequence3 m_sequence3Front{0.0f, 0.0f, -1.0f}; // Camera direction (forward vector)
      floating_sequence3 m_sequence3Up{0.0f, 1.0f, 0.0f}; // Up vector
      floating_sequence3 m_sequence3Right{1.0f, 0.0f, 0.0f}; // Right vector (cross product)
      floating_sequence3 m_sequence3WorldUp;

      // Euler angles
      //float_angle m_angleYaw = 0.0_degree;
      //float_angle m_anglePitch = -90.0_degree;

      // Camera options
      //float m_fZoom;
      float                m_fMovementSpeed; // Added movement speed
      
      float_angle          m_angleFovY;
      float                m_fAspectRatio;
      float                m_fNearZ;
      float                m_fFarZ;



		camera();
		~camera() override;


      inline const floating_sequence3 & position() const { return m_sequence3Position; }
      inline const floating_rotation & rotation() const { return m_rotation; }
//      inline const floating_angle & pitch() const { return m_anglePitch; }


      inline const floating_sequence3 & front() const { return m_sequence3Front; }
      inline const floating_sequence3 & right() const { return m_sequence3Right; }
      inline const floating_sequence3 & up() const { return m_sequence3Up; }
      inline const floating_sequence3 & world_up() const { return m_sequence3WorldUp; }

      //inline float_angle yaw() const { return m_quaternionRotation.yaw(); }
      //inline float_angle pitch() const { return m_quaternionRotation.pitch(); }


      inline const floating_matrix4 & projection() const { return m_matrixProjection; }
      inline const floating_matrix4 & impact() const { return m_matrixImpact; }
      inline const floating_matrix4 & inversed_impact() const { return m_matrixInversedImpact; }


      virtual void update_vectors();

      virtual void update();


      virtual void calculate_impact(::floating_matrix4 &matrixImpact);

      virtual void calculate_projection(::floating_matrix4 &matrixProjection);


	};


} // namespace graphics3d



