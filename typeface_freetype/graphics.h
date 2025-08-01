#pragma once


#include "bred/gpu/graphics.h"



//struct OffscreenContext
//{
//   HWND window;
//   HDC dev_context;
//   HGLRC openGLContext;
//   int width;
//   int height;
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
      ::int_size                          m_size;
      //HDC                           m_hdcGraphics;
      float                               m_z;
      //int_point                           m_pointTranslate;
      // bool                                      m_bFont;
      ::int_size                          m_sizeWindow;
      //HGLRC m_hrc;
      ::pointer < ::windowing::window >   m_pwindow;
      //::pointer<::gpu::context>          m_pgpucontextOpenGL;
      ::pointer < ::gpu::shader >         m_pgpushaderTextOut;


      graphics();
      ~graphics() override;

#ifdef _DEBUG
         long long increment_reference_count() override;
      long long decrement_reference_count() override;
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
      
      
      void start_gpu_layer(::gpu::frame * pgpuframe) override;
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
      //void fill_rectangle(const double_rectangle& rectangle, color32_t color32);


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


      void _draw_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptionsParam, const ::double_point & pointSrc) override;

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
                    const_char_pointer lpszOutput, const void * lpInitData);
      bool CreateIC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName,
                    const_char_pointer lpszOutput, const void * lpInitData);
      void create_memory_graphics(const ::int_size & size = {}) override;
      void create_window_graphics(::windowing::window * pwindow) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      //void set_hint_window_output() override;

      //virtual bool opengl_create_offscreen_buffer(const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_rectangle & rectanglePlacement);
      virtual bool opengl_create_offscreen_buffer(const ::int_size& rectanglePlacement);
      virtual bool opengl_delete_offscreen_buffer();

      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size) override;

      virtual bool opengl_defer_create_window_context(::windowing::window * pwindow);

      void DeleteDC() override;

      // Device-Context Functions
      int save_graphics_context()override;
      void restore_graphics_context(int iSavedContext)override;
      //int GetDeviceCaps(int nIndex) override;
      unsigned int SetBoundsRect(const ::double_rectangle & rectangleBounds, unsigned int flags) override;
      unsigned int GetBoundsRect(double_rectangle * rectangleBounds, unsigned int flags) override;
      //bool ResetDC(const DEVMODE* lpDevMode);


      void resize(const ::int_size & sizeWindow) override;


      // Drawing-Tool Functions
      int_point GetBrushOrg() const;
      int_point SetBrushOrg(int x, int y);
      int_point SetBrushOrg(const ::int_point & point);
      int EnumObjects(int nObjectType,
                          int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);

      // Type-safe selection helpers
   public:

      ::typeface_freetype::draw2d * typeface_freetype();


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
      //virtual int_point get_origin() const;
      virtual int SetMapMode(int nMapMode);
      // Context Origin
      virtual int_point set_origin(int x, int y);
      virtual int_point set_origin(const ::int_point & point);
      virtual int_point offset_origin(int nWidth, int nHeight);

      // Context Extent
      virtual int_size get_context_extents() const;
      //virtual int_size set_context_extents(int cx, int cy);
      //virtual int_size set_context_extents(const ::int_size & size);
      //virtual int_size scale_context_extents(int xNum, int xDenom, int yNum, int yDenom);

      // Window Origin
      int_point GetWindowOrg() const;
      int_point SetWindowOrg(int x, int y);
      int_point SetWindowOrg(const ::int_point & point);
      int_point offset_window_org(int nWidth, int nHeight);

      // Window extent
      int_size GetWindowExt() const;
      virtual int_size set_window_ext(int cx, int cy);
      int_size set_window_ext(const ::int_size & size);
      virtual int_size scale_window_ext(int xNum, int xDenom, int yNum, int yDenom);

      // Coordinate Functions
      void DPtoLP(::double_point * ppoints,::collection::count nCount = 1) override;
      void DPtoLP(::double_rectangle * prectangle) override;
      void DPtoLP(::double_size * psize) override;
      void LPtoDP(::double_point * ppoints,::collection::count nCount = 1) override;
      void LPtoDP(::double_rectangle * prectangle) override;
      void LPtoDP(::double_size * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::double_size * pSize) override;
      void LPtoHIMETRIC(::double_size * pSize) override;
      void HIMETRICtoDP(::double_size * pSize) override;
      void HIMETRICtoLP(::double_size * pSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight);
      bool InvertRgn(::draw2d::region* pRgn);
      //bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual int get_clip_box(double_rectangle * prectangle) const;
      virtual bool PtVisible(int x, int y) const;
      bool PtVisible(const ::int_point & point) const;
      //virtual bool RectVisible(const ::int_rectangle & int_rectangle) const;
      int SelectClipRgn(::draw2d::region* pRgn);
      int ExcludeClipRect(int x1, int y1, int x2, int y2);
      int ExcludeClipRect(const ::int_rectangle & int_rectangle);
      int ExcludeUpdateRgn(::user::interaction_base * pwindow);
      int IntersectClipRect(int x1, int y1, int x2, int y2);
      int IntersectClipRect(const ::int_rectangle & int_rectangle);
      int OffsetClipRgn(int x, int y);
      int OffsetClipRgn(const ::int_size & size);
      int SelectClipRgn(::draw2d::region* pRgn, int nMode);


      void text_out(double x, double y, const ::scoped_string & scopedstr) override;
      //virtual void text_out_2024_and_before(double x, double y, const ::scoped_string& scopedstr);

      // Line-Output Functions
      // int_point GetCurrentPosition() const;
