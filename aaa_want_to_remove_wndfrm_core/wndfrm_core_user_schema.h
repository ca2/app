#pragma once


namespace experience_core
{


   class CLASS_DECL_APP_CORE_EXPERIENCE_CORE user_style:
      virtual public ::user::style_simple_impl
   {
   public:



      user_style(::object * pobject);
      virtual ~user_style();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {

         return ::object::add_ref(OBJ_REF_DBG_ARGS);

      }

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {

         return ::object::dec_ref(OBJ_REF_DBG_ARGS);

      }

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab);
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,LPCRECT lpcrect,::draw2d::brush_pointer & brushText);
      bool _001OnTabLayout(::user::tab * ptab);

      virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pinteraction) override;

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, simple_scroll_bar * pbar);

   };


} // namespace experience_rootkiller


