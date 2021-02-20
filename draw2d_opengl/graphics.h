#pragma once



//struct OffscreenContext
//{
//   HWND window;
//   HDC dev_context;
//   HGLRC openGLContext;
//   int width;
//   int height;
//   //fbo_t* fbo;
//};
namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL graphics :
      virtual public ::draw2d::graphics
   {
   public:

      //::plusplus::Matrix *           m_pm;
      //::plusplus::Graphics *         m_pgraphics;
      //::plusplus::GraphicsPath *     m_ppath;
      //::plusplus::GraphicsPath *     m_ppathPaint;
      HGLRC                         m_hglrc;
      HDC                           m_hdc;
      HWND                          m_hwnd;
      ::size_i32                        m_size;
      HDC                           m_hdcGraphics;
      float                         m_z;
      point_i32                         m_pointTranslate;
      // bool                                      m_bFont;

      graphics();
      virtual ~graphics();


      //plusplus::Graphics & g()
      //{
      //   if(m_pgraphics == nullptr)
      //   {
      //      m_pgraphics = ::plusplus::Graphics::FromHDC(get_handle1());
      //   }
      //   return *m_pgraphics;
      //}
      //oswindow get_window_handle() const;
//      ::user::interaction_impl * GetWindow() const;

      virtual void thread_select();


      virtual bool attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      virtual void * detach() override;

      virtual bool Attach(HDC hdc);   // attach/detach affects only the Output DC
      virtual HDC Detach();
      virtual bool AttachPrinter(HDC hdc);
      virtual HDC DetachPrinter();
      using draw2d::graphics::fill_rectangle;
      void fill_rectangle(const rectangle_f64& rectangle, color32_t cr);


      virtual void SetAttribDC(HDC hDC);  // set the Attribute DC
      virtual void SetOutputDC(HDC hDC);  // set the Output DC
      virtual void ReleaseAttribDC();     // Release the Attribute DC
      virtual void ReleaseOutputDC();     // Release the Output DC

      bool IsPrinting() const;            // true if being used for printing

      ::draw2d::pen_pointer     get_current_pen() const;
      ::draw2d::brush_pointer   get_current_brush() const;
      ::draw2d::palette_pointer get_current_palette() const;
      ::write_text::font_pointer    get_current_font() const;
      ::draw2d::bitmap_pointer  get_current_bitmap() const;




      //plusplus::Pen *       gl2d_pen();
      //plusplus::Brush *     gl2d_brush();
      //plusplus::Font *      gl2d_font();

      // for bidi and mirrored localization
      u32 GetLayout() const;
      u32 SetLayout(u32 dwLayout);


      HDC get_hdc();
      void release_hdc(HDC hdc);


      virtual double get_dpix() const;
      virtual double get_dpiy() const;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics);

      virtual bool opengl_create_offscreen_buffer(const ::size_i32 & size);
      virtual bool opengl_delete_offscreen_buffer();

      bool DeleteDC();

      // Device-Context Functions
      virtual i32 SaveDC();
      virtual bool RestoreDC(i32 nSavedDC);
      i32 GetDeviceCaps(i32 nIndex) const;
      ::u32 SetBoundsRect(const RECTANGLE_I32 &  rectBounds, ::u32 flags);
      ::u32 GetBoundsRect(RECTANGLE_I32 * rectBounds, ::u32 flags);
      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      point_i32 GetBrushOrg() const;
      point_i32 SetBrushOrg(i32 x, i32 y);
      point_i32 SetBrushOrg(const ::point_i32 & point);
      i32 EnumObjects(i32 nObjectType,
                          i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(i32 nIndex);
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::write_text::font* SelectObject(::write_text::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      i32 SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d::object* SelectObject(::draw2d::object* pObject);
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      // color and color Palette Functions
      color32_t GetNearestColor(color32_t crColor) const;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      ::u32 RealizePalette();
      void UpdateColors();

      i32 GetPolyFillMode() const;
      i32 GetROP2() const;
      i32 GetStretchBltMode() const;

      i32 SetPolyFillMode(i32 nPolyFillMode);
      i32 SetROP2(i32 nDrawMode);
      i32 set_interpolation_mode(i32 nStretchMode);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      color32_t GetDCBrushColor() const;
      color32_t SetDCBrushColor(color32_t crColor);

      color32_t GetDCPenColor() const;
      color32_t SetDCPenColor(color32_t crColor);

#endif

      // Graphics mode
      i32 SetGraphicsMode(i32 iMode);
      i32 GetGraphicsMode() const;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,u32 iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual i32 GetMapMode() const;
      //virtual point_i32 GetViewportOrg() const;
      virtual i32 SetMapMode(i32 nMapMode);
      // Viewport Origin
      virtual point_i32 SetViewportOrg(i32 x, i32 y);
      virtual point_i32 SetViewportOrg(const ::point_i32 & point);
      virtual point_i32 OffsetViewportOrg(i32 nWidth, i32 nHeight);

      // Viewport Extent
      virtual size_i32 GetViewportExt() const;
      virtual size_i32 SetViewportExt(i32 cx, i32 cy);
      virtual size_i32 SetViewportExt(const ::size_i32 & size);
      virtual size_i32 ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Window Origin
      point_i32 GetWindowOrg() const;
      point_i32 SetWindowOrg(i32 x, i32 y);
      point_i32 SetWindowOrg(const ::point_i32 & point);
      point_i32 offset_window_org(i32 nWidth, i32 nHeight);

      // Window extent
      size_i32 GetWindowExt() const;
      virtual size_i32 set_window_ext(i32 cx, i32 cy);
      size_i32 set_window_ext(const ::size_i32 & size);
      virtual size_i32 scale_window_ext(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Coordinate Functions
      void DPtoLP(POINT_I32 * lpPoints,count nCount = 1) const;
      void DPtoLP(RECTANGLE_I32 * prectangle) const;
      void DPtoLP(LPSIZE32 LPSIZE32) const;
      void LPtoDP(POINT_I32 * lpPoints,count nCount = 1) const;
      void LPtoDP(RECTANGLE_I32 * prectangle) const;
      void LPtoDP(LPSIZE32 LPSIZE32) const;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE32 LPSIZE32) const;
      void LPtoHIMETRIC(LPSIZE32 LPSIZE32) const;
      void HIMETRICtoDP(LPSIZE32 LPSIZE32) const;
      void HIMETRICtoLP(LPSIZE32 LPSIZE32) const;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual i32 get_clip_box(RECTANGLE_I32 * prectangle) const;
      virtual bool PtVisible(i32 x, i32 y) const;
      bool PtVisible(const ::point_i32 & point) const;
      virtual bool RectVisible(const RECTANGLE_I32 &  rectangle_i32) const;
      i32 SelectClipRgn(::draw2d::region* pRgn);
      i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 ExcludeClipRect(const RECTANGLE_I32 &  rectangle_i32);
      i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 IntersectClipRect(const RECTANGLE_I32 &  rectangle_i32);
      i32 OffsetClipRgn(i32 x, i32 y);
      i32 OffsetClipRgn(const ::size_i32 & size);
      i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode);

      // Line-Output Functions
      // point_i32 GetCurrentPosition() const;
//      point_i32 MoveTo(i32 x, i32 y);
      //    point_i32 MoveTo(const ::point_i32 & point);
      virtual bool line_to(const ::point_f64 & point) override;
      //bool LineTo(int x,int y);
      //  bool LineTo(const ::point_i32 & point);
      bool polyline(const POINT_I32* lpPoints,count nCount);

      virtual bool _set(const ::draw2d::matrix & matrix) override;

      using ::draw2d::graphics::Arc;
      bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,i32 x3,i32 y3,i32 x4,i32 y4);
      bool Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);

      bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,double start, double extends);
      bool Arc(double x1,double y1,double x2,double y2,double start, double extends);

      bool AngleArc(i32 x,i32 y,i32 nRadius,float fStartAngle,float fSweepAngle);
      bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      bool ArcTo(const RECTANGLE_I32 &  rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      i32 GetArcDirection() const;
      i32 SetArcDirection(i32 nArcDirection);

      bool PolyDraw(const POINT_I32* lpPoints, const byte* lpTypes,count nCount);
      bool polyline_to(const POINT_I32* lpPoints,count nCount);
      bool poly_polyline(const POINT_I32* lpPoints, const ::i32 * lpPolyPoints,count nCount);

      bool poly_bezier(const POINT_I32* lpPoints,count nCount);
      bool poly_bezier_to(const POINT_I32* lpPoints,count nCount);

      // Simple Drawing Functions
      virtual bool fill_rectangle(const ::rectangle_i32 &  rectangle, ::draw2d::brush* pBrush) override;
      void FrameRect(const RECTANGLE_I32 &  rectangle, ::draw2d::brush* pBrush);
      //bool DrawRect(const ::rectangle_i32 & rectangle, ::draw2d::pen * ppen);
      void InvertRect(const RECTANGLE_I32 &  rectangle_i32);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon);
      bool DrawIcon(const ::point_i32 & point, ::draw2d::icon * picon);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                 i32 x4, i32 y4);
      bool Chord(const RECTANGLE_I32 &  rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      void DrawFocusRect(const RECTANGLE_I32 &  rectangle_i32);

      //bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool DrawEllipse(const RECTANGLE_I32 &  rectangle_i32);
      //bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool FillEllipse(const RECTANGLE_I32 &  rectangle_i32);

      //virtual bool DrawEllipse(double x1,double y1,double x2,double y2);
      virtual bool draw_ellipse(const ::rectangle_f64 & rectangle) override;
      //virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      virtual bool fill_ellipse(const ::rectangle_f64 & rectangle) override;

      //virtual bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      //virtual bool Pie(const RECTANGLE_I32 &  rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      virtual bool fill_polygon(const POINT_F64 * lpPoints,count nCount) override;
      virtual bool fill_polygon(const POINT_I32 * lpPoints,count nCount) override;
      virtual bool draw_polygon(const POINT_I32 * lpPoints,count nCount) override;
      virtual bool draw_polygon(const POINT_F64 * lpPoints,count nCount) override;
      virtual bool polygon_i32(const POINT_I32* lpPoints,count nCount) override;
      virtual bool polygon_i32(const POINT_F64* lpPoints,count nCount) override;
      virtual bool poly_polygon(const POINT_I32* lpPoints, const i32 * lpPolyCounts,count nCount) override;
      //virtual bool rectangle_i32(i32 x1, i32 y1, i32 x2, i32 y2) override;
      virtual bool rectangle_i32(const ::rectangle_f64 & rectangle) override;
      //virtual bool drw(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool draw_rectangle(const ::rectangle_f64 & rectangle);
      virtual bool draw_rectangle(const ::rectangle_f64& rectangle, ::draw2d::pen * ppen);
      //virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool fill_rectangle(const ::rectangle_f64 & rectangle);
      bool RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
      bool RoundRect(const RECTANGLE_I32 &  rectangle, const ::point_i32 & point);

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight);
      virtual bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc) override;
      virtual bool StretchBltRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight) override;
