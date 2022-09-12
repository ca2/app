#pragma once


#include "aura/graphics/draw2d/graphics.h"


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
      ~graphics() override;


      void assert_ok() const override;
      void dump(dump_context& dumpcontext) const override;


      void initialize(::object * pobject) override;

      void * detach() override;

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


      double get_dpix() override;

      // Constructors
      //bool CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
      //bool CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      void DeleteDC() override;

      // Device-Context Functions
      i32 SaveDC() override;
      void RestoreDC(i32 nSavedDC) override;
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
   //public:
      ::draw2d::object* set_stock_object(i32 nIndex) override;
      //virtual void set(::draw2d::pen* ppen) override;
      //virtual void set(::draw2d::brush* pbrush) override;
      //virtual void set(::write_text::font* pfont) override;
      void set(::draw2d::bitmap* pbitmap) override;
      void set(::draw2d::region* pregion) override;       // special return for regions
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


      void set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;


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
      point_f64 get_origin() override;
      //virtual i32 SetMapMode(i32 nMapMode) override;
      // Context Origin
      point_f64 set_origin(double x, double y) override;
      point_f64 set_origin(const ::point_f64 & point_f64) override;
      point_f64 offset_origin(double nWidth, double nHeight) override;

      // Context Extent
      size_f64 get_extents() override;
      size_f64 set_extents(double cx, double cy) override;
      size_f64 set_extents(const ::size_f64 & size_f64) override;
      size_f64 scale_extents(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point_f64 GetWindowOrg() override;
      point_f64 SetWindowOrg(double x, double y) override;
      point_f64 SetWindowOrg(const ::point_f64 & point_f64) override;
      point_f64 offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      size_f64 GetWindowExt() override;
      size_f64 set_window_ext(double cx, double cy) override;
      size_f64 set_window_ext(const ::size_f64 & size_f64) override;
      size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

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
      void fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      void frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      void invert_region(::draw2d::region* pRgn) override;
      void paint_region(::draw2d::region* pRgn) override;

      // Clipping Functions
      i32 get_clip_box(::rectangle_f64 * prectangle) override;


      void intersect_clip(const ::rectangle_f64 & rectangle) override;

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

      void reset_clip() override;

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      void _intersect_clip() override;
      //virtual void _add_shape(const ::rectangle_f64 & rectangle_f64) override;
      void _add_clipping_shape(const ::rectangle & rectangle_f64, ___shape < ::draw2d::region >* pshape) override;
      //virtual void _add_shape(const ::ellipse & ellipse) override;
      void _add_clipping_shape(const ::ellipse & ellipse, ___shape < ::draw2d::region >* pshape) override;
      //virtual void _add_shape(const ::polygon_i32 & polygon_i32) override;
      void _add_clipping_shape(const ::polygon & polygon_i32, ___shape < ::draw2d::region >* pshape) override;

      void _add_shape(const ::rectangle_f64 & rectangle_f64);
      //virtual void _add_shape(const ::ellipse & ellipse) override;
      void _add_shape(const ::ellipse & ellipse);
      //virtual void _add_shape(const ::polygon_i32 & polygon_i32) override;
      void _add_shape(const ::polygon_f64 & polygon_i32);


      // Line-Output Functions
      point_f64 current_position() override;
      void set_current_point(double x, double y) override;
      //    point_f64 MoveTo(const ::point_f64 & point_f64) override;
      void line_to(double x, double y) override;
      //  bool LineTo(const ::point_f64 & point_f64) override;
      void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;
      void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc(double x, double y, double w, double h, angle start, angle extends) override;
      void arc(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void polyline(const ::point_f64 * lpPoints, count nCount) override;

      void angle_arc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      //bool ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc_to(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      //i32 GetArcDirection() override;
      //i32 SetArcDirection(i32 nArcDirection) override;

      void polydraw(const ::point_f64* lpPoints, const byte* lpTypes, count nCount) override;
      void polyline_to(const ::point_f64* lpPoints, count nCount) override;
      void poly_polyline(const ::point_f64* lpPoints, const ::i32 * lpPolyPoints, count nCount) override;

      void poly_bezier(const ::point_f64* lpPoints, count nCount) override;
      void poly_bezier_to(const ::point_f64* lpPoints, count nCount) override;

      // Simple Drawing Functions
      void fill_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::brush* pBrush) override;
      void draw_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::pen * ppen) override;
      //virtual bool frame_rectangle(const ::rectangle_f64 & rectangle_f64, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::rectangle_f64 & rectangle_f64) override;

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




      void Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                 double x4, double y4) override;
      void Chord(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void DrawFocusRect(const ::rectangle_f64 & rectangle_f64) override;

//      bool DrawEllipse(double x1, double y1, double x2, double y2) override;
//      bool DrawEllipse(const ::rectangle_f64 & rectangle_f64) override;
//
//      bool FillEllipse(double x1, double y1, double x2, double y2) override;
//      bool FillEllipse(const ::rectangle_f64 & rectangle_f64) override;

      void draw_ellipse(double x1, double y1, double x2, double y2) override;
      void draw_ellipse(const ::rectangle_f64 & rectangle_f64) override;

      void fill_ellipse(double x1, double y1, double x2, double y2) override;
      void fill_ellipse(const ::rectangle_f64 & rectangle_f64) override;

      void Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void Pie(const ::rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;

      void fill_polygon(const POINT_F64 * lpPoints, count nCount) override;

      void draw_polygon(const POINT_F64 * lpPoints, count nCount) override;


      void polygon(const POINT_F64 * lpPoints, count nCount) override;
      void rectangle(const ::rectangle_f64 & rectangle_f64) override;
      //virtual bool draw_rectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool DrawRectangle(const ::rectangle_f64 & rectangle_f64) override;
      //virtual bool FillRectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool FillRectangle(const ::rectangle_f64 & rectangle_f64) override;
      //bool roundRect(double x1, double y1, double x2, double y2, double x3, double y3) override;
      void round_rectangle(const ::rectangle_f64 & rectangle_f64, double dRadius) override;

      // Bitmap Functions
      //bool PatBlt(double x, double y, double nWidth, double nHeight) override;


      //virtual bool _draw_raw(const ::image_drawing & imagedrawing) override;
      void _draw_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawing, const ::point_f64 & pointSrc) override;
      bool _draw_blend(const ::image_drawing & imagedrawing) override;
      void _stretch_raw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::image_drawing_options & imagedrawing, const ::rectangle_f64 & rectdSrc) override;
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
      //bool SetPixelV(double x, double y, const ::color::color & color) override;
      //bool SetPixelV(const ::point_f64 & point_f64, const ::color::color & color) override;
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
      void TextOutRaw(double x, double y, const block & block) override;
      ///virtual bool text_out(double x, double y, const ::string & str) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle_f64, const ::string & lpszString, strsize nCount, int * lpDxWidths) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle_f64, const ::string & str, int * lpDxWidths) override;
