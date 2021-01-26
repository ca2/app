#pragma once



struct NSVGimage;

namespace draw2d
{


   class graphics;


   //template < typename GRAPHICS_SOURCE_POINTER >
   //concept graphics_source_pointer = requires(const ::image_drawing & imagedrawing, const ::sized & sizeHint)
   //{

   //   { pgraphicssource->g(sizeHint) } -> ::std::convertible_to < ::draw2d::graphics * >;
   //   { pgraphicssource->origin() } -> ::std::convertible_to < ::sized >;
   //   { pgraphicssource->size(sizeHint) } -> ::std::convertible_to < ::sized >;

   //};

/// <summary>
/// graphics * -> image_source_pointer concept
/// </summary>
   class CLASS_DECL_AURA graphics :
      virtual public ::aura::simple_chain < ::aura::draw_context >,
      virtual public ::image_drawer
   {
   public:


      bool                                   m_bOutline;
      void *                                 m_pthis;
      ::user::interaction *                  m_puserinteraction;

      bool                                   m_bPat;

      __reference(::apex::str_context)       m_pstrcontext;
      ::aura::draw_context *                 m_pdrawcontext;
      ::image_pointer                        m_pimageAlphaBlend;
      ::pointd                               m_pointAlphaBlend;
      __pointer(::task)                      m_ptask;


      image * m_pimage;
      ::draw2d::bitmap_pointer               m_pbitmap;
      ::draw2d::pen_pointer                  m_ppen;
      ::draw2d::brush_pointer                m_pbrush;
      ::draw2d::font_pointer                 m_pfont;
      ::draw2d::font_pointer                 m_pfontDevice;
      ::draw2d::region_pointer               m_pregion;
      bool                                   m_bStoreThumbnails;

      ::pointd                               m_point;

      enum_alpha_mode                        m_ealphamode;
      e_smooth_mode                          m_esmoothmode;
      enum_interpolation_mode                m_einterpolationmode;
      e_compositing_quality                  m_ecompositingquality;
      e_text_rendering_hint                  m_etextrenderinghint;
      double                                 m_dFontFactor;

      ::draw2d::matrix                       m_matrixViewport;
      ::draw2d::matrix                       m_matrixTransform;

      ::rectd                                m_rectDraw;

      bool                                   m_bPrinting;
      void * m_osdata[8];
      ::user::style_pointer                  m_puserstyle;
      ::pointd                               m_pointAddShapeTranslate;


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
      inline T * get_os_data(i8 i = 0) const
      {

         return (T *)m_osdata[i];

      }


      inline void * get_os_data(i8 i = 0) const
      {

         return get_os_data < void >(i);

      }

      virtual ::file::path get_font_path(const string & strName, int iWeight, bool bItalic);

      virtual oswindow get_window_handle() const;
      
      
      
      inline ::draw2d::graphics * g(const ::sized & sizeHint) { return this; }
      inline ::sized origin() const { return ::sized(); }


      inline ::image * get_image(const concrete < ::size > & sizeDst) { return m_pimage->get_image(sizeDst); }


      inline concrete < ::size > size(const ::sized & sizeDst, enum_image_selection eimageselection) const { return m_pimage->size(sizeDst, eimageselection); }
      inline concrete < ::size > size() const { return m_pimage->size(); }


      //#ifdef _UWP
      //
      //
      //      virtual void set_directd2d_plugin(::draw2d_directd2d::plugin * pplugin);
      //
      //
      //#endif


      virtual bool on_begin_draw();


      


      void draw_ca2(int x,int y,int z,const ::color & colorBk,const ::color & color);
      void draw_ca2_with_border(int x,int y,int z,int b,const ::color & colorBk,const ::color & color,const ::color & colorOut);
      void draw_ca2_border2(int x,int y,int z,int bOut,int bIn,const ::color & colorBk,const ::color & color,const ::color & colorBorderOut,const ::color & colorIn);
      void draw_ca2_with_border2(int x,int y,int z,int bOut,int bIn,const ::color & colorBk,const ::color & color,const ::color & colorBorderOut,const ::color & colorIn);


      void draw_border(const ::rectd & rect, const ::color & color, int iWidth);
      void draw_rect_side(const ::rectd& rectd, enum_border eborder);

      virtual bool is_set();


      virtual void thread_select();


      virtual ::e_status clear_current_point();


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

      virtual e_smooth_mode get_smooth_mode();

      virtual bool blur(bool bExpand, double dRadius, const ::rectd & rect);

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

      virtual void on_begin_draw(oswindow wnd, const ::sized & sz);
      virtual void on_end_draw(oswindow wnd);

      virtual bool DeleteDC();


      // Device-Context Functions
      virtual i32 GetDeviceCaps(i32 nIndex);
      virtual ::u32 SetBoundsRect(const ::rectd & rectBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::rectd * rectdBounds, ::u32 flags);
      
#ifdef WINDOWS
      virtual bool ResetDC(const DEVMODE* pDevMode);

#endif

      // Drawing-Tool Functions
      virtual ::pointd GetBrushOrg();
      virtual ::pointd SetBrushOrg(double x, double y);
      virtual ::pointd SetBrushOrg(const ::pointd & point);
      //virtual i32 EnumObjects(i32 nObjectType,
                              //i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData);



      virtual bool set_text_color(color c);

      virtual ::e_status set(::draw2d::region* pregion);
      virtual ::e_status set(::draw2d::pen* ppen);
      virtual ::e_status set(::draw2d::font* pfont);
      virtual ::e_status set(::draw2d::brush* pbrush);
      virtual ::e_status set(::draw2d::bitmap* pbitmap);
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


      virtual ::sized get_size() const;

      virtual ::size get_image_drawer_size() const;







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
      virtual ::pointd GetViewportOrg();
      virtual i32 SetMapMode(i32 nMapMode);
      // Viewport Origin
      virtual ::pointd SetViewportOrg(double x, double y);
      virtual ::pointd SetViewportOrg(const ::pointd & pointd);
      virtual ::pointd OffsetViewportOrg(double x, double y);

      // Viewport Extent
      virtual ::sized GetViewportExt();
      virtual ::sized SetViewportExt(double cx, double cy);
      virtual ::sized SetViewportExt(const ::sized & size);
      virtual ::sized ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom);

