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

      ::draw2d::e_text_rendering_hint                    m_etextrenderinghintDevice;


      // advanced use and implementation
      bool                                               m_bPrinting;

      HDC                                                m_hdcAttach;
      ::draw2d::e_alpha_mode                             m_ealphamodeDevice;


      graphics();
      virtual ~graphics();

      virtual bool TextOutAlphaBlend(double x, double y, const string & str) override;
      virtual bool BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop) override;

      bool IsPrinting() override;            // TRUE if being used for printing

      
      using ::draw2d::graphics::set;
      virtual ::estatus graphics::set(::draw2d::bitmap* pbitmap) override;


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

         if (m_etextrenderinghint != m_etextrenderinghintDevice)
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

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName,
                    const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual int SaveDC() override;
      virtual bool RestoreDC(int nSavedDC) override;
      int GetDeviceCaps(int nIndex) override;
      UINT SetBoundsRect(const ::rect & rectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectBounds, UINT flags) override;
      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(int x, int y) override;
      point SetBrushOrg(const ::point & point) override;
      int EnumObjects(int nObjectType,
                      int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      //virtual ::draw2d::object* set_stock_object(int nIndex) override;
      //virtual ::estatus set(::draw2d::font * pfont) override;
      //virtual ::estatus set(::draw2d::pen* pPen) override;
      //virtual ::estatus set(::draw2d::brush* pBrush) override;
      //virtual ::estatus set(::draw2d::font* pFont) override;
      //virtual ::estatus set(::draw2d::bitmap* pBitmap) override;
      //virtual i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions
      //::draw2d::object* SelectObject(::draw2d::object* pObject) override;
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      //// color and color Palette Functions
      //COLORREF GetNearestColor(const ::color & color) override;
      //// ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //UINT RealizePalette() override;
      //void UpdateColors() override;

      int GetPolyFillMode() override;
      int GetROP2() override;
      int GetStretchBltMode() override;

      int SetPolyFillMode(int nPolyFillMode) override;
      int SetROP2(int nDrawMode) override;
      int SetStretchBltMode(int nStretchMode) override;


//#if (_WIN32_WINNT >= 0x0500)
//
//      COLORREF GetDCBrushColor() override;
//      COLORREF SetDCBrushColor(const ::color & color) override;
//
//      COLORREF GetDCPenColor() override;
//      COLORREF SetDCPenColor(const ::color & color) override;
//
//#endif

      // Graphics mode
      int SetGraphicsMode(int iMode) override;
      int GetGraphicsMode() override;


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;

      virtual ::estatus clear_current_point() override;

      virtual bool draw_path(::draw2d::path * ppath) override;
      virtual bool fill_path(::draw2d::path * ppath) override;
      virtual bool path(::draw2d::path * ppath) override;

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform) override;
      bool ModifyWorldTransform(const XFORM* pXform,u32 iMode) override;
      bool GetWorldTransform(XFORM* pXform) override;

      // Mapping Functions
      virtual int GetMapMode() override;
      virtual point GetViewportOrg() override;
      virtual int SetMapMode(int nMapMode) override;
      // Viewport Origin
      virtual point SetViewportOrg(int x, int y) override;
      virtual point SetViewportOrg(const ::point & point) override;
      virtual point OffsetViewportOrg(int nWidth, int nHeight) override;

      // Viewport Extent
      virtual size GetViewportExt() override;
      virtual size SetViewportExt(int cx, int cy) override;
      virtual size SetViewportExt(const ::size & size) override;
      virtual size ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point GetWindowOrg() override;
      point SetWindowOrg(int x, int y) override;
      point SetWindowOrg(const ::point & point) override;
      point OffsetWindowOrg(int nWidth, int nHeight) override;

      // Window extent
      size GetWindowExt() override;
      virtual size SetWindowExt(int cx, int cy) override;
      size SetWindowExt(const ::size & size) override;
      virtual size ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom) override;

      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints,count nCount = 1) override;
      void DPtoLP(RECT * prect) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints,count nCount = 1) override;
      void LPtoDP(RECT * prect) override;
      void LPtoDP(LPSIZE lpSize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) override;
      void LPtoHIMETRIC(LPSIZE lpSize) override;
      void HIMETRICtoDP(LPSIZE lpSize) override;
      void HIMETRICtoLP(LPSIZE lpSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual int GetClipBox(RECT * prect) override;
      virtual bool PtVisible(int x, int y) override;
      bool PtVisible(const ::point & point) override;
      virtual bool RectVisible(const ::rect & rect) override;
      int SelectClipRgn(::draw2d::region* pRgn) override;
      int ExcludeClipRect(int x1, int y1, int x2, int y2) override;
      int ExcludeClipRect(const ::rect & rect) override;
      //int ExcludeUpdateRgn(::user::primitive * pwindow) override;
      int IntersectClipRect(int x1, int y1, int x2, int y2) override;
      int IntersectClipRect(const ::rect & rect) override;
      int OffsetClipRgn(int x, int y) override;
      int OffsetClipRgn(const ::size & size) override;
      int SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;

      // Line-Output Functions
      pointd current_position() override;
//      point move_to(int x, int y) override;
      //    point move_to(const ::point & point) override;
      using ::draw2d::graphics::line_to;
      bool line_to(const ::pointd & point) override;
      bool draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen) override;
      //  bool line_to(const ::point & point) override;
      bool Arc(double x1, double y1, double w, double h, angle start, angle extends) override;
      bool Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Arc(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      bool Polyline(const POINT* lpPoints,count nCount) override;

      bool AngleArc(int x, int y, int nRadius, angle fStartAngle, angle fSweepAngle) override;
      bool ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      int GetArcDirection() override;
      int SetArcDirection(int nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount) override;
      bool PolylineTo(const POINT* lpPoints,count nCount) override;
      bool PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount) override;

      bool PolyBezier(const POINT* lpPoints,count nCount) override;
      bool PolyBezierTo(const POINT* lpPoints,count nCount) override;


      virtual void frame_rect(const ::rect & rect, ::draw2d::brush* pBrush) override;


      virtual void invert_rect(const ::rect & rect) override;

      bool DrawIcon(int x, int y, ::draw2d::icon * picon) override;
      bool DrawIcon(const ::point & point, ::draw2d::icon * picon) override;
      bool DrawIcon(int x, int y, ::draw2d::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, UINT nFlags,
                     HBRUSH hBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                     ::draw2d::brush* pBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                     HBRUSH hBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                     ::draw2d::brush* pBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int nTextLen = 0, HBRUSH hBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //       LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr) override;
      //  bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //   LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr) override;

      // Ellipse and Polygon Functions
      bool Chord(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4) override;
      bool Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      void DrawFocusRect(const ::rect & rect) override;
      //bool DrawEllipse(int x1, int y1, int x2, int y2) override;
      //bool DrawEllipse(const ::rect & rect) override;
      bool draw_ellipse(const ::rectd & rect) override;
      //bool FillEllipse(int x1, int y1, int x2, int y2) override;
      //bool FillEllipse(const ::rect & rect) override;
      bool fill_ellipse(const ::rectd & rect) override;
      bool Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
      bool Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      //bool polygon(LPCPOINT lppoints, count nCount);
      bool polygon(const POINTD * lppoints, count nCount);
      //bool draw_polygon(LPCPOINT lpPoints, count nCount) override;
      bool draw_polygon(const POINTD * lppoints, count nCount) override;
      //bool fill_polygon(LPCPOINT lpPoints, count nCount) override;
      bool fill_polygon(const POINTD * lppoints, count nCount) override;
      //      bool poly_polygon(LPCPOINT  lppoint, LPCINT lpPolyCounts, count nCount) override;

      //virtual bool fill_polygon(const POINTD * lpPoints,count nCount) override;

      using ::draw2d::graphics::rectangle;
      using ::draw2d::graphics::draw_rect;
      using ::draw2d::graphics::fill_rect;
      using ::draw2d::graphics::round_rect;
      virtual bool rectangle(const ::rectd & rect) override;
      virtual bool draw_rect(const ::rectd & rect, ::draw2d::pen * ppen) override;
      virtual bool fill_rect(const ::rectd & rect, ::draw2d::brush * ppen) override;
      virtual bool round_rect(const ::rectd & rect, const ::pointd & point) override;


      // Bitmap Functions
      bool PatBlt(int x, int y, int nWidth, int nHeight, u32 dwRop) override;
      bool BitBltRaw(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                     int xSrc, int ySrc, u32 dwRop) override;
      bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                         int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, u32 dwRop) override;
      ::color GetPixel(int x, int y) override;
      ::color GetPixel(const ::point & point) override;
      ::color SetPixel(int x, int y, const ::color & color) override;
      ::color SetPixel(const ::point & point, const ::color & color) override;
      bool FloodFill(int x, int y, const ::color & color) override;
      bool ExtFloodFill(int x, int y, const ::color & color, UINT nFillType) override;
      bool MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
                   int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask,
                   u32 dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc,
                  int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask) override;
      bool SetPixelV(int x, int y, const ::color & color) override;
      bool SetPixelV(const ::point & point, const ::color & color) override;
      bool GradientFill(TRIVERTEX* pVertices, ULONG nVertices,
                        void * pMesh, ULONG nMeshElements, u32 dwMode) override;
      bool TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
                          UINT clrTransparent) override;

      virtual bool alpha_blendRaw(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,
        BLENDFUNCTION blend) override;*/

      // Text Functions
      virtual bool text_out(int x, int y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(int x, int y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const string & str) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::rect & rect, const char * lpszString, strsize nCount, LPINT lpDxWidths) override;
      virtual bool ExtTextOut(int x, int y, UINT nOptions, const ::rect & rect, const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(int x, int y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;
      virtual size TabbedTextOut(int x, int y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;

      virtual bool draw_text(const char * lpszString, strsize nCount, const ::rect & rect, UINT nFormat) override;
      virtual bool draw_text(const string & str,const ::rect & rect,UINT nFormat) override;

//      virtual int draw_text_ex(LPTSTR lpszString, int nCount, RECT * prect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;
      //    virtual int draw_text_ex(const string & str, RECT * prect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;

      virtual sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      //virtual sized GetTextExtent(const char * lpszString, strsize nCount) override;
      virtual sized GetTextExtent(const string & str) override;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) override;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      virtual bool GetTextExtent(sized & size, const string & str) override;
      virtual size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      virtual size GetOutputTextExtent(const string & str) override;
      virtual size GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual size GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual size GetOutputTabbedTextExtent(const string & str, count  nTabPositions, LPINT lpnTabStopPositions) override;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight) override;
      virtual UINT GetTextAlign() override;
      virtual UINT SetTextAlign(UINT nFlags) override;
      virtual int GetTextFace(count nCount, LPTSTR lpszFacename) override;
      virtual int GetTextFace(string & rString) override;
      virtual bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      virtual bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount) override;
      //virtual int GetTextCharacterExtra() override;
      //virtual int SetTextCharacterExtra(int nCharExtra) override;

