#pragma once


#include "bred/gpu/graphics.h"



//struct OffscreenContext
//{
//   HWND window;
//   HDC dev_context;
//   HGLRC openGLContext;
//   ::i32 width;
//   ::i32 height;
//   //fbo_t* fbo;
//};
namespace typeface_freetype
{

   
   class draw2d;


   class CLASS_DECL_TYPEFACE_FREETYPE graphics :
      virtual public ::draw2d_gpu::graphics
   {
   public:

      
      //::plusplus::Matrix *           m_pm;
      //::plusplus::Graphics *         m_pgraphics;
      //::plusplus::GraphicsPath *     m_ppath;
      //::plusplus::GraphicsPath *     m_ppathPaint;
      //HGLRC                         m_hglrc;
      //HDC                           m_hdc;
      //HWND                          m_hwnd;
      ::i32_size                          m_size;
      //HDC                           m_hdcGraphics;
      ::f32                               m_z;
      //i32_point                           m_pointTranslate;
      // bool                                      m_bFont;
      ::i32_size                          m_sizeWindow;
      //HGLRC m_hrc;
      ::pointer < ::windowing::window >   m_pwindow;
      //::pointer<::gpu::context>          m_pgpucontextOpenGL;
      ::pointer < ::gpu::shader >         m_pgpushaderTextOut;


      graphics();
      ~graphics() override;

#ifdef _DEBUG
         ::i64 increment_reference_count() override;
      ::i64 decrement_reference_count() override;
#endif

      void initialize(::particle * pparticle) override;
      //plusplus::Graphics & g()
      //{
      //   if(m_pgraphics == nullptr)
      //   {
      //      m_pgraphics = ::plusplus::Graphics::FromHDC(get_handle1());
      //   }
      //   return *m_pgraphics;
      //}
      //oswindow get_window_handle() const;
//      ::windowing::window * GetWindow() const;

      virtual void thread_select();
      void do_on_context(const ::procedure & procedure) override;
      
      
      void start_gpu_layer(::gpu::layer * pgpulayer) override;
      ::gpu::frame * end_gpu_layer() override;

      ::gpu_opengl::context* gpu_context();

      //void attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      void * detach() override;


      //void defer_add_graphics_render(::graphics::render * pgpurender) override;

      //virtual bool Attach(HDC hdc);   // attach/detach affects only the Output DC
      //virtual HDC Detach();
      //virtual bool AttachPrinter(HDC hdc);
      //virtual HDC DetachPrinter();
      //using draw2d::graphics::fill_rectangle;
      //void fill_rectangle(const ::f64_rectangle& rectangle, color32_t color32);


      //virtual void SetAttribDC(HDC hDC);  // set the Attribute DC
      //virtual void SetOutputDC(HDC hDC);  // set the Output DC
      //virtual void ReleaseAttribDC();     // Release the Attribute DC
      //virtual void ReleaseOutputDC();     // Release the Output DC

      //bool IsPrinting() const;            // true if being used for printing

      ::draw2d::pen *     get_current_pen() override;
      ::draw2d::brush *   get_current_brush() override;
      //::draw2d::palette_pointer get_current_palette() const;
      ::write_text::font *    get_current_font() override;
      ::draw2d::bitmap *  get_current_bitmap() override;


      void _draw_raw(const ::f64_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptionsParam, const ::f64_point & pointSrc) override;

      //plusplus::Pen *       gl2d_pen();
      //plusplus::Brush *     gl2d_brush();
      //plusplus::Font *      gl2d_font();

      // for bidi and mirrored localization
      ::u32 GetLayout() const;
      ::u32 SetLayout(::u32 dwLayout);


      //HDC get_hdc();
      //void release_hdc(HDC hdc);


      virtual ::f64 get_dpix() const;
      virtual ::f64 get_dpiy() const;

      // Constructors
      bool CreateDC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const_char_pointer pszOutput, const void * lpInitData);
      bool CreateIC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const_char_pointer pszOutput, const void * lpInitData);
      void create_memory_graphics(const ::i32_size & size = {}) override;
      void create_window_graphics(::windowing::window * pwindow) override;
      void create_compatible_graphics(::draw2d::graphics * pgraphics) override;

      //void set_hint_window_output() override;

      //virtual bool opengl_create_offscreen_buffer(const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::i32_rectangle & rectanglePlacement);
      virtual bool opengl_create_offscreen_buffer(const ::i32_size& rectanglePlacement);
      virtual bool opengl_delete_offscreen_buffer();

      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::i32_size& size) override;

      virtual bool opengl_defer_create_window_context(::windowing::window * pwindow);

      void DeleteDC() override;

      // Device-Context Functions
      ::i32 save_graphics_context()override;
      void restore_graphics_context(::i32 iSavedContext)override;
      //::i32 GetDeviceCaps(::i32 nIndex) override;
      ::u32 SetBoundsRect(const ::f64_rectangle & rectangleBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(::f64_rectangle * rectangleBounds, ::u32 flags) override;
      //bool ResetDC(const DEVMODE* lpDevMode);


      void resize(const ::i32_size & sizeWindow) override;


      // Drawing-Tool Functions
      i32_point GetBrushOrg() const;
      i32_point SetBrushOrg(::i32 x, ::i32 y);
      i32_point SetBrushOrg(const ::i32_point & point);
      ::i32 EnumObjects(::i32 nObjectType,
                          ::i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:

      ::typeface_freetype::draw2d * typeface_freetype();


      virtual ::draw2d::object* SelectStockObject(::i32 nIndex);
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::write_text::font* SelectObject(::write_text::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      ::i32 SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d::object* SelectObject(::draw2d::object* pObject);
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      // color and color Palette Functions
      color32_t GetNearestColor(color32_t crColor) const;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      ::u32 RealizePalette();
      void UpdateColors();

      ::i32 GetPolyFillMode() const;
      ::i32 GetROP2() const;
      ::i32 GetStretchBltMode() const;

      ::i32 SetPolyFillMode(::i32 nPolyFillMode);
      ::i32 SetROP2(::i32 nDrawMode);
      ::i32 set_interpolation_mode(::i32 nStretchMode);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      color32_t GetDCBrushColor() const;
      color32_t SetDCBrushColor(color32_t crColor);

      color32_t GetDCPenColor() const;
      color32_t SetDCPenColor(color32_t crColor);

#endif

      // Graphics mode
      ::i32 SetGraphicsMode(::i32 iMode);
      ::i32 GetGraphicsMode() const;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,::u32 iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual ::i32 GetMapMode() const;
      //virtual i32_point get_origin() const;
      virtual ::i32 SetMapMode(::i32 nMapMode);
      // Context Origin
      virtual i32_point set_origin(::i32 x, ::i32 y);
      virtual i32_point set_origin(const ::i32_point & point);
      virtual i32_point offset_origin(::i32 nWidth, ::i32 nHeight);

      // Context Extent
      virtual i32_size get_context_extents() const;
      //virtual i32_size set_context_extents(::i32 cx, ::i32 cy);
      //virtual i32_size set_context_extents(const ::i32_size & size);
      //virtual i32_size scale_context_extents(::i32 xNum, ::i32 xDenom, ::i32 yNum, ::i32 yDenom);

      // Window Origin
      i32_point GetWindowOrg() const;
      i32_point SetWindowOrg(::i32 x, ::i32 y);
      i32_point SetWindowOrg(const ::i32_point & point);
      i32_point offset_window_org(::i32 nWidth, ::i32 nHeight);

      // Window extent
      i32_size GetWindowExt() const;
      virtual i32_size set_window_ext(::i32 cx, ::i32 cy);
      i32_size set_window_ext(const ::i32_size & size);
      virtual i32_size scale_window_ext(::i32 xNum, ::i32 xDenom, ::i32 yNum, ::i32 yDenom);

      // Coordinate Functions
      void DPtoLP(::f64_point * ppoints,::collection::count nCount = 1) override;
      void DPtoLP(::f64_rectangle * prectangle) override;
      void DPtoLP(::f64_size * psize) override;
      void LPtoDP(::f64_point * ppoints,::collection::count nCount = 1) override;
      void LPtoDP(::f64_rectangle * prectangle) override;
      void LPtoDP(::f64_size * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::f64_size * pSize) override;
      void LPtoHIMETRIC(::f64_size * pSize) override;
      void HIMETRICtoDP(::f64_size * pSize) override;
      void HIMETRICtoLP(::f64_size * pSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, ::i32 nWidth, ::i32 nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      //bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual ::i32 get_clip_box(::f64_rectangle * prectangle) const;
      virtual bool PtVisible(::i32 x, ::i32 y) const;
      bool PtVisible(const ::i32_point & point) const;
      //virtual bool RectVisible(const ::i32_rectangle & i32_rectangle) const;
      ::i32 SelectClipRgn(::draw2d::region* pRgn);
      ::i32 ExcludeClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      ::i32 ExcludeClipRect(const ::i32_rectangle & i32_rectangle);
      ::i32 ExcludeUpdateRgn(::user::interaction_base * pwindow);
      ::i32 IntersectClipRect(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      ::i32 IntersectClipRect(const ::i32_rectangle & i32_rectangle);
      ::i32 OffsetClipRgn(::i32 x, ::i32 y);
      ::i32 OffsetClipRgn(const ::i32_size & size);
      ::i32 SelectClipRgn(::draw2d::region* pRgn, ::i32 nMode);


      void text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstr) override;
      //virtual void text_out_2024_and_before(::f64 x, ::f64 y, const ::scoped_string& scopedstr);

      // Line-Output Functions
      // i32_point GetCurrentPosition() const;
//      i32_point MoveTo(::i32 x, ::i32 y);
      //    i32_point MoveTo(const ::i32_point & point);
      void line_to(::f64 x, ::f64 y) override;
      //bool LineTo(::i32 x,::i32 y);
      //  bool LineTo(const ::i32_point & point);
      void polyline(const ::f64_point* ppoints,::collection::count nCount) override;

      void _set(const ::geometry2d::matrix & matrix) override;

      //using ::draw2d::graphics::Arc;
      //bool arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2,::i32 x3,::i32 y3,::i32 x4,::i32 y4);
      void arc(::f64 x1,::f64 y1,::f64 x2,::f64 y2,::f64 x3,::f64 y3,::f64 x4,::f64 y4);

      //bool Arc(::i32 x1,::i32 y1,::i32 x2,::i32 y2,::f64 start, ::f64 extends);
      void arc(::f64 x1,::f64 y1,::f64 x2,::f64 y2,::f64 start, ::f64 extends);

      void angle_arc(::f64 x, ::f64 y, ::f64 nRadius,::f64_angle fStartAngle, ::f64_angle fSweepAngle);
      void arc_to(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4);
      void arc_to(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd);
      //::i32 GetArcDirection() const;
      //::i32 SetArcDirection(::i32 nArcDirection);

      //void polydraw(const ::f64_point* lpPoints, const ::u8* lpTypes,::collection::count nCount);
      void polyline_to(const ::f64_point * lpPoints,::collection::count nCount);
      void poly_polyline(const ::f64_point * lpPoints, const ::i32 * lpPolyPoints,::collection::count nCount);

      void poly_bezier(const ::f64_point * lpPoints,::collection::count nCount);
      void poly_bezier_to(const ::f64_point * lpPoints,::collection::count nCount);

      // Simple Drawing Functions

      void fill_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color) override;
      void fill_rectangle(const ::f64_rectangle &  rectangle, ::draw2d::brush* pBrush) override;
      virtual void fill_rectangle_2025_06(const ::f64_rectangle& rectangle, ::draw2d::brush* pBrush);
      void frame_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      //bool DrawRect(const ::i32_rectangle & rectangle, ::draw2d::pen * ppen);
      void invert_rectangle(const ::f64_rectangle & i32_rectangle) override;
      //void draw_icon(::f64 x, ::f64 y, ::image::icon * picon) override;
      //void draw_icon(const ::i32_point & point, ::image::icon * picon);
      //void draw_icon(::f64 x, ::f64 y, ::image::icon * picon, ::i32 cx, ::i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, HBITMAP hBitmap, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, HICON hIcon, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, ::i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, const ::scoped_string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, ::i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::i32_point & point, const ::i32_size & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3,
                 ::i32 x4, ::i32 y4);
      bool Chord(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd);
      void DrawFocusRect(const ::i32_rectangle & i32_rectangle);

      //bool DrawEllipse(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      //bool DrawEllipse(const ::i32_rectangle & i32_rectangle);
      //bool FillEllipse(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      //bool FillEllipse(const ::i32_rectangle & i32_rectangle);

      //virtual bool DrawEllipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2);
      void draw_ellipse(const ::f64_rectangle & rectangle) override;
      //virtual bool fill_ellipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2);
      void fill_ellipse(const ::f64_rectangle & rectangle) override;

      //virtual bool Pie(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 x3, ::i32 y3, ::i32 x4, ::i32 y4) override;
      //virtual bool Pie(const ::i32_rectangle & rectangle, const ::i32_point & pointStart, const ::i32_point & pointEnd) override;
      void fill_polygon(const ::f64_point * lpPoints,::collection::count nCount) override;
      //void fill_polygon(const ::i32_point * lpPoints,::collection::count nCount) override;
      //void draw_polygon(const ::i32_point * lpPoints,::collection::count nCount) override;
      void draw_polygon(const ::f64_point * lpPoints,::collection::count nCount) override;
      //void i32_polygon(const ::i32_point* lpPoints,::collection::count nCount) override;
      void polygon(const ::f64_point* lpPoints,::collection::count nCount) override;
      void poly_polygon(const ::f64_point * lpPoints, const ::i32 * lpPolyCounts,::collection::count nCount) override;
      //virtual bool i32_rectangle(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2) override;
      void rectangle(const ::f64_rectangle & rectangle) override;
      //virtual bool drw(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      void draw_rectangle(const ::f64_rectangle & rectangle) override;
      void draw_rectangle(const ::f64_rectangle& rectangle, ::draw2d::pen * ppen) override;
      //virtual bool FillRectangle(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      void fill_rectangle(const ::f64_rectangle & rectangle);
      //void round_rectangle(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3) override;
      void round_rectangle(const ::f64_rectangle & rectangle, const ::i32_point & point);

      // Bitmap Functions
      //bool PatBlt(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight);
      //virtual bool BitBltRaw(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics* pgraphicsSrc, ::i32 xSrc, ::i32 ySrc) override;
      //virtual bool StretchBltRaw(::i32 xDst, ::i32 yDst, ::i32 nDstWidth, ::i32 nDstHeight, ::draw2d::graphics* pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight) override;
//      {

//         bool StretchBlt(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight);
      ::color::color GetPixel(::i32 x, ::i32 y) const;
      ::color::color GetPixel(const ::i32_point & point) const;
      ::color::color SetPixel(::f64 x, ::f64 y, ::color::color crColor);
      ::color::color SetPixel(const ::i32_point & point, ::color::color crColor);
//      bool FloodFill(::i32 x, ::i32 y, color32_t crColor);
//      bool ExtFloodFill(::i32 x, ::i32 y, color32_t crColor, ::u32 nFillType);
//      bool MaskBlt(::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   ::i32 xSrc, ::i32 ySrc, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask,
//                   ::u32 dwRop);
//      bool PlgBlt(::i32_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc,
//                  ::i32 nWidth, ::i32 nHeight, ::draw2d::bitmap& maskBitmap, ::i32 xMask, ::i32 yMask);
      void SetPixelV(::i32 x, ::i32 y, ::color::color crColor);
      void SetPixelV(const ::i32_point & point, ::color::color crColor);
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, ::u32 dwMode);
      void TransparentBlt(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
                          ::u32 clrTransparent);

      ///void alpha_blend(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight, ::f64 dOpacity);

      /*bool alpha_blend(::i32 xDest, ::i32 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, ::i32 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool TextOut(::i32 x, ::i32 y, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool TextOut(::i32 x, ::i32 y, const ::scoped_string & str);
      //virtual bool TextOut(::f64 x, ::f64 y, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool TextOut(::f64 x, ::f64 y, const ::scoped_string & str);
      //virtual bool ExtTextOut(::i32 x, ::i32 y, ::u32 nOptions, const ::i32_rectangle & rectangle, const ::scoped_string & lpszString,character_count nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(::i32 x, ::i32 y, ::u32 nOptions, const ::i32_rectangle & rectangle, const ::scoped_string & str, LPINT lpDxWidths);
      //virtual i32_size TabbedTextOut(::i32 x, ::i32 y, const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions, ::i32 nTabOrigin);
      //virtual i32_size TabbedTextOut(::i32 x, ::i32 y, const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions, ::i32 nTabOrigin);

      //void text_out(::f64 x, ::f64 y, const ::scoped_string & lpszString, character_count nCount) override;

      void draw_text(const ::scoped_string & str,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::scoped_string & str,const ::i32_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      void draw_text(const ::scoped_string & str,const ::f64_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual ::f64_size get_text_extent(const ::scoped_string & lpszString, character_count nCount, character_count iIndex) override;
      //virtual ::f64_size get_text_extent(const ::scoped_string & lpszString, character_count nCount) override;
      virtual ::f64_size get_text_extent(const ::scoped_string & str) override;
      //virtual bool get_text_extent(::f64_size & size, const ::scoped_string & lpszString, character_count nCount, character_count iIndex);
      //virtual bool get_text_extent(::f64_size & size, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool get_text_extent(::f64_size & size, const ::scoped_string & str);
      //virtual i32_size GetOutputTextExtent(const ::scoped_string & lpszString, character_count nCount);
      //virtual i32_size GetOutputTextExtent(const ::scoped_string & str);
      //virtual i32_size GetTabbedTextExtent(const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual i32_size GetTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual i32_size GetOutputTabbedTextExtent(const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual i32_size GetOutputTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, ::i32), LPARAM lpData, ::i32 nCount, ::i32 x, ::i32 y, ::i32 nWidth, ::i32 nHeight);
      virtual ::u32 GetTextAlign() override;
      virtual ::u32 SetTextAlign(::u32 nFlags) override;
      //virtual ::i32 GetTextFace(::collection::count nCount, char_pointer lpszFacename);
      //virtual ::i32 GetTextFace(string & rString);
      //virtual bool get_text_metrics(::write_text::text_metric * lpMetrics);
      //virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics);
      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric * pmetrics) override;
      void get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual ::i32 SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount);
      //virtual ::i32 GetTextCharacterExtra();
      //virtual ::i32 SetTextCharacterExtra(::i32 nCharExtra);

      //virtual ::u32 GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;
      //virtual ::u32 GetCharacterPlacement(const ::scoped_string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, ::i32 cgi, ::i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, ::i32 cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      bool DrawEdge(const ::i32_rectangle & rectangle,::u32 nEdge,::u32 nFlags);
//      bool DrawFrameControl(const ::i32_rectangle & rectangle,::u32 nType,::u32 nState);

      // Scrolling Functions
      //bool ScrollDC(::i32 Δx, ::i32 Δy, const ::i32_rectangle & lpRectScroll, const ::i32_rectangle & lpRectClip,
        //            ::draw2d::region* pRgnUpdate, ::i32_rectangle * lpRectUpdate);

      // font Functions
      //bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      //bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      //::u32 SetMapperFlags(::u32 dwFlag);
      //i32_size GetAspectRatioFilter() const;

      //bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
      //::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID lpData, ::u32 cbData) const;
      //::i32 GetKerningPairs(::i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      //::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const;
      //::u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //                         ::u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      //bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
                            //LPABCFLOAT lpABCF) const;
      //bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
                        //::f32* lpFloatBuffer) const;

      ::u32 GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual ::i32 Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & lpszInData, LPVOID lpOutData);
      ::i32 Escape(::i32 nEscape, ::i32 nInputSize,  const_char_pointer pszInputData,::i32 nOutputSize, char_pointer lpszOutputData);
      ::i32 DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & lpszInputData);

      // Escape helpers
      ::i32 StartDoc(const ::scoped_string & lpszDocName);  // old Win3.0 version
      ::i32 StartDoc(LPDOCINFO lpDocInfo);
      ::i32 StartPage();
      ::i32 EndPage();
      ::i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, ::i32));
      ::i32 AbortDoc();
      ::i32 EndDoc();

      // MetaFile Functions
      //bool PlayMetaFile(HMETAFILE hMF);
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::i32_rectangle & lpBounds);
      //bool AddMetaFileComment(::u32 nDataSize, const ::u8* pCommentData);
      // can be used for enhanced metafiles only

      // Path Functions
      void abort_path()override;
      void begin_path()override;
      void close_figure()override;
      void end_path()override;
      void fill_path()override;
      void flatten_path()override;
      void stroke_and_fill_path()override;
      void stroke_path()override;
      void widen_path() override;
      ::f32 GetMiterLimit() override;
      void SetMiterLimit(::f32 fMiterLimit) override;

      void draw(::draw2d::path * ppath);
      void draw(::draw2d::path * ppath, ::draw2d::pen * ppen);
      void fill(::draw2d::path * ppath);
      void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      //::f32 GetMiterLimit() const;
      //bool SetMiterLimit(::f32 fMiterLimit);
      //::i32 GetPath(::i32_point * lpPoints, LPBYTE lpTypes,::collection::count nCount) const;
      void SelectClipPath(::i32 nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush();
      //void DrawDragRect(const ::i32_rectangle & rectangle, const ::i32_size & size,
      //                  const ::i32_rectangle & lpRectLast, const ::i32_size & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const ::i64_rectangle * rectangle, color32_t clr);
      //void FillSolidRect(const ::i32_rectangle & rectangle, color32_t clr);
      //void FillSolidRect(::i32 x, ::i32 y, ::i32 cx, ::i32 cy, color32_t clr);
      /*void Draw3dRect(const ::i32_rectangle & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(::i32 x, ::i32 y, ::i32 cx, ::i32 cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);
*/

      //void draw_inset_3d_rectangle(const ::f64_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //virtual void draw_inset_3d_rectangle(const ::f64_rectangle & rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      //void draw_inset_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color, ::f64 dWidth, const ::e_border & eborder = e_border_all) override;
      //void frame_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color, const ::e_border & eborder = e_border_all) override;

      void intersect_clip(const ::draw2d::clip_group & clipgroup) override;
      void intersect_clip(const ::f64_rectangle & rectangle) override;

   public:
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      //HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      void set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode) override;

      void set_text_rendering_hint(::write_text::enum_rendering etextrendering) override;

      //virtual void * get_os_data() const;
      //virtual void * get_os_data_ex(::i32 i) const;
      //virtual void release_os_data_ex(::i32 i, void *p);
      //virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata);


      //virtual plusplus::FillMode gl2d_get_fill_mode();

      bool blur(bool bExpand, ::f64 dRadius, const ::i32_rectangle & rectangle);


      void flush() override;
      void sync_flush() override;

      //virtual bool DrawLine(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::draw2d::pen * ppen);
      //virtual bool DrawLine(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::draw2d::pen * ppen);

      
      void draw_line(const i32_point& point1, const i32_point& point2, ::draw2d::pen* ppen);


      //virtual void enum_fonts(::write_text::font_enumeration_item_array& itema) override;

      //void prefer_mapped_image_on_mix() override;

      virtual void set(::draw2d::region* pregion) override;
      virtual void set(::draw2d::pen* ppen) override;
      virtual void set(::write_text::font* pfont) override;
      virtual void set(::draw2d::brush* pbrush) override;
      virtual void set(::draw2d::bitmap* pbitmap) override;
      virtual ::draw2d::object* set_stock_object(::i32 nIndex) override;

      void create_window_graphics(::acme::windowing::window * pacmewindowingwindow) override;
      void is_valid_update_window_thread() override;


      //void _add_clipping_shape(const ::f64_rectangle & rectangle, ::draw2d::region * pregion) override;


      //void on_begin_draw() override;
      //void on_end_draw() override;
      //void on_end_draw() override;
      void on_present() override;

      
      bool _is_ok() const override;

      

   };


   CLASS_DECL_TYPEFACE_FREETYPE graphics * thread_graphics();

   CLASS_DECL_TYPEFACE_FREETYPE void thread_graphics(graphics * graphics);


} // namespace typeface_freetype