//      {

//         bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      color32_t GetPixel(i32 x, i32 y) const;
      color32_t GetPixel(const ::point_i32 & point) const;
      color32_t SetPixel(i32 x, i32 y, color32_t crColor);
      color32_t SetPixel(const ::point_i32 & point, color32_t crColor);
//      bool FloodFill(i32 x, i32 y, color32_t crColor);
//      bool ExtFloodFill(i32 x, i32 y, color32_t crColor, ::u32 nFillType);
//      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
//                   u32 dwRop);
//      bool PlgBlt(POINT_I32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask);
      bool SetPixelV(i32 x, i32 y, color32_t crColor);
      bool SetPixelV(const ::point_i32 & point, color32_t crColor);
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, u32 dwMode);
      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                          ::u32 clrTransparent);

      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool TextOut(i32 x, i32 y, const char * lpszString, strsize nCount);
      //virtual bool TextOut(i32 x, i32 y, const string & str);
      //virtual bool TextOut(double x, double y, const char * lpszString, strsize nCount);
      //virtual bool TextOut(double x, double y, const string & str);
      //virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const RECTANGLE_I32 &  rectangle, const char * lpszString,strsize nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const RECTANGLE_I32 &  rectangle, const string & str, LPINT lpDxWidths);
      //virtual size_i32 TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      //virtual size_i32 TabbedTextOut(i32 x, i32 y, const string & str,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      virtual bool text_out(double x, double y, const char* lpszString, strsize nCount) override;

      virtual bool draw_text(const string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      virtual bool draw_text_ex(const string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual bool draw_text(const string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      virtual bool draw_text_ex(const string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual size_f64 GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      virtual size_f64 GetTextExtent(const char * lpszString, strsize nCount) override;
      virtual size_f64 GetTextExtent(const string & str) override;
      virtual bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex);
      virtual bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount);
      virtual bool GetTextExtent(size_f64 & size, const string & str);
      virtual size_i32 GetOutputTextExtent(const char * lpszString, strsize nCount);
      virtual size_i32 GetOutputTextExtent(const string & str);
      virtual size_i32 GetTabbedTextExtent(const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size_i32 GetTabbedTextExtent(const string & str,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size_i32 GetOutputTabbedTextExtent(const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size_i32 GetOutputTabbedTextExtent(const string & str,count nTabPositions, LPINT lpnTabStopPositions);
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);
      virtual ::u32 GetTextAlign();
      virtual ::u32 SetTextAlign(::u32 nFlags);
      virtual i32 GetTextFace(count nCount, char * lpszFacename);
      virtual i32 GetTextFace(string & rString);
      virtual bool get_text_metrics(::write_text::text_metric * lpMetrics);
      virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics);
      virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      virtual i32 GetTextCharacterExtra();
      virtual i32 SetTextCharacterExtra(i32 nCharExtra);

      virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;
      virtual u32 GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      bool DrawEdge(const ::rectangle_i32 & rectangle,::u32 nEdge,::u32 nFlags);
//      bool DrawFrameControl(const ::rectangle_i32 & rectangle,::u32 nType,::u32 nState);

      // Scrolling Functions
      bool ScrollDC(i32 dx, i32 dy, const RECTANGLE_I32 &  lpRectScroll, const RECTANGLE_I32 &  lpRectClip,
                    ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate);

      // font Functions
      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      u32 SetMapperFlags(u32 dwFlag);
      size_i32 GetAspectRatioFilter() const;

      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const;
      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const;
      //u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //                         u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
                            LPABCFLOAT lpABCF) const;
      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
                        float* lpFloatBuffer) const;

      u32 GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData);
      i32 Escape(i32 nEscape, i32 nInputSize,  const char * lpszInputData,i32 nOutputSize, char * lpszOutputData);
      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData);

      // Escape helpers
      i32 StartDoc(const char * lpszDocName);  // old Win3.0 version
      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage();
      i32 EndPage();
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32));
      i32 AbortDoc();
      i32 EndDoc();

      // MetaFile Functions
      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const RECTANGLE_I32 &  lpBounds);
      bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData);
      // can be used for enhanced metafiles only

      // Path Functions
      bool AbortPath();
      bool BeginPath();
      bool CloseFigure();
      bool EndPath();
      bool FillPath();
      bool FlattenPath();
      bool StrokeAndFillPath();
      bool StrokePath();
      bool WidenPath();

      bool draw_path(::draw2d::path * ppath);
      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_path(::draw2d::path * ppath);
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      float GetMiterLimit() const;
      bool SetMiterLimit(float fMiterLimit);
      i32 GetPath(POINT_I32 * lpPoints, LPBYTE lpTypes,count nCount) const;
      bool SelectClipPath(i32 nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::layered * pobjectContext);
      void DrawDragRect(const RECTANGLE_I32 &  rectangle, const ::size_i32 & size,
                        const RECTANGLE_I32 &  lpRectLast, const ::size_i32 & sizeLast,
                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const RECTANGLE_I64 * rectangle, color32_t clr);
      //void FillSolidRect(const RECTANGLE_I32 &  rectangle, color32_t clr);
      //void FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr);
      void Draw3dRect(const RECTANGLE_I32 &  rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);




      // Implementation
   public:
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode);

      virtual bool set_smooth_mode(::draw2d::e_smooth_mode esmoothmode);

      virtual bool set_text_rendering_hint(::write_text::enum_rendering etextrendering);

      //virtual void * get_os_data() const;
      //virtual void * get_os_data_ex(int i) const;
      //virtual void release_os_data_ex(int i, void *p);
      //virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata);


      //virtual plusplus::FillMode gl2d_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rectangle_i32 & rectangle);


      virtual bool flush();
      virtual bool sync_flush();

      //virtual bool DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      //virtual bool DrawLine(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::pen * ppen);

      
      virtual bool draw_line(const point_i32& point1, const point_i32& point2, ::draw2d::pen* ppen);


      virtual void enum_fonts(::write_text::font_enum_item_array& itema) override;

      virtual bool prefer_mapped_image_on_mix();

      virtual ::e_status set(::draw2d::region* pregion) override;
      virtual ::e_status set(::draw2d::pen* ppen) override;
      virtual ::e_status set(::write_text::font* pfont) override;
      virtual ::e_status set(::draw2d::brush* pbrush) override;
      virtual ::e_status set(::draw2d::bitmap* pbitmap) override;
      virtual ::draw2d::object* set_stock_object(i32 nIndex) override;

      virtual bool CreateWindowDC(oswindow wnd) override;
      virtual bool is_valid_update_window_thread() override;

      virtual void on_begin_draw(oswindow wnd, const size_i32& sz) override;
      virtual void on_end_draw(oswindow wnd) override;



   };


   CLASS_DECL_DRAW2D_OPENGL graphics * thread_graphics();

   CLASS_DECL_DRAW2D_OPENGL void thread_graphics(graphics * graphics);


} // namespace draw2d_opengl


#define new ACME_NEW


