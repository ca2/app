#pragma once


namespace experience
{


   namespace anthill
   {


      class CLASS_DECL_APP_EXPERIENCE_ANTHILL style:
         virtual public ::base::style
      {
      public:




         style();
         ~style() override;

         virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {

            return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

         }

         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
         {

            return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

         }


         virtual void initialize_theme();


         virtual ::color::color get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate) const override;


   //      virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::interaction * pframewindow) override;
         //    virtual bool get_font(::write_text::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
         //  virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::interaction * pframewindow) override;


   //      virtual bool on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow) override;

         bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
         void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & brushText) override;
         bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;

         virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar) override;
         virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
         virtual void _001DrawAnthillToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
         virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

   //      virtual bool get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
   //      virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


      };


   } // namespace anthill


} // namespace experience



