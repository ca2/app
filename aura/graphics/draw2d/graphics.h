#pragma once


struct NSVGimage;


namespace draw2d
{


   class CLASS_DECL_AURA graphics :
      virtual public ::aura::simple_chain < ::aura::draw_context >
   {
   public:


      bool                                m_bOutline;
      void *                              m_pthis;
      ::user::interaction *               m_puserinteraction;

      bool                                m_bPat;

      __reference(::apex::str_context)    m_pstrcontext;
      ::aura::draw_context *              m_pdrawcontext;
      ::image_pointer                     m_pimageAlphaBlend;
      point                               m_pointAlphaBlend;
      __pointer(::task)                   m_ptask;


      image *                             m_pimage;
      ::draw2d::bitmap_pointer            m_pbitmap;
      ::draw2d::pen_pointer               m_ppen;
      ::draw2d::brush_pointer             m_pbrush;
      ::draw2d::font_pointer              m_pfont;
      ::draw2d::region_pointer            m_pregion;
      bool                                m_bStoreThumbnails;

      pointd                              m_point;

      enum_alpha_mode                        m_ealphamode;
      e_smooth_mode                       m_esmoothmode;
      enum_interpolation_mode             m_einterpolationmode;
      e_compositing_quality               m_ecompositingquality;
      e_text_rendering_hint               m_etextrenderinghint;
      double                              m_dFontFactor;

      ::draw2d::matrix                    m_matrixViewport;
      ::draw2d::matrix                    m_matrixTransform;

      ::rect                              m_rectDraw;

      bool                                m_bPrinting;
      void *                              m_osdata[8];
      ::user::style_pointer               m_puserstyle;
      ::point                             m_pointAddShapeTranslate;


      graphics();
      virtual ~graphics();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      inline operator ::user::style & ()
      {

         return *m_puserstyle;

      }

      inline void clear_os_data()
      {

         m_osdata[0] = nullptr;
         m_osdata[1] = nullptr;
         m_osdata[2] = nullptr;
         m_osdata[3] = nullptr;
         m_osdata[4] = nullptr;
         m_osdata[5] = nullptr;
         m_osdata[6] = nullptr;
         m_osdata[7] = nullptr;

      }


      template < typename T >
      inline T* get_os_data(i8 i = 0) const
      {

         return (T*)m_osdata[i];

      }


      inline void* get_os_data(i8 i = 0) const
      {

         return get_os_data < void >(i);

      }

      virtual ::file::path get_font_path(const string& strName);

      virtual oswindow get_window_handle() const;


      void draw_ca2(int x,int y,int z,const ::color & colorBk,const ::color & color);
      void draw_ca2_with_border(int x,int y,int z,int b,const ::color & colorBk,const ::color & color,const ::color & colorOut);
      void draw_ca2_border2(int x,int y,int z,int bOut,int bIn,const ::color & colorBk,const ::color & color,const ::color & colorBorderOut,const ::color & colorIn);
      void draw_ca2_with_border2(int x,int y,int z,int bOut,int bIn,const ::color & colorBk,const ::color & color,const ::color & colorBorderOut,const ::color & colorIn);


      void draw_border(const ::rect & rect, const ::color & color, int iWidth);
      void draw_rect_side(const ::rect& rect, enum_border eborder);

      virtual bool is_set();


      virtual void thread_select();


      virtual ::estatus clear_current_point();


      virtual bool attach(void * pdata);
      virtual void * detach();

#ifdef WINDOWS_DESKTOP

      virtual bool attach_hdc(HDC hdc);
      virtual HDC detach_hdc();
      virtual bool AttachPrinter(HDC hdc);
      virtual HDC DetachPrinter();

#endif


      virtual bool prefer_mapped_image_on_mix();

      virtual ::apex::str_context * str_context();
      virtual ::aura::draw_context * draw_context();

      virtual bool set_alpha_mode(enum_alpha_mode ealphamode);

      virtual bool set_smooth_mode(e_smooth_mode esmoothmode);

      virtual bool set_interpolation_mode(enum_interpolation_mode einterpolationmode);

      virtual bool set_compositing_quality(e_compositing_quality ecompositingquality);

      virtual bool set_text_rendering_hint(e_text_rendering_hint etextrenderinghint);

      virtual bool blur(bool bExpand, double dRadius, const ::rect & rect);

      virtual bool set_solid_pen(double dWidth, const ::color & color);

      virtual bool IsPrinting();            // TRUE if being used for printing

      virtual ::draw2d::pen *      get_current_pen();
      virtual ::draw2d::brush *    get_current_brush();
      virtual ::draw2d::palette *  get_current_palette();
      virtual ::draw2d::font *     get_current_font();
      virtual ::draw2d::bitmap *   get_current_bitmap();

      // for bidi and mirrored localization
      virtual u32 GetLayout();
      virtual u32 SetLayout(u32 dwLayout);

      // Constructors
      virtual bool CreateDC(const char * pszDriverName, const char * pszDeviceName, const char * pszOutput, const void * lpInitData);

      virtual bool CreateIC(const char * pszDriverName, const char * pszDeviceName, const char * pszOutput, const void * lpInitData);

      virtual bool create_memory_graphics();
      virtual bool CreateCompatibleDC(::draw2d::graphics * pgraphics);
      virtual bool CreateWindowDC(oswindow wnd);

      virtual void on_begin_draw(oswindow wnd, const size & sz);
      virtual void on_end_draw(oswindow wnd);

      virtual bool DeleteDC();


      // Device-Context Functions
      virtual i32 GetDeviceCaps(i32 nIndex);
      virtual ::u32 SetBoundsRect(const ::rect & rectBounds,::u32 flags);
      virtual ::u32 GetBoundsRect(RECT32 * rectBounds,::u32 flags);
#ifdef WINDOWS
      virtual bool ResetDC(const DEVMODE* pDevMode);

#endif

      // Drawing-Tool Functions
      virtual point GetBrushOrg();
      virtual point SetBrushOrg(i32 x, i32 y);
      virtual point SetBrushOrg(const ::point & point);
      //virtual i32 EnumObjects(i32 nObjectType,
                              //i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData);



      virtual bool set_text_color(color c);

      virtual ::estatus set(::draw2d::region* pregion);
      virtual ::estatus set(::draw2d::pen* ppen);
      virtual ::estatus set(::draw2d::font* pfont);
      virtual ::estatus set(::draw2d::brush* pbrush);
      virtual ::estatus set(::draw2d::bitmap* pbitmap);
      virtual ::draw2d::object* set_stock_object(i32 nIndex);


      // color and color Palette Functions
      //virtual color32_t GetNearestColor(const ::color & color);
      //virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      //virtual ::u32 RealizePalette();
      //virtual void UpdateColors();

      // Drawing-Attribute Functions
      virtual i32 GetPolyFillMode();
      virtual i32 GetROP2();
      virtual i32 GetStretchBltMode();


      virtual double get_dpix();
      virtual double get_dpiy();

      virtual i32 SetPolyFillMode(i32 nPolyFillMode);
      virtual i32 SetROP2(i32 nDrawMode);
//      virtual bool set_interpolation_mode(enum_interpolation_mode einterpolationmode);


      virtual bool flush();
      virtual bool sync_flush();


      virtual ::size get_size();







//#ifdef WINDOWS_DESKTOP
//      virtual bool GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust);
//
//      virtual bool SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust);
//
//#endif

//#if (_WIN32_WINNT >= 0x0500)
//
//      virtual color32_t GetDCBrushColor();
//      virtual color32_t SetDCBrushColor(const ::color & color);
//
//      virtual color32_t GetDCPenColor();
//      virtual color32_t SetDCPenColor(const ::color & color);
//
//#endif

      // Graphics mode
      virtual i32 SetGraphicsMode(i32 iMode);
      virtual i32 GetGraphicsMode();

      // World transform
#ifdef WINDOWS
      virtual bool SetWorldTransform(const XFORM* pXform);
      virtual bool ModifyWorldTransform(const XFORM* pXform,u32 iMode);
      virtual bool GetWorldTransform(XFORM* pXform);
#endif

      virtual void get_viewport_scale(::draw2d::matrix & matrix);

      // Mapping Functions
      virtual i32 GetMapMode();
      virtual point GetViewportOrg();
      virtual i32 SetMapMode(i32 nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(i32 x, i32 y);
      virtual point SetViewportOrg(const ::point & point);
      virtual point OffsetViewportOrg(i32 nWidth, i32 nHeight);

      // Viewport Extent
      virtual size GetViewportExt();
      virtual size SetViewportExt(i32 cx, i32 cy);
      virtual size SetViewportExt(const ::size & size);
      virtual size ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom);

      // Window Origin
      virtual point GetWindowOrg();
      virtual point SetWindowOrg(i32 x, i32 y);
      virtual point SetWindowOrg(const ::point & point);
      virtual point OffsetWindowOrg(i32 nWidth, i32 nHeight);

      // Window extent
      virtual size GetWindowExt();
      virtual size SetWindowExt(i32 cx, i32 cy);
      virtual size SetWindowExt(const ::size & size);
      virtual size ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Coordinate Functions
      virtual void DPtoLP(POINT32 * ppoint,count nCount = 1);
      virtual void DPtoLP(RECT32 * prect);

      virtual void DPtoLP(LPSIZE32 pSize);

      virtual void LPtoDP(POINT32 * ppoint,count nCount = 1);
      virtual void LPtoDP(RECT32 * prect);

      virtual void LPtoDP(LPSIZE32 pSize);


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(LPSIZE32 pSize);

      virtual void LPtoHIMETRIC(LPSIZE32 pSize);

      virtual void HIMETRICtoDP(LPSIZE32 pSize);

      virtual void HIMETRICtoLP(LPSIZE32 pSize);


      // Region Functions
      virtual bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      virtual bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight);
      virtual bool InvertRgn(::draw2d::region* pRgn);
      virtual bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual i32 GetClipBox(RECT32 * prect);

