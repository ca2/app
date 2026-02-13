//
// Created by camilo on 2025-12-25 20:20 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_gpu_opengl.h"
#include "device_egl.h"
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>


namespace gpu_opengl
{


   void device_egl::__egl_x11_swap_buffers(void * pDisplay, long lWindow)
   {

      eglSwapBuffers(m_egldisplay, nullptr);

   }


} // namespace gpu_opengl



