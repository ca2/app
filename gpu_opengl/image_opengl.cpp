#include "framework.h"
#include "aura/operating_system.h"
#include "aura/graphics/draw2d/image.h"
#ifdef WINDOWS_DESKTOP
#include <gl/glew.h>
#include <gl/gl.h>
#endif


CLASS_DECL_GPU_OPENGL void image_gl_set(image * pimage)
{

   unsigned char* data = (unsigned char *) pimage->m_pcolorrefRaw;

   if (data)
   {

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pimage->m_size.cx, pimage->m_size.cy, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

      glGenerateMipmap(GL_TEXTURE_2D);

   }

}