      virtual i32 GetClipBox(rect64 * prect);

      //virtual bool PtVisible(i32 x, i32 y);
      //virtual bool PtVisible(const ::point & point);
      //virtual bool RectVisible(const ::rect & rect);
      

      
      virtual ::estatus add_shapes(const shape_array & shapea);
      virtual ::estatus reset_clip();
      virtual ::estatus intersect_clip(const ::rect& rect);
      virtual ::estatus intersect_clip(const ::rectd& rect);
      virtual ::estatus intersect_clip(const ::oval& oval);
      virtual ::estatus intersect_clip(const ::ovald& oval);
      virtual ::estatus intersect_clip(const ::polygon& polygon);
      virtual ::estatus intersect_clip(const ::polygond& polygon);

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual ::estatus _intersect_clip();
      virtual ::estatus _add_shape(___shape* pshape);
      virtual ::estatus _add_shape(const ::rect & rect);
      virtual ::estatus _add_shape(const ::rectd & rect);
      virtual ::estatus _add_shape(const ::oval & oval);
      virtual ::estatus _add_shape(const ::ovald & oval);
      virtual ::estatus _add_shape(const ::polygon & polygon);
      virtual ::estatus _add_shape(const ::polygond & polygon);

      

      
      //virtual ::estatus IntersectClipRgn(::draw2d::region * pregion);
      //virtual ::estatus IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      //virtual ::estatus IntersectClipRect(const ::rect & rect);
      //virtual i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      //virtual i32 ExcludeClipRect(const ::rect & rect);
      //virtual i32 ExcludeUpdateRgn(::user::interaction_impl * pwindow);
      //virtual i32 OffsetClipRgn(i32 x, i32 y);
      //virtual i32 OffsetClipRgn(const ::size & size);
      //virtual i32 SelectClipRgn(::draw2d::region* pregion, ::draw2d::enum_combine ecombine);

