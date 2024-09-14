// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


namespace innate_ui
{

   class CLASS_DECL_APEX window :
      virtual public ::object
   {
   public:


      ::pointer_array < window > m_childa;



      window();
      ~window() override;

      virtual void create();
      virtual void create_child(window * pwindowParent);
      virtual void destroy_window();

      //virtual void set_size(const ::size_i32 & size);
      
      virtual void center();
      virtual void show();
      virtual void hide();


      virtual void set_text(const ::scoped_string & scopedstr);

      virtual void fit();
      virtual void set_position(const ::point_i32 & point);
      virtual void set_size(const ::size_i32 & size);
      virtual void adjust_for_client_size(const ::size_i32 & size);

      ::innate_ui::innate_ui * innate_ui();

      virtual void set_icon(icon * picon);

      virtual void post(const ::procedure & procedure);
      virtual void sync(const ::procedure & procedure);

      virtual void defer_show_system_menu(const ::point_i32 & pointAbsolute);

   
   };


} // namespace innate_ui



