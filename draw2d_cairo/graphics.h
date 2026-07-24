#pragma once


#include "acme/prototype/geometry2d/_collection.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


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


      ::i32                        m_iSaveContext;
      ::i32                        m_iSaveContextPositiveClip;
      cairo_t *                  m_pdc;
      ::i32                        m_iType;
      bool                       m_bPrinting;
      ::i32                        m_nStretchBltMode;
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
      ::u32 GetLayout() override;
      ::u32 SetLayout(::u32 dwLayout) override;


      ::f64 get_dpix() override;

      // Constructors
      //bool CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override;
      //bool CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData) override
      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::i32_size& size) override;
      void create_compatible_graphics(::draw2d::graphics * pgraphics) override;

      void DeleteDC() override;

      // Device-Context Functions
      ::i32 save_graphics_context() override;
      void restore_graphics_context(::i32 iSavedContext) override;
      ::i32 GetDevicecaps(::i32 nIndex);
      ::u32 SetBoundsRect(const ::f64_rectangle & rectangleBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(::f64_rectangle * rectangleBounds, ::u32 flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      ::f64_point GetBrushOrg() override;
      ::f64_point SetBrushOrg(::f64 x, ::f64 y) override;
      ::f64_point SetBrushOrg(const ::f64_point & point) override;
      //::i32 EnumObjects(::i32 nObjectType,
                      //::i32(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   //public:
      ::draw2d::object* set_stock_object(::i32 nIndex) override;
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

      //::i32 GetPolyFillMode() override;
      //::i32 GetROP2() override;
      //::i32 GetStretchBltMode() override;

      //::i32 SetPolyFillMode(::i32 nPolyFillMode) override;
      //::i32 SetROP2(::i32 nDrawMode) override;


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
      //::i32 SetGraphicsMode(::i32 iMode) override;
      //::i32 GetGraphicsMode() override;

//      // World transform
//      bool SetWorldTransform(const XFORM* pXform);
//      bool ModifyWorldTransform(const XFORM* pXform, ::u32 iMode);
//      bool GetWorldTransform(XFORM* pXform);

      // Mapping Functions
      //virtual ::i32 GetMapMode() override;
      //::f64_point get_origin() override;
      //virtual ::i32 SetMapMode(::i32 nMapMode) override;
      // Context Origin
      //::f64_point set_origin(::f64 x, ::f64 y) override;
      //::f64_point set_origin(const ::f64_point & point) override;
      //::f64_point offset_origin(::f64 nWidth, ::f64 nHeight) override;

      // Context Extent
      ::f64_size get_extents() override;
      ::f64_size set_extents(::f64 cx, ::f64 cy) override;
      ::f64_size set_extents(const ::f64_size & size) override;
      ::f64_size scale_extents(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom) override;

      // Window Origin
      ::f64_point GetWindowOrg() override;
      ::f64_point SetWindowOrg(::f64 x, ::f64 y) override;
      ::f64_point SetWindowOrg(const ::f64_point & point) override;
      ::f64_point offset_window_org(::f64 nWidth, ::f64 nHeight) override;

      // Window extent
      ::f64_size GetWindowExt() override;
      //::f64_size set_window_ext(::f64 cx, ::f64 cy) override;
      //::f64_size set_window_ext(const ::f64_size & size) override;
      //::f64_size scale_window_ext(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom) override;

      // Coordinate Functions
      void DPtoLP(::f64_point * lpPoints, ::collection::count nCount = 1) override;
      void DPtoLP(::f64_rectangle * prectangle) override;
      void DPtoLP(::f64_size * psize) override;
      void LPtoDP(::f64_point * lpPoints, ::collection::count nCount = 1) override;
      void LPtoDP(::f64_rectangle * prectangle) override;
      void LPtoDP(::f64_size * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::f64_size * psize) override;
      //void LPtoHIMETRIC(::f64_size * psize) override;
      void HIMETRICtoDP(::f64_size * psize) override;
      //void HIMETRICtoLP(::f64_size * psize) override;

      // Region Functions
      void fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      void frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, ::f64 nWidth, ::f64 nHeight) override;
      void invert_region(::draw2d::region* pRgn) override;
      void paint_region(::draw2d::region* pRgn) override;

      // Clipping Functions
      ::i32 get_clip_box(::f64_rectangle & rectangle) override;

      //void _intersect_clip() override;
      //void _add_shape(const ::f64_rectangle & rectangle) override;
      //void _add_shape(const ::f64_ellipse & ellipse) override;
      //void _add_shape(const ::f64_polygon_base & polygon) override;

      //void intersect_clip(const ::f64_rectangle & rectangle) override;
      //void intersect_clip(const ::f64_ellipse & rectangle) override;
      //void intersect_clip(const ::f64_polygon_base & rectangle) override;

      //void set_clipping(::draw2d::region* pregion) override;
      //virtual void intersect_clip(const ::draw2d::clip & clip);
      //virtual void intersect_clip(const ::draw2d::clip_group & clipgroup);
      //virtual void _add_clip_item(::draw2d::clip_item * pclipitem);


      //virtual bool PtVisible(::f64 x, ::f64 y) override;
      //bool PtVisible(const ::f64_point & point) override;
      //virtual bool RectVisible(const ::f64_rectangle & rectangle) override;
      //::i32 SelectClipRgn(::draw2d::region* pRgn) override;
      //::i32 ExcludeClipRect(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      //::i32 ExcludeClipRect(const ::f64_rectangle & rectangle) override;
      //::i32 ExcludeUpdateRgn(::user::interaction_base * pwindow);
      //virtual ::i32 IntersectClipRect(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      //virtual ::i32 IntersectClipRect(const ::f64_rectangle & rectangle) override;
      //::i32 OffsetClipRgn(::f64 x, ::f64 y) override;
      //::i32 OffsetClipRgn(const ::f64_size & size) override;
      //::i32 SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      bool fill_contains(const ::f64_point & point) override;

      void reset_clip() override;

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      void _intersect_clip() override;
      void _eo_clip() override;
      //virtual void _add_shape(const ::f64_rectangle & rectangle) override;
      //void _add_shape(const ::f64_rectangle & rectangle, ::draw2d::region * pregion) override;
      //virtual void _add_shape(const ::f64_ellipse & ellipse) override;
      //void _add_clipping_shape(const ::f64_ellipse & ellipse, ::draw2d::region * pregion) override;
      //virtual void _add_shape(const ::i32_polygon & i32_polygon) override;
      //void _add_clipping_shape(const ::f64_polygon_base & i32_polygon, ::draw2d::region * pregion) override;

      void _add_shape(const ::f64_rectangle & rectangle) override;
      //virtual void _add_shape(const ::f64_ellipse & ellipse) override;
      void _add_shape(const ::f64_ellipse & ellipse) override;
      //virtual void _add_shape(const ::i32_polygon & i32_polygon) override;
      void _add_shape(const ::f64_polygon_base & i32_polygon) override;


      // Line-Output Functions
      ::f64_point current_position() override;
      //void set_current_point(::f64 x, ::f64 y) override;
      //    ::f64_point MoveTo(const ::f64_point & point) override;
      void line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      //  bool LineTo(const ::f64_point & point) override;
      void line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen) override;
      void arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4) override;
      void arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, ::f64_angle start, ::f64_angle extends) override;
      void arc(const ::f64_rectangle & rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;
      void polyline(const ::f64_point * lpPoints, ::collection::count nCount) override;

      void angle_arc(::f64 x, ::f64 y, ::f64 nRadius, ::f64_angle fStartAngle, ::f64_angle fSweepAngle) override;
      //bool ArcTo(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4) override;
      void arc_to(const ::f64_rectangle & rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;
      //::i32 GetArcDirection() override;
      //::i32 SetArcDirection(::i32 nArcDirection) override;

      void polydraw(const ::f64_point* lpPoints, const ::u8* lpTypes, ::collection::count nCount) override;
      void polyline_to(const ::f64_point* lpPoints, ::collection::count nCount) override;
      void poly_polyline(const ::f64_point* lpPoints, const ::i32 * lpPolyPoints, ::collection::count nCount) override;

      void poly_bezier(const ::f64_point* lpPoints, ::collection::count nCount) override;
      void poly_bezier_to(const ::f64_point* lpPoints, ::collection::count nCount) override;

      // Simple Drawing Functions
      void fill_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void draw_rectangle(const ::f64_rectangle & rectangle, ::draw2d::pen * ppen) override;
      //virtual bool frame_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      void invert_rectangle(const ::f64_rectangle & rectangle) override;

      //bool DrawIcon(::f64 x, ::f64 y, ::image::icon * picon) override;
      //virtual bool draw(const ::f64_point & point, ::image::icon * picon, const ::f64_size & size) override;
      //bool DrawIcon(::f64 x, ::f64 y, ::image::icon * picon, ::f64 cx, ::f64 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
      //bool DrawState(const ::f64_point & point, const ::f64_size & size, HBITMAP hBitmap, ::u32 nFlags,
        //             HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::f64_point & point, const ::f64_size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::f64_point & point, const ::f64_size & size, const ::scoped_string & scopedstrText, ::u32 nFlags,
//                     bool bPrefixText = true, ::i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::f64_point & point, const ::f64_size & size, const ::scoped_string & scopedstrText, ::u32 nFlags,
//                     bool bPrefixText = true, ::i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;




      void Chord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3,
                 ::f64 x4, ::f64 y4) override;
      void Chord(const ::f64_rectangle & rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;
      void DrawFocusRect(const ::f64_rectangle & rectangle) override;

//      bool DrawEllipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
//      bool DrawEllipse(const ::f64_rectangle & rectangle) override;
//
//      bool FillEllipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
//      bool FillEllipse(const ::f64_rectangle & rectangle) override;

      void draw_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      void draw_ellipse(const ::f64_rectangle & rectangle) override;

      void fill_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      void fill_ellipse(const ::f64_rectangle & rectangle) override;

      void Pie(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4) override;
      void Pie(const ::f64_rectangle & rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd) override;

      void fill_polygon(const ::f64_point * lpPoints, ::collection::count nCount) override;

      void draw_polygon(const ::f64_point * lpPoints, ::collection::count nCount) override;


      void polygon(const ::f64_point * lpPoints, ::collection::count nCount) override;
      void rectangle(const ::f64_rectangle & rectangle) override;
      //virtual bool draw_rectangle(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      //virtual bool DrawRectangle(const ::f64_rectangle & rectangle) override;
      //virtual bool FillRectangle(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) override;
      //virtual bool FillRectangle(const ::f64_rectangle & rectangle) override;
      //bool roundRect(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3) override;
      void round_rectangle(const ::f64_rectangle & rectangle, ::f64 dRadius) override;

      // Bitmap Functions
      //bool PatBlt(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight) override;


      //virtual bool _draw_raw(const ::image::image_drawing & imagedrawing) override;
      void _draw_raw(const ::f64_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawing, const ::f64_point & pointSrc) override;
      bool _draw_blend(const ::image::image_drawing & imagedrawing) override;
      void _stretch_raw(const ::f64_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawing, const ::f64_rectangle & rectdSrc) override;
      //bool _stretch_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource) override;


      ::color::color GetPixel(::f64 x, ::f64 y) override;
      ::color::color GetPixel(const ::f64_point & point) override;
      ::color::color SetPixel(::f64 x, ::f64 y, const ::color::color & color) override;
      ::color::color SetPixel(const ::f64_point & point, const ::color::color & color) override;
//      bool FloodFill(::f64 x, ::f64 y, const ::color::color & color) override;
//      bool ExtFloodFill(::f64 x, ::f64 y, const ::color::color & color, ::u32 nFillType) override;
//      bool MaskBlt(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   ::f64 xSrc, ::f64 ySrc, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::f64 yMask,
//                   ::u32 dwRop) override;
//      bool PlgBlt(::f64_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::f64 ySrc,
//                  ::f64 nWidth, ::f64 nHeight, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::f64 yMask) override;
      //bool SetPixelV(::f64 x, ::f64 y, const ::color::color & color) override;
      //bool SetPixelV(const ::f64_point & point, const ::color::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, ::u32 dwMode) override;
//      bool TransparentBlt(::f64 xDest, ::f64 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::f64 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
//                          ::u32 clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource, ::f64 dOpacity) override;

      /*bool alpha_blend(::f64 xDest, ::f64 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::f64 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount) override;
      //virtual bool text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstr) override;
      void TextOutRaw(::f64 x, ::f64 y, const ::scoped_string & scopedstr) override;
      ///virtual bool text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstr) override;
      //virtual bool ExtTextOut(::f64 x, ::f64 y, ::u32 nOptions, const ::f64_rectangle & rectangle, const ::scoped_string & scopedstrString, character_count nCount, ::i32 * lpDxWidths) override;
      //virtual bool ExtTextOut(::f64 x, ::f64 y, ::u32 nOptions, const ::f64_rectangle & rectangle, const ::scoped_string & scopedstr, ::i32 * lpDxWidths) override;
//      virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions, ::i32 nTabOrigin) override;
//      virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions, ::i32 nTabOrigin) override;

      virtual void internal_draw_text_cairo(const block & block, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnText = nullptr);
      virtual void internal_draw_text(const block & block, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#if defined(USE_PANGO)
      virtual void internal_draw_text_pango(::draw2d_cairo::font * pfont, const block & block, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_PANGO_TEXT pfnText = nullptr);
//#else
//      virtual void internal_draw_text(const block & block, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnTtext);
#endif
      //virtual bool draw_text(const ::scoped_string & scopedstrString, character_count nCount, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      void draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual bool draw_text_ex(char_pointer lpszString, character_count nCount, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      //virtual bool draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams = nullptr) override;
      void draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      ::f64_size _get_text_extent(const ::scoped_string & scopedstr, character_count iIndex) override;
      ::f64_size _get_text_extent(const ::scoped_string & scopedstr) override;
      //::f64_size get_text_extent(const block & block) override;
      bool _GetTextExtent(::f64_size & size, const_char_pointer pszString, character_count nCount, character_count iIndex);
      //::f64_size get_text_extent(const ::scoped_string & scopedstr, character_count iIndex) override;
      //::f64_size get_text_extent(const ::scoped_string & scopedstr) override;
      ///::f64_size get_text_extent(const ::scoped_string & scopedstr) override;
      //::f64_size GetOutputTextExtent(const_char_pointer pszString, character_count nCount) override;
      //::f64_size GetOutputTextExtent(const ::scoped_string & scopedstr) override;
      //::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions) override;
      //::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions) override;
      //::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions) override;
      //::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, ::i32), LPARAM lpData, ::i32 nCount, ::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
      //::i32 GetTextFace(count nCount, char_pointer lpszFacename) override;
      //::i32 GetTextFace(string & rString) override;
      void get_text_metrics(::write_text::text_metric * lpMetrics) override;
      void get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
//      ::i32 SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount) override;
//      ::i32 GetTextCharacterExtra() override;
//      ::i32 SetTextCharacterExtra(::i32 nCharExtra) override;

      //xxx      ::u32 GetCharacterPlacement(const ::string & lpString, ::i32 nCount, ::i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) override;
      //xxx      ::u32 GetCharacterPlacement(string & str, ::i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, ::i32 cgi, ::i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt ::f64_size ::f64_size) override;
//      bool GetTextExtentPointI(LPWORD pgiIn, ::i32 cgi, __out_opt ::f64_size ::f64_size) override;
//
//#endif

//      // Advanced Drawing
//      bool DrawEdge(const ::f64_rectangle & rectangle, ::u32 nEdge, ::u32 nFlags) override;
//      bool DrawFrameControl(const ::f64_rectangle & rectangle, ::u32 nType, ::u32 nState) override;

//      // Scrolling Functions
//      bool ScrollDC(::i32 Δx, ::i32 Δy, const ::f64_rectangle & rectangleScroll, const ::f64_rectangle & rectangleClip,
//                    ::draw2d::region* pRgnUpdate, ::i32_rectangle * lpRectUpdate) override;

//      // font Functions
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      ::u32 SetMapperFlags(::u32 dwFlag) override;
//      ::f64_size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) override;
//      ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID lpData, ::u32 cbData) override;
      //xxx      ::i32 GetKerningPairs(::i32 nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      ::u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    ::u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//      //xxx         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        ::f32* lpFloatBuffer) override;
//
//      ::u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) override;
//      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual ::i32 Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData) override;
//      ::i32 Escape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData, ::i32 nOutputSize, char_pointer lpszOutputData) override;
//      ::i32 DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData) override;
//
      // Escape helpers
      //::i32 StartDoc(const ::scoped_string & scopedstrDocName) override;  // old Win3.0 version
//xxx      ::i32 StartDoc(LPDOCINFO lpDocInfo) override;
      ::i32 StartPage() override;
      ::i32 EndPage() override;
      //::i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, ::i32)) override;
      ::i32 AbortDoc() override;
      ::i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::f64_rectangle & rectangleBounds) override;
      //    bool AddMetaFileComment(::u32 nDataSize, const ::u8* pCommentData) override;
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

      ::f32 GetMiterLimit() override;
      void SetMiterLimit(::f32 fMiterLimit) override;
      //::i32 GetPath(::f64_point * lpPoints, LPBYTE lpTypes, ::collection::count nCount) override;
      void SelectClipPath(::i32 nMode) override;

      // Misc Helper Functions
      //static ::draw2d::brush* PASCAL GetHalftoneBrush(::particle * pparticle);
//      void DrawDragRect(const ::f64_rectangle & rectangle, const ::f64_size & size,
//                        const ::f64_rectangle & rectangleLast, const ::f64_size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rectangle(const ::i64_rectangle * ::f64_rectangle, color32_t clr) override;
      //void fill_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color) override;
      void fill_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color) override;
      //void fill_rectangle(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, color32_t clr) override;
      //bool draw_inset_3d_rectangle(const ::f64_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw_inset_3d_rectangle(::f64 x, ::f64 y, ::f64 cx, ::f64 cy,
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

      void blur(bool bExpand, ::f64 dRadius, const ::f64_rectangle & rectangle) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h) override;


      // operating_system-specific or operating_system-internals
      bool _set_os_color(const ::color::color & color);
      bool _set(::draw2d::brush * pbrush, ::f64 x = 0.0, ::f64 y = 0.0);
      bool _set(::draw2d::pen * ppen);
      bool _set(::write_text::font * pfont);
      bool _set(::draw2d::path * ppath);

      bool _set(const ::i32_point_array & pointa);
      bool _set(const ::f64_point_array & pointa);

      //bool _set(___shape<::draw2d::region> * pshape);
      //bool _set(___shape<::draw2d::path> * pshape);
      bool _set(::geometry2d::item * pitem) override;
      bool _set(::draw2d::region * pregion);
      //bool _set(::draw2d::path * ppath);
      bool _set(const ::draw2d::enum_item & eitem) override;


      bool _set(const ::f64_arc & arc, const ::pointer<::draw2d::region>& pregion) override;
      //bool _set(const ::line & line) override;
      //bool _set(const ::lines & lines) override;
      bool _set(const ::f64_rectangle & rectangle, const ::pointer<::draw2d::region>& pregion) override;
      bool _set(const ::f64_ellipse & ellipse, const ::pointer<::draw2d::region>& pregion) override;
      bool _set(const ::f64_polygon_base & polygon, const ::pointer<::draw2d::region>& pregion) override;
      bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::region>& pregion) override;
      bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::region>& pregion) override;


      bool _set(const ::f64_arc & arc, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::f64_line & line, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::f64_lines & lines, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::f64_rectangle & rectangle, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::f64_ellipse & ellipse, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::f64_polygon_base & polygon, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::path>& ppath) override;
      bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::path>& ppath) override;


      bool _set(const ::f64_arc & arc) override;
      bool _set(const ::f64_line & line) override;
      bool _set(const ::f64_lines & lines) override;
      bool _set(const ::f64_rectangle & rectangle) override;
      bool _set(const ::f64_ellipse & ellipse) override;
      bool _set(const ::f64_polygon_base & polygon) override;
      bool _set(const ::write_text::text_out & textout) override;
      bool _set(const ::write_text::draw_text & drawtext) override;


      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush, ::f64 xOrg  = 0.0, ::f64 yOrg = 0.0);
      bool _fill1(::draw2d::brush* pbrush, ::f64 xOrg = 0.0, ::f64 yOrg = 0.0);
      bool _fill2(::draw2d::brush* pbrush, ::f64 xOrg = 0.0, ::f64 yOrg = 0.0);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill(::f64 xOrg = 0.0, ::f64 yOrg = 0.0);
      bool _fill1(::f64 xOrg = 0.0, ::f64 yOrg = 0.0);
      bool _fill2(::f64 xOrg = 0.0, ::f64 yOrg = 0.0);
      bool draw();


      void _get(::geometry2d::matrix & matrix) override;
      void _set(const ::geometry2d::matrix & matrix) override;


      void flush() override;

//#ifdef WINDOWS

  //    virtual bool attach_hdc(HDC hdc) override;
    //  virtual HDC detach_hdc() override;

//#endif

      //virtual void enum_fonts(::write_text::font_enumeration_item_array & itema) override;

      //virtual ::file::path get_font_path(const ::scoped_string & scopedstrName, ::i32 iWeight, bool bItalic) override;


      FT_Face ftface(const ::scoped_string & scopedstrFontName, ::i32 iWeight, bool bItalic);
      //FT_Face ftface(const ::block & block);

      //virtual void on_apply_clip_region() override;


   };


   CLASS_DECL_AURA string q_valid_string(const ::scoped_string & scopedstr);


} // namespace win





