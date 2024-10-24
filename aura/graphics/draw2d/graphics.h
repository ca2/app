#pragma once


#include "acme/constant/element.h"


#include "aura/platform/draw_context2.h"


#include "aura/graphics/write_text/drawer.h"
#include "aura/graphics/image/drawer.h"
#include "aura/graphics/image/source.h"
//#include "acme/prototype/geometry2d/collection.h"
#include "acme/prototype/geometry2d/angle.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "acme/prototype/geometry2d/shift.h"
#include "aura/user/user/redraw.h"
#include "region.h"
#include "bitmap.h"


//#include "acme/prototype/geometry2d/_geometry2d.h"


//#include "acme/prototype/geometry2d/ellipse.h"


using hdc = void *;


struct NSVGimage;


template < typename HOLDEE >
class shape_array;


namespace draw2d
{


   class clip;
   class clip_group;
   class clip_item;
   class graphics;
   class palette;
   class host;

   //template < typename GRAPHICS_SOURCE_POINTER >
   //concept graphics_source_pointer = requires(const ::image::image_drawing & imagedrawing, const ::size_f64 & sizeHint)
   //{

   //   { pgraphicssource->g(sizeHint) } -> ::std::convertible_to < ::draw2d::graphics * >;
   //   { pgraphicssource->origin() } -> ::std::convertible_to < ::size_f64 >;
   //   { pgraphicssource->size_i32(sizeHint) } -> ::std::convertible_to < ::size_f64 >;

   //};

/// <summary>
/// graphics * -> ::image::image_source_pointer concept
/// </summary>
   class CLASS_DECL_AURA graphics :
      virtual public ::aura::simple_chain < ::aura::draw_context >,
      virtual public ::image::image_drawer,
      virtual public ::write_text::drawer,
      virtual public ::image::image_source_interface
   {
   public:


      e_graphics                             m_egraphics;
      bool                                   m_bBeginDraw;
      bool                                   m_bInheritDraw;
      bool                                   m_bOutline;
      void *                                 m_pthis;
      ::user::interaction *                  m_puserinteraction;
      ::pointer<::draw2d::host>              m_pdraw2dhost;

      bool                                   m_bPat;

      //bool                                   m_bAlphaBlend;

      ::pointer<::text::context>          m_ptextcontext;
      ::aura::draw_context *                 m_pdrawcontext;
      ::image::image_pointer                        m_pimageAlphaBlend;
      ::point_f64                            m_pointAlphaBlend;
      ::pointer<::task>                     m_ptask;
      bool                                   m_bDraw;

      ::image::image *                      m_pimage = nullptr;
      ::draw2d::bitmap_pointer               m_pbitmap;
      ::draw2d::pen_pointer                  m_ppen;
      ::draw2d::brush_pointer                m_pbrush;
      ::draw2d::region_pointer               m_pregion;
      bool                                   m_bStoreThumbnails;

      ::point_f64                            m_point;

   protected:
      enum_alpha_mode                        m_ealphamode;


   public:
      enum_fill_mode                         m_efillmode;
      enum_smooth_mode                          m_esmoothmode;
      enum_interpolation_mode                m_einterpolationmode;
      enum_compositing_quality                  m_ecompositingquality;
      ::write_text::enum_rendering           m_ewritetextrendering;
      double                                 m_dFontFactor;

      ::size_f64                             m_sizeScaling;
      ::point_f64                            m_pointOrigin;
      ::geometry2d::matrix                   m_matrix;

      ::rectangle_f64                        m_rectangleDraw;

      bool                                   m_bPrinting;
      void *                                 m_osdata[8];
      ::user::style_pointer                  m_puserstyle;
      //::point_f64                            m_pointAddShapeTranslate;
      bool                                   m_bUseImageMipMapsOrResizedImages;

      //::e_status                             m_estatus;
      //::e_status                             m_estatusLast;

      ::pointer < ::graphics::graphics >     m_pgraphicsgraphics;
      ::pointer < ::graphics::buffer_item >  m_pgraphicsbufferitem;

      ::pointer < ::user::redraw >           m_puserredraw;

      graphics();
      ~graphics() override;


      void on_initialize_particle() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      
      
      void destroy() override;
      void destroy_os_data() override;
      
      virtual void do_on_context(const ::procedure & procedure);

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

      using image_drawer::draw;
      using write_text::drawer::draw;

      virtual ::file::path get_font_path(const ::string & strName, int iWeight, bool bItalic);

      //virtual oswindow get_window_handle() const;
      
      
      
      inline ::draw2d::graphics * g(const ::size_f64 & sizeHint) { return this; }
      inline ::size_f64 origin() const { return ::size_f64(); }

      bool _is_ok() const override;

      ::image::image_pointer image_source_image(const ::size_i32 & sizeDst) override;

      ::size_i32 image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const override;

      ::size_i32 image_source_size() const override;


      ::user::redraw * user_redraw();
      //#ifdef UNIVERSAL_WINDOWS
      //
      //
      //      virtual void set_directd2d_plugin(::draw2d_directd2d::plugin * pplugin);
      //
      //
      //#endif


      virtual void on_begin_draw();

      virtual bool fill_contains(const point_f64 & point);

      void draw_ca2(int x,int y,int z,const ::color::color & colorBk,const ::color::color & color);
      void draw_ca2_with_border(int x,int y,int z,int b,const ::color::color & colorBk,const ::color::color & color,const ::color::color & colorOut);
      void draw_ca2_border2(int x,int y,int z,int bOut,int bIn,const ::color::color & colorBk,const ::color::color & color,const ::color::color & colorBorderOut,const ::color::color & colorIn);
      void draw_ca2_with_border2(int x,int y,int z,int bOut,int bIn,const ::color::color & colorBk,const ::color::color & color,const ::color::color & colorBorderOut,const ::color::color & colorIn);


      void draw_border(const ::rectangle_f64 & rectangle, const ::color::color & color, int iWidth);
      void draw_rect_side(const ::rectangle_f64& rectangle_f64, enum_border eborder);

      virtual bool is_set();


      virtual void thread_select();


      virtual void clear_current_point();


      virtual void attach(void * pdata);
      virtual void * detach();

#ifdef WINDOWS_DESKTOP

      virtual void attach_hdc(hdc hdc);
      virtual hdc detach_hdc();
      virtual void AttachPrinter(hdc hdc);
      virtual hdc DetachPrinter();

#endif


      virtual void prefer_mapped_image_on_mix();

      virtual ::text::context * textcontext();
      virtual ::aura::draw_context * draw_context();

      virtual void set_alpha_mode(enum_alpha_mode ealphamode);
      inline enum_alpha_mode alpha_mode() const { return m_ealphamode; }

      virtual void set_smooth_mode(enum_smooth_mode esmoothmode);

      virtual void set_interpolation_mode(enum_interpolation_mode einterpolationmode);

      virtual void set_compositing_quality(enum_compositing_quality ecompositingquality);

      virtual void set_text_rendering_hint(::write_text::enum_rendering erendering);

      virtual enum_smooth_mode get_smooth_mode();

      virtual void blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle);

