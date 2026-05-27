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
   //concept graphics_source_pointer = requires(const ::image::image_drawing & imagedrawing, const ::f64_size & sizeHint)
   //{

   //   { pgraphicssource->g(sizeHint) } -> ::std::convertible_to < ::draw2d::graphics * >;
   //   { pgraphicssource->origin() } -> ::std::convertible_to < ::f64_size >;
   //   { pgraphicssource->i32_size(sizeHint) } -> ::std::convertible_to < ::f64_size >;

   //};

class graphics_context;

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
      ::i32                                          m_iYFlipHeight;
      // try to draw using paths and full prototypes
      // there is little control over lines drawn with move_to line_to than generalized
      //bool                                         m_bHasCurrentPoint;
      bool                                         m_bOutline;
      void* m_pthis;
      ::pointer < ::user::interaction >            m_puserinteractionDraw2dGraphics;
      ::pointer<::draw2d::host>                    m_pdraw2dhost;
      ::f64                                       m_dSizeScaler;
      bool                                         m_bPat;
      ///::image32_callback                           m_callbackImage32CpuBuffer;
      ::i32                                          m_iTargetLayer;
      ::i32                                          m_iLayer;

      //bool                                   m_bAlphaBlend;

      ::pointer<::text::context>          m_ptextcontext;
      ::aura::draw_context* m_pdrawcontext;
      ::image::image_pointer                        m_pimageAlphaBlend;
      ::f64_point                            m_pointAlphaBlend;
      ::pointer<::task>                     m_ptask;
      bool                                   m_bDraw;

      ::image::image* m_pimage = nullptr;
      ::draw2d::bitmap_pointer               m_pbitmap;
      ::draw2d::pen_pointer                  m_ppen;
      ::draw2d::brush_pointer                m_pbrush;
      ::draw2d::region_pointer               m_pregion;
      bool                                   m_bStoreThumbnails;

      ::f64_point                            m_point;

   protected:
      //bool                                   _m_bYFlip;
      enum_alpha_mode                        m_ealphamode;


   public:
      enum_fill_mode                         m_efillmode;
      enum_smooth_mode                          m_esmoothmode;
      enum_interpolation_mode                m_einterpolationmode;
      enum_compositing_quality                  m_ecompositingquality;
      ::write_text::enum_rendering           m_ewritetextrendering;
      //::f64                                 m_dFontFactor;

      ::f64_size                             m_sizeScaling;
      ::f64_point                            m_pointOrigin;
      ::f64_size                             m_sizeImpact2;
      ::f64_size                             m_sizeTotal2;
      ::geometry2d::matrix                      m_matrix;
      ::f64_size                             m_sizeScaleOutput;
      ::f64_point                            m_pointTranslateOutput;

      ::f64_rectangle                        m_rectangleDraw;

      bool                                   m_bPrinting;
      void* m_osdata[8];
      ::user::style_pointer                  m_puserstyleGraphics;
      //::f64_point                            m_pointAddShapeTranslate;
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

      virtual ::f64 size_scaler();
      virtual void set_size_scaler(::f64 dSizeScaler);

      //virtual void send_on_context(::draw2d::graphics_context * pgraphicscontext, const ::procedure& procedure);


      virtual void send_on_context(::draw2d::graphics_context * pgraphicscontext, const ::procedure & procedure);


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
      inline T* get_os_data(::i8 i = 0) const
      {

         return (T*)m_osdata[i];

      }


      inline void* get_os_data(::i8 i = 0) const
      {

         return get_os_data < void >(i);

      }

      using image_drawer::draw;
      using write_text::drawer::draw;

      virtual ::file::path get_font_path(const ::scoped_string & scopedstrName, ::i32 iWeight, bool bItalic);

      //virtual oswindow get_window_handle() const;
      virtual void defer_snapshot_for_composition();


      inline ::draw2d::graphics* g(const ::f64_size& sizeHint) { return this; }
      inline ::f64_size origin() const { return ::f64_size(); }

      bool _is_ok() const override;

      ::image::image_pointer image_source_image(const ::i32_size& sizeDst) override;

      ::i32_size image_source_size(const ::f64_size& sizeDst, enum_image_selection eimageselection) const override;

      ::i32_size image_source_size() const override;


      //virtual void start_gpu_layer(const ::i32_rectangle & rectangleTarget);

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

      virtual bool fill_contains(const ::f64_point& point);

      void draw_ca2(::i32 x, ::i32 y, ::i32 z, const ::color::color& colorBk, const ::color::color& color);
      void draw_ca2_with_border(::i32 x, ::i32 y, ::i32 z, ::i32 b, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorOut);
      void draw_ca2_border2(::i32 x, ::i32 y, ::i32 z, ::i32 bOut, ::i32 bIn, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorBorderOut, const ::color::color& colorIn);
      void draw_ca2_with_border2(::i32 x, ::i32 y, ::i32 z, ::i32 bOut, ::i32 bIn, const ::color::color& colorBk, const ::color::color& color, const ::color::color& colorBorderOut, const ::color::color& colorIn);


      void draw_border(const ::f64_rectangle& rectangle, const ::color::color& color, ::i32 iWidth);
      void draw_rect_side(const ::f64_rectangle& rectangle, enum_border eborder);

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

      virtual void blur(bool bExpand, ::f64 dRadius, const ::f64_rectangle& rectangle);

      virtual void set_solid_pen(::f64 dWidth, const ::color::color& color);

      //virtual void IsPrinting();            // true if being used for printing

      virtual ::draw2d::pen* get_current_pen();
      virtual ::draw2d::brush* get_current_brush();
      virtual ::draw2d::palette* get_current_palette();
      virtual ::draw2d::bitmap* get_current_bitmap();






      // for bidi and mirrored localization
      virtual ::u32 GetLayout();
      virtual ::u32 SetLayout(::u32 dwLayout);

      // Constructors
      virtual void create_device_context(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void* lpInitData);

      virtual void create_information_context(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void* lpInitData);

      virtual void create_window_graphics(::windowing::window* pwindow);
      virtual void create_offscreen_graphics_for_swap_chain_blitting(::user::interaction* puserinteraction, const ::i32_size& size = {});
      virtual void create_memory_graphics(const ::i32_size& sizeParameter);
      virtual void create_for_window_draw2d(::user::interaction * puserinteraction, const ::i32_size& size = {});
      virtual void defer_set_size(const ::i32_size& size = {});
      virtual void _create_memory_graphics(const ::i32_size& size = {});
      virtual void create_compatible_graphics(::draw2d::graphics* pgraphics);
      virtual void create_window_graphics(const ::operating_system::window & operatingsystemwindow);


      virtual ::pointer < ::draw2d::path > create_path();
      virtual ::pointer < ::draw2d::pen > create_solid_pen(::f64 dWidth, const ::color::color & color);
      virtual ::pointer < ::draw2d::brush > create_solid_brush(const ::color::color & color);

      //virtual void set_hint_window_output();

      virtual void defer_resize_memory_graphics(const ::i32_size& size);

      virtual void on_begin_draw(::acme::windowing::window * pacmewindowingwindow, const ::f64_size& sz);
      virtual void on_end_draw(::acme::windowing::window * pacmewindowingwindow);
      virtual void on_present();

      virtual void DeleteDC();


      // Device-Context Functions
      virtual ::i32 GetDeviceCaps(::i32 nIndex);
      virtual ::u32 SetBoundsRect(const ::f64_rectangle& rectangleBounds, ::u32 flags);
      virtual ::u32 GetBoundsRect(::f64_rectangle* rectdBounds, ::u32 flags);


      virtual void resize(const ::i32_size& sizeWindow);



      //#ifdef WINDOWS
      //      virtual void ResetDC(const DEVMODE* pDevMode);
      //
      //#endif

            // Drawing-Tool Functions
      virtual ::f64_point GetBrushOrg();
      virtual ::f64_point SetBrushOrg(::f64 x, ::f64 y);
      virtual ::f64_point SetBrushOrg(const ::f64_point& point);
      //virtual ::i32 EnumObjects(::i32 nObjectType,
                              //::i32 (CALLBACK* pfn)(LPVOID, lparam), lparam lpData);



      virtual void set_text_color(::color::color color);


      using ::write_text::drawer::set;
      virtual void set(::draw2d::region* pregion);
      virtual void set(::draw2d::pen* ppen);
      virtual void set(::draw2d::brush* pbrush);
      virtual void set(::draw2d::bitmap* pbitmap);
      virtual ::draw2d::object* set_stock_object(::i32 nIndex);


      // color and color Palette Functions
      //virtual ::color::color GetNearestColor(const ::color::color & color);
      //virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, void bForceBackground);
      //virtual ::u32 RealizePalette();
      //virtual void UpdateColors();

      // Drawing-Attribute Functions
      //virtual ::i32 GetPolyFillMode();
      //virtual ::i32 GetROP2();
      //virtual ::i32 GetStretchBltMode();


      virtual ::f64 get_dpix();
      virtual ::f64 get_dpiy();

      //virtual ::i32 SetPolyFillMode(::i32 nPolyFillMode);
      //virtual ::i32 SetROP2(::i32 nDrawMode);
