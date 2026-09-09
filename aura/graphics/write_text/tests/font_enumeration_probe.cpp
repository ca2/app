#include <windows.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <cstdio>
#include <set>
#include <string>

using Microsoft::WRL::ComPtr;
struct probe
{
   ComPtr<IDWriteFontCollection> collection;
   ComPtr<IDWriteGdiInterop> interop;
   std::set<std::wstring> families;
   unsigned retained = 0, excluded = 0, unresolvedRetained = 0;
};

static std::wstring substitute(std::wstring family)
{
   // Match the provider's charset-suffixed FontSubstitutes lookup.
   for (int depth = 0; depth < 16; ++depth)
   {
      std::wstring replacement;
      for (HKEY root : {HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE})
      {
         HKEY key = nullptr;
         if (RegOpenKeyExW(root, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\FontSubstitutes",
                           0, KEY_READ, &key) != ERROR_SUCCESS) continue;
         for (DWORD i = 0;; ++i)
         {
            wchar_t name[1024]{}, value[1024]{};
            DWORD names = 1024, bytes = sizeof(value), type = 0;
            if (RegEnumValueW(key, i, name, &names, nullptr, &type,
                              reinterpret_cast<BYTE *>(value), &bytes) != ERROR_SUCCESS) break;
            std::wstring base(name);
            base = base.substr(0, base.find(L','));
            if (type == REG_SZ && _wcsicmp(base.c_str(), family.c_str()) == 0)
            {
               replacement = value;
               replacement = replacement.substr(0, replacement.find(L','));
               break;
            }
         }
         RegCloseKey(key);
         if (!replacement.empty()) break;
      }
      if (replacement.empty() || _wcsicmp(replacement.c_str(), family.c_str()) == 0) break;
      family = replacement;
   }
   return family;
}

static int CALLBACK enumerate(const LOGFONTW *lf, const TEXTMETRICW *, DWORD type, LPARAM data)
{
   auto &p = *reinterpret_cast<probe *>(data);
   if (lf->lfFaceName[0] == L'@' || !p.families.insert(lf->lfFaceName).second)
      return 1;
   const bool supported = (type & TRUETYPE_FONTTYPE) && !(type & RASTER_FONTTYPE);
   supported ? ++p.retained : ++p.excluded;
   UINT32 index = 0;
   BOOL exists = FALSE;
   ComPtr<IDWriteFont> font;
   const auto resolved = substitute(lf->lfFaceName);
   if (SUCCEEDED(p.collection->FindFamilyName(resolved.c_str(), &index, &exists)) && exists)
   {
      ComPtr<IDWriteFontFamily> family;
      if (SUCCEEDED(p.collection->GetFontFamily(index, &family)))
         family->GetFirstMatchingFont(DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                                     DWRITE_FONT_STYLE_NORMAL, &font);
   }
   else
   {
      LOGFONTW requested{};
      requested.lfWeight = FW_NORMAL;
      requested.lfCharSet = DEFAULT_CHARSET;
      wcscpy_s(requested.lfFaceName, resolved.c_str());
      p.interop->CreateFontFromLOGFONT(&requested, &font);
   }
   if (!supported || !font)
      std::wprintf(L"%ls: type=%lu %ls DWrite=%ls\n", lf->lfFaceName, type,
                   supported ? L"retained" : L"excluded", font ? L"resolved" : L"UNRESOLVED");
   if (supported && !font)
      ++p.unresolvedRetained;
   return 1;
}

int main()
{
   ComPtr<IDWriteFactory> factory;
   probe p;
   if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                  reinterpret_cast<IUnknown **>(factory.GetAddressOf()))) ||
       FAILED(factory->GetSystemFontCollection(&p.collection, TRUE)) ||
       FAILED(factory->GetGdiInterop(&p.interop)))
      return 2;
   HDC dc = CreateCompatibleDC(nullptr);
   if (!dc) return 3;
   EnumFontFamiliesW(dc, nullptr, enumerate, reinterpret_cast<LPARAM>(&p));
   DeleteDC(dc);
   std::printf("Retained=%u Excluded=%u Unresolved retained=%u\n",
               p.retained, p.excluded, p.unresolvedRetained);
   return p.unresolvedRetained ? 1 : 0;
}
