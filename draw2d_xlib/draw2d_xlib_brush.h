#pragma once


namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB brush :
      virtual public ::draw2d::brush
   {
   public:



//xxx      Gdiplus::Brush * m_pbrush;

      color    m_color;


      brush(::layered * pobjectContext);
      //virtual void construct(COLORREF crColor);                // CreateSolidBrush
      //virtual void construct(i32 nIndex, COLORREF crColor);    // CreateHatchBrush
      //virtual void construct(::draw2d::bitmap * pbitmap);                // CreatePatternBrush
      virtual ~brush();


      virtual void * get_os_data() const;


      //bool CreateSolidBrush(COLORREF crColor);
      //bool CreateHatchBrush(i32 nIndex, COLORREF crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      //bool CreateSysColorBrush(i32 nIndex);


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_xlib