      // Window Origin
      virtual ::pointd GetWindowOrg();
      virtual ::pointd SetWindowOrg(double x, double y);
      virtual ::pointd SetWindowOrg(const ::pointd & point);
      virtual ::pointd offset_window_org(double nWidth, double nHeight);

      // Window extent
      virtual ::sized GetWindowExt();
      virtual ::sized set_window_ext(double cx, double cy);
      virtual ::sized set_window_ext(const ::sized & size);
      virtual ::sized scale_window_ext(double xNum, double xDenom, double yNum, double yDenom);

      // Coordinate Functions
      virtual void DPtoLP(::pointd * ppoint,count nCount = 1);
      virtual void DPtoLP(::rectd * prectd);

      virtual void DPtoLP(::sized * pSize);

      virtual void LPtoDP(::pointd * ppoint,count nCount = 1);
      virtual void LPtoDP(::rectd * prectd);

      virtual void LPtoDP(::sized * pSize);


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(::sized * pSize);

      virtual void LPtoHIMETRIC(::sized * pSize);

      virtual void HIMETRICtoDP(::sized * pSize);

      virtual void HIMETRICtoLP(::sized * pSize);


      // Region Functions
      virtual bool fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush);
      virtual bool frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight);
      virtual bool invert_region(::draw2d::region* pregion);
      virtual bool paint_region(::draw2d::region* pregion);

      // Clipping Functions
      virtual i32 get_clip_box(::rectd * prect);

      //virtual i32 get_clip_box(::rectd * prect);

      //virtual bool PtVisible(double x, double y);
      //virtual bool PtVisible(const ::pointd & point);
      //virtual bool RectVisible(const ::rectd & rect);
      

      
      virtual ::e_status add_shapes(const shape_array & shapea);
      virtual ::e_status reset_clip();
      virtual ::e_status intersect_clip(const ::rectd& rectd);
      virtual ::e_status intersect_clip(const ::ovald& oval);
      virtual ::e_status intersect_clip(const ::polygond& polygon);

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual ::e_status _intersect_clip();
      virtual ::e_status _add_shape(___shape* pshape);
      virtual ::e_status _add_shape(const ::rectd & rect);
      virtual ::e_status _add_shape(const ::ovald & oval);
      virtual ::e_status _add_shape(const ::polygond & polygon);

      

      
      //virtual ::e_status IntersectClipregion(::draw2d::region * pregion);
      //virtual ::e_status IntersectClipRect(double x1, double y1, double x2, double y2);
      //virtual ::e_status IntersectClipRect(const ::rectd & rect);
      //virtual i32 ExcludeClipRect(double x1, double y1, double x2, double y2);
      //virtual i32 ExcludeClipRect(const ::rectd & rect);
      //virtual i32 ExcludeUpdateRgn(::user::interaction_impl * pwindow);
      //virtual i32 OffsetClipregion(double x, double y);
      //virtual i32 OffsetClipregion(const ::sized & ::sized);
      //virtual i32 SelectClipregion(::draw2d::region* pregion, ::draw2d::enum_combine ecombine);

      virtual void on_apply_clip_region();

      virtual ::pointd current_position();

      //inline bool move_to(double x, double y)
      //{

      //   return move_to({ x, y });

      //}


      virtual bool move_to(double x, double y);
      virtual bool line_to(double x, double y);
      virtual bool draw_line(double x1, double y1, double x2, double y2);
      virtual bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen);

      
      inline bool move_to(const ::pointd & point) 
      { 
      
         return move_to(point.x, point.y); 
      
      }


      virtual bool line_to(const ::pointd & point) 
      { 
         
         return line_to(point.x, point.y); 

      }

      
      inline bool draw_line(const ::pointd & point1, const ::pointd & point2) 
      { 

         return draw_line(point1.x, point1.y, point2.x, point2.y);

      }


      inline bool draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen)
      {

         return draw_line(point1.x, point1.y, point2.x, point2.y, ppen);

      }


      virtual bool draw_error_line(double x1, double h, double x2, ::i32 iStyle);







      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual bool Arc(const ::rectd & rect, const ::pointd & pointStart, const ::pointd & pointEnd);
      virtual bool Arc(double x1, double y1, double x2, double y2, angle start, angle extends);
      virtual bool Arc(const ::rectd & rect, angle start, angle extends);
      
      
      virtual bool polyline(const ::pointd * ppoints,count nCount);


