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
		glm::mat4		m_matrixProjection{ 1.f };
		glm::mat4		m_matrixImpact{ 1.f };
		glm::mat4		m_matrixAntImpact{ 1.f };

		//float m_LastX; // Last mouse x position
		//float m_LastY; // Last mouse y position
		float				m_MouseSensitivity = 0.1f; // Sensitivity factor for mouse input
		// Deadzone
		float				m_MouseDeadZone;
		// Inertia
		glm::vec3				m_poleVelocity;
		// Camera attributes
		glm::vec3				m_locationPosition;
		glm::vec3				m_poleFront{ 0.0f, 0.0f, -1.0f };  // Camera direction (forward vector)
		glm::vec3				m_poleUp{ 0.0f, 1.0f, 0.0f };     // Up vector
		glm::vec3				m_poleRight{ 1.0f, 0.0f, 0.0f };   // Right vector (cross product)
		glm::vec3				m_poleWorldUp;

		// Euler angles
		float				m_fYaw = 0.0f;
		float				m_fPitch = glm::radians(-90.0f);

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
		camera() {};
		//camera(glm::vec3 position, float yaw, float pitch);
		//camera(glm::vec3 position, glm::vec3 to, glm::vec3 from);

		virtual void initialize_camera(glm::vec3 position, float yaw, float pitch);
		virtual void initialize_camera(glm::vec3 target, glm::vec3 camera);

		void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
		void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });
		void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{ 0.f, -1.f, 0.f });

//		void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

		virtual void setPerspectiveProjection(float fovy, float aspect, float near, float far);
		const glm::mat4& getProjection() const { return m_matrixProjection; }
		const glm::mat4& getView() const { return m_matrixImpact; }
		const glm::mat4& getInverseView() const { return m_matrixAntImpact; }

		// Get zoom (field of view)
		float GetZoom() const;
		// Get the view matrix
		glm::mat4 GetViewMatrix() const;


		glm::vec3 GetPosition() const;
		// Set movement speed
		void SetMovementSpeed(float speed);
		// new shit
		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void ProcessKeyboardInput(int direction, float deltaTime);

		//glm::vec3 pole_up();
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