//      int_point MoveTo(int x, int y);
      //    int_point MoveTo(const ::int_point & point);
      void line_to(double x, double y) override;
      //bool LineTo(int x,int y);
      //  bool LineTo(const ::int_point & point);
      void polyline(const ::double_point* ppoints,::collection::count nCount) override;

      void _set(const ::geometry2d::matrix & matrix) override;

      //using ::draw2d::graphics::Arc;
      //bool arc(double x1, double y1, double x2, double y2,int x3,int y3,int x4,int y4);
      void arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);

      //bool Arc(int x1,int y1,int x2,int y2,double start, double extends);
      void arc(double x1,double y1,double x2,double y2,double start, double extends);

      void angle_arc(double x, double y, double nRadius,::double_angle fStartAngle, ::double_angle fSweepAngle);
      void arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      void arc_to(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);
      //int GetArcDirection() const;
      //int SetArcDirection(int nArcDirection);

      //void polydraw(const ::double_point* lpPoints, const unsigned char* lpTypes,::collection::count nCount);
      void polyline_to(const ::double_point * lpPoints,::collection::count nCount);
      void poly_polyline(const ::double_point * lpPoints, const int * lpPolyPoints,::collection::count nCount);

      void poly_bezier(const ::double_point * lpPoints,::collection::count nCount);
      void poly_bezier_to(const ::double_point * lpPoints,::collection::count nCount);

      // Simple Drawing Functions

      void fill_rectangle(const ::double_rectangle& rectangle, const ::color::color& color) override;
      void fill_rectangle(const ::double_rectangle &  rectangle, ::draw2d::brush* pBrush) override;
      virtual void fill_rectangle_2025_06(const ::double_rectangle& rectangle, ::draw2d::brush* pBrush);
      void frame_rectangle(const ::double_rectangle & rectangle, ::draw2d::brush* pBrush) override;
      //bool DrawRect(const ::int_rectangle & rectangle, ::draw2d::pen * ppen);
      void invert_rectangle(const ::double_rectangle & int_rectangle) override;
      //void draw_icon(double x, double y, ::image::icon * picon) override;
      //void draw_icon(const ::int_point & point, ::image::icon * picon);
      //void draw_icon(double x, double y, ::image::icon * picon, int cx, int cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags);