//      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
//      virtual bool Arc(const rectd & rectd, const ::pointd & pointStart, const ::pointd & pointEnd);

//      virtual bool Arc(double x1, double y1, double x2, double y2, angle start, angle extends);
//      virtual bool Arc(const rectd & rectd, angle start, angle extends);


      virtual bool AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle);
      virtual bool ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual bool ArcTo(const ::rectd & rect,const ::pointd & pointStart,const ::pointd & pointEnd);
      //virtual i32 GetArcDirectdion();
      //virtual i32 SetArcDirectdion(i32 nArcDirectdion);

      virtual bool polydraw(const ::pointd * ppoints, const byte* pTypes,count nCount);

      virtual bool polyline_to(const ::pointd * ppoints, ::count nCount);
      virtual bool poly_polyline(const ::pointd * ppoints, const int * pPolyPoints, ::count nCount);


      virtual bool poly_bezier(const ::pointd * ppoints, ::count nCount);
      virtual bool poly_bezier_to(const ::pointd * ppoints, ::count nCount);


      virtual bool frame_rect(const ::rectd & rect, ::draw2d::brush* pbrush);
      virtual bool invert_rect(const ::rectd & rect);
      
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, ::draw2d::bitmap* pBitmap, ::u32 nFlags,::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, HICON hIcon, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, const char * pszText, ::u32 nFlags,

  //                           bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, const char * pszText, ::u32 nFlags,