      virtual void on_apply_clip_region();

      virtual pointd current_position();

      virtual bool move_to(const ::point & point);
      virtual bool move_to(const pointd & point);

      virtual bool line_to(const ::point & point);
      virtual bool line_to(const pointd & point);

      virtual bool draw_line(const point & point1, const point & point2);
      virtual bool draw_line(const point & point1, const point & point2, ::draw2d::pen * ppen);

      virtual bool draw_line(const pointd & point1, const pointd & point2);
      virtual bool draw_line(const pointd & point1, const pointd & point2, ::draw2d::pen * ppen);

      virtual bool draw_error_line(i32 x1, i32 h, i32 x2, i32 iStyle);







      virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool Arc(const ::rect & rect,const point & pointStart,const point & pointEnd);
      virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, angle start, angle extends);
      virtual bool Arc(const ::rect & rect, angle start, angle extends);
      virtual bool Polyline(const POINT32 * ppoints,count nCount);


      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual bool Arc(const rectd & rect, const pointd & pointStart, const pointd & pointEnd);

      virtual bool Arc(double x1, double y1, double x2, double y2, angle start, angle extends);
      virtual bool Arc(const rectd & rect, angle start, angle extends);


      virtual bool AngleArc(i32 x, i32 y, i32 nRadius, angle fStartAngle, angle fSweepAngle);
      virtual bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool ArcTo(const ::rect & rect,const point & pointStart,const point & pointEnd);
      virtual i32 GetArcDirection();
      virtual i32 SetArcDirection(i32 nArcDirection);

      virtual bool PolyDraw(const POINT32 * ppoints, const byte* pTypes,count nCount);

      virtual bool PolylineTo(const POINT32 * ppoints,count nCount);
      virtual bool PolyPolyline(const POINT32 * ppoints, const int * pPolyPoints,count nCount);


      virtual bool PolyBezier(const POINT32 * ppoints,count nCount);
      virtual bool PolyBezierTo(const POINT32 * ppoints,count nCount);

      virtual void frame_rect(const ::rect & rect, ::draw2d::brush* pbrush);
      virtual void invert_rect(const ::rect & rect);
      
//      virtual bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS
//      virtual bool DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * pszText, ::u32 nFlags,

  //                           bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * pszText, ::u32 nFlags,
