#pragma once


#include "acme/constant/element.h"
#include "acme/graphics/image/image32.h"

#include "aura/platform/draw_context2.h"
#include "aura/graphics/write_text/drawer.h"
#include "aura/graphics/image/drawer.h"
#include "aura/graphics/image/source.h"
#include "acme/prototype/geometry2d/angle.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "acme/prototype/geometry2d/shift.h"
#include "aura/user/user/redraw.h"
#include "aura/graphics/draw2d/region.h"
#include "aura/graphics/draw2d/bitmap.h"
#include "aura/graphics/draw2d/offset.h"
namespace gpu
{

   class renderer;

} // namespace gpu
//#include "acme/prototype/geometry2d/_geometry2d.h"


//#include "acme/prototype/geometry2d/ellipse.h"


using hdc = void*;


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
   //concept graphics_source_pointer = requires(const ::image::image_drawing & imagedrawing, const ::double_size & sizeHint)
   //{

   //   { pgraphicssource->g(sizeHint) } -> ::std::convertible_to < ::draw2d::graphics * >;
   //   { pgraphicssource->origin() } -> ::std::convertible_to < ::double_size >;
   //   { pgraphicssource->int_size(sizeHint) } -> ::std::convertible_to < ::double_size >;

   //};



/// <summary>
/// graphics * -> ::image::image_source_pointer concept
/// </summary>
   class CLASS_DECL_AURA graphics :
      virtual public ::aura::simple_chain < ::aura::draw_context >,
      virtual public ::image::image_drawer,
      virtual public ::write_text::drawer,
      virtual public ::image::image_source_interface,
      virtual public ::draw2d::offsetable
   {
   public:


      e_graphics                                   m_egraphics;
      bool                                         m_bSwapChainFinalInterop = false;
      bool                                         m_bForWindowDraw2d;
      bool                                         m_bBeginDraw;
      bool                                         m_bInheritDraw;
      // try to draw using paths and full primitives
      // there is little control over lines drawn with move_to line_to than generalized
      //bool                                         m_bHasCurrentPoint;
      bool                                         m_bOutline;
      void* m_pthis;
      ::user::interaction* m_puserinteraction;
      ::pointer<::draw2d::host>                    m_pdraw2dhost;

      bool                                         m_bPat;
      ///::image32_callback                           m_callbackImage32CpuBuffer;


      //bool                                   m_bAlphaBlend;

      ::pointer<::text::context>          m_ptextcontext;
      ::aura::draw_context* m_pdrawcontext;
      ::image::image_pointer                        m_pimageAlphaBlend;
      ::double_point                            m_pointAlphaBlend;
      ::pointer<::task>                     m_ptask;
      bool                                   m_bDraw;

      ::image::image* m_pimage = nullptr;
      ::draw2d::bitmap_pointer               m_pbitmap;
      ::draw2d::pen_pointer                  m_ppen;
      ::draw2d::brush_pointer                m_pbrush;
      ::draw2d::region_pointer               m_pregion;
      bool                                   m_bStoreThumbnails;

      ::double_point                            m_point;

   protected:
      //bool                                   _m_bYFlip;
      enum_alpha_mode                        m_ealphamode;


   public:
      enum_fill_mode                         m_efillmode;
      enum_smooth_mode                          m_esmoothmode;
      enum_interpolation_mode                m_einterpolationmode;
      enum_compositing_quality                  m_ecompositingquality;
      ::write_text::enum_rendering           m_ewritetextrendering;
      double                                 m_dFontFactor;

      ::double_size                             m_sizeScaling;
      ::double_point                            m_pointOrigin;
      ::double_size                             m_sizeImpact2;
      ::double_size                             m_sizeTotal2;
      ::geometry2d::matrix                      m_matrix;
      ::double_size                             m_sizeScaleOutput;
      ::double_point                            m_pointTranslateOutput;

      ::double_rectangle                        m_rectangleDraw;

      bool                                   m_bPrinting;
      void* m_osdata[8];
      ::user::style_pointer                  m_puserstyleGraphics;
      //::double_point                            m_pointAddShapeTranslate;
      bool                                   m_bUseImageMipMapsOrResizedImages;

      //::e_status                             m_estatus;
      //::e_status                             m_estatusLast;

      ::pointer < ::graphics::graphics >     m_pgraphicsgraphics;
      ::pointer < ::graphics::buffer_item >  m_pgraphicsbufferitem;

      ::pointer < ::user::redraw >           m_puserredraw;

      graphics();
      ~graphics() override;


      void on_initialize_particle() override;

      virtual bool is_gpu_oriented();
      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;


      void destroy() override;
      void destroy_os_data() override;


      virtual bool is_y_flip();


      virtual void do_on_context(const ::procedure& procedure);

      inline operator ::user::style& ()
      {

         return *m_puserstyleGraphics;

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
      inline T* get_os_data(char i = 0) const
      {

         return (T*)m_osdata[i];

      }


      inline void* get_os_data(char i = 0) const
      {

         return get_os_data < void >(i);

      }

      using image_drawer::draw;
      using write_text::drawer::draw;

      virtual ::file::path get_font_path(const ::scoped_string & scopedstrName, int iWeight, bool bItalic);

      //virtual oswindow get_window_handle() const;
      virtual void defer_snapshot_for_composition();


      inline ::draw2d::graphics* g(const ::double_size& sizeHint) { return this; }
      inline ::double_size origin() const { return ::double_size(); }

      bool _is_ok() const override;

      ::image::image_pointer image_source_image(const ::int_size& sizeDst) override;

      ::int_size image_source_size(const ::double_size& sizeDst, enum_image_selection eimageselection) const override;

      ::int_size image_source_size() const override;


      //virtual void start_gpu_layer(const ::int_rectangle & rectangleTarget);

      ::user::redraw* user_redraw();
      //#ifdef UNIVERSAL_WINDOWS
      //
      //
      //      virtual void set_directd2d_plugin(::draw2d_directd2d::plugin * pplugin);
      //
      //
      //#endif


      virtual void defer_add_graphics_render(::graphics::render* pgraphicsrender);


      virtual void on_begin_draw();
      virtual void on_end_draw();

      virtual void __on_begin_draw();

      virtual bool fill_contains(const double_point& point);

      void draw_ca2(int x, int y, int z, const ::color::color& colorBk, const ::color::color& color);
      void draw_ca2_with_border(int x, int y, int z, int b, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorOut);
      void draw_ca2_border2(int x, int y, int z, int bOut, int bIn, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorBorderOut, const ::color::color& colorIn);
      void draw_ca2_with_border2(int x, int y, int z, int bOut, int bIn, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorBorderOut, const ::color::color& colorIn);


      void draw_border(const ::double_rectangle& rectangle, const ::color::color& color, int iWidth);
      void draw_rect_side(const ::double_rectangle& double_rectangle, enum_border eborder);

      virtual bool is_set();


      virtual void thread_select();


      virtual void clear_current_point();


      virtual void attach(void* pdata);
      virtual void* detach();

#ifdef WINDOWS_DESKTOP

      virtual void attach_hdc(hdc hdc);
      virtual hdc detach_hdc();
      virtual void AttachPrinter(hdc hdc);
      virtual hdc DetachPrinter();

#endif


      virtual void prefer_mapped_image_on_mix();

      virtual ::text::context* textcontext();
      virtual ::aura::draw_context* draw_context();

      virtual void set_alpha_mode(enum_alpha_mode ealphamode);
      inline enum_alpha_mode alpha_mode() const { return m_ealphamode; }

      virtual void set_smooth_mode(enum_smooth_mode esmoothmode);

      virtual void set_interpolation_mode(enum_interpolation_mode einterpolationmode);

      virtual void set_compositing_quality(enum_compositing_quality ecompositingquality);

      virtual void set_text_rendering_hint(::write_text::enum_rendering erendering);

      virtual enum_smooth_mode get_smooth_mode();

      virtual void blur(bool bExpand, double dRadius, const ::double_rectangle& rectangle);

      virtual void set_solid_pen(double dWidth, const ::color::color& color);

      //virtual void IsPrinting();            // true if being used for printing

      virtual ::draw2d::pen* get_current_pen();
      virtual ::draw2d::brush* get_current_brush();
      virtual ::draw2d::palette* get_current_palette();
      virtual ::draw2d::bitmap* get_current_bitmap();






      // for bidi and mirrored localization
      virtual unsigned int GetLayout();
      virtual unsigned int SetLayout(unsigned int dwLayout);

      // Constructors
      virtual void create_device_context(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void* lpInitData);

      virtual void create_information_context(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void* lpInitData);

      virtual void create_window_graphics(::windowing::window* pwindow);
      virtual void create_offscreen_graphics_for_swap_chain_blitting(::user::interaction* puserinteraction, const ::int_size& size = {});
      virtual void create_memory_graphics(const ::int_size& size = {});
      virtual void create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size = {});
      virtual void defer_set_size(const ::int_size& size = {});
      virtual void _create_memory_graphics(const ::int_size& size = {});
      virtual void CreateCompatibleDC(::draw2d::graphics* pgraphics);
      virtual void CreateWindowDC(oswindow wnd);


      virtual ::pointer < ::draw2d::path > create_path();
      virtual ::pointer < ::draw2d::pen > create_solid_pen(double dWidth, const ::color::color & color);
      virtual ::pointer < ::draw2d::brush > create_solid_brush(const ::color::color & color);

      //virtual void set_hint_window_output();

      virtual void defer_resize_memory_graphics(const ::int_size& size);

      virtual void on_begin_draw(oswindow wnd, const ::double_size& sz);
      virtual void on_end_draw(oswindow wnd);
      virtual void on_present();

      virtual void DeleteDC();


      // Device-Context Functions
      virtual int GetDeviceCaps(int nIndex);
      virtual unsigned int SetBoundsRect(const ::double_rectangle& rectangleBounds, unsigned int flags);
      virtual unsigned int GetBoundsRect(::double_rectangle* rectdBounds, unsigned int flags);


      virtual void resize(const ::int_size& sizeWindow);



      //#ifdef WINDOWS
      //      virtual void ResetDC(const DEVMODE* pDevMode);
      //
      //#endif

            // Drawing-Tool Functions
      virtual ::double_point GetBrushOrg();
      virtual ::double_point SetBrushOrg(double x, double y);
      virtual ::double_point SetBrushOrg(const ::double_point& point);
      //virtual int EnumObjects(int nObjectType,
                              //int (CALLBACK* pfn)(LPVOID, lparam), lparam lpData);



      virtual void set_text_color(::color::color color);


      using ::write_text::drawer::set;
      virtual void set(::draw2d::region* pregion);
      virtual void set(::draw2d::pen* ppen);
      virtual void set(::draw2d::brush* pbrush);
      virtual void set(::draw2d::bitmap* pbitmap);
      virtual ::draw2d::object* set_stock_object(int nIndex);


      // color and color Palette Functions
      //virtual ::color::color GetNearestColor(const ::color::color & color);
      //virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, void bForceBackground);
      //virtual unsigned int RealizePalette();
      //virtual void UpdateColors();

      // Drawing-Attribute Functions
      //virtual int GetPolyFillMode();
      //virtual int GetROP2();
      //virtual int GetStretchBltMode();


      virtual double get_dpix();
      virtual double get_dpiy();

      //virtual int SetPolyFillMode(int nPolyFillMode);
      //virtual int SetROP2(int nDrawMode);
//      virtual void set_interpolation_mode(enum_interpolation_mode einterpolationmode);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual void flush();
      virtual void sync_flush();


      virtual ::double_size get_size() const;

      ::int_size get_image_drawer_size() const override;







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
            //virtual int SetGraphicsMode(int iMode);
            //virtual int GetGraphicsMode();

      //      // World transform
      //#ifdef WINDOWS
      //      virtual void SetWorldTransform(const XFORM* pXform);
      //      virtual void ModifyWorldTransform(const XFORM* pXform,unsigned int iMode);
      //      virtual void GetWorldTransform(XFORM* pXform);
      //#endif

      virtual ::double_size get_scaling();

      // Mapping Functions
      ///virtual int GetMapMode();
      ///virtual ::double_point _get_origin();
      //virtual int SetMapMode(int nMapMode);
      // Context Origin
      //virtual void _set_origin(double x, double y);
      //virtual void _set_origin(const ::double_point& double_point);
      //virtual void _offset_origin(double x, double y);


      virtual void reset_impact_area();
      virtual void place_impact_area(double x, double y, double w, double h);
      virtual void place_impact_area(const ::double_point& pointImpactArea, const ::double_size & sizeImpactArea);
      virtual void place_impact_area(const ::double_rectangle& rectangleImpactArea);
      void shift_impact_area(double dx, double dy, double w, double h) override;
      virtual void shift_impact_area(const ::double_size& shiftImpactArea, const ::double_size& sizeImpactArea);
      virtual void shift_impact_area(const ::double_rectangle& rectangleImpactArea);


      virtual ::double_size impact_size();
      virtual ::double_size total_size();


      void x_offset(double dx) override;
      void y_offset(double dy) override;
      void offset(double dx, double dy) override;
      virtual void _x_offset(double dx);
      virtual void _y_offset(double dy);
      virtual void _offset(double dx, double dy);
      virtual void offset(const ::double_size& size);

      
      // Context Extent
      virtual ::double_size get_extents();
      virtual ::double_size set_extents(double cx, double cy);
      virtual ::double_size set_extents(const ::double_size& size);
      virtual ::double_size scale_extents(double xNum, double xDenom, double yNum, double yDenom);

      // Window Origin
      virtual ::double_point GetWindowOrg();
      virtual ::double_point SetWindowOrg(double x, double y);
      virtual ::double_point SetWindowOrg(const ::double_point& point);
      virtual ::double_point offset_window_org(double nWidth, double nHeight);

      // Window extent
      virtual ::double_size GetWindowExt();
      //virtual ::double_size set_window_ext(double cx, double cy);
      //virtual ::double_size set_window_ext(const ::double_size& size);
      //virtual ::double_size scale_window_ext(double xNum, double xDenom, double yNum, double yDenom);

      // Coordinate Functions
      virtual void DPtoLP(::double_point* ppoint, ::collection::count nCount = 1);
      virtual void DPtoLP(::double_rectangle* prectd);

      virtual void DPtoLP(::double_size* pSize);

      virtual void LPtoDP(::double_point* ppoint, ::collection::count nCount = 1);
      virtual void LPtoDP(::double_rectangle* prectd);

      virtual void LPtoDP(::double_size* pSize);


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(::double_size* pSize);

      virtual void LPtoHIMETRIC(::double_size* pSize);

      virtual void HIMETRICtoDP(::double_size* pSize);

      virtual void HIMETRICtoLP(::double_size* pSize);


      // Region Functions
      virtual void fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush);
      virtual void frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight);
      virtual void invert_region(::draw2d::region* pregion);
      virtual void paint_region(::draw2d::region* pregion);

      // Clipping Functions
      virtual int get_clip_box(::double_rectangle& rectangle);

      //virtual int get_clip_box(::double_rectangle * prectangle);

      //virtual void PtVisible(double x, double y);
      //virtual void PtVisible(const ::double_point & point);
      //virtual void RectVisible(const ::double_rectangle & rectangle);



      //virtual void add_clipping_shapes(const pointer_array < ::draw2d::region > & regiona);
      virtual void reset_clip();


      //virtual void set_clipping(::draw2d::region * pregion);

      virtual void intersect_clip(const ::double_rectangle& double_rectangle);
      virtual void intersect_clip(const ::double_ellipse& ellipse);
      virtual void intersect_clip(const ::double_polygon& polygon);


      virtual ::draw2d::region* defer_get_os_data(::pointer < ::geometry2d::region >& pregion);


      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual void _clip(bool bAdd);
      virtual void _intersect_clip();
      virtual void _eo_clip();
      //virtual void _add_clipping_shape(___shape<::draw2d::region> & shape);

      virtual void intersect_clip(const clip& clip);
      virtual void intersect_clip(const clip_group& clipgroup);
      virtual void _add_clip_item(clip_item* pclipitem);

      /// If it is "simple" shape (not combine_item) it
      /// calls add_shape on the item and returns true.
      /// Otherwise (if it is "complex" shape, a combine_item)
      /// it returns false.
      virtual bool _add_simple_shape(::geometry2d::item* pitem);
      virtual void _add_shape(const ::double_rectangle& rectangle);
      virtual void _add_shape(const ::double_ellipse& ellipse);
      virtual void _add_shape(const ::double_polygon& polygon);

      //virtual void IntersectClipregion(::draw2d::region * pregion);
      //virtual void IntersectClipRect(double x1, double y1, double x2, double y2);
      //virtual void IntersectClipRect(const ::double_rectangle & rectangle);
      //virtual int ExcludeClipRect(double x1, double y1, double x2, double y2);
      //virtual int ExcludeClipRect(const ::double_rectangle & rectangle);
      //virtual int ExcludeUpdateRgn(::windowing::window * pwindow);
      //virtual int OffsetClipregion(double x, double y);
      //virtual int OffsetClipregion(const ::double_size & ::double_size);
      //virtual int SelectClipregion(::draw2d::region* pregion, ::draw2d::enum_combine ecombine);

      virtual void on_apply_clip_region();

      virtual ::double_point current_position();

      //inline void set_current_point(double x, double y)
      //{

      //   return set_current_point({ x, y });

      //}


      //virtual void set_current_point(double x, double y);
      //virtual void line_to(double x, double y);
      virtual void line(double x1, double y1, double x2, double y2);
      virtual void line(double x1, double y1, double x2, double y2, ::draw2d::pen* ppen);


      //inline void set_current_point(const ::double_point& point)
      //{

      //   return set_current_point(point.x(), point.y());

      //}


      //virtual void line_to(const ::double_point& point)
      //{

      //   return line_to(point.x(), point.y());

      //}

      template< typename POINT>
      void process_line(POINT & pointLast, const POINT & pointNow)
      {

         line(pointLast, pointNow);
         pointLast = pointNow;

      }

      inline void line(const ::double_point& point1, const ::double_point& point2)
      {

         return line(point1.x(), point1.y(), point2.x(), point2.y());

      }


      inline void line(const ::double_point& point1, const ::double_point& point2, ::draw2d::pen* ppen)
      {

         return line(point1.x(), point1.y(), point2.x(), point2.y(), ppen);

      }


      virtual void draw_error_line(double x1, double h, double x2, int iStyle);


      virtual void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void arc(const ::double_rectangle& rectangle, const ::double_point& pointStart, const ::double_point& pointEnd);
      virtual void arc(double x1, double y1, double x2, double y2, ::double_angle start, ::double_angle extends);
      virtual void arc(const ::double_rectangle& rectangle, ::double_angle start, ::double_angle extends);


      virtual void polyline(const ::double_point_array& pointa);
      virtual void polyline(const ::double_point* ppoints, ::collection::count nCount);


      //      virtual void arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      //      virtual void arc(const double_rectangle & double_rectangle, const ::double_point & pointStart, const ::double_point & pointEnd);

      //      virtual void arc(double x1, double y1, double x2, double y2, angle start, angle extends);
      //      virtual void arc(const double_rectangle & double_rectangle, angle start, angle extends);


      virtual void angle_arc(double x, double y, double nRadius, ::double_angle fStartAngle, ::double_angle fSweepAngle);
      virtual void arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void arc_to(const ::double_rectangle& rectangle, const ::double_point& pointStart, const ::double_point& pointEnd);
      //virtual int GetArcDirectdion();
      //virtual int SetArcDirectdion(int nArcDirectdion);

      virtual void polydraw(const ::double_point* ppoints, const unsigned char* pTypes, ::collection::count nCount);

      virtual void polyline_to(const ::double_point* ppoints, ::collection::count nCount);
      virtual void poly_polyline(const ::double_point* ppoints, const int* pPolyPoints, ::collection::count nCount);


      virtual void poly_bezier(const ::double_point* ppoints, ::collection::count nCount);
      virtual void poly_bezier_to(const ::double_point* ppoints, ::collection::count nCount);


      virtual void frame_rectangle(const ::double_rectangle& rectangle, ::draw2d::brush* pbrush);
      virtual void invert_rectangle(const ::double_rectangle& rectangle);

      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, HBITMAP hBitmap, unsigned int nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, ::draw2d::bitmap* pBitmap, unsigned int nFlags,::draw2d::brush* pBrush = nullptr);
      //#ifdef WINDOWS
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, hicon hIcon, unsigned int nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, hicon hIcon, unsigned int nFlags, ::draw2d::brush* pBrush = nullptr);
      //#endif
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, const ::scoped_string & scopedstrText, unsigned int nFlags,

        //                           void bPrefixText = true, int nTextLen = 0, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, const ::scoped_string & scopedstrText, unsigned int nFlags,
      //
      //                             void bPrefixText = true, int nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
      //#ifdef WINDOWS_DESKTOP
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, DRAWSTATEPROC pDrawProc,
      //
      //                             lparam lData, unsigned int nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::double_point & point, const ::double_size & ::double_size, DRAWSTATEPROC pDrawProc,
      //
      //                             lparam lData, unsigned int nFlags, ::draw2d::brush* pBrush = nullptr);
      //#endif
            // Ellipse and Polygon Functions
      virtual void Chord(double x1, double y1, double x2, double y2, double x3, double y3,
         double x4, double y4);
      virtual void Chord(const ::double_rectangle& rectangle, const ::double_point& pointStart, const ::double_point& pointEnd);

      virtual void DrawFocusRect(const ::double_rectangle& rectangle);

      /*  virtual void ellipse(double x1, double y1, double x2, double y2);
        virtual void ellipse(const ::double_rectangle & double_rectangle);

        virtual void draw_ellipse(double x1, double y1, double x2, double y2);
        virtual void draw_ellipse(const ::double_rectangle & double_rectangle);

        virtual void fill_ellipse(double x1, double y1, double x2, double y2);
        virtual void fill_ellipse(const ::double_rectangle & double_rectangle);*/





      virtual void ellipse(double x1, double y1, double x2, double y2);
      virtual void ellipse(const double_rectangle& prectd);

      virtual void draw_ellipse(double x1, double y1, double x2, double y2);
      virtual void draw_ellipse(const double_rectangle& prectd);

      virtual void fill_ellipse(double x1, double y1, double x2, double y2);
      virtual void fill_ellipse(const double_rectangle& prectd);


      virtual void Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
      virtual void Pie(const ::double_rectangle& rectangle, const ::double_point& pointStart, const ::double_point& pointEnd);


      //virtual void int_polygon(const ::double_point * ppoints, ::collection::count nCount);
      virtual void polygon(const ::double_point* ppoints, ::collection::count nCount);
      //virtual void draw_polygon(const ::double_point * ppoints, ::collection::count nCount);
      virtual void draw_polygon(const ::double_point* ppoints, ::collection::count nCount);
      //virtual void fill_polygon(const ::double_point * ppoints,count nCount);
      virtual void fill_polygon(const ::double_point* ppoints, ::collection::count nCount);

      //virtual void poly_polygon(const ::double_point * ppoints, const int * pPolyCounts, ::collection::count nCount);
      virtual void poly_polygon(const ::double_point* ppoints, const int* pPolyCounts, ::collection::count nCount);
      //virtual void draw_poly_polygon(const ::double_point * ppoints, const int * pPolyCounts, ::collection::count nCount);
      virtual void draw_poly_polygon(const ::double_point* ppoints, const int* pPolyCounts, ::collection::count nCount);
      //virtual void fill_poly_polygon(const ::double_point * ppoints, const int * pPolyCounts, ::collection::count nCount);
      virtual void fill_poly_polygon(const ::double_point* ppoints, const int* pPolyCounts, ::collection::count nCount);


      virtual void rectangle(const ::double_rectangle& rectangle);

      virtual void frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width);

      virtual void draw_rectangle(const ::double_rectangle& rectangle);
      virtual void draw_rectangle(const ::double_rectangle& rectangle, ::draw2d::pen* ppen);

      virtual void fill_rectangle(const ::double_rectangle& rectangle);
      virtual void fill_rectangle(const ::double_rectangle& rectangle, ::draw2d::brush* pbrush);
      virtual void fill_rectangle(const ::double_rectangle& rectangle, const ::color::color& color);
      virtual void fill_inset_rectangle(const ::double_rectangle& rectangle, const ::color::color& color);
      virtual void fill_solid_rectangle(const ::double_rectangle& rectangle, const ::color::color& color);

      virtual void color_blend_3dRect(const int_rectangle& rectangleParam, const ::color::color& colorTopLeft, const class ::opacity& opacityTopLeft, const ::color::color& color, const class ::opacity& opacityBottomRight);

      //virtual void color_blend(const ::int_rectangle& rectangle, const ::color::color& color, const ::opacity & opacity);

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
//         if (!color_blend(::int_rectangle(pimagesource->size()), color, opacity))
//         {
//
//            return false;
//
//         }
//
//         return true;
//
//      }



      //virtual void int_rectangle(const double_rectangle & double_rectangle);
      //virtual void draw_rectangle(const double_rectangle & double_rectangle);
      //virtual void draw_rectangle(const double_rectangle & double_rectangle, ::draw2d::pen * ppen);
      //virtual void fill_rectangle(const double_rectangle & double_rectangle);
      //virtual void fill_rectangle(const double_rectangle & double_rectangle, ::draw2d::brush * pbrush);

      //virtual void round_rectd(const ::double_rectangle & rectangle, const ::double_point & point);

      virtual void round_rectangle(const ::double_rectangle& rectangle, double dRadius);


      //virtual void from(const ::double_point & pointDst, const ::double_size & ::double_size, ::draw2d::graphics * pgraphicsSrc, const ::double_point & pointSrc);
      //virtual void from(const ::double_size & ::double_size, ::draw2d::graphics * pgraphicsSrc, const ::double_point & pSrc);
      //virtual void from(const ::double_size & ::double_size, ::draw2d::graphics * pgraphicsSrc);
      //virtual void PatBlt(double x, double y, int nWidth, int nHeight);



      //virtual void draw_image(const ::double_rectangle & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::double_point & point);

      //virtual void draw_image(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangle);
      //virtual void draw_image(const ::double_rectangle & rectdDst, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangle);
      //virtual void draw_image(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource);
      // virtual void draw_image(const ::double_rectangle & rectddDst, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource);


      // bit block transfer (pixel-to-pixel)
      //virtual void draw_at(const ::double_point & pointDst, ::image::image *pimage);
      //virtual void draw_at(const ::double_point & pointDst, ::image::image_frame * pframe);
      //virtual void draw_at(const ::double_point & pointDst, ::draw2d::graphics * pgraphicsSrc);


      bool has_blender() const override;

      bool _draw_blend(const ::image::image_drawing& imagedrawing) override;


      //virtual void _draw(const ::double_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::double_rectangle & rectangleSource) override;
      //virtual void _draw_raw(const ::double_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::double_rectangle & rectangleSource) override;
      //virtual void _draw_blend(const ::double_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::double_rectangle & rectangleSource) override;

      //
      //virtual void _draw_raw(const ::double_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::double_point & pointSrc) override;
      //virtual void _stretch_raw(const ::double_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::double_rectangle & rectangleSource) override;




      // potentially stretching
      //virtual void stretch(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::double_rectangle & rectangleSource = ::double_rectangle());
      //virtual void stretch(const ::double_rectangle & rectangleTarget, ::image::image_frame * pframe, const ::double_rectangle & rectangleSource = ::double_rectangle());
      //virtual void stretch(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource = ::double_rectangle());
      //virtual void stretch_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource = ::double_rectangle());
      //virtual void stretch_blend(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource = ::double_rectangle());


      //template < primitive_size SIZE >
      //inline void alpha_blend(const SIZE & sizeDst, const ::image::image_drawing & imagedrawing, double dOpacity)
      //{

      //   auto finalSrcSize = pimagesource->int_size(sizeDst, sizeSrc, eimageselection);

      //   auto pimage = pimagesource->get_image(sizeSrc);

      //   return _alpha_blend(::double_rectangle(sizeDst), pgraphicssource, ::double_rectangle(sizeDst), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE >
      //inline void alpha_blend(const RECTANGLE & rectangleTarget, const ::image::image_drawing & imagedrawing, double dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, ::double_rectangle(rectangleTarget.size()), dOpacity);

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

      //   return _alpha_blend(double_rectangle(rectangleTarget.top_left(), sizeDst), pgraphicssource, ::double_rectangle(pointSrc, pgraphicssource->int_size(sizeDst) - pointSrc), dOpacity);

      //}


      //template < primitive_rectangle RECTANGLE_DST, primitive_rectangle RECTANGLE_SRC >
      //inline void alpha_blend(const RECTANGLE_DST & rectangleTarget, const ::image::image_drawing & imagedrawing, const RECTANGLE_SRC & rectangleSource, double dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, rectangleSource, dOpacity);

      //}


      //virtual void _alpha_blend(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource, double dOpacity);
      //virtual void _alpha_blend_raw(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource, double dRate);
      //virtual void _alpha_blend_blend(const ::double_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::double_rectangle & rectangleSource, double dRate);


      //virtual void draw(const ::double_rectangle & point, cursor * pcursor);
      //virtual void draw(const ::double_rectangle & rectangleTarget, icon * picon);



      virtual ::color::color GetPixel(double x, double y);
      virtual ::color::color GetPixel(const ::double_point& point);
      virtual ::color::color SetPixel(double x, double y, const ::color::color& color);
      virtual ::color::color SetPixel(const ::double_point& point, const ::color::color& color);
      virtual ::color::color blend_pixel(const ::double_point& point, const ::color::color& color);
      //      virtual void FloodFill(double x, double y, const ::color::color & color);
      //      virtual void ExtFloodFill(double x, double y, const ::color::color & color, unsigned int nFillType);
      //      virtual void MaskBlt(double x, double y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                           double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
      //                           unsigned int dwRop);
      //      virtual void PlgBlt(::double_point * pPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
      //
      //                          int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask);
      virtual void SetPixelV(double x, double y, const ::color::color& color);
      virtual void SetPixelV(const ::double_point& point, const ::color::color& color);
      //virtual void GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
      //void * pMesh, WINULONG nMeshElements, unsigned int dwMode);