      virtual void set_solid_pen(double dWidth, const ::color::color & color);

      //virtual void IsPrinting();            // true if being used for printing

      virtual ::draw2d::pen *      get_current_pen();
      virtual ::draw2d::brush *    get_current_brush();
      virtual ::draw2d::palette *  get_current_palette();
      virtual ::draw2d::bitmap *   get_current_bitmap();






      // for bidi and mirrored localization
      virtual u32 GetLayout();
      virtual u32 SetLayout(u32 dwLayout);

      // Constructors
      virtual void create_device_context(const ::string & pszDriverName, const ::string & pszDeviceName, const ::string & pszOutput, const void * lpInitData);

      virtual void create_information_context(const ::string & pszDriverName, const ::string & pszDeviceName, const ::string & pszOutput, const void * lpInitData);

      virtual void create_memory_graphics(const ::size_i32 & size = {});
      virtual void CreateCompatibleDC(::draw2d::graphics * pgraphics);
      virtual void CreateWindowDC(oswindow wnd);

      virtual void on_begin_draw(oswindow wnd, const ::size_f64 & sz);
      virtual void on_end_draw(oswindow wnd);

      virtual void DeleteDC();


      // Device-Context Functions
      virtual i32 GetDeviceCaps(i32 nIndex);
      virtual ::u32 SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::rectangle_f64 * rectdBounds, ::u32 flags);


      virtual void resize(const ::size_i32 & sizeWindow);


      
//#ifdef WINDOWS
//      virtual void ResetDC(const DEVMODE* pDevMode);
//
//#endif

      // Drawing-Tool Functions
      virtual ::point_f64 GetBrushOrg();
      virtual ::point_f64 SetBrushOrg(double x, double y);
      virtual ::point_f64 SetBrushOrg(const ::point_f64 & point);
      //virtual i32 EnumObjects(i32 nObjectType,
                              //i32 (CALLBACK* pfn)(LPVOID, lparam), lparam lpData);



      virtual void set_text_color(::color::color color);


      using ::write_text::drawer::set;
      virtual void set(::draw2d::region* pregion);
      virtual void set(::draw2d::pen* ppen);
      virtual void set(::draw2d::brush* pbrush);
      virtual void set(::draw2d::bitmap* pbitmap);
      virtual ::draw2d::object* set_stock_object(i32 nIndex);


      // color and color Palette Functions
      //virtual ::color::color GetNearestColor(const ::color::color & color);
      //virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, void bForceBackground);
      //virtual ::u32 RealizePalette();
      //virtual void UpdateColors();

      // Drawing-Attribute Functions
      //virtual i32 GetPolyFillMode();
      //virtual i32 GetROP2();
      //virtual i32 GetStretchBltMode();


      virtual double get_dpix();
      virtual double get_dpiy();

      //virtual i32 SetPolyFillMode(i32 nPolyFillMode);
      //virtual i32 SetROP2(i32 nDrawMode);
//      virtual void set_interpolation_mode(enum_interpolation_mode einterpolationmode);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual void flush();
      virtual void sync_flush();


      virtual ::size_f64 get_size() const;

      ::size_i32 get_image_drawer_size() const override;







//#ifdef WINDOWS_DESKTOP
//      virtual void GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust);
//
//      virtual void SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust);
//
//#endif

//#if (_WIN32_WINNT >= 0x0500)
//
//      virtual ::color::color GetDCBrushColor();
//      virtual ::color::color SetDCBrushColor(const ::color::color & color);
//
//      virtual ::color::color GetDCPenColor();
//      virtual ::color::color SetDCPenColor(const ::color::color & color);
//
//#endif

      // Graphics mode
      //virtual i32 SetGraphicsMode(i32 iMode);
      //virtual i32 GetGraphicsMode();

