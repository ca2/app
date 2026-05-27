// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 20:12 <3ThomasBorregaardSorensen!!
#pragma once 


#include "bred/graphics3d/types.h"


namespace graphics3d
{


	enum CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};


	struct camera_t
	{

		//void calculateMouseOffset(::f32 xoffset, ::f32 yoffset);
//private:
		floating_matrix4		m_matrixProjection{ 1.f };
		floating_matrix4		m_matrixImpact{ 1.f };
		floating_matrix4		m_matrixAntImpact{ 1.f };

		//::f32 m_LastX; // Last mouse x position
		//::f32 m_LastY; // Last mouse y position
		::f32				m_MouseSensitivity = 0.1f; // Sensitivity factor for mouse input
		// Deadzone
		::f32				m_MouseDeadZone;
		// Inertia
		floating_sequence3				m_sequence3Velocity;
		// Camera attributes
		floating_sequence3				m_locationPosition;
		floating_sequence3				m_sequence3Front{ 0.0f, 0.0f, -1.0f };  // Camera direction (forward vector)
		floating_sequence3				m_sequence3Up{ 0.0f, 1.0f, 0.0f };     // Up vector
		floating_sequence3				m_sequence3Right{ 1.0f, 0.0f, 0.0f };   // Right vector (cross product)
		floating_sequence3				m_sequence3WorldUp;

		// Euler angles
		::f32				m_angleYaw = 0.0f;
		::f32				m_anglePitch = glm::radians(-90.0f);

		// Camera options
		::f32				m_fZoom;
		::f32				m_fMovementSpeed;  // Added movement speed

		::block as_block()
		{

			return as_memory_block(*this);

		}

	};

	
	class CLASS_DECL_BRED camera :
		virtual public camera_t,
		virtual public ::particle
	{
	public:


		::pointer < ::graphics3d::engine > m_pengine;
		camera();
		~camera() override;
		//camera(const ::floating_sequence3 & position, ::f32 yaw, ::f32 pitch);
		//camera(const ::floating_sequence3 & position, floating_sequence3 to, floating_sequence3 from);

		virtual void initialize_camera(const ::floating_sequence3 & position, ::f32 yaw, ::f32 pitch);
		virtual void initialize_camera(floating_sequence3 target, floating_sequence3 camera);

		void setOrthographicProjection(::f32 left, ::f32 right, ::f32 top, ::f32 bottom, ::f32 near, ::f32 far);
		void setViewDirection(const ::floating_sequence3 & position, const ::floating_sequence3 & direction, const ::floating_sequence3 & up = floating_sequence3{ 0.f, -1.f, 0.f });
		void setViewTarget(const ::floating_sequence3 & position, const ::floating_sequence3 & target, const ::floating_sequence3 & up = floating_sequence3{ 0.f, -1.f, 0.f });

//		void setViewYXZ(const ::floating_sequence3 & position, floating_sequence3 rotation);

		virtual void setPerspectiveProjection(::f32 fovy, ::f32 aspect, ::f32 near, ::f32 far);
		const floating_matrix4& getProjection() const { return m_matrixProjection; }
		const floating_matrix4& getView() const { return m_matrixImpact; }
		const floating_matrix4& getInverseView() const { return m_matrixAntImpact; }

		// Get zoom (field of view)
		::f32 GetZoom() const;
		// Get the view matrix
		floating_matrix4 GetViewMatrix() const;


		floating_sequence3 GetPosition() const;
		// Set movement speed
		void SetMovementSpeed(::f32 speed);
		// new shit
		void ProcessMouseMovement(::f32 xoffset, ::f32 yoffset, bool constrainPitch = true);
		void ProcessKeyboardInput(::i32 direction, ::f32 deltaTime);

		//floating_sequence3 pole_up();
		// Update camera vectors
		void UpdateCameraVectors();


		// from MyPlace2025@V0idsEmbrace@Twitch
      void UpdateIdleMovement(::f32 deltaTime); // Add this line
      //// Get zoom (field of view)
      //::f32 GetZoom() const;
      //// Set movement speed
      //void SetMovementSpeed(::f32 speed);
      void Jump(::f32 jumpHeight);
      void TeleportDownward(::f32 distance); // Moves the camera down
      void TeleportInDirection(::i32 direction);
		// END from MyPlace2025@V0idsEmbrace@Twitch


	};


} // namespace graphics3d