//      virtual void TransparentBlt(double xDest, double yDest, int nDestWidth, int nDestHeight,
//                                  ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, int nSrcWidth, int nSrcHeight,
//                                  unsigned int clrTransparent);



      // Text Functions
      //virtual void text_out(double x, double y, const ::scoped_string & scopedstrString, character_count nCount);

      inline void text_out(const ::double_point& point, const ::scoped_string& scopedstr)
      {

         return text_out(point.x(), point.y(), scopedstr);

      }

      virtual void text_out(double x, double y, const ::scoped_string& scopedstr);
      //virtual void ExtTextOut(double x, double y, unsigned int nOptions, const ::double_rectangle & rectangle, const ::scoped_string & scopedstrString, character_count nCount, int * lpDxWidths);

      //virtual void ExtTextOut(double x, double y, unsigned int nOptions, const ::double_rectangle & rectangle, const ::scoped_string & scopedstr, int * lpDxWidths);

      //virtual ::double_size TabbedTextOut(double x, double y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions, int nTabOrigin);

      //virtual ::double_size TabbedTextOut(double x, double y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * pnTabStopPositions, int nTabOrigin);


      void TextOutRaw(double x, double y, const ::scoped_string& scopedstr) override;

      virtual bool TextOutAlphaBlend(double x, double y, const ::scoped_string& scopedstr);


      virtual void _001DrawText(const ::scoped_string & scopedstr, double_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none, bool bMeasure = false);


      virtual void draw_text(const ::scoped_string & scopedstr, const ::double_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none);

      //virtual void draw_text(const ::scoped_string & scopedstr, const double_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);