//
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS_DESKTOP
//      virtual bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC pDrawProc,
//
//                             LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC pDrawProc,
//
//                             LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
      // Ellipse and Polygon Functions
      virtual bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                         i32 x4, i32 y4);
      virtual bool Chord(const ::rect & rect, const point & pointStart, const point & pointEnd);

      virtual void DrawFocusRect(const ::rect & rect);

    /*  virtual bool ellipse(double x1, double y1, double x2, double y2);
      virtual bool ellipse(const ::rectd & rect);

      virtual bool draw_ellipse(double x1, double y1, double x2, double y2);
      virtual bool draw_ellipse(const ::rectd & rect);

      virtual bool fill_ellipse(double x1, double y1, double x2, double y2);
      virtual bool fill_ellipse(const ::rectd & rect);*/



      virtual bool ellipse(double x1,double y1,double x2,double y2);
      virtual bool ellipse(const rectd & prect);

      virtual bool draw_ellipse(double x1,double y1,double x2,double y2);
      virtual bool draw_ellipse(const rectd & prect);

      virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      virtual bool fill_ellipse(const rectd & prect);


      virtual bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool Pie(const ::rect & rect, const point & pointStart, const point & pointEnd);


      virtual bool polygon(const POINT32 * ppoints, count nCount);
      virtual bool polygon(const POINTD * ppoints, count nCount);
      virtual bool draw_polygon(const POINT32 * ppoints, count nCount);
      virtual bool draw_polygon(const POINTD * ppoints, count nCount);
      virtual bool fill_polygon(const POINT32 * ppoints,count nCount);
      virtual bool fill_polygon(const POINTD * ppoints,count nCount);

      virtual bool poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool draw_poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool draw_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool fill_poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool fill_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);


      virtual bool rectangle(const ::rect & rect);
      virtual bool draw_rect(const ::rect & rect);
      virtual bool draw_rect(const ::rect & rect, ::draw2d::pen * ppen);
      virtual bool fill_rect(const ::rect & rect);
      virtual bool fill_rect(const ::rect & rect, ::draw2d::brush * pbrush);

      virtual bool rectangle(const rectd & rectd);
      virtual bool draw_rect(const rectd & rectd);
      virtual bool draw_rect(const rectd & rectd, ::draw2d::pen * ppen);
      virtual bool fill_rect(const rectd & rectd);
      virtual bool fill_rect(const rectd & rectd, ::draw2d::brush * pbrush);

      virtual bool round_rect(const ::rect & rect, const ::point & point);

      virtual bool round_rect(const ::rectd & rectd, const ::pointd & point);


      //virtual bool from(const ::point & pointDst, const ::size & size, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc);
      //virtual bool from(const ::size & size, ::draw2d::graphics * pgraphicsSrc, const point & pSrc);
      //virtual bool from(const ::size & size, ::draw2d::graphics * pgraphicsSrc);
      //virtual bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight);



      //virtual bool draw_image(const ::rect & rect, ::draw2d::graphics * pgraphicsSrc, const ::point & point);

      //virtual bool draw_image(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rect);
      //virtual bool draw_image(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rect);
      //virtual bool draw_image(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc);
      // virtual bool draw_image(const ::rectd & rectdDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc);


      // bit block transfer (pixel-to-pixel)
      virtual bool draw_at(const ::point & pointDst, ::image * pimage);
      virtual bool draw_at(const ::point & pointDst, ::image_frame * pframe);
      virtual bool draw_at(const ::point & pointDst, ::draw2d::graphics * pgraphicsSrc);


      // bit block transfer (pixel-to-pixel)
      virtual bool draw(::image * pimage, const ::point & pointSrc = ::point());
      virtual bool draw(::image_frame * pframe, const ::point & pointSrc = ::point());
      virtual bool draw(::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc = ::point());
      virtual bool draw(const ::rect & rectDst, ::image * pimage, const ::point & pointSrc = ::point());
      virtual bool draw(const ::rect & rectDst, ::image_frame * pframe, const ::point & pointSrc = ::point());
      virtual bool draw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc = ::point());
      virtual bool draw_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc = ::point());
      virtual bool draw_blend(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc = ::point());




      // potentially stretching
      virtual bool stretch(const ::rect & rectDst, ::image * pimage, const ::rect & rectSrc = ::rect());
      virtual bool stretch(const ::rect & rectDst, ::image_frame * pframe, const ::rect & rectSrc = ::rect());
      virtual bool stretch(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc = ::rect());
      virtual bool stretch_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc = ::rect());
      virtual bool stretch_blend(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc = ::rect());


      //virtual bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      //virtual bool StretchBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);

      //virtual bool StretchBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      //virtual bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      //virtual bool StretchBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);
      //virtual bool StretchBltAlphaBlend(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight);

      virtual ::color GetPixel(i32 x, i32 y);
      virtual ::color GetPixel(const ::point & point);
      virtual ::color SetPixel(i32 x, i32 y, const ::color & color);
      virtual ::color SetPixel(const ::point & point, const ::color & color);
      virtual ::color blend_pixel(const ::point& point, const ::color& color);
//      virtual bool FloodFill(i32 x, i32 y, const ::color & color);
//      virtual bool ExtFloodFill(i32 x, i32 y, const ::color & color, ::u32 nFillType);
//      virtual bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                           i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
//                           u32 dwRop);
//      virtual bool PlgBlt(POINT32 * pPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//
//                          i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask);
      virtual bool SetPixelV(i32 x, i32 y, const ::color & color);
      virtual bool SetPixelV(const ::point & point, const ::color & color);
      //virtual bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
      //void * pMesh, WINULONG nMeshElements, u32 dwMode);