//      u32 GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      //    u32 GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
//      bool GetTextExtentPointI(LPWORD pgiIn, int cgi, __out_opt LPSIZE lpSize) override;
//
//#endif



      // Advanced Drawing
      //bool DrawEdge(const ::rect & rect, UINT nEdge, UINT nFlags) override;
      //bool DrawFrameControl(const ::rect & rect, UINT nType, UINT nState) override;

//      // Scrolling Functions
//      bool ScrollDC(int dx, int dy, const ::rect & rectScroll, const ::rect & rectClip,
//                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;
//
//      // font Functions
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
//      u32 SetMapperFlags(u32 dwFlag) override;
//      size GetAspectRatioFilter() override;
//
////      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
//      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
////      int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) override;
////      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
////      u32 GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
////         u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;
//
////      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
////         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
//                        float* lpFloatBuffer) override;
//
//      u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
////      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
////      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif

      //// Printer/Device Escape Functions
      //virtual int Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData) override;
      //virtual int Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData) override;
      //virtual int DrawEscape(int nEscape, int nInputSize, const char * lpszInputData) override;

      // Escape helpers
      int StartDoc(const char * lpszDocName) override;  // old Win3.0 version
//      int StartDoc(LPDOCINFO lpDocInfo) override;
      int StartPage() override;
      int EndPage() override;
      int SetAbortProc(bool (CALLBACK* lpfn)(HDC, int)) override;
      int AbortDoc() override;
      int EndDoc() override;

      // MetaFile Functions
      bool PlayMetaFile(HMETAFILE hMF) override;
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect & rectBounds) override;
      bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
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
      virtual i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes, ::count nCount) override;
      bool SelectClipPath(int nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* GetHalftoneBrush(::layered * pobjectContext);
      //void DrawDragRect(const ::rect & rect, const ::size & size,
      //                  const ::rect & rectLast, const ::size & sizeLast,
      //                  ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;

      void fill_rect(const ::rect & rect, const ::color & color) override;
      void fill_rect(const ::rectd & rect, const ::color & color) override;

      void draw_3drect(const ::rect & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder = border_all) override;
      void draw_3drect(const ::rectd & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder = border_all) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual bool set_alpha_mode(::draw2d::e_alpha_mode ealphamode) override;


      virtual HDC get_handle() const;
      virtual HDC get_handle1() const;
      virtual HDC get_handle2() const;

      virtual bool attach(void * pdata) override;
      virtual void * detach() override;

#ifdef WINDOWS_DESKTOP
      virtual bool attach_hdc(HDC hdc) override;
      virtual HDC detach_hdc() override;
#endif

//      virtual Gdiplus::FillMode direct2d_get_fill_mode() override;

      bool blur(bool bExpand, double dRadius, const ::rect & rect) override;


      virtual bool destroy();

      //IDWriteTextFormat * get_os_font(::draw2d::font * pfont);
      //ID2D1Brush * get_os_brush(::draw2d::brush * pbrush);
      //ID2D1Brush * get_os_pen_brush(::draw2d::pen * ppen);

      virtual bool draw(::draw2d::path::text_out * ptextout, ::draw2d::pen * ppen);

      virtual bool fill(::draw2d::path::text_out * ptextout, ::draw2d::brush * pbrush);

      virtual bool draw(::draw2d::path::draw_text * ptextout, ::draw2d::pen* ppen);

      virtual bool fill(::draw2d::path::draw_text* ptextout, ::draw2d::brush* pbrush);


      virtual bool flush() override;

      virtual void debug() override;
      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d::object* SelectGdiObject(application * papp, HDC hDC, HGDIOBJ h) override;

      virtual void enum_fonts(::draw2d::font_enum_item_array & itema) override;


      //virtual bool update_window(::image* pimage) override;

   };


} // namespace draw2d_direct2d