#ifndef UNIVERSAL_WINDOWS

//      virtual void draw_text_ex(const ::scoped_string & scopedstr,const ::double_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

//      virtual void draw_text_ex(const ::scoped_string & scopedstr,const double_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual void draw_text_ex(const ::scoped_string & scopedstr, const ::double_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none);

      //virtual void draw_text_ex(const ::scoped_string & scopedstr,const double_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#endif


      virtual ::collection::count get_character_extent(double_array& daLeft, double_array& daRight, const ::scoped_string & scopedstr, character_count iStart = 0, character_count iCount = -1);

      //virtual ::double_size get_text_extent(const ::scoped_string & scopedstrString);

      ::double_size get_text_extent(const ::scoped_string& scopedstr) override;

      virtual ::double_size get_text_extent(const ::scoped_string& scopedstr, ::character_count iIndex);

      virtual ::double_size GetTextBegin(const ::scoped_string& scopedstrString, ::character_count iIndex);

      //virtual ::double_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount);

      //virtual void get_text_extent(::double_size & size, const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex);

      //virtual void get_text_extent(::double_size & size, const ::scoped_string & scopedstrString, character_count nCount);

      //virtual void get_text_extent(::double_size & size, const ::scoped_string & scopedstr);
      //virtual ::double_size GetOutputTextExtent(const ::scoped_string & scopedstrString, character_count nCount);

      //virtual ::double_size GetOutputTextExtent(const ::scoped_string & scopedstr);
      //virtual ::double_size GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions);

      //virtual ::double_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * pnTabStopPositions);

      //virtual ::double_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, int * lpnTabStopPositions);

      //virtual ::double_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, int * pnTabStopPositions);

      //virtual void GrayString(::draw2d::brush* pBrush, void (CALLBACK* pfnOutput)(HDC, lparam, int), lparam lpData, int nCount, double x, double y, int nWidth, int nHeight);

      virtual unsigned int GetTextAlign();
      virtual unsigned int SetTextAlign(unsigned int nFlags);
      //virtual int GetTextFace(count nCount, char * pszFacename);

      //virtual int GetTextFace(string & rString);

      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric* pmetrics) override;
      virtual void get_output_text_metrics(::write_text::text_metric* pMetrics);



      //virtual int SetTextJustification(int nBreakExtra, int nBreakCount);
      //virtual int GetTextCharacterExtra();
      //virtual int SetTextCharacterExtra(int nCharExtra);