//      // World transform
//#ifdef WINDOWS
//      virtual void SetWorldTransform(const XFORM* pXform);
//      virtual void ModifyWorldTransform(const XFORM* pXform,u32 iMode);
//      virtual void GetWorldTransform(XFORM* pXform);
//#endif

      virtual ::size_f64 get_scaling();

      // Mapping Functions
      ///virtual i32 GetMapMode();
      virtual ::point_f64 get_origin();
      //virtual i32 SetMapMode(i32 nMapMode);
      // Context Origin
      virtual ::point_f64 set_origin(double x, double y);
      virtual ::point_f64 set_origin(const ::point_f64 & point_f64);
      virtual ::point_f64 offset_origin(double x, double y);

      // Context Extent
      virtual ::size_f64 get_extents();
      virtual ::size_f64 set_extents(double cx, double cy);
      virtual ::size_f64 set_extents(const ::size_f64 & size);
      virtual ::size_f64 scale_extents(double xNum, double xDenom, double yNum, double yDenom);

      // Window Origin
      virtual ::point_f64 GetWindowOrg();
      virtual ::point_f64 SetWindowOrg(double x, double y);
      virtual ::point_f64 SetWindowOrg(const ::point_f64 & point);
      virtual ::point_f64 offset_window_org(double nWidth, double nHeight);

      // Window extent
      virtual ::size_f64 GetWindowExt();
      virtual ::size_f64 set_window_ext(double cx, double cy);
      virtual ::size_f64 set_window_ext(const ::size_f64 & size);
      virtual ::size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom);

      // Coordinate Functions
      virtual void DPtoLP(::point_f64 * ppoint, ::collection::count nCount = 1);
      virtual void DPtoLP(::rectangle_f64 * prectd);

      virtual void DPtoLP(::size_f64 * pSize);

      virtual void LPtoDP(::point_f64 * ppoint, ::collection::count nCount = 1);
      virtual void LPtoDP(::rectangle_f64 * prectd);

      virtual void LPtoDP(::size_f64 * pSize);


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(::size_f64 * pSize);

      virtual void LPtoHIMETRIC(::size_f64 * pSize);

      virtual void HIMETRICtoDP(::size_f64 * pSize);

      virtual void HIMETRICtoLP(::size_f64 * pSize);


      // Region Functions
      virtual void fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush);
      virtual void frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight);
      virtual void invert_region(::draw2d::region* pregion);
      virtual void paint_region(::draw2d::region* pregion);

      // Clipping Functions
      virtual i32 get_clip_box(::rectangle_f64 & rectangle);

      //virtual i32 get_clip_box(::rectangle_f64 * prectangle);

      //virtual void PtVisible(double x, double y);
      //virtual void PtVisible(const ::point_f64 & point);
      //virtual void RectVisible(const ::rectangle_f64 & rectangle);
      

      
      //virtual void add_clipping_shapes(const pointer_array < ::draw2d::region > & regiona);
      virtual void reset_clip();
      
      
      //virtual void set_clipping(::draw2d::region * pregion);
      
      virtual void intersect_clip(const ::rectangle_f64 & rectangle_f64);
      virtual void intersect_clip(const ::ellipse_f64 & ellipse);
      virtual void intersect_clip(const ::polygon_f64 & polygon);
      

      virtual ::draw2d::region * defer_get_os_data(::pointer < ::geometry2d::region > & pregion);


      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual void _clip(bool bAdd);
      virtual void _intersect_clip();
      virtual void _eo_clip();
      //virtual void _add_clipping_shape(___shape<::draw2d::region> & shape);

      virtual void intersect_clip(const clip & clip);
      virtual void intersect_clip(const clip_group & clipgroup);
      virtual void _add_clip_item(clip_item * pclipitem);
    
      /// If it is "simple" shape (not combine_item) it
      /// calls add_shape on the item and returns true.
      /// Otherwise (if it is "complex" shape, a combine_item)
      /// it returns false.
      virtual bool _add_simple_shape(::geometry2d::item * pitem);
      virtual void _add_shape(const ::rectangle_f64 & rectangle);
      virtual void _add_shape(const ::ellipse_f64 & ellipse);
      virtual void _add_shape(const ::polygon_f64 & polygon);

      //virtual void IntersectClipregion(::draw2d::region * pregion);
      //virtual void IntersectClipRect(double x1, double y1, double x2, double y2);
      //virtual void IntersectClipRect(const ::rectangle_f64 & rectangle);
      //virtual i32 ExcludeClipRect(double x1, double y1, double x2, double y2);
      //virtual i32 ExcludeClipRect(const ::rectangle_f64 & rectangle);
      //virtual i32 ExcludeUpdateRgn(::windowing::window * pwindow);
      //virtual i32 OffsetClipregion(double x, double y);
      //virtual i32 OffsetClipregion(const ::size_f64 & ::size_f64);
      //virtual i32 SelectClipregion(::draw2d::region* pregion, ::draw2d::enum_combine ecombine);

      virtual void on_apply_clip_region();

      virtual ::point_f64 current_position();

      //inline void set_current_point(double x, double y)
      //{

      //   return set_current_point({ x, y });

      //}


      virtual void set_current_point(double x, double y);
      virtual void line_to(double x, double y);
      virtual void draw_line(double x1, double y1, double x2, double y2);
      virtual void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen);

      
      inline void set_current_point(const ::point_f64 & point) 
      { 
      
         return set_current_point(point.x(), point.y());
      
      }


      virtual void line_to(const ::point_f64 & point) 
      { 
         
         return line_to(point.x(), point.y()); 

      }

      
      inline void draw_line(const ::point_f64 & point1, const ::point_f64 & point2) 
      { 

         return draw_line(point1.x(), point1.y(), point2.x(), point2.y());

      }


      inline void draw_line(const ::point_f64 & point1, const ::point_f64 & point2, ::draw2d::pen * ppen)
      {

         return draw_line(point1.x(), point1.y(), point2.x(), point2.y(), ppen);

      }


      virtual void draw_error_line(double x1, double h, double x2, ::i32 iStyle);







      virtual void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd);
      virtual void arc(double x1, double y1, double x2, double y2, ::angle_f64 start, ::angle_f64 extends);
      virtual void arc(const ::rectangle_f64 & rectangle, ::angle_f64 start, ::angle_f64 extends);
      
      
      virtual void polyline(const ::point_f64_array & pointa);
      virtual void polyline(const ::point_f64 * ppoints, ::collection::count nCount);


//      virtual void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
//      virtual void arc(const rectangle_f64 & rectangle_f64, const ::point_f64 & pointStart, const ::point_f64 & pointEnd);

