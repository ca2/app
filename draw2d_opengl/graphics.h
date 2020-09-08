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
      ::size                        m_size;
      HDC                           m_hdcGraphics;
      float                         m_z;
      point                         m_pointTranslate;
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
      using draw2d::graphics::fill_rect;
      void fill_rect(const rectd& rect, COLORREF cr);


      virtual void SetAttribDC(HDC hDC);  // set the Attribute DC
      virtual void SetOutputDC(HDC hDC);  // set the Output DC
      virtual void ReleaseAttribDC();     // Release the Attribute DC
      virtual void ReleaseOutputDC();     // Release the Output DC

      bool IsPrinting() const;            // TRUE if being used for printing

      ::draw2d::pen_pointer     get_current_pen() const;
      ::draw2d::brush_pointer   get_current_brush() const;
      ::draw2d::palette_pointer get_current_palette() const;
      ::draw2d::font_pointer    get_current_font() const;
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

      virtual bool opengl_create_offscreen_buffer(const ::size & size);
      virtual bool opengl_delete_offscreen_buffer();

      bool DeleteDC();

      // Device-Context Functions
      virtual i32 SaveDC();
      virtual bool RestoreDC(i32 nSavedDC);
      i32 GetDeviceCaps(i32 nIndex) const;
      UINT SetBoundsRect(const RECT &  rectBounds, UINT flags);
      UINT GetBoundsRect(LPRECT rectBounds, UINT flags);
      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      point GetBrushOrg() const;
      point SetBrushOrg(i32 x, i32 y);
      point SetBrushOrg(const ::point & point);
      i32 EnumObjects(i32 nObjectType,
                          i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(i32 nIndex);
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      i32 SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d::object* SelectObject(::draw2d::object* pObject);
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      // color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) const;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      UINT RealizePalette();
      void UpdateColors();

      i32 GetPolyFillMode() const;
      i32 GetROP2() const;
      i32 GetStretchBltMode() const;

      i32 SetPolyFillMode(i32 nPolyFillMode);
      i32 SetROP2(i32 nDrawMode);
      i32 SetStretchBltMode(i32 nStretchMode);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() const;
      COLORREF SetDCBrushColor(COLORREF crColor);

      COLORREF GetDCPenColor() const;
      COLORREF SetDCPenColor(COLORREF crColor);

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
      //virtual point GetViewportOrg() const;
      virtual i32 SetMapMode(i32 nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(i32 x, i32 y);
      virtual point SetViewportOrg(const ::point & point);
      virtual point OffsetViewportOrg(i32 nWidth, i32 nHeight);

      // Viewport Extent
      virtual size GetViewportExt() const;
      virtual size SetViewportExt(i32 cx, i32 cy);
      virtual size SetViewportExt(const ::size & size);
      virtual size ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Window Origin
      point GetWindowOrg() const;
      point SetWindowOrg(i32 x, i32 y);
      point SetWindowOrg(const ::point & point);
      point OffsetWindowOrg(i32 nWidth, i32 nHeight);

      // Window extent
      size GetWindowExt() const;
      virtual size SetWindowExt(i32 cx, i32 cy);
      size SetWindowExt(const ::size & size);
      virtual size ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints,count nCount = 1) const;
      void DPtoLP(RECT * prect) const;
      void DPtoLP(LPSIZE lpSize) const;
      void LPtoDP(LPPOINT lpPoints,count nCount = 1) const;
      void LPtoDP(RECT * prect) const;
      void LPtoDP(LPSIZE lpSize) const;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) const;
      void LPtoHIMETRIC(LPSIZE lpSize) const;
      void HIMETRICtoDP(LPSIZE lpSize) const;
      void HIMETRICtoLP(LPSIZE lpSize) const;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual i32 GetClipBox(RECT * prect) const;
      virtual bool PtVisible(i32 x, i32 y) const;
      bool PtVisible(const ::point & point) const;
      virtual bool RectVisible(const RECT &  rect) const;
      i32 SelectClipRgn(::draw2d::region* pRgn);
      i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 ExcludeClipRect(const RECT &  rect);
      i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 IntersectClipRect(const RECT &  rect);
      i32 OffsetClipRgn(i32 x, i32 y);
      i32 OffsetClipRgn(const ::size & size);
      i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode);

      // Line-Output Functions
      // point GetCurrentPosition() const;
