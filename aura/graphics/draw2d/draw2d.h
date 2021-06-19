#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA draw2d  :
      virtual public ::acme::department
   {
   public:


      static double g_dEmboss;
      void* m_pimpl;

      i32_map < __pointer(memory) > m_alpha_spread__24CC_filterMap;
      i32_map < __pointer(memory) > m_alpha_spread__32CC_filterMap;


      __pointer(class ::draw2d::api)                           m_papi;

      //::mutex                                        m_pmutexFont;
//#ifdef WINDOWS
  //    __composite(::draw2d_direct2d::plugin)                     m_pplugin;
//#endif

      __pointer(::write_text::write_text)                      m_pwritetext;



      draw2d();
      virtual ~draw2d();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init() override;
      virtual ::e_status init1() override;

      virtual ::e_status term() override;

      virtual ::e_status finalize() override;


      __pointer(save_image) new_save_image(const ::payload& varFile, const ::payload& varOptions);


      virtual graphics_pointer create_graphics();

      virtual graphics_pointer create_memory_graphics();

      virtual class api & api();

      inline class ::write_text::write_text * write_text() { return m_pwritetext; }

//#ifdef WINDOWS
  //    ::draw2d_direct2d::plugin * direct2d();
//#endif

      

      e_format file_extension_to_format(const ::payload & varFile);
      e_format text_to_format(string str);
      
      virtual ::e_status initialize_write_text();
      virtual ::e_status write_text_factory_exchange(::factory_map * pfactorymap);


      virtual ::e_status term_instance() override;


      virtual string write_text_get_default_library_name();

      virtual bool embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rectangle_i32 & rectangle,
      string strText,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      ::write_text::font * pfont,
      const ::e_align & ealign,
      const ::e_draw_text & edrawtext,
      color32_t crText,
      color32_t crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      const ::color_filter & colorfilter = nullptr);


      template < typename PRED >
      bool emboss_predicate(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rectangle_i32 & rectangle,
      PRED pred,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      color32_t crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      const color_filter & colorfilter = nullptr);

      virtual void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin, i32 iRadius);

      virtual bool channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, color32_t crSpreadSetColor);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);


   };


} // namespace draw2d


