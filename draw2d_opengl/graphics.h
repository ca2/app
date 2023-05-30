#pragma once


#include "aura/graphics/draw2d/graphics.h"


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

   class draw2d;

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
      ::size_i32                    m_sizeWindow;
      HGLRC m_hrc;

      graphics();
      ~graphics() override;


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


      //void attach(void * pgraphics) override;   // attach/detach affects only the Output DC
      void * detach() override;

      //virtual bool Attach(HDC hdc);   // attach/detach affects only the Output DC
      //virtual HDC Detach();
      //virtual bool AttachPrinter(HDC hdc);
      //virtual HDC DetachPrinter();
      //using draw2d::graphics::fill_rectangle;
      //void fill_rectangle(const rectangle_f64& rectangle, color32_t color32);


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
      bool CreateDC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      bool CreateIC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      void create_memory_graphics(const ::size_i32 & size = nullptr) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      virtual bool opengl_create_offscreen_buffer(const ::size_i32 & size);
      virtual bool opengl_delete_offscreen_buffer();

      void DeleteDC() override;

      // Device-Context Functions
      i32 save_graphics_context()override;
      void restore_graphics_context(i32 iSavedContext)override;
      //i32 GetDeviceCaps(i32 nIndex) override;
      ::u32 SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(rectangle_f64 * rectangleBounds, ::u32 flags) override;
      //bool ResetDC(const DEVMODE* lpDevMode);


      void resize(const ::size_i32 & sizeWindow) override;


      // Drawing-Tool Functions
      point_i32 GetBrushOrg() const;
      point_i32 SetBrushOrg(i32 x, i32 y);
      point_i32 SetBrushOrg(const ::point_i32 & point);
      i32 EnumObjects(i32 nObjectType,
                          i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:

      ::draw2d_opengl::draw2d * draw2d_opengl();


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
      //virtual point_i32 get_origin() const;
      virtual i32 SetMapMode(i32 nMapMode);
      // Context Origin
      virtual point_i32 set_origin(i32 x, i32 y);
      virtual point_i32 set_origin(const ::point_i32 & point);
      virtual point_i32 offset_origin(i32 nWidth, i32 nHeight);

      // Context Extent
      virtual size_i32 get_context_extents() const;
      //virtual size_i32 set_context_extents(i32 cx, i32 cy);
      //virtual size_i32 set_context_extents(const ::size_i32 & size);
      //virtual size_i32 scale_context_extents(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

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
      void DPtoLP(::point_f64 * ppoints,::count nCount = 1) override;
      void DPtoLP(::rectangle_f64 * prectangle) override;
      void DPtoLP(::size_f64 * psize) override;
      void LPtoDP(::point_f64 * ppoints,::count nCount = 1) override;
      void LPtoDP(::rectangle_f64 * prectangle) override;
      void LPtoDP(::size_f64 * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::size_f64 * pSize) override;
      void LPtoHIMETRIC(::size_f64 * pSize) override;
      void HIMETRICtoDP(::size_f64 * pSize) override;
      void HIMETRICtoLP(::size_f64 * pSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      //bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual i32 get_clip_box(rectangle_f64 * prectangle) const;
      virtual bool PtVisible(i32 x, i32 y) const;
      bool PtVisible(const ::point_i32 & point) const;
      //virtual bool RectVisible(const ::rectangle_i32 & rectangle_i32) const;
      i32 SelectClipRgn(::draw2d::region* pRgn);
      i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 ExcludeClipRect(const ::rectangle_i32 & rectangle_i32);
      i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      i32 IntersectClipRect(const ::rectangle_i32 & rectangle_i32);
      i32 OffsetClipRgn(i32 x, i32 y);
      i32 OffsetClipRgn(const ::size_i32 & size);
      i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode);


      void text_out(double x, double y, const ::scoped_string & scopedstr) override;

      // Line-Output Functions
      // point_i32 GetCurrentPosition() const;
//      point_i32 MoveTo(i32 x, i32 y);
      //    point_i32 MoveTo(const ::point_i32 & point);
      void line_to(double x, double y) override;
      //bool LineTo(int x,int y);
      //  bool LineTo(const ::point_i32 & point);
      void polyline(const ::point_f64* ppoints,::count nCount) override;

      void set(const ::draw2d::matrix & matrix) override;

      //using ::draw2d::graphics::Arc;
      //bool arc(double x1, double y1, double x2, double y2,i32 x3,i32 y3,i32 x4,i32 y4);
      void arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);

      //bool Arc(i32 x1,i32 y1,i32 x2,i32 y2,double start, double extends);
      void arc(double x1,double y1,double x2,double y2,double start, double extends);

      void angle_arc(double x, double y, double nRadius,::angle fStartAngle, ::angle fSweepAngle);
      void arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      void arc_to(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      //i32 GetArcDirection() const;
      //i32 SetArcDirection(i32 nArcDirection);

      //void polydraw(const ::point_f64* lpPoints, const byte* lpTypes,::count nCount);
      void polyline_to(const ::point_f64 * lpPoints,::count nCount);
      void poly_polyline(const ::point_f64 * lpPoints, const ::i32 * lpPolyPoints,::count nCount);

      void poly_bezier(const ::point_f64 * lpPoints,::count nCount);
      void poly_bezier_to(const ::point_f64 * lpPoints,::count nCount);

      // Simple Drawing Functions
      void fill_rectangle(const ::rectangle_f64 &  rectangle, ::draw2d::brush* pBrush) override;
      void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;
      //bool DrawRect(const ::rectangle_i32 & rectangle, ::draw2d::pen * ppen);
      void invert_rectangle(const ::rectangle_f64 & rectangle_i32) override;
      //void draw_icon(double x, double y, ::draw2d::icon * picon) override;
      //void draw_icon(const ::point_i32 & point, ::draw2d::icon * picon);
      //void draw_icon(double x, double y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::scoped_string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::scoped_string & lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                 i32 x4, i32 y4);
      bool Chord(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      void DrawFocusRect(const ::rectangle_i32 & rectangle_i32);

      //bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool DrawEllipse(const ::rectangle_i32 & rectangle_i32);
      //bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      //bool FillEllipse(const ::rectangle_i32 & rectangle_i32);

      //virtual bool DrawEllipse(double x1,double y1,double x2,double y2);
      void draw_ellipse(const ::rectangle_f64 & rectangle) override;
      //virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      void fill_ellipse(const ::rectangle_f64 & rectangle) override;

      //virtual bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      //virtual bool Pie(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      void fill_polygon(const ::point_f64 * lpPoints,::count nCount) override;
      //void fill_polygon(const ::point_i32 * lpPoints,::count nCount) override;
      //void draw_polygon(const ::point_i32 * lpPoints,::count nCount) override;
      void draw_polygon(const ::point_f64 * lpPoints,::count nCount) override;
      //void polygon_i32(const ::point_i32* lpPoints,::count nCount) override;
      void polygon(const ::point_f64* lpPoints,::count nCount) override;
      void poly_polygon(const point_f64 * lpPoints, const i32 * lpPolyCounts,::count nCount) override;
      //virtual bool rectangle_i32(i32 x1, i32 y1, i32 x2, i32 y2) override;
      void rectangle(const ::rectangle_f64 & rectangle) override;
      //virtual bool drw(i32 x1, i32 y1, i32 x2, i32 y2);
      void draw_rectangle(const ::rectangle_f64 & rectangle) override;
      void draw_rectangle(const ::rectangle_f64& rectangle, ::draw2d::pen * ppen) override;
      //virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      void fill_rectangle(const ::rectangle_f64 & rectangle);
      //void round_rectangle(double x1, double y1, double x2, double y2, double x3, double y3) override;
      void round_rectangle(const ::rectangle_f64 & rectangle, const ::point_i32 & point);

      // Bitmap Functions
      //bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight);
      //virtual bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc) override;
      //virtual bool StretchBltRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics* pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight) override;
//      {

//         bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      ::color::color GetPixel(i32 x, i32 y) const;
      ::color::color GetPixel(const ::point_i32 & point) const;
      ::color::color SetPixel(double x, double y, ::color::color crColor);
      ::color::color SetPixel(const ::point_i32 & point, ::color::color crColor);
//      bool FloodFill(i32 x, i32 y, color32_t crColor);
//      bool ExtFloodFill(i32 x, i32 y, color32_t crColor, ::u32 nFillType);
//      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
//                   u32 dwRop);
//      bool PlgBlt(::point_i32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask);
      void SetPixelV(i32 x, i32 y, ::color::color crColor);
      void SetPixelV(const ::point_i32 & point, ::color::color crColor);
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, u32 dwMode);
      void TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                          ::u32 clrTransparent);

      ///void alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool TextOut(i32 x, i32 y, const ::scoped_string & lpszString, strsize nCount);
      //virtual bool TextOut(i32 x, i32 y, const ::scoped_string & str);
      //virtual bool TextOut(double x, double y, const ::scoped_string & lpszString, strsize nCount);
      //virtual bool TextOut(double x, double y, const ::scoped_string & str);
      //virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectangle_i32 & rectangle, const ::scoped_string & lpszString,strsize nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectangle_i32 & rectangle, const ::scoped_string & str, LPINT lpDxWidths);
      //virtual size_i32 TabbedTextOut(i32 x, i32 y, const ::scoped_string & lpszString, strsize nCount,::count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      //virtual size_i32 TabbedTextOut(i32 x, i32 y, const ::scoped_string & str,::count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      //void text_out(double x, double y, const ::scoped_string & lpszString, strsize nCount) override;

      void draw_text(const ::scoped_string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::scoped_string & str,const ::rectangle_i32 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      void draw_text(const ::scoped_string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::string & str, const ::rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual size_f64 get_text_extent(const ::scoped_string & lpszString, strsize nCount, strsize iIndex) override;
      //virtual size_f64 get_text_extent(const ::scoped_string & lpszString, strsize nCount) override;
      virtual size_f64 get_text_extent(const ::scoped_string & str) override;
      //virtual bool get_text_extent(size_f64 & size, const ::scoped_string & lpszString, strsize nCount, strsize iIndex);
      //virtual bool get_text_extent(size_f64 & size, const ::scoped_string & lpszString, strsize nCount);
      //virtual bool get_text_extent(size_f64 & size, const ::scoped_string & str);
      //virtual size_i32 GetOutputTextExtent(const ::scoped_string & lpszString, strsize nCount);
      //virtual size_i32 GetOutputTextExtent(const ::scoped_string & str);
      //virtual size_i32 GetTabbedTextExtent(const ::scoped_string & lpszString, strsize nCount,::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetTabbedTextExtent(const ::scoped_string & str,::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetOutputTabbedTextExtent(const ::scoped_string & lpszString, strsize nCount,::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetOutputTabbedTextExtent(const ::scoped_string & str,::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);
      virtual ::u32 GetTextAlign() override;
      virtual ::u32 SetTextAlign(::u32 nFlags) override;
      //virtual i32 GetTextFace(::count nCount, char * lpszFacename);
      //virtual i32 GetTextFace(string & rString);
      //virtual bool get_text_metrics(::write_text::text_metric * lpMetrics);
      //virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics);
      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric * pmetrics) override;
      void get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      //virtual i32 GetTextCharacterExtra();
      //virtual i32 SetTextCharacterExtra(i32 nCharExtra);

      //virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;
      //virtual u32 GetCharacterPlacement(const ::scoped_string & lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;

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
      //bool ScrollDC(i32 greekdeltax, i32 greekdeltay, const ::rectangle_i32 & lpRectScroll, const ::rectangle_i32 & lpRectClip,
        //            ::draw2d::region* pRgnUpdate, ::rectangle_i32 * lpRectUpdate);

      // font Functions
      //bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      //bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const;
      //u32 SetMapperFlags(u32 dwFlag);
      //size_i32 GetAspectRatioFilter() const;

      //bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
      //u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const;
      //i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      //::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const;
      //u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //                         u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      //bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
                            //LPABCFLOAT lpABCF) const;
      //bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
                        //float* lpFloatBuffer) const;

      u32 GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const ::scoped_string & lpszInData, LPVOID lpOutData);
      i32 Escape(i32 nEscape, i32 nInputSize,  const char * lpszInputData,i32 nOutputSize, char * lpszOutputData);
      i32 DrawEscape(i32 nEscape, i32 nInputSize, const ::scoped_string & lpszInputData);

      // Escape helpers
      i32 StartDoc(const ::scoped_string & lpszDocName);  // old Win3.0 version
      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage();
      i32 EndPage();
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32));
      i32 AbortDoc();
      i32 EndDoc();

      // MetaFile Functions
      //bool PlayMetaFile(HMETAFILE hMF);
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_i32 & lpBounds);
      //bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData);
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
      float GetMiterLimit() override;
      void SetMiterLimit(float fMiterLimit) override;

      void draw(::draw2d::path * ppath);
      void draw(::draw2d::path * ppath, ::draw2d::pen * ppen);
      void fill(::draw2d::path * ppath);
      void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      //float GetMiterLimit() const;
      //bool SetMiterLimit(float fMiterLimit);
      //i32 GetPath(::point_i32 * lpPoints, LPBYTE lpTypes,::count nCount) const;
      void SelectClipPath(i32 nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush();
      //void DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_i32 & size,
      //                  const ::rectangle_i32 & lpRectLast, const ::size_i32 & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const ::rectangle_i64 * rectangle, color32_t clr);
      //void FillSolidRect(const ::rectangle_i32 & rectangle, color32_t clr);
      //void FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr);
      /*void Draw3dRect(const ::rectangle_i32 & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);
*/

      //void draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //virtual void draw_inset_3d_rectangle(const rectangle_f64 & rectangle_f64, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      //void draw_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, double dWidth, const ::e_border & eborder = e_border_all) override;
      //void frame_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, const ::e_border & eborder = e_border_all) override;


      
   public:
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      //HGDIOBJ SelectObject(HGDIOBJ);      // do not use for regions

      void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      void set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode) override;

      void set_text_rendering_hint(::write_text::enum_rendering etextrendering) override;

      //virtual void * get_os_data() const;
      //virtual void * get_os_data_ex(int i) const;
      //virtual void release_os_data_ex(int i, void *p);
      //virtual HDC get_handle() const;
      //virtual HDC get_handle1() const;
      //virtual HDC get_handle2() const;

