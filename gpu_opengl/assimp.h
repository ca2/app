#pragma once


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


namespace assimp
{


   bool load_obj(const void * data, memsize size, array<unsigned short> & indices, array<::glm::vec3> & vertices, array<::glm::vec2> & uvs, array<::glm::vec3> & normals);


} // namespace assimp



