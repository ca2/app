#pragma once



namespace draw2d_quartz2d
{

   class graphics;


   class brush;
   class pen;
   class font;
   class path;


   class CLASS_DECL_DRAW2D_QUARTZ2D graphics :
      virtual public ::draw2d::graphics
   {
   public:

      
      int                           m_iSaveDC;
      bool                          m_bOwnDC;
      CGContextRef                  m_pdc;
      CGLayerRef                    m_layer;

      i32                           m_iType;
#ifdef __MM
      NSColor *                     m_nscolorFore;
      NSColor *                     m_nscolorBack;
#else
      void *                        m_pnscolorFore;
      void *                        m_pnscolorBack;
#endif

      bool                          m_bForeColor;
      bool                          m_bBackColor;
      u64                           m_uiForeColor;
      u64                           m_uiBackColor;
      bool                          m_bPrinting;
      


      graphics();
      virtual ~graphics();


      bool IsPrinting() override;            // TRUE if being used for printing

      ::draw2d::pen * get_current_pen() override;
      ::draw2d::brush * get_current_brush() override;
      ::draw2d::palette * get_current_palette() override;
      ::draw2d::font * get_current_font() override;
      ::draw2d::bitmap * get_current_bitmap() override;


      // for bidi and mirrored localization
      ::u32 GetLayout() override;
      ::u32 SetLayout(::u32 dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual bool RestoreDC(i32 nSavedDC) override;
      i32 GetDeviceCaps(i32 nIndex) override;
      ::u32 SetBoundsRect(const ::rect & rectBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(LPRECT32 rectBounds, ::u32 flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(i32 x, i32 y) override;
      point SetBrushOrg(const ::point & point) override;
      i32 EnumObjects(i32 nObjectType,
                          i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

//      // Type-safe selection helpers
//   public:
//      virtual ::draw2d::object* SelectStockObject(i32 nIndex) override;
//      ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
//      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
//      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont) override;
      virtual ::estatus set(::draw2d::bitmap* pBitmap) override;
//      i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions
//      ::draw2d::object* SelectObject(::draw2d::object* pObject);


      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      //virtual bool SelectFont(::draw2d::font * pfont) override;


      // color and color Palette Functions
//      color32_t GetNearestColor(const ::color & color) override;
//      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
//      ::u32 RealizePalette() override;
//      void UpdateColors() override;

      // Drawing-Attribute Functions
      color32_t GetBkColor() const;
      i32 GetBkMode() const;
      i32 GetPolyFillMode() override;
      i32 GetROP2() override;
      i32 GetStretchBltMode() override;

      //virtual color32_t SetBkColor(const ::color & color);
      i32 SetBkMode(i32 nBkMode);
      i32 SetPolyFillMode(i32 nPolyFillMode) override;
      i32 SetROP2(i32 nDrawMode) override;
      i32 set_interpolation_mode(i32 nStretchMode) override;

      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      color32_t GetDCBrushColor() const;
      color32_t SetDCBrushColor(const ::color & color);

      color32_t GetDCPenColor() const;
      color32_t SetDCPenColor(const ::color & color);

#endif

      // Graphics mode
      i32 SetGraphicsMode(i32 iMode) override;
      i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,::u32 iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual i32 GetMapMode() override;
      virtual point GetViewportOrg() override;
      virtual i32 SetMapMode(i32 nMapMode) override;
      // Viewport Origin
      virtual point SetViewportOrg(i32 x, i32 y) override;
      virtual point SetViewportOrg(const ::point & point) override;
      virtual point OffsetViewportOrg(i32 nWidth, i32 nHeight) override;

      // Viewport Extent
      virtual size GetViewportExt() override;
      virtual size SetViewportExt(i32 cx, i32 cy) override;
      virtual size SetViewportExt(const ::size & size) override;
      virtual size ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point GetWindowOrg() override;
      point SetWindowOrg(i32 x, i32 y) override;
      point SetWindowOrg(const ::point & point) override;
      point OffsetWindowOrg(i32 nWidth, i32 nHeight) override;

      // Window extent
      size GetWindowExt() override;
      virtual size SetWindowExt(i32 cx, i32 cy) override;
      size SetWindowExt(const ::size & size) override;
      virtual size ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom) override;

      // Coordinate Functions
      void DPtoLP(POINT32 * lpPoints, i32 nCount = 1) const;
      void DPtoLP(RECT32 * prect) override;
      void DPtoLP(LPSIZE32 LPSIZE32) override;
      void LPtoDP(POINT32 * lpPoints, i32 nCount = 1) const;
      void LPtoDP(RECT32 * prect) override;
      void LPtoDP(LPSIZE32 LPSIZE32) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE32 LPSIZE32) override;
      void LPtoHIMETRIC(LPSIZE32 LPSIZE32) override;
      void HIMETRICtoDP(LPSIZE32 LPSIZE32) override;
      void HIMETRICtoLP(LPSIZE32 LPSIZE32) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual i32 GetClipBox(RECT32 * prect) override;
      //virtual bool PtVisible(i32 x, i32 y) override;
      //virtual bool PtVisible(const ::point & point) override;
      //virtual bool RectVisible(const ::rect & rect) override;
//      virtual i32 SelectClipRgn(::draw2d::region* pRgn) override;
//      virtual i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      virtual i32 ExcludeClipRect(const ::rect & rect) override;
      //i32 ExcludeUpdateRgn(::user::interaction * pWnd);
      //virtual i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual i32 IntersectClipRect(const ::rect & rect) override;
      //virtual i32 OffsetClipRgn(i32 x, i32 y) override;
      //virtual i32 OffsetClipRgn(const ::size & size) override;
      //virtual i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode) override;
      
      
      virtual ::estatus reset_clip() override;
      virtual ::estatus _intersect_clip() override;
      virtual ::estatus _add_shape(const ::rect & rect) override;
      virtual ::estatus _add_shape(const ::rectd & rect) override;
      virtual ::estatus _add_shape(const ::oval & oval) override;
      virtual ::estatus _add_shape(const ::ovald & oval) override;
      virtual ::estatus _add_shape(const ::polygon & polygon) override;
      virtual ::estatus _add_shape(const ::polygond & polygon) override;

      
      //virtual void on_apply_clip_region() override;

      // Line-Output Functions
      virtual pointd current_position() override;
      //      point MoveTo(i32 x, i32 y);
      //    point MoveTo(const ::point & point);
      virtual bool line_to(const ::pointd & point) override;
      //  bool LineTo(const ::point & point);
//      virtual bool Arc(i32 x1, i32 y1, i32 w, i32 h, double start, double extends) override;
  //    virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
//      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      virtual bool Arc(double x, double y, double w, double h, angle start, angle end) override;
//      virtual bool Arc(const ::rectd & rect, const ::pointd & pointStart, const ::pointd & pointEnd) override;
      virtual bool Polyline(const POINT32* lpPoints, count nCount) override;

      virtual bool AngleArc(i32 x, i32 y, i32 nRadius, angle fStartAngle, angle fSweepAngle) override;
//      virtual bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      virtual bool ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual i32 GetArcDirection() override;
      virtual i32 SetArcDirection(i32 nArcDirection) override;

      bool PolyDraw(const POINT32* lpPoints, const byte* lpTypes, i32 nCount);
      bool PolylineTo(const POINT32* lpPoints, i32 nCount);
      bool PolyPolyline(const POINT32* lpPoints,
                        const ::u32* lpPolyPoints, i32 nCount);

      bool PolyBezier(const POINT32* lpPoints, i32 nCount);
      bool PolyBezierTo(const POINT32* lpPoints, i32 nCount);

      // Simple Drawing Functions
      virtual bool fill_rect(const ::rectd & rect, ::draw2d::brush* pbrush) override;
      virtual bool draw_rect(const ::rectd & rect, ::draw2d::pen* ppen) override;

      virtual bool rectangle(const ::rectd & rect) override;
      virtual bool draw_rect(const ::rectd & rect) override;
      virtual bool fill_rect(const ::rectd & rect) override;

      virtual void frame_rect(const ::rect & rect, ::draw2d::brush* pbrush) override;
      virtual void invert_rect(const ::rect & rect) override;
      
      
      virtual bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon) override;
      virtual bool DrawIcon(const ::point & point, ::draw2d::icon * picon) override;
      virtual bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags,
//                             HBRUSH hBrush = nullptr) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                             ::draw2d::brush* pBrush = nullptr) override;
      /*      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags,
                           HBRUSH hBrush = nullptr);
            bool DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags,
                           ::draw2d::brush* pBrush = nullptr);*/
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags,
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags,
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //xxx      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
      //xxx      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      virtual bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                         i32 x4, i32 y4) override;
      virtual bool Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual void DrawFocusRect(const ::rect& rect) override;

//      bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool DrawEllipse(const ::rectd & rect) override;
//
//      bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool FillEllipse(const ::rectd & rect) override;

      //bool draw(double x1, double y1, double x2, double y2) override;
      bool draw_ellipse(const ::rectd & rect) override;

      //bool FillEllipse(double x1, double y1, double x2, double y2) override;
      bool fill_ellipse(const ::rectd & rect) override;

      bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual bool set_polygon(const POINTD * lpPoints, count nCount);
      virtual bool set_polygon(const POINT32 * lpPoints, count nCount);
      virtual bool fill_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool fill_polygon(const POINT32* lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINT32 * lpPoints, count nCount) override;
      virtual bool polygon(const POINTD * ppoint,count nCount) override;
      virtual bool round_rect(const ::rectd & rect, const ::pointd & point) override;

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::u32 dwRop) override;
      using ::draw2d::graphics::BitBlt;
      bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                     i32 xSrc, i32 ySrc, ::u32 dwRop) override;
      virtual bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                                 i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 dwRop) override;
      ::color GetPixel(i32 x, i32 y) override;
      ::color GetPixel(const ::point & point) override;
      ::color SetPixel(i32 x, i32 y, const ::color & color) override;
      ::color SetPixel(const ::point & point, const ::color & color) override;