//      virtual void set_interpolation_mode(enum_interpolation_mode einterpolationmode);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual void flush();
      virtual void sync_flush();


      virtual ::f64_size get_size() const;

      ::i32_size get_image_drawer_size() const override;







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
            //virtual ::i32 SetGraphicsMode(::i32 iMode);
            //virtual ::i32 GetGraphicsMode();

      //      // World transform
      //#ifdef WINDOWS
      //      virtual void SetWorldTransform(const XFORM* pXform);
      //      virtual void ModifyWorldTransform(const XFORM* pXform,::u32 iMode);
      //      virtual void GetWorldTransform(XFORM* pXform);
      //#endif

      virtual ::f64_size get_scaling();

      // Mapping Functions
      ///virtual ::i32 GetMapMode();
      ///virtual ::f64_point _get_origin();
      //virtual ::i32 SetMapMode(::i32 nMapMode);
      // Context Origin
      //virtual void _set_origin(::f64 x, ::f64 y);
      //virtual void _set_origin(const ::f64_point& ::f64_point);
      //virtual void _offset_origin(::f64 x, ::f64 y);


      virtual void reset_impact_area();
      virtual void place_impact_area(::f64 x, ::f64 y, ::f64 w, ::f64 h);
      virtual void place_impact_area(const ::f64_point& pointImpactArea, const ::f64_size & sizeImpactArea);
      virtual void place_impact_area(const ::f64_rectangle& rectangleImpactArea);
      void shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h) override;
      virtual void shift_impact_area(const ::f64_size& shiftImpactArea, const ::f64_size& sizeImpactArea);
      virtual void shift_impact_area(const ::f64_rectangle& rectangleImpactArea);


      virtual ::f64_size impact_size();
      virtual ::f64_size total_size();


      void x_offset(::f64 dx) override;
      void y_offset(::f64 dy) override;
      void offset(::f64 dx, ::f64 dy) override;
      virtual void _x_offset(::f64 dx);
      virtual void _y_offset(::f64 dy);
      virtual void _offset(::f64 dx, ::f64 dy);
      virtual void offset(const ::f64_size& size);

      
      // Context Extent
      virtual ::f64_size get_extents();
      virtual ::f64_size set_extents(::f64 cx, ::f64 cy);
      virtual ::f64_size set_extents(const ::f64_size& size);
      virtual ::f64_size scale_extents(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom);

      // Window Origin
      virtual ::f64_point GetWindowOrg();
      virtual ::f64_point SetWindowOrg(::f64 x, ::f64 y);
      virtual ::f64_point SetWindowOrg(const ::f64_point& point);
      virtual ::f64_point offset_window_org(::f64 nWidth, ::f64 nHeight);

      // Window extent
      virtual ::f64_size GetWindowExt();
      //virtual ::f64_size set_window_ext(::f64 cx, ::f64 cy);
      //virtual ::f64_size set_window_ext(const ::f64_size& size);
      //virtual ::f64_size scale_window_ext(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom);

      // Coordinate Functions
      virtual void DPtoLP(::f64_point* ppoint, ::collection::count nCount = 1);
      virtual void DPtoLP(::f64_rectangle* prectd);

      virtual void DPtoLP(::f64_size* pSize);

      virtual void LPtoDP(::f64_point* ppoint, ::collection::count nCount = 1);
      virtual void LPtoDP(::f64_rectangle* prectd);

      virtual void LPtoDP(::f64_size* pSize);


      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(::f64_size* pSize);

      virtual void LPtoHIMETRIC(::f64_size* pSize);

      virtual void HIMETRICtoDP(::f64_size* pSize);

      virtual void HIMETRICtoLP(::f64_size* pSize);


      // Region Functions
      virtual void fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush);
      virtual void frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, ::f64 nWidth, ::f64 nHeight);
      virtual void invert_region(::draw2d::region* pregion);
      virtual void paint_region(::draw2d::region* pregion);

      // Clipping Functions
      virtual ::i32 get_clip_box(::f64_rectangle& rectangle);

      //virtual ::i32 get_clip_box(::f64_rectangle * prectangle);

      //virtual void PtVisible(::f64 x, ::f64 y);
      //virtual void PtVisible(const ::f64_point & point);
      //virtual void RectVisible(const ::f64_rectangle & rectangle);



      //virtual void add_clipping_shapes(const pointer_array < ::draw2d::region > & regiona);
      virtual void reset_clip();


      //virtual void set_clipping(::draw2d::region * pregion);

      virtual void intersect_clip(const ::f64_rectangle& rectangle);
      virtual void intersect_clip(const ::f64_ellipse& ellipse);
      virtual void intersect_clip(const ::f64_polygon_base& polygon);


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
      virtual void _add_shape(const ::f64_rectangle& rectangle);
      virtual void _add_shape(const ::f64_ellipse& ellipse);
      virtual void _add_shape(const ::f64_polygon_base& polygon);

      //virtual void IntersectClipregion(::draw2d::region * pregion);
      //virtual void IntersectClipRect(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      //virtual void IntersectClipRect(const ::f64_rectangle & rectangle);
      //virtual ::i32 ExcludeClipRect(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      //virtual ::i32 ExcludeClipRect(const ::f64_rectangle & rectangle);
      //virtual ::i32 ExcludeUpdateRgn(::windowing::window * pwindow);
      //virtual ::i32 OffsetClipregion(::f64 x, ::f64 y);
      //virtual ::i32 OffsetClipregion(const ::f64_size & ::f64_size);
      //virtual ::i32 SelectClipregion(::draw2d::region* pregion, ::draw2d::enum_combine ecombine);

      virtual void on_apply_clip_region();

      virtual ::f64_point current_position();

      //inline void set_current_point(::f64 x, ::f64 y)
      //{

      //   return set_current_point({ x, y });

      //}


      //virtual void set_current_point(::f64 x, ::f64 y);
      //virtual void line_to(::f64 x, ::f64 y);
      virtual void line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      virtual void line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen* ppen);


      //inline void set_current_point(const ::f64_point& point)
      //{

      //   return set_current_point(point.x, point.y);

      //}


      //virtual void line_to(const ::f64_point& point)
      //{

      //   return line_to(point.x, point.y);

      //}

      template< typename POINT>
      void process_line(POINT & pointLast, const POINT & pointNow)
      {

         line(pointLast, pointNow);
         pointLast = pointNow;

      }

      inline void line(const ::f64_point& point1, const ::f64_point& point2)
      {

         return line(point1.x, point1.y, point2.x, point2.y);

      }


      inline void line(const ::f64_point& point1, const ::f64_point& point2, ::draw2d::pen* ppen)
      {

         return line(point1.x, point1.y, point2.x, point2.y, ppen);

      }


      virtual void draw_error_line(::f64 x1, ::f64 h, ::f64 x2, ::i32 iStyle);


      virtual void arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4);
      virtual void arc(const ::f64_rectangle& rectangle, const ::f64_point& pointStart, const ::f64_point& pointEnd);
      virtual void arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64_angle start, ::f64_angle extends);
      virtual void arc(const ::f64_rectangle& rectangle, ::f64_angle start, ::f64_angle extends);


      virtual void polyline(const ::f64_point_array& pointa);
      virtual void polyline(const ::f64_point* ppoints, ::collection::count nCount);


      //      virtual void arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4);
      //      virtual void arc(const ::f64_rectangle & ::f64_rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd);

      //      virtual void arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, angle start, angle extends);
      //      virtual void arc(const ::f64_rectangle & ::f64_rectangle, angle start, angle extends);


      virtual void angle_arc(::f64 x, ::f64 y, ::f64 nRadius, ::f64_angle fStartAngle, ::f64_angle fSweepAngle);
      virtual void arc_to(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4);
      virtual void arc_to(const ::f64_rectangle& rectangle, const ::f64_point& pointStart, const ::f64_point& pointEnd);
      //virtual ::i32 GetArcDirectdion();
      //virtual ::i32 SetArcDirectdion(::i32 nArcDirectdion);

      virtual void polydraw(const ::f64_point* ppoints, const ::u8* pTypes, ::collection::count nCount);

      virtual void polyline_to(const ::f64_point* ppoints, ::collection::count nCount);
      virtual void poly_polyline(const ::f64_point* ppoints, const ::i32* pPolyPoints, ::collection::count nCount);


      virtual void poly_bezier(const ::f64_point* ppoints, ::collection::count nCount);
      virtual void poly_bezier_to(const ::f64_point* ppoints, ::collection::count nCount);


      virtual void frame_rectangle(const ::f64_rectangle& rectangle, ::draw2d::brush* pbrush);
      virtual void invert_rectangle(const ::f64_rectangle& rectangle);

      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,::draw2d::brush* pBrush = nullptr);
      //#ifdef WINDOWS
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, hicon hIcon, ::u32 nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, hicon hIcon, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
      //#endif
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, const ::scoped_string & scopedstrText, ::u32 nFlags,

        //                           void bPrefixText = true, ::i32 nTextLen = 0, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, const ::scoped_string & scopedstrText, ::u32 nFlags,
      //
      //                             void bPrefixText = true, ::i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr);
      //#ifdef WINDOWS_DESKTOP
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, DRAWSTATEPROC pDrawProc,
      //
      //                             lparam lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
      //      virtual void DrawState(const ::f64_point & point, const ::f64_size & ::f64_size, DRAWSTATEPROC pDrawProc,
      //
      //                             lparam lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);
      //#endif
            // Ellipse and Polygon Functions
      virtual void Chord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3,
         ::f64 x4, ::f64 y4);
      virtual void Chord(const ::f64_rectangle& rectangle, const ::f64_point& pointStart, const ::f64_point& pointEnd);

      virtual void DrawFocusRect(const ::f64_rectangle& rectangle);

      /*  virtual void ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
        virtual void ellipse(const ::f64_rectangle & ::f64_rectangle);

        virtual void draw_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
        virtual void draw_ellipse(const ::f64_rectangle & ::f64_rectangle);

        virtual void fill_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
        virtual void fill_ellipse(const ::f64_rectangle & ::f64_rectangle);*/





      virtual void ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      virtual void ellipse(const ::f64_rectangle& prectd);

      virtual void draw_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      virtual void draw_ellipse(const ::f64_rectangle& prectd);

      virtual void fill_ellipse(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      virtual void fill_ellipse(const ::f64_rectangle& prectd);


      virtual void Pie(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4);
      virtual void Pie(const ::f64_rectangle& rectangle, const ::f64_point& pointStart, const ::f64_point& pointEnd);


      //virtual void i32_polygon(const ::f64_point * ppoints, ::collection::count nCount);
      virtual void polygon(const ::f64_point* ppoints, ::collection::count nCount);
      //virtual void draw_polygon(const ::f64_point * ppoints, ::collection::count nCount);
      virtual void draw_polygon(const ::f64_point* ppoints, ::collection::count nCount);
      //virtual void fill_polygon(const ::f64_point * ppoints,count nCount);
      virtual void fill_polygon(const ::f64_point* ppoints, ::collection::count nCount);

      //virtual void poly_polygon(const ::f64_point * ppoints, const ::i32 * pPolyCounts, ::collection::count nCount);
      virtual void poly_polygon(const ::f64_point* ppoints, const ::i32* pPolyCounts, ::collection::count nCount);
      //virtual void draw_poly_polygon(const ::f64_point * ppoints, const ::i32 * pPolyCounts, ::collection::count nCount);
      virtual void draw_poly_polygon(const ::f64_point* ppoints, const ::i32* pPolyCounts, ::collection::count nCount);
      //virtual void fill_poly_polygon(const ::f64_point * ppoints, const ::i32 * pPolyCounts, ::collection::count nCount);
      virtual void fill_poly_polygon(const ::f64_point* ppoints, const ::i32* pPolyCounts, ::collection::count nCount);


      virtual void rectangle(const ::f64_rectangle& rectangle);

      virtual void frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color, ::i32 width);

      virtual void draw_rectangle(const ::f64_rectangle& rectangle);
      virtual void draw_rectangle(const ::f64_rectangle& rectangle, ::draw2d::pen* ppen);

      virtual void fill_rectangle(const ::f64_rectangle& rectangle);
      virtual void fill_rectangle(const ::f64_rectangle& rectangle, ::draw2d::brush* pbrush);
      virtual void fill_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color);
      virtual void fill_inset_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color);
      virtual void fill_solid_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color);

      virtual void color_blend_3dRect(const i32_rectangle& rectangleParam, const ::color::color& colorTopLeft, const class ::opacity& opacityTopLeft, const ::color::color& color, const class ::opacity& opacityBottomRight);

      //virtual void color_blend(const ::i32_rectangle& rectangle, const ::color::color& color, const ::opacity & opacity);

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
//         if (!color_blend(::i32_rectangle(pimagesource->size()), color, opacity))
//         {
//
//            return false;
//
//         }
//
//         return true;
//
//      }



      //virtual void i32_rectangle(const ::f64_rectangle & ::f64_rectangle);
      //virtual void draw_rectangle(const ::f64_rectangle & ::f64_rectangle);
      //virtual void draw_rectangle(const ::f64_rectangle & ::f64_rectangle, ::draw2d::pen * ppen);
      //virtual void fill_rectangle(const ::f64_rectangle & ::f64_rectangle);
      //virtual void fill_rectangle(const ::f64_rectangle & ::f64_rectangle, ::draw2d::brush * pbrush);

      //virtual void round_rectd(const ::f64_rectangle & rectangle, const ::f64_point & point);

      virtual void round_rectangle(const ::f64_rectangle& rectangle, ::f64 dRadius);


      //virtual void from(const ::f64_point & pointDst, const ::f64_size & ::f64_size, ::draw2d::graphics * pgraphicsSrc, const ::f64_point & pointSrc);
      //virtual void from(const ::f64_size & ::f64_size, ::draw2d::graphics * pgraphicsSrc, const ::f64_point & pSrc);
      //virtual void from(const ::f64_size & ::f64_size, ::draw2d::graphics * pgraphicsSrc);
      //virtual void PatBlt(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight);



      //virtual void draw_image(const ::f64_rectangle & rectangle, ::draw2d::graphics * pgraphicsSrc, const ::f64_point & point);

      //virtual void draw_image(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangle);
      //virtual void draw_image(const ::f64_rectangle & rectdDst, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangle);
      //virtual void draw_image(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource);
      // virtual void draw_image(const ::f64_rectangle & rectddDst, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource);


      // bit block transfer (pixel-to-pixel)
      //virtual void draw_at(const ::f64_point & pointDst, ::image::image *pimage);
      //virtual void draw_at(const ::f64_point & pointDst, ::image::image_frame * pframe);
      //virtual void draw_at(const ::f64_point & pointDst, ::draw2d::graphics * pgraphicsSrc);


      bool has_blender() const override;

      bool _draw_blend(const ::image::image_drawing& imagedrawing) override;


      //virtual void _draw(const ::f64_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::f64_rectangle & rectangleSource) override;
      //virtual void _draw_raw(const ::f64_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::f64_rectangle & rectangleSource) override;
      //virtual void _draw_blend(const ::f64_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::f64_rectangle & rectangleSource) override;

      //
      //virtual void _draw_raw(const ::f64_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::f64_point & pointSrc) override;
      //virtual void _stretch_raw(const ::f64_rectangle & rectangleTarget, const ::image::image_drawing & imagedrawing, const ::f64_rectangle & rectangleSource) override;




      // potentially stretching
      //virtual void stretch(const ::f64_rectangle & rectangleTarget, ::image::image *pimage, const ::f64_rectangle & rectangleSource = ::f64_rectangle());
      //virtual void stretch(const ::f64_rectangle & rectangleTarget, ::image::image_frame * pframe, const ::f64_rectangle & rectangleSource = ::f64_rectangle());
      //virtual void stretch(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource = ::f64_rectangle());
      //virtual void stretch_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource = ::f64_rectangle());
      //virtual void stretch_blend(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource = ::f64_rectangle());


      //template < prototype_size SIZE >
      //inline void alpha_blend(const SIZE & sizeDst, const ::image::image_drawing & imagedrawing, ::f64 dOpacity)
      //{

      //   auto finalSrcSize = pimagesource->i32_size(sizeDst, sizeSrc, eimageselection);

      //   auto pimage = pimagesource->get_image(sizeSrc);

      //   return _alpha_blend(::f64_rectangle(sizeDst), pgraphicssource, ::f64_rectangle(sizeDst), dOpacity);

      //}


      //template < prototype_rectangle RECTANGLE >
      //inline void alpha_blend(const RECTANGLE & rectangleTarget, const ::image::image_drawing & imagedrawing, ::f64 dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, ::f64_rectangle(rectangleTarget.size()), dOpacity);

      //}

      //
      //template < prototype_rectangle RECTANGLE, prototype_point POINT >
      //inline void alpha_blend(const RECTANGLE & rectangleTarget, const ::image::image_drawing & imagedrawing, const POINT & pointSrc, ::f64 dOpacity)
      //{

      //   if (::is_null(pgraphicssource))
      //   {

      //      return false;

      //   }

      //   auto sizeDst = rectangleTarget.size() - pointSrc;

      //   return _alpha_blend(::f64_rectangle(rectangleTarget.top_left(), sizeDst), pgraphicssource, ::f64_rectangle(pointSrc, pgraphicssource->i32_size(sizeDst) - pointSrc), dOpacity);

      //}


      //template < prototype_rectangle RECTANGLE_DST, prototype_rectangle RECTANGLE_SRC >
      //inline void alpha_blend(const RECTANGLE_DST & rectangleTarget, const ::image::image_drawing & imagedrawing, const RECTANGLE_SRC & rectangleSource, ::f64 dOpacity)
      //{

      //   return _alpha_blend(rectangleTarget, pgraphicssource, rectangleSource, dOpacity);

      //}


      //virtual void _alpha_blend(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource, ::f64 dOpacity);
      //virtual void _alpha_blend_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource, ::f64 dRate);
      //virtual void _alpha_blend_blend(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource, ::f64 dRate);


      //virtual void draw(const ::f64_rectangle & point, cursor * pcursor);
      //virtual void draw(const ::f64_rectangle & rectangleTarget, icon * picon);



      virtual ::color::color GetPixel(::f64 x, ::f64 y);
      virtual ::color::color GetPixel(const ::f64_point& point);
      virtual ::color::color SetPixel(::f64 x, ::f64 y, const ::color::color& color);
      virtual ::color::color SetPixel(const ::f64_point& point, const ::color::color& color);
      virtual ::color::color blend_pixel(const ::f64_point& point, const ::color::color& color);
      //      virtual void FloodFill(::f64 x, ::f64 y, const ::color::color & color);
      //      virtual void ExtFloodFill(::f64 x, ::f64 y, const ::color::color & color, ::u32 nFillType);
      //      virtual void MaskBlt(::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
      //                           ::f64 xSrc, ::f64 ySrc, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::f64 yMask,
      //                           ::u32 dwRop);
      //      virtual void PlgBlt(::f64_point * pPoint, ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::f64 ySrc,
      //
      //                          ::i32 nWidth, ::i32 nHeight, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::f64 yMask);
      virtual void SetPixelV(::f64 x, ::f64 y, const ::color::color& color);
      virtual void SetPixelV(const ::f64_point& point, const ::color::color& color);
      //virtual void GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
      //void * pMesh, WINULONG nMeshElements, ::u32 dwMode);
