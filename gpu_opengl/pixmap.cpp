// From bred/gpu/pixmap.cpp by
//  camilo on 2025-07-01 14:39 <3ThomasBorregaardSørensen!!
#include "framework.h"
//#include "pixmap.h"
//
//
//namespace gpu_opengl
//{
//
//
//   pixmap::pixmap()
//   {
//
//   }
//
//
//   pixmap::~pixmap()
//   {
//
//   }
//
//
//   void pixmap::initialize_gpu_pixmap(::gpu::renderer* pgpurenderer, const ::int_size& m_size)
//   {
//
//      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//      // generate texture
//         //unsigned int texture;
//      glGenTextures(1, &m_gluTexture);
//      glBindTexture(GL_TEXTURE_2D, m_gluTexture); // You must bind before setting parameters
//
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//
//   }
//
//
//   void pixmap::set_pixels(const void* data, int w, int h)
//   {
//
//      glBindTexture(GL_TEXTURE_2D, m_gluTexture);
//
//      glTexImage2D(
//         GL_TEXTURE_2D,
//         0,
//         GL_BGRA,
//         w,
//         h,
//         0,
//         GL_BGRA,
//         GL_UNSIGNED_BYTE,
//         data
//      );
//      
//      glBindTexture(GL_TEXTURE_2D, 0);
//
//   }
//
//
//   void pixmap::bind_texture(::gpu::shader* pgpushader)
//   {
//
//      glBindTexture(GL_TEXTURE_2D, m_gluTexture);
//      GLCheckError("");
//
//   }
//
//   
//   void pixmap::unbind_texture(::gpu::shader* pgpushader)
//   {
//
//      glBindTexture(GL_TEXTURE_2D, 0);
//      GLCheckError("");
//
//   }
//
//
//} // namespace character
//
//
