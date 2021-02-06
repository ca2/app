#pragma once


namespace draw2d_xlib
{


   class brush;
   class pen;
   class font;
   class object;





   class CLASS_DECL_DRAW2D_XLIB graphics :
      virtual public ::draw2d::graphics
   {
      // // DECLARE_DYNCREATE(::draw2d::graphics_pointer)
   public:


      ::user::interaction         m_ui;
      device_context *        m_pdc;
      i32                 m_iType;
      //bool                    m_bForeColor;
      //bool                    m_bBackColor;
      //u64                m_uiForeColor;
      //u64                m_uiBackColor;
      //color32_t                m_colorTextColor;
      //xxx ::Gdiplus::GraphicsPath *     m_ppath;
      //xxx ::Gdiplus::GraphicsPath *     m_ppathPaint;
      //xxx HDC                           m_hdc;

      // advanced use and implementation
      bool                          m_bPrinting;
      int                     m_nStretchBltMode;



      //graphics();
      graphics(::layered * pobjectContext);
      virtual ~graphics();


      /* xxx      Gdiplus::Graphics & g()
            {
               if(m_pgraphics == nullptr)
               {
                  m_pgraphics = ::Gdiplus::Graphics::FromHDC(get_handle1());
               }
               return *m_pgraphics;
            }*/

      //::user::user::interaction_impl * GetWindow() const;

      //static ::draw2d::graphics * PASCAL from_handle(HDC hDC);
      //static void PASCAL DeleteTempMap();
      //bool Attach(HDC hdc);   // Attach/Detach affects only the Output DC
      //HDC Detach();


      virtual void * detach();

      //virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
      //virtual void SetOutputDC(HDC hDC);  // Set the Output DC
      //virtual void ReleaseAttribDC();     // Release the Attribute DC
      //virtual void ReleaseOutputDC();     // Release the Output DC

      bool IsPrinting() const;            // true if being used for printing

      ::draw2d::pen_pointer     get_current_pen() const;
      ::draw2d::brush_pointer   get_current_brush() const;
      ::draw2d::palette_pointer get_current_palette() const;
      ::draw2d::font_pointer    get_current_font() const;
      ::draw2d::bitmap_pointer  get_current_bitmap() const;


      //pen *       lnx_pen();
      //brush *     lnx_brush();
      //font *      lnx_font();

      // for bidi and mirrored localization
      u32 GetLayout() const;
      u32 SetLayout(u32 dwLayout);


      virtual double get_dpix() const;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      bool CreateCompatibleDC(::image::image * pimage);

      bool DeleteDC();

      // Device-Context Functions
      virtual i32 SaveDC();
      virtual bool RestoreDC(i32 nSavedDC);
      i32 GetDevicecaps(i32 nIndex) const;
      ::u32 SetBoundsRect(::rectangle_i32 rectBounds, ::u32 flags);
      ::u32 GetBoundsRect(RECTANGLE_I32 * rectBounds, ::u32 flags);
// xxx      bool ResetDC(const DEVMODE* lpDevMode);

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
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      i32 SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d_xlib::object* SelectObject(::draw2d_xlib::object* pObject);
      // ::draw2d_xlib::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

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

// xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
// xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

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
      virtual point_i32 GetViewportOrg() const;
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
      void DPtoLP(POINT_I32 * lpPoints, i32 nCount = 1) const;
      void DPtoLP(RECTANGLE_I32 * prectangle) const;
      void DPtoLP(LPSIZE32 LPSIZE32) const;
      void LPtoDP(POINT_I32 * lpPoints, i32 nCount = 1) const;
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
      using draw2d::graphics::get_clip_box;
      virtual i32 get_clip_box(RECTANGLE_I32 * prectangle) const;
      virtual bool PtVisible(i32 x, i32 y) const;
      bool PtVisible(const ::point_i32 & point) const;
      virtual bool RectVisible(const ::rectangle_i32 & rectangle) const;
      i32 SelectClipRgn(::draw2d::region* pRgn);
      i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 ExcludeClipRect(const ::rectangle_i32 & rectangle);
      i32 ExcludeUpdateRgn(::window * pWnd);
      i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 IntersectClipRect(const ::rectangle_i32 & rectangle);
      i32 OffsetClipRgn(i32 x, i32 y);
      i32 OffsetClipRgn(const ::size_i32 & size);
      i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode);

