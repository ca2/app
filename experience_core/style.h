#pragma once

namespace experience
{


   namespace core
   {



   class CLASS_DECL_APP_EXPERIENCE_CORE style:
      virtual public ::base::style
   {
   public:



      style();
      virtual ~style();


      //virtual i64 add_ref(OBJECT_REF_DEBUG_PARAMS) override
      //{

      //   return ::object::add_ref(OBJECT_REF_DEBUG_ARGS);

      //}

      //virtual i64 dec_ref(OBJECT_REF_DEBUG_PARAMS) override
      //{

      //   return ::object::dec_ref(OBJECT_REF_DEBUG_ARGS);

      //}


      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & brushText) override;
      bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab) override;

      virtual ::color::color get_color(const ::user::interaction * pinteraction, ::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const override;

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;



   };



   } // namespace core


} // namespace experience



