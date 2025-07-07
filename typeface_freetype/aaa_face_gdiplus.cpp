// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "face_gdiplus.h"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

bool g_bGdiplusInitialized = false;
ULONG_PTR g_gdiplusToken;
void defer_initialize_gdiplus()
{

   if (g_bGdiplusInitialized)
   {

      return;

   }

   g_bGdiplusInitialized = true;

   GdiplusStartupInput gdiplusStartupInput;

   GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, nullptr);


}


namespace typeface_freetype
{



   // Converts a 32bpp bitmap into an 8bpp grayscale buffer
   memory ExtractGrayscaleFromBitmap(Bitmap& bmp) {
      int width = bmp.GetWidth();
      int height = bmp.GetHeight();

      memory grayBuffer(width * height);

      BitmapData data;
      Rect rect(0, 0, width, height);
      bmp.LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &data);

      BYTE* src = static_cast<BYTE*>(data.Scan0);

      for (int y = 0; y < height; ++y) {
         BYTE* row = src + y * data.Stride;
         for (int x = 0; x < width; ++x) {
            BYTE b = row[x * 4 + 0];
            BYTE g = row[x * 4 + 1];
            BYTE r = row[x * 4 + 2];
            BYTE a = row[x * 4 + 3];

            // Premultiplied alpha correction (optional)
            if (a > 0) {
               r = r * 255 / a;
               g = g * 255 / a;
               b = b * 255 / a;
            }

            BYTE gray = static_cast<BYTE>(0.299 * r + 0.587 * g + 0.114 * b);
            grayBuffer[y * width + x] = gray;
         }
      }

      bmp.UnlockBits(&data);
      return grayBuffer;
   }

   //memory RenderGlyphTo8BitGray(wchar_t ch, int width = 64, int height = 64) 
   //{

   //   //// Display as ASCII art (debugging purpose)
   //   //for (int y = 0; y < height; ++y) {
   //   //   for (int x = 0; x < width; ++x) {
   //   //      BYTE value = grayscale[y * width + x];
   //   //      putchar(value > 128 ? '#' : (value > 32 ? '+' : '.'));
   //   //   }
   //   //   putchar('\n');
   //   //}

   //   //GdiplusShutdown(gdiplusToken);

   //   return grayscale;
   //}

   face_gdiplus::face_gdiplus()
   {

      //m_bFace = false;

      m_pfont = nullptr;
      m_pfamily = nullptr;


   }


   face_gdiplus::~face_gdiplus()
   {

      ::acme::del(m_pfont);
      ::acme::del(m_pfamily);

   }

   void face_gdiplus::create_character(::gpu::character& ch, const ::scoped_string& scopedstr)
      //Character& face_freetype::get_character(const ::scoped_string& scopedstr)
   {

      if (!m_pfamily || !m_pfont)
      {

         defer_initialize_gdiplus();
         //m_bFace = true;
         //return ch;
         m_pfamily = new FontFamily(::wstring(m_strFontName));
         //FontFamily* m_pfamily(L"Segoe UI");
         m_pfont = new Font(m_pfamily, m_iPixelSize, FontStyleRegular, UnitPixel);

         create_draw_buffers();

      }

      int fontSize = m_iPixelSize;
      wd32_character ia[2];
      ia[0] = unicode_index(scopedstr);
      ia[1] = 0;
      WCHAR wch[5];
      auto len = wd32_to_wd16(wch, ia);
      wch[len] = L'\0';
      // Use a temporary Graphics to measure the glyph
      HDC screenDC = GetDC(NULL);
      Graphics measureGraphics(screenDC);
      measureGraphics.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);

      RectF layoutRect;
      PointF origin(0, 0);
      
      measureGraphics.MeasureString(wch, 1, m_pfont, origin, &layoutRect);
      ReleaseDC(NULL, screenDC);

      int bmpWidth = static_cast<int>(ceil(layoutRect.Width)) + 4;   // padding
      int bmpHeight = static_cast<int>(ceil(layoutRect.Height)) + 4;

      Bitmap bmp(bmpWidth, bmpHeight, PixelFormat32bppARGB);
      Graphics g(&bmp);
      g.SetSmoothingMode(SmoothingModeAntiAlias);
      g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
      g.Clear(Color(0, 0, 0, 0)); // Transparent background

      SolidBrush brush(Color(255, 255, 255, 255)); // Black text

      // Draw glyph at (2, 2) for margin
      PointF drawPoint(2.0f, 2.0f);
      g.DrawString(wch, 1, m_pfont, drawPoint, &brush);

      // Lock pixels
      BitmapData data;
      Rect rect(0, 0, bmpWidth, bmpHeight);
      bmp.LockBits(&rect, ImageLockModeRead, PixelFormat32bppPARGB, &data);

      //memory pre;
      //pre.set_size(bmpWidth * bmpHeight*4);
      //BYTE* src = static_cast<BYTE*>(data.Scan0);

      //for (int y = 0; y < bmpHeight; ++y) {
      //   BYTE* row = src + y * data.Stride;
      //   for (int x = 0; x < bmpWidth; ++x) {
      //      BYTE b = row[x * 4 + 0];
      //      BYTE g = row[x * 4 + 1];
      //      BYTE r = row[x * 4 + 2];
      //      BYTE a = row[x * 4 + 3];

      //      //if (a > 0) {
      //        // r = r * 255 / a;
      //         //g = g * 255 / a;
      //         //b = b * 255 / a;
      //      //}

      //      BYTE luminance = static_cast<BYTE>(0.299 * r + 0.587 * g + 0.114 * b);
      //      gray.data()[y * bmpWidth + x] = luminance;
      //   }
      //}

      

      // Measure metrics (bearing and advance)
      HDC hdc = GetDC(NULL);
      HFONT hFont = CreateFontW(
         static_cast<int>(-fontSize), 0, 0, 0, FW_NORMAL,
         FALSE, FALSE, FALSE, DEFAULT_CHARSET,
         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
         DEFAULT_PITCH | FF_DONTCARE, ::wstring(m_strFontName));

      SelectObject(hdc, hFont);

      ABC abc;
      GetCharABCWidthsW(hdc, wch[0], wch[0], &abc);

      TEXTMETRIC tm;
      GetTextMetrics(hdc, &tm);

      int bearingX = abc.abcA;
      int bearingY = tm.tmAscent; // baseline to top
      int advance = abc.abcA + abc.abcB + abc.abcC;

      DeleteObject(hFont);
      ReleaseDC(NULL, hdc);

      // now store character for later use
      //aracter = {
        //  texture,
      ch.Size = glm::ivec2(bmpWidth, bmpHeight);
      ch.Bearing = glm::ivec2(bearingX, bearingY);
      ch.Advance = advance;


      create_texture(ch,  (const unsigned char *) data.Scan0);
      bmp.UnlockBits(&data);
      //};
      //Characters.insert(std::pair<char, Character>(c, character));
   //}

      
      //Bitmap bmp(bmpWidth, bmpHeight, PixelFormat32bppARGB);
      //Graphics g(&bmp);
      //g.SetSmoothingMode(SmoothingModeAntiAlias);
      //g.Clear(Color(255, 255, 255, 255)); // white background

      //SolidBrush brush(Color(255, 0, 0, 0)); // black text

      //PointF origin(0, 0);
      //g.DrawString(wch, 1, m_pfont, origin, &brush);

      //auto grayscale = ExtractGrayscaleFromBitmap(bmp);


   }


}// namespace typeface_freetype


