// From github:/tristancalderbank/OpenGL-PBR-Renderer/cube.cpp by
// camilo on 2025-09-26 21:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cube.h"


 namespace gpu
 {

    cube::cube()
    {
    }


    cube::~cube()
    {
    }


    void cube::draw(::gpu::command_buffer *pcommandbuffer)
    {
       // draw mesh
       // glBindVertexArray(mVAO);
       // glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
       // glBindVertexArray(0);
    }


    void cube::initialize_gpu_cube(::gpu::context* pgpucontext)
    {

       m_modeldata.m_vertexes = {
          // positions
                      {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f},
          {-1.0f, 1.0f, -1.0f},

          {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f},
          {-1.0f, -1.0f, 1.0f},

          {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, -1.0f},
          {1.0f, -1.0f, -1.0f},

          {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f},
          {-1.0f, -1.0f, 1.0f},

          {-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f},
          {-1.0f, 1.0f, -1.0f},

          {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f},  {1.0f, -1.0f, 1.0f}
       };

       //// create our data structures
       //glGenVertexArrays(1, &mVAO);
       //glGenBuffers(1, &mVBO);

       //glBindVertexArray(mVAO); // use this VAO for subsequent calls

       //glBindBuffer(GL_ARRAY_BUFFER, mVBO); // use this VBO for subsequent calls
       //glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW); // copy over the vertex data

       //// setup the locations of vertex data
       //// positions
       //glEnableVertexAttribArray(0);
       //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

       //glBindVertexArray(0);
    }


 } // namespace gpu
