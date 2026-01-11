// Created by camilo on 2026-01-06 21:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "typeface_fontconfig.h"
#include <fontconfig/fontconfig.h>


namespace typeface_fontconfig
{


   typeface::typeface()
   {

   }


   typeface::~typeface()
   {


   }


   ::file::path typeface::_get_font_file_path_by_font_name(const ::scoped_string &scopedstrFontName)
   {

      ::file::path path;

      ::string strFontName(scopedstrFontName);

      FcPattern *pat = FcNameParse((FcChar8 *)strFontName.c_str());
      FcConfigSubstitute(NULL, pat, FcMatchPattern);
      FcDefaultSubstitute(pat);

      FcResult result;
      FcPattern *font = FcFontMatch(NULL, pat, &result);

      FcChar8 *file;
      FcPatternGetString(font, FC_FILE, 0, &file);

      if (file)
      {

         path = (const char *)file;
      }

      return path;

   }


} // namespace typeface_fontconfig