//      bool FloodFill(i32 x, i32 y, const ::color & color) override;
//      bool ExtFloodFill(i32 x, i32 y, const ::color & color, ::u32 nFillType) override;
//      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
//                   ::u32 dwRop) override;
//      bool PlgBlt(POINT32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask) override;
      bool SetPixelV(i32 x, i32 y, const ::color & color) override;
      bool SetPixelV(const ::point & point, const ::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, ::u32 dwMode) override;
//      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                          ::u32 clrTransparent) override;

      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
       ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
       BLENDFUNCTION blend);*/


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;

      // Text Functions
      virtual bool internal_show_text(double x, double y, double w, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, const string & str, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr, ::draw2d::pen * ppen=nullptr, ::draw2d::brush * pbrush = nullptr, ::draw2d::font * pfont = nullptr);

      virtual bool internal_show_text(::draw2d::font_pointer spfont,::draw2d::brush_pointer spbrush,::draw2d::pen_pointer sppen, double x, double y, double w, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, const string & str, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr);

      void internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush);

      virtual bool BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc) override;

      virtual bool draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen) override;
      virtual bool text_out(i32 x, i32 y, const char * lpszString, strsize nCount) override;

      virtual bool text_out(i32 x, i32 y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const string & str) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectd & rect,
                              const char * lpszString, ::u32 nCount, LPINT lpDxWidths);
      bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect,
                      const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, i32 nCount,
                                 i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      size TabbedTextOut(i32 x, i32 y, const string & str,
                         i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      virtual i32 draw_text(const char * lpszString, i32 nCount, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
      virtual bool draw_text(const string & str, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const string & strParam,const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      virtual i32 draw_text_ex(char * lpszString, i32 nCount, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;

      sized GetTextExtent(const char * lpszString, strsize nCount, i32 iIndex);
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, i32 iIndex) ;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) ;
      virtual bool GrayString(::draw2d::brush* pBrush,
                              bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData,
                              i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
      i32 GetTextFace(i32 nCount, char * lpszFacename);
      i32 GetTextFace(string & rString) override;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
//      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
//      i32 GetTextCharacterExtra() override;
//      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      ::u32 GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;
      //xxx      ::u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      bool DrawEdge(RECT32 * prect, ::u32 nEdge, ::u32 nFlags);
//      bool DrawFrameControl(RECT32 * prect, ::u32 nType, ::u32 nState);

//      // Scrolling Functions
//      bool ScrollDC(i32 dx, i32 dy, const ::rect & rectScroll, const ::rect & rectClip,
//                    ::draw2d::region* pRgnUpdate, LPRECT32 lpRectUpdate) override;
//
//      // font Functions
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      ::u32 SetMapperFlags(::u32 dwFlag) override;
//      size GetAspectRatioFilter() override;
//
//      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
//      ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID lpData, ::u32 cbData) override;
//      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
//      //xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRIC lpotm) const;
//      //xxx      ::u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
//      //xxx    ::u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;
//
//      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//      //xxx         LPABCFLOAT lpABCF) const;
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        float* lpFloatBuffer) override;
//
//      ::u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
//      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData) override;
//      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData) override;

      // Escape helpers
      i32 StartDoc(const char * lpszDocName) override;  // old Win3.0 version
      //xxx      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage() override;
      i32 EndPage() override;
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect & rectBounds);
      bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData) override;
      // can be used for enhanced metafiles only

      // Path Functions
      virtual bool abort_path() override;
      virtual bool begin_path() override;
      virtual bool close_figure() override;
      virtual bool end_path() override;
      virtual bool fill_path() override;
      virtual bool flatten_path() override;
      virtual bool stroke_and_fill_path() override;
      virtual bool stroke_path() override;
      virtual bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;

      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      bool draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      i32 GetPath(POINT32 * lpPoints, LPBYTE lpTypes, i32 nCount) ;
      //bool SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::base::application * papp);
