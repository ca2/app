// From draw2d component by camilo on 2022-08-28 16:58 <3ThomasBorregaardSorensen!!
#pragma once


#include "glyph.h"


namespace write_text
{


   class glyph_set :
      public array<glyph, glyph &>
   {
   public:



      glyph_set();
      virtual ~glyph_set();


      virtual index add(glyph & glyph);

      void quick_sort();

      index find_first(::u32 user);

      glyph * GetGlyph(::u32 user);


   };


} // namespace write_text


