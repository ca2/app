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

		//void calculateMouseOffset(float xoffset, float yoffset);
//private:
		floating_matrix4		m_matrixProjection{ 1.f };
		floating_matrix4		m_matrixImpact{ 1.f };
		floating_matrix4		m_matrixAntImpact{ 1.f };

		//float m_LastX; // Last mouse x position
		//float m_LastY; // Last mouse y position
		float				m_MouseSensitivity = 0.1f; // Sensitivity factor for mouse input
		// Deadzone
		float				m_MouseDeadZone;
		// Inertia
		floating_sequence3				m_sequence3Velocity;
		// Camera attributes
		floating_sequence3				m_locationPosition;
		floating_sequence3				m_sequence3Front{ 0.0f, 0.0f, -1.0f };  // Camera direction (forward vector)
		floating_sequence3				m_sequence3Up{ 0.0f, 1.0f, 0.0f };     // Up vector
		floating_sequence3				m_sequence3Right{ 1.0f, 0.0f, 0.0f };   // Right vector (cross product)
		floating_sequence3				m_sequence3WorldUp;

		// Euler angles
		float				m_angleYaw = 0.0f;
		float				m_anglePitch = glm::radians(-90.0f);

		// Camera options
		float				m_fZoom;
		float				m_fMovementSpeed;  // Added movement speed

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
		//camera(const ::floating_sequence3 & position, float yaw, float pitch);
		//camera(const ::floating_sequence3 & position, floating_sequence3 to, floating_sequence3 from);

		virtual void initialize_camera(const ::floating_sequence3 & position, float yaw, float pitch);
		virtual void initialize_camera(floating_sequence3 target, floating_sequence3 camera);

		void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
		void setViewDirection(const ::floating_sequence3 & position, const ::floating_sequence3 & direction, const ::floating_sequence3 & up = floating_sequence3{ 0.f, -1.f, 0.f });
		void setViewTarget(const ::floating_sequence3 & position, const ::floating_sequence3 & target, const ::floating_sequence3 & up = floating_sequence3{ 0.f, -1.f, 0.f });

//		void setViewYXZ(const ::floating_sequence3 & position, floating_sequence3 rotation);

		virtual void setPerspectiveProjection(float fovy, float aspect, float near, float far);
		const floating_matrix4& getProjection() const { return m_matrixProjection; }
		const floating_matrix4& getView() const { return m_matrixImpact; }
		const floating_matrix4& getInverseView() const { return m_matrixAntImpact; }

		// Get zoom (field of view)
		float GetZoom() const;
		// Get the view matrix
		floating_matrix4 GetViewMatrix() const;


		floating_sequence3 GetPosition() const;
		// Set movement speed
		void SetMovementSpeed(float speed);
		// new shit
		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void ProcessKeyboardInput(int direction, float deltaTime);

		//floating_sequence3 pole_up();
		// Update camera vectors
		void UpdateCameraVectors();


		// from MyPlace2025@V0idsEmbrace@Twitch
      void UpdateIdleMovement(float deltaTime); // Add this line
      //// Get zoom (field of view)
      //float GetZoom() const;
      //// Set movement speed
      //void SetMovementSpeed(float speed);
      void Jump(float jumpHeight);
      void TeleportDownward(float distance); // Moves the camera down
      void TeleportInDirection(int direction);
		// END from MyPlace2025@V0idsEmbrace@Twitch


	};


} // namespace graphics3d