      // Line-Output Functions
      point_i32 GetCurrentPosition() const;
      using ::draw2d::graphics::MoveTo;
      point_i32 MoveTo(i32 x, i32 y);
      point_f64 MoveTo(double x, double y);
      //    point_i32 MoveTo(const ::point_i32 & point);
      using ::draw2d::graphics::LineTo;
      bool LineTo(double x, double y);
      //  bool LineTo(const ::point_i32 & point);
      using ::draw2d::graphics::Arc;
      bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      bool Arc(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      bool polyline(const POINT_I32* lpPoints, i32 nCount);

      bool AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle);
      bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      bool ArcTo(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      i32 GetArcDirection() const;
      i32 SetArcDirection(i32 nArcDirection);

      bool PolyDraw(const POINT_I32* lpPoints, const byte* lpTypes, i32 nCount);
      bool polyline_to(const POINT_I32* lpPoints, i32 nCount);
      bool poly_polyline(const POINT_I32* lpPoints,
                        const u32* lpPolyPoints, i32 nCount);

      bool poly_bezier(const POINT_I32* lpPoints, i32 nCount);
      bool poly_bezier_to(const POINT_I32* lpPoints, i32 nCount);

      // Simple Drawing Functions
      void FillRect(const ::rectangle_i32 & rectangle, ::draw2d::brush* pBrush);
      void FrameRect(const ::rectangle_i32 & rectangle, ::draw2d::brush* pBrush);

      using ::draw2d::graphics::DrawRect;
      bool DrawRect(const ::rectangle_i32 & rectangle, ::draw2d::pen * pBrush);
      bool DrawRect(int x1, int y1, int x2, int y2, ::draw2d::pen * pBrush);

      void InvertRect(const ::rectangle_i32 & rectangle);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon);
      bool DrawIcon(const ::point_i32 & point, ::draw2d::icon * picon);
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags);
      //bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, ::u32 nFlags,
        //             HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
      /*      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
               HBRUSH hBrush = nullptr);
            bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
               ::draw2d::brush* pBrush = nullptr);*/
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//xxx      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//xxx         LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//xxx      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//xxx         LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                 i32 x4, i32 y4);
      bool Chord(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      void DrawFocusRect(const ::rectangle_i32 & rectangle);
      bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      bool DrawEllipse(const ::rectangle_i32 & rectangle);
      bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      bool FillEllipse(const ::rectangle_i32 & rectangle);
      bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      bool Pie(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);

      virtual bool fill_polygon(const POINT_F64 * lpPoints, i32 nCount);
      virtual bool fill_polygon(const POINT_I32* lpPoints, i32 nCount);

      virtual bool draw_polygon(const POINT_F64 * lpPoints, i32 nCount);
      virtual bool draw_polygon(const POINT_I32* lpPoints, i32 nCount);


      using ::draw2d::graphics::Polygon;
      bool Polygon(const POINT_I32* lpPoints, i32 nCount);
      bool PolyPolygon(const POINT_I32* lpPoints, const ::i32* lpPolyCounts, i32 nCount);
      bool Rectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      bool Rectangle(const ::rectangle_i32 & rectangle);
      virtual bool DrawRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool DrawRectangle(const ::rectangle_i32 & rectangle);
      virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool FillRectangle(const ::rectangle_i32 & rectangle);
      bool RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
      bool RoundRect(const ::rectangle_i32 & rectangle, const ::point_i32 & point);

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight);
      using ::draw2d::graphics::BitBlt;
      bool BitBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                  i32 xSrc, i32 ySrc);
      bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                      i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
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
//      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
//                        void * pMesh, ULONG nMeshElements, u32 dwMode);
//      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                          ::u32 clrTransparent);

      using ::draw2d::graphics::alpha_blend;
      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool TextOut(i32 x, i32 y, const char * lpszString, i32 nCount);
      virtual bool TextOut(i32 x, i32 y, const string & str);
      virtual bool TextOut(double x, double y, const char * lpszString, i32 nCount);
      virtual bool TextOut(double x, double y, const string & str);
      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectangle_i32 & rectangle,
                              const char * lpszString, ::u32 nCount, LPINT lpDxWidths);
      bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectangle_i32 & rectangle,
                      const string & str, LPINT lpDxWidths);
      virtual size_i32 TabbedTextOut(i32 x, i32 y, const char * lpszString, i32 nCount,
                                 i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      size_i32 TabbedTextOut(i32 x, i32 y, const string & str,
                         i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      using ::draw2d::graphics::draw_text;
      virtual i32 draw_text(const char * lpszString, i32 nCount, RECTANGLE_I32 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
      virtual i32 draw_text(const string & str, RECTANGLE_I32 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      using ::draw2d::graphics::draw_text_ex;
      virtual i32 draw_text_ex(char * lpszString, i32 nCount, RECTANGLE_I32 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      virtual i32 draw_text_ex(const string & str, RECTANGLE_I32 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);

      size_i32 GetTextExtent(const char * lpszString, strsize nCount, i32 iIndex) const;
      size_i32 GetTextExtent(const char * lpszString, strsize nCount) const;
      size_i32 GetTextExtent(const string & str) const;
      bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, i32 iIndex) const;
      bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount) const;
      bool GetTextExtent(size_f64 & size, const string & str) const;
      size_i32 GetOutputTextExtent(const char * lpszString, strsize nCount) const;
      size_i32 GetOutputTextExtent(const string & str) const;
      size_i32 GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions) const;
      size_i32 GetTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) const;
      size_i32 GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions) const;
      size_i32 GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) const;
      virtual bool GrayString(::draw2d::brush* pBrush,
                              bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData,
                              i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);
      ::u32 GetTextAlign() const;
      ::u32 SetTextAlign(::u32 nFlags);
      i32 GetTextFace(i32 nCount, char * lpszFacename) const;
      i32 GetTextFace(string & rString) const;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) const;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) const;
      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      i32 GetTextCharacterExtra() const;
      i32 SetTextCharacterExtra(i32 nCharExtra);

