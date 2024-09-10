#include "framework.h"
#include "aura/graphics/image/image.h"


#include "acme/_operating_system.h"


#ifdef WINDOWS_DESKTOP
//#include <gl/glew.h>
//#include <gl/gl.h>
#include <glad.h>
#endif


CLASS_DECL_GPU_OPENGL void image_gl_set(::image::image *pimage)
{

   unsigned char* data = (unsigned char *) pimage->m_pimage32Raw;

   if (data)
   {

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pimage->m_size.cx(), pimage->m_size.cy(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

      glGenerateMipmap(GL_TEXTURE_2D);

   }

}