//      virtual void arc(double x1, double y1, double x2, double y2, angle start, angle extends);
//      virtual void arc(const rectangle_f64 & rectangle_f64, angle start, angle extends);


      virtual void angle_arc(double x, double y, double nRadius, ::angle_f64 fStartAngle, ::angle_f64 fSweepAngle);
      virtual void arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void arc_to(const ::rectangle_f64 & rectangle,const ::point_f64 & pointStart,const ::point_f64 & pointEnd);
      //virtual i32 GetArcDirectdion();
      //virtual i32 SetArcDirectdion(i32 nArcDirectdion);

      virtual void polydraw(const ::point_f64 * ppoints, const ::u8* pTypes, ::collection::count nCount);

      virtual void polyline_to(const ::point_f64 * ppoints, ::collection::count nCount);
      virtual void poly_polyline(const ::point_f64 * ppoints, const int * pPolyPoints, ::collection::count nCount);


      virtual void poly_bezier(const ::point_f64 * ppoints, ::collection::count nCount);
      virtual void poly_bezier_to(const ::point_f64 * ppoints, ::collection::count nCount);


      virtual void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pbrush);
      virtual void invert_rectangle(const ::rectangle_f64 & rectangle);
      
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, ::draw2d::bitmap* pBitmap, ::u32 nFlags,::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, hicon hIcon, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, hicon hIcon, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, const ::string & pszText, ::u32 nFlags,

  //                           void bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr);
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, const ::string & pszText, ::u32 nFlags,
//
//                             void bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
//#ifdef WINDOWS_DESKTOP
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, DRAWSTATEPROC pDrawProc,
//
//                             lparam lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
//      virtual void DrawState(const ::point_f64 & point, const ::size_f64 & ::size_f64, DRAWSTATEPROC pDrawProc,
//
//                             lparam lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
//#endif
      // Ellipse and Polygon Functions
      virtual void Chord(double x1, double y1, double x2, double y2, double x3, double y3,
                         double x4, double y4);
      virtual void Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd);

      virtual void DrawFocusRect(const ::rectangle_f64 & rectangle);

    /*  virtual void ellipse(double x1, double y1, double x2, double y2);
      virtual void ellipse(const ::rectangle_f64 & rectangle_f64);

      virtual void draw_ellipse(double x1, double y1, double x2, double y2);
      virtual void draw_ellipse(const ::rectangle_f64 & rectangle_f64);

      virtual void fill_ellipse(double x1, double y1, double x2, double y2);
      virtual void fill_ellipse(const ::rectangle_f64 & rectangle_f64);*/





      virtual void ellipse(double x1,double y1,double x2,double y2);
      virtual void ellipse(const rectangle_f64 & prectd);

      virtual void draw_ellipse(double x1,double y1,double x2,double y2);
      virtual void draw_ellipse(const rectangle_f64 & prectd);

      virtual void fill_ellipse(double x1,double y1,double x2,double y2);
      virtual void fill_ellipse(const rectangle_f64 & prectd);


      virtual void Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd);


      //virtual void polygon_i32(const ::point_f64 * ppoints, ::collection::count nCount);
      virtual void polygon(const ::point_f64 * ppoints, ::collection::count nCount);
      //virtual void draw_polygon(const ::point_f64 * ppoints, ::collection::count nCount);
      virtual void draw_polygon(const ::point_f64 * ppoints, ::collection::count nCount);
      //virtual void fill_polygon(const ::point_f64 * ppoints,count nCount);
      virtual void fill_polygon(const ::point_f64 * ppoints, ::collection::count nCount);

      //virtual void poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);
      virtual void poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);
      //virtual void draw_poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);
      virtual void draw_poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);
      //virtual void fill_poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);
      virtual void fill_poly_polygon(const ::point_f64 * ppoints, const i32 * pPolyCounts, ::collection::count nCount);


      virtual void rectangle(const ::rectangle_f64 & rectangle);

      virtual void frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width);

      virtual void draw_rectangle(const ::rectangle_f64 & rectangle);
      virtual void draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen);

      virtual void fill_rectangle(const ::rectangle_f64 & rectangle);
      virtual void fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush);
      virtual void fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color);
      virtual void fill_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color);
      virtual void fill_solid_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color);

      virtual void color_blend_3dRect(const rectangle_i32& rectangleParam, const ::color::color& colorTopLeft, const class ::opacity & opacityTopLeft, const ::color::color& color, const class ::opacity& opacityBottomRight);

      //virtual void color_blend(const ::rectangle_i32& rectangle, const ::color::color& color, const ::opacity & opacity);

//      virtual void color_blend(image_list * pilBlend, image_list * pil, const ::color::color& color32, const ::opacity& opacity);

