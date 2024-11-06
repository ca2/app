#pragma once


#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/gpu/render.h"


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
      virtual public ::draw2d::graphics,
      virtual public ::gpu::render
   {
   public:

      //::plusplus::Matrix *           m_pm;
      //::plusplus::Graphics *         m_pgraphics;
      //::plusplus::GraphicsPath *     m_ppath;
      //::plusplus::GraphicsPath *     m_ppathPaint;
      //HGLRC                         m_hglrc;
      //HDC                           m_hdc;
      //HWND                          m_hwnd;
      ::size_i32                        m_size;
      //HDC                           m_hdcGraphics;
      float                         m_z;
      point_i32                         m_pointTranslate;
      // bool                                      m_bFont;
      ::size_i32                    m_sizeWindow;
      //HGLRC m_hrc;

      //::pointer<::gpu::context>          m_pgpucontextOpenGL;


      graphics();
      ~graphics() override;

#ifdef _DEBUG
         int64_t increment_reference_count() override;
      int64_t decrement_reference_count() override;
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


      void _draw_raw(const ::rectangle_f64 & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptionsParam, const ::point_f64 & pointSrc) override;

      //plusplus::Pen *       gl2d_pen();
      //plusplus::Brush *     gl2d_brush();
      //plusplus::Font *      gl2d_font();

      // for bidi and mirrored localization
      unsigned int GetLayout() const;
      unsigned int SetLayout(unsigned int dwLayout);


      //HDC get_hdc();
      //void release_hdc(HDC hdc);


      virtual double get_dpix() const;
      virtual double get_dpiy() const;

      // Constructors
      bool CreateDC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      bool CreateIC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData);
      void create_memory_graphics(const ::size_i32 & size = {}) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      virtual bool opengl_create_offscreen_buffer(const ::size_i32 & size);
      virtual bool opengl_delete_offscreen_buffer();

      void DeleteDC() override;

      // Device-Context Functions
      int save_graphics_context()override;
      void restore_graphics_context(int iSavedContext)override;
      //int GetDeviceCaps(int nIndex) override;
      unsigned int SetBoundsRect(const ::rectangle_f64 & rectangleBounds, unsigned int flags) override;
      unsigned int GetBoundsRect(rectangle_f64 * rectangleBounds, unsigned int flags) override;
      //bool ResetDC(const DEVMODE* lpDevMode);


      void resize(const ::size_i32 & sizeWindow) override;


      // Drawing-Tool Functions
      point_i32 GetBrushOrg() const;
      point_i32 SetBrushOrg(int x, int y);
      point_i32 SetBrushOrg(const ::point_i32 & point);
      int EnumObjects(int nObjectType,
                          int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:

      ::draw2d_opengl::draw2d * draw2d_opengl();


      virtual ::draw2d::object* SelectStockObject(int nIndex);
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::write_text::font* SelectObject(::write_text::font* pFont);
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      int SelectObject(::draw2d::region* pRgn);       // special return for regions
      ::draw2d::object* SelectObject(::draw2d::object* pObject);
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      // color and color Palette Functions
      color32_t GetNearestColor(color32_t crColor) const;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      unsigned int RealizePalette();
      void UpdateColors();

      int GetPolyFillMode() const;
      int GetROP2() const;
      int GetStretchBltMode() const;

      int SetPolyFillMode(int nPolyFillMode);
      int SetROP2(int nDrawMode);
      int set_interpolation_mode(int nStretchMode);

      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      color32_t GetDCBrushColor() const;
      color32_t SetDCBrushColor(color32_t crColor);

      color32_t GetDCPenColor() const;
      color32_t SetDCPenColor(color32_t crColor);

#endif

      // Graphics mode
      int SetGraphicsMode(int iMode);
      int GetGraphicsMode() const;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,unsigned int iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual int GetMapMode() const;
      //virtual point_i32 get_origin() const;
      virtual int SetMapMode(int nMapMode);
      // Context Origin
      virtual point_i32 set_origin(int x, int y);
      virtual point_i32 set_origin(const ::point_i32 & point);
      virtual point_i32 offset_origin(int nWidth, int nHeight);

      // Context Extent
      virtual size_i32 get_context_extents() const;
      //virtual size_i32 set_context_extents(int cx, int cy);
      //virtual size_i32 set_context_extents(const ::size_i32 & size);
      //virtual size_i32 scale_context_extents(int xNum, int xDenom, int yNum, int yDenom);

      // Window Origin
      point_i32 GetWindowOrg() const;
      point_i32 SetWindowOrg(int x, int y);
      point_i32 SetWindowOrg(const ::point_i32 & point);
      point_i32 offset_window_org(int nWidth, int nHeight);

      // Window extent
      size_i32 GetWindowExt() const;
      virtual size_i32 set_window_ext(int cx, int cy);
      size_i32 set_window_ext(const ::size_i32 & size);
      virtual size_i32 scale_window_ext(int xNum, int xDenom, int yNum, int yDenom);

      // Coordinate Functions
      void DPtoLP(::point_f64 * ppoints,::collection::count nCount = 1) override;
      void DPtoLP(::rectangle_f64 * prectangle) override;
      void DPtoLP(::size_f64 * psize) override;
      void LPtoDP(::point_f64 * ppoints,::collection::count nCount = 1) override;
      void LPtoDP(::rectangle_f64 * prectangle) override;
      void LPtoDP(::size_f64 * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::size_f64 * pSize) override;
      void LPtoHIMETRIC(::size_f64 * pSize) override;
      void HIMETRICtoDP(::size_f64 * pSize) override;
      void HIMETRICtoLP(::size_f64 * pSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      //bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual int get_clip_box(rectangle_f64 * prectangle) const;
      virtual bool PtVisible(int x, int y) const;
      bool PtVisible(const ::point_i32 & point) const;
      //virtual bool RectVisible(const ::rectangle_i32 & rectangle_i32) const;
      int SelectClipRgn(::draw2d::region* pRgn);
      int ExcludeClipRect(int x1, int y1, int x2, int y2);
      int ExcludeClipRect(const ::rectangle_i32 & rectangle_i32);
      int ExcludeUpdateRgn(::user::interaction_base * pwindow);
      int IntersectClipRect(int x1, int y1, int x2, int y2);
      int IntersectClipRect(const ::rectangle_i32 & rectangle_i32);
      int OffsetClipRgn(int x, int y);
      int OffsetClipRgn(const ::size_i32 & size);
      int SelectClipRgn(::draw2d::region* pRgn, int nMode);


      void text_out(double x, double y, const ::scoped_string & scopedstr) override;

      // Line-Output Functions
      // point_i32 GetCurrentPosition() const;
//      point_i32 MoveTo(int x, int y);
      //    point_i32 MoveTo(const ::point_i32 & point);
      void line_to(double x, double y) override;
      //bool LineTo(int x,int y);
      //  bool LineTo(const ::point_i32 & point);
      void polyline(const ::point_f64* ppoints,::collection::count nCount) override;

      void _set(const ::geometry2d::matrix & matrix) override;

      //using ::draw2d::graphics::Arc;
      //bool arc(double x1, double y1, double x2, double y2,int x3,int y3,int x4,int y4);
      void arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);

      //bool Arc(int x1,int y1,int x2,int y2,double start, double extends);
      void arc(double x1,double y1,double x2,double y2,double start, double extends);

      void angle_arc(double x, double y, double nRadius,::angle_f64 fStartAngle, ::angle_f64 fSweepAngle);
      void arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      void arc_to(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      //int GetArcDirection() const;
      //int SetArcDirection(int nArcDirection);

      //void polydraw(const ::point_f64* lpPoints, const unsigned char* lpTypes,::collection::count nCount);
      void polyline_to(const ::point_f64 * lpPoints,::collection::count nCount);
      void poly_polyline(const ::point_f64 * lpPoints, const int * lpPolyPoints,::collection::count nCount);

      void poly_bezier(const ::point_f64 * lpPoints,::collection::count nCount);
      void poly_bezier_to(const ::point_f64 * lpPoints,::collection::count nCount);

      // Simple Drawing Functions
      void fill_rectangle(const ::rectangle_f64 &  rectangle, ::draw2d::brush* pBrush) override;
      void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;
      //bool DrawRect(const ::rectangle_i32 & rectangle, ::draw2d::pen * ppen);
      void invert_rectangle(const ::rectangle_f64 & rectangle_i32) override;
      //void draw_icon(double x, double y, ::image::icon * picon) override;
      //void draw_icon(const ::point_i32 & point, ::image::icon * picon);
      //void draw_icon(double x, double y, ::image::icon * picon, int cx, int cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HBITMAP hBitmap, unsigned int nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, unsigned int nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, HICON hIcon, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::scoped_string & lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, const ::scoped_string & lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, unsigned int nFlags, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::point_i32 & point, const ::size_i32 & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4);
      bool Chord(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd);
      void DrawFocusRect(const ::rectangle_i32 & rectangle_i32);

      //bool DrawEllipse(int x1, int y1, int x2, int y2);
      //bool DrawEllipse(const ::rectangle_i32 & rectangle_i32);
      //bool FillEllipse(int x1, int y1, int x2, int y2);
      //bool FillEllipse(const ::rectangle_i32 & rectangle_i32);

      //virtual bool DrawEllipse(double x1,double y1,double x2,double y2);
      void draw_ellipse(const ::rectangle_f64 & rectangle) override;
      //virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      void fill_ellipse(const ::rectangle_f64 & rectangle) override;

      //virtual bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      //virtual bool Pie(const ::rectangle_i32 & rectangle, const ::point_i32 & pointStart, const ::point_i32 & pointEnd) override;
      void fill_polygon(const ::point_f64 * lpPoints,::collection::count nCount) override;
      //void fill_polygon(const ::point_i32 * lpPoints,::collection::count nCount) override;
      //void draw_polygon(const ::point_i32 * lpPoints,::collection::count nCount) override;
      void draw_polygon(const ::point_f64 * lpPoints,::collection::count nCount) override;
      //void polygon_i32(const ::point_i32* lpPoints,::collection::count nCount) override;
      void polygon(const ::point_f64* lpPoints,::collection::count nCount) override;
      void poly_polygon(const point_f64 * lpPoints, const int * lpPolyCounts,::collection::count nCount) override;
      //virtual bool rectangle_i32(int x1, int y1, int x2, int y2) override;
      void rectangle(const ::rectangle_f64 & rectangle) override;
      //virtual bool drw(int x1, int y1, int x2, int y2);
      void draw_rectangle(const ::rectangle_f64 & rectangle) override;
      void draw_rectangle(const ::rectangle_f64& rectangle, ::draw2d::pen * ppen) override;
      //virtual bool FillRectangle(int x1, int y1, int x2, int y2);
      void fill_rectangle(const ::rectangle_f64 & rectangle);
      //void round_rectangle(double x1, double y1, double x2, double y2, double x3, double y3) override;
      void round_rectangle(const ::rectangle_f64 & rectangle, const ::point_i32 & point);

      // Bitmap Functions
      //bool PatBlt(int x, int y, int nWidth, int nHeight);
      //virtual bool BitBltRaw(int x, int y, int nWidth, int nHeight, ::draw2d::graphics* pgraphicsSrc, int xSrc, int ySrc) override;
      //virtual bool StretchBltRaw(int xDst, int yDst, int nDstWidth, int nDstHeight, ::draw2d::graphics* pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight) override;
//      {

//         bool StretchBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    int xSrc, int ySrc, int nSrcWidth, int nSrcHeight);
      ::color::color GetPixel(int x, int y) const;
      ::color::color GetPixel(const ::point_i32 & point) const;
      ::color::color SetPixel(double x, double y, ::color::color crColor);
      ::color::color SetPixel(const ::point_i32 & point, ::color::color crColor);
//      bool FloodFill(int x, int y, color32_t crColor);
//      bool ExtFloodFill(int x, int y, color32_t crColor, unsigned int nFillType);
//      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
//                   unsigned int dwRop);
//      bool PlgBlt(::point_i32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
//                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask);
      void SetPixelV(int x, int y, ::color::color crColor);
      void SetPixelV(const ::point_i32 & point, ::color::color crColor);
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, unsigned int dwMode);
      void TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                          unsigned int clrTransparent);

      ///void alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dOpacity);

      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      //virtual bool TextOut(int x, int y, const ::scoped_string & lpszString, strsize nCount);
      //virtual bool TextOut(int x, int y, const ::scoped_string & str);
      //virtual bool TextOut(double x, double y, const ::scoped_string & lpszString, strsize nCount);
      //virtual bool TextOut(double x, double y, const ::scoped_string & str);
      //virtual bool ExtTextOut(int x, int y, unsigned int nOptions, const ::rectangle_i32 & rectangle, const ::scoped_string & lpszString,strsize nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(int x, int y, unsigned int nOptions, const ::rectangle_i32 & rectangle, const ::scoped_string & str, LPINT lpDxWidths);
      //virtual size_i32 TabbedTextOut(int x, int y, const ::scoped_string & lpszString, strsize nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
      //virtual size_i32 TabbedTextOut(int x, int y, const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

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
      //virtual size_i32 GetTabbedTextExtent(const ::scoped_string & lpszString, strsize nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetOutputTabbedTextExtent(const ::scoped_string & lpszString, strsize nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual size_i32 GetOutputTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight);
      virtual unsigned int GetTextAlign() override;
      virtual unsigned int SetTextAlign(unsigned int nFlags) override;
      //virtual int GetTextFace(::collection::count nCount, char * lpszFacename);
      //virtual int GetTextFace(string & rString);
      //virtual bool get_text_metrics(::write_text::text_metric * lpMetrics);
      //virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics);
      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric * pmetrics) override;
      void get_output_text_metrics(::write_text::text_metric * pMetrics) override;

      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount);
      //virtual int GetTextCharacterExtra();
      //virtual int SetTextCharacterExtra(int nCharExtra);

      //virtual unsigned int GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;
      //virtual unsigned int GetCharacterPlacement(const ::scoped_string & lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      bool DrawEdge(const ::rectangle_i32 & rectangle,unsigned int nEdge,unsigned int nFlags);
