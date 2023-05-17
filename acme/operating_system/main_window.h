// Created by camilo on 2023-04-15 19:23 <3ThomasBorregaardSorensen!!
#pragma once


namespace operating_system
{


   class application;


   class CLASS_DECL_ACME main_window :
      virtual public ::particle
   {
   public:


      main_window();
      ~main_window() override;


      virtual void from_application(application * papplication);

      virtual void post_close();

      virtual void post_application_exit();

      virtual ::string get_window_text(const ::iptr_array & idPath);
      virtual ::string indexed_get_window_text(const ::iptr_array & idPath);


   };


} // namespace operating_system



