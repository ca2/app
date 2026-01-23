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


#include <OpenGL/OpenGL.h>  // CGL types FIRST
#include <OpenGL/gl3.h>     // Core profile GL


//#include <glad.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/gl3.h>
////#include <OpenGL/CGLTypes.h>
////#include <OpenGL/glu.h>
////#include <OpenGL/gl3.h>
//#include <OpenGL/glext.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/CGLTypes.h>
//#include <OpenGL/CGLContext.h>
//#include <OpenGL/CGLCurrent.h>
//
//
//#define GLAD_GLAPI_EXPORT
//#include <glad/glad.h>
//
//
//extern "C"
//{
///*
// ** Pixel format functions
// */
//extern CGLError CGLChoosePixelFormat(const CGLPixelFormatAttribute *attribs, CGLPixelFormatObj * pix, GLint *npix);
//extern CGLError CGLDestroyPixelFormat(CGLPixelFormatObj pix);
//extern CGLError CGLDescribePixelFormat(CGLPixelFormatObj pix, GLint pix_num, CGLPixelFormatAttribute attrib, GLint *value);
//extern void CGLReleasePixelFormat(CGLPixelFormatObj pix);
//extern CGLPixelFormatObj CGLRetainPixelFormat(CGLPixelFormatObj pix);
//extern GLuint CGLGetPixelFormatRetainCount(CGLPixelFormatObj pix);
//
///*
// ** Renderer information functions
// */
//extern CGLError CGLQueryRendererInfo(GLuint display_mask, CGLRendererInfoObj * rend, GLint *nrend);
//extern CGLError CGLDestroyRendererInfo(CGLRendererInfoObj rend);
//extern CGLError CGLDescribeRenderer(CGLRendererInfoObj rend, GLint rend_num, CGLRendererProperty prop, GLint * value);
//
///*
// ** Context functions
// */
//extern CGLError CGLCreateContext(CGLPixelFormatObj pix, CGLContextObj share, CGLContextObj * ctx);
//extern CGLError CGLDestroyContext(CGLContextObj ctx);
//extern CGLError CGLCopyContext(CGLContextObj src, CGLContextObj dst, GLbitfield mask);
//extern CGLContextObj CGLRetainContext(CGLContextObj ctx);
//extern void CGLReleaseContext(CGLContextObj ctx);
//extern GLuint CGLGetContextRetainCount(CGLContextObj ctx);
//extern CGLPixelFormatObj CGLGetPixelFormat(CGLContextObj ctx);
//
///*
// ** PBuffer functions
// */
//extern CGLError CGLCreatePBuffer(GLsizei width, GLsizei height, GLenum target, GLenum internalFormat, GLint max_level, CGLPBufferObj * pbuffer);
//extern CGLError CGLDestroyPBuffer(CGLPBufferObj pbuffer);
//extern CGLError CGLDescribePBuffer(CGLPBufferObj obj, GLsizei *width, GLsizei *height, GLenum *target, GLenum *internalFormat, GLint *mipmap);
//extern CGLError CGLTexImagePBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum source);
//extern CGLPBufferObj CGLRetainPBuffer(CGLPBufferObj pbuffer);
//extern void CGLReleasePBuffer(CGLPBufferObj pbuffer);
//extern GLuint CGLGetPBufferRetainCount(CGLPBufferObj pbuffer);
//
/////*
////** Drawable Functions
////*/
////extern CGLError CGLSetOffScreen(CGLContextObj ctx, GLsizei width, GLsizei height, GLint rowbytes, void *baseaddr);
////extern CGLError CGLGetOffScreen(CGLContextObj ctx, GLsizei *width, GLsizei *height, GLint *rowbytes, void * * baseaddr);
////extern CGLError CGLSetFullScreen(CGLContextObj ctx) OPENGL_DEPRECATED(10.0, 10.6);
////extern CGLError CGLSetFullScreenOnDisplay(CGLContextObj ctx, GLuint display_mask);
//
//extern CGLError CGLSetPBuffer(CGLContextObj ctx, CGLPBufferObj pbuffer, GLenum face, GLint level, GLint screen);
//extern CGLError CGLGetPBuffer(CGLContextObj ctx, CGLPBufferObj * pbuffer, GLenum *face, GLint *level, GLint *screen);
//
//extern CGLError CGLClearDrawable(CGLContextObj ctx);
//extern CGLError CGLFlushDrawable(CGLContextObj ctx);
//
///*
// ** Per context enables and parameters
// */
//extern CGLError CGLEnable(CGLContextObj ctx, CGLContextEnable pname);
//extern CGLError CGLDisable(CGLContextObj ctx, CGLContextEnable pname);
//extern CGLError CGLIsEnabled(CGLContextObj ctx, CGLContextEnable pname, GLint *enable);
//extern CGLError CGLSetParameter(CGLContextObj ctx, CGLContextParameter pname, const GLint *params);
//extern CGLError CGLGetParameter(CGLContextObj ctx, CGLContextParameter pname, GLint *params);
//
///*
// ** Virtual screen functions
// */
//extern CGLError CGLSetVirtualScreen(CGLContextObj ctx, GLint screen);
//extern CGLError CGLGetVirtualScreen(CGLContextObj ctx, GLint *screen);
//
//extern CGLError CGLUpdateContext(CGLContextObj ctx);
//
///*
// ** Global library options
// */
//extern CGLError CGLSetGlobalOption(CGLGlobalOption pname, const GLint * params);
//extern CGLError CGLGetGlobalOption(CGLGlobalOption pname, GLint *params);
//
//extern CGLError CGLSetOption(CGLGlobalOption pname, GLint param) ;  /* Use CGLSetGlobalOption */
//extern CGLError CGLGetOption(CGLGlobalOption pname, GLint *param); /* Use CGLGetGlobalOption */
//
///*
// ** Locking functions
// */
//extern CGLError CGLLockContext(CGLContextObj ctx);
//
//extern CGLError CGLUnlockContext(CGLContextObj ctx);
//
///*
// ** Version numbers
// */
//extern void CGLGetVersion(GLint * majorvers, GLint * minorvers);
//
///*
// ** Convert an error code to a string
// */
//const char *CGLErrorString(CGLError error);
//
//} // extern "C"

//#include <OpenGL/OpenGL.h>
//#include <OpenGL/CGLTypes.h>
//#include <OpenGL/CGLContext.h>
//#include <OpenGL/CGLDevice.h>
//#include <OpenGL/CGLMacro.h>
//#include <OpenGL/CGLCurrent.h>
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/CGLMacro.h>

//#include <OpenGL/CGLTypes.h>     // CGLPixelFormatObj, CGLContextObj
//#include <OpenGL/CGLCurrent.h>   // CGLSetCurrentContext, etc (if needed)
//#include <OpenGL/CGLContext.h>
//#include <OpenGL/gl3.h>          // Core profile OpenGL
////#include <OpenGL/glext.h>

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


void gl_insert_debug_message(const_char_pointer pszMessage);


