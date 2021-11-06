#pragma once


#include "acme/_start.h"


#include "aura/_.h"


#include "aura/operating_system.h"


#include "aura/gpu/gpu/_.h"


#ifdef _GPU_OPENGL_STATIC
#define CLASS_DECL_GPU_OPENGL
#elif defined(_GPU_OPENGL_LIBRARY)
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_IMPORT
#endif


#ifdef _UWP


// Enable function definitions in the GL headers below
#define GL_GLEXT_PROTOTYPES


// OpenGL ES includes
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>


#elif defined(LINUX)


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


//#include <OpenGL/gl.h>
//#include <OpenGL/gl3.h>
//#include <OpenGL/CGLTypes.h>
//#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
//#include <OpenGL/gl.h>


#else


#include <gl/glew.h>
#include <gl/gl.h>


#endif


#include "buffer.h"

#include "context.h"

#include "shader.h"
#include "program.h"

#include "opengl.h"