//      virtual void TransparentBlt(::f64 xDest, ::f64 yDest, ::i32 nDestWidth, ::i32 nDestHeight,
//                                  ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::f64 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight,
//                                  ::u32 clrTransparent);



      // Text Functions
      //virtual void text_out(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount);

      inline void text_out(const ::f64_point& point, const ::scoped_string& scopedstr)
      {

         return text_out(point.x, point.y, scopedstr);

      }

      virtual void text_out(::f64 x, ::f64 y, const ::scoped_string& scopedstr);
      //virtual void ExtTextOut(::f64 x, ::f64 y, ::u32 nOptions, const ::f64_rectangle & rectangle, const ::scoped_string & scopedstrString, character_count nCount, ::i32 * lpDxWidths);

      //virtual void ExtTextOut(::f64 x, ::f64 y, ::u32 nOptions, const ::f64_rectangle & rectangle, const ::scoped_string & scopedstr, ::i32 * lpDxWidths);

      //virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions, ::i32 nTabOrigin);

      //virtual ::f64_size TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * pnTabStopPositions, ::i32 nTabOrigin);


      void TextOutRaw(::f64 x, ::f64 y, const ::scoped_string& scopedstr) override;

      virtual bool TextOutAlphaBlend(::f64 x, ::f64 y, const ::scoped_string& scopedstr);


      virtual void _001DrawText(const ::scoped_string & scopedstr, ::f64_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none, bool bMeasure = false);


      virtual void draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none);

      //virtual void draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);