//      virtual bool attach(void * pdata);


      //virtual plusplus::FillMode gl2d_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rectangle_i32 & rectangle);


      void flush() override;
      void sync_flush() override;

      //virtual bool DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      //virtual bool DrawLine(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::pen * ppen);

      
      void draw_line(const point_i32& point1, const point_i32& point2, ::draw2d::pen* ppen);


      //virtual void enum_fonts(::write_text::font_enumeration_item_array& itema) override;

      //void prefer_mapped_image_on_mix() override;

      virtual void set(::draw2d::region* pregion) override;
      virtual void set(::draw2d::pen* ppen) override;
      virtual void set(::write_text::font* pfont) override;
      virtual void set(::draw2d::brush* pbrush) override;
      virtual void set(::draw2d::bitmap* pbitmap) override;
      virtual ::draw2d::object* set_stock_object(i32 nIndex) override;

      void CreateWindowDC(oswindow wnd) override;
      void is_valid_update_window_thread() override;


      void _add_clipping_shape(const ::rectangle_f64 & rectangle, ___shape < ::draw2d::region > & shape) override;


      void on_begin_draw() override;
      void on_end_draw(oswindow wnd) override;

      
      bool _is_ok() const override;


   };


   CLASS_DECL_DRAW2D_OPENGL graphics * thread_graphics();

   CLASS_DECL_DRAW2D_OPENGL void thread_graphics(graphics * graphics);


} // namespace draw2d_opengl


//#define memory_new ACME_NEW


