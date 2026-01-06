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


#elif defined(LINUX) || defined(__BSD__)


//#define __GPU_OPENGL_USE_EGL

#define __GPU_OPENGL_USE_GLAD


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
#include <glad/glad.h>

// OpenGL ES includes
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


//#include <GL/gl.h>


// apt install libosmesa6-dev
// dnf install mesa-libOSMesa-devel
///#define GLAPI extern
//#include <GL/osmesa.h>
//#include <GL/glx.h>

// Ubuntu  libglfw3-dev
//#include <GLFW/glfw3.h>

// Ubuntu : 	libglu1-mesa-dev
//#include <GL/glu.h>
 
#endif


#elif defined(MACOS)


//#include <glad.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/gl3.h>
////#include <OpenGL/CGLTypes.h>
////#include <OpenGL/glu.h>
////#include <OpenGL/gl3.h>
//#include <OpenGL/glext.h>
//#include <OpenGL/gl.h>

#define GLAD_GLAPI_EXPORT
#include <glad/glad.h>
//#include <OpenGL/CGLTypes.h>


#elif defined(WINDOWS_DESKTOP)


//#include <gl/glew.h>
//#include <gl/gl.h>
#ifndef GLAD_GLAPI_EXPORT
#define GLAD_GLAPI_EXPORT
#endif
#include <glad/glad.h>


#else


#error "Not yet supported OpenGL include"

#endif



CLASS_DECL_GPU_OPENGL const_char_pointer opengl_error_string(int iError);


CLASS_DECL_GPU_OPENGL void GLCheckError(const_char_pointer pszErrorMessage);


CLASS_DECL_GPU_OPENGL void GLEnsureNonNullHandle(long lHandle, const_char_pointer pszMessage = nullptr);


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL exception :
      virtual public ::exception
   {
   public:


      int m_iGlError;


      exception(const ::scoped_string& scopestrMessage, int iGLError, const_char_pointer pszGlErrorMessage, const ::scoped_string & nameFile, int iLine);

      ~exception() override;
      
   };


   [[noreturn]] CLASS_DECL_GPU_OPENGL void throw_opengl_exception(const ::scoped_string& scopestrMessage, int iGLError, const ::scoped_string& nameFile, int iLine);




   CLASS_DECL_GPU_OPENGL GLenum get_gpu_type_unit_opengl_type(::gpu::enum_type etype);

   CLASS_DECL_GPU_OPENGL GLenum as_gl_draw_mode(::gpu::enum_topology etopology);

   CLASS_DECL_GPU_OPENGL const char * check_framebuffer_status_text(GLenum status);


} // namespace opengl


CLASS_DECL_GPU_OPENGL void defer_throw_gl_error();