//      virtual bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
//                                  ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                                  ::u32 clrTransparent);

      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);
      virtual bool alpha_blend(const point & pDst, const size & sizeDst,::draw2d::graphics * pgraphicsSrc, const point & pSrc, size szSrc, double dOpacity);
      inline bool alpha_blend(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc, double dOpacity)
      {
         return alpha_blend(rectDst.top_left(), rectDst.size(), pgraphicsSrc, rectSrc.top_left(), rectSrc.size(), dOpacity);
      }
      virtual bool alpha_blend(const point & pDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, const point & pSrc, double dOpacity);
      virtual bool alpha_blend(const point & pDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, double dOpacity);
      virtual bool alpha_blend(const ::rect & rect, ::draw2d::graphics * pgraphicsSrc, double dOpacity);
      virtual bool alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, const point & pSrc, double dOpacity);
      virtual bool alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, double dOpacity);


      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::image * pimage, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity);
      virtual bool alpha_blend(const point & pDst, const size & sizeDst, ::image * pimage, const point & pSrc, size szSrc, double dOpacity);
      inline bool alpha_blend(const ::rect & rectDst, ::image * pimage, const ::rect & rectSrc, double dOpacity)
      {
         return alpha_blend(rectDst.top_left(), rectDst.size(), pimage, rectSrc.top_left(), rectSrc.size(), dOpacity);
      }
      virtual bool alpha_blend(const point & pDst, const ::size & size, ::image * pimage, const point & pSrc, double dOpacity);
      virtual bool alpha_blend(const point & pDst, const ::size & size, ::image * pimage, double dOpacity);
      virtual bool alpha_blend(const ::rect & rect, ::image * pimage, double dOpacity);
      virtual bool alpha_blend(const ::size & size, ::image * pimage, const point & pSrc, double dOpacity);
      virtual bool alpha_blend(const ::size & size, ::image * pimage, double dOpacity);


      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate);
      virtual bool alpha_blendAlphaBlend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate);


      /*      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
              ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
              BLENDFUNCTION blend);*/
      /*      virtual bool alpha_blend(const point & pDst, const size & sizeDst,::draw2d::graphics * pgraphicsSrc, const point & pSrc, size szSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(const point & pDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, const point & pSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(const point & pDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, const point & pSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool text_out(i32 x, i32 y, const char * pszString, strsize nCount);

      virtual bool text_out(i32 x, i32 y, const string & str);
      virtual bool text_out(double x, double y, const char * pszString, strsize nCount);

      inline bool text_out(const ::point& point, const string& str) { return text_out((::i32) point.x, (::i32) point.y, str); }

      virtual bool text_out(double x, double y, const string & str);
      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const char * pszString, strsize nCount, i32 * lpDxWidths);

      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const string & str, i32 * lpDxWidths);

      virtual size TabbedTextOut(i32 x, i32 y, const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions, i32 nTabOrigin);

      virtual size TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, i32 * pnTabStopPositions, i32 nTabOrigin);



      virtual bool TextOutRaw(double x, double y, const string & str);

      virtual bool TextOutAlphaBlend(double x, double y, const string & str);


      virtual bool _001DrawText(const string & str, rectd & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false);


      virtual bool draw_text(const string & str, const ::rect & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      virtual bool draw_text(const string & str,const rectd & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);


#ifndef _UWP

//      virtual bool draw_text_ex(const string & str,const ::rect & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

//      virtual bool draw_text_ex(const string & str,const rectd & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual bool draw_text_ex(const string & str,const ::rect & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      virtual bool draw_text_ex(const string & str,const rectd & prect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#endif


      virtual ::count get_character_extent(double_array & daLeft, double_array & daRight, const string & str, strsize iStart = 0, strsize iCount = -1);

      virtual sized GetTextExtent(const char * pszString, strsize nCount, strsize iIndex);

      virtual sized GetTextBegin(const char * pszString, strsize nCount, strsize iIndex);

      virtual sized GetTextExtent(const char * pszString, strsize nCount);

      virtual sized GetTextExtent(const string & str);
      virtual bool GetTextExtent(sized & size, const char * pszString, strsize nCount, strsize iIndex);

      virtual bool GetTextExtent(sized & size, const char * pszString, strsize nCount);

      virtual bool GetTextExtent(sized & size, const string & str);
      virtual size GetOutputTextExtent(const char * pszString, strsize nCount);

      virtual size GetOutputTextExtent(const string & str);
      virtual size GetTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions);

      virtual size GetTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions);

      virtual size GetOutputTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions);

      virtual size GetOutputTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions);

      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);

      virtual ::u32 GetTextAlign();
      virtual ::u32 SetTextAlign(::u32 nFlags);
      virtual i32 GetTextFace(count nCount, char * pszFacename);

      virtual i32 GetTextFace(string & rString);


      virtual text_metric get_text_metrics();
      virtual bool get_text_metrics(text_metric * pmetrics);
      virtual bool get_output_text_metrics(text_metric * pMetrics);



      //virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      //virtual i32 GetTextCharacterExtra();
      //virtual i32 SetTextCharacterExtra(i32 nCharExtra);

// #ifdef WINDOWS_DESKTOP

//       virtual u32 GetCharacterPlacement(const char * pString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags);

//       virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS pResults, u32 dwFlags);


// #endif

// #if (_WIN32_WINNT >= 0x0500)

//       virtual bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, i32 * pnFit, i32 * alpDx, __out_opt LPSIZE32 LPSIZE32);

//       virtual bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 pSize);


// #endif

//
//
//  /*    // Advanced Drawing
//      virtual bool DrawEdge(const ::rect & prect,::u32 nEdge,::u32 nFlags);
//
//      virtual bool DrawFrameControl(const ::rect & prect,::u32 nType,::u32 nState);
//*/

      //// Scolorolling Functions
      //virtual bool ScrollDC(i32 dx, i32 dy, const ::rect &  pRectScoloroll, const ::rect &  lpRectClip,

      //                      ::draw2d::region* pRgnUpdate, RECT32 * pRectUpdate);


      // font Functions
