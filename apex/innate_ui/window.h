// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


namespace innate_ui
{


   class innate_ui;
   class icon;


   class CLASS_DECL_APEX window :
      virtual public ::particle
   {
   public:


      window *                         m_pwindowParent;
      ::pointer_array < window >       m_childa;
      procedure_array                  m_procedureaLayoutChildSize;
      procedure_array                  m_procedureaLayoutChildPosition;
      procedure_array                  m_procedureaLayoutParent;


      window();
      ~window() override;

      virtual void create();
      virtual void create_child(window * pwindowParent);
      virtual void destroy_window();

      virtual void center();
      virtual void show();
      virtual void hide();
      virtual void show_front(::user::activation_token * puseractivationtoken);


      virtual void set_text(const ::scoped_string & scopedstr);

      virtual void fit();
      virtual void set_position(const ::int_point & point);
      virtual void set_size(const ::int_size & size);
      virtual void adjust_for_client_size(const ::int_size & size);

      ::innate_ui::innate_ui * innate_ui();

      virtual void set_icon(icon * picon);

      void _main_post(const ::procedure & procedure) override;
      void _main_send(const ::procedure & procedure) override;

      virtual void defer_show_system_menu(::user::mouse * pmouse);

   
   };


} // namespace innate_ui



