// Created by camilo on 2026-01-06 21:18 <3ThomasBorregaardSørensen!!
#pragma once


namespace typeface_fontconfig
{


   class CLASS_DECL_TYPEFACE_FREETYPE typeface : virtual public ::typeface::typeface
   {
   public:


      typeface();
      ~typeface() override;


      virtual ::file::path get_font_file_path_by_font_name(const ::scoped_string &scopedstr);


   };

} // namespace typeface_fontconfig

            FcPattern *pat = FcNameParse((FcChar8 *)m_strFontName.c_str());
FcConfigSubstitute(NULL, pat, FcMatchPattern);
FcDefaultSubstitute(pat);

FcResult result;
FcPattern *font = FcFontMatch(NULL, pat, &result);

FcChar8 *file;
FcPatternGetString(font, FC_FILE, 0, &file);

if (file)
{

   path = (const char *)file;