//      point MoveTo(i32 x, i32 y);
      //    point MoveTo(const ::point & point);
      virtual bool line_to(const ::pointd & point) override;
      //bool LineTo(int x,int y);
      //  bool LineTo(const ::point & point);
      bool Polyline(const POINT* lpPoints,count nCount);

      virtual bool _set(const ::draw2d::matrix & matrix) override;

      using ::draw2d::graphics::Arc;
      bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,i32 x3,i32 y3,i32 x4,i32 y4);
      bool Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);

      bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,double start, double extends);
      bool Arc(double x1,double y1,double x2,double y2,double start, double extends);

      bool AngleArc(i32 x,i32 y,i32 nRadius,float fStartAngle,float fSweepAngle);
      bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      bool ArcTo(const RECT &  rect, const ::point & pointStart, const ::point & pointEnd);
      i32 GetArcDirection() const;
      i32 SetArcDirection(i32 nArcDirection);

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount);
      bool PolylineTo(const POINT* lpPoints,count nCount);
      bool PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount);

      bool PolyBezier(const POINT* lpPoints,count nCount);
      bool PolyBezierTo(const POINT* lpPoints,count nCount);

      // Simple Drawing Functions
      virtual bool fill_rect(const ::rect &  rect, ::draw2d::brush* pBrush) override;
      void FrameRect(const RECT &  rect, ::draw2d::brush* pBrush);
      //bool DrawRect(const ::rect & rect, ::draw2d::pen * ppen);
      void InvertRect(const RECT &  rect);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon);
      bool DrawIcon(const ::point & point, ::draw2d::icon * picon);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, UINT nFlags,
                     HBRUSH hBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                     ::draw2d::brush* pBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                     HBRUSH hBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                     ::draw2d::brush* pBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
                     LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr);
      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
                     LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                 i32 x4, i32 y4);
      bool Chord(const RECT &  rect, const ::point & pointStart, const ::point & pointEnd);
      void DrawFocusRect(const RECT &  rect);

      //bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool DrawEllipse(const RECT &  rect);
      //bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool FillEllipse(const RECT &  rect);

      //virtual bool DrawEllipse(double x1,double y1,double x2,double y2);
      virtual bool draw_ellipse(const ::rectd & rect) override;
      //virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      virtual bool fill_ellipse(const ::rectd & rect) override;

      //virtual bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      //virtual bool Pie(const RECT &  rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual bool fill_polygon(const POINTD * lpPoints,count nCount) override;
      virtual bool fill_polygon(const POINT * lpPoints,count nCount) override;
      virtual bool draw_polygon(const POINT * lpPoints,count nCount) override;
      virtual bool draw_polygon(const POINTD * lpPoints,count nCount) override;
      virtual bool polygon(const POINT* lpPoints,count nCount) override;
      virtual bool polygon(const POINTD* lpPoints,count nCount) override;
      virtual bool poly_polygon(const POINT* lpPoints, const i32 * lpPolyCounts,count nCount) override;
      //virtual bool rectangle(i32 x1, i32 y1, i32 x2, i32 y2) override;
      virtual bool rectangle(const ::rectd &  rect) override;
      //virtual bool drw(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool draw_rect(const ::rectd & rect);
      virtual bool draw_rect(const ::rectd& rect, ::draw2d::pen * ppen);
      //virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool fill_rect(const ::rectd &  rect);
      bool RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
      bool RoundRect(const RECT &  rect, const ::point & point);

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, u32 dwRop);
      virtual bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop) override;
      virtual bool StretchBltRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop) override;
//      {