//      template < ::image::image_source_pointer IMAGE_SOURCE_POINTER >
//      void color_blend(IMAGE_SOURCE_POINTER pimagesource, const ::color::color& color, const ::opacity& opacity)
//      {
//
//         if (!draw(pimagesource))
//         {
//
//            return false;
//
//         }
//
//         if (!color_blend(::rectangle_i32(pimagesource->size()), color, opacity))
//         {
//
//            return false;
//
//         }
//
//         return true;
//
//      }



      //virtual void rectangle_i32(const rectangle_f64 & rectangle_f64);
      //virtual void draw_rectangle(const rectangle_f64 & rectangle_f64);
      //virtual void draw_rectangle(const rectangle_f64 & rectangle_f64, ::draw2d::pen * ppen);
      //virtual void fill_rectangle(const rectangle_f64 & rectangle_f64);
      //virtual void fill_rectangle(const rectangle_f64 & rectangle_f64, ::draw2d::brush * pbrush);

      //virtual void round_rectd(const ::rectangle_f64 & rectangle, const ::point_f64 & point);

      virtual void round_rectangle(const ::rectangle_f64 & rectangle, double dRadius);


      //virtual void from(const ::point_f64 & pointDst, const ::size_f64 & ::size_f64, ::draw2d::graphics * pgraphicsSrc, const ::point_f64 & pointSrc);
      //virtual void from(const ::size_f64 & ::size_f64, ::draw2d::graphics * pgraphicsSrc, const ::point_f64 & pSrc);
      //virtual void from(const ::size_f64 & ::size_f64, ::draw2d::graphics * pgraphicsSrc);
      //virtual void PatBlt(double x, double y, i32 nWidth, i32 nHeight);



      //virtual void draw_image(const ::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::point_f64 & point);

      //virtual void draw_image(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangle);
      //virtual void draw_image(const ::rectangle_f64 & rectdDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangle);
      //virtual void draw_image(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource);
      // virtual void draw_image(const ::rectangle_f64 & rectddDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource);


      // bit block transfer (pixel-to-pixel)
      //virtual void draw_at(const ::point_f64 & pointDst, ::image::image *pimage);
      //virtual void draw_at(const ::point_f64 & pointDst, ::::image::image_frame * pframe);
      //virtual void draw_at(const ::point_f64 & pointDst, ::draw2d::graphics * pgraphicsSrc);


      bool has_blender() const override;

      bool _draw_blend(const ::image::image_drawing & imagedrawing) override;

      
      //virtual void _draw(const ::rectangle_f64 & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource) override;
      //virtual void _draw_raw(const ::rectangle_f64 & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource) override;
      //virtual void _draw_blend(const ::rectangle_f64 & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource) override;

      //
      //virtual void _draw_raw(const ::rectangle_f64 & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::point_f64 & pointSrc) override;
      //virtual void _stretch_raw(const ::rectangle_f64 & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::rectangle_f64 & rectangleSource) override;




      // potentially stretching
      //virtual void stretch(const ::rectangle_f64 & rectangleTarget, ::image::image *pimage, const ::rectangle_f64 & rectangleSource = ::rectangle_f64());
      //virtual void stretch(const ::rectangle_f64 & rectangleTarget, ::::image::image_frame * pframe, const ::rectangle_f64 & rectangleSource = ::rectangle_f64());
      //virtual void stretch(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64());
      //virtual void stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64());
      //virtual void stretch_blend(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource = ::rectangle_f64());


      //template < primitive_size SIZE >
      //inline void alpha_blend(const SIZE & sizeDst, const ::image::image_drawing & imagedrawing, double dOpacity)
      //{

      //   auto finalSrcSize = pimagesource->size_i32(sizeDst, sizeSrc, eimageselection);

      //   auto pimage = pimagesource->get_image(sizeSrc);

      //   return _alpha_blend(::rectangle_f64(sizeDst), pgraphicssource, ::rectangle_f64(sizeDst), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE >
      //inline void alpha_blend(const RECTANGLE & rectangleTarget, const ::image::image_drawing & imagedrawing, double dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, ::rectangle_f64(rectangleTarget.size()), dOpacity);

      //}

      //
      //template < primitive_rectangle RECTANGLE, primitive_point POINT >
      //inline void alpha_blend(const RECTANGLE & rectangleTarget, const ::image::image_drawing & imagedrawing, const POINT & pointSrc, double dOpacity)
      //{

      //   if (::is_null(pgraphicssource))
      //   {

      //      return false;

      //   }

      //   auto sizeDst = rectangleTarget.size() - pointSrc;

      //   return _alpha_blend(rectangle_f64(rectangleTarget.top_left(), sizeDst), pgraphicssource, ::rectangle_f64(pointSrc, pgraphicssource->size_i32(sizeDst) - pointSrc), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE_DST, primitive_rectangle RECTANGLE_SRC >
      //inline void alpha_blend(const RECTANGLE_DST & rectangleTarget, const ::image::image_drawing & imagedrawing, const RECTANGLE_SRC & rectangleSource, double dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, rectangleSource, dOpacity);

      //}


      //virtual void _alpha_blend(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dOpacity);
      //virtual void _alpha_blend_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dRate);
      //virtual void _alpha_blend_blend(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource, double dRate);


      //virtual void draw(const ::rectangle_f64 & point, cursor * pcursor);
      //virtual void draw(const ::rectangle_f64 & rectangleTarget, icon * picon);



      virtual ::color::color GetPixel(double x, double y);
      virtual ::color::color GetPixel(const ::point_f64 & point);
      virtual ::color::color SetPixel(double x, double y, const ::color::color & color);
      virtual ::color::color SetPixel(const ::point_f64 & point, const ::color::color & color);
      virtual ::color::color blend_pixel(const ::point_f64 & point, const ::color::color & color);
//      virtual void FloodFill(double x, double y, const ::color::color & color);
//      virtual void ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType);
//      virtual void MaskBlt(double x, double y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                           double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                           u32 dwRop);
//      virtual void PlgBlt(::point_f64 * pPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//
//                          i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask);
      virtual void SetPixelV(double x, double y, const ::color::color & color);
      virtual void SetPixelV(const ::point_f64 & point, const ::color::color & color);
      //virtual void GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
      //void * pMesh, WINULONG nMeshElements, u32 dwMode);
