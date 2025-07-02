#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "device_win32.h"
#include "frame_buffer.h"
#include "lock.h"
#include "model_buffer.h"
#include "program.h"
#include "renderer.h"
#include "render_target.h"
#include "shader.h"
#include "texture.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/types.h"
#include "glm/mat4x4.hpp"


namespace gpu_opengl
{

   void vertex2f(const ::double_rectangle& rectangle, float fZ);

   void vertex2f(const ::double_polygon& a, float fZ);


   context::context()
   {

      m_gluLayerFrameBuffer = 0;
      m_globalUBO = 0;
      //m_gluLayFrameBufferRenderer = 0;

      //m_fboID = 0;
      //m_texID = 0;
      //m_bMesa = false;

      //m_emode = e_mode_system;

      m_estatus = error_not_initialized;

      //m_emode = e_mode_none;
      //m_itaskGpu = 0;
      m_iLastBitmap1Scan = -1;

      m_gluTextureBitmap1 = 0;
      m_VAO = 0;
      m_VBO = 0;

   }


   context::~context()
   {

   }


   void context::draw()
   {

      ::gpu::context_lock contextlock(this);

      ::cast < device_win32 > pgpudevice = m_pgpudevice;

      if (pgpudevice->m_itaskCurrentGpuContext != ::current_itask())
      {

         ASSERT(false);

      }

      if (m_VAO != 0)
      {

         //return ::success;
         return;

      }
      //glGenBuffers(1, &VAO);
//      float vertices[] = {
         // positions         // colors
  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
      //};
      float vertices[] = {
         // first triangle
          1.f,  1.f, 0.0f,  // top right
          1.f, -1.f, 0.0f,  // bottom right
         -1.f,  1.f, 0.0f,  // top left
         // second triangle
          1.f, -1.f, 0.0f,  // bottom right
         -1.f, -1.f, 0.0f,  // bottom left
         -1.f,  1.f, 0.0f   // top left
      };

#if defined(__APPLE__)

      glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArray(m_VAO);

      //#elif defined(__ANDROID__)
      //
      //      glGenVertexArrays(1, &m_VAO);
      //      glGenBuffers(1, &m_VBO);
      //      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      //      glBindVertexArray(m_VAO);

#else

      glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArray(m_VAO);

#endif

      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      // color attribute
      //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
      //glEnableVertexAttribArray(1);

      //return ::success;
   }


   void context::start_drawing()
   {

      ::gpu::context_lock contextlock(this);

      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
//int iError16 = glGetError();

//int size = 0; 
//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//int iError17 = glGetError();

//glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
//int iError18 = glGetError();

      ::cast < device_win32 > pgpudevice = m_pgpudevice;

      if (pgpudevice->m_itaskCurrentGpuContext != ::current_itask())
      {

         ASSERT(false);

      }

      //      glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

            // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //glClear(GL_COLOR_BUFFER_BIT);

      if (m_pshader)
      {

         m_pshader->bind();

      }
      // Use our shader
      //glUseProgram(programID);

      // be sure to activate the shader
      //glUseProgram(shaderProgram);

      // update the uniform color
      //float timeValue = glfwGetTime();
      //float greenValue = sin(timeValue) / 2.0f + 0.5f;
      //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      //return ::success;

   }



   void context::global_transform()
   {

      ::gpu::context_lock contextlock(this);

      // Get a handle for our "MVP" uniform
      //GLint MatrixID = glGetUniformLocation(programID, "MVP");

      if (m_iMatrixUniform >= 0)
      {

         // Compute the MVP matrix from keyboard and mouse input
         //computeMatricesFromInputs();
         ::glm::mat4 matrixProjection = (::glm::mat4&)projection_matrix();
         ::glm::mat4 matrixView = (::glm::mat4&)view_matrix();
         ::glm::mat4 matrixModel = glm::mat4(1.0);
         ::glm::mat4 matrixMVP = matrixProjection * matrixView * matrixModel;

         // Send our transformation to the currently bound shader, 
         // in the "MVP" uniform
         glUniformMatrix4fv(m_iMatrixUniform, 1, GL_FALSE, &matrixMVP[0][0]);

      }

      //glm::mat4 getViewMatrix() {
      //   return ViewMatrix;
      //}
      //glm::mat4 getProjectionMatrix() {
      //   return ProjectionMatrix;
      //}


      //// Initial position : on +Z
      //glm::vec3 position = glm::vec3(0, 0, 5);
      //// Initial horizontal angle : toward -Z
      //float horizontalAngle = 3.14f;
      //// Initial vertical angle : none
      //float verticalAngle = 0.0f;
      //// Initial Field of View
      //float initialFoV = 45.0f;

      //float speed = 3.0f; // 3 units / second
      //float mouseSpeed = 0.005f;



   }


   void context::render()
   {

      ::gpu::context_lock contextlock(this);

      ::cast < device_win32 > pgpudevice = m_pgpudevice;

      if (pgpudevice->m_itaskCurrentGpuContext != ::current_itask())
      {

         ASSERT(false);

      }

      //#ifdef __APPLE__

            //glBindVertexArrayAPPLE(m_VAO);

      //#else

      if (m_gluTextureBitmap1)
      {

         //glMatrixMode(GL_PROJECTION);
         //glOrtho(0, 800, 0, 600, -1, 1);
         // glMatrixMode(GL_MODELVIEW);

         //clear and draw quad with texture (could be in display callback)
         //glClear(GL_COLOR_BUFFER_BIT);
         //glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);
         ////glEnable(GL_TEXTURE_2D);
         //glBegin(GL_QUADS);
         //glTexCoord2i(0, 0); glVertex2f(-1.0, -1.0);
         //glTexCoord2i(0, 1); glVertex2f(-1.0, 1.0);
         //glTexCoord2i(1, 1); glVertex2f(1.0, 1.0);
         //glTexCoord2i(1, 0); glVertex2f(1.0, -1.0);
         //glEnd();
         //glDisable(GL_TEXTURE_2D);
         //glBindTexture(GL_TEXTURE_2D, 0);
         //glFlush();

         GLuint readFboId = 0;
         glGenFramebuffers(1, &readFboId);
         glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
         glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, m_gluTextureBitmap1, 0);
         glBlitFramebuffer(0, 0, m_sizeBitmap1.cx(), m_sizeBitmap1.cy(),
            0, 0, m_rectangle.width(), m_rectangle.height(),
            GL_COLOR_BUFFER_BIT, GL_LINEAR);
         glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
         glDeleteFramebuffers(1, &readFboId);
      }
      else
      {

#ifdef __APPLE__
         glBindVertexArrayAPPLE(m_VAO);
#else
         glBindVertexArray(m_VAO);
#endif

         glDrawArrays(GL_TRIANGLES, 0, 6);

      }

