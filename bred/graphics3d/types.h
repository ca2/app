// From landen by camilo on 2025-05-18 03:39
#pragma once


#include "bred/gpu/properties.h"
#include "bred/gpu/types.h"


//
// From point_light_render_system by camilo on 2025-08-19 <3ThomasBorregaardSorensen!!
//
//#pragma once


#include "bred/graphics3d/rotation.h"


//
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
// 	floating_sequence3 translation{};
// 	floating_sequence3 scale{ 1.f };
// 	floating_sequence3 rotation{};
//
// 	floating_matrix4 floating_matrix4() const;
// 	floating_matrix3 normalMatrix() const;
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


      ::floating_sequence2 m_position;
   };


   struct sequence3_color
   {

      floating_sequence3 position; // x, y, z
      floating_sequence4 color; // r, g, b, a
   };


   struct sequence2_color
   {

      floating_sequence2 position; // x, y
      floating_sequence4 color; // r, g, b, a
   };


   struct sequence2_uv
   {

      floating_sequence2 position{};
      floating_sequence2 uv{};
   };


   struct Vertex
   {

      floating_sequence3 position{};
      floating_sequence3 color{};
      floating_sequence3 normal{};
      floating_sequence2 uv{};

      // static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
      // static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

      bool operator==(const Vertex &other) const
      {
         return position == other.position && normal == other.normal && uv == other.uv;
      }
   };


   struct point_light_t
   {
      inline static const int MAX_LIGHTS = 10;
      floating_sequence4 position{}; // ignore w
      floating_sequence4 color{}; // w is intensity
   };


} // namespace graphics3d


template < >
inline ::hash32 as_hash32<::graphics3d::Vertex>(const ::graphics3d::Vertex& vertex)
{

   hash32 seed{};

   ::gpu::hash_combine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);

   return seed;

}




DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence2_uv)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence3_color)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::sequence2_color)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::Vertex)




