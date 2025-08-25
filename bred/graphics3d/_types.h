//
// From point_light_render_system by camilo on 2025-08-19 <3ThomasBorregaardSorensen!!
//
#pragma once


// #include <glm/glm.hpp>
//

// namespace graphics3d
// {

//
//    struct point_light_component
//    {
//
//        float lightIntensity = 1.0f;
//
//    };
//
// struct CLASS_DECL_BRED ::graphics3d::transform
// {
// 	//::graphics3d::transform() = default;
// 	glm::vec3 translation{};
// 	glm::vec3 scale{ 1.f };
// 	glm::vec3 rotation{};
//
// 	glm::mat4 mat4() const;
// 	glm::mat3 normalMatrix() const;
//
// };


namespace graphics3d
{

   /** @brief State of mouse/touch input */
   struct mouse_state
   {


      struct
      {


         bool left = false;
         bool right = false;
         bool middle = false;


      } m_buttons;


      ::glm::vec2 m_position;


   };


   // struct CLASS_DECL_BRED ::graphics3d::transform
   // {
   //
   // 	glm::vec3 translation{};
   // 	glm::vec3 scale{ 1.f, 1.f, 1.f };
   // 	glm::vec3 rotation{};
   //
   // 	// Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
   // 	// Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
   //
   // 	//glm::mat4 mat4();
   // 	//glm::mat4 normalMatrix();
   //
   // };
   struct CLASS_DECL_BRED transform
   {
      //::graphics3d::transform() = default;
      glm::vec3 m_vec3Translation{};
      glm::vec3 m_vec3Scale{1.f};
      glm::vec3 m_vec3Rotation{};


      glm::mat4 getMatrix() const;


      glm::mat3 normalMatrix() const;

   };


   struct sequence3_color
   {

      glm::vec3 position; // x, y, z
      glm::vec4 color; // r, g, b, a

   };


   struct sequence2_color
   {

      glm::vec2 position; // x, y
      glm::vec4 color; // r, g, b, a

   };


   struct sequence2_uv
   {

      glm::vec2 position{};
      glm::vec2 uv{};

   };


   struct Vertex
   {

      glm::vec3 position{};
      glm::vec3 color{};
      glm::vec3 normal{};
      glm::vec2 uv{};

      //static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
      //static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

      bool operator==(const Vertex &other) const
      {
         return position == other.position && normal == other.normal && uv == other.uv;
      }

   };


   struct point_light_t
   {
      inline static const int MAX_LIGHTS = 10;
      glm::vec4 position{}; // ignore w
      glm::vec4 color{}; // w is intensity
   };


} // namespace graphics3d