      //return ::success;

   }


   void context::set_bitmap_1(::image::image* pimage)
   {

      ::gpu::context_lock contextlock(this);

      ::cast < device_win32 > pgpudevice = m_pgpudevice;

      if (pgpudevice->m_itaskCurrentGpuContext != ::current_itask())
      {

         ASSERT(false);

      }

      if (!m_gluTextureBitmap1)
      {

         glGenTextures(1, &m_gluTextureBitmap1); // generate texture id for your texture (can skip this line)
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);

         glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set alignment of data in memory (a good thing to do before glTexImage)

         //#if defined(__APPLE__) || defined(__ANDROID__)
         //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // set clamp (GL_CLAMP_TO_EDGE would be better)
         //#else
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // set clamp (GL_CLAMP_TO_EDGE would be better)
         //#endif
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // set linear filtering (so you can scale your image)

      }

      if (pimage->is_ok())
      {

         pimage->map();

         glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);

         if (m_iLastBitmap1Scan != pimage->m_iScan)
         {

            m_iLastBitmap1Scan = pimage->m_iScan;

            glPixelStorei(GL_UNPACK_ROW_LENGTH, pimage->m_iScan / 4);

         }

         m_sizeBitmap1 = pimage->size();


         m_memorySwap.set_size(m_sizeBitmap1.area() * 4);

         //vertical_swap_copy_image32_swap_red_blue(
         ((image32_t*)m_memorySwap.data())->vertical_swap_copy_swap_red_blue(
            m_sizeBitmap1.cx(),
            m_sizeBitmap1.cy(),
            m_sizeBitmap1.cx() * 4,
            pimage->get_data(),
            pimage->m_iScan);

         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            m_sizeBitmap1.cx(),
            m_sizeBitmap1.cy(),
            0, GL_RGBA, GL_UNSIGNED_BYTE,
            m_memorySwap.data()); // upload image data to the textur





      }

   }


   //void context::swap_buffers()
   //{

   //   ::cast < device_win32 > pgpudevice = m_pgpudevice;

   //   pgpudevice->_swap_buffers();

   //}





   void context::update_framebuffer(const ::int_size& size)
   {

      if (m_eoutput == ::gpu::e_output_swap_chain)
      {

         return;

      }

      __defer_construct(m_pframebuffer);

      if (size.area() > 0)
      {

         m_pframebuffer->create(size, m_bDepthBuffer);

      }

      //if (!m_fboID)
      //{

      //   glGenFramebuffers(1, &m_fboID);

      //}

      //if (size == m_sizeTex)
      //{

      //   return;

      //}

      //glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

      //if (m_texID == 0)
      //{
      //   glGenTextures(1, &m_texID);
      //   auto iError = glGetError();
      //   if (iError != 0)
      //   {
      //      auto pszError = opengl_error_string(iError);
      //      warning() << "error generating texture " << pszError;
      //   }
      //   glBindTexture(GL_TEXTURE_2D, m_texID);
      //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width(), size.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //   glBindTexture(GL_TEXTURE_2D, 0);

      //   // attach it to currently bound framebuffer object
      //   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texID, 0);

      //}
      //else
      //{

      //   glBindTexture(GL_TEXTURE_2D, m_texID);
      //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width(), size.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      //   glBindTexture(GL_TEXTURE_2D, 0);

      //}

      //auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      //if (status != GL_FRAMEBUFFER_COMPLETE)
      //{
      // 
      //   warning() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! " << status;

      //}
      //else
      //{

      //   m_sizeTex = size;

      //}

      //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      ////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //glClear(GL_COLOR_BUFFER_BIT);

      //glBindFramebuffer(GL_FRAMEBUFFER, 0);

      ////if (oldTexID)
      ////{

      ////   glDeleteTextures(1, &oldTexID);

      ////   auto iError = glGetError();

      ////   if (iError != 0)
      ////   {

      ////      auto pszError = opengl_error_string(iError);

      ////      warning() << "error generating texture " << pszError;

      ////   }

      ////}

   }


   //void context::create_offscreen_buffer(const ::int_size& size)
   //{

   //   auto pgpu = application()->get_gpu();

   //   if (::is_null(pgpu))
   //   {

   //      return ::error_failed;

   //   }

   //   ::e_status estatus = __øconstruct(m_pbuffer);

   //   if (!estatus)
   //   {

   //      return false;

   //   }

   //   m_pbuffer->m_pimage = create_image(size);

   //   if (!::is_ok(m_pbuffer->m_pimage))
   //   {

   //      return false;

   //   }

   //   estatus = _create_offscreen_buffer(size);

   //   if(!estatus)
   //   {

   //      return estatus;

   //   }

   //   return ::success_none;

   //}


   //void context::_create_offscreen_buffer(const ::int_size& size)
   //{

   //   return ::success_none;

   //}


   //void context::resize_offscreen_buffer(const ::int_size& size)
   //{

   //   return ::success_none;

   //}



   //void context::make_current()
   //{

   //   return ::success_none;

   //}


   //void context::destroy_offscreen_buffer()
   //{

   //   return ::success_none;

   //}


   string context::_001GetIntroProjection()
   {

      string strVersion = get_shader_version_text();


      string strProjection =
         "layout(location = 0) in vec3 aPos;\n"
         "out vec3 ourPosition;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   gl_Position = vec4(aPos, 1.0);\n"
         "   ourPosition = aPos;\n"
         "}\n";

      return strProjection;
   }


   string context::_001GetIntroFragment()
   {

      string strVersion = get_shader_version_text();

      string strFragment =
         "uniform vec2 resolution;\n"
         "uniform float time;\n"
         "uniform vec2 mouse;\n"
         "uniform sampler2D backbuffer;\n"
         "\n"
         "void main(void) {\n"
         "float base_res = min(resolution.x(), resolution.y());\n"
         "vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / base_res;\n"
         "\n"
         //"gl_FragColor = vec4(uv, (uv.x() * uv.x()) / 2.0, ((uv.x() + (base_res - uv.y())) *(uv.x() + (base_res - uv.y()))) / 2.0);\n"
         "float posx = max(0.f, uv.x());\n"
         "float posy = max(0.f, uv.y());\n"
         "gl_FragColor = vec4(uv, (posx * posx) / 4.0, ((posx + posy) * (posx + posy)) / 4.0);\n"
         "}\n";

      return strFragment;

   }

   //   string context::load_fragment(const ::string & pszPath, enum_shader & eshader)
   //   {
   //
   //      ::file::path path(pszPath);
   //
   //      auto & app = papp;
   //
   //      auto & file = app.file();
   //
   //      string strFragment = file.as_string(path);
   //
   //      string strExtension = path.extension();
   //
   //      string strVersion = get_shader_version_text();
   //
   //      if (strExtension.case_insensitive_begins("shadertoy"))
   //      {
   //
   //         eshader = e_shader_shadertoy;
   //
   //         strFragment =
   //            //"#" + strVersion + "\n"
   //            //"\n"
   //            //"precision highp float;\n"
   //            "\n"
   //            "uniform vec2 iResolution;\n"
   //            "uniform float iTime;\n"
   //            "uniform vec2 iMouse;\n"
   //            "uniform sampler2D backbuffer;\n"
   //            "\n"
   //            "\n"
   //            + strFragment;
   //
   //
   //         strFragment +=
   //            "\n\n"
   //            "void main(void)\n"
   //            "{\n"
   //            "   mainImage(gl_FragColor, gl_FragCoord.xy);\n"
   //            "}\n";
   //
   //      }
   //      else
   //      {
   //
   //         strFragment =
   ////            "#" + strVersion + "\n"
   ////            "\n"
   //            + strFragment;
   //
   //         eshader = e_shader_neort;
   //
   //      }
   //
   //      return strFragment;
   //
   //   }


      //string context::get_shader_version_text()
      //{

      //   return "version 330 core";

      //}

      //void context::translate_shader(string& strFragment)
      //{

      //   string_array stra;

      //   stra.add_lines(strFragment);

      //   auto pFind = stra.case_insensitive_find_first_begins("#version ");

      //   if (::is_set(pFind))
      //   {

      //      stra[iFind] = get_shader_version_text();

      //   }
      //   else
      //   {

      //      stra.insert_at(0, get_shader_version_text());

      //   }

      //   _translate_shader(stra);

      //   strFragment = stra.implode("\n");

      //}


      //void context::_translate_shader(string_array& stra)
      //{

      //}


   void context::set_matrix_uniform(const ::gpu::payload& uniformMatrix)
   {

      m_iMatrixUniform = uniformMatrix.m_iUniform;

   }


   void context::clear(const ::color::color& color)
   {

      ::gpu::context_lock contextlock(this);
      // Clear the screen 
      GLCheckError("");
      //   glClearColor(0.678f, 0.847f, 0.902f, 1.0f);//
      glClearColor(color.f32_red(), color.f32_green(), color.f32_blue(), color.f32_opacity());//
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      GLCheckError("");

   }


   void context::create_global_ubo(int iGlobalUboSize, int iFrameCount)
   {

      ::gpu::context_lock contextlock(this);

      // Create the UBO
      glGenBuffers(1, &m_globalUBO);
      glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
      glBufferData(GL_UNIFORM_BUFFER, iGlobalUboSize, NULL, GL_STATIC_DRAW); // For 2 mat4s = 2 * sizeof(float) * 16
      unsigned int uUboBindingPoint = 0;
      glBindBufferBase(GL_UNIFORM_BUFFER, uUboBindingPoint, m_globalUBO);
      glBindBuffer(GL_UNIFORM_BUFFER, 0);

   }


   void context::update_global_ubo(const ::block& block)
   {

      ::gpu::context_lock contextlock(this);

      glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
      GLCheckError("");

      // Map the entire buffer for writing
      void* p = glMapBufferRange(
         GL_UNIFORM_BUFFER,
         0, block.size(),
         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
      GLCheckError("");

      if (p)
      {

         memcpy(p, block.data(), block.size());

         glUnmapBuffer(GL_UNIFORM_BUFFER);
         GLCheckError("");

      }
      else
      {

         warning() << "Failed to map UBO";

      }

      glBindBuffer(GL_UNIFORM_BUFFER, 0);
      GLCheckError("");

   }


   //void createFullscreenQuad(GLuint* vao, GLuint* vbo) {
   //   float quadVertices[] = {
   //      // pos     // uv
   //      -1, -1,    0, 0,
   //      +1, -1,    1, 0,
   //      -1, +1,    0, 1,
   //      +1, +1,    1, 1,
   //   };

   //   glGenVertexArrays(1, vao);
   //   glGenBuffers(1, vbo);
   //   glBindVertexArray(*vao);

   //   glBindBuffer(GL_ARRAY_BUFFER, *vbo);
   //   glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

   //   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // position
   //   glEnableVertexAttribArray(0);

   //   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // UV
   //   glEnableVertexAttribArray(1);

   //   glBindVertexArray(0);
   //}


   void context::copy(::gpu::texture* ptextureParam)
   {

      _copy_using_shader(ptextureParam);

   }


   void context::_copy_using_shader(::gpu::texture* ptextureParam)
   {

      ::gpu::context_lock contextlock(this);

      if (!m_pshaderCopy)
      {

         __construct_new(m_pshaderCopy);

         // Vertex shader
         const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inUV;
out vec2 fragUV;
void main() {
    fragUV = inUV;
    gl_Position = vec4(inPos, 0.0, 1.0);
}
)";

         // Fragment shader
         const char* fragmentShaderSource = R"(
#version 330 core
in vec2 fragUV;
out vec4 outColor;
uniform sampler2D uTexture;
void main() {
    outColor = texture(uTexture, fragUV);
}
)";

         m_pshaderCopy->initialize_shader_with_block(
            m_pgpurenderer,
            vertexShaderSource,
            fragmentShaderSource);
      }

      auto pmodelbufferFullScreenQuad = sequence2_uv_fullscreen_quad_model_buffer();

    /*  if (!m_vaoFullScreenQuad)
      {

         createFullscreenQuad(&m_vaoFullScreenQuad, &m_vboFullScreenQuad);

      }*/
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      //glDisable(GL_BLEND);                    // Ensure no blending

      int cx = m_rectangle.width();
      int cy = m_rectangle.height();
      glViewport(0, 0, cx, cy);
      //glClearColor(0.1, 0.1, 0.1, 1.0);
      //glClear(GL_COLOR_BUFFER_BIT);

      
      m_pshaderCopy->bind();

      m_pshaderCopy->bind_source(ptextureParam);

      auto pcommandbuffer = m_pgpurenderer->getCurrentCommandBuffer2();

      pmodelbufferFullScreenQuad->bind(pcommandbuffer);

      // glBindVertexArray(m_vaoFullScreenQuad);

      //::cast < texture > ptexture = ptextureParam;
      pmodelbufferFullScreenQuad->draw(pcommandbuffer);


      pmodelbufferFullScreenQuad->unbind(pcommandbuffer);

      ////glActiveTexture(GL_TEXTURE0);
      //;; glBindTexture(GL_TEXTURE_2D, ptexture->m_gluTextureID);
      //m_pshaderCopy->_set_int("uTexture", 0);

      //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      m_pshaderCopy->unbind();

   }


   void context::merge_layers(::gpu::texture* ptextureTarget, ::pointer_array < ::gpu::layer >* playera)
   {


      ::gpu::context_lock contextlock(this);

      if (!m_pmodelbufferDummy)
      {

         __defer_construct(m_pmodelbufferDummy);

         m_pmodelbufferDummy->initialize_gpu_context_object(this);

         m_pmodelbufferDummy->m_iVertexCount = 3;

      }

      {

         if (!m_pshaderBlend3)
         {

            const char full_screen_triangle_vertex_shader[] = R"vert(
#version 330 core

out vec2 uv;

void main() {
    const vec2 pos[3] = vec2[](
        vec2(-1.0, -1.0),
        vec2(-1.0,  3.0),
        vec2( 3.0, -1.0)
    );

    const vec2 tex[3] = vec2[](
        vec2(0.0, 0.0),
        vec2(0.0, 2.0),
        vec2(2.0, 0.0)
    );

    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    uv = tex[gl_VertexID];
}
)vert";

            const char full_screen_triangle_fragment_shader[] = R"frag(
#version 330 core

uniform sampler2D uTexture;

in vec2 uv;
out vec4 outColor;

void main() {
    vec4 color = texture(uTexture, uv);
    outColor = color;
}
)frag";

            __defer_construct_new(m_pshaderBlend3);

            m_pshaderBlend3->m_bEnableBlend = true;
            m_pshaderBlend3->m_bTextureAndSampler = true;
            m_pshaderBlend3->m_bDisableDepthTest = true;
            //m_pshaderBlend3->m_bT
            //m_pshaderBlend3->m_pgpurenderer = this;
            //m_pshaderBlend3->m_iSamplerSlot = 0;
            // Image Blend descriptors
   //if (!m_psetdescriptorlayoutImageBlend)

            //m_pshaderBlend3->m_bClearColor = true;
            //m_pshaderBlend3->m_colorClear = ::color::transparent;

            //m_pshaderBlend3->m_bClearColor = false;
            //m_pshaderBlend3->m_colorClear = ::color::transparent;

            m_pshaderBlend3->initialize_shader_with_block(
               m_pgpurenderer,
               ::as_block(full_screen_triangle_vertex_shader),
               ::as_block(full_screen_triangle_fragment_shader),
               {},
               {},
               {},
               {},
               // this means the vertex input layout will be null/empty
               // the full screen shader is embed in the shader code
               ::gpu::shader::e_flag_clear_default_bindings_and_attributes_descriptions

            );

         }


         //if (!m_pd3d11blendstateBlend3)
         //{

         //   D3D12_BLEND_DESC blendDesc = { 0 };
         //   blendDesc.RenderTarget[0].BlendEnable = TRUE;
         //   blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;              // Premultiplied alpha
         //   blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;   // Use inverse of alpha
         //   blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

         //   blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;         // Alpha blending (optional)
         //   blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
         //   blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

         //   blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

         //   ::cast < ::gpu_directx11::device > pgpudevice = m_pgpudevice;

         //   HRESULT hr = pgpudevice->m_pdevice->CreateBlendState(&blendDesc, &m_pd3d11blendstateBlend3);
         //   ::defer_throw_hresult(hr);

         //}

         ::cast < renderer > prenderer = m_pgpurenderer;

         ::cast < ::gpu_opengl::command_buffer > pcommandbuffer = prenderer->getCurrentCommandBuffer2();

         //auto vkcommandbuffer = pcommandbuffer->m_vkcommandbuffer;

         ::cast <texture > ptextureDst = ptextureTarget;

         int iH = ptextureDst->m_pgpurenderer->m_pgpucontext->m_rectangle.height();

         //ptextureDst->_new_state(
         //   pcommandbuffer,
         //   VK_ACCESS_TRANSFER_WRITE_BIT,
         //   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
         //   VK_PIPELINE_STAGE_TRANSFER_BIT
         //);



         //pcommandbuffer->set_viewport(m_rectangle.size());

         //pcommandbuffer->set_scissor(m_rectangle.size());


         //// 2. Clear
         //VkClearColorValue clearColor = { .float32 = { 0.0f, 0.0f, 0.0f, 0.0f } };
         //VkImageSubresourceRange range = {
         //    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
         //    .baseMipLevel = 0,
         //    .levelCount = 1,
         //    .baseArrayLayer = 0,
         //    .layerCount = 1,
         //};

         //vkCmdClearColorImage(
         //   vkcommandbuffer,
         //   ptextureDst->m_vkimage,
         //   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
         //   &clearColor,
         //   1,
         //   &range);


         ////float clearColor[4] = { 0.95f * 0.5f, 0.95f * 0.5f, 0.25f * 0.5f, 0.5f }; // Clear to transparent
         ////m_pcontext->ClearRenderTargetView(ptextureDst->m_prendertargetview, clearColor);
         //float clearColor[4] = { 0.f, 0.f, 0.f, 0.f }; // Clear to transparent
         //pcommandlist->ClearRenderTargetView(ptextureDst->m_handleRenderTargetView, clearColor, 0, nullptr);
         //ptextureDst->_new_state(pcommandbuffer,
         //   VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
         //   VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
         //   VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
         //);

         //if (!ptextureDst->m_handleRenderTargetView.ptr)
         //{

           // ptextureDst->create_render_target();

         //}


         //m_pshaderBlend3->bind(ptextureTarget);


         //int iDescriptorSize = ptextureDst->m_rtvDescriptorSize;
         //int iFrameIndex = m_pgpurendertarget->get_frame_index();
         //auto hRtv = pgpurendertargetview->m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
         //auto hRtv = ptextureDst->m_handleRenderTargetView;
         //CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
           // hRtv,
            //iFrameIndex,
            //iDescriptorSize);

         //float clearColor[4] = { 0.5f * 0.5f, 0.75f * 0.5f, 0.9f * 0.5f, 0.5f };
         //float clearColor[4] = { 0.f, 0.f , 0.f, 0.f };
         //pcommandlist->ClearRenderTargetView(hRtv, clearColor, 0, nullptr);

         //{
         //   float blendFactor[4] = { 0, 0, 0, 0 }; // Ignored with this blend mode
         //   UINT sampleMask = 0xFFFFFFFF;
         //   m_pcontext->OMSetBlendState(m_pd3d11blendstateBlend3, blendFactor, sampleMask);
         //}



         //ID3D11RenderTargetView* rendertargetview[] = { ptextureDst->m_prendertargetview };

         //m_p(1, rendertargetview, nullptr);

         //m_pcontext->OMSetBlendState(g_blendState, nullptr, 0xffffffff);
         //g_context->VSSetShader(g_vs, nullptr, 0);
         //g_context->PSSetShader(g_ps, nullptr, 0);
         //g_context->PSSetSamplers(0, 1, &g_sampler);

         if (1)
         {
            int iLayer = 0;
            for (auto player : *playera)
            {

               //if (iLayer == 2)
               {


                  ::cast <texture > ptextureSrc = player->texture();

                  //ptextureSrc->_new_state(
                  //   pcommandbuffer,
                  //   0,
                  //   VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                  //   VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
                  //);

                  m_pshaderBlend3->bind(ptextureDst, ptextureSrc);

                  if (iLayer == 0)
                  {

                     glClearColor(0.f, 0.f, 0.f, 0.f);
                     glClearDepth(1.0f);
                     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                  }

                  auto r = ptextureSrc->m_rectangleTarget;

                  int h = r.height();

                  r.top() = iH - r.bottom();

                  r.bottom() = r.top() + h;

                  pcommandbuffer->set_viewport(r);

                  pcommandbuffer->set_scissor(r);

                  m_pmodelbufferDummy->bind(pcommandbuffer);

                  m_pmodelbufferDummy->draw(pcommandbuffer);

                  m_pmodelbufferDummy->unbind(pcommandbuffer);

                  //ID3D11SamplerState* samplerstatea[] =
                  //{ ptexture->m_psamplerstate };
                  //ID3D11ShaderResourceView* sharedresourceviewa[] =
                  //{ ptexture->m_pshaderresourceview };

                                 // 1. Define viewport and scissor rectangle
                  //D3D12_VIEWPORT viewport = {};
                  //viewport.TopLeftX = ptextureSrc->m_rectangleTarget.left();
                  //viewport.TopLeftY = ptextureSrc->m_rectangleTarget.top();
                  //viewport.Width = static_cast<float>(ptextureSrc->m_rectangleTarget.width());
                  //viewport.Height = static_cast<float>(ptextureSrc->m_rectangleTarget.height());
                  //viewport.MinDepth = 0.0f;
                  //viewport.MaxDepth = 1.0f;

                  //D3D12_RECT scissorRect = {};
                  //scissorRect.left = ptextureSrc->m_rectangleTarget.left();
                  //scissorRect.top = ptextureSrc->m_rectangleTarget.top();
                  //scissorRect.right = ptextureSrc->m_rectangleTarget.right();
                  //scissorRect.bottom = ptextureSrc->m_rectangleTarget.bottom();


                  ////// 4. Set the viewport and scissor
                  //pcommandlist->RSSetViewports(1, &viewport);
                  //pcommandlist->RSSetScissorRects(1, &scissorRect);
                  //D3D11_VIEWPORT vp = {};
                  //vp.TopLeftX = ptexture->m_rectangleTarget.left();
                  //vp.TopLeftY = ptexture->m_rectangleTarget.top();
                  //vp.Width = static_cast<float>(ptexture->m_rectangleTarget.width());
                  //vp.Height = static_cast<float>(ptexture->m_rectangleTarget.height());
                  //vp.MinDepth = 0.0f;
                  //vp.MaxDepth = 1.0f;
                  //m_pcontext->RSSetViewports(1, &vp);

                  //m_pcontext->PSSetSamplers(0, 1, samplerstatea);
                  //m_pcontext->PSSetShaderResources(0, 1, sharedresourceviewa);


                  //pcommandlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                  //vkCmdDraw(vkcommandbuffer, 3, 1, 0, 0);
                  m_pshaderBlend3->unbind();
               }
               iLayer++;

            }

         }
         //}



         ////::cast <texture > ptextureDst = ptextureTarget;
         //{
         //   
         //   float clearColor2[4] = { 0.95f * 0.5f, 0.75f * 0.5f, 0.95f * 0.5f, 0.5f }; // Clear to transparent
         //   
         //   D3D12_RECT r[1];
         //   
         //   r[0].left = 100;
         //   r[0].top = 200;
         //   r[0].right = 200;
         //   r[0].bottom = 300;
         //   
         //   pcommandlist->ClearRenderTargetView(
         //      ptextureDst->m_pheapRenderTargetView->GetCPUDescriptorHandleForHeapStart(),
         //      clearColor2,
         //      1, r);

         //}


      }


      //::gpu::context::merge_layers(ptextureTarget, playera);

      ////::gpu::context_lock contextlock(this);

      ////::cast < texture > ptextureDst = ptextureTarget;

      //////if()

      //////GLuint framebuffer;
      //////glGenFramebuffers(1, &framebuffer);
      //////GLCheckError("glGenFramebuffers");
      //////glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
      //////GLCheckError("glBindFramebuffer");

      //////auto gluTextureID = ptextureDst->m_gluTextureID;

      //////// Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      //////glFramebufferTexture2D(
      //////   GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      //////   gluTextureID,
      //////   0);
      //////GLCheckError("glFramebufferTexture2D");

      //////if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      //////   printf("Framebuffer not complete!\n");
      //////   glDeleteFramebuffers(1, &framebuffer);
      //////   return;
      //////}

      //////glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      ////////glClearColor(0.5f * 0.5f, 0.75f * 0.5f, 0.95f * 0.5f, 0.5f);
      //////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ////glFlush();

      ////::cast < renderer > prenderer = m_pgpurenderer;

      ////for (auto& player : *playera)
      ////{

      ////   if (player.is_null())
      ////   {

      ////      continue;

      ////   }

      ////   prenderer->__blend(ptextureTarget, player->texture());

      ////}

      ////glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer
      ////GLCheckError("glBindFramebuffer");

      ////glDeleteFramebuffers(1, &framebuffer);
      ////GLCheckError("glDeleteFramebuffers");




   }


   void context::on_start_layer(::gpu::layer* player)
   {

      ::gpu::context::on_start_layer(player);

      //if (m_escene == ::gpu::e_scene_2d)
      //{

      //   glClearColor(0.0, 0.0, 0.0, 0.0); // test with a bright clear
      //   glClear(GL_COLOR_BUFFER_BIT);

      //}
      //else if (m_escene == ::gpu::e_scene_3d)
      //{

      //   glClearColor(0.0, 0.0, 0.0, 0.0); // test with a bright clear
      //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //}


   }


   //void context::_ensure_layer_framebuffer()
   //{

   //   ::gpu::context_lock contextlock(this);

   //   GLint fbo = 0;
   //   glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fbo);
   //   GLCheckError("");

   //   if (m_gluLayerFrameBuffer &&
   //      m_gluLayerFrameBuffer == fbo)
   //   {

   //      return; // already bound

   //   }

   //   if (!m_gluLayerFrameBuffer)
   //   {

   //      GLuint fboSrc, fboDst;
   //      glGenFramebuffers(1, &m_gluLayerFrameBuffer);
   //      GLCheckError("");

   //   }

   //   glBindFramebuffer(GL_FRAMEBUFFER, m_gluLayerFrameBuffer);
   //   GLCheckError("");

   //   ::cast < texture > ptexture = m_pgpurenderer->m_pgpurendertarget->current_texture();

   //   int textureID = ptexture->m_gluTextureID;

   //   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
   //      GL_TEXTURE_2D, textureID, 0);
   //   GLCheckError("");

   //   ::cast < context > pgpucontext = this;

   //   if (pgpucontext->m_escene == ::gpu::e_scene_3d)
   //   {

   //      if (!ptexture->m_gluDepthStencilRBO)
   //      {

   //         int width = pgpucontext->m_rectangle.width();

   //         int height = pgpucontext->m_rectangle.height();

   //         glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
   //         GLCheckError("");

   //         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
   //         GLCheckError("");

   //         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
   //         GLCheckError("");

   //      }

   //      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
   //      GLCheckError("");

   //   }

   //}


   void context::_copy_using_blit(::gpu::texture* ptextureParam)
   {

      ::gpu::context_lock contextlock(this);

      ::cast < texture > ptexture = ptextureParam;


      GLuint framebuffer;
      glGenFramebuffers(1, &framebuffer);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);

      // Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      glFramebufferTexture2D(
         GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
         ptexture->m_gluTextureID,
         0);

      if (glCheckFramebufferStatus(GL_READ_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
         printf("Framebuffer not complete!\n");
         glDeleteFramebuffers(1, &framebuffer);
         return;
      }


      //glReadBuffer(GL_COLOR_ATTACHMENT0);

      // Bind default framebuffer as draw target
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


      glViewport(
         0,
         0,
         m_rectangle.width(),
         m_rectangle.height());

      // Optional: scissor if you want to limit drawing region
      glEnable(GL_SCISSOR_TEST);
      glScissor(
         0,
         0,
         m_rectangle.width(),
         m_rectangle.height()
      );


      // Blit from source to default framebuffer
      glBlitFramebuffer(
         0, 0, ptexture->size().cx(), ptexture->size().cy(), // src rect
         0, 0, m_rectangle.width(), m_rectangle.height(), // dst rect
         GL_COLOR_BUFFER_BIT, GL_NEAREST);

      glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer

      glDeleteFramebuffers(1, &framebuffer);

#ifdef SHOW_DEBUG_DRAWING
      {

         glBindFramebuffer(GL_FRAMEBUFFER, 0);


         glEnable(GL_BLEND);
         glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
         //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

         {
            float fOpacity = 0.5;
            float fRed = 0.5;
            float fGreen = 0.75;
            float fBlue = 0.95;
            auto f32Opacity = (float)fOpacity;
            auto f32Red = (float)(fRed * fOpacity);
            auto f32Green = (float)(fGreen * fOpacity);
            auto f32Blue = (float)(fBlue * fOpacity);
            ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
         }

         ::double_polygon polygon;

         ::double_rectangle rectangle(100, 100, 200, 200);

         polygon = rectangle;

         glBegin(GL_QUADS);


         vertex2f(polygon, 0.f);

         glEnd();

      }
#endif // SHOW_DEBUG_DRAWING

   }


   //context::context()
   //{
   //   m_fboID = 0;
   //   m_bMesa = false;

   //   //m_emode = e_mode_system;

   //   m_estatus = error_not_initialized;

   //}


   //context::~context()
   //{

   //}


   //bool context::is_mesa()
   //{

   //   return m_bMesa;

   //}


   void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size)
   {

      if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         //if (startcontext.m_callbackImage32CpuBuffer
         //   && !startcontext.m_rectanglePlacement.is_empty())
         //{

         //   ASSERT(startcontext.m_callbackImage32CpuBuffer);
         //   ASSERT(!startcontext.m_rectanglePlacement.is_empty());

         create_cpu_buffer(size);

         //}

      }
      else if (eoutput == ::gpu::e_output_swap_chain)
      {

         defer_create_window_context(pwindow);

      }
      else
      {

         auto r = ::int_rectangle(::int_point{}, size);
         //         
           //       ::gpu::rear_guard guard(this);

         send([this, r]()
            {

               _create_cpu_buffer(r.size());

               //::gpu::context_guard guard(this);

            });

      }


   }


   void context::copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource)
   {

      ::gpu::context_lock contextlock(this);

      ::cast < texture > ptextureDst = ptextureTarget;

      ::cast < texture > ptextureSrc = ptextureSource;

      auto textureSrc = ptextureSrc->m_gluTextureID;

      auto textureDst = ptextureDst->m_gluTextureID;

      glFlush();

      if (!ptextureSrc->m_gluFbo)
      {

         ptextureSrc->create_render_target();

      }

      if (!ptextureDst->m_gluFbo)
      {

         ptextureDst->create_render_target();

      }

      //GLuint fboSrc, fboDst;
      //glGenFramebuffers(1, &fboSrc);
      //GLCheckError("");
      //glGenFramebuffers(1, &fboDst);
      //GLCheckError("");

      // Attach source texture to fboSrc
      glBindFramebuffer(GL_READ_FRAMEBUFFER, ptextureSrc->m_gluFbo);
      GLCheckError("");
      //glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
      //   GL_TEXTURE_2D, textureSrc, 0);
      //GLCheckError("");

      // Attach dest texture to fboDst
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ptextureDst->m_gluFbo);
      GLCheckError("");
      //glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
      //   GL_TEXTURE_2D, textureDst, 0);
      //GLCheckError("");

      auto sizeSrc = ptextureSrc->size();
      auto sizeDst = ptextureDst->size();

      // Blit from source to destination
      glBlitFramebuffer(
         0, 0, sizeSrc.cx(), sizeSrc.cy(),
         0, 0, sizeDst.cx(), sizeDst.cy(),
         GL_COLOR_BUFFER_BIT, GL_NEAREST
      );
      GLCheckError("");