//      virtual bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual u32 SetMapperFlags(u32 dwFlag);
//      virtual size GetAspectRatioFilter();

// #ifdef WINDOWS_DESKTOP

//       virtual bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC pabc);


// #endif

//      virtual u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID pData, u32 cbData);


// #ifdef WINDOWS_DESKTOP

//       virtual i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR pkrnpair);

//       virtual ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW potm);

//       virtual u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm, u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2);


//       virtual bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT pABCF);


// #endif

      // virtual bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float * pFloatBuffer);


      // virtual u32 GetFontLanguageInfo();

//#if defined(WINDOWS_DESKTOP) && (_WIN32_WINNT >= 0x0500)
//
//      virtual bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC pabc);
//
//      virtual bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, i32 * pBuffer);
//
//
//#endif

      //// Printer/Device Escape Functions
      //virtual i32 Escape(i32 nEscape, i32 nCount, const char * pszInData, LPVOID lpOutData);

      //virtual i32 Escape(i32 nEscape, i32 nInputSize, const char * pszInputData, i32 nOutputSize, char * pszOutputData);

      //virtual i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * pszInputData);


      // Escape helpers
      virtual i32 StartDoc(const char * pszDocName);  // old Win3.0 version


#ifdef WINDOWS_DESKTOP

      virtual i32 StartDoc(LPDOCINFOW pDocInfo);

#endif

      virtual i32 StartPage();
      virtual i32 EndPage();
//      virtual i32 SetAbortProc(bool (CALLBACK* pfn)(HDC, i32));

      virtual i32 AbortDoc();
      virtual i32 EndDoc();

      // MetaFile Functions
#ifdef WINDOWS
      virtual bool PlayMetaFile(HMETAFILE hMF);
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect &  pBounds);

