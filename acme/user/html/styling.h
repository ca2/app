#pragma once

namespace user::html
{

   enum enum_color_scheme
   {
      e_color_scheme_automatic,
      e_color_scheme_light,
      e_color_scheme_dark,
   };

   // Shared site layout and light/Nord palettes, with no required network assets.
   class CLASS_DECL_ACME styling
   {
   public:

      static void append_styles(string & strHtml);
      static void append_color_scheme(string & strHtml, enum_color_scheme ecolorscheme);

   };

} // namespace user::html
