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


   class fastblur;


   class CLASS_DECL_AURA draw2d :
      virtual public ::acme::department
   {
   public:


      static double g_dEmboss;
      void * m_pimpl;

      i32_map < ::pointer<memory >>m_alpha_spread__24CC_filterMap;
      i32_map < ::pointer<memory >>m_alpha_spread__32CC_filterMap;


      ::pointer<class ::draw2d::api>                           m_papi;


      ::pointer<::write_text::write_text>                     m_pwritetext;


      critical_section                                         m_criticalsectionObjectList;
      pointer_array < ::draw2d::object >                        m_objecta;

      critical_section                                         m_criticalsectionImageList;
      ::pointer<image_array>                                  m_pimagea;

      critical_section                                         m_criticalsectionGraphicsContextList;
      pointer_array < graphics >                                m_graphicsa;


      draw2d();
      ~draw2d() override;


      virtual void initialize(::object * pobject) override;

   protected:
      friend class ::draw2d::object;
      void add_object(::draw2d::object * pobject);
      void erase_object(::draw2d::object * pobject);
      friend class ::image;
      void add_image(::image * pimage);
      void erase_image(::image * pimage);
      friend class graphics;
      void add_graphics(graphics * pimage);
      void erase_graphics(graphics * pimage);
      //::mutex * get_object_list_mutex();
      //::mutex * get_image_list_mutex();
      //::mutex * get_graphics_context_list_mutex();

   public:



      void clear_all_objects_os_data();

      void clear_object_list_os_data();
      void clear_image_list_os_data();
      void clear_graphics_context_list_os_data();




      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;


      ::pointer<save_image>new_save_image(const ::payload & payloadFile, const ::payload & varOptions);


      virtual graphics_pointer create_graphics(::draw2d::host * pdraw2dhost);

      virtual graphics_pointer create_memory_graphics(::draw2d::host * pdraw2dhost);

      virtual class api & api();

      inline class ::write_text::write_text * write_text() { return m_pwritetext; }

      //#ifdef WINDOWS
        //    ::draw2d_direct2d::plugin * direct2d();
      //#endif



      enum_format file_extension_to_format(const ::payload & payloadFile);
      enum_format text_to_format(string str);

      virtual void initialize_write_text();
      virtual ::pointer<::factory::factory>& write_text_factory();


      virtual void term_instance() override;


      virtual string write_text_get_default_library_name();

      virtual void embossed_text_out(
         ::draw2d::graphics_pointer & pgraphics,
         const ::rectangle_i32 & rectangle,
         string strText,
         ::draw2d::fastblur & blur,
         ::image_pointer & imageBlur,
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
         const ::rectangle_i32 & rectangle,
         const ::function < void(::draw2d::graphics *) > & functionDraw,
         ::draw2d::fastblur & blur,
         ::image_pointer & pimageBlur,
         ::color::color crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
                            const ::color_filter & colorfilter = nullptr);


      virtual void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin, i32 iRadius);

      virtual bool channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, ::color::color crSpreadSetColor);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);


      virtual void lock_device();
      virtual void unlock_device();



   };


} // namespace draw2d



