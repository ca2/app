// From draw2d component by camilo on 2022-08-28 16:58 <3ThomasBorregaardSorensen!!
#pragma once


#include "glyph.h"


namespace write_text
{


   class glyph_set :
      public pointer_array<glyph>
   {
   public:



      glyph_set();
      virtual ~glyph_set();


      virtual ::collection::index add(glyph * pglyph);

      void quick_sort();

      ::collection::index find_first(unsigned int user);

      glyph * GetGlyph(unsigned int user);


   };


} // namespace write_text


