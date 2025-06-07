// From gpu_opengl::device by
// camilo on 2025-05-27 06:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "device.h"
#include "program.h"
#include "shader.h"
#include "aura/graphics/image/image.h"
#include "glm/mat4x4.hpp"


namespace gpu_opengl
{

#ifdef WINDOWS_DESKTOP

   ::pointer <::gpu::context > allocate_system_context(::particle* pparticle);

#elif defined(__APPLE__)

#if 1

   ::pointer <::gpu::context > allocate_fbo_context(::particle* pparticle);

#else

   ::pointer <::gpu::context > allocate_cgl_context(::particle* pparticle);

#endif

#else

   ::pointer <::gpu::context > allocate_egl_context(::particle* pparticle);

   //::pointer <::gpu::context > allocate_glx_context(::particle * pparticle);

#endif


   device::device()
   {

      //m_emode = e_mode_none;
      ////m_itaskGpu = 0;
      //m_iLastBitmap1Scan = -1;

      //m_gluTextureBitmap1 = 0;
      //m_VAO = 0;
      //m_VBO = 0;

   }


   device::~device()
   {

   }



   bool device::make_current(::gpu::context* pgpucontext)
   {

      return ::gpu::device::make_current(pgpucontext);

   }


   void device::_swap_buffers()
   {


   }


   void device::release_current(::gpu::context* pgpucontext)
   {

      ::gpu::device::release_current(pgpucontext);

   }

   //void device::initialize(::particle * pparticle)
   //{

