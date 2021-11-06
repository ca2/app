#include "framework.h"
#include "_.h"


namespace opengl
{


   context::context()
   {

      m_emode = e_mode_none;

   }


   context::~context()
   {

   }


   //::e_status context::initialize(::object * pobject)
   //{

   //   ::e_status estatus = ::object::initialize(pobject);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   ::e_status context::draw()
   {

      if (m_VAO != 0)
      {

         return ::success;

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

//#ifdef __APPLE__
//
//      glGenVertexArraysAPPLE(1, &m_VAO);
//      glGenBuffers(1, &m_VBO);
//      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//      glBindVertexArrayAPPLE(m_VAO);
//
//#else

      glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
      glBindVertexArray(m_VAO);

//#endif

      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      // color attribute
      //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
      //glEnableVertexAttribArray(1);

      return ::success;
   }


   ::e_status context::start()
   {

      glClearColor(0.2f, 0.3f, 0.3f, 0.3f);

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

      return ::success;

   }


   ::e_status context::render()
   {

//#ifdef __APPLE__

      //glBindVertexArrayAPPLE(m_VAO);

//#else

      glBindVertexArray(m_VAO);

//#endif

      glDrawArrays(GL_TRIANGLES, 0, 6);

      return ::success;

   }


   //::e_status context::create_offscreen_buffer(const ::size_i32& size)
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


   //::e_status context::_create_offscreen_buffer(const ::size_i32& size)
   //{

   //   return ::success_none;

   //}


   //::e_status context::resize_offscreen_buffer(const ::size_i32& size)
   //{

   //   return ::success_none;

   //}



   //::e_status context::make_current()
   //{

   //   return ::success_none;

   //}


   //::e_status context::destroy_offscreen_buffer()
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
//      auto & app = papplication;
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