//      bool DrawFrameControl(const ::rectangle_i32 & rectangle,unsigned int nType,unsigned int nState);

      // Scrolling Functions
      //bool ScrollDC(int Δx, int Δy, const ::rectangle_i32 & lpRectScroll, const ::rectangle_i32 & lpRectClip,
        //            ::draw2d::region* pRgnUpdate, ::rectangle_i32 * lpRectUpdate);

      // font Functions
      //bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      //bool GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      //unsigned int SetMapperFlags(unsigned int dwFlag);
      //size_i32 GetAspectRatioFilter() const;

      //bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) const;
      //unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData, unsigned int cbData) const;
      //int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const;
      //unsigned int GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) const;
      //unsigned int GetGlyphOutline(unsigned int nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //                         unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      //bool GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar,
                            //LPABCFLOAT lpABCF) const;
      //bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar,
                        //float* lpFloatBuffer) const;

      unsigned int GetFontLanguageInfo() const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual int Escape(int nEscape, int nCount, const ::scoped_string & lpszInData, LPVOID lpOutData);
      int Escape(int nEscape, int nInputSize,  const char * lpszInputData,int nOutputSize, char * lpszOutputData);
      int DrawEscape(int nEscape, int nInputSize, const ::scoped_string & lpszInputData);

      // Escape helpers
      int StartDoc(const ::scoped_string & lpszDocName);  // old Win3.0 version
      int StartDoc(LPDOCINFO lpDocInfo);
      int StartPage();
      int EndPage();
      int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int));
      int AbortDoc();
      int EndDoc();

      // MetaFile Functions
      //bool PlayMetaFile(HMETAFILE hMF);
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_i32 & lpBounds);
      //bool AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData);
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
      //int GetPath(::point_i32 * lpPoints, LPBYTE lpTypes,::collection::count nCount) const;
      void SelectClipPath(int nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush();
      //void DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_i32 & size,
      //                  const ::rectangle_i32 & lpRectLast, const ::size_i32 & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const ::rectangle_i64 * rectangle, color32_t clr);
      //void FillSolidRect(const ::rectangle_i32 & rectangle, color32_t clr);
      //void FillSolidRect(int x, int y, int cx, int cy, color32_t clr);
      /*void Draw3dRect(const ::rectangle_i32 & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(int x, int y, int cx, int cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);
*/

      //void draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //virtual void draw_inset_3d_rectangle(const rectangle_f64 & rectangle_f64, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      //void draw_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, double dWidth, const ::e_border & eborder = e_border_all) override;
      //void frame_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, const ::e_border & eborder = e_border_all) override;

      void intersect_clip(const ::draw2d::clip_group & clipgroup) override;
      void intersect_clip(const ::rectangle_f64 & rectangle) override;

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
      //virtual bool DrawLine(int x1, int y1, int x2, int y2, ::draw2d::pen * ppen);

      
      void draw_line(const point_i32& point1, const point_i32& point2, ::draw2d::pen* ppen);


      //virtual void enum_fonts(::write_text::font_enumeration_item_array& itema) override;

      //void prefer_mapped_image_on_mix() override;

      virtual void set(::draw2d::region* pregion) override;
      virtual void set(::draw2d::pen* ppen) override;
      virtual void set(::write_text::font* pfont) override;
      virtual void set(::draw2d::brush* pbrush) override;
      virtual void set(::draw2d::bitmap* pbitmap) override;
      virtual ::draw2d::object* set_stock_object(int nIndex) override;

      void CreateWindowDC(oswindow wnd) override;
      void is_valid_update_window_thread() override;


      //void _add_clipping_shape(const ::rectangle_f64 & rectangle, ::draw2d::region * pregion) override;


      void on_begin_draw() override;
      void on_end_draw(oswindow wnd) override;
      //void on_end_draw() override;

      
      bool _is_ok() const override;

      

   };


   CLASS_DECL_DRAW2D_OPENGL graphics * thread_graphics();

   CLASS_DECL_DRAW2D_OPENGL void thread_graphics(graphics * graphics);


} // namespace draw2d_opengl





