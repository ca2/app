#pragma once


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

      index find_first(UINT user);

      glyph * GetGlyph(UINT user);


   };


} // namespace draw2d


