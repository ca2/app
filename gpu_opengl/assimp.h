#pragma once


#if !defined(__APPLE__) && !defined(WINDOWS)


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


namespace assimp
{


   bool load_obj(const void * data, memsize size, array<unsigned short> & indexes, array<::glm::vec3> & vertexes, array<::glm::vec2> & uvs, array<::glm::vec3> & normals);


} // namespace assimp



#endif







