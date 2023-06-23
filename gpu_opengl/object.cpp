// Created by camilo on 2022-04-25 21:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "object.h"
#include <math.h>
#include "acme/constant/id.h"
#include "acme/filesystem/file/text_reader.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "assimp.h"
#include "opengl.h"

//#include <GLUT/GLUT.h>

//GLuint loadDDS(const char * imagepath);


const char * opengl_error_string(int iError)
{
   
   switch(iError)
   {
      case GL_NO_ERROR:
         return "GL_NO_ERROR";
      case GL_INVALID_ENUM:
         return "GL_INVALID_ENUM";


      case  GL_INVALID_VALUE:
         return "GL_INVALID_VALUE";

      case GL_INVALID_OPERATION:
   
         return "GL_INVALID_OPERATION";

      case GL_INVALID_FRAMEBUFFER_OPERATION:
         return "GL_INVALID_FRAMEBUFFER_OPERATION";

      case  GL_OUT_OF_MEMORY:
  
         return "GL_OUT_OF_MEMORY";

      case GL_STACK_UNDERFLOW:
     
         return "GL_STACK_UNDERFLOW";

      case GL_STACK_OVERFLOW:
         
         return "GL_STACK_OVERFLOW";
      default:
         return "Unknown GL Error";
         
         
   }
   
}

namespace opengl
{


   object::object()
   {

      m_bPrepared = false;

   }


   object::~object()
   {


   }


   void object::load(const ::file::path & path)
   {

      m_path = path;

      auto memory = file()->as_memory(path);

      ::assimp::load_obj(memory.data(), memory.size(), m_indices, m_vertices, m_uvs, m_normals);

   }


   //void object::prepare(::gpu::approach * papproach)
   //{

   //   if (m_bPrepared)
   //   {

   //      return;

   //   }

   //   _prepare(papproach);

   //   m_bPrepared = true;

   //}


