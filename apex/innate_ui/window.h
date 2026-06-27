// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once



#include "acme/windowing/window.h"


namespace innate_ui
{


   class innate_ui;
   class icon;


   class CLASS_DECL_APEX window :
      virtual public ::acme::windowing::window
   {
   public:


      ::f64 m_dFontSizeEm = 1.0;
      ::i32 m_iFontWeight = 400;
      window *                         m_pwindowParent;
      ::pointer_array < window >       m_childa;
      ::procedure_array                m_procedureaLayoutChildSize;
      ::procedure_array                m_procedureaLayoutChildPosition;
      ::procedure_array                m_procedureaLayoutParent;


      window();
      ~window() override;

      virtual void create();
      virtual void create_child(window * pwindowParent);
      void destroy_window() override;

      virtual void center();
      virtual void show();
      virtual void hide();
      virtual void show_front(::user::activation_token * puseractivationtoken);


      virtual void set_text(const ::scoped_string & scopedstr);

      virtual void fit();
      virtual ::f64 get_scale_factor();
      void set_position(const ::i32_point & point) override;
      void set_size(const ::i32_size & size) override;
      virtual void adjust_for_client_size(const ::i32_size & size);

      ::innate_ui::innate_ui * innate_ui();

      virtual void set_icon(icon * picon);
      virtual void set_icon_path(const ::scoped_string & scopedstr, const ::i32_size & size);
      void main_post(const ::procedure & procedure) override;
      void main_send(const ::procedure & procedure) override;

      virtual void defer_show_system_menu(::user::mouse * pmouse);


      void on_size() override;
      
   
   };


} // namespace innate_ui



