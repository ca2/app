#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D graphics :
      virtual public ::draw2d::graphics
   {
   public:


      class state :
         virtual public ::object
      {
      public:




         D2D1::Matrix3x2F                    m_m;
         array < D2D1::Matrix3x2F >          m_maRegion;
         __pointer_array(::draw2d::region)        m_sparegionClip;
         D2D1_LAYER_PARAMETERS               m_layerparameters;

         state();
         virtual ~state();


      };

      Microsoft::WRL::ComPtr<ID2D1DeviceContext>         m_pdevicecontext; // 0
      Microsoft::WRL::ComPtr<ID2D1RenderTarget>          m_prendertarget; // 1
      Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget>    m_pbitmaprendertarget; // 2
      Microsoft::WRL::ComPtr<ID2D1DCRenderTarget>        m_pdcrendertarget; // 3

      Microsoft::WRL::ComPtr<IDXGIAdapter>               m_padapter;
      Microsoft::WRL::ComPtr<IDXGIFactory2>              m_pfactory2;
      Microsoft::WRL::ComPtr<ID2D1Layer>                 m_player;
      Microsoft::WRL::ComPtr<ID2D1PathGeometry>          m_ppathgeometryClip;

      __pointer_array(state)                             m_statea;
      __pointer(state)                                   m_pstate;

      bool                                               m_bSaveClip;

      int                                                m_iType;

      D2D1_BITMAP_INTERPOLATION_MODE                     m_bitmapinterpolationmode;
      D2D1_INTERPOLATION_MODE                            m_interpolationmode;

      ::write_text::enum_rendering                    m_etextrenderinghintDevice;


      // advanced use and implementation
      bool                                               m_bPrinting;

      HDC                                                m_hdcAttach;
      ::draw2d::enum_alpha_mode                          m_ealphamodeDevice;


      graphics();
      virtual ~graphics();


      virtual bool TextOutAlphaBlend(double x, double y, const block & block) override;
      virtual bool _draw_blend(const ::image_drawing & imagedrawing) override;


      bool IsPrinting() override;            // true if being used for printing

      
      virtual bool on_begin_draw() override;

      using ::draw2d::graphics::set;
      virtual ::e_status set(::draw2d::bitmap* pbitmap) override;


      oswindow get_window_handle();

      void apply_primitive_blend();

      void apply_text_rendering_hint();

      inline void defer_primitive_blend() 
      {
         
         if (m_ealphamode != m_ealphamodeDevice)
         {

            apply_primitive_blend();

         }
      
      }

      inline void defer_text_rendering_hint()
      {

         if (m_ewritetextrendering != m_etextrenderinghintDevice)
         {

            apply_primitive_blend();

         }

      }

      void defer_text_primitive_blend();

      // for bidi and mirrored localization
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;


      //virtual bool save_clip() override;
      //virtual bool restore_clip() override;

      virtual double get_dpix() override;

      //// Constructors
      //bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
      //              const char * lpszOutput, const void * lpInitData) override;
      //bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
      //              const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual int SaveDC() override;
      virtual bool RestoreDC(int nSavedDC) override;
      //int GetDeviceCaps(int nIndex) override;
      ::u32 SetBoundsRect(const ::rectangle_f64 & rectBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(::rectangle_f64 * rectBounds, ::u32 flags) override;
//      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      ::point_f64 GetBrushOrg() override;
      ::point_f64 SetBrushOrg(double x, double y) override;
      ::point_f64 SetBrushOrg(const ::point_f64 & point) override;
//      int EnumObjects(int nObjectType,
  //                    int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      //virtual ::draw2d::object* set_stock_object(int nIndex) override;
      //virtual ::e_status set(::write_text::font * pfont) override;
      //virtual ::e_status set(::draw2d::pen* pPen) override;
      //virtual ::e_status set(::draw2d::brush* pBrush) override;
      //virtual ::e_status set(::write_text::font* pFont) override;
      //virtual ::e_status set(::draw2d::bitmap* pBitmap) override;
      //virtual i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions
      //::draw2d::object* SelectObject(::draw2d::object* pObject) override;
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      //// color and color Palette Functions
      //color32_t GetNearestColor(const ::color::color & color) override;
      //// ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //::u32 RealizePalette() override;
      //void UpdateColors() override;

      int GetPolyFillMode() override;
      int GetROP2() override;
      int GetStretchBltMode() override;

      int SetPolyFillMode(int nPolyFillMode) override;
      int SetROP2(int nDrawMode) override;
      virtual bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;


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
      int SetGraphicsMode(int iMode) override;
      int GetGraphicsMode() override;


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;

      virtual ::e_status clear_current_point() override;

      virtual bool draw_path(::draw2d::path * ppath) override;
      virtual bool fill_path(::draw2d::path * ppath) override;
      virtual bool path(::draw2d::path * ppath) override;

      virtual bool draw_path(ID2D1PathGeometry * pgeometry, ::draw2d::pen * ppen);
      virtual bool fill_path(ID2D1PathGeometry * pgeometry, ::draw2d::brush * pbrush);

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      // World transform
      //bool SetWorldTransform(const XFORM* pXform) override;
      //bool ModifyWorldTransform(const XFORM* pXform,u32 iMode) override;
      //bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual int GetMapMode() override;
      virtual ::point_f64 GetViewportOrg() override;
      virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      virtual ::point_f64 SetViewportOrg(double x, double y) override;
      virtual ::point_f64 SetViewportOrg(const ::point_f64 & point) override;
      virtual ::point_f64 OffsetViewportOrg(double nWidth, double nHeight) override;

      // Viewport Extent
      virtual size_f64 GetViewportExt() override;
      virtual size_f64 SetViewportExt(double cx, double cy) override;
      virtual size_f64 SetViewportExt(const ::size_f64 & size) override;
      virtual size_f64 ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      ::point_f64 GetWindowOrg() override;
      ::point_f64 SetWindowOrg(double x, double y) override;
      ::point_f64 SetWindowOrg(const ::point_f64 & point) override;
      ::point_f64 offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      ::size_f64 GetWindowExt() override;
      virtual ::size_f64 set_window_ext(double cx, double cy) override;
      ::size_f64 set_window_ext(const ::size_f64 & size) override;
      virtual ::size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      void DPtoLP(::point_f64 * ppoints, ::count nCount = 1) override;
      void DPtoLP(::rectangle_f64 * prectangle) override;
      void DPtoLP(::size_f64 * psize) override;
      void LPtoDP(::point_f64 * ppoints, ::count nCount = 1) override;
      void LPtoDP(::rectangle_f64 * prectangle) override;
      void LPtoDP(::size_f64 * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(::size_f64 * LPSIZE32) override;
      //void LPtoHIMETRIC(::size_f64 * LPSIZE32) override;
      virtual void HIMETRICtoDP(::size_f64 * LPSIZE32) override;
      //void HIMETRICtoLP(::size_f64 * LPSIZE32) override;

      // Region Functions
      virtual bool fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      virtual bool frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight) override;
      virtual bool invert_region(::draw2d::region* pRgn) override;
      virtual bool paint_region(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual int get_clip_box(::rectangle_f64 * prectangle) override;


      virtual ::e_status add_shapes(const shape_array& shapea);
      virtual ::e_status reset_clip();
      virtual ::e_status intersect_clip(const ::rectangle_f64& rectangle);
      //virtual ::e_status intersect_clip(const ::rectangle_f64& rectangle);
      //virtual ::e_status intersect_clip(const ::ellipse& ellipse);
      virtual ::e_status intersect_clip(const ::ellipse& ellipse);
      //virtual ::e_status intersect_clip(const ::polygon_i32& polygon_i32);
      virtual ::e_status intersect_clip(const ::polygon_f64& polygon_i32);

      //virtual bool PtVisible(double x, double y) override;
      //bool PtVisible(const ::point_f64 & point) override;
      //virtual bool RectVisible(const ::rectangle_f64 & rectangle) override;
      //int SelectClipRgn(::draw2d::region* pRgn) override;
      //int ExcludeClipRect(double x1, double y1, double x2, double y2) override;
      //int ExcludeClipRect(const ::rectangle_f64 & rectangle) override;
      ////int ExcludeUpdateRgn(::user::primitive * pwindow) override;
      //int IntersectClipRect(double x1, double y1, double x2, double y2) override;
      //int IntersectClipRect(const ::rectangle_f64 & rectangle) override;
      //int OffsetClipRgn(double x, double y) override;
      //int OffsetClipRgn(const ::size_f64 & size) override;
      //int SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      point_f64 current_position() override;
//      ::point_f64 move_to(double x, double y) override;
      //    ::point_f64 move_to(const ::point_f64 & point) override;
      using ::draw2d::graphics::line_to;
      bool line_to(double x, double y) override;
      bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;
      //  bool line_to(const ::point_f64 & point) override;
      bool Arc(double x1, double y1, double w, double h, angle start, angle extends) override;
      bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      //bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      bool polyline(const ::point_f64* ppoints,count nCount) override;

      bool AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle) override;
      bool ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool ArcTo(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      //int GetArcDirection() override;
      //int SetArcDirection(int nArcDirection) override;

      bool polydraw(const ::point_f64* ppoints, const byte* lpTypes,count nCount) override;
      bool polyline_to(const ::point_f64* ppoints,count nCount) override;
      bool poly_polyline(const ::point_f64* ppoints, const ::i32 * lpPolyPoints,count nCount) override;

      bool poly_bezier(const ::point_f64* ppoints,count nCount) override;
      bool poly_bezier_to(const ::point_f64* ppoints,count nCount) override;


      virtual bool frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pBrush) override;


      virtual bool invert_rectangle(const ::rectangle_f64 & rectangle) override;

      //virtual bool draw(const ::rectangle_f64 & rectDst, ::draw2d::icon * picon) override;

      //bool DrawIcon(double x, double y, ::draw2d::icon * picon) override;
      //bool DrawIcon(const ::point_f64 & point, ::draw2d::icon * picon) override;
      //bool DrawIcon(double x, double y, ::draw2d::icon * picon, double cx, double cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, HBITMAP hBitmap, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, HICON hIcon, ::u32 nFlags,
//                     HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, HICON hIcon, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, DRAWSTATEPROC lpDrawProc,
      //       LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr) override;
      //  bool DrawState(const ::point_f64 & point, const ::size_f64 & size, DRAWSTATEPROC lpDrawProc,
      //   LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      bool Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                 double x4, double y4) override;
      bool Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void DrawFocusRect(const ::rectangle_f64 & rectangle) override;
      //bool DrawEllipse(double x1, double y1, double x2, double y2) override;
      //bool DrawEllipse(const ::rectangle_f64 & rectangle) override;
      bool draw_ellipse(const ::rectangle_f64 & rectangle) override;
      //bool FillEllipse(double x1, double y1, double x2, double y2) override;
      //bool FillEllipse(const ::rectangle_f64 & rectangle) override;
      bool fill_ellipse(const ::rectangle_f64 & rectangle) override;
      bool Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      //bool polygon_i32(LPCPOINT lppoints, count nCount);
      bool polygon_i32(const POINT_F64 * lppoints, count nCount);
      //bool draw_polygon(LPCPOINT ppoints, count nCount) override;
      bool draw_polygon(const POINT_F64 * lppoints, count nCount) override;
      //bool fill_polygon(LPCPOINT ppoints, count nCount) override;
      bool fill_polygon(const POINT_F64 * lppoints, count nCount) override;
      //      bool poly_polygon(LPCPOINT  lppoint, LPCINT lpPolyCounts, count nCount) override;

      //virtual bool fill_polygon(const POINT_F64 * ppoints,count nCount) override;

      using ::draw2d::graphics::rectangle;
      using ::draw2d::graphics::draw_rectangle;
      using ::draw2d::graphics::fill_rectangle;
      using ::draw2d::graphics::round_rectangle;
      virtual bool rectangle(const ::rectangle_f64 & rectangle) override;
      virtual bool draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen) override;
      virtual bool fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * ppen) override;
      virtual bool round_rectangle(const ::rectangle_f64 & rectangle, double dRadius) override;


      //virtual bool _draw_raw(const ::rectangle_f64 & rectDst, ::image * pimage, const ::image_drawing_options & imagedrawingoptions, const ::point_f64 & rectSrc = ::point_f64()) override;

      using ::draw2d::graphics::_draw_raw;


      // Bitmap Functions
      //bool PatBlt(double x, double y, double nWidth, double nHeight) override;
      virtual bool _draw_raw(const ::rectangle_f64 & rectDst, ::image * pimage, const image_drawing_options & imagedrawingoptions, const ::point_f64 & pointSrc) override;
      virtual bool _stretch_raw(const ::rectangle_f64 & rectDst, ::image * pimage, const image_drawing_options & imagedrawingoptions, const ::rectangle_f64 & rectSrc) override;


      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::point_f64 & point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::point_f64 & point, const ::color::color & color) override;