#ifndef UNIVERSAL_WINDOWS

//      virtual void draw_text_ex(const ::scoped_string & scopedstr,const ::f64_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

//      virtual void draw_text_ex(const ::scoped_string & scopedstr,const ::f64_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none,LPDRAWTEXTPARAMS lpDTParams = nullptr);

      virtual void draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle& prectd, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none);

      //virtual void draw_text_ex(const ::scoped_string & scopedstr,const ::f64_rectangle & prectd, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);

#endif


      virtual ::collection::count get_character_extent(f64_array& daLeft, f64_array& daRight, const ::scoped_string & scopedstr, character_count iStart = 0, character_count iCount = -1);

      //virtual ::f64_size get_text_extent(const ::scoped_string & scopedstrString);

      ::f64_size get_text_extent(const ::scoped_string& scopedstr) override;

      virtual ::f64_size _get_text_extent(const ::scoped_string& scopedstr);

      virtual ::f64_size get_text_extent(const ::scoped_string& scopedstr, ::character_count iIndex);

      virtual ::f64_size _get_text_extent(const ::scoped_string& scopedstr, ::character_count iIndex);

      virtual ::f64_size GetTextBegin(const ::scoped_string& scopedstrString, ::character_count iIndex);

      //virtual ::f64_size get_text_extent(const ::scoped_string & scopedstrString, character_count nCount);

      //virtual void get_text_extent(::f64_size & size, const ::scoped_string & scopedstrString, character_count nCount, character_count iIndex);

      //virtual void get_text_extent(::f64_size & size, const ::scoped_string & scopedstrString, character_count nCount);

      //virtual void get_text_extent(::f64_size & size, const ::scoped_string & scopedstr);
      //virtual ::f64_size GetOutputTextExtent(const ::scoped_string & scopedstrString, character_count nCount);

      //virtual ::f64_size GetOutputTextExtent(const ::scoped_string & scopedstr);
      //virtual ::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions);

      //virtual ::f64_size GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * pnTabStopPositions);

      //virtual ::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, ::i32 * lpnTabStopPositions);

      //virtual ::f64_size GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, ::i32 * pnTabStopPositions);

      //virtual void GrayString(::draw2d::brush* pBrush, void (CALLBACK* pfnOutput)(HDC, lparam, ::i32), lparam lpData, ::i32 nCount, ::f64 x, ::f64 y, ::i32 nWidth, ::i32 nHeight);

      virtual ::u32 GetTextAlign();
      virtual ::u32 SetTextAlign(::u32 nFlags);
      //virtual ::i32 GetTextFace(count nCount, char_pointer pszFacename);

      //virtual ::i32 GetTextFace(string & rString);

      using ::write_text::drawer::get_text_metrics;
      void get_text_metrics(::write_text::text_metric* pmetrics) override;
      virtual void get_output_text_metrics(::write_text::text_metric* pMetrics);



      //virtual ::i32 SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount);
      //virtual ::i32 GetTextCharacterExtra();
      //virtual ::i32 SetTextCharacterExtra(::i32 nCharExtra);

