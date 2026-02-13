// From github:/tristancalderbank/OpenGL-PBR-Renderer/cube.cpp by
// camilo on 2025-09-27 ~02:27 <3ThomasBorregaardSorensen!!
#include "../framework.h"
//#include "cube.h"
//#include "_gpu_opengl.h"
//#include <glad/glad.h>
//
// namespace gpu_opengl
// {
//
//    cube::cube()
//    {
//    }
//
//    cube::~cube()
//    {
//    }
//
//
//
//    void cube::draw(::gpu::command_buffer *pcommandbuffer)
//    {
//
//       if (m_uVAO == 0)
//       {
//
//          throw ::exception(error_wrong_state);
//
//       }
//       if (m_modeldata.m_vertexes.is_empty())
//       {
//
//          throw ::exception(error_wrong_state);
//
//       }
//       // draw mesh
//       glBindVertexArray(m_uVAO);
//       ::opengl::check_error("");
//       glDrawArrays(GL_TRIANGLES, 0, m_modeldata.m_vertexes.size());
//       ::opengl::check_error("");
//       glBindVertexArray(0);
//       ::opengl::check_error("");
//
//    }
//
//    void cube::initialize_gpu_cube(::gpu::context* pgpucontext)
//    {
//
//       ::gpu::cube::initialize_gpu_cube(pgpucontext);
//       // create our data structures
//       glGenVertexArrays(1, &m_uVAO);
//       ::opengl::check_error("");
//       glGenBuffers(1, &m_uVBO);
//       ::opengl::check_error("");
//
//       glBindVertexArray(m_uVAO); // use this VAO for subsequent calls
//       ::opengl::check_error("");
//
//       int iSizeItem = sizeof(m_modeldata.m_vertexes[0]);
//       int iSize = m_modeldata.m_vertexes.size();
//
//       glBindBuffer(GL_ARRAY_BUFFER, m_uVBO); // use this VBO for subsequent calls
//       ::opengl::check_error("");
//       glBufferData(GL_ARRAY_BUFFER, iSize * sizeof(float) * 3, m_modeldata.m_vertexes.data(),
//                    GL_STATIC_DRAW); // copy over the vertex data
//       ::opengl::check_error("");
//
//       // setup the locations of vertex data
//       // positions
//       glEnableVertexAttribArray(0);
//       ::opengl::check_error("");
//       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//       ::opengl::check_error("");
//
//       glBindVertexArray(0);
//       ::opengl::check_error("");
//
//    }
//
//
// } // namespace gpu_opengl
//
//
