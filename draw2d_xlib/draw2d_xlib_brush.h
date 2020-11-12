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
      //virtual void construct(color32_t crColor);                // CreateSolidBrush
      //virtual void construct(i32 nIndex, color32_t crColor);    // CreateHatchBrush
      //virtual void construct(::draw2d::bitmap * pbitmap);                // CreatePatternBrush
      virtual ~brush();


      virtual void * get_os_data() const;


      //bool CreateSolidBrush(color32_t crColor);
      //bool CreateHatchBrush(i32 nIndex, color32_t crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, ::u32 nUsage);
      //bool CreateSysColorBrush(i32 nIndex);


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_xlib