// #ifdef WINDOWS_DESKTOP

//       virtual ::u32 GetCharacterPlacement(const ::scoped_string & scopedstrString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags);

//       virtual ::u32 GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS pResults, ::u32 dwFlags);


// #endif

// #if (_WIN32_WINNT >= 0x0500)

//       virtual void get_text_extentExPointI(LPWORD pgiIn, ::i32 cgi, ::i32 nMaxExtent, ::i32 * pnFit, ::i32 * alpDx, __out_opt ::f64_size * ::f64_size *);

//       virtual void get_text_extentPointI(LPWORD pgiIn, ::i32 cgi, __out_opt ::f64_size * pSize);


// #endif

//
//
//  /*    // Advanced Drawing
//      virtual void DrawEdge(const ::f64_rectangle & prectd,::u32 nEdge,::u32 nFlags);
//
//      virtual void DrawFrameControl(const ::f64_rectangle & prectd,::u32 nType,::u32 nState);
//*/

      //// Scolorolling Functions
      //virtual void ScrollDC(::i32 Δx, ::i32 Δy, const ::f64_rectangle &  pRectScoloroll, const ::f64_rectangle &  lpRectClip,

      //                      ::draw2d::region* pregionUpdate, ::f64_rectangle * pRectUpdate);


      // font Functions
