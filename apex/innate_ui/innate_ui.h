// Created by camilo on 2024-09-13 01:38 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace innate_ui
{

   class CLASS_DECL_APEX innate_ui :
      virtual public ::acme::department
   {
   public:


      ::pointer_array < window > m_windowa;

      innate_ui();
      ~innate_ui() override;
      
      
      void on_initialize_particle() override;
      
      virtual void add_top_level_window(window * pwindow);
      void main_post(const ::procedure & procedure) override;
      void main_send(const ::procedure & procedure) override;


      virtual ::pointer < ::innate_ui::icon > innate_ui_icon(const ::payload & payloadFile, const ::size_i32 & size);


   };


} // namespace innate_ui



