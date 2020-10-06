#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA palette :
      virtual public ::draw2d::object
   {
   public:



      palette();
      virtual ~palette();


      virtual bool CreatePalette(LPLOGPALETTE pLogPalette);

      virtual bool CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics);


      virtual i32 GetEntryCount();
      virtual UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors) const;

      virtual UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors);



// Operations


      virtual void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors);

      virtual UINT GetNearestPaletteIndex(COLORREF crColor) const;
      virtual bool ResizePalette(UINT nNumEntries);


   };


   typedef ___pointer < palette > palette_pointer;


} // namespace draw2d