// #ifdef WINDOWS_DESKTOP

//       virtual unsigned int GetCharacterPlacement(const ::string & pString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags);

//       virtual unsigned int GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS pResults, unsigned int dwFlags);


// #endif

// #if (_WIN32_WINNT >= 0x0500)

//       virtual void get_text_extentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, int * pnFit, int * alpDx, __out_opt ::double_size * ::double_size *);

//       virtual void get_text_extentPointI(LPWORD pgiIn, int cgi, __out_opt ::double_size * pSize);


// #endif

//
//
//  /*    // Advanced Drawing
//      virtual void DrawEdge(const ::double_rectangle & prectd,unsigned int nEdge,unsigned int nFlags);
//
//      virtual void DrawFrameControl(const ::double_rectangle & prectd,unsigned int nType,unsigned int nState);
//*/

      //// Scolorolling Functions
      //virtual void ScrollDC(int Δx, int Δy, const ::double_rectangle &  pRectScoloroll, const ::double_rectangle &  lpRectClip,

      //                      ::draw2d::region* pregionUpdate, ::double_rectangle * pRectUpdate);


      // font Functions
//      virtual void GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, int * pBuffer);

//      virtual void GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, int * pBuffer);

//      virtual unsigned int SetMapperFlags(unsigned int dwFlag);
//      virtual ::double_size GetAspectRatioFilter();