//      virtual void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, ::i32 * pBuffer);

//      virtual void GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, ::i32 * pBuffer);

//      virtual ::u32 SetMapperFlags(::u32 dwFlag);
//      virtual ::f64_size GetAspectRatioFilter();

// #ifdef WINDOWS_DESKTOP

//       virtual void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC pabc);


// #endif

//      virtual ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID pData, ::u32 cbData);


// #ifdef WINDOWS_DESKTOP

//       virtual ::i32 GetKerningPairs(::i32 nPairs, LPKERNINGPAIR pkrnpair);

//       virtual ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW potm);

//       virtual ::u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS pgm, ::u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2);


//       virtual void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT pABCF);


// #endif

      // virtual void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, ::f32 * pFloatBuffer);


      // virtual ::u32 GetFontLanguageInfo();

//#if defined(WINDOWS_DESKTOP) && (_WIN32_WINNT >= 0x0500)
//
//      virtual void GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC pabc);
//
//      virtual void GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, ::i32 * pBuffer);
//
//
//#endif

      //// Printer/Device Escape Functions
      //virtual ::i32 Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData);

      //virtual ::i32 Escape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData, ::i32 nOutputSize, char_pointer pszOutputData);

      //virtual ::i32 DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData);


      // Escape helpers
      //virtual ::i32 StartDoc(const ::scoped_string & scopedstrDocName);  // old Win3.0 version


//#ifdef WINDOWS_DESKTOP
//
//      virtual ::i32 StartDoc(LPDOCINFOW pDocInfo);
//
//#endif

      virtual ::i32 StartPage();
      virtual ::i32 EndPage();
      //      virtual ::i32 SetAbortProc(void (CALLBACK* pfn)(HDC, ::i32));

      virtual ::i32 AbortDoc();
      virtual ::i32 EndDoc();

      // MetaFile Functions