   //   ::e_status estatus = ::object::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


//   void device::draw()
//   {
//
//      ASSERT(m_itaskGpu == ::current_itask());
//
//      if (m_VAO != 0)
//      {
//
//         //return ::success;
//         return;
//
//      }
//      //glGenBuffers(1, &VAO);
////      float vertices[] = {
//         // positions         // colors
//  //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
//      //    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
//      //};
//      float vertices[] = {
//         // first triangle
//          1.f,  1.f, 0.0f,  // top right
//          1.f, -1.f, 0.0f,  // bottom right
//         -1.f,  1.f, 0.0f,  // top left
//         // second triangle
//          1.f, -1.f, 0.0f,  // bottom right
//         -1.f, -1.f, 0.0f,  // bottom left
//         -1.f,  1.f, 0.0f   // top left
//      };
//
//#if defined(__APPLE__)
//
//      glGenVertexArrays(1, &m_VAO);
//      glGenBuffers(1, &m_VBO);
//      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//      glBindVertexArray(m_VAO);
//
//      //#elif defined(__ANDROID__)
//      //
//      //      glGenVertexArrays(1, &m_VAO);
//      //      glGenBuffers(1, &m_VBO);
//      //      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//      //      glBindVertexArray(m_VAO);
//
//#else
//
//      glGenVertexArrays(1, &m_VAO);
//      glGenBuffers(1, &m_VBO);
//      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//      glBindVertexArray(m_VAO);
//
//#endif
//
//      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//      // position attribute
//      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//      glEnableVertexAttribArray(0);
//      // color attribute
//      //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//      //glEnableVertexAttribArray(1);
//
//      //return ::success;
//   }
//
//
//   void device::start_drawing()
//   {
//
//
//      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_elements);
////int iError16 = glGetError();
//
////int size = 0; 
////glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
////int iError17 = glGetError();
//
////glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
////int iError18 = glGetError();
//
//
//
//
//      ASSERT(m_itaskGpu == ::current_itask());
//
//      //      glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//
//            // Clear the screen
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//      //glClear(GL_COLOR_BUFFER_BIT);
//
//      if (m_pshader)
//      {
//
//         m_pshader->bind();
//
//      }
//      // Use our shader
//      //glUseProgram(programID);
//
//      // be sure to activate the shader
//      //glUseProgram(shaderProgram);
//
//      // update the uniform color
//      //float timeValue = glfwGetTime();
//      //float greenValue = sin(timeValue) / 2.0f + 0.5f;
//      //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//      //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
//      //return ::success;
//
//   }
//
//
//
//   void device::global_transform()
//   {
//
//
//      // Get a handle for our "MVP" uniform
//      //GLint MatrixID = glGetUniformLocation(programID, "MVP");
//
//      if (m_iMatrixUniform >= 0)
//      {
//
//         // Compute the MVP matrix from keyboard and mouse input
//         //computeMatricesFromInputs();
//         ::glm::mat4 matrixProjection = (::glm::mat4&)projection_matrix();
//         ::glm::mat4 matrixView = (::glm::mat4&)view_matrix();
//         ::glm::mat4 matrixModel = glm::mat4(1.0);
//         ::glm::mat4 matrixMVP = matrixProjection * matrixView * matrixModel;
//
//         // Send our transformation to the currently bound shader, 
//         // in the "MVP" uniform
//         glUniformMatrix4fv(m_iMatrixUniform, 1, GL_FALSE, &matrixMVP[0][0]);
//
//      }
//
//      //glm::mat4 getViewMatrix() {
//      //   return ViewMatrix;
//      //}
//      //glm::mat4 getProjectionMatrix() {
//      //   return ProjectionMatrix;
//      //}
//
//
//      //// Initial position : on +Z
//      //glm::vec3 position = glm::vec3(0, 0, 5);
//      //// Initial horizontal angle : toward -Z
//      //float horizontalAngle = 3.14f;
//      //// Initial vertical angle : none
//      //float verticalAngle = 0.0f;
//      //// Initial Field of View
//      //float initialFoV = 45.0f;
//
//      //float speed = 3.0f; // 3 units / second
//      //float mouseSpeed = 0.005f;
//
//
//
//   }
//
//
//   void device::render()
//   {
//
//      ASSERT(m_itaskGpu == ::current_itask());
//
//      //#ifdef __APPLE__
//
//            //glBindVertexArrayAPPLE(m_VAO);
//
//      //#else
//
//      if (m_gluTextureBitmap1)
//      {
//
//         //glMatrixMode(GL_PROJECTION);
//         //glOrtho(0, 800, 0, 600, -1, 1);
//         // glMatrixMode(GL_MODELVIEW);
//
//         //clear and draw quad with texture (could be in display callback)
//         //glClear(GL_COLOR_BUFFER_BIT);
//         //glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);
//         ////glEnable(GL_TEXTURE_2D);
//         //glBegin(GL_QUADS);
//         //glTexCoord2i(0, 0); glVertex2f(-1.0, -1.0);
//         //glTexCoord2i(0, 1); glVertex2f(-1.0, 1.0);
//         //glTexCoord2i(1, 1); glVertex2f(1.0, 1.0);
//         //glTexCoord2i(1, 0); glVertex2f(1.0, -1.0);
//         //glEnd();
//         //glDisable(GL_TEXTURE_2D);
//         //glBindTexture(GL_TEXTURE_2D, 0);
//         //glFlush();
//
//         GLuint readFboId = 0;
//         glGenFramebuffers(1, &readFboId);
//         glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
//         glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//            GL_TEXTURE_2D, m_gluTextureBitmap1, 0);
//         glBlitFramebuffer(0, 0, m_sizeBitmap1.cx(), m_sizeBitmap1.cy(),
//            0, 0, m_size.cx(), m_size.cy(),
//            GL_COLOR_BUFFER_BIT, GL_LINEAR);
//         glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
//         glDeleteFramebuffers(1, &readFboId);
//      }
//      else
//      {
//
//#ifdef __APPLE__
//         glBindVertexArrayAPPLE(m_VAO);
//#else
//         glBindVertexArray(m_VAO);
//#endif
//
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//
//      }
//
//      //return ::success;
//
//   }
//
//
//   void device::set_bitmap_1(::image::image* pimage)
//   {
//
//      ASSERT(m_itaskGpu == ::current_itask());
//
//      if (!m_gluTextureBitmap1)
//      {
//
//         glGenTextures(1, &m_gluTextureBitmap1); // generate texture id for your texture (can skip this line)
//         glEnable(GL_TEXTURE_2D);
//         glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);
//
//         glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set alignment of data in memory (a good thing to do before glTexImage)
//
//#if defined(__APPLE__) || defined(__ANDROID__)
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // set clamp (GL_CLAMP_TO_EDGE would be better)
//#else
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // set clamp (GL_CLAMP_TO_EDGE would be better)
//#endif
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // set linear filtering (so you can scale your image)
//
//      }
//
//      if (pimage->is_ok())
//      {
//
//         pimage->map();
//
//         glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);
//
//         if (m_iLastBitmap1Scan != pimage->m_iScan)
//         {
//
//            m_iLastBitmap1Scan = pimage->m_iScan;
//
//            glPixelStorei(GL_UNPACK_ROW_LENGTH, pimage->m_iScan / 4);
//
//         }
//
//         m_sizeBitmap1 = pimage->size();
//
//
//         m_memorySwap.set_size(m_sizeBitmap1.area() * 4);
//
//         //vertical_swap_copy_image32_swap_red_blue(
//         ((image32_t*)m_memorySwap.data())->vertical_swap_copy_swap_red_blue(
//            m_sizeBitmap1.cx(),
//            m_sizeBitmap1.cy(),
//            m_sizeBitmap1.cx() * 4,
//            pimage->get_data(),
//            pimage->m_iScan);
//
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//            m_sizeBitmap1.cx(),
//            m_sizeBitmap1.cy(),
//            0, GL_RGBA, GL_UNSIGNED_BYTE,
//            m_memorySwap.data()); // upload image data to the textur
//
//
//
//
//
//      }
//
//   }
//
//
//   void device::swap_buffers()
//   {
//
//
//   }
//