//      bool DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, unsigned int nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags,
//                     HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags,
//                     ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, const ::scoped_string & lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, const ::scoped_string & lpszText, unsigned int nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, unsigned int nFlags, HBRUSH hBrush = nullptr);
//      bool DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc,
//                     LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4);
      bool Chord(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd);
      void DrawFocusRect(const ::int_rectangle & int_rectangle);

      //bool DrawEllipse(int x1, int y1, int x2, int y2);
      //bool DrawEllipse(const ::int_rectangle & int_rectangle);
      //bool FillEllipse(int x1, int y1, int x2, int y2);
      //bool FillEllipse(const ::int_rectangle & int_rectangle);

      //virtual bool DrawEllipse(double x1,double y1,double x2,double y2);
      void draw_ellipse(const ::double_rectangle & rectangle) override;
      //virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      void fill_ellipse(const ::double_rectangle & rectangle) override;

      //virtual bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      //virtual bool Pie(const ::int_rectangle & rectangle, const ::int_point & pointStart, const ::int_point & pointEnd) override;
      void fill_polygon(const ::double_point * lpPoints,::collection::count nCount) override;
      //void fill_polygon(const ::int_point * lpPoints,::collection::count nCount) override;
      //void draw_polygon(const ::int_point * lpPoints,::collection::count nCount) override;
      void draw_polygon(const ::double_point * lpPoints,::collection::count nCount) override;
      //void int_polygon(const ::int_point* lpPoints,::collection::count nCount) override;
      void polygon(const ::double_point* lpPoints,::collection::count nCount) override;
      void poly_polygon(const double_point * lpPoints, const int * lpPolyCounts,::collection::count nCount) override;
      //virtual bool int_rectangle(int x1, int y1, int x2, int y2) override;
      void rectangle(const ::double_rectangle & rectangle) override;
      //virtual bool drw(int x1, int y1, int x2, int y2);
      void draw_rectangle(const ::double_rectangle & rectangle) override;
      void draw_rectangle(const ::double_rectangle& rectangle, ::draw2d::pen * ppen) override;
      //virtual bool FillRectangle(int x1, int y1, int x2, int y2);
      void fill_rectangle(const ::double_rectangle & rectangle);
      //void round_rectangle(double x1, double y1, double x2, double y2, double x3, double y3) override;
      void round_rectangle(const ::double_rectangle & rectangle, const ::int_point & point);

      // Bitmap Functions
      //bool PatBlt(int x, int y, int nWidth, int nHeight);
      //virtual bool BitBltRaw(int x, int y, int nWidth, int nHeight, ::draw2d::graphics* pgraphicsSrc, int xSrc, int ySrc) override;
      //virtual bool StretchBltRaw(int xDst, int yDst, int nDstWidth, int nDstHeight, ::draw2d::graphics* pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight) override;
//      {

//         bool StretchBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
  //                    int xSrc, int ySrc, int nSrcWidth, int nSrcHeight);
      ::color::color GetPixel(int x, int y) const;
      ::color::color GetPixel(const ::int_point & point) const;
      ::color::color SetPixel(double x, double y, ::color::color crColor);
      ::color::color SetPixel(const ::int_point & point, ::color::color crColor);
