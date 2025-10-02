// From github:/tristancalderbank/OpenGL-PBR-Renderer/cube.cpp by
// camilo on 2025-09-27 ~02:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cube.h"
#include "_gpu_opengl.h"
#include <glad/glad.h>

 namespace gpu_opengl
 {

    cube::cube()
    {
    }

    cube::~cube()
    {
    }



    void cube::draw(::gpu::command_buffer *pcommandbuffer)
    {

       if (m_uVAO == 0)
       {

          throw ::exception(error_wrong_state);

       }
       if (m_vertexa.is_empty())
       {

          throw ::exception(error_wrong_state);

       }
       // draw mesh
       glBindVertexArray(m_uVAO);
       GLCheckError("");
       glDrawArrays(GL_TRIANGLES, 0, m_vertexa.size());
       GLCheckError("");
       glBindVertexArray(0);
       GLCheckError("");

    }

    void cube::initialize_gpu_cube(::gpu::context* pgpucontext)
    {

       ::gpu::cube::initialize_gpu_cube(pgpucontext);
       // create our data structures
       glGenVertexArrays(1, &m_uVAO);
       GLCheckError("");
       glGenBuffers(1, &m_uVBO);
       GLCheckError("");

       glBindVertexArray(m_uVAO); // use this VAO for subsequent calls
       GLCheckError("");

       glBindBuffer(GL_ARRAY_BUFFER, m_uVBO); // use this VBO for subsequent calls
       GLCheckError("");
       glBufferData(GL_ARRAY_BUFFER, m_vertexa.size() * sizeof(float),m_vertexa.data(), GL_STATIC_DRAW); // copy over the vertex data
       GLCheckError("");

       // setup the locations of vertex data
       // positions
       glEnableVertexAttribArray(0);
       GLCheckError("");
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
       GLCheckError("");

       glBindVertexArray(0);
       GLCheckError("");

    }


 } // namespace gpu_opengl


