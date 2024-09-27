//
// Created by camilo on 2024-09-13 13:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/user.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_ACME user :
            virtual public ::nano::user::user
         {
         public:


            user();
            ~user() override;


            //virtual void _defer_show_system_menu(HWND hwnd, HMENU * phmenuSystem, const ::point_i32 & pointAbsolute);
            //virtual bool _on_command(LRESULT & lresult, HWND hwnd, WPARAM wparam, LPARAM lparam);
            //virtual void _erase_minimize_box_style(HWND hwnd);

         };



      } // namespace user


   } // namespace nano

} // namespace windows