//      virtual void TransparentBlt(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
//                                  ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                                  ::u32 clrTransparent);



      // Text Functions
      //virtual void text_out(double x, double y, const ::string & pszString, strsize nCount);

      inline void text_out(const ::point_f64 & point, const ::scoped_string & scopedstr)
      {

         return text_out(point.x(), point.y(), scopedstr);

      }

      virtual void text_out(double x, double y, const ::scoped_string & scopedstr);
      //virtual void ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const ::string & pszString, strsize nCount, i32 * lpDxWidths);

      //virtual void ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const ::string & str, i32 * lpDxWidths);

      //virtual ::size_f64 TabbedTextOut(double x, double y, const ::string & pszString, strsize nCount, ::collection::count nTabPositions, i32 * lpnTabStopPositions, i32 nTabOrigin);

      //virtual ::size_f64 TabbedTextOut(double x, double y, const ::string & str, ::collection::count nTabPositions, i32 * pnTabStopPositions, i32 nTabOrigin);


      void TextOutRaw(double x, double y, const ::scoped_string & scopedstr) override;

      virtual bool TextOutAlphaBlend(double x, double y, const ::scoped_string & scopedstr);


      virtual void _001DrawText(const ::string & str, rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bMeasure = false);


      virtual void draw_text(const ::string & str, const ::rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //virtual void draw_text(const ::string & str, const rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);


#ifndef UNIVERSAL_WINDOWS

//      virtual void draw_text_ex(const ::string & str,const ::rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

//      virtual void draw_text_ex(const ::string & str,const rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual void draw_text_ex(const ::string & str,const ::rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

      //virtual void draw_text_ex(const ::string & str,const rectangle_f64 & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#endif


      virtual ::collection::count get_character_extent(f64_array & daLeft, f64_array & daRight, const ::string & str, strsize iStart = 0, strsize iCount = -1);

      //virtual ::size_f64 get_text_extent(const ::scoped_string & scopedstrString);

      ::size_f64 get_text_extent(const ::scoped_string & scopedstr) override;

      virtual ::size_f64 get_text_extent(const ::scoped_string & scopedstr, ::strsize iIndex);

      virtual ::size_f64 GetTextBegin(const ::scoped_string & scopedstrString, ::strsize iIndex);

      //virtual ::size_f64 get_text_extent(const ::scoped_string & scopedstrString, strsize nCount);

      //virtual void get_text_extent(::size_f64 & size, const ::scoped_string & scopedstrString, strsize nCount, strsize iIndex);

      //virtual void get_text_extent(::size_f64 & size, const ::scoped_string & scopedstrString, strsize nCount);

      //virtual void get_text_extent(::size_f64 & size, const ::scoped_string & scopedstr);
      //virtual ::size_f64 GetOutputTextExtent(const ::scoped_string & scopedstrString, strsize nCount);

      //virtual ::size_f64 GetOutputTextExtent(const ::string & str);
      //virtual ::size_f64 GetTabbedTextExtent(const ::scoped_string & scopedstrString, strsize nCount, ::collection::count nTabPositions, i32 * lpnTabStopPositions);

      //virtual ::size_f64 GetTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, i32 * pnTabStopPositions);

      //virtual ::size_f64 GetOutputTabbedTextExtent(const ::string & pszString, strsize nCount, ::collection::count nTabPositions, i32 * lpnTabStopPositions);

      //virtual ::size_f64 GetOutputTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, i32 * pnTabStopPositions);

      //virtual void GrayString(::draw2d::brush* pBrush, void (CALLBACK* pfnOutput)(HDC, lparam, i32), lparam lpData, i32 nCount, double x, double y, i32 nWidth, i32 nHeight);

      virtual ::u32 GetTextAlign();
      virtual ::u32 SetTextAlign(::u32 nFlags);
      //virtual i32 GetTextFace(count nCount, char * pszFacename);

      //virtual i32 GetTextFace(string & rString);

      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric * pmetrics) override;
      virtual void get_output_text_metrics(::write_text::text_metric * pMetrics);



      //virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      //virtual i32 GetTextCharacterExtra();
      //virtual i32 SetTextCharacterExtra(i32 nCharExtra);

// #ifdef WINDOWS_DESKTOP

//       virtual u32 GetCharacterPlacement(const ::string & pString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags);

//       virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS pResults, u32 dwFlags);


// #endif

// #if (_WIN32_WINNT >= 0x0500)

//       virtual void get_text_extentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, i32 * pnFit, i32 * alpDx, __out_opt ::size_f64 * ::size_f64 *);

//       virtual void get_text_extentPointI(LPWORD pgiIn, i32 cgi, __out_opt ::size_f64 * pSize);


// #endif

//
//
//  /*    // Advanced Drawing
//      virtual void DrawEdge(const ::rectangle_f64 & prectd,::u32 nEdge,::u32 nFlags);
//
//      virtual void DrawFrameControl(const ::rectangle_f64 & prectd,::u32 nType,::u32 nState);
//*/

      //// Scolorolling Functions
      //virtual void ScrollDC(i32 Δx, i32 Δy, const ::rectangle_f64 &  pRectScoloroll, const ::rectangle_f64 &  lpRectClip,

      //                      ::draw2d::region* pregionUpdate, ::rectangle_f64 * pRectUpdate);


      // font Functions
//      virtual void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual void GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, i32 * pBuffer);

//      virtual u32 SetMapperFlags(u32 dwFlag);
//      virtual ::size_f64 GetAspectRatioFilter();

// #ifdef WINDOWS_DESKTOP

//       virtual void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC pabc);


// #endif

//      virtual u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID pData, u32 cbData);


// #ifdef WINDOWS_DESKTOP

//       virtual i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR pkrnpair);

//       virtual ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW potm);

//       virtual u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm, u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2);


//       virtual void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT pABCF);


// #endif

      // virtual void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float * pFloatBuffer);


      // virtual u32 GetFontLanguageInfo();

//#if defined(WINDOWS_DESKTOP) && (_WIN32_WINNT >= 0x0500)
//
//      virtual void GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC pabc);
//
//      virtual void GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, i32 * pBuffer);
//
//
//#endif

      //// Printer/Device Escape Functions
      //virtual i32 Escape(i32 nEscape, i32 nCount, const ::string & pszInData, LPVOID lpOutData);

      //virtual i32 Escape(i32 nEscape, i32 nInputSize, const ::string & pszInputData, i32 nOutputSize, char * pszOutputData);

      //virtual i32 DrawEscape(i32 nEscape, i32 nInputSize, const ::string & pszInputData);


      // Escape helpers
      //virtual i32 StartDoc(const ::string & pszDocName);  // old Win3.0 version


