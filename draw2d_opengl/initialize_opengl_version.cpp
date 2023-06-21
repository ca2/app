// Created by camilo on 2023-40-27 16:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "acme/exception/resource.h"
//
//
//#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
//#include "acme/_operating_system.h"
////#include "glad.h"
//#define GLAD_GLAPI_EXPORT
//#include "glad_wgl.h"
////#include <GL/gl.h>
////#include <GL/glu.h>
////#include <GL/glext.h>
////#include <GL/wglext.h>
//
////#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
////#define WGL_CONTEXT_MINOR_VERSION_ARB 0X2092
////#define WGL_CONTEXT_FLAGS_ARB 0X2094
////#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
////#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
////typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int * attribList);
//
////typedef const char * (WINAPI * PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
////typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int);
////typedef int (WINAPI * PFNWGLGETSWAPINTERVALEXTPROC) (void);
//
//
//HGLRC initialize_opengl_version(HDC hdc, int iMajor, int iMinor)
//{
//
//   // Init GLFW
//   //glfwInit();
//   // ... <snip> ... setup a window and a context
//
//   // Load all OpenGL functions using the glfw loader function
//   // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
//   //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//   //   std::cout << "Failed to initialize OpenGL context" << std::endl;
//   //   return -1;
//   //}
//   if (!gladLoadWGL(hdc))
//   {
//      // Problem: glewInit failed, something is seriously wrong.
//      information("gladLoadWGL failed");
//      //return false;
//      throw resource_exception();
//
//      return nullptr;
//
//   }
//   int attribs[] =
//   {
//      WGL_CONTEXT_MAJOR_VERSION_ARB, iMajor,
//      WGL_CONTEXT_MINOR_VERSION_ARB, iMinor,
//      WGL_CONTEXT_FLAGS_ARB, 0,
//      WGL_CONTEXT_PROFILE_MASK_ARB,
//      WGL_CONTEXT_COREPROFILE_BIT_ARB, 0};
//
//   //PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
//   //wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
//
//   return wglCreateContextAttribsARB(hdc, 0, attribs);
//
//}