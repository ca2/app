#pragma once


#if !defined(__APPLE__) && !defined(WINDOWS)






namespace assimp
{


   bool load_obj(const void * data, memsize size, array<unsigned short> & indexes, array<::floating_sequence3> & vertexes, array<::floating_sequence2> & uvs, array<::floating_sequence3> & normals);


} // namespace assimp



#endif







