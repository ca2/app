// Created by camilo on 2025-06-15 18:15 <3ThomasBorregaardSørensen!!
#pragma once



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



CLASS_DECL_GPU_OPENGL const char* opengl_error_string(int iError);



#define GLCheckError(message) \
{ \
int iGlError = glGetError(); \
if (iGlError != 0) \
{ \
   ::opengl::throw_opengl_exception(message, iGlError, __FILE__, __LINE__); \
} \
}



namespace opengl
{


   class CLASS_DECL_GPU_OPENGL exception :
      virtual public ::exception
   {
   public:


      int m_iGlError;


      exception(const ::scoped_string& scopestrMessage, int iGLError, const char * pszGlErrorMessage, const ::scoped_string & nameFile, int iLine);

      ~exception() override;
      
   };


   [[noreturn]] CLASS_DECL_GPU_OPENGL void throw_opengl_exception(const ::scoped_string& scopestrMessage, int iGLError, const ::scoped_string& nameFile, int iLine);




   CLASS_DECL_GPU_OPENGL GLenum get_gpu_type_unit_opengl_type(::gpu::enum_type etype);



} // namespace opengl


CLASS_DECL_GPU_OPENGL void defer_throw_gl_error();
