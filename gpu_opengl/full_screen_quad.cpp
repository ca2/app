// From github:/tristancalderbank/OpenGL-PBR-Renderer/full_screen_quad.cpp by
// camilo on 2025-09-27 01:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "full_screen_quad.h"
//#include "gpu_opengl/_gpu_opengl.h"
//#include <glad/glad.h>
//
//#include "bred/gpu/command_buffer.h"
//
//
//namespace gpu_opengl
//{
//
//
//
//   full_screen_quad::full_screen_quad()
//   {
//
//      m_uVAO = 0;
//      m_uVBO = 0;
//
//   }
//
//   
//   full_screen_quad::~full_screen_quad()
//   {
//
//   }
//
//
//   void full_screen_quad::bind(::gpu::command_buffer *pgpucommandbuffer)
//   {
//
//      if (m_uVAO == 0)
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      glDisable(GL_DEPTH_TEST);
//      ::opengl::check_error("");
//      glBindVertexArray(m_uVAO);
//      ::opengl::check_error("");
//
//   }
//
//
//   void full_screen_quad::draw(::gpu::command_buffer * pgpucommandbuffer) 
//   {
//
//      glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM_TRIANGLES);
//      ::opengl::check_error("");
//
//   }
//
//   
//   void full_screen_quad::unbind(::gpu::command_buffer * pcommandbuffer)
//   {
//
//      glEnable(GL_DEPTH_TEST);
//      ::opengl::check_error("");
//      glBindVertexArray(0);
//      ::opengl::check_error("");
//
//   }
//
//
//   void full_screen_quad::initialize_full_screen_quad(::gpu::context * pgpucontext) 
//   {
//
//      ::gpu::full_screen_quad::initialize_full_screen_quad(pgpucontext);
//
//      // create our data structures
//      glGenVertexArrays(1, &m_uVAO);
//      ::opengl::check_error("");
//      glGenBuffers(1, &m_uVBO);
//      ::opengl::check_error("");
//
//      glBindVertexArray(m_uVAO); // use this VAO for subsequent calls
//      ::opengl::check_error("");
//
//      auto size = m_vertexa.size();
//
//      auto data = m_vertexa.data();
//
//      glBindBuffer(GL_ARRAY_BUFFER, m_uVBO); // use this VBO for subsequent calls
//      ::opengl::check_error("");
//      glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW); // copy over the vertex data
//      ::opengl::check_error("");
//
//      // setup the locations of vertex data
//      // positions
//      glEnableVertexAttribArray(0);
//      ::opengl::check_error("");
//      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//      ::opengl::check_error("");
//
//      // texture coordinates
//      glEnableVertexAttribArray(1);
//      ::opengl::check_error("");
//      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//      ::opengl::check_error("");
//
//      glBindVertexArray(0);
//      ::opengl::check_error("");
//
//   }
//
//
//} // namespace gpu_opengl
//
//