//      bool FloodFill(double x, double y, const ::color::color & color) override;
//      bool ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType) override;
//      bool MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                   u32 dwRop) override;
//      bool PlgBlt(::point_f64 * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//                  double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask) override;
      bool SetPixelV(double x, double y, const ::color::color & color) override;
      bool SetPixelV(const ::point_f64 & point, const ::color::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
//                        void * pMesh, ULONG nMeshElements, u32 dwMode) override;
//      bool TransparentBlt(double xDest, double yDest, int nDestWidth, int nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, int nSrcWidth, int nSrcHeight,
//                          ::u32 clrTransparent) override;

      //virtual bool _alpha_blend_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrc, double dOpacity) override;

      /*bool alpha_blend(double xDest, double yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      //virtual bool text_out(double x, double y, const char * lpszString, strsize nCount) override;
      //virtual bool text_out(double x, double y, const block & block) override;
      virtual bool TextOutRaw(double x, double y, const block & block) override;
      //virtual bool text_out(double x, double y, const string & str) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const char * lpszString, strsize nCount, LPINT lpDxWidths) override;
      //virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const string & str, LPINT lpDxWidths) override;
      //virtual ::size_f64 TabbedTextOut(double x, double y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;
      //virtual ::size_f64 TabbedTextOut(double x, double y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;

      //virtual bool draw_text(const char * lpszString, strsize nCount, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

//      virtual int draw_text_ex(char * lpszString, int nCount, ::rectangle_f64 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;
      //    virtual int draw_text_ex(const string & str, ::rectangle_f64 * prectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;

      virtual size_f64 GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      //virtual size_f64 GetTextExtent(const char * lpszString, strsize nCount) override;
      virtual size_f64 GetTextExtent(const string & str) override;
      virtual bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex) override;
      virtual bool GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount) override;
      virtual bool GetTextExtent(size_f64 & size, const string & str) override;
      virtual ::size_f64 GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      virtual ::size_f64 GetOutputTextExtent(const string & str) override;
      //virtual ::size_f64 GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      //virtual ::size_f64 GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual ::size_f64 GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual ::size_f64 GetOutputTabbedTextExtent(const string & str, count  nTabPositions, LPINT lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, double x, double y, double nWidth, double nHeight) override;
      virtual ::u32 GetTextAlign() override;
      virtual ::u32 SetTextAlign(::u32 nFlags) override;
      //virtual int GetTextFace(count nCount, char * lpszFacename) override;
      //virtual int GetTextFace(string & rString) override;
      virtual bool get_text_metrics(::write_text::text_metric * lpMetrics) override;
      virtual bool get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount) override;
      //virtual int GetTextCharacterExtra() override;
      //virtual int SetTextCharacterExtra(int nCharExtra) override;

//      u32 GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      //    u32 GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) override;
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE32 LPSIZE32) override;
//
//#endif



      // Advanced Drawing
      //bool DrawEdge(const ::rectangle_f64 & rectangle, ::u32 nEdge, ::u32 nFlags) override;
      //bool DrawFrameControl(const ::rectangle_f64 & rectangle, ::u32 nType, ::u32 nState) override;

//      // Scrolling Functions
//      bool ScrollDC(int dx, int dy, const ::rectangle_f64 & rectScroll, const ::rectangle_f64 & rectClip,
//                    ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate) override;
//
//      // font Functions
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      u32 SetMapperFlags(u32 dwFlag) override;
//      ::size_f64 GetAspectRatioFilter() override;
//
////      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) override;
//      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
////      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) override;
////      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) override;
////      u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
////         u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;
//
////      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
////         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        float* lpFloatBuffer) override;
//
//      u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
////      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) override;
////      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif

      //// Printer/Device Escape Functions
      //virtual int Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData) override;
      //virtual int Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData) override;
      //virtual int DrawEscape(int nEscape, int nInputSize, const char * lpszInputData) override;

      // Escape helpers
      //int StartDoc(const char * lpszDocName) override;  // old Win3.0 version
//      int StartDoc(LPDOCINFO lpDocInfo) override;
      int StartPage() override;
      int EndPage() override;
      //int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int)) override;
      int AbortDoc() override;
      int EndDoc() override;

      // MetaFile Functions
      //bool PlayMetaFile(HMETAFILE hMF) override;
      //bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_f64 & rectBounds) override;
      bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData) override;
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
      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      virtual i32 GetPath(::point_f64 * ppoints, LPBYTE lpTypes, ::count nCount) override;
      bool SelectClipPath(int nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::object * pobject);
      //void DrawDragRect(const ::rectangle_f64 & rectangle, const ::size_f64 & size,
      //                  const ::rectangle_f64 & rectLast, const ::size_f64 & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      bool fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color) override;
      //void fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color) override;

      //bool draw_3drect(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;
      //void draw_3drect(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;


      virtual HDC get_handle() const;
      virtual HDC get_handle1() const;
      virtual HDC get_handle2() const;

      virtual bool attach(void * pdata) override;
      virtual void * detach() override;

#ifdef WINDOWS_DESKTOP
      //virtual bool attach_hdc(HDC hdc) override;
      //virtual HDC detach_hdc() override;
#endif

//      virtual Gdiplus::FillMode direct2d_get_fill_mode() override;

      bool blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle) override;


      virtual bool destroy();

      //IDWriteTextFormat * get_os_font(::write_text::font * pfont);
      //ID2D1Brush * get_os_brush(::draw2d::brush * pbrush);
      //ID2D1Brush * get_os_pen_brush(::draw2d::pen * ppen);

      using ::draw2d::graphics::draw;

      virtual bool draw(const ::text_out & textout, ::draw2d::pen * ppen);

      virtual bool fill(const ::text_out & textout, ::draw2d::brush * pbrush);

      virtual bool draw(const ::draw_text & drawtext, ::draw2d::pen* ppen);

      virtual bool fill(const ::draw_text & drawtext, ::draw2d::brush* pbrush);


      virtual bool flush() override;

      virtual void debug() override;
      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d::object* SelectGdiObject(application * papp, HDC hDC, HGDIOBJ h) override;

      //virtual void enum_fonts(::write_text::font_enum_item_array & itema) override;

//#ifdef _UWP
//      virtual void set_direct2d_plugin(::draw2d_direct2d::plugin * pplugin);
//#endif

      //virtual bool update_window(::image* pimage) override;

   };


} // namespace draw2d_direct2d