//      virtual size_f64 TabbedTextOut(double x, double y, const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;
//      virtual size_f64 TabbedTextOut(double x, double y, const ::string & str, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;

      virtual void internal_draw_text_cairo(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnText = nullptr);
      virtual void internal_draw_text(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#if defined(USE_PANGO)
      virtual void internal_draw_text_pango(::draw2d_cairo::font * pfont, const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_PANGO_TEXT pfnText = nullptr);
//#else
//      virtual void internal_draw_text(const block & block, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnTtext);
#endif
      //virtual bool draw_text(const ::string & lpszString, strsize nCount, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      void draw_text(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual bool draw_text_ex(char * lpszString, strsize nCount, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      //virtual bool draw_text_ex(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams = nullptr) override;
      void draw_text_ex(const ::string & str, const ::rectangle_f64 & rectangle_f64, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      size_f64 get_text_extent(const char * lpszString, strsize nCount, strsize iIndex) override;
      size_f64 get_text_extent(const char * lpszString, strsize nCount) override;
      size_f64 get_text_extent(const block & block) override;
      bool _GetTextExtent(size_f64 & size_f64, const char * lpszString, strsize nCount, strsize iIndex);
      void get_text_extent(size_f64 & size_f64, const char * lpszString, strsize nCount, strsize iIndex) override;
      void get_text_extent(size_f64 & size_f64, const char * lpszString, strsize nCount) override;
      void get_text_extent(size_f64 & size_f64, const ::string & str) override;
      //size_f64 GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      //size_f64 GetOutputTextExtent(const ::string & str) override;
      //size_f64 GetTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      //size_f64 GetTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions) override;
      //size_f64 GetOutputTabbedTextExtent(const ::string & lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      //size_f64 GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, int * lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, double nWidth, double nHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
      //i32 GetTextFace(count nCount, char * lpszFacename) override;
      //i32 GetTextFace(string & rString) override;
      void get_text_metrics(::write_text::text_metric * lpMetrics) override;
      void get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
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
      void abort_path() override;
      void begin_path() override;
      void close_figure() override;
      void end_path() override;
      void fill_path() override;
      void flatten_path() override;
      void stroke_and_fill_path() override;
      void stroke_path() override;
      void widen_path() override;


      using ::draw2d::graphics::draw;

      void draw(::draw2d::path * ppath) override;
      void fill(::draw2d::path * ppath) override;

      void draw(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      float GetMiterLimit() override;
      void SetMiterLimit(float fMiterLimit) override;
      //i32 GetPath(::point_f64 * lpPoints, LPBYTE lpTypes, count nCount) override;
      void SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      //static ::draw2d::brush* PASCAL GetHalftoneBrush(::object * pobject);
//      void DrawDragRect(const ::rectangle_f64 & rectangle_f64, const ::size_f64 & size_f64,
//                        const ::rectangle_f64 & rectangleLast, const ::size_f64 & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rectangle(const RECTANGLE_I64 * rectangle_f64, color32_t clr) override;
      //void fill_rectangle(const ::rectangle_f64 & rectangle_f64, const ::color::color & color) override;
      void fill_rectangle(const ::rectangle_f64 & rectangle_f64, const ::color::color & color) override;
      //void fill_rectangle(double x, double y, double cx, double cy, color32_t clr) override;
      //bool draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle_f64, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw_inset_3d_rectangle(double x, double y, double cx, double cy,
      //              color32_t clrTopLeft, color32_t clrBottomRight) override;




      // Implementation
   //public:

      //      HGDIOBJ SelectObject(HGDIOBJ) override;      // do not use for regions

      void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      void set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint) override;

//      virtual void * get_os_data() const override;
      //      virtual HDC get_handle() override;
      //    virtual HDC get_handle1() override;
      //  virtual HDC get_handle2() override;

      void attach(void * pdata) override;

      void clear_current_point() override;
      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      void blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle_f64) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h) override;


      // operating-system-specific or operating-system-internals
      bool _set_os_color(const ::color::color & color);
      bool _set(::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool _set(::draw2d::pen * ppen);
      bool _set(::write_text::font * pfont);
      bool _set(::draw2d::path * ppath);

      bool _set(const ::point_i32_array & pointa);
      bool _set(const ::point_f64_array & pointa);

      bool _set(___shape<::draw2d::region> * pshape);
      bool _set(___shape<::draw2d::path> * pshape);
      bool _set(const enum_shape & eshape);


      bool _set(const ::arc & arc, const __pointer(::draw2d::region) & pregion);
      //bool _set(const ::line & line);
      //bool _set(const ::lines & lines);
      bool _set(const ::rectangle & rectangle, const __pointer(::draw2d::region) & pregion);
      bool _set(const ::ellipse & ellipse, const __pointer(::draw2d::region) & pregion);
      bool _set(const ::polygon & polygon, const __pointer(::draw2d::region) & pregion);
      bool _set(const ::write_text::text_out & textout, const __pointer(::draw2d::region) & pregion);
      bool _set(const ::write_text::draw_text & drawtext, const __pointer(::draw2d::region) & pregion);


      bool _set(const ::arc & arc, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::line & line, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::lines & lines, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::rectangle & rectangle, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::ellipse & ellipse, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::polygon & polygon, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::write_text::text_out & textout, const __pointer(::draw2d::path) & ppath);
      bool _set(const ::write_text::draw_text & drawtext, const __pointer(::draw2d::path) & ppath);


      bool _set(const ::arc & arc);
      bool _set(const ::line & line);
      bool _set(const ::lines & lines);
      bool _set(const ::rectangle & rectangle);
      bool _set(const ::ellipse & ellipse);
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


      void _get(::draw2d::matrix & matrix) override;
      void _set(const ::draw2d::matrix & matrix) override;


      void flush() override;

//#ifdef WINDOWS

  //    virtual bool attach_hdc(HDC hdc) override;
    //  virtual HDC detach_hdc() override;

//#endif

      //virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      //virtual ::file::path get_font_path(const ::string & strName, int iWeight, bool bItalic) override;


      FT_Face ftface(const ::string & pszFontName, int iWeight, bool bItalic);
      //FT_Face ftface(const ::block & block);

      //virtual void on_apply_clip_region() override;


   };


   CLASS_DECL_AURA string q_valid_string(string str);


} // namespace win