   void object::_prepare(::gpu::approach * papproach)
   {

      // Dark blue background
      glClearColor(0.0f, 0.0f, 0.4f, 0.2f);


      // Enable depth test
      glEnable(GL_DEPTH_TEST);
      // Accept fragment if it closer to the camera than the former one
      glDepthFunc(GL_LESS);

      // Cull triangles which normal is not towards the camera
      glEnable(GL_CULL_FACE);


      int iErrorN;
      const char * pszErrorN = nullptr;

      while ((iErrorN = glGetError()))
      {
       
         pszErrorN = (const char *)opengl_error_string(iErrorN);

      }

#ifdef __APPLE__
      glGenVertexArraysAPPLE(1, (GLuint *) &m_vao_vertices); // vertext array object
#else
      glGenVertexArrays(1, (GLuint *) &m_vao_vertices); // vertext array object
#endif
      int iError2 = glGetError();
      auto pszError2 = (const char *)opengl_error_string(iError2);
      if(pszError2)
      {
         
         information() << "error " << pszError2;
         
      }
#ifdef __APPLE__
      glBindVertexArrayAPPLE(m_vao_vertices);
#else
      glBindVertexArray(m_vao_vertices);
#endif
      int iErrorA = glGetError();
      auto pszErrorA = (const char *)opengl_error_string(iErrorA);
      if(pszErrorA)
      {
         
         information() << "error " << pszErrorA;
         
      }

      glGenBuffers(1, (GLuint *)&m_vbo_vertices); // vertex buffer object
      int iError1 = glGetError();
      auto pszError1 = (const char *) opengl_error_string(iError1);
      if(pszError1)
      {
         
         information() << "error " << pszError1;
         
      }


      glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
      int iError5 = glGetError();
      auto pszError5 = (const char *)opengl_error_string(iError5);
      if(pszError5)
      {
         
         information() << "error " << pszError5;
         
      }

      auto byteCount1 = m_vertices.byte_count();
      auto data1 = m_vertices.data();

      glBufferData(GL_ARRAY_BUFFER, byteCount1, data1, GL_STATIC_DRAW);
      int iError4 = glGetError();
      auto pszError4 = (const char *)opengl_error_string(iError4);
      if(pszError4)
      {
         
         information() << "error " << pszError4;
         
      }
      //glEnableVertexAttribArray(m_vao_vertices);
      //int iError3 = glGetError();
      //auto pszError3 = (const char *)gluErrorString(iError3);

      //glVertexAttribPointer(
      //   m_vao_vertices,  // attribute
      //   4,                  // number of elements per vertex, here (x,y,z,w)
      //   GL_FLOAT,           // the type of each element
      //   GL_FALSE,           // take our values as-is
      //   0,                  // no extra data between each position
      //   0                   // offset of first element
      //);
      //int iError6 = glGetError();
      //auto pszError6 = (const char *)gluErrorString(iError6);

      //glGenBuffers(1, &m_vbo_normals); // vertex buffer object
      //int iError7 = glGetError();
      //auto pszError7 = (const char *)gluErrorString(iError7);

      //glGenVertexArrays(1, &m_vao_normals); // vertext array object
      //int iError8 = glGetError();
      //auto pszError8 = (const char *)gluErrorString(iError8);

      //glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
      //int iError11 = glGetError();
      //auto pszError11 = (const char *)gluErrorString(iError11);

      //glBufferData(GL_ARRAY_BUFFER, m_normals.byte_count(), m_normals.data(), GL_STATIC_DRAW);
      //int iError10 = glGetError();
      //auto pszError10 = (const char *)gluErrorString(iError10);

      //glEnableVertexAttribArray(m_vao_normals);
      //int iError9 = glGetError();
      //auto pszError9 = (const char *)gluErrorString(iError9);

      //glVertexAttribPointer(
      //   m_vao_normals, // attribute
      //   3,             // number of elements per vertex, here (x,y,z)
      //   GL_FLOAT,      // the type of each element
      //   GL_FALSE,      // take our values as-is
      //   0,             // no extra data between each position
      //   0              // offset of first element
      //);
      //int iError12 = glGetError();
      //auto pszError12 = (const char *)gluErrorString(iError12);


      //GLuint vertexbuffer;
      //glGenBuffers(1, &vertexbuffer);
      //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
      //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


      auto byteCount2 = m_uvs.byte_count();
      auto data2 = m_uvs.data();

      glGenBuffers(1, (GLuint *)&m_vbo_uvs);
      glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
      glBufferData(GL_ARRAY_BUFFER, byteCount2, data2, GL_STATIC_DRAW);


      //glGenBuffers(1, &m_ibo_elements);
      //int iError13 = glGetError();
      //auto pszError13 = (const char *)gluErrorString(iError13);

      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
      //int iError16 = glGetError();
      //auto pszError16 = (const char *)gluErrorString(iError16);

      //glBufferData(GL_ARRAY_BUFFER, m_normals.byte_count(), m_normals.data(), GL_STATIC_DRAW);
      //int iError14 = glGetError();
      //auto pszError14 = (const char *)gluErrorString(iError14);

      //glBufferData(GL_ARRAY_BUFFER, m_vertices.byte_count(), m_vertices.data(), GL_STATIC_DRAW);
      //int iError15 = glGetError();
      //auto pszError15 = (const char *)gluErrorString(iError15);

      // Load the texture
      m_uniformTexture = papproach->load_dds(m_path+ ".uvmap.DDS");
      //m_uniformTexture = papproach->load_dds(m_path + ".uvmap.DDS");
      //m_uniformTexture = papproach->load_normal_map(m_path.folder() / (m_path.title() + ".png"));

   }


   void object::draw()
   {

      if (m_iTextureUniform > 0)
      {

         // Bind our texture in Texture Unit 0
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, m_uniformTexture);
         // Set our "myTextureSampler" sampler to use Texture Unit 0
         glUniform1i(m_iTextureUniform, 0);

      }

      // 1rst attribute buffer : vertices
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
      glVertexAttribPointer(
         0,                  // attribute
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void *)0            // array buffer offset
      );

      // 2nd attribute buffer : UVs
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uvs);
      glVertexAttribPointer(
         1,                                // attribute
         2,                                // size
         GL_FLOAT,                         // type
         GL_FALSE,                         // normalized?
         0,                                // stride
         (void *)0                          // array buffer offset
      );

      auto sizeVertices = m_vertices.size();
      // Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, (GLsizei)sizeVertices);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);


   }


   void object::set_texture_uniform(::gpu::uniform uniformTexture)
   {

      m_uniformTexture = uniformTexture;

   }


} // namespace opengl



