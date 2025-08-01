#pragma once


#include "acme/prototype/geometry2d/_collection.h"
#include "aura/graphics/draw2d/graphics.h"


typedef void FN_CAIRO_TEXT(cairo_t *, const_char_pointer );
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


      int                        m_iSaveContext;
      int                        m_iSaveContextPositiveClip;
      cairo_t *                  m_pdc;
      int                        m_iType;
      bool                       m_bPrinting;
      int                        m_nStretchBltMode;
      bool                       m_bToyQuotedFontSelection;

#ifdef WINDOWS
      cairo_surface_t *          m_psurfaceAttach;
      HDC                        m_hdcAttach;
#endif

      graphics();
      ~graphics() override;


      // void assert_ok() const override;
      //void dump(dump_context& dumpcontext) const override;


      void initialize(::particle * pparticle) override;

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
      unsigned int GetLayout() override;
      unsigned int SetLayout(unsigned int dwLayout) override;


      double get_dpix() override;

      // Constructors
      //bool CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      //bool CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override
      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      void DeleteDC() override;

      // Device-Context Functions
      int save_graphics_context() override;
      void restore_graphics_context(int iSavedContext) override;
      int GetDevicecaps(int nIndex);
      unsigned int SetBoundsRect(const ::double_rectangle & rectangleBounds, unsigned int flags) override;
      unsigned int GetBoundsRect(::double_rectangle * rectangleBounds, unsigned int flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      double_point GetBrushOrg() override;
      double_point SetBrushOrg(double x, double y) override;
      double_point SetBrushOrg(const ::double_point & double_point) override;
      //int EnumObjects(int nObjectType,
                      //int(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   //public:
      ::draw2d::object* set_stock_object(int nIndex) override;
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
      //unsigned int RealizePalette() override;
      //void UpdateColors() override;

      //int GetPolyFillMode() override;
      //int GetROP2() override;
      //int GetStretchBltMode() override;

      //int SetPolyFillMode(int nPolyFillMode) override;
      //int SetROP2(int nDrawMode) override;


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
      //int SetGraphicsMode(int iMode) override;
      //int GetGraphicsMode() override;

//      // World transform
//      bool SetWorldTransform(const XFORM* pXform);
//      bool ModifyWorldTransform(const XFORM* pXform, unsigned int iMode);
//      bool GetWorldTransform(XFORM* pXform);

      // Mapping Functions
      //virtual int GetMapMode() override;
      //double_point get_origin() override;
      //virtual int SetMapMode(int nMapMode) override;
      // Context Origin
      //double_point set_origin(double x, double y) override;
      //double_point set_origin(const ::double_point & double_point) override;
      //double_point offset_origin(double nWidth, double nHeight) override;

      // Context Extent
      double_size get_extents() override;
      double_size set_extents(double cx, double cy) override;
      double_size set_extents(const ::double_size & double_size) override;
      double_size scale_extents(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      double_point GetWindowOrg() override;
      double_point SetWindowOrg(double x, double y) override;
      double_point SetWindowOrg(const ::double_point & double_point) override;
      double_point offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      double_size GetWindowExt() override;
      //double_size set_window_ext(double cx, double cy) override;
      //double_size set_window_ext(const ::double_size & double_size) override;
      //double_size scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      void DPtoLP(::double_point * lpPoints, ::collection::count nCount = 1) override;
      void DPtoLP(::double_rectangle * prectangle) override;
      void DPtoLP(::double_size * psize) override;
      void LPtoDP(::double_point * lpPoints, ::collection::count nCount = 1) override;
      void LPtoDP(::double_rectangle * prectangle) override;
      void LPtoDP(::double_size * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::double_size * psize) override;
      //void LPtoHIMETRIC(::double_size * psize) override;
      void HIMETRICtoDP(::double_size * psize) override;
      //void HIMETRICtoLP(::double_size * psize) override;

      // Region Functions
      void fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      void frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      void invert_region(::draw2d::region* pRgn) override;
      void paint_region(::draw2d::region* pRgn) override;

      // Clipping Functions
      int get_clip_box(::double_rectangle & rectangle) override;

      //void _intersect_clip() override;
      //void _add_shape(const ::double_rectangle & rectangle) override;
      //void _add_shape(const ::double_ellipse & ellipse) override;
      //void _add_shape(const ::double_polygon & polygon) override;

      //void intersect_clip(const ::double_rectangle & rectangle) override;
      //void intersect_clip(const ::double_ellipse & rectangle) override;
      //void intersect_clip(const ::double_polygon & rectangle) override;

      //void set_clipping(::draw2d::region* pregion) override;
      //virtual void intersect_clip(const ::draw2d::clip & clip);
      //virtual void intersect_clip(const ::draw2d::clip_group & clipgroup);
      //virtual void _add_clip_item(::draw2d::clip_item * pclipitem);


      //virtual bool PtVisible(double x, double y) override;
      //bool PtVisible(const ::double_point & double_point) override;
      //virtual bool RectVisible(const ::double_rectangle & double_rectangle) override;
      //int SelectClipRgn(::draw2d::region* pRgn) override;
      //int ExcludeClipRect(double x1, double y1, double x2, double y2) override;
      //int ExcludeClipRect(const ::double_rectangle & double_rectangle) override;
      //int ExcludeUpdateRgn(::user::interaction_base * pwindow);
      //virtual int IntersectClipRect(double x1, double y1, double x2, double y2) override;
      //virtual int IntersectClipRect(const ::double_rectangle & double_rectangle) override;
      //int OffsetClipRgn(double x, double y) override;
      //int OffsetClipRgn(const ::double_size & double_size) override;
      //int SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      bool fill_contains(const double_point & point) override;

      void reset_clip() override;

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      void _intersect_clip() override;
      void _eo_clip() override;
      //virtual void _add_shape(const ::double_rectangle & double_rectangle) override;
      //void _add_shape(const ::double_rectangle & double_rectangle, ::draw2d::region * pregion) override;
      //virtual void _add_shape(const ::double_ellipse & ellipse) override;
      //void _add_clipping_shape(const ::double_ellipse & ellipse, ::draw2d::region * pregion) override;
      //virtual void _add_shape(const ::int_polygon & int_polygon) override;
      //void _add_clipping_shape(const ::double_polygon & int_polygon, ::draw2d::region * pregion) override;

      void _add_shape(const ::double_rectangle & double_rectangle) override;
      //virtual void _add_shape(const ::double_ellipse & ellipse) override;
      void _add_shape(const ::double_ellipse & ellipse) override;
      //virtual void _add_shape(const ::int_polygon & int_polygon) override;
      void _add_shape(const ::double_polygon & int_polygon) override;


      // Line-Output Functions
      double_point current_position() override;
      //void set_current_point(double x, double y) override;
      //    double_point MoveTo(const ::double_point & double_point) override;
      void line(double x1, double y1, double x2, double y2) override;
      //  bool LineTo(const ::double_point & double_point) override;
      void line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;
      void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc(double x, double y, double w, double h, ::double_angle start, ::double_angle extends) override;
      void arc(const ::double_rectangle & double_rectangle, const ::double_point & pointStart, const ::double_point & pointEnd) override;
      void polyline(const ::double_point * lpPoints, ::collection::count nCount) override;

      void angle_arc(double x, double y, double nRadius, ::double_angle fStartAngle, ::double_angle fSweepAngle) override;
      //bool ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc_to(const ::double_rectangle & double_rectangle, const ::double_point & pointStart, const ::double_point & pointEnd) override;
      //int GetArcDirection() override;
      //int SetArcDirection(int nArcDirection) override;

      void polydraw(const ::double_point* lpPoints, const unsigned char* lpTypes, ::collection::count nCount) override;
      void polyline_to(const ::double_point* lpPoints, ::collection::count nCount) override;
      void poly_polyline(const ::double_point* lpPoints, const int * lpPolyPoints, ::collection::count nCount) override;

      void poly_bezier(const ::double_point* lpPoints, ::collection::count nCount) override;
      void poly_bezier_to(const ::double_point* lpPoints, ::collection::count nCount) override;

      // Simple Drawing Functions
      void fill_rectangle(const ::double_rectangle & double_rectangle, ::draw2d::brush* pBrush) override;
      void draw_rectangle(const ::double_rectangle & double_rectangle, ::draw2d::pen * ppen) override;
      //virtual bool frame_rectangle(const ::double_rectangle & double_rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::double_rectangle & double_rectangle) override;

      //bool DrawIcon(double x, double y, ::image::icon * picon) override;
      //virtual bool draw(const ::double_point & double_point, ::image::icon * picon, const ::double_size & double_size) override;
      //bool DrawIcon(double x, double y, ::image::icon * picon, double cx, double cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags) override;
      //bool DrawState(const ::double_point & double_point, const ::double_size & double_size, HBITMAP hBitmap, unsigned int nFlags,
        //             HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::double_point & double_point, const ::double_size & double_size, ::draw2d::bitmap* pBitmap, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::double_point & double_point, const ::double_size & double_size, const ::scoped_string & scopedstrText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::double_point & double_point, const ::double_size & double_size, const ::scoped_string & scopedstrText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;




      void Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                 double x4, double y4) override;
      void Chord(const ::double_rectangle & double_rectangle, const ::double_point & pointStart, const ::double_point & pointEnd) override;
      void DrawFocusRect(const ::double_rectangle & double_rectangle) override;

//      bool DrawEllipse(double x1, double y1, double x2, double y2) override;
//      bool DrawEllipse(const ::double_rectangle & double_rectangle) override;
//
//      bool FillEllipse(double x1, double y1, double x2, double y2) override;
//      bool FillEllipse(const ::double_rectangle & double_rectangle) override;

      void draw_ellipse(double x1, double y1, double x2, double y2) override;
      void draw_ellipse(const ::double_rectangle & double_rectangle) override;

      void fill_ellipse(double x1, double y1, double x2, double y2) override;
      void fill_ellipse(const ::double_rectangle & double_rectangle) override;

      void Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void Pie(const ::double_rectangle & double_rectangle, const ::double_point & pointStart, const ::double_point & pointEnd) override;

      void fill_polygon(const ::double_point * lpPoints, ::collection::count nCount) override;

      void draw_polygon(const ::double_point * lpPoints, ::collection::count nCount) override;


      void polygon(const ::double_point * lpPoints, ::collection::count nCount) override;
      void rectangle(const ::double_rectangle & double_rectangle) override;
      //virtual bool draw_rectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool DrawRectangle(const ::double_rectangle & double_rectangle) override;
      //virtual bool FillRectangle(double x1, double y1, double x2, double y2) override;
      //virtual bool FillRectangle(const ::double_rectangle & double_rectangle) override;
      //bool roundRect(double x1, double y1, double x2, double y2, double x3, double y3) override;
      void round_rectangle(const ::double_rectangle & double_rectangle, double dRadius) override;

      // Bitmap Functions
      //bool PatBlt(double x, double y, double nWidth, double nHeight) override;


      //virtual bool _draw_raw(const ::image::image_drawing & imagedrawing) override;
      void _draw_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawing, const ::double_point & pointSrc) override;
      bool _draw_blend(const ::image::image_drawing & imagedrawing) override;
      void _stretch_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawing, const ::double_rectangle & rectdSrc) override;
      //bool _stretch_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource) override;


      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::double_point & double_point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::double_point & double_point, const ::color::color & color) override;