#endif
      virtual bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData);
      // can be used for enhanced metafiles only

      virtual bool abort_path();
      virtual bool begin_path();
      virtual bool close_figure();
      virtual bool end_path();
      virtual bool fill_path();
      virtual bool flatten_path();
      virtual bool stroke_and_fill_path();
      virtual bool stroke_path();
      virtual bool widen_path();
      virtual float GetMiterLimit();
      virtual bool SetMiterLimit(float fMiterLimit);
      virtual i32 GetPath(POINT32 * ppoint, byte * pTypes, count nCount);

      virtual bool SelectClipPath(i32 nMode);

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      virtual bool draw_path(::draw2d::path * ppath);
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      virtual bool fill_path(::draw2d::path * ppath);
      virtual bool path(::draw2d::path * ppath);

      // Misc helper Functions
      virtual ::draw2d::brush * GetHalftoneBrush();
      //virtual void DrawDragRect(const ::rect & rect, const ::size & size,

      //                          const ::rect &  pRectLast, const size & sizeLast,

      //                          ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);

      virtual void fill_rect(const ::rect & rect, const ::color & color);
      virtual void fill_rect(const rectd & rectd, const ::color & color);

      virtual void draw_3drect(const ::rect & rect, const ::color& colorTopLeft, const ::color& colorBottomRight, eborder eborder = e_border_all);
      virtual void draw_3drect(const rectd & rectd, const ::color& colorTopLeft, const ::color& colorBottomRight, eborder eborder = e_border_all);

      virtual void draw_rect(const ::rect & rect, const ::color& color, eborder eborder = e_border_all);
      virtual void draw_rect(const rectd & rectd, const ::color& color, eborder eborder = e_border_all);

      virtual bool set_font(::user::interaction* pinteraction, ::user::eelement eelement = ::user::e_element_none, ::user::estate estate = ::user::e_state_none);


      virtual bool get(matrix & matrix);
      using ::aura::simple_chain < ::aura::draw_context >::set;
      virtual bool set(const matrix & matrix);
      virtual bool append(const matrix & matrix);
      virtual bool prepend(const matrix & matrix);
      virtual bool update_matrix();

      virtual bool _get(matrix & matrix);
      virtual bool _set(const matrix & matrix);

      //=============================================================================
      //
      // draw_round_rect()
      //
      // Purpose:     Draws a rounded rectangle with a solid pen
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rect        - [in]   Rect that defines the round rectangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //          width    - [in]  width of the border
      //
      // Returns:     None
      //
      bool draw_round_rect(const ::rect & rect, ::draw2d::pen * ppen, i32 radius, eborder eborder = e_border_all);
      //bool draw_round_top_left(const ::rect & rect, ::draw2d::pen * ppen, i32 radius, eborder eborder = e_border_all);
      //bool draw_round_bottom_right(const ::rect & rect, ::draw2d::pen * ppen, i32 radius, eborder eborder = e_border_all);

      bool draw_round_rect(const ::rect & rect, const ::color & color, i32 radius, i32 width, eborder eborder = e_border_all);
      //bool draw_round_top_left(const ::rect & rect, const ::color & color, i32 radius, i32 width, eborder eborder = e_border_all);
      //bool draw_round_bottom_right(const ::rect & rect, const ::color & color, i32 radius, i32 width, eborder eborder = e_border_all);


      bool draw_stock_icon(const ::rectd & rect, e_stock_icon eicon);


      //=============================================================================
      //
      // fill_round_rect()
      //
      // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
      //          first then fills in the rectangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rect        - [in]   Rect that defines the round rectangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const ::rect & rect, const ::color & color, i32 radius);

      //=============================================================================
      //
      // fill_round_rect()
      //
      // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
      //          first then fills in the rectangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          pBrush      - [in]  pointer to a Brush
      //          rect        - [in]   Rect that defines the round rectangle boundaries
      //          color    - [in]   Color value for the border (needed in case the
      //                         brush is a type other than solid)
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const ::rect & rect, ::draw2d::brush * pbrush, i32 radius);


      bool round_rect(const ::rect & rect, i32 radius);

      virtual i32 _DrawText(const string & str, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, ::draw2d::font * pfontUnderline = nullptr);

      virtual void debug();


      virtual void enum_fonts(::draw2d::font_enum_item_array & itema);
      virtual void sorted_fonts(::draw2d::font_enum_item_array & itema);


      virtual float nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy);
      virtual void nanosvg_cubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tol, int level);
      virtual void nanosvg_drawPath(float* pts, int npts, char closed, float tol, const ::color & color);
      virtual void nanosvg_drawControlPts(float* pts, int npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, int x, int y, int w, int h);
      // virtual void nanosvg_resizecb(int width, int height, int x, int y, int w, int h);

      virtual bool nanosvg(string str, int x, int y, int w, int h);

      virtual bool is_valid_update_window_thread();

      inline bool move_to(i32 x, i32 y) { return move_to(::point(x, y)); }
      inline bool move_to(double x, double y) { return move_to(pointd(x, y)); }

      inline bool line_to(i32 x, i32 y) { return line_to(::point(x, y)); }
      inline bool line_to(double x, double y) { return line_to(pointd(x, y)); }

      inline bool draw_line(i32 x1, i32 y1, i32 x2, i32 y2) { return draw_line(point(x1,y1), point(x2, y2)); }
      inline bool draw_line(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::pen * ppen) { return draw_line(point(x1, y1), point(x2, y2), ppen); }

      inline bool draw_line(double x1, double y1, double x2, double y2) { return draw_line(pointd(x1, y1), pointd(x2, y2)); }
      inline bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(pointd(x1, y1), pointd(x2, y2), ppen); }

      inline bool rectangle_coord(i32 x1, i32 y1, i32 x2, i32 y2) { return rectangle(::rect(x1, y1, x2, y2)); }
      inline bool rectangle_coord(double x1, double y1, double x2, double y2) { return rectangle(rectd(x1, y1, x2, y2)); }

      inline bool rectangle_dim(i32 x, i32 y, i32 cx, i32 cy) { return rectangle(rect_dim(x, y, cx, cy)); }
      inline bool rectangle_dim(double x, double y, double cx, double cy) { return rectangle(rectd_dim(x, y, cx, cy)); }

      inline bool draw_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2) { return draw_rect(::rect(x1, y1, x2, y2)); }
      inline bool draw_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::pen * ppen) { return draw_rect(::rect(x1, y1, x2, y2), ppen); }
      inline bool draw_rect_coord(double x1, double y1, double x2, double y2) { return draw_rect(rectd(x1, y1, x2, y2)); }
      inline bool draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_rect(rectd(x1, y1, x2, y2), ppen); }

      inline bool draw_rect_dim(i32 x, i32 y, i32 cx, i32 cy) { return draw_rect(rect_dim(x, y, cx, cy)); }
      inline bool draw_rect_dim(i32 x, i32 y, i32 cx, i32 cy, ::draw2d::pen * ppen) { return draw_rect(rect_dim(x, y, cx, cy), ppen); }
      inline bool draw_rect_dim(double x, double y, double cx, double cy) { return draw_rect(rectd_dim(x, y, cx, cy)); }
      inline bool draw_rect_dim(double x, double y, double cx, double cy, ::draw2d::pen * ppen) { return draw_rect(rectd_dim(x, y, cx, cy), ppen); }

      inline bool fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2) { return fill_rect(::rect(x1, y1, x2, y2)); }
      inline bool fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, ::draw2d::brush * pbrush) { return fill_rect(::rect(x1, y1, x2, y2), pbrush); }
      inline bool fill_rect_coord(double x1, double y1, double x2, double y2) { return fill_rect(rectd(x1, y1, x2, y2)); }
      inline bool fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush) { return fill_rect(rectd(x1, y1, x2, y2), pbrush); }

      inline bool fill_rect_dim(i32 x, i32 y, i32 cx, i32 cy) { return fill_rect(rect_dim(x, y, cx, cy)); }
      inline bool fill_rect_dim(i32 x, i32 y, i32 cx, i32 cy, ::draw2d::brush * pbrush) { return fill_rect(rect_dim(x, y, cx, cy), pbrush); }
      inline bool fill_rect_dim(double x, double y, double cx, double cy) { return fill_rect(rectd_dim(x, y, cx, cy)); }
      inline bool fill_rect_dim(double x, double y, double cx, double cy, ::draw2d::brush * pbrush) { return fill_rect(rectd_dim(x, y, cx, cy), pbrush); }

      inline bool polygon(point_array & pointa) { return polygon(pointa.get_data(), pointa.get_count()); }
      inline bool polygon(pointd_array & pointa) { return polygon(pointa.get_data(), pointa.get_count()); }
      inline bool draw_polygon(point_array & pointa) { return draw_polygon(pointa.get_data(), pointa.get_count()); }
      inline bool draw_polygon(pointd_array & pointa) { return draw_polygon(pointa.get_data(), pointa.get_count()); }
      inline bool fill_polygon(point_array & pointa) { return fill_polygon(pointa.get_data(), pointa.get_count()); }
      inline bool fill_polygon(pointd_array & pointa) { return fill_polygon(pointa.get_data(), pointa.get_count()); }

      inline void fill_solid_rect_dim(i32 x, i32 y, i32 cx, i32 cy, const ::color & color) { return fill_rect(rect_dim(x, y, cx, cy), color); }
      inline void fill_solid_rect_dim(double x, double y, double cx, double cy, const ::color & color) { return fill_rect(rectd_dim(x, y, cx, cy), color); }

      inline void fill_solid_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, const ::color & color) { return fill_rect(::rect(x1, y1, x2, y2), color); }
      inline void fill_solid_rect_coord(double x1, double y1, double x2, double y2, const ::color & color) { return fill_rect(rectd(x1, y1, x2, y2), color); }

      inline void draw_3drect_dim(i32 x, i32 y, i32 cx, i32 cy, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rect_dim(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      inline void draw_3drect_dim(double x, double y, double cx, double cy, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rectd_dim(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      inline void draw_rect_dim(i32 x, i32 y, i32 cx, i32 cy, const ::color& color) { return draw_rect(rect_dim(x, y, cx, cy), color); }
      inline void draw_rect_dim(double x, double y, double cx, double cy, const ::color& color) { return draw_rect(rectd_dim(x, y, cx, cy), color); }

      inline void draw_3drect_coord(i32 x1, i32 y1, i32 x2, i32 y2, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(::rect(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rectd(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      inline void draw_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, const ::color& color) { return draw_rect(::rect(x1, y1, x2, y2), color); }
      inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color& color) { return draw_rect(rectd(x1, y1, x2, y2), color); }


      //inline bool draw(::image * pimage);
      //inline bool draw(const point & pDst, const ::size & size, ::draw2d::graphics * pgraphicsSrc, const point & pSrc = nullptr) { return draw(::rect(pDst, size), pgraphicsSrc, pSrc); }
      //inline bool draw(const ::size & size, ::draw2d::graphics * pgraphicsSrc, const point & pSrc = nullptr) { return draw(::rect(size), pgraphicsSrc, pSrc); }
      //inline bool draw_dim(i32 x, i32 y, i32 w, i32 h, ::draw2d::graphics * pgraphicsSrc, i32 xSrc = 0, i32 ySrc = 0) { return draw(rect_dim(x, y, w, h), pgraphicsSrc, ::point(xSrc, ySrc)); }
      //inline bool BitBlt(i32 x, i32 y, i32 w, i32 h, ::draw2d::graphics * pgraphicsSrc, i32 xSrc = 0, i32 ySrc = 0) { return draw_dim(x, y, w, h, pgraphicsSrc, xSrc, ySrc); }


      //inline bool draw::image * pimage;
      //inline bool draw(const point & pDst, const ::size & size, ::image * pimage, const point & pSrc = nullptr);
      //inline bool draw(const ::size & size, ::image * pimage, const point & pSrc = nullptr);
      //inline bool draw_dim(i32 x, i32 y, i32 w, i32 h, ::image * pimage, i32 xSrc = 0, i32 ySrc = 0);
      //inline bool BitBlt(i32 x, i32 y, i32 w, i32 h, ::image * pimage, i32 xSrc = 0, i32 ySrc = 0);
      virtual bool draw(const ::point & point, cursor * pcursor);
      virtual bool draw(const ::rect & rectDst, icon * picon);

   protected:

      friend class savedc;
      virtual i32 SaveDC();
      virtual bool RestoreDC(i32 nSavedDC);

   };


   class CLASS_DECL_AURA savedc
   {
   public:


      graphics *     m_pgraphics;
      int            m_iSavedDC;

      matrix         m_matrixViewport;
      matrix         m_matrixTransform;

      savedc(graphics * graphics);
      ~savedc();


   };

   CLASS_DECL_AURA ::draw2d::graphics_pointer create_graphics();
   CLASS_DECL_AURA ::draw2d::graphics_pointer create_memory_graphics();



} // namespace draw2d


CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::size & size);
CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::point & point);



CLASS_DECL_AURA PFN_factory_exchange get_draw2d_factory_exchange();

CLASS_DECL_AURA void set_draw2d_factory_exchange(PFN_factory_exchange pfnfactoryDraw2d);