//
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS_DESKTOP
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, DRAWSTATEPROC pDrawProc,
//
//                             LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual bool DrawState(const ::pointd & point, const ::sized & ::sized, DRAWSTATEPROC pDrawProc,
//
//                             LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
      // Ellipse and Polygon Functions
      virtual bool Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                         double x4, double y4);
      virtual bool Chord(const ::rectd & rect, const ::pointd & pointStart, const ::pointd & pointEnd);

      virtual void DrawFocusRect(const ::rectd & rect);

    /*  virtual bool ellipse(double x1, double y1, double x2, double y2);
      virtual bool ellipse(const ::rectd & rectd);

      virtual bool draw_ellipse(double x1, double y1, double x2, double y2);
      virtual bool draw_ellipse(const ::rectd & rectd);

      virtual bool fill_ellipse(double x1, double y1, double x2, double y2);
      virtual bool fill_ellipse(const ::rectd & rectd);*/



      virtual bool ellipse(double x1,double y1,double x2,double y2);
      virtual bool ellipse(const rectd & prectd);

      virtual bool draw_ellipse(double x1,double y1,double x2,double y2);
      virtual bool draw_ellipse(const rectd & prectd);

      virtual bool fill_ellipse(double x1,double y1,double x2,double y2);
      virtual bool fill_ellipse(const rectd & prectd);


      virtual bool Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual bool Pie(const ::rectd & rect, const ::pointd & pointStart, const ::pointd & pointEnd);


      //virtual bool polygon(const ::pointd * ppoints, count nCount);
      virtual bool polygon(const POINTD * ppoints, count nCount);
      //virtual bool draw_polygon(const ::pointd * ppoints, count nCount);
      virtual bool draw_polygon(const POINTD * ppoints, count nCount);
      //virtual bool fill_polygon(const ::pointd * ppoints,count nCount);
      virtual bool fill_polygon(const POINTD * ppoints,count nCount);

      //virtual bool poly_polygon(const ::pointd * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);
      //virtual bool draw_poly_polygon(const ::pointd * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool draw_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);
      //virtual bool fill_poly_polygon(const ::pointd * ppoints, const i32 * pPolyCounts, count nCount);
      virtual bool fill_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount);


      virtual bool rectangle(const ::rectd & rect);

      virtual bool draw_rect(const ::rectd & rect);
      virtual bool draw_rect(const ::rectd & rect, ::draw2d::pen * ppen);

      virtual bool fill_rect(const ::rectd & rect);
      virtual bool fill_rect(const ::rectd & rect, ::draw2d::brush * pbrush);
      virtual bool fill_rect(const ::rectd & rect, const ::color & color);

      //virtual bool rectangle(const rectd & rectd);
      //virtual bool draw_rect(const rectd & rectd);
      //virtual bool draw_rect(const rectd & rectd, ::draw2d::pen * ppen);
      //virtual bool fill_rect(const rectd & rectd);
      //virtual bool fill_rect(const rectd & rectd, ::draw2d::brush * pbrush);

      //virtual bool round_rectd(const ::rectd & rect, const ::pointd & point);

      virtual bool round_rect(const ::rectd & rectd, double dRadius);


      //virtual bool from(const ::pointd & pointDst, const ::sized & ::sized, ::draw2d::graphics * pgraphicsSrc, const ::pointd & pointSrc);
      //virtual bool from(const ::sized & ::sized, ::draw2d::graphics * pgraphicsSrc, const ::pointd & pSrc);
      //virtual bool from(const ::sized & ::sized, ::draw2d::graphics * pgraphicsSrc);
      //virtual bool PatBlt(double x, double y, i32 nWidth, i32 nHeight);



      //virtual bool draw_image(const ::rectd & rect, ::draw2d::graphics * pgraphicsSrc, const ::pointd & point);

      //virtual bool draw_image(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rect);
      //virtual bool draw_image(const ::rectd & rectdDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rect);
      //virtual bool draw_image(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc);
      // virtual bool draw_image(const ::rectd & rectddDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc);


      // bit block transfer (pixel-to-pixel)
      //virtual bool draw_at(const ::pointd & pointDst, ::image * pimage);
      //virtual bool draw_at(const ::pointd & pointDst, ::image_frame * pframe);
      //virtual bool draw_at(const ::pointd & pointDst, ::draw2d::graphics * pgraphicsSrc);


      virtual bool _draw_blend(const ::image_drawing & imagedrawing) override;

      
      //virtual bool _draw(const ::rectd & rectDst, const image_drawing & imagedrawing, const ::rectd & rectSrc) override;
      //virtual bool _draw_raw(const ::rectd & rectDst, const image_drawing & imagedrawing, const ::rectd & rectSrc) override;
      //virtual bool _draw_blend(const ::rectd & rectDst, const image_drawing & imagedrawing, const ::rectd & rectSrc) override;

      //
      //virtual bool _draw_raw(const ::rectd & rectDst, const image_drawing & imagedrawing, const ::pointd & pointSrc) override;
      //virtual bool _stretch_raw(const ::rectd & rectDst, const image_drawing & imagedrawing, const ::rectd & rectSrc) override;




      // potentially stretching
      //virtual bool stretch(const ::rectd & rectDst, ::image * pimage, const ::rectd & rectSrc = ::rectd());
      //virtual bool stretch(const ::rectd & rectDst, ::image_frame * pframe, const ::rectd & rectSrc = ::rectd());
      //virtual bool stretch(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc = ::rectd());
      //virtual bool stretch_raw(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc = ::rectd());
      //virtual bool stretch_blend(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc = ::rectd());


      //template < primitive_size SIZE >
      //inline bool alpha_blend(const SIZE & sizeDst, const ::image_drawing & imagedrawing, double dOpacity)
      //{

      //   auto finalSrcSize = pimagesource->size(sizeDst, sizeSrc, eimageselection);

      //   auto pimage = pimagesource->get_image(sizeSrc);

      //   return _alpha_blend(::rectd(sizeDst), pgraphicssource, ::rectd(sizeDst), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE >
      //inline bool alpha_blend(const RECTANGLE & rectDst, const ::image_drawing & imagedrawing, double dOpacity)
      //{

      //   return _alpha_blend(rectDst, pgraphicssource, ::rectd(rectDst.size()), dOpacity);

      //}

      //
      //template < primitive_rectangle RECTANGLE, primitive_point POINT >
      //inline bool alpha_blend(const RECTANGLE & rectDst, const ::image_drawing & imagedrawing, const POINT & pointSrc, double dOpacity)
      //{

      //   if (::is_null(pgraphicssource))
      //   {

      //      return false;

      //   }

      //   auto sizeDst = rectDst.size() - pointSrc;

      //   return _alpha_blend(rectd(rectDst.top_left(), sizeDst), pgraphicssource, ::rectd(pointSrc, pgraphicssource->size(sizeDst) - pointSrc), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE_DST, primitive_rectangle RECTANGLE_SRC >
      //inline bool alpha_blend(const RECTANGLE_DST & rectDst, const ::image_drawing & imagedrawing, const RECTANGLE_SRC & rectSrc, double dOpacity)
      //{

      //   return _alpha_blend(rectDst, pgraphicssource, rectSrc, dOpacity);

      //}


      //virtual bool _alpha_blend(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc, double dOpacity);
      //virtual bool _alpha_blend_raw(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc, double dRate);
      //virtual bool _alpha_blend_blend(const ::rectd & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectd & rectSrc, double dRate);


      //virtual bool draw(const ::rectd & point, cursor * pcursor);
      //virtual bool draw(const ::rectd & rectDst, icon * picon);



      virtual ::color GetPixel(double x, double y);
      virtual ::color GetPixel(const ::pointd & point);
      virtual ::color SetPixel(double x, double y, const ::color & color);
      virtual ::color SetPixel(const ::pointd & point, const ::color & color);
      virtual ::color blend_pixel(const ::pointd & point, const ::color & color);