//      bool FloodFill(int x, int y, color32_t crColor);
//      bool ExtFloodFill(int x, int y, color32_t crColor, unsigned int nFillType);
//      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
//                   unsigned int dwRop);
//      bool PlgBlt(::int_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
//                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask);
      void SetPixelV(int x, int y, ::color::color crColor);
      void SetPixelV(const ::int_point & point, ::color::color crColor);
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
      //virtual bool TextOut(int x, int y, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool TextOut(int x, int y, const ::scoped_string & str);
      //virtual bool TextOut(double x, double y, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool TextOut(double x, double y, const ::scoped_string & str);
      //virtual bool ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle, const ::scoped_string & lpszString,character_count nCount, LPINT lpDxWidths);
      //virtual bool ExtTextOut(int x, int y, unsigned int nOptions, const ::int_rectangle & rectangle, const ::scoped_string & str, LPINT lpDxWidths);
      //virtual int_size TabbedTextOut(int x, int y, const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
      //virtual int_size TabbedTextOut(int x, int y, const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

      //void text_out(double x, double y, const ::scoped_string & lpszString, character_count nCount) override;

      void draw_text(const ::scoped_string & str,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::scoped_string & str,const ::int_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      void draw_text(const ::scoped_string & str,const ::double_rectangle & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //void draw_text_ex(const ::scoped_string & scopedstr, const ::double_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual double_size get_text_extent(const ::scoped_string & lpszString, character_count nCount, character_count iIndex) override;
      //virtual double_size get_text_extent(const ::scoped_string & lpszString, character_count nCount) override;
      virtual double_size get_text_extent(const ::scoped_string & str) override;
      //virtual bool get_text_extent(double_size & size, const ::scoped_string & lpszString, character_count nCount, character_count iIndex);
      //virtual bool get_text_extent(double_size & size, const ::scoped_string & lpszString, character_count nCount);
      //virtual bool get_text_extent(double_size & size, const ::scoped_string & str);
      //virtual int_size GetOutputTextExtent(const ::scoped_string & lpszString, character_count nCount);
      //virtual int_size GetOutputTextExtent(const ::scoped_string & str);
      //virtual int_size GetTabbedTextExtent(const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual int_size GetTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual int_size GetOutputTabbedTextExtent(const ::scoped_string & lpszString, character_count nCount,::collection::count nTabPositions, LPINT lpnTabStopPositions);
      //virtual int_size GetOutputTabbedTextExtent(const ::scoped_string & str,::collection::count nTabPositions, LPINT lpnTabStopPositions);
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

      //virtual unsigned int GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;
      //virtual unsigned int GetCharacterPlacement(const ::scoped_string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      bool DrawEdge(const ::int_rectangle & rectangle,unsigned int nEdge,unsigned int nFlags);
//      bool DrawFrameControl(const ::int_rectangle & rectangle,unsigned int nType,unsigned int nState);

      // Scrolling Functions
      //bool ScrollDC(int Δx, int Δy, const ::int_rectangle & lpRectScroll, const ::int_rectangle & lpRectClip,
        //            ::draw2d::region* pRgnUpdate, ::int_rectangle * lpRectUpdate);

      // font Functions
      //bool GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      //bool GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const;
      //unsigned int SetMapperFlags(unsigned int dwFlag);
      //int_size GetAspectRatioFilter() const;

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
      int Escape(int nEscape, int nInputSize,  const_char_pointer lpszInputData,int nOutputSize, char * lpszOutputData);
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
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::int_rectangle & lpBounds);
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
      //int GetPath(::int_point * lpPoints, LPBYTE lpTypes,::collection::count nCount) const;
      void SelectClipPath(int nMode);

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush();
      //void DrawDragRect(const ::int_rectangle & rectangle, const ::int_size & size,
      //                  const ::int_rectangle & lpRectLast, const ::int_size & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);
      //void FillSolidRect(const ::long_long_rectangle * rectangle, color32_t clr);
      //void FillSolidRect(const ::int_rectangle & rectangle, color32_t clr);
      //void FillSolidRect(int x, int y, int cx, int cy, color32_t clr);
      /*void Draw3dRect(const ::int_rectangle & rectangle, color32_t clrTopLeft, color32_t clrBottomRight);
      void Draw3dRect(int x, int y, int cx, int cy,
                      color32_t clrTopLeft, color32_t clrBottomRight);
*/

      //void draw_inset_3d_rectangle(const ::double_rectangle & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //virtual void draw_inset_3d_rectangle(const double_rectangle & double_rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      //void draw_inset_rectangle(const ::double_rectangle & rectangle, const ::color::color & color, double dWidth, const ::e_border & eborder = e_border_all) override;
      //void frame_rectangle(const ::double_rectangle & rectangle, const ::color::color & color, const ::e_border & eborder = e_border_all) override;

      void intersect_clip(const ::draw2d::clip_group & clipgroup) override;
      void intersect_clip(const ::double_rectangle & rectangle) override;

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

      bool blur(bool bExpand, double dRadius, const ::int_rectangle & rectangle);


      void flush() override;
      void sync_flush() override;

      //virtual bool DrawLine(float x1, float y1, float x2, float y2, ::draw2d::pen * ppen);
      //virtual bool DrawLine(int x1, int y1, int x2, int y2, ::draw2d::pen * ppen);

      
      void draw_line(const int_point& point1, const int_point& point2, ::draw2d::pen* ppen);


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


      //void _add_clipping_shape(const ::double_rectangle & rectangle, ::draw2d::region * pregion) override;


      //void on_begin_draw() override;
      //void on_end_draw() override;
      //void on_end_draw() override;
      void on_present() override;

      
      bool _is_ok() const override;

      

   };


   CLASS_DECL_TYPEFACE_FREETYPE graphics * thread_graphics();

   CLASS_DECL_TYPEFACE_FREETYPE void thread_graphics(graphics * graphics);


} // namespace typeface_freetype





