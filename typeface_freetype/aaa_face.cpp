// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:22 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "face.h"


namespace typeface_freetype
{


   face::face()
   {

      m_FaceVAO = 0;
      m_FaceVBO = 0;

   }

   face::~face()
   {



   }


   //::draw2d_gpu::character& face::get_character(const ::scoped_string& scopedstr)
   //{

   //   ::string str(scopedstr);

   //   character& ch = m_mapCharacter[str];

   //   if (ch.m_bInit)
   //   {

   //      return ch;

   //   }
   //   ch.m_bInit = true;
   //   ch.m_iUnicode = unicode_index(scopedstr);
   //   create_character(ch, scopedstr);
   //   return ch;

   //}


   void face::create_character(::gpu::character& ch, const ::scoped_string& scopedstr)
   {

   }

   void face::create_draw_buffers()
   {
      glGenVertexArrays(1, &m_FaceVAO);
      GLCheckError("");
      glGenBuffers(1, &m_FaceVBO);
      GLCheckError("");
      glBindVertexArray(m_FaceVAO);
      GLCheckError("");
      glBindBuffer(GL_ARRAY_BUFFER, m_FaceVBO);
      GLCheckError("");
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
      GLCheckError("");
      glEnableVertexAttribArray(0);
      GLCheckError("");
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
      GLCheckError("");
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      GLCheckError("");
      glBindVertexArray(0);
      GLCheckError("");

   }

   void face::create_texture(::gpu::character& ch, const unsigned char* p)
   {

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      // generate texture
         //unsigned int texture;
      glGenTextures(1, &ch.TextureID);
      glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      glTexImage2D(
         GL_TEXTURE_2D,
         0,
         GL_BGRA,
         ch.Size.x,
         ch.Size.y,
         0,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         p
      );
      // set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glBindTexture(GL_TEXTURE_2D, 0);


   }

} // namespace typeface_freetype


