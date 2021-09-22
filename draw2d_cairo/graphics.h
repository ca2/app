#pragma once


typedef void FN_CAIRO_TEXT(cairo_t *, const char *);
typedef FN_CAIRO_TEXT * PFN_CAIRO_TEXT;

#if defined(USE_PANGO)

typedef void FN_PANGO_TEXT(cairo_t *color32, PangoLayout *layout);
typedef FN_PANGO_TEXT * PFN_PANGO_TEXT;

#endif

namespace draw2d_cairo
{


   class brush;
   class pen;
   class font;
   class object;


   class CLASS_DECL_DRAW2D_CAIRO graphics :
      virtual public ::draw2d::graphics
   {
   public:


      int                        m_iSaveDC;
      int                        m_iSaveDCPositiveClip;
      cairo_t *                  m_pdc;
      i32                        m_iType;
      bool                       m_bPrinting;
      int                        m_nStretchBltMode;
      bool                       m_bToyQuotedFontSelection;

#ifdef WINDOWS
      cairo_surface_t *          m_psurfaceAttach;
      HDC                        m_hdcAttach;
#endif

      graphics();
      virtual ~graphics();


      virtual ::e_status initialize(::object * pobject) override;

      virtual void * detach() override;

      // bool IsPrinting() override;            // true if being used for printing

      //::draw2d::pen *     get_current_pen() override;
      //::draw2d::brush *   get_current_brush() override;
      //::draw2d::palette * get_current_palette() override;
      //::write_text::font *    get_current_font() override;
      //::draw2d::bitmap *  get_current_bitmap() override;


      //pen *       lnx_pen();
      //brush *     lnx_brush();
      //font *      lnx_font();

      // for bidi and mirrored localization
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
      //bool CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
      //bool CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual bool RestoreDC(i32 nSavedDC) override;
      i32 GetDevicecaps(i32 nIndex);
      ::u32 SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(::rectangle_f64 * rectangleBounds, ::u32 flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point_f64 GetBrushOrg() override;
      point_f64 SetBrushOrg(double x, double y) override;
      point_f64 SetBrushOrg(const ::point_f64 & point_f64) override;
      //i32 EnumObjects(i32 nObjectType,
                      //i32(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* set_stock_object(i32 nIndex) override;
      //virtual ::e_status set(::draw2d::pen* ppen) override;
      //virtual ::e_status set(::draw2d::brush* pbrush) override;
      //virtual ::e_status set(::write_text::font* pfont) override;
      virtual ::e_status set(::draw2d::bitmap* pbitmap) override;
      virtual ::e_status set(::draw2d::region* pregion) override;       // special return for regions
      //::draw2d_cairo::object* SelectObject(::draw2d_cairo::object* pObject);
      // ::draw2d_cairo::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

// color and color Palette Functions
      //color32_t GetNearestColor(const ::color::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //::u32 RealizePalette() override;
      //void UpdateColors() override;

      //i32 GetPolyFillMode() override;
      //i32 GetROP2() override;
      //i32 GetStretchBltMode() override;

      //i32 SetPolyFillMode(i32 nPolyFillMode) override;
      //i32 SetROP2(i32 nDrawMode) override;


      bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;


      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      color32_t GetDCBrushColor() override;
//      color32_t SetDCBrushColor(const ::color::color & color) override;
//
//      color32_t GetDCPenColor() override;
//      color32_t SetDCPenColor(const ::color::color & color) override;
//
//#endif

      // Graphics mode
      //i32 SetGraphicsMode(i32 iMode) override;
      //i32 GetGraphicsMode() override;

//      // World transform
//      bool SetWorldTransform(const XFORM* pXform);
//      bool ModifyWorldTransform(const XFORM* pXform, u32 iMode);
//      bool GetWorldTransform(XFORM* pXform);

      // Mapping Functions
      //virtual i32 GetMapMode() override;
      virtual point_f64 GetViewportOrg() override;
      //virtual i32 SetMapMode(i32 nMapMode) override;
      // Viewport Origin
      virtual point_f64 SetViewportOrg(double x, double y) override;
      virtual point_f64 SetViewportOrg(const ::point_f64 & point_f64) override;
      virtual point_f64 OffsetViewportOrg(double nWidth, double nHeight) override;

      // Viewport Extent
      virtual size_f64 GetViewportExt() override;
      virtual size_f64 SetViewportExt(double cx, double cy) override;
      virtual size_f64 SetViewportExt(const ::size_f64 & size_f64) override;
      virtual size_f64 ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point_f64 GetWindowOrg() override;
      point_f64 SetWindowOrg(double x, double y) override;
      point_f64 SetWindowOrg(const ::point_f64 & point_f64) override;
      point_f64 offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      size_f64 GetWindowExt() override;
      virtual size_f64 set_window_ext(double cx, double cy) override;
      size_f64 set_window_ext(const ::size_f64 & size_f64) override;
      virtual size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      void DPtoLP(::point_f64 * lpPoints, count nCount = 1) override;
      void DPtoLP(::rectangle_f64 * prectangle) override;
      void DPtoLP(::size_f64 * psize) override;
      void LPtoDP(::point_f64 * lpPoints, count nCount = 1) override;
      void LPtoDP(::rectangle_f64 * prectangle) override;
      void LPtoDP(::size_f64 * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::size_f64 * psize) override;
      //void LPtoHIMETRIC(::size_f64 * psize) override;
      void HIMETRICtoDP(::size_f64 * psize) override;
      //void HIMETRICtoLP(::size_f64 * psize) override;

      // Region Functions
      bool fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      bool invert_region(::draw2d::region* pRgn) override;
      bool paint_region(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual i32 get_clip_box(::rectangle_f64 * prectangle) override;
      //virtual bool PtVisible(double x, double y) override;
      //bool PtVisible(const ::point_f64 & point_f64) override;
      //virtual bool RectVisible(const ::rectangle_f64 & rectangle_f64) override;
      //i32 SelectClipRgn(::draw2d::region* pRgn) override;
      //i32 ExcludeClipRect(double x1, double y1, double x2, double y2) override;
      //i32 ExcludeClipRect(const ::rectangle_f64 & rectangle_f64) override;
      //i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      //virtual i32 IntersectClipRect(double x1, double y1, double x2, double y2) override;
      //virtual i32 IntersectClipRect(const ::rectangle_f64 & rectangle_f64) override;
      //i32 OffsetClipRgn(double x, double y) override;
      //i32 OffsetClipRgn(const ::size_f64 & size_f64) override;
      //i32 SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      bool fill_contains(const point_f64 & point) override;

      virtual ::e_status reset_clip() override;

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual ::e_status _intersect_clip() override;
      //virtual ::e_status _add_shape(const ::rectangle_f64 & rectangle_f64) override;
      virtual ::e_status _add_shape(const ::rectangle_f64 & rectangle_f64) override;
      //virtual ::e_status _add_shape(const ::ellipse & ellipse) override;
      virtual ::e_status _add_shape(const ::ellipse & ellipse) override;
      //virtual ::e_status _add_shape(const ::polygon_i32 & polygon_i32) override;
      virtual ::e_status _add_shape(const ::polygon_f64 & polygon_i32) override;

      // Line-Output Functions
      point_f64 current_position() override;
      bool move_to(double x, double y) override;
      //    point_f64 MoveTo(const ::point_f64 & point_f64) override;
      bool line_to(double x, double y) override;
      //  bool LineTo(const ::point_f64 & point_f64) override;
      virtual bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;
      bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Arc(double x, double y, double w, double h, angle start, angle extends) override;
      bool Arc(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      bool polyline(const ::point_f64 * lpPoints, count nCount) override;

      bool AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool ArcTo(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      //i32 GetArcDirection() override;
      //i32 SetArcDirection(i32 nArcDirection) override;

      bool polydraw(const ::point_f64* lpPoints, const byte* lpTypes, count nCount) override;
      bool polyline_to(const ::point_f64* lpPoints, count nCount) override;
      bool poly_polyline(const ::point_f64* lpPoints, const ::i32 * lpPolyPoints, count nCount) override;

      bool poly_bezier(const ::point_f64* lpPoints, count nCount) override;
      bool poly_bezier_to(const ::point_f64* lpPoints, count nCount) override;

      // Simple Drawing Functions
      virtual bool fill_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::brush* pBrush) override;
      virtual bool draw_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::pen * ppen) override;
      //virtual bool frame_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::brush* pBrush) override;
      virtual bool invert_rectangle(const ::rectangle_f64 & rectangle_f64) override;

      //bool DrawIcon(double x, double y, ::draw2d::icon * picon) override;
      //virtual bool draw(const ::point_f64 & point_f64, ::draw2d::icon * picon, const ::size_f64 & size_f64) override;
      //bool DrawIcon(double x, double y, ::draw2d::icon * picon, double cx, double cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
      //bool DrawState(const ::point_f64 & point_f64, const ::size_f64 & size_f64, HBITMAP hBitmap, ::u32 nFlags,
        //             HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point_f64, const ::size_f64 & size_f64, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point_f64, const ::size_f64 & size_f64, const ::string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point_f64, const ::size_f64 & size_f64, const ::string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;




      bool Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                 double x4, double y4) override;
      bool Chord(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void DrawFocusRect(const ::rectangle_f64 & rectangle_f64) override;

//      bool DrawEllipse(double x1, double y1, double x2, double y2) override;
//      bool DrawEllipse(const ::rectangle_f64 & rectangle_f64) override;
//
//      bool FillEllipse(double x1, double y1, double x2, double y2) override;
//      bool FillEllipse(const ::rectangle_f64 & rectangle_f64) override;

      bool draw_ellipse(double x1, double y1, double x2, double y2) override;
      bool draw_ellipse(const ::rectangle_f64 & rectangle_f64) override;

      bool fill_ellipse(double x1, double y1, double x2, double y2) override;
      bool fill_ellipse(const ::rectangle_f64 & rectangle_f64) override;

      bool Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Pie(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;

      virtual bool fill_polygon(const POINT_F64 * lpPoints, count nCount) override;

      virtual bool draw_polygon(const POINT_F64 * lpPoints, count nCount) override;


      bool polygon(const POINT_F64 * lpPoints, count nCount) override;
      bool rectangle(const ::rectangle_f64 & rectangle_f64) override;
      //virtual bool draw_rectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool DrawRectangle(const ::rectangle_f64 & rectangle_f64) override;
      //virtual bool FillRectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool FillRectangle(const ::rectangle_f64 & rectangle_f64) override;
      //bool roundRect(double x1, double y1, double x2, double y2, double x3, double y3) override;
      bool round_rectangle(const ::rectangle_f64 & rectangle_f64, double dRadius) override;

      // Bitmap Functions
      //bool PatBlt(double x, double y, double nWidth, double nHeight) override;


      //virtual bool _draw_raw(const ::image_drawing & imagedrawing) override;
      virtual bool _draw_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawing, const ::point_f64 & pointSrc);
      virtual bool _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawing, const ::rectangle_f64 & rectdSrc);
      //bool _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource) override;


      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::point_f64 & point_f64) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::point_f64 & point_f64, const ::color::color & color) override;
//      bool FloodFill(double x, double y, const ::color::color & color) override;
//      bool ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType) override;
//      bool MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                   u32 dwRop) override;
//      bool PlgBlt(::point_f64 * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//                  double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask) override;
      bool SetPixelV(double x, double y, const ::color::color & color) override;
      bool SetPixelV(const ::point_f64 & point_f64, const ::color::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, u32 dwMode) override;
//      bool TransparentBlt(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                          ::u32 clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool text_out(double x, double y, const ::string & lpszString, strsize nCount) override;
      //virtual bool text_out(double x, double y, const ::string & str) override;
      virtual ::e_status TextOutRaw(double x, double y, const block & block) override;
      ///virtual bool text_out(double x, double y, const ::string & str) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle_f64, const ::string & lpszString, strsize nCount, int * lpDxWidths) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle_f64, const ::string & str, int * lpDxWidths) override;
//      virtual size_f64 TabbedTextOut(double x, double y, const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;
//      virtual size_f64 TabbedTextOut(double x, double y, const ::string & str, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;

#if defined(USE_PANGO)
      //virtual bool internal_draw_text_cairo(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnText = nullptr);
      virtual bool internal_draw_text_pango(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_PANGO_TEXT pfnText = nullptr);
      virtual bool internal_draw_text(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
#else
      virtual bool internal_draw_text(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnTtext = nullptr);
#endif
      //virtual bool draw_text(const ::string & lpszString, strsize nCount, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual bool draw_text_ex(char * lpszString, strsize nCount, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      //virtual bool draw_text_ex(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams = nullptr) override;
      virtual bool draw_text_ex(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      size_f64 get_text_extent(const char * lpszString, strsize nCount, strsize iIndex) override;
      size_f64 get_text_extent(const char * lpszString, strsize nCount) override;
      size_f64 get_text_extent(const block & block) override;
      bool _GetTextExtent(size_f64 & size_f64, const char * lpszString, strsize nCount, strsize iIndex);
      bool get_text_extent(size_f64 & size_f64, const char * lpszString, strsize nCount, strsize iIndex) override;
      bool get_text_extent(size_f64 & size_f64, const char * lpszString, strsize nCount) override;
      bool get_text_extent(size_f64 & size_f64, const ::string & str) override;
      size_f64 GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size_f64 GetOutputTextExtent(const ::string & str) override;
      //size_f64 GetTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      //size_f64 GetTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions) override;
      size_f64 GetOutputTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      size_f64 GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, double nWidth, double nHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
      //i32 GetTextFace(count nCount, char * lpszFacename) override;
      //i32 GetTextFace(string & rString) override;
      ::e_status get_text_metrics(::write_text::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
//      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
//      i32 GetTextCharacterExtra() override;
//      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      u32 GetCharacterPlacement(const ::string & lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      //xxx      u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt ::size_f64 ::size_f64) override;
//      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt ::size_f64 ::size_f64) override;
//
//#endif

//      // Advanced Drawing
//      bool DrawEdge(const ::rectangle_f64 & rectangle_f64, ::u32 nEdge, ::u32 nFlags) override;
//      bool DrawFrameControl(const ::rectangle_f64 & rectangle_f64, ::u32 nType, ::u32 nState) override;

//      // Scrolling Functions
//      bool ScrollDC(i32 dx, i32 dy, const ::rectangle_f64 & rectangleScroll, const ::rectangle_f64 & rectangleClip,
//                    ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate) override;

//      // font Functions
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      u32 SetMapperFlags(u32 dwFlag) override;
//      size_f64 GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) override;
//      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//      //xxx         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        float* lpFloatBuffer) override;
//
//      u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) override;
//      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual i32 Escape(i32 nEscape, i32 nCount, const ::string & lpszInData, LPVOID lpOutData) override;
//      i32 Escape(i32 nEscape, i32 nInputSize, const ::string & lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const ::string & lpszInputData) override;
//
      // Escape helpers
      //i32 StartDoc(const ::string & lpszDocName) override;  // old Win3.0 version
//xxx      i32 StartDoc(LPDOCINFO lpDocInfo) override;
      i32 StartPage() override;
      i32 EndPage() override;
      //i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_f64 & rectangleBounds) override;
      //    bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData) override;
      // can be used for enhanced metafiles only

// Path Functions
      bool abort_path() override;
      bool begin_path() override;
      bool close_figure() override;
      bool end_path() override;
      bool fill_path() override;
      bool flatten_path() override;
      bool stroke_and_fill_path() override;
      bool stroke_path() override;
      bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;

      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      //i32 GetPath(::point_f64 * lpPoints, LPBYTE lpTypes, count nCount) override;
      bool SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      //static ::draw2d::brush* PASCAL GetHalftoneBrush(::object * pobject);
//      void DrawDragRect(const ::rectangle_f64 & rectangle_f64, const ::size_f64 & size_f64,
//                        const ::rectangle_f64 & rectangleLast, const ::size_f64 & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rectangle(const RECTANGLE_I64 * rectangle_f64, color32_t clr) override;
      //void fill_rectangle(const ::rectangle_f64 & rectangle_f64, const ::color::color & color) override;
      bool fill_rectangle(const ::rectangle_f64 & rectangle_f64, const ::color::color & color) override;
      //void fill_rectangle(double x, double y, double cx, double cy, color32_t clr) override;
      //bool draw_inset_3drect(const ::rectangle_f64 & rectangle_f64, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw3d_rect(double x, double y, double cx, double cy,
      //              color32_t clrTopLeft, color32_t clrBottomRight) override;




      // Implementation
   public:
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      //      HGDIOBJ SelectObject(HGDIOBJ) override;      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      virtual bool set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint) override;

//      virtual void * get_os_data() const override;
      //      virtual HDC get_handle() override;
      //    virtual HDC get_handle1() override;
      //  virtual HDC get_handle2() override;

      virtual bool attach(void * pdata) override;

      virtual ::e_status clear_current_point() override;
      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle_f64) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h) override;


      // platform-specific or platform-internals
      bool _set_os_color(color32_t color32);
      bool _set(::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool _set(::draw2d::pen * ppen);
#if !defined(USE_PANGO)
      bool _set(::write_text::font * pfont);
#endif
      bool _set(::draw2d::path * ppath);

      bool _set(const ::point_i32_array & pointa);
      bool _set(const ::point_f64_array & pointa);

      bool _set(___shape * pshape);
      bool _set(const enum_shape & eshape);
      bool _set(const ::arc & arc);
      bool _set(const ::line & line);
      bool _set(const ::lines & lines);
      bool _set(const ::rectangle & rectangle);
      bool _set(const ::polygon & polygon);
      bool _set(const ::write_text::text_out & textout);
      bool _set(const ::write_text::draw_text & drawtext);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush, double xOrg  = 0.0, double yOrg = 0.0);
      bool _fill1(::draw2d::brush* pbrush, double xOrg = 0.0, double yOrg = 0.0);
      bool _fill2(::draw2d::brush* pbrush, double xOrg = 0.0, double yOrg = 0.0);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill(double xOrg = 0.0, double yOrg = 0.0);
      bool _fill1(double xOrg = 0.0, double yOrg = 0.0);
      bool _fill2(double xOrg = 0.0, double yOrg = 0.0);
      bool draw();


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;


      virtual bool flush() override;

//#ifdef WINDOWS

  //    virtual bool attach_hdc(HDC hdc) override;
    //  virtual HDC detach_hdc() override;

//#endif

      //virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      //virtual ::file::path get_font_path(const ::string & strName, int iWeight, bool bItalic) override;


      FT_Face ftface(const ::string & pszFontName, int iWeight, bool bItalic);

      //virtual void on_apply_clip_region() override;


   };


   CLASS_DECL_AURA string q_valid_string(string str);


} // namespace win