//      bool FloodFill(double x, double y, const ::color::color & color) override;
//      bool ExtFloodFill(double x, double y, const ::color::color & color, unsigned int nFillType) override;
//      bool MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                   unsigned int dwRop) override;
//      bool PlgBlt(::double_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//                  double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask) override;
      //bool SetPixelV(double x, double y, const ::color::color & color) override;
      //bool SetPixelV(const ::double_point & double_point, const ::color::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, unsigned int dwMode) override;
//      bool TransparentBlt(double xDest, double yDest, int nDestWidth, int nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, int nSrcWidth, int nSrcHeight,
//                          unsigned int clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource, double dOpacity) override;

      /*bool alpha_blend(double xDest, double yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool text_out(double x, double y, const ::scoped_string & scopedstrString, character_count nCount) override;
      //virtual bool text_out(double x, double y, const ::scoped_string & scopedstr) override;
      void TextOutRaw(double x, double y, const ::scoped_string & scopedstr) override;
      ///virtual bool text_out(double x, double y, const ::scoped_string & scopedstr) override;
      //virtual bool ExtTextOut(double x, double y, unsigned int nOptions, const ::double_rectangle & double_rectangle, const ::scoped_string & scopedstrString, character_count nCount, int * lpDxWidths) override;
      //virtual bool ExtTextOut(double x, double y, unsigned int nOptions, const ::double_rectangle & double_rectangle, const ::scoped_string & scopedstr, int * lpDxWidths) override;
//      virtual double_size TabbedTextOut(double x, double y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions, int nTabOrigin) override;
//      virtual double_size TabbedTextOut(double x, double y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * lpnTabStopPositions, int nTabOrigin) override;

      virtual void internal_draw_text_cairo(const block & block, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnText = nullptr);
      virtual void internal_draw_text(const block & block, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#if defined(USE_PANGO)
      virtual void internal_draw_text_pango(::draw2d_cairo::font * pfont, const block & block, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_PANGO_TEXT pfnText = nullptr);
//#else
//      virtual void internal_draw_text(const block & block, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnTtext);
#endif
      //virtual bool draw_text(const ::scoped_string & scopedstrString, character_count nCount, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      void draw_text(const ::scoped_string & scopedstr, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual bool draw_text_ex(char * lpszString, character_count nCount, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      //virtual bool draw_text_ex(const ::scoped_string & scopedstr, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams = nullptr) override;
      void draw_text_ex(const ::scoped_string & scopedstr, const ::double_rectangle & double_rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      double_size get_text_extent(const ::scoped_string & scopedstr, character_count iIndex) override;
      double_size get_text_extent(const ::scoped_string & scopedstr) override;
      //double_size get_text_extent(const block & block) override;
      bool _GetTextExtent(double_size & double_size, const_char_pointer lpszString, character_count nCount, character_count iIndex);
      //double_size get_text_extent(const ::scoped_string & scopedstr, character_count iIndex) override;
      //double_size get_text_extent(const ::scoped_string & scopedstr) override;
      ///double_size get_text_extent(const ::scoped_string & scopedstr) override;
      //double_size GetOutputTextExtent(const_char_pointer lpszString, character_count nCount) override;
      //double_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      //double_size GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions) override;
      //double_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * lpnTabStopPositions) override;
      //double_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions) override;
      //double_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, double x, double y, double nWidth, double nHeight) override;
      unsigned int GetTextAlign() override;
      unsigned int SetTextAlign(unsigned int nFlags) override;
      //int GetTextFace(count nCount, char * lpszFacename) override;
      //int GetTextFace(string & rString) override;
      void get_text_metrics(::write_text::text_metric * lpMetrics) override;
      void get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
//      int SetTextJustification(int nBreakExtra, int nBreakCount) override;
//      int GetTextCharacterExtra() override;
//      int SetTextCharacterExtra(int nCharExtra) override;

      //xxx      unsigned int GetCharacterPlacement(const ::string & lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;
      //xxx      unsigned int GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt ::double_size ::double_size) override;
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt ::double_size ::double_size) override;
//
//#endif

//      // Advanced Drawing
//      bool DrawEdge(const ::double_rectangle & double_rectangle, unsigned int nEdge, unsigned int nFlags) override;
//      bool DrawFrameControl(const ::double_rectangle & double_rectangle, unsigned int nType, unsigned int nState) override;

//      // Scrolling Functions
//      bool ScrollDC(int Δx, int Δy, const ::double_rectangle & rectangleScroll, const ::double_rectangle & rectangleClip,
//                    ::draw2d::region* pRgnUpdate, ::int_rectangle * lpRectUpdate) override;

//      // font Functions
//      bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) override;
//      unsigned int SetMapperFlags(unsigned int dwFlag) override;
//      double_size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) override;
//      unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData, unsigned int cbData) override;
      //xxx      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      unsigned int GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      unsigned int GetGlyphOutline(unsigned int nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar,
//      //xxx         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar,
//                        float* lpFloatBuffer) override;
//
//      unsigned int GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) override;
//      bool GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual int Escape(int nEscape, int nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData) override;
//      int Escape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData, int nOutputSize, char * lpszOutputData) override;
//      int DrawEscape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData) override;
//
      // Escape helpers
      //int StartDoc(const ::scoped_string & scopedstrDocName) override;  // old Win3.0 version
//xxx      int StartDoc(LPDOCINFO lpDocInfo) override;
      int StartPage() override;
      int EndPage() override;
      //int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int)) override;
      int AbortDoc() override;
      int EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::double_rectangle & rectangleBounds) override;
      //    bool AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData) override;
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
      //int GetPath(::double_point * lpPoints, LPBYTE lpTypes, ::collection::count nCount) override;
      void SelectClipPath(int nMode) override;

      // Misc Helper Functions
      //static ::draw2d::brush* PASCAL GetHalftoneBrush(::particle * pparticle);
//      void DrawDragRect(const ::double_rectangle & double_rectangle, const ::double_size & double_size,
//                        const ::double_rectangle & rectangleLast, const ::double_size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rectangle(const ::long_long_rectangle * double_rectangle, color32_t clr) override;
      //void fill_rectangle(const ::double_rectangle & double_rectangle, const ::color::color & color) override;
      void fill_rectangle(const ::double_rectangle & double_rectangle, const ::color::color & color) override;
      //void fill_rectangle(double x, double y, double cx, double cy, color32_t clr) override;
      //bool draw_inset_3d_rectangle(const ::double_rectangle & double_rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw_inset_3d_rectangle(double x, double y, double cx, double cy,
      //              color32_t clrTopLeft, color32_t clrBottomRight) override;




      
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

      void blur(bool bExpand, double dRadius, const ::double_rectangle & double_rectangle) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h) override;


      // operating_system-specific or operating_system-internals
      bool _set_os_color(const ::color::color & color);
      bool _set(::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool _set(::draw2d::pen * ppen);
      bool _set(::write_text::font * pfont);
      bool _set(::draw2d::path * ppath);

      bool _set(const ::int_point_array & pointa);
      bool _set(const ::double_point_array & pointa);

      //bool _set(___shape<::draw2d::region> * pshape);
      //bool _set(___shape<::draw2d::path> * pshape);
      bool _set(::geometry2d::item * pitem);
      bool _set(::draw2d::region * pregion);
      //bool _set(::draw2d::path * ppath);
      bool _set(const ::draw2d::enum_item & eitem);


      bool _set(const ::double_arc & arc, const ::pointer<::draw2d::region>& pregion);
      //bool _set(const ::line & line);
      //bool _set(const ::lines & lines);
      bool _set(const ::double_rectangle & rectangle, const ::pointer<::draw2d::region>& pregion);
      bool _set(const ::double_ellipse & ellipse, const ::pointer<::draw2d::region>& pregion);
      bool _set(const ::double_polygon & polygon, const ::pointer<::draw2d::region>& pregion);
      bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::region>& pregion);
      bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::region>& pregion);


      bool _set(const ::double_arc & arc, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::double_line & line, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::double_lines & lines, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::double_rectangle & rectangle, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::double_ellipse & ellipse, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::double_polygon & polygon, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::path>& ppath);
      bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::path>& ppath);


      bool _set(const ::double_arc & arc);
      bool _set(const ::double_line & line);
      bool _set(const ::double_lines & lines);
      bool _set(const ::double_rectangle & rectangle);
      bool _set(const ::double_ellipse & ellipse);
      bool _set(const ::double_polygon & polygon);
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


      void _get(::geometry2d::matrix & matrix) override;
      void _set(const ::geometry2d::matrix & matrix) override;


      void flush() override;

//#ifdef WINDOWS

  //    virtual bool attach_hdc(HDC hdc) override;
    //  virtual HDC detach_hdc() override;

//#endif

      //virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      //virtual ::file::path get_font_path(const ::scoped_string & scopedstrName, int iWeight, bool bItalic) override;


      FT_Face ftface(const ::scoped_string & scopedstrFontName, int iWeight, bool bItalic);
      //FT_Face ftface(const ::block & block);

      //virtual void on_apply_clip_region() override;


   };


   CLASS_DECL_AURA string q_valid_string(const ::scoped_string & scopedstr);


} // namespace win