//xxx      u32 GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;
//xxx      u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 LPSIZE32) const;

#endif



//      // Advanced Drawing
//      bool DrawEdge(RECTANGLE_I32 * prectangle, ::u32 nEdge, ::u32 nFlags);
//      bool DrawFrameControl(RECTANGLE_I32 * prectangle, ::u32 nType, ::u32 nState);

      // Scrolling Functions
      bool ScrollDC(i32 dx, i32 dy, rectangle_i32 lpRectScroll, const ::rectangle_i32 & rectClip,
                    ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate);

      // font Functions
      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      u32 SetMapperFlags(u32 dwFlag);
      size_i32 GetAspectRatioFilter() const;

//xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const;
//xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
//xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const;
//xxx      u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

//xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//xxx         LPABCFLOAT lpABCF) const;
      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
                        float* lpFloatBuffer) const;

      u32 GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData);
      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData);
      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData);

      // Escape helpers
      i32 StartDoc(const char * lpszDocName);  // old Win3.0 version
//xxx      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage();
      i32 EndPage();
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32));
      i32 AbortDoc();
      i32 EndDoc();

      // MetaFile Functions
//xxx      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, rectangle_i32 lpBounds);
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

      using ::draw2d::graphics::draw_path;
      bool draw_path(::draw2d::path * ppath);
      using ::draw2d::graphics::fill_path;
      bool fill_path(::draw2d::path * ppath);


      float GetMiterLimit() const;
      bool SetMiterLimit(float fMiterLimit);
      i32 GetPath(POINT_I32 * lpPoints, LPBYTE lpTypes, i32 nCount) const;
      bool SelectClipPath(i32 nMode);

      // Misc Helper Functions
      using ::draw2d::graphics::GetHalftoneBrush;
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::layered * pobjectContext);
      void DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_i32 & size,
                        rectangle_i32 lpRectLast, const ::size_i32 & sizeLast,
                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      void FillSolidRect(const RECTANGLE_I64 * rectangle, color32_t clr);
      void FillSolidRect(const ::rectangle_i32 & rectangle, color32_t clr);
      void FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr);
      void Draw3dRect(const ::rectangle_i32 & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);




      // Implementation
   public:
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

//      HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      virtual void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode);

      virtual void set_text_rendering_hint(::draw2d::e_text_rendering_hint_hint etextrendering);

      virtual void * get_os_data() const;
//      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;

      virtual bool attach(void * pdata);


//xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rectangle_i32 & rectangle);

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_xlib::object* PASCAL SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h);


      // platform-specific or platform-internals
      bool set_os_color(color32_t cr);
      bool set(const ::draw2d::brush * pbrush);
      bool set(const ::draw2d::pen * ppen);
      bool set(const ::draw2d::font * pfont);
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::matter & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill();
      bool draw();


      unsigned int compute_line_height();

   };


} // namespace win





