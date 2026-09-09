#include <windows.h>
#include <gdiplus.h>
#include <set>
#include <string>
#include <cstdio>
static std::set<std::wstring> names;
static int CALLBACK enumerate(const LOGFONTW * font, const TEXTMETRICW *, DWORD kind, LPARAM)
{
   if ((kind & TRUETYPE_FONTTYPE) && font->lfFaceName[0] != L'@') names.insert(font->lfFaceName);
   return 1;
}
int main()
{
   Gdiplus::GdiplusStartupInput input;
   ULONG_PTR token;
   if (Gdiplus::GdiplusStartup(&token, &input, nullptr) != Gdiplus::Ok) return 1;
   HDC dc = CreateCompatibleDC(nullptr);
   LOGFONTW font = {};
   font.lfCharSet = DEFAULT_CHARSET;
   EnumFontFamiliesExW(dc, &font, enumerate, 0, 0);
   DeleteDC(dc);
   int failures = 0;
   for (const auto & name : names)
   {
      Gdiplus::FontFamily family(name.c_str());
      Gdiplus::Font regular(&family, 24.f, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
      const auto familyStatus = family.GetLastStatus();
      const auto fontStatus = regular.GetLastStatus();
      if (familyStatus != Gdiplus::Ok || fontStatus != Gdiplus::Ok)
      {
         ++failures;
         std::wprintf(L"FAIL %ls: family=%d regular=%d\n", name.c_str(), familyStatus, fontStatus);
      }
      else if (name <= L"Arial") std::wprintf(L"OK %ls\n", name.c_str());
   }
   std::printf("%zu families, %d failures\n", names.size(), failures);
   Gdiplus::GdiplusShutdown(token);
}