#ifdef SHOW_DEBUG_DRAWING
      {

         //glBindFramebuffer(GL_FRAMEBUFFER, 0);


         glEnable(GL_BLEND);
         glBlendFunc(GL_ONE, GL_ZERO); // Source Copy mode
         //glBlendEquation(GL_FUNC_ADD); // default, can be omitted if unchanged

         {
            float fOpacity = 0.5;
            float fRed = 0.5;
            float fGreen = 0.75;
            float fBlue = 0.95;
            auto f32Opacity = (float)fOpacity;
            auto f32Red = (float)(fRed * fOpacity);
            auto f32Green = (float)(fGreen * fOpacity);
            auto f32Blue = (float)(fBlue * fOpacity);
            ::glColor4f(f32Red, f32Green, f32Blue, f32Opacity);
         }

         ::double_polygon polygon;

         ::double_rectangle rectangle(300, 300, 400, 400);

         polygon = rectangle;

         glBegin(GL_QUADS);


         vertex2f(polygon, 0.f);

         glEnd();

      }
#endif

      // Cleanup
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      //GLCheckError("");
      //glDeleteFramebuffers(1, &fboSrc);
      //GLCheckError("");
      //glDeleteFramebuffers(1, &fboDst);
      //GLCheckError("");

   }


   void context::_create_offscreen_window(const ::int_size& size)
   {

      ::cast < device_win32 > pdevice = m_pgpudevice;

      pdevice->_defer_create_offscreen_window(size);

      //if (::IsWindow(m_hwnd))
      //{

      //   if (!::SetWindowPos(m_hwnd,
      //      nullptr, 0, 0,
      //      size.cx()
      //      , size.cy(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
      //      | SWP_NOCOPYBITS | SWP_NOSENDCHANGING
      //      | SWP_NOREPOSITION | SWP_NOREDRAW))
      //   {

      //      information() << "SetWindowPos Failed";

      //   }


      //   //return m_hwnd;

      //}
      //else
      //{

      //   LPCTSTR lpClassName = L"draw2d_opengl_offscreen_buffer_window";
      //   LPCTSTR lpWindowName = L"draw2d_opengl_offscreen_buffer_window";
      //   //unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
      //   unsigned int dwExStyle = 0;
      //   unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
      //   dwStyle |= WS_POPUP;
      //   //dwStyle |= WS_VISIBLE;
      //   //dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
      //   dwStyle &= ~WS_CAPTION;
      //   //dwStyle = 0;
      //   dwStyle &= ~WS_THICKFRAME;
      //   dwStyle &= ~WS_BORDER;
      //   int x = 0;
      //   int y = 0;
      //   int nWidth = size.cx();
      //   int nHeight = size.cy();
      //   HWND hWndParent = nullptr;
      //   HMENU hMenu = nullptr;
      //   HINSTANCE hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
      //   LPVOID lpParam = nullptr;

      //   m_hwnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

      //   if (!m_hwnd)
      //   {

      //      informationf("MS GDI - CreateWindow failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   //return m_hwnd;

      //}


   }


   void context::_create_window_buffer()
   {

      ::cast < device_win32 > pdevice = m_pgpudevice;

      pdevice->_create_device(m_rectangle.size());

      //if (!m_hdc || !m_hrc)
      //{

      //   ::cast < device > pgpudevice = m_pgpudevice;

      //   ::cast < approach > pgpuapproach = pgpudevice->m_pgpuapproach;

      //   if (!pgpuapproach->m_atomClass)
      //   {

      //      informationf("MS GDI - RegisterClass failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   // create WGL context, make current

      //   PIXELFORMATDESCRIPTOR pixformat;

      //   int chosenformat;

      //   HDC hdc = GetDC(m_hwnd);

      //   if (!hdc)
      //   {

      //      informationf("MS GDI - GetDC failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   zero(pixformat);
      //   pixformat.nSize = sizeof(pixformat);
      //   pixformat.nVersion = 1;
      //   pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      //   pixformat.iPixelType = PFD_TYPE_RGBA;
      //   pixformat.cColorBits = 32;
      //   pixformat.cRedShift = 16;
      //   pixformat.cGreenShift = 8;
      //   pixformat.cBlueShift = 0;
      //   pixformat.cAlphaShift = 24;
      //   pixformat.cAlphaBits = 8;
      //   pixformat.cDepthBits = 24;
      //   pixformat.cStencilBits = 8;

      //   chosenformat = ChoosePixelFormat(hdc, &pixformat);

      //   if (chosenformat == 0)
      //   {

      //      informationf("MS GDI - ChoosePixelFormat failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

      //   if (!spfok)
      //   {

      //      informationf("MS GDI - SetPixelFormat failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   HGLRC hglrc = wglCreateContext(hdc);

      //   if (!hglrc)
      //   {

      //      informationf("MS WGL - wglCreateContext failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

      //   if (!bMakeCurrentOk)
      //   {

      //      informationf("MS WGL - wglMakeCurrent failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      ReleaseDC(m_hwnd, hdc);

      //      throw ::exception(error_failed);

      //   }

      //   pgpuapproach->defer_init_gpu_library();

      //   auto pszVersion = (const char*)glGetString(GL_VERSION);
      //   //::e_status estatus = 

      //   ::string strVersion(pszVersion);

      //   if (strVersion.case_insensitive_contains("mesa"))
      //   {

      //      m_bMesa = true;

      //   }

      //   //if (!estatus)
      //   //{

      //   //   ReleaseDC(window, hdc);

      //   //   return estatus;

      //   //}

      //   m_hwnd = m_hwnd;
      //   m_hdc = hdc;
      //   m_hrc = hglrc;

      //}

      //RECT rectClient;

      //::GetClientRect(m_hwnd, &rectClient);

      //m_size = { rectClient.right - rectClient.left,
      //   rectClient.bottom - rectClient.top };

      //get_renderer()->set_placement({ 0, 0, m_size.cx(), m_size.cy() });

      //m_itaskGpu = ::current_itask();

      //m_estatus = ::success;

      //set_ok_flag();

   }


   void context::_create_window_context(::windowing::window* pwindowParam)
   {

      //   ::cast < ::windowing_win32::window > pwindow = pwindowParam;

      //   if (!m_hdc || !m_hrc)
      //   {

      //      ::cast < approach > pgpuapproach = m_pgpudevice->m_pgpuapproach;

      //      //if (!popengl->m_atomClass)
      //      //{

      //      //   informationf("MS GDI - RegisterClass failed");

      //      //   informationf("last-error code: %d\n", GetLastError());

      //      //   throw ::exception(error_failed);

      //      //}

      //      if (!m_hwnd)
      //      {

      //         auto hwnd = pwindow->m_hwnd;


      //         m_hwnd = hwnd;


      //         //// create WGL context, make current

      //         //PIXELFORMATDESCRIPTOR pixformat;

      //         //int chosenformat;

      //         HDC hdc = GetDC(m_hwnd);

      //         //if (!hdc)
      //         //{

      //         //   informationf("MS GDI - GetDC failed");

      //         //   informationf("last-error code: %d\n", GetLastError());

      //         //   throw ::exception(error_failed);

      //         //}

      //         //zero(pixformat);
      //         //pixformat.nSize = sizeof(pixformat);
      //         //pixformat.nVersion = 1;
      //         //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      //         //pixformat.iPixelType = PFD_TYPE_RGBA;
      //         //pixformat.cColorBits = 32;
      //         //pixformat.cRedShift = 16;
      //         //pixformat.cGreenShift = 8;
      //         //pixformat.cBlueShift = 0;
      //         //pixformat.cAlphaShift = 24;
      //         //pixformat.cAlphaBits = 8;
      //         //pixformat.cDepthBits = 24;
      //         //pixformat.cStencilBits = 8;

      //         //chosenformat = ChoosePixelFormat(hdc, &pixformat);

      //         //if (chosenformat == 0)
      //         //{

      //         //   informationf("MS GDI - ChoosePixelFormat failed");

      //         //   informationf("last-error code: %d\n", GetLastError());

      //         //   ReleaseDC(m_hwnd, hdc);

      //         //   throw ::exception(error_failed);

      //         //}

      //         //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

      //         //if (!spfok)
      //         //{

      //         //   informationf("MS GDI - SetPixelFormat failed");

      //         //   informationf("last-error code: %d\n", GetLastError());

      //         //   ReleaseDC(m_hwnd, hdc);

      //         //   throw ::exception(error_failed);

      //         //}

      //         auto hglrc = wglCreateContext(hdc);

      //         pwindow->m_hglrcProto = hglrc;

      //         //         int context_attribs[] = {
      //         //WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
      //         //WGL_CONTEXT_MINOR_VERSION_ARB, 1,
      //         //0, 0
      //         //         };
      //         //         auto hglrc = wglCreateContextAttribsARB(hdc, NULL, context_attribs);
      //         //         if (!hglrc) {
      //         //            //ReleaseDC(hWnd, hDC);
      //         //            //DestroyWindow(hWnd);

      //         //            throw ::exception(error_failed);
      //         //         }
      //         //         //ReleaseDC(hWnd, hDC);

      //         if (!pwindow->m_hglrcProto)
      //         {

      //            informationf("MS WGL - wglCreateContext failed");

      //            informationf("last-error code: %d\n", GetLastError());

      //            ReleaseDC(m_hwnd, hdc);

      //            throw ::exception(error_failed);

      //         }

      //         auto hglrcProto = pwindow->m_hglrcProto;

      //         bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrcProto);

      //         if (!bMakeCurrentOk)
      //         {

      //            informationf("MS WGL - wglMakeCurrent failed");

      //            informationf("last-error code: %d\n", GetLastError());

      //            ReleaseDC(m_hwnd, hdc);

      //            throw ::exception(error_failed);

      //         }

      //         m_pgpudevice->m_pgpuapproach->defer_init_gpu_library();

      //         auto pszVersion = (const char*)glGetString(GL_VERSION);
      //         //::e_status estatus = 

      //         ::string strVersion(pszVersion);

      //         if (strVersion.case_insensitive_contains("mesa"))
      //         {

      //            m_bMesa = true;

      //         }

      //         //if (!estatus)
      //         //{

      //         //   ReleaseDC(window, hdc);

      //         //   return estatus;

      //         //}

      //         m_hwnd = m_hwnd;
      //         m_hdc = hdc;
      //         m_hrc = pwindow->m_hglrcProto;

      //         wglMakeCurrent(nullptr, nullptr);

      //      }

      //   }

      //   RECT rectClient;

      //   ::GetClientRect(m_hwnd, &rectClient);

      //   ::int_size sizeNew = { rectClient.right - rectClient.left,
      //rectClient.bottom - rectClient.top };

      //   if (m_size != sizeNew)
      //   {
      //      m_size = sizeNew;

      //      m_sizeHost = sizeNew;
      //      //HDC pdcDIB;                      // контекст устройства в памяти
      //      //HBITMAP hbmpDIB;                 // и его текущий битмапvoid *pBitsDIB(NULL);            // содержимое битмапаint cxDIB(200); int cyDIB(300);  // его размеры (например для окна 200х300)
      //      //auto &BIH=pwindow->m_bitmapinfoheaderProto;            // и заголовок// …// создаем DIB section// создаем структуру BITMAPINFOHEADER, описывающую наш DIBint iSize = sizeof(BITMAPINFOHEADER);  // размер
      //      //memset(&BIH, 0, sizeof(pwindow->m_bitmapinfoheaderProto));

      //      //BIH.biSize = sizeof(pwindow->m_bitmapinfoheaderProto);        // размер структуры
      //      //BIH.biWidth = m_size.cx();       // геометрия
      //      //BIH.biHeight = m_size.cy();      // битмапа
      //      //BIH.biPlanes = 1;          // один план
      //      //BIH.biBitCount = 32;       // 24 bits per pixel
      //      //BIH.biCompression = BI_RGB;// без сжатия// создаем новый DC в памяти
      //      ////pdcDIB = CreateCompatibleDC(NULL);
      //      ////void * pBits = nullptr;
      //      //// создаем DIB-секцию
      //      //pwindow->m_hbitmapProto = CreateDIBSection(
      //      //  m_hdc,                  // контекст устройства
      //      //  (BITMAPINFO *)&BIH,       // информация о битмапе
      //      //  DIB_RGB_COLORS,          // параметры цвета
      //      //  &pwindow->m_pbitsProto,               // местоположение буфера (память выделяет система)
      //      //  NULL,                    // не привязываемся к отображаемым в память файлам
      //      //  0);

      //      //// выберем новый битмап (DIB section) для контекста устройства в памяти
      //      //SelectObject(m_hdc, pwindow->m_hbitmapProto);
      //      //pwindow->m_hdcProto = m_hdc;
      //   }

      //   m_itaskGpu = ::current_itask();

      //   m_estatus = ::success;

      //   set_ok_flag();

   }


   void context::_create_cpu_buffer(const ::int_size& size)
   {

      _create_offscreen_window(size);

      _create_window_buffer();

   }


   void context::defer_create_window_context(::windowing::window* pwindow)
   {

      //if (m_hrc)
      //{

      //   return;

      //}

      //::gpu_opengl::context::defer_create_window_context(pwindow);

   }


   void context::_defer_create_window_context(::windowing::window* pwindow)
   {

      //_create_window_context(pwindow);

   }


   void context::resize_cpu_buffer(const ::int_size& sizeParam)
   {

      //if (m_papplication->m_bUseSwapChainWindow)
      {

         // return;

      }

      auto size(sizeParam);

      send([this, size]()
         {
            //if (!m_pcpubuffer)

            create_cpu_buffer(size);

            ::gpu::context_lock contextlock(this);
            ///m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

      //#ifdef WINDOWS_DESKTOP
      //
      //      ::SetWindowPos(m_hwnd, 0, 0, 0, size.cx(), size.cy(), SWP_NOZORDER | SWP_NOMOVE | SWP_HIDEWINDOW);
      //
      //#else

      //      destroy_offscreen_buffer();
      //
      //      if(!create_offscreen_buffer(size))
      //      {
      //
      //         return error_failed;
      //
      //      }

      //#endif

            //make_current();

            glViewport(0, 0, size.cx(), size.cy());
            //glMatrixMode(GL_PROJECTION);
            //glLoadIdentity();
            //glOrtho(0, size.cx(), 0, size.cy(), -10, 10);
            //glMatrixMode(GL_MODELVIEW);
            //glutPostRedisplay();

            //return ::success;
         });


   }


   void context::defer_make_current()
   {

      if (m_pgpudevice->m_pgpucontextCurrent4 != this)
      {

         if (::is_set(m_pgpudevice->m_pgpucontextCurrent4))
         {

            m_pgpudevice->m_pgpucontextCurrent4->_send([this]()
               {

                  ///m_pgpudevice->release_current(m_pgpudevice->m_pgpucontextCurrent4);

               });

         }

         //make_current();

      }

   }


   //xxxopengl
   //void context::make_current()
   //{

   //   ::gpu::context::make_current();

   //   update_framebuffer(m_rectangle.size());

   //   if (m_pframebuffer)
   //   {

   //      m_pframebuffer->bind();

   //   }
   //   else if(m_eoutput == ::gpu::e_output_swap_chain)
   //   {
   //      
   //      // If using swap chain, no need to bind framebuffer

   //      GLint drawFboId = 0, readFboId = 0;

   //      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
   //      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

   //      if (drawFboId != 0)
   //      {

   //         glBindFramebuffer(GL_FRAMEBUFFER, 0);

   //         glViewport(0, 0, m_rectangle.width(), m_rectangle.height());

   //      }

   //   }

   //   //pgpudevice->m_pgpucontextCurrent = this;

   //   //glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

   //   //return estatus;

   //}


   ////xxxopengl
   //void context::release_current()
   //{

   //   ::gpu::context::release_current();

   //}


   void context::_context_lock()
   {

      ::cast < device > pdevice = m_pgpudevice;

      pdevice->_opengl_lock();

   }


   void context::_context_unlock()
   {

      ::cast < device > pdevice = m_pgpudevice;

      pdevice->_opengl_unlock();

   }


   void context::destroy_cpu_buffer()
   {

      ::cast < device_win32 > pgpudevice = m_pgpudevice;

      if (pgpudevice->m_itaskCurrentGpuContext != ::current_itask())
      {

         ASSERT(false);

      }

      m_pframebuffer.release();

      //::e_status estatus = ::success;

      //::glDeleteFramebuffers(1, &m_fboID);

   }


   //void context::render()
   //{

   //   ::gpu_opengl::context::render();

   //}


   //void context::swap_buffers()
   //{

   //   SwapBuffers(m_hdc);

   //}


   string context::get_shader_version_text()
   {

      return "#version 330 core";

   }


   void context::_translate_shader(string_array& stra)
   {

      ::gpu::context::_translate_shader(stra);

      character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");

      if (iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

   }


   ::memory context::rectangle_shader_vert()
   {
      const char proto_vert[] = R"vert(
#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec4 inColor;

out vec4 fragColor;

void main() {
    gl_Position = vec4(inPos, 0.0, 1.0);
    fragColor = inColor;
})vert";

      return ::as_memory_block(proto_vert);

   }


   ::memory context::rectangle_shader_frag()
   {

      const char proto_frag[] = R"frag(
            #version 330 core

               in vec4 fragColor;      // Input from the vertex shader (location = 0)
            out vec4 outColor;      // Output to framebuffer (location = 0)

            void main() {
               outColor = fragColor;
            }
)frag";

      return ::as_memory_block(proto_frag);

   }


} // namespace gpu_opengl



