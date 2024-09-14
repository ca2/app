// Created by camilo on 2024-09-13 00:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX still :
      virtual public ::innate_ui::window
   {
   public:


      still();
      ~still() override;


      virtual void create_icon_still(window * pwindowParent);

      //void _create_window(window * pwindowParent) override;
      //virtual void create_child(window * pwindowParent);


      //virtual void set_text(const ::scoped_string & scopedstr);

      //virtual void fit();


   };


} // namespace innate_ui