//         bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop);
      COLORREF GetPixel(i32 x, i32 y) const;
      COLORREF GetPixel(const ::point & point) const;
      COLORREF SetPixel(i32 x, i32 y, COLORREF crColor);
      COLORREF SetPixel(const ::point & point, COLORREF crColor);
      bool FloodFill(i32 x, i32 y, COLORREF crColor);
      bool ExtFloodFill(i32 x, i32 y, COLORREF crColor, UINT nFillType);
      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
                   u32 dwRop);
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask);
      bool SetPixelV(i32 x, i32 y, COLORREF crColor);
      bool SetPixelV(const ::point & point, COLORREF crColor);
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, u32 dwMode);
      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                          UINT clrTransparent);

      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool TextOut(i32 x, i32 y, const char * lpszString, strsize nCount);
      //virtual bool TextOut(i32 x, i32 y, const string & str);
      //virtual bool TextOut(double x, double y, const char * lpszString, strsize nCount);
      //virtual bool TextOut(double x, double y, const string & str);
      //virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  rect, const char * lpszString,strsize nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  rect, const string & str, LPINT lpDxWidths);
      //virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      //virtual size TabbedTextOut(i32 x, i32 y, const string & str,count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      virtual bool text_out(double x, double y, const char* lpszString, strsize nCount) override;

      virtual bool draw_text(const char * lpszString,strsize nCount,const ::rect & rect,UINT nFormat);
      virtual bool draw_text(const string & str,const ::rect & rect,UINT nFormat);

      virtual bool draw_text_ex(LPTSTR lpszString,strsize nCount,const ::rect & rect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str,const ::rect & rect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);

      virtual bool draw_text(const char * lpszString,strsize nCount,const ::rectd & rect,UINT nFormat);
      virtual bool draw_text(const string & str,const ::rectd & rect,UINT nFormat);

      virtual bool draw_text_ex(const char * lpszString,strsize nCount,const ::rectd & rect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str,const ::rectd & rect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);

      virtual sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      virtual sized GetTextExtent(const char * lpszString, strsize nCount) override;
      virtual sized GetTextExtent(const string & str) override;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex);
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount);
      virtual bool GetTextExtent(sized & size, const string & str);
      virtual size GetOutputTextExtent(const char * lpszString, strsize nCount);
      virtual size GetOutputTextExtent(const string & str);
      virtual size GetTabbedTextExtent(const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size GetTabbedTextExtent(const string & str,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions);
      virtual size GetOutputTabbedTextExtent(const string & str,count nTabPositions, LPINT lpnTabStopPositions);
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);
      virtual UINT GetTextAlign();
      virtual UINT SetTextAlign(UINT nFlags);
      virtual i32 GetTextFace(count nCount, LPTSTR lpszFacename);
      virtual i32 GetTextFace(string & rString);
      virtual bool get_text_metrics(::draw2d::text_metric * lpMetrics);
      virtual bool get_output_text_metrics(::draw2d::text_metric * lpMetrics);
      virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      virtual i32 GetTextCharacterExtra();
      virtual i32 SetTextCharacterExtra(i32 nCharExtra);

      virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;
      virtual u32 GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE lpSize) const;
//
//#endif



      // Advanced Drawing
      bool DrawEdge(const ::rect & rect,UINT nEdge,UINT nFlags);
      bool DrawFrameControl(const ::rect & rect,UINT nType,UINT nState);

      // Scrolling Functions
      bool ScrollDC(i32 dx, i32 dy, const RECT &  lpRectScroll, const RECT &  lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate);

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      u32 SetMapperFlags(u32 dwFlag);
      size GetAspectRatioFilter() const;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const;
      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const;
      u32 GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
                               u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
                            LPABCFLOAT lpABCF) const;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) const;

      u32 GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

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
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const RECT &  lpBounds);
      bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
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
      i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes,count nCount) const;
      bool SelectClipPath(i32 nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::object * pobject);
      void DrawDragRect(const RECT &  rect, const ::size & size,
                        const RECT &  lpRectLast, const ::size & sizeLast,
                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const RECT64 * rect, COLORREF clr);
      //void FillSolidRect(const RECT &  rect, COLORREF clr);
      //void FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, COLORREF clr);
      void Draw3dRect(const RECT &  rect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      void Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                      COLORREF clrTopLeft, COLORREF clrBottomRight);




      // Implementation
   public:
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::e_alpha_mode ealphamode);

      virtual bool set_smooth_mode(::draw2d::e_smooth_mode esmoothmode);

      virtual bool set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrendering);

      //virtual void * get_os_data() const;
      //virtual void * get_os_data_ex(int i) const;
      //virtual void release_os_data_ex(int i, void *p);
      //virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata);


      //virtual plusplus::FillMode gl2d_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rect & rect);


      virtual bool flush();
      virtual bool sync_flush();

      //virtual bool DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      //virtual bool DrawLine(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::pen * ppen);

      
      virtual bool draw_line(const point& point1, const point& point2, ::draw2d::pen* ppen);


      virtual void enum_fonts(::draw2d::font_enum_item_array& itema) override;

      virtual bool prefer_mapped_image_on_mix();

      virtual void set(::draw2d::pen * ppen);
      virtual void set(::draw2d::brush * pbrush);
      virtual void set(const ::draw2d::font * pfont);

      virtual bool CreateWindowDC(oswindow wnd) override;
      virtual bool is_valid_update_window_thread() override;

      virtual void on_begin_draw(oswindow wnd, const size& sz) override;
      virtual void on_end_draw(oswindow wnd) override;



   };


   CLASS_DECL_DRAW2D_OPENGL graphics * thread_graphics();

   CLASS_DECL_DRAW2D_OPENGL void thread_graphics(graphics * graphics);


} // namespace draw2d_opengl


#define new ACME_NEW


