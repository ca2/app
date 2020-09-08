#pragma once
//
//#ifdef _UWP
//
//// Enable function definitions in the GL headers below
//#define GL_GLEXT_PROTOTYPES
//
//// OpenGL ES includes
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//
//// EGL includes
//#include <EGL/egl.h>
//#include <EGL/eglext.h>
//#include <EGL/eglplatform.h>
//
//#elif defined(LINUX)
//
//
//// Enable function definitions in the GL headers below
//#define GL_GLEXT_PROTOTYPES 1
//
//// Ubuntu : libglew-dev
//#include <GL/glew.h> // added for GL_VERTEX_SHADER
////#define GL_GLEXT_PROTOTYPES 1
////#include <GLES/gl.h>
////#include <GLES/glext.h>
//
//
//
//// OpenGL ES includes
////#include <GLES2/gl2.h>
////#include <GLES2/gl2ext.h>
//
////#include <GL/gl.h>
//
//
//// Ubuntu :    libosmesa6-dev
//#define GLAPI extern
//#include <GL/osmesa.h>
////#include <GL/glx.h>
//
//// Ubuntu  libglfw3-dev
////#include <GLFW/glfw3.h>
//
//// Ubuntu : 	libglu1-mesa-dev
////#include <GL/glu.h>
//
#include <glm/glm.hpp>
//
//
//#else
//
//#include <gl/glew.h>
//#include <gl/gl.h>
//#include <glm/glm.hpp>
//
//#endif

namespace gpu
{

   class buffer;
   class context;
   class shader;
   class program;
   class opengl;

} // gpu

#include "buffer.h"
#include "program.h"
#include "shader.h"
#include "context.h"

#include "approach.h"



