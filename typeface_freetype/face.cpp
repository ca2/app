// Created by camilo (from https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp
// with interaction with v0idsEmbrace in twitch chat)
// on 2025-06-01 22:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "face.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "bred/platform/system.h"
#include "bred/typeface/typeface.h"

#include "aura/graphics/write_text/text_metric.h"
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


   void face::initialize(::particle * pparticle)
   {

      ::typeface::face::initialize(pparticle);

   }


   void face::create_character(::typeface::character& ch, const ::scoped_string& scopedstr)
      //Character& face::get_character(const ::scoped_string& scopedstr)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pszFontName = m_strFontName.c_str();

      if (!m_bFace)
      {
         //return ch;

         defer_initialize_freetype();

         //::file::path path;

         ::cast < ::bred::system > psystem = system();

         auto ptypeface = psystem->typeface();

         auto path = ptypeface->get_font_file_path_by_font_name(m_strFontName);

         //{

         //   FcPattern* pat = FcNameParse((FcChar8*)m_strFontName.c_str());
         //   FcConfigSubstitute(NULL, pat, FcMatchPattern);
         //   FcDefaultSubstitute(pat);

         //   FcResult result;
         //   FcPattern* font = FcFontMatch(NULL, pat, &result);

         //   FcChar8* file;
         //   FcPatternGetString(font, FC_FILE, 0, &file);

         //   if (file)
         //   {

         //      path = (const char * ) file;

         //   }
         //   else
         //   {

         //      path = "matter://font/truetype/Roboto-Regular.ttf";

         //   }

         //}

         m_memoryFace = file()->as_memory(path);
         // Roboto - Regular.ttf
            // load font as face

         if (FT_New_Memory_Face(g_freetype, m_memoryFace.data(),(FT_Long) m_memoryFace.size(), 0, &m_face))
         {
            error() << "ERROR::FREETYPE: Failed to load font";
            throw ::exception(error_failed, "Failed to load font");
         }

         //create_draw_buffers();
         m_bFace = true;

      }


      //FT_Set_Pixel_Sizes(m_face, 0, 48);
      FT_Set_Pixel_Sizes(m_face, 0, m_iPixelSize);
      if (m_iCapHeight < 0)
      {

         FT_Load_Char(m_face, 'H', FT_LOAD_RENDER);
         m_iCapHeight = (m_face->glyph->metrics.horiBearingY + 32 ) >> 6;

      }
      //auto iUnicodeIndex = unicode_index(scopedstr);

      auto iUnicodeIndex = ch.m_iUnicode;

      if (iUnicodeIndex == 32)
      {

         information("iUnicodeIndex == 32");

      }

      if (FT_Load_Char(m_face, iUnicodeIndex, FT_LOAD_RENDER))
      {
         warning() << "ERROR::FREETYTPE: Failed to load Glyph";
         return;
      }


      ch.Size.x = m_face->glyph->bitmap.width;
      ch.Size.y = m_face->glyph->bitmap.rows;

      int w = ch.Size.x;
      int h = ch.Size.y;

      ::memory memory;

      memory.set_size(w*h*4);

      auto rgba = (char *) memory.data();

      for (int y = 0; y < h; ++y)
      {
         for (int x = 0; x < w; ++x)
         {
            unsigned char a = m_face->glyph->bitmap.buffer[y * m_face->glyph->bitmap.pitch + x];
            rgba[0] = a;
            rgba[1] = a;
            rgba[2] = a;
            rgba[3] = a;
            rgba+=4;
         }
      }


      create_texture(ch, memory.data());

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
      int iAscender = m_face->size->metrics.ascender;
      int iAscender2 = (iAscender + 32) >> 6;
      int iVertAdvance = m_face->glyph->metrics.vertAdvance;
      int iVertAdvance2 = (iVertAdvance + 32) >> 6;
      int iBearingY = m_face->glyph->metrics.vertBearingY;
      int iBearingY2 = (iBearingY + 32) >> 6;

      char ch1 = *scopedstr.m_begin;

      auto bitmap_top = m_face->glyph->bitmap_top;

      ch.Size = {(int) m_face->glyph->bitmap.width, (int) m_face->glyph->bitmap.rows};
      ch.Bearing = {m_face->glyph->bitmap_left, bitmap_top};
      ch.Advance = static_cast<unsigned int>(m_face->glyph->advance.x + 32) >> 6;
      //ch.h2 = m_iPixelSize- ch.Bearing.y;
      //ch.h2 = iAscender2- ch.Bearing.y;
      //ch.h2 = iAscender2-iBearingY2;
      ch.h2 = m_iCapHeight - bitmap_top;

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



   void face::get_text_metric(::write_text::text_metric* ptextmetrics)
   {

// #include <ft2build.h>
// #include FT_FREETYPE_H
//
// void face::get_text_metric(::write_text::text_metric* pmetric)
// {
   if (!ptextmetrics)
   {
      throw ::exception(error_null_pointer);
   }

   if (!m_face)
   {
      throw ::exception(error_null_pointer);
   }

   // -----------------------------------------
   // Configuration (match GDI+ behavior)
   // -----------------------------------------

    double fontSizePt = m_iPixelSize;     // same value you passed to GDI+ Font
    double dpiY       = 96.0;             // or get from system if you prefer
   //
   // // Set character size in points (26.6 format)
   // FT_Error err = FT_Set_Char_Size(
   //    m_face,
   //    0,
   //    (FT_F26Dot6)(fontSizePt * 64.0),
   //    (FT_UInt)dpiY,
   //    (FT_UInt)dpiY
   // );

      FT_Set_Pixel_Sizes(m_face, 0, m_iPixelSize);
   // if (err)
   // {
   //    throw ::exception(error_failed);
   // }

   FT_Size_Metrics& metrics = m_face->size->metrics;

   // -----------------------------------------
   // Raw font units
   // -----------------------------------------

   double emHeight     = (double)m_face->units_per_EM;
   double cellAscent   = (double)m_face->ascender;
   double cellDescent  = (double)(-m_face->descender);
   double lineSpacing  = (double)m_face->height;

   // -----------------------------------------
   // Convert to pixels (match your math)
   // -----------------------------------------

   double ascentPx =
      fontSizePt * cellAscent * dpiY / (emHeight * 72.0 + 0.5);

   double descentPx =
      fontSizePt * cellDescent * dpiY / (emHeight * 72.0 + 0.5);

   // FreeType font height (already scaled)
   double fontHeightPx =
      metrics.height / 64.0;

   double lineSpacingPx =
      fontSizePt * lineSpacing * dpiY / (emHeight * 72.0 + 0.5);

   double effectiveLineSpacing =
      std::max(fontHeightPx, lineSpacingPx);

   // -----------------------------------------
   // Fill output
   // -----------------------------------------

   ptextmetrics->m_dAscent  = ascentPx;
   ptextmetrics->m_dDescent = descentPx;
   ptextmetrics->m_dHeight  = fontHeightPx;

   ptextmetrics->m_dInternalLeading = 0.0;

   ptextmetrics->m_dExternalLeading =
      effectiveLineSpacing - (ascentPx + descentPx);
//}

   }



} // namespace typeface_freetype



