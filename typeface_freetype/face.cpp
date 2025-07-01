// Created by camilo (from https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp
// with interaction with v0idsEmbrace in twitch chat)
// on 2025-06-01 22:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "face.h"
#include "bred/gpu/pixmap.h"
#include "acme/filesystem/filesystem/file_context.h"


#ifdef WINDOWS_DESKTOP
#pragma comment( lib, "freetype.lib" )
#endif


// FreeType
// --------
FT_Library g_freetype;
bool g_bFreeTypeInitialized = false;
void defer_initialize_freetype()
{
   if (!g_bFreeTypeInitialized)
   {
      g_bFreeTypeInitialized = true;

      // All functions return a value different than 0 whenever an error occurred
      if (FT_Init_FreeType(&g_freetype))
      {
         error() << "ERROR::FREETYPE: Could not init FreeType Library";
         throw ::exception(error_failed, "Could not init FreeType Library");
      }

   }
}


namespace typeface_freetype
{

   face::face()
   {

      m_bFace = false;
      m_face = nullptr;
      //m_FaceVAO = 0;
      //m_FaceVBO = 0;

   }

   face::~face()
   {

      if (m_face)
      {
         FT_Done_Face(m_face);
      }


   }


   void face::create_character(::typeface::character& ch, const ::scoped_string& scopedstr)
      //Character& face::get_character(const ::scoped_string& scopedstr)
   {

      if (!m_bFace)
      {
         m_bFace = true;
         //return ch;

         defer_initialize_freetype();

         auto m = file()->as_memory("matter://font/truetype/Roboto-Regular.ttf");
         // Roboto - Regular.ttf
            // load font as face

         if (FT_New_Memory_Face(g_freetype, m.data(), m.size(), 0, &m_face))
         {
            error() << "ERROR::FREETYPE: Failed to load font";
            throw ::exception(error_failed, "Failed to load font");
         }

         create_draw_buffers();

      }

      FT_Set_Pixel_Sizes(m_face, 0, 48);
      if (FT_Load_Char(m_face, unicode_index(scopedstr), FT_LOAD_RENDER))
      {
         warning() << "ERROR::FREETYTPE: Failed to load Glyph";
         return;
      }


      ch.Size.x = m_face->glyph->bitmap.width;
      ch.Size.y = m_face->glyph->bitmap.rows;

      create_texture(ch, m_face->glyph->bitmap.buffer);

      //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      //// generate texture
      //   //unsigned int texture;
      //glGenTextures(1, &ch.TextureID);
      //glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      //glTexImage2D(
      //   GL_TEXTURE_2D,
      //   0,
      //   GL_RED,
      //   m_face->glyph->bitmap.width,
      //   m_face->glyph->bitmap.rows,
      //   0,
      //   GL_RED,
      //   GL_UNSIGNED_BYTE,
      //   m_face->glyph->bitmap.buffer
      //);
      //// set texture options
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //// now store character for later use
      ////aracter = {
      //  //  texture,
      ch.Size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
      ch.Bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
      ch.Advance = static_cast<unsigned int>(m_face->glyph->advance.x);
//      //};
//      //Characters.insert(std::pair<char, Character>(c, character));
//   //}
//      glBindTexture(GL_TEXTURE_2D, 0);
//      //}
////else {
//
//      //// find path to font
//      //std::string font_name = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
//      //if (font_name.empty())
//      //{
//      //   std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
//      //   return -1;
//      //}
//
//      //// load font as face
//      //FT_Face face;
//      //if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
//      //   std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//      //   return -1;
//      //}
//      //else {
//      //   // set size to load glyphs as
//      //   FT_Set_Pixel_Sizes(face, 0, 48);
//
//      //   // disable byte-alignment restriction
//      //   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//      //   // load first 128 characters of ASCII set
//      //   for (unsigned char c = 0; c < 128; c++)
//      //   {
//      //      // Load character glyph 
//      //      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//      //      {
//      //         std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//      //         continue;
//      //      }
//      //      // generate texture
//      //      unsigned int texture;
//      //      glGenTextures(1, &texture);
//      //      glBindTexture(GL_TEXTURE_2D, texture);
//      //      glTexImage2D(
//      //         GL_TEXTURE_2D,
//      //         0,
//      //         GL_RED,
//      //         face->glyph->bitmap.width,
//      //         face->glyph->bitmap.rows,
//      //         0,
//      //         GL_RED,
//      //         GL_UNSIGNED_BYTE,
//      //         face->glyph->bitmap.buffer
//      //      );
//      //      // set texture options
//      //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//      //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//      //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//      //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//      //      // now store character for later use
//      //      Character character = {
//      //          texture,
//      //          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//      //          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//      //          static_cast<unsigned int>(face->glyph->advance.x)
//      //      };
//      //      Characters.insert(std::pair<char, Character>(c, character));
//      //   }
//      //   glBindTexture(GL_TEXTURE_2D, 0);
//      //}
//      //// destroy FreeType once we're finished
//      //FT_Done_Face(face);
//      //FT_Done_FreeType(ft);
//
//
//      //return ch;

   }


} // namespace typeface_freetype