//#ifdef WINDOWS_DESKTOP
//
//      virtual i32 StartDoc(LPDOCINFOW pDocInfo);
//
//#endif

      virtual i32 StartPage();
      virtual i32 EndPage();
//      virtual i32 SetAbortProc(void (CALLBACK* pfn)(HDC, i32));

      virtual i32 AbortDoc();
      virtual i32 EndDoc();

      // MetaFile Functions
//#ifdef WINDOWS
//      virtual void PlayMetaFile(HMETAFILE hMF);
//      virtual void PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_f64 &  pBounds);
//
//#endif
      virtual void AddMetaFileComment(::u32 nDataSize, const ::u8* pCommentData);
      // can be used for enhanced metafiles only

      virtual void abort_path();
      virtual void begin_path();
      virtual void close_figure();
      virtual void end_path();
      virtual void fill_path();
      virtual void flatten_path();
      virtual void stroke_and_fill_path();
      virtual void stroke_path();
      virtual void widen_path();
      virtual float GetMiterLimit();
      virtual void SetMiterLimit(float fMiterLimit);
//      virtual i32 GetPath(::point_f64 * ppoint, ::u8 * pTypes, ::collection::count nCount);

      virtual void SelectClipPath(i32 nMode);

      virtual void draw(::draw2d::path * ppath, ::draw2d::pen * ppen);
      virtual void draw(::draw2d::path * ppath);
      virtual void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      virtual void fill(::draw2d::path * ppath);
      virtual void path(::draw2d::path * ppath);

      virtual void intersect_clip(::draw2d::path * ppath);
      virtual void set_clip(::draw2d::path * ppath);

      // Misc helper Functions
      virtual ::draw2d::brush * GetHalftoneBrush();
      //virtual void DrawDragRect(const ::rectangle_f64 & rectangle, const ::size_f64 & ::size_f64,

      //                          const ::rectangle_f64 &  pRectLast, const ::size_f64 & sizeLast,

      //                          ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);

      //virtual void fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color);
      //virtual void fill_rectangle(const rectangle_f64 & rectangle_f64, const ::color::color & color);

      virtual void draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, double dWidth, const ::e_border & eborder = e_border_all);
      //virtual void draw_inset_3d_rectangle(const rectangle_f64 & rectangle_f64, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      virtual void draw_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color& color, double dWidth, const ::e_border & eborder = e_border_all);
      virtual void frame_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, const ::e_border & eborder = e_border_all);
      //virtual void draw_rectangle(const rectangle_f64 & rectangle_f64, const ::color::color& color, const ::e_border & eborder = e_border_all);

      virtual void set_font(::user::interaction* pinteraction, ::enum_element eelement = ::e_element_none, ::user::enum_state estate = ::user::e_state_none);


      virtual void get(::geometry2d::matrix & matrix);
      //using ::aura::simple_chain < ::aura::draw_context >::set;
      virtual void set(const ::geometry2d::matrix & matrix);
      virtual void append(const ::geometry2d::matrix & matrix);
      virtual void prepend(const ::geometry2d::matrix & matrix);
      virtual void update_matrix();

      virtual void _get(::geometry2d::matrix & matrix);
      virtual void _set(const ::geometry2d::matrix & matrix);

      //=============================================================================
      //
      // draw_round_rectd()
      //
      // Purpose:     Draws a rounded rectdangle with a solid pen
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rectangle_f64        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //          width    - [in]  width of the border
      //
      // Returns:     None
      //
      virtual void draw_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, double radius, const ::e_border & eborder);
      virtual void draw_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, double radius);
      //void draw_round_rect(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, const ::point_f64 & point, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, i32 radius, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, i32 radius, const ::e_border & eborder = e_border_all);

      //void draw_round_rect(const ::rectangle_f64 & rectangle, const ::color::color & color, double radius, double width, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::rectangle_f64 & rectangle, const ::color::color & color, i32 radius, i32 width, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::rectangle_f64 & rectangle, const ::color::color & color, i32 radius, i32 width, const ::e_border & eborder = e_border_all);


      virtual void draw_stock_icon(const ::rectangle_f64 & rectangle_f64, enum_stock_icon estockicon);


      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          rectangle_f64        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, double radius);

      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          pBrush      - [in]  pointer to a Brush
      //          rectangle_f64        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the border (needed in case the
      //                         brush is a type other than solid)
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush, double radius);


      //void fill_round_rect(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush, const ::point_f64 & point);


      //virtual void round_rectangle(const ::rectangle_f64 & rectangle, double radius);

      virtual i32 _DrawText(const ::string & str, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, ::write_text::font * pfontUnderline = nullptr);

      virtual void debug();




      virtual float nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy);
      virtual void nanosvg_cubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tol, int level);
      virtual void nanosvg_drawPath(float* pts, int npts, char closed, float tol, const ::color::color & color);
      virtual void nanosvg_drawControlPts(float* pts, int npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, int x, int y, int w, int h);
      // virtual void nanosvg_resizecb(int width, int height, int x, int y, int w, int h);

      virtual void nanosvg(string str, int x, int y, int w, int h);

      virtual void is_valid_update_window_thread();

      //virtual void set_current_point(double x, double y); // { return set_current_point(::point_f64(x, y)); }
      //inline void set_current_point(double x, double y) { return set_current_point(::point_f64(x, y)); }

      //inline void line_to(double x, double y) { return line_to(::point_f64(x, y)); }
      //inline void line_to(double x, double y) { return line_to(::point_f64(x, y)); }
      //virtual void line_to(double x, double y);// { return line_to(::point_f64(x, y)); }

      //inline void draw_line(double x1, double y1, double x2, double y2) { return draw_line(::point_f64(x1,y1), ::point_f64(x2, y2)); }
      //inline void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::point_f64(x1, y1), ::point_f64(x2, y2), ppen); }

      ///virtual void draw_line(double x1, double y1, double x2, double y2); // { return draw_line(::point_f64(x1, y1), ::point_f64(x2, y2)); }
      //virtual void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_line(::point_f64(x1, y1), ::point_f64(x2, y2), ppen); }

      //inline void draw_line(double x1, double y1, double x2, double y2) { return draw_line(::point_f64(x1, y1), ::point_f64(x2, y2)); }
      //inline void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::point_f64(x1, y1), ::point_f64(x2, y2), ppen); }

      //inline void rectdangle_coord(double x1, double y1, double x2, double y2) { return rectdangle(::rectangle_f64(x1, y1, x2, y2)); }
      //inline void rectdangle_coord(double x1, double y1, double x2, double y2); // { return rectdangle(rectangle_f64(x1, y1, x2, y2)); }

      //inline void rectdangle_dim(double x, double y, i32 cx, i32 cy) { return rectdangle(rectangle_f64_dimension(x, y, cx, cy)); }
      //inline void rectdangle_dim(double x, double y, double cx, double cy); // { return rectdangle(rectdd_dim(x, y, cx, cy)); }

      //inline void draw_rect_coord(double x1, double y1, double x2, double y2) { return draw_rectangle(::rectangle_f64(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_rectangle(::rectangle_f64(x1, y1, x2, y2), ppen); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2); // { return draw_rectangle(rectangle_f64(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_rectangle(rectangle_f64(x1, y1, x2, y2), ppen); }

      //inline void draw_rect_dim(double x, double y, i32 cx, i32 cy) { return draw_rectangle(rectangle_f64_dimension(x, y, cx, cy)); }
      //inline void draw_rect_dim(double x, double y, i32 cx, i32 cy, ::draw2d::pen * ppen) { return draw_rectangle(rectangle_f64_dimension(x, y, cx, cy), ppen); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy); // { return draw_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy, ::draw2d::pen * ppen); // { return draw_rectangle(rectdd_dim(x, y, cx, cy), ppen); }

      //inline void fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rectangle(::rectangle_f64(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rectangle(::rectangle_f64(x1, y1, x2, y2), pbrush); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rectangle(rectangle_f64(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rectangle(rectangle_f64(x1, y1, x2, y2), pbrush); }

      //inline void fill_rect_dim(double x, double y, i32 cx, i32 cy) { return fill_rectangle(rectangle_f64_dimension(x, y, cx, cy)); }
      //inline void fill_rect_dim(double x, double y, i32 cx, i32 cy, ::draw2d::brush * pbrush) { return fill_rectangle(rectangle_f64_dimension(x, y, cx, cy), pbrush); }
      //inline void fill_rect_dim(double x, double y, double cx, double cy); // { return fill_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void fill_rect_dim(double x, double y, double cx, double cy, ::draw2d::brush * pbrush); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), pbrush); }

      //inline void polygon(point_i32_array & pointa) { return polygon(pointa.data(), pointa.size()); }
      inline void polygon(point_f64_array & pointa) { return polygon(pointa.data(), pointa.size()); }
      //inline void draw_polygon(point_i32_array & pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      inline void draw_polygon(point_f64_array & pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      //inline void fill_polygon(point_i32_array & pointa) { return fill_polygon(pointa.data(), pointa.size()); }
      inline void fill_polygon(point_f64_array & pointa) { return fill_polygon(pointa.data(), pointa.size()); }

      //inline void fill_solid_rect_dim(double x, double y, i32 cx, i32 cy, const ::color::color & color) { return fill_rectangle(rectangle_f64_dimension(x, y, cx, cy), color); }
      //inline void fill_solid_rect_dim(double x, double y, double cx, double cy, const ::color::color & color); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), color); }

      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color::color & color) { return fill_rectangle(::rectangle_f64(x1, y1, x2, y2), color); }
      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color::color & color) { return fill_rectangle(rectangle_f64(x1, y1, x2, y2), color); }

      //inline void draw_3drect_dim(double x, double y, i32 cx, i32 cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(rectangle_f64_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_dim(double x, double y, double cx, double cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(rectangle_f64_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_dim(double x, double y, i32 cx, i32 cy, const ::color::color& color) { return draw_rectangle(rectangle_f64_dimension(x, y, cx, cy), color); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy, const ::color::color& color) { return draw_rectangle(rectangle_f64_dimension(x, y, cx, cy), color); }

      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(::rectangle_f64(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(rectangle_f64(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color::color& color) { return draw_rectangle(::rectangle_f64(x1, y1, x2, y2), color); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color::color& color) { return draw_rectangle(rectangle_f64(x1, y1, x2, y2), color); }

      
   //protected:

     // friend class savedc;
      virtual i32 save_graphics_context();
      virtual void restore_graphics_context(i32 nSavedContext);

   };


   class CLASS_DECL_AURA save_context
   {
   public:


      graphics *              m_pgraphics;
      int                     m_iSavedDC;

      ::size_f64              m_sizeScaling;
      ::point_f64             m_pointOrigin;
      ::geometry2d::matrix    m_matrix;

      save_context(graphics * graphics);
      ~save_context();


   };

   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_graphics();
   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_memory_graphics();



} // namespace draw2d


//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::size_f64 & size);
//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::point_f64 & point);



//CLASS_DECL_AURA PFN_factory ([a-z0-9_]+)_factory(::factory::factory * pfactory);

//CLASS_DECL_AURA void ([a-z0-9_]+)_factory(PFN_factory pfnfactoryDraw2d);