//      void DrawDragRect(const ::rectd & rect, const ::size & size,
//                        const ::rectd & rectLast, const ::size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      virtual void fill_rect(const ::rectd & rect, const ::color & color) override;
      virtual void draw_3drect(const ::rectd & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      virtual bool set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrenderinghint) override;

      //virtual void * get_os_data() const override;
      //      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;

      virtual bool attach(void * pdata) override;
      virtual void * detach() override;


      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rect & rect) override;


      // platform-specific or platform-internals
      bool _clip(::draw2d::region * pregion, bool bEO = false);
      bool _add_path(::draw2d::region * pregion);
      bool _set(::draw2d::brush * pbrush);
      bool _set_pen(::draw2d::brush * pbrush, double dWidth);
      bool _set(::draw2d::pen * ppen);
//      //bool set(const ::draw2d::font * pfont);
//      bool _set(::draw2d::path * ppath);
//      bool _set(::draw2d::path::matter * pmatter);
//      bool _set(::draw2d::path::arc * parc);
//      //bool set(const ::draw2d::path::move & move);
//      bool _set(::draw2d::path::line * pline);
      bool _fill_inline(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      bool _draw_inline(::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool _fill_inline(::draw2d::path::matter * pmatter, ::draw2d::brush * pbrush);
      bool _draw_inline(::draw2d::path::matter * pmatter, ::draw2d::pen * ppen);
      bool _set(::draw2d::path::text_out * ptextout);
      bool _fill_inline(::draw2d::path::text_out * ptextout, ::draw2d::brush * pbrush);
      bool _draw_inline(::draw2d::path::text_out * ptextout, ::draw2d::pen * ppen);
      bool _set(::draw2d::path::draw_text * pdrawtext);
      bool _fill_inline(::draw2d::path::draw_text * pdrawtext, ::draw2d::brush * pbrush);
      bool _draw_inline(::draw2d::path::draw_text * pdrawtext, ::draw2d::pen * ppen);
      bool _fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool _fill(::draw2d::brush * pbrush);
      bool _fill(::draw2d::brush * pbrush, bool bClip);
      bool _draw(::draw2d::brush * pbrush);
      bool _draw(::draw2d::pen * ppen);
      bool _fill_and_draw();
      bool _fill();
      bool _draw();


      void internal_set_fill_color(const ::color & color);


      virtual void enum_fonts(::draw2d::font_enum_item_array & itema) override;
      
      
      virtual ::estatus clear_current_point() override;
      

   };


} // namespace draw2d_quartz2d