//      virtual bool FloodFill(double x, double y, const ::color & color);
//      virtual bool ExtFloodFill(double x, double y, const ::color & color, ::u32 nFillType);
//      virtual bool MaskBlt(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                           double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                           u32 dwRop);
//      virtual bool PlgBlt(::pointd * pPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//
//                          i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask);
      virtual bool SetPixelV(double x, double y, const ::color & color);
      virtual bool SetPixelV(const ::pointd & point, const ::color & color);
      //virtual bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
      //void * pMesh, WINULONG nMeshElements, u32 dwMode);
//      virtual bool TransparentBlt(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
//                                  ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                                  ::u32 clrTransparent);



      // Text Functions
      //virtual bool text_out(double x, double y, const char * pszString, strsize nCount);

      inline bool text_out(const ::pointd & point, const block & block)
      {

         return text_out(point.x, point.y, block);

      }

      virtual bool text_out(double x, double y, const block & str);
      virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectd & rect, const char * pszString, strsize nCount, i32 * lpDxWidths);

      virtual bool ExtTextOut(double x, double y, ::u32 nOptions, const ::rectd & rect, const string & str, i32 * lpDxWidths);

      virtual ::sized TabbedTextOut(double x, double y, const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions, i32 nTabOrigin);

      virtual ::sized TabbedTextOut(double x, double y, const string & str, count nTabPositions, i32 * pnTabStopPositions, i32 nTabOrigin);



      virtual bool TextOutRaw(double x, double y, const block & block);

      virtual bool TextOutAlphaBlend(double x, double y, const block & block);


      virtual bool _001DrawText(const string & str, rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false);


      virtual bool draw_text(const string & str, const ::rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //virtual bool draw_text(const string & str, const rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);


#ifndef _UWP

//      virtual bool draw_text_ex(const string & str,const ::rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

//      virtual bool draw_text_ex(const string & str,const rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual bool draw_text_ex(const string & str,const ::rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //virtual bool draw_text_ex(const string & str,const rectd & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#endif


      virtual ::count get_character_extent(double_array & daLeft, double_array & daRight, const string & str, strsize iStart = 0, strsize iCount = -1);

      virtual ::sized GetTextExtent(const char * pszString, strsize nCount, strsize iIndex);

      virtual ::sized GetTextBegin(const char * pszString, strsize nCount, strsize iIndex);

      virtual ::sized GetTextExtent(const char * pszString, strsize nCount);

      virtual ::sized GetTextExtent(const string & str);
      virtual bool GetTextExtent(::sized & size, const char * pszString, strsize nCount, strsize iIndex);

      virtual bool GetTextExtent(::sized & size, const char * pszString, strsize nCount);

      virtual bool GetTextExtent(::sized & size, const string & str);
      virtual ::sized GetOutputTextExtent(const char * pszString, strsize nCount);

      virtual ::sized GetOutputTextExtent(const string & str);
      virtual ::sized GetTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions);

      virtual ::sized GetTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions);

      virtual ::sized GetOutputTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * lpnTabStopPositions);

      virtual ::sized GetOutputTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions);

      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, double x, double y, i32 nWidth, i32 nHeight);

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