// #ifdef WINDOWS_DESKTOP

//       virtual void GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC pabc);


// #endif

//      virtual unsigned int GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID pData, unsigned int cbData);


// #ifdef WINDOWS_DESKTOP

//       virtual int GetKerningPairs(int nPairs, LPKERNINGPAIR pkrnpair);

//       virtual unsigned int GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW potm);

//       virtual unsigned int GetGlyphOutline(unsigned int nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm, unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2);


//       virtual void GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABCFLOAT pABCF);


// #endif

      // virtual void GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, float * pFloatBuffer);


      // virtual unsigned int GetFontLanguageInfo();

//#if defined(WINDOWS_DESKTOP) && (_WIN32_WINNT >= 0x0500)
//
//      virtual void GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC pabc);
//
//      virtual void GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, int * pBuffer);
//
//
//#endif

      //// Printer/Device Escape Functions
      //virtual int Escape(int nEscape, int nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData);

      //virtual int Escape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData, int nOutputSize, char * pszOutputData);

      //virtual int DrawEscape(int nEscape, int nInputSize, const ::scoped_string & scopedstrInputData);


      // Escape helpers
      //virtual int StartDoc(const ::scoped_string & scopedstrDocName);  // old Win3.0 version


//#ifdef WINDOWS_DESKTOP
//
//      virtual int StartDoc(LPDOCINFOW pDocInfo);
//
//#endif

      virtual int StartPage();
      virtual int EndPage();
      //      virtual int SetAbortProc(void (CALLBACK* pfn)(HDC, int));

      virtual int AbortDoc();
      virtual int EndDoc();

      // MetaFile Functions
