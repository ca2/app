// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSørensen!!
#pragma once


#include "aura/_.h"
#include "aura/gpu/gpu/_.h"


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


#if defined(_gpu_opengl_project)
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_IMPORT
#endif


#ifdef ANDROID


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


#elif defined(LINUX) || defined(FREEBSD)


// Enable function definitions in the GL headers below
#define GL_GLEXT_PROTOTYPES 1


// apt install libglew-dev
// dnf install glew-devel
#include <GL/glew.h> // added for GL_VERTEX_SHADER
//#define GL_GLEXT_PROTOTYPES 1
//#include <GLES/gl.h>
//#include <GLES/glext.h>


// OpenGL ES includes
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


//#include <GL/gl.h>


// apt install libosmesa6-dev
// dnf install mesa-libOSMesa-devel
#define GLAPI extern
#include <GL/osmesa.h>
//#include <GL/glx.h>

// Ubuntu  libglfw3-dev
//#include <GLFW/glfw3.h>

// Ubuntu : 	libglu1-mesa-dev
//#include <GL/glu.h>

//#include <glm/glm.hpp>


#elif defined(MACOS)


#include <OpenGL/gl.h>
//#include <OpenGL/gl3.h>
//#include <OpenGL/CGLTypes.h>
//#include <OpenGL/glu.h>
//#include <OpenGL/gl3.h>
//#include <OpenGL/glext.h>
//#include <OpenGL/gl.h>


#else


//#include <gl/glew.h>
//#include <gl/gl.h>
#define GLAD_GLAPI_EXPORT
#include <glad.h>
CLASS_DECL_GPU_OPENGL const char * opengl_error_string(int iError);


#endif



