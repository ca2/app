// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:52 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "face.h"


namespace draw2d_gpu
{


   face::face()
   {

      m_iPixelSize = -1;


   }

   face::~face()
   {



   }


   character& face::get_character(const ::scoped_string& scopedstr)
   {

      ::string str(scopedstr);

      character& ch = m_mapCharacter[str];

      if (ch.m_bInit)
      {

         return ch;

      }
      ch.m_bInit = true;
      ch.m_iUnicode = unicode_index(scopedstr);
      create_character(ch, scopedstr);
      return ch;

   }


   void face::create_character(character& ch, const ::scoped_string& scopedstr)
   {

   }

   void face::create_draw_buffers()
   {
     /* glGenVertexArrays(1, &m_VAO);
      glGenBuffers(1, &m_VBO);
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);*/

   }

   void face::create_texture(character& ch, const unsigned char* p)
   {

      //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      //// generate texture
      //   //unsigned int texture;
      //glGenTextures(1, &ch.TextureID);
      //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      //glTexImage2D(
      //   GL_TEXTURE_2D,
      //   0,
      //   GL_BGRA,
      //   ch.Size.x,
      //   ch.Size.y,
      //   0,
      //   GL_BGRA,
      //   GL_UNSIGNED_BYTE,
      //   p
      //);
      //// set texture options
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      //glBindTexture(GL_TEXTURE_2D, 0);


   }

} // namespace draw2d_gpu