//#ifdef WINDOWS
//      virtual void PlayMetaFile(HMETAFILE hMF);
//      virtual void PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::double_rectangle &  pBounds);
//
//#endif
      virtual void AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData);
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
      //      virtual int GetPath(::double_point * ppoint, unsigned char * pTypes, ::collection::count nCount);

      virtual void SelectClipPath(int nMode);

      virtual void draw(::draw2d::path* ppath, ::draw2d::pen* ppen);
      virtual void draw(::draw2d::path* ppath);
      virtual void fill(::draw2d::path* ppath, ::draw2d::brush* pbrush);
      virtual void fill(::draw2d::path* ppath);
      virtual void path(::draw2d::path* ppath);

      virtual void intersect_clip(::draw2d::path* ppath);
      virtual void set_clip(::draw2d::path* ppath);

      // Misc helper Functions
      virtual ::draw2d::brush* GetHalftoneBrush();
      //virtual void DrawDragRect(const ::double_rectangle & rectangle, const ::double_size & ::double_size,

      //                          const ::double_rectangle &  pRectLast, const ::double_size & sizeLast,

      //                          ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);

      //virtual void fill_rectangle(const ::double_rectangle & rectangle, const ::color::color & color);
      //virtual void fill_rectangle(const double_rectangle & double_rectangle, const ::color::color & color);

      virtual void draw_inset_3d_rectangle(const ::double_rectangle& rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, double dWidth, const ::e_border& eborder = e_border_all);
      //virtual void draw_inset_3d_rectangle(const double_rectangle & double_rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      virtual void draw_inset_rectangle(const ::double_rectangle& rectangle, const ::color::color& color, double dWidth, const ::e_border& eborder = e_border_all);
      virtual void frame_rectangle(const ::double_rectangle& rectangle, const ::color::color& color, const ::e_border& eborder = e_border_all);
      //virtual void draw_rectangle(const double_rectangle & double_rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);

      virtual void set_font(::user::interaction* pinteraction, ::enum_element eelement = ::e_element_none, ::user::enum_state estate = ::user::e_state_none);


      virtual void get(::geometry2d::matrix& matrix);
      //using ::aura::simple_chain < ::aura::draw_context >::set;
      virtual void set(const ::geometry2d::matrix& matrix);
      virtual void append(const ::geometry2d::matrix& matrix);
      virtual void prepend(const ::geometry2d::matrix& matrix);
      virtual void update_matrix();
      //void _apply_offset() override;
      void _get(::draw2d::offset_context* poffsetcontext) override;
      void _set(::draw2d::offset_context* poffsetcontext) override;


      virtual void _get(::geometry2d::matrix& matrix);
      virtual void _set(const ::geometry2d::matrix& matrix);

      //=============================================================================
      //
      // draw_round_rectd()
      //
      // Purpose:     Draws a rounded rectdangle with a solid pen
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          double_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //          width    - [in]  width of the border
      //
      // Returns:     None
      //
      virtual void draw_round_rectangle(const ::double_rectangle& rectangle, ::draw2d::pen* ppen, double radius, const ::e_border& eborder);
      virtual void draw_round_rectangle(const ::double_rectangle& rectangle, ::draw2d::pen* ppen, double radius);
      //void draw_round_rect(const ::double_rectangle & rectangle, ::draw2d::pen * ppen, const ::double_point & point, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::double_rectangle & rectangle, ::draw2d::pen * ppen, int radius, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::double_rectangle & rectangle, ::draw2d::pen * ppen, int radius, const ::e_border & eborder = e_border_all);

      //void draw_round_rect(const ::double_rectangle & rectangle, const ::color::color & color, double radius, double width, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::double_rectangle & rectangle, const ::color::color & color, int radius, int width, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::double_rectangle & rectangle, const ::color::color & color, int radius, int width, const ::e_border & eborder = e_border_all);


      virtual void draw_stock_icon(const ::double_rectangle& double_rectangle, enum_stock_icon estockicon);


      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          double_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::double_rectangle& rectangle, const ::color::color& color, double radius);

      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          pBrush      - [in]  pointer to a Brush
      //          double_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the border (needed in case the
      //                         brush is a type other than solid)
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::double_rectangle& rectangle, ::draw2d::brush* pbrush, double radius);


      //void fill_round_rect(const ::double_rectangle & rectangle, ::draw2d::brush * pbrush, const ::double_point & point);


      //virtual void round_rectangle(const ::double_rectangle & rectangle, double radius);

      virtual int _DrawText(const ::scoped_string & scopedstr, const ::double_rectangle& rectangle, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none, ::write_text::font* pfontUnderline = nullptr);

      virtual void debug();




      //virtual float nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy);
      //virtual void nanosvg_cubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tol, int level);
      //virtual void nanosvg_drawPath(float* pts, int npts, char closed, float tol, const ::color::color& color);
      //virtual void nanosvg_drawControlPts(float* pts, int npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, int x, int y, int w, int h);
      // virtual void nanosvg_resizecb(int width, int height, int x, int y, int w, int h);

      virtual void nanosvg(string str, int x, int y, int w, int h);

      virtual void is_valid_update_window_thread();

      //virtual void set_current_point(double x, double y); // { return set_current_point(::double_point(x, y)); }
      //inline void set_current_point(double x, double y) { return set_current_point(::double_point(x, y)); }

      //inline void line_to(double x, double y) { return line_to(::double_point(x, y)); }
      //inline void line_to(double x, double y) { return line_to(::double_point(x, y)); }
      //virtual void line_to(double x, double y);// { return line_to(::double_point(x, y)); }

      //inline void draw_line(double x1, double y1, double x2, double y2) { return draw_line(::double_point(x1,y1), ::double_point(x2, y2)); }
      //inline void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::double_point(x1, y1), ::double_point(x2, y2), ppen); }

      ///virtual void draw_line(double x1, double y1, double x2, double y2); // { return draw_line(::double_point(x1, y1), ::double_point(x2, y2)); }
      //virtual void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_line(::double_point(x1, y1), ::double_point(x2, y2), ppen); }

      //inline void draw_line(double x1, double y1, double x2, double y2) { return draw_line(::double_point(x1, y1), ::double_point(x2, y2)); }
      //inline void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_line(::double_point(x1, y1), ::double_point(x2, y2), ppen); }

      //inline void rectdangle_coord(double x1, double y1, double x2, double y2) { return rectdangle(::double_rectangle(x1, y1, x2, y2)); }
      //inline void rectdangle_coord(double x1, double y1, double x2, double y2); // { return rectdangle(double_rectangle(x1, y1, x2, y2)); }

      //inline void rectdangle_dim(double x, double y, int cx, int cy) { return rectdangle(double_rectangle_dimension(x, y, cx, cy)); }
      //inline void rectdangle_dim(double x, double y, double cx, double cy); // { return rectdangle(rectdd_dim(x, y, cx, cy)); }

      //inline void draw_rect_coord(double x1, double y1, double x2, double y2) { return draw_rectangle(::double_rectangle(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) { return draw_rectangle(::double_rectangle(x1, y1, x2, y2), ppen); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2); // { return draw_rectangle(double_rectangle(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen); // { return draw_rectangle(double_rectangle(x1, y1, x2, y2), ppen); }

      //inline void draw_rect_dim(double x, double y, int cx, int cy) { return draw_rectangle(double_rectangle_dimension(x, y, cx, cy)); }
      //inline void draw_rect_dim(double x, double y, int cx, int cy, ::draw2d::pen * ppen) { return draw_rectangle(double_rectangle_dimension(x, y, cx, cy), ppen); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy); // { return draw_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy, ::draw2d::pen * ppen); // { return draw_rectangle(rectdd_dim(x, y, cx, cy), ppen); }

      //inline void fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rectangle(::double_rectangle(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rectangle(::double_rectangle(x1, y1, x2, y2), pbrush); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2); // { return fill_rectangle(double_rectangle(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(double x1, double y1, double x2, double y2, ::draw2d::brush * pbrush); // { return fill_rectangle(double_rectangle(x1, y1, x2, y2), pbrush); }

      //inline void fill_rect_dim(double x, double y, int cx, int cy) { return fill_rectangle(double_rectangle_dimension(x, y, cx, cy)); }
      //inline void fill_rect_dim(double x, double y, int cx, int cy, ::draw2d::brush * pbrush) { return fill_rectangle(double_rectangle_dimension(x, y, cx, cy), pbrush); }
      //inline void fill_rect_dim(double x, double y, double cx, double cy); // { return fill_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void fill_rect_dim(double x, double y, double cx, double cy, ::draw2d::brush * pbrush); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), pbrush); }

      //inline void polygon(int_point_array & pointa) { return polygon(pointa.data(), pointa.size()); }
      inline void polygon(double_point_array& pointa) { return polygon(pointa.data(), pointa.size()); }
      //inline void draw_polygon(int_point_array & pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      inline void draw_polygon(double_point_array& pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      //inline void fill_polygon(int_point_array & pointa) { return fill_polygon(pointa.data(), pointa.size()); }
      inline void fill_polygon(double_point_array& pointa) { return fill_polygon(pointa.data(), pointa.size()); }

      //inline void fill_solid_rect_dim(double x, double y, int cx, int cy, const ::color::color & color) { return fill_rectangle(double_rectangle_dimension(x, y, cx, cy), color); }
      //inline void fill_solid_rect_dim(double x, double y, double cx, double cy, const ::color::color & color); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), color); }

      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color::color & color) { return fill_rectangle(::double_rectangle(x1, y1, x2, y2), color); }
      //inline void fill_solid_rectd_coord(double x1, double y1, double x2, double y2, const ::color::color & color) { return fill_rectangle(double_rectangle(x1, y1, x2, y2), color); }

      //inline void draw_3drect_dim(double x, double y, int cx, int cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(double_rectangle_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_dim(double x, double y, double cx, double cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(double_rectangle_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_dim(double x, double y, int cx, int cy, const ::color::color& color) { return draw_rectangle(double_rectangle_dimension(x, y, cx, cy), color); }
      //inline void draw_rect_dim(double x, double y, double cx, double cy, const ::color::color& color) { return draw_rectangle(double_rectangle_dimension(x, y, cx, cy), color); }

      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(::double_rectangle(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_coord(double x1, double y1, double x2, double y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(double_rectangle(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color::color& color) { return draw_rectangle(::double_rectangle(x1, y1, x2, y2), color); }
      //inline void draw_rect_coord(double x1, double y1, double x2, double y2, const ::color::color& color) { return draw_rectangle(double_rectangle(x1, y1, x2, y2), color); }


   //protected:

     // friend class savedc;
      virtual int save_graphics_context();
      virtual void restore_graphics_context(int nSavedContext);

   };


   class CLASS_DECL_AURA save_context
   {
   public:


      graphics* m_pgraphics;
      int                     m_iSavedDC;

      ::double_size              m_sizeScaling;
      ::double_point             m_pointOrigin;
      ::geometry2d::matrix    m_matrix;

      save_context(graphics* graphics);
      ~save_context();


   };

   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_graphics();
   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_memory_graphics();

} // namespace draw2d


//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::double_size & size);
//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::double_point & point);



//CLASS_DECL_AURA PFN_factory ([a-z0-9_]+)_factory(::factory::factory * pfactory);

//CLASS_DECL_AURA void ([a-z0-9_]+)_factory(PFN_factory pfnfactoryDraw2d);
