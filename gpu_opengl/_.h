// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/_.h"


#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#endif
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


#if defined(_gpu_opengl_project)
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_IMPORT
#endif


#ifdef __ANDROID__


// OpenGL ES includes
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>


#elif defined(UNIVERSAL_WINDOWS)


// Enable function definitions in the GL headers below
#define GL_GLEXT_PROTOTYPES


// OpenGL ES includes
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>


#elif defined(LINUX) || defined(FREEBSD) || defined(OPENBSD) || defined(NETBSD)


#define __GPU_OPENGL_USE_EGL


#ifdef __GPU_OPENGL_USE_EGL

#include <GL/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
// OpenGL ES includes
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#else

// Enable function definitions in the GL headers below
#define GL_GLEXT_PROTOTYPES 1


// apt install libglew-dev
// dnf install glew-devel
///#include <GL/glew.h> // added for GL_VERTEX_SHADER
//#define GL_GLEXT_PROTOTYPES 1
//#include <GLES/gl.h>
//#include <GLES/glext.h>
//#include <glad.h>

// OpenGL ES includes
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


#include <GL/gl.h>


// apt install libosmesa6-dev
// dnf install mesa-libOSMesa-devel
///#define GLAPI extern
//#include <GL/osmesa.h>
//#include <GL/glx.h>

// Ubuntu  libglfw3-dev
//#include <GLFW/glfw3.h>

// Ubuntu : 	libglu1-mesa-dev
//#include <GL/glu.h>

//#include <glm/glm.hpp>

#endif


#elif defined(MACOS)


//#include <glad.h>
//#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
//#include <OpenGL/CGLTypes.h>
//#include <OpenGL/glu.h>
//#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
//#include <OpenGL/gl.h>


#else


//#include <gl/glew.h>
//#include <gl/gl.h>
#define GLAD_GLAPI_EXPORT
#include <glad.h>


#endif

CLASS_DECL_GPU_OPENGL const char * opengl_error_string(int iError);



#define GLCheckError() GLError::CheckError(__FILE__, __LINE__)

class GLError
{
public:


   static void CheckError(const char* file, int line)
   {

      GLenum err;

      while ((err = glGetError()) != GL_NO_ERROR)
      {

         warning() << "OpenGL error: " << err << " in " << file << " at line " << line;

      }

   }

};


namespace gpu_opengl
{


   class frame_buffer;

   class device;

#if defined(WINDOWS_DESKTOP)

   class device_win32;

#endif


} // namespace gpu_opengl


