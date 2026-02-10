#pragma once


#include "color_filter.h"


#include "api.h"


#include "aura/graphics/write_text/write_text.h"


//#include "aura/graphics/image/_image.h"


#include "brush.h"


#include "graphics.h"


#include "aura/platform/system.h"


class save_image;


namespace draw2d
{


   class CLASS_DECL_AURA draw2d :
      virtual public ::platform::department
   {
   public:



      static double g_dEmboss;
      void * m_pimpl;

      int_map < ::pointer<memory >>m_alpha_spread__24CC_filterMap;
      int_map < ::pointer<memory >>m_alpha_spread__32CC_filterMap;


      ::pointer<class ::draw2d::api>                           m_papi;


      ::pointer<::write_text::write_text>                     m_pwritetext;


      critical_section                                         m_criticalsectionObjectList;
      numeric_array_base < ::draw2d::object * >                m_objecta;

      critical_section                                         m_criticalsectionImageList;
      ::pointer<::image::image_array>                          m_pimagea;

      critical_section                                         m_criticalsectionGraphicsContextList;
      pointer_array < graphics >                               m_graphicsa;


      draw2d();
      ~draw2d() override;


      virtual void initialize(::particle * pparticle) override;

   protected:
      friend class ::draw2d::object;
      void add_object(::draw2d::object * pobject);
      void erase_object(::draw2d::object * pobject);
      friend class ::image::image;
      void add_image(::image::image *pimage);
      void erase_image(::image::image *pimage);
      friend class graphics;
      void add_graphics(graphics * pimage);
      void erase_graphics(graphics * pimage);
      //::pointer< ::mutex > get_object_list_mutex();
      //::pointer< ::mutex > get_image_list_mutex();
      //::pointer< ::mutex > get_graphics_context_list_mutex();

   public:

      //virtual void on_before_create_window(::windowing::window* pwindow);
      //virtual void on_create_window(::windowing::window * pwindow);

      void clear_all_objects_os_data();

      void clear_object_list_os_data();
      void clear_image_list_os_data();
      void clear_graphics_context_list_os_data();




      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;



      virtual graphics_pointer create_graphics(::draw2d::host * pdraw2dhost);

      virtual graphics_pointer create_memory_graphics(::draw2d::host * pdraw2dhost);

      virtual brush_pointer create_solid_brush(const ::color::color & color);

      virtual class api & api();

      virtual class ::write_text::write_text * write_text();


      virtual bool graphics_context_supports_single_buffer_mode();
      virtual bool graphics_context_does_full_redraw();

      //#ifdef WINDOWS
        //    ::draw2d_direct2d::plugin * direct2d();
      //#endif


      virtual void initialize_write_text();
      virtual ::pointer<::factory::factory>& write_text_factory();


      virtual void term_instance() override;


      virtual string write_text_get_default_implementation_name();

      virtual void embossed_text_out(
         ::draw2d::graphics_pointer & pgraphics,
         const ::int_rectangle & rectangle,
         const ::scoped_string & scopedstrText,
         ::image::fastblur & blur,
         ::image::image_pointer & imageBlur,
         ::write_text::font * pfont,
         const ::e_align & ealign,
         const ::e_draw_text & edrawtext,
         const ::color::color & colorText,
         const ::color::color & colorGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
         const ::color_filter & colorfilter = nullptr);


      void emboss_predicate(
         ::draw2d::graphics_pointer & pgraphics,
         const ::int_rectangle & rectangle,
         const ::function < void(::draw2d::graphics *) > & functionDraw,
         ::image::fastblur & blur,
         ::image::image_pointer & pimageBlur,
         ::color::color crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
                            const ::color_filter & colorfilter = nullptr);


      virtual void alpha_spread__24CC(unsigned char * pbDest, int xDest, int yDest, int wDest, int cx, int cy, unsigned char * pbSrc, int ySrc, int xSrc, int wSrc, unsigned char bMin, int iRadius);

      virtual bool channel_spread__32CC(::image::image *pimageDst, ::image::image *pimageSrc, int iChannel, int iRadius, const ::color::color & colorSpreadSetColor);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);


      [[nodiscard]] virtual bool lock_device();
      virtual void unlock_device();


      virtual void adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle);


   };


} // namespace draw2d