   //void device::create_offscreen_buffer(const ::int_size& size)
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


   //void device::_create_offscreen_buffer(const ::int_size& size)
   //{

   //   return ::success_none;

   //}


   //void device::resize_offscreen_buffer(const ::int_size& size)
   //{

   //   return ::success_none;

   //}



   //void device::make_current()
   //{

   //   return ::success_none;

   //}


   //void device::destroy_offscreen_buffer()
   //{

   //   return ::success_none;

   //}


   //string device::_001GetIntroProjection()
   //{

   //   string strVersion = get_shader_version_text();


   //   string strProjection =
   //      "layout(location = 0) in vec3 aPos;\n"
   //      "out vec3 ourPosition;\n"
   //      "\n"
   //      "void main()\n"
   //      "{\n"
   //      "   gl_Position = vec4(aPos, 1.0);\n"
   //      "   ourPosition = aPos;\n"
   //      "}\n";

   //   return strProjection;
   //}


   //string device::_001GetIntroFragment()
   //{

   //   string strVersion = get_shader_version_text();

   //   string strFragment =
   //      "uniform vec2 resolution;\n"
   //      "uniform float time;\n"
   //      "uniform vec2 mouse;\n"
   //      "uniform sampler2D backbuffer;\n"
   //      "\n"
   //      "void main(void) {\n"
   //      "float base_res = min(resolution.x(), resolution.y());\n"
   //      "vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / base_res;\n"
   //      "\n"
   //      //"gl_FragColor = vec4(uv, (uv.x() * uv.x()) / 2.0, ((uv.x() + (base_res - uv.y())) *(uv.x() + (base_res - uv.y()))) / 2.0);\n"
   //      "float posx = max(0.f, uv.x());\n"
   //      "float posy = max(0.f, uv.y());\n"
   //      "gl_FragColor = vec4(uv, (posx * posx) / 4.0, ((posx + posy) * (posx + posy)) / 4.0);\n"
   //      "}\n";

   //   return strFragment;

   //}

   //   string device::load_fragment(const ::string & pszPath, enum_shader & eshader)
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


      //string device::get_shader_version_text()
      //{

      //   return "version 330 core";

      //}

      //void device::translate_shader(string& strFragment)
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


      //void device::_translate_shader(string_array& stra)
      //{

      //}


   //void device::set_matrix_uniform(const ::gpu::payload& uniformMatrix)
   //{

   //   m_iMatrixUniform = uniformMatrix.m_iUniform;

   //}


   //void device::clear(const ::color::color& color)
   //{

   //   // Clear the screen 
   //   GLCheckError();
   //   //   glClearColor(0.678f, 0.847f, 0.902f, 1.0f);//
   //   glClearColor(color.f32_red(), color.f32_green(), color.f32_blue(), color.f32_opacity());//
   //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //   GLCheckError();

   //}



} // namespace gpu_opengl