//       virtual bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, i32 * pnFit, i32 * alpDx, __out_opt ::sized * ::sized *);

//       virtual bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt ::sized * pSize);


// #endif

//
//
//  /*    // Advanced Drawing
//      virtual bool DrawEdge(const ::rectd & prectd,::u32 nEdge,::u32 nFlags);
//
//      virtual bool DrawFrameControl(const ::rectd & prectd,::u32 nType,::u32 nState);
//*/

      //// Scolorolling Functions
      //virtual bool ScrollDC(i32 dx, i32 dy, const ::rectd &  pRectScoloroll, const ::rectd &  lpRectClip,

      //                      ::draw2d::region* pregionUpdate, ::rectd * pRectUpdate);


      // font Functions
//      virtual bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual u32 SetMapperFlags(u32 dwFlag);
//      virtual ::sized GetAspectRatioFilter();

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
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectd &  pBounds);

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
      virtual i32 GetPath(::pointd * ppoint, byte * pTypes, count nCount);

      virtual bool SelectClipPath(i32 nMode);

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      virtual bool draw_path(::draw2d::path * ppath);
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      virtual bool fill_path(::draw2d::path * ppath);
      virtual bool path(::draw2d::path * ppath);

      // Misc helper Functions
      virtual ::draw2d::brush * GetHalftoneBrush();
      //virtual void DrawDragRect(const ::rectd & rect, const ::sized & ::sized,

      //                          const ::rectd &  pRectLast, const ::sized & sizeLast,

      //                          ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);

      //virtual void fill_rect(const ::rectd & rect, const ::color & color);
      //virtual void fill_rect(const rectd & rectd, const ::color & color);

      virtual bool draw_3drect(const ::rectd & rect, const ::color& colorTopLeft, const ::color& colorBottomRight, const ::e_border & eborder = e_border_all);
      //virtual void draw_3drect(const rectd & rectd, const ::color& colorTopLeft, const ::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      virtual bool draw_rect(const ::rectd & rect, const ::color& color, const ::e_border & eborder = e_border_all);
      //virtual void draw_rect(const rectd & rectd, const ::color& color, const ::e_border & eborder = e_border_all);

      virtual bool set_font(::user::interaction* pinteraction, ::user::enum_element eelement = ::user::e_element_none, ::user::enum_state estate = ::user::e_state_none);


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
      // draw_round_rectd()
      //
      // Purpose:     Draws a rounded rectdangle with a solid pen
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rectd        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //          width    - [in]  width of the border
      //
      // Returns:     None
      //
      bool draw_round_rect(const ::rectd & rect, ::draw2d::pen * ppen, double radius, const ::e_border & eborder = e_border_all);
      //bool draw_round_rect(const ::rectd & rect, ::draw2d::pen * ppen, const ::pointd & point, const ::e_border & eborder = e_border_all);
      //bool draw_round_top_left(const ::rectd & rect, ::draw2d::pen * ppen, i32 radius, const ::e_border & eborder = e_border_all);
      //bool draw_round_bottom_right(const ::rectd & rect, ::draw2d::pen * ppen, i32 radius, const ::e_border & eborder = e_border_all);

      //bool draw_round_rect(const ::rectd & rect, const ::color & color, double radius, double width, const ::e_border & eborder = e_border_all);
      //bool draw_round_top_left(const ::rectd & rect, const ::color & color, i32 radius, i32 width, const ::e_border & eborder = e_border_all);
      //bool draw_round_bottom_right(const ::rectd & rect, const ::color & color, i32 radius, i32 width, const ::e_border & eborder = e_border_all);


      bool draw_stock_icon(const ::rectd & rectd, e_stock_icon eicon);


      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rectd        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const ::rectd & rect, const ::color & color, double radius);

      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          pBrush      - [in]  pointer to a Brush
      //          rectd        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the border (needed in case the
      //                         brush is a type other than solid)
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      bool fill_round_rect(const ::rectd & rect, ::draw2d::brush * pbrush, double radius);


      //bool fill_round_rect(const ::rectd & rect, ::draw2d::brush * pbrush, const ::pointd & point);


      //virtual bool round_rect(const ::rectd & rect, double radius);

      virtual i32 _DrawText(const string & str, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, ::draw2d::font * pfontUnderline = nullptr);

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

      //virtual bool move_to(double x, double y); // { return move_to(::::pointd(x, y)); }
      //inline bool move_to(double x, double y) { return move_to(::pointd(x, y)); }

      //inline bool line_to(double x, double y) { return line_to(::::pointd(x, y)); }
      //inline bool line_to(double x, double y) { return line_to(::pointd(x, y)); }
      //virtual bool line_to(double x, double y);// { return line_to(::pointd(x, y)); }

      //inline bool draw_line(double x1, double y1, double x2, double y2) { return draw_line(::pointd(x1,y1), ::pointd(x2, y2)); }
      //inline bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::pointd(x1, y1), ::pointd(x2, y2), ppen); }

      ///virtual bool draw_line(double x1, double y1, double x2, double y2); // { return draw_line(::pointd(x1, y1), ::pointd(x2, y2)); }
      //virtual bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_line(::pointd(x1, y1), ::pointd(x2, y2), ppen); }

      //inline bool draw_line(double x1, double y1, double x2, double y2) { return draw_line(::pointd(x1, y1), ::pointd(x2, y2)); }
      //inline bool draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::pointd(x1, y1), ::pointd(x2, y2), ppen); }

      //inline bool rectdangle_coord(double x1, double y1, double x2, double y2) { return rectdangle(::rectd(x1, y1, x2, y2)); }
      //inline bool rectdangle_coord(double x1, double y1, double x2, double y2); // { return rectdangle(rectd(x1, y1, x2, y2)); }

      //inline bool rectdangle_dim(double x, double y, i32 cx, i32 cy) { return rectdangle(rectd_dim(x, y, cx, cy)); }
      //inline bool rectdangle_dim(double x, double y, double cx, double cy); // { return rectdangle(rectdd_dim(x, y, cx, cy)); }

      //inline bool draw_rect_coord(double x1, double y1, double x2, double y2) { return draw_rect(::rectd(x1, y1, x2, y2)); }
      //inline bool draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_rect(::rectd(x1, y1, x2, y2), ppen); }
      //inline bool draw_rect_coord(double x1, double y1, double x2, double y2); // { return draw_rect(rectd(x1, y1, x2, y2)); }
      //inline bool draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_rect(rectd(x1, y1, x2, y2), ppen); }

      //inline bool draw_rect_dim(double x, double y, i32 cx, i32 cy) { return draw_rect(rectd_dim(x, y, cx, cy)); }
      //inline bool draw_rect_dim(double x, double y, i32 cx, i32 cy, ::draw2d::pen * ppen) { return draw_rect(rectd_dim(x, y, cx, cy), ppen); }
      //inline bool draw_rect_dim(double x, double y, double cx, double cy); // { return draw_rect(rectdd_dim(x, y, cx, cy)); }
      //inline bool draw_rect_dim(double x, double y, double cx, double cy, ::draw2d::pen * ppen); // { return draw_rect(rectdd_dim(x, y, cx, cy), ppen); }

      //inline bool fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rect(::rectd(x1, y1, x2, y2)); }
      //inline bool fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rect(::rectd(x1, y1, x2, y2), pbrush); }
      //inline bool fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rect(rectd(x1, y1, x2, y2)); }
      //inline bool fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rect(rectd(x1, y1, x2, y2), pbrush); }

      //inline bool fill_rect_dim(double x, double y, i32 cx, i32 cy) { return fill_rect(rectd_dim(x, y, cx, cy)); }
      //inline bool fill_rect_dim(double x, double y, i32 cx, i32 cy, ::draw2d::brush * pbrush) { return fill_rect(rectd_dim(x, y, cx, cy), pbrush); }
      //inline bool fill_rect_dim(double x, double y, double cx, double cy); // { return fill_rect(rectdd_dim(x, y, cx, cy)); }
      //inline bool fill_rect_dim(double x, double y, double cx, double cy, ::draw2d::brush * pbrush); // { return fill_rect(rectdd_dim(x, y, cx, cy), pbrush); }

      //inline bool polygon(point_array & pointa) { return polygon(pointa.get_data(), pointa.get_count()); }
      inline bool polygon(pointd_array & pointa) { return polygon(pointa.get_data(), pointa.get_count()); }
      //inline bool draw_polygon(point_array & pointa) { return draw_polygon(pointa.get_data(), pointa.get_count()); }
      inline bool draw_polygon(pointd_array & pointa) { return draw_polygon(pointa.get_data(), pointa.get_count()); }
      //inline bool fill_polygon(point_array & pointa) { return fill_polygon(pointa.get_data(), pointa.get_count()); }
      inline bool fill_polygon(pointd_array & pointa) { return fill_polygon(pointa.get_data(), pointa.get_count()); }

      //inline void fill_solid_rect_dim(double x, double y, i32 cx, i32 cy, const ::color & color) { return fill_rect(rectd_dim(x, y, cx, cy), color); }
      //inline void fill_solid_rect_dim(double x, double y, double cx, double cy, const ::color & color); // { return fill_rect(rectdd_dim(x, y, cx, cy), color); }

      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color & color) { return fill_rect(::rectd(x1, y1, x2, y2), color); }
      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color & color) { return fill_rect(rectd(x1, y1, x2, y2), color); }

      //inline void draw_3drect_dim(double x, double y, i32 cx, i32 cy, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rectd_dim(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_dim(double x, double y, double cx, double cy, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rectd_dim(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_dim(double x, double y, i32 cx, i32 cy, const ::color& color) { return draw_rect(rectd_dim(x, y, cx, cy), color); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy, const ::color& color) { return draw_rect(rectd_dim(x, y, cx, cy), color); }

      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(::rectd(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color& colorTopLeft, const ::color& colorBottomLeft) { return draw_3drect(rectd(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color& color) { return draw_rect(::rectd(x1, y1, x2, y2), color); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color& color) { return draw_rect(rectd(x1, y1, x2, y2), color); }


      
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


CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::sized & size);
CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::pointd & point);



CLASS_DECL_AURA PFN_factory_exchange get_draw2d_factory_exchange();

CLASS_DECL_AURA void set_draw2d_factory_exchange(PFN_factory_exchange pfnfactoryDraw2d);

