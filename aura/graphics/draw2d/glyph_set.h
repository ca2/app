#pragma once


#include "glyph.h"


namespace draw2d
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


} // namespace draw2d