//#ifdef WINDOWS
//      virtual void PlayMetaFile(HMETAFILE hMF);
//      virtual void PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::f64_rectangle &  pBounds);
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
      virtual ::f32 GetMiterLimit();
      virtual void SetMiterLimit(::f32 fMiterLimit);
      //      virtual ::i32 GetPath(::f64_point * ppoint, ::u8 * pTypes, ::collection::count nCount);

      virtual void SelectClipPath(::i32 nMode);

      virtual void draw(::draw2d::path* ppath, ::draw2d::pen* ppen);
      virtual void draw(::draw2d::path* ppath);
      virtual void fill(::draw2d::path* ppath, ::draw2d::brush* pbrush);
      virtual void fill(::draw2d::path* ppath);
      virtual void path(::draw2d::path* ppath);

      virtual void intersect_clip(::draw2d::path* ppath);
      virtual void set_clip(::draw2d::path* ppath);

      // Misc helper Functions
      virtual ::draw2d::brush* GetHalftoneBrush();
      //virtual void DrawDragRect(const ::f64_rectangle & rectangle, const ::f64_size & ::f64_size,

      //                          const ::f64_rectangle &  pRectLast, const ::f64_size & sizeLast,

      //                          ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr);

      //virtual void fill_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color);
      //virtual void fill_rectangle(const ::f64_rectangle & ::f64_rectangle, const ::color::color & color);

      virtual void draw_inset_3d_rectangle(const ::f64_rectangle& rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, ::f64 dWidth, const ::e_border& eborder = e_border_all);
      //virtual void draw_inset_3d_rectangle(const ::f64_rectangle & ::f64_rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder = e_border_all);

      virtual void draw_inset_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color, ::f64 dWidth, const ::e_border& eborder = e_border_all);
      virtual void frame_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color, const ::e_border& eborder = e_border_all);
      //virtual void draw_rectangle(const ::f64_rectangle & ::f64_rectangle, const ::color::color& color, const ::e_border & eborder = e_border_all);

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
      //          ::f64_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //          width    - [in]  width of the border
      //
      // Returns:     None
      //
      virtual void draw_round_rectangle(const ::f64_rectangle& rectangle, ::draw2d::pen* ppen, ::f64 radius, const ::e_border& eborder);
      virtual void draw_round_rectangle(const ::f64_rectangle& rectangle, ::draw2d::pen* ppen, ::f64 radius);
      //void draw_round_rect(const ::f64_rectangle & rectangle, ::draw2d::pen * ppen, const ::f64_point & point, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::f64_rectangle & rectangle, ::draw2d::pen * ppen, ::i32 radius, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::f64_rectangle & rectangle, ::draw2d::pen * ppen, ::i32 radius, const ::e_border & eborder = e_border_all);

      //void draw_round_rect(const ::f64_rectangle & rectangle, const ::color::color & color, ::f64 radius, ::f64 width, const ::e_border & eborder = e_border_all);
      //void draw_round_top_left(const ::f64_rectangle & rectangle, const ::color::color & color, ::i32 radius, ::i32 width, const ::e_border & eborder = e_border_all);
      //void draw_round_bottom_right(const ::f64_rectangle & rectangle, const ::color::color & color, ::i32 radius, ::i32 width, const ::e_border & eborder = e_border_all);


      virtual void draw_stock_icon(const ::f64_rectangle& rectangle, enum_stock_icon estockicon);


      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          ::f64_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the brush
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color, ::f64 radius);

      //=============================================================================
      //
      // fill_round_rectd()
      //
      // Purpose:     Fills a rounded rectdangle with a solid brush.  Draws the border
      //          first then fills in the rectdangle.
      //
      // Parameters:  pGraphics  - [in]   pointer to the Graphics device
      //          pBrush      - [in]  pointer to a Brush
      //          ::f64_rectangle        - [in]   Rect that defines the round rectdangle boundaries
      //          color    - [in]   Color value for the border (needed in case the
      //                         brush is a type other than solid)
      //          radius      - [in]  radius of the rounded corner
      //
      // Returns:     None
      //
      virtual void fill_round_rectangle(const ::f64_rectangle& rectangle, ::draw2d::brush* pbrush, ::f64 radius);


      //void fill_round_rect(const ::f64_rectangle & rectangle, ::draw2d::brush * pbrush, const ::f64_point & point);


      //virtual void round_rectangle(const ::f64_rectangle & rectangle, ::f64 radius);

      virtual ::i32 _DrawText(const ::scoped_string & scopedstr, const ::f64_rectangle& rectangle, const ::e_align& ealign = e_align_top_left, const ::e_draw_text& edrawtext = e_draw_text_none, ::write_text::font* pfontUnderline = nullptr);

      virtual void debug();




      //virtual ::f32 nanosvg_distPtSeg(::f32 x, ::f32 y, ::f32 px, ::f32 py, ::f32 qx, ::f32 qy);
      //virtual void nanosvg_cubicBez(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::f32 x3, ::f32 y3, ::f32 x4, ::f32 y4, ::f32 tol, ::i32 level);
      //virtual void nanosvg_drawPath(::f32* pts, ::i32 npts, ::i8 closed, ::f32 tol, const ::color::color& color);
      //virtual void nanosvg_drawControlPts(::f32* pts, ::i32 npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, ::i32 x, ::i32 y, ::i32 w, ::i32 h);
      // virtual void nanosvg_resizecb(::i32 width, ::i32 height, ::i32 x, ::i32 y, ::i32 w, ::i32 h);

      virtual void nanosvg(const ::scoped_string & scopedstr, ::i32 x, ::i32 y, ::i32 w, ::i32 h);

      virtual void is_valid_update_window_thread();

      //virtual void set_current_point(::f64 x, ::f64 y); // { return set_current_point(::f64_point(x, y)); }
      //inline void set_current_point(::f64 x, ::f64 y) { return set_current_point(::f64_point(x, y)); }

      //inline void line_to(::f64 x, ::f64 y) { return line_to(::f64_point(x, y)); }
      //inline void line_to(::f64 x, ::f64 y) { return line_to(::f64_point(x, y)); }
      //virtual void line_to(::f64 x, ::f64 y);// { return line_to(::f64_point(x, y)); }

      //inline void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) { return draw_line(::f64_point(x1,y1), ::f64_point(x2, y2)); }
      //inline void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen) { return draw_line(::f64_point(x1, y1), ::f64_point(x2, y2), ppen); }

      ///virtual void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2); // { return draw_line(::f64_point(x1, y1), ::f64_point(x2, y2)); }
      //virtual void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen); // { return draw_line(::f64_point(x1, y1), ::f64_point(x2, y2), ppen); }

      //inline void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) { return draw_line(::f64_point(x1, y1), ::f64_point(x2, y2)); }
      //inline void draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen) { return draw_line(::f64_point(x1, y1), ::f64_point(x2, y2), ppen); }

      //inline void rectdangle_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) { return rectdangle(::f64_rectangle(x1, y1, x2, y2)); }
      //inline void rectdangle_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2); // { return rectdangle(::f64_rectangle(x1, y1, x2, y2)); }

      //inline void rectdangle_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy) { return rectdangle(f64_rectangle_dimension(x, y, cx, cy)); }
      //inline void rectdangle_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy); // { return rectdangle(rectdd_dim(x, y, cx, cy)); }

      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen) { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2), ppen); }
      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2); // { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2)); }
      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppen); // { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2), ppen); }

      //inline void draw_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy) { return draw_rectangle(f64_rectangle_dimension(x, y, cx, cy)); }
      //inline void draw_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy, ::draw2d::pen * ppen) { return draw_rectangle(f64_rectangle_dimension(x, y, cx, cy), ppen); }
      //inline void draw_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy); // { return draw_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void draw_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::draw2d::pen * ppen); // { return draw_rectangle(rectdd_dim(x, y, cx, cy), ppen); }

      //inline void fill_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2); // { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::brush * pbrush); // { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2), pbrush); }
      //inline void fill_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2); // { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2)); }
      //inline void fill_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::brush * pbrush); // { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2), pbrush); }

      //inline void fill_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy) { return fill_rectangle(f64_rectangle_dimension(x, y, cx, cy)); }
      //inline void fill_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy, ::draw2d::brush * pbrush) { return fill_rectangle(f64_rectangle_dimension(x, y, cx, cy), pbrush); }
      //inline void fill_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy); // { return fill_rectangle(rectdd_dim(x, y, cx, cy)); }
      //inline void fill_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::draw2d::brush * pbrush); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), pbrush); }

      //inline void polygon(i32_point_array & pointa) { return polygon(pointa.data(), pointa.size()); }
      inline void polygon(f64_point_array_base &pointa) { return polygon(pointa.data(), pointa.size()); }
      //inline void draw_polygon(i32_point_array & pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      inline void draw_polygon(f64_point_array_base &pointa) { return draw_polygon(pointa.data(), pointa.size()); }
      //inline void fill_polygon(i32_point_array & pointa) { return fill_polygon(pointa.data(), pointa.size()); }
      inline void fill_polygon(f64_point_array_base& pointa) { return fill_polygon(pointa.data(), pointa.size()); }

      //inline void fill_solid_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy, const ::color::color & color) { return fill_rectangle(f64_rectangle_dimension(x, y, cx, cy), color); }
      //inline void fill_solid_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, const ::color::color & color); // { return fill_rectangle(rectdd_dim(x, y, cx, cy), color); }

      //inline void fill_solid_rectd_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color & color) { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2), color); }
      //inline void fill_solid_rectd_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color & color) { return fill_rectangle(::f64_rectangle(x1, y1, x2, y2), color); }

      //inline void draw_3drect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(f64_rectangle_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(f64_rectangle_dimension(x, y, cx, cy), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_dim(::f64 x, ::f64 y, ::i32 cx, ::i32 cy, const ::color::color& color) { return draw_rectangle(f64_rectangle_dimension(x, y, cx, cy), color); }
      //inline void draw_rect_dim(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, const ::color::color& color) { return draw_rectangle(f64_rectangle_dimension(x, y, cx, cy), color); }

      //inline void draw_3drect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(::f64_rectangle(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_3drect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color& colorTopLeft, const ::color::color& colorBottomLeft) { return draw_inset_3d_rectangle(::f64_rectangle(x1, y1, x2, y2), colorTopLeft, colorBottomLeft); }
      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color& color) { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2), color); }
      //inline void draw_rect_coord(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, const ::color::color& color) { return draw_rectangle(::f64_rectangle(x1, y1, x2, y2), color); }


   //protected:

     // friend class savedc;
      virtual ::i32 save_graphics_context();
      virtual void restore_graphics_context(::i32 nSavedContext);


      virtual bool _set(::geometry2d::item * pitem);
      virtual bool _set(const ::draw2d::enum_item & eitem);


      virtual bool _set(const ::f64_arc & arc, const ::pointer<::draw2d::region>& pregion);
      //virtual bool _set(const ::line & line);
      //virtual bool _set(const ::lines & lines);
      virtual bool _set(const ::f64_rectangle & rectangle, const ::pointer<::draw2d::region>& pregion);
      virtual bool _set(const ::f64_ellipse & ellipse, const ::pointer<::draw2d::region>& pregion);
      virtual bool _set(const ::f64_polygon_base & polygon, const ::pointer<::draw2d::region>& pregion);
      virtual bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::region>& pregion);
      virtual bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::region>& pregion);


      virtual bool _set(const ::f64_arc & arc, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::f64_line & line, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::f64_lines & lines, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::f64_rectangle & rectangle, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::f64_ellipse & ellipse, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::f64_polygon_base & polygon, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::write_text::text_out & textout, const ::pointer<::draw2d::path>& ppath);
      virtual bool _set(const ::write_text::draw_text & drawtext, const ::pointer<::draw2d::path>& ppath);


      virtual bool _set(const ::f64_arc & arc);
      virtual bool _set(const ::f64_line & line);
      virtual bool _set(const ::f64_lines & lines);
      virtual bool _set(const ::f64_rectangle & rectangle);
      virtual bool _set(const ::f64_ellipse & ellipse);
      virtual bool _set(const ::f64_polygon_base & polygon);
      virtual bool _set(const ::write_text::text_out & textout);
      virtual bool _set(const ::write_text::draw_text & drawtext);


   };


   class CLASS_DECL_AURA save_context
   {
   public:


      graphics* m_pgraphics;
      ::i32                     m_iSavedDC;

      ::f64_size              m_sizeScaling;
      ::f64_point             m_pointOrigin;
      ::geometry2d::matrix    m_matrix;

      save_context(graphics* graphics);
      ~save_context();


   };

   
   class CLASS_DECL_AURA graphics_context_interface :
      virtual public ::particle
   {
   public:
   
      virtual void _context_lock() = 0;
      virtual void _context_unlock() = 0;

   };


   class CLASS_DECL_AURA graphics_context :
      virtual public ::particle
   {
   public:
      
      
      ::pointer < ::draw2d::graphics > m_pgraphics;
      ::pointer < ::draw2d::graphics_context_interface > m_pgraphicscontextinterface;
      ::pointer < ::graphics::buffer_item > m_pbufferitem;
      
      
      graphics_context()
      {
         
         
      }
      
      
      ~graphics_context()
      {
         
         m_pgraphics.release();
         
         if(m_pgraphicscontextinterface)
         {
            
            m_pgraphicscontextinterface->_context_unlock();
            
         }
         
      }
   

      void insert_graphics_and_context(::draw2d::graphics_context_interface * pinterface)
      {
         
         m_pgraphicscontextinterface = pinterface;
       
         m_pgraphicscontextinterface->_context_lock();
         
      }


   };



   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_graphics();
   //CLASS_DECL_AURA ::draw2d::graphics_pointer create_memory_graphics();

} // namespace draw2d


//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::f64_size & size);
//CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const ::f64_point & point);



//CLASS_DECL_AURA PFN_factory ([a-z0-9_]+)_factory(::factory::factory * pfactory);

//CLASS_DECL_AURA void ([a-z0-9_]+)_factory(PFN_factory pfnfactoryDraw2d);
