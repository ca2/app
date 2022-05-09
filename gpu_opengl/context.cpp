#include "framework.h"
#include "_.h"
#include "aura/graphics/image/image.h"


namespace opengl
{


   context::context()
   {

      m_emode = e_mode_none;
      m_itaskGpu = 0;
      m_iLastBitmap1Scan = -1;

      m_gluTextureBitmap1 = 0;
      m_VAO = 0;
      m_VBO = 0;

   }


   context::~context()
   {

   }


   //void context::initialize(::object * pobject)
   //{

   //   ::e_status estatus = ::object::initialize(pobject);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   void context::draw()
   {

      ASSERT(m_itaskGpu == ::get_current_itask());

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
      
      glGenVertexArraysAPPLE(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArrayAPPLE(m_VAO);

//#elif defined(ANDROID)
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


   void context::start()
   {

      ASSERT(m_itaskGpu == ::get_current_itask());

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

      glClear(GL_COLOR_BUFFER_BIT);

      if (m_pprogram && m_pprogram->m_pshader)
      {

         m_pprogram->m_pshader->use();

      }

      // be sure to activate the shader
      //glUseProgram(shaderProgram);

      // update the uniform color
      //float timeValue = glfwGetTime();
      //float greenValue = sin(timeValue) / 2.0f + 0.5f;
      //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      //return ::success;

   }


   void context::render()
   {

      ASSERT(m_itaskGpu == ::get_current_itask());

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
         glBlitFramebuffer(0, 0, m_sizeBitmap1.cx, m_sizeBitmap1.cy,
            0, 0, m_size.cx, m_size.cy,
            GL_COLOR_BUFFER_BIT, GL_LINEAR);
         glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
         glDeleteFramebuffers(1, &readFboId);
      }
      else
      {

         glBindVertexArray(m_VAO);

         //#endif

         glDrawArrays(GL_TRIANGLES, 0, 6);

      }

      //return ::success;

   }


   void context::set_bitmap_1(::image * pimage)
   {

      ASSERT(m_itaskGpu == ::get_current_itask());

      if (!m_gluTextureBitmap1)
      {

         glGenTextures(1, &m_gluTextureBitmap1); // generate texture id for your texture (can skip this line)
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, m_gluTextureBitmap1);

         glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set alignment of data in memory (a good thing to do before glTexImage)
         
#if defined(__APPLE__) || defined(ANDROID)
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // set clamp (GL_CLAMP_TO_EDGE would be better)
#else
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // set clamp (GL_CLAMP_TO_EDGE would be better)
#endif
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // set linear filtering (so you can scale your image)

      }

      if (::is_ok(pimage))
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

         vertical_swap_copy_colorref_swap_red_blue(
            (color32_t *) m_memorySwap.get_data(),
            m_sizeBitmap1.cx,
            m_sizeBitmap1.cy,
            m_sizeBitmap1.cx * 4,
            pimage->get_data(),
            pimage->m_iScan);

         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            m_sizeBitmap1.cx,
            m_sizeBitmap1.cy,
            0, GL_RGBA, GL_UNSIGNED_BYTE,
            m_memorySwap.get_data()); // upload image data to the textur


         


      }

   }


   void context::swap_buffers()
   {


   }



   //void context::create_offscreen_buffer(const ::size_i32& size)
   //{

   //   auto pgpu = psystem->get_gpu();

   //   if (::is_null(pgpu))
   //   {

   //      return ::error_failed;

   //   }

   //   ::e_status estatus = __construct(m_pbuffer);

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


   //void context::_create_offscreen_buffer(const ::size_i32& size)
   //{

   //   return ::success_none;

   //}


   //void context::resize_offscreen_buffer(const ::size_i32& size)
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
         "float base_res = min(resolution.x, resolution.y);\n"
         "vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / base_res;\n"
         "\n"
         //"gl_FragColor = vec4(uv, (uv.x * uv.x) / 2.0, ((uv.x + (base_res - uv.y)) *(uv.x + (base_res - uv.y))) / 2.0);\n"
         "float posx = max(0.f, uv.x);\n"
         "float posy = max(0.f, uv.y);\n"
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
//      if (strExtension.begins_ci("shadertoy"))
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

   //   strsize iFind = stra.find_first_begins_ci("#version ");

   //   if (iFind >= 0)
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



} // namespace opengl



