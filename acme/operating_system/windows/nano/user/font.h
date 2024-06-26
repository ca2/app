//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/user/font.h"
#include "object.h"


namespace windows
{

   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_ACME font :
            virtual public ::nano::user::font,
            virtual public object
         {
         public:

            //CreatableFromBase(::nano::user::font, ::nano::user::font);


            font();
            ~font() override;


            void update(::nano::user::device* pnanodevice) override;


            static HFONT _create_point_font(int nPointSize, const ::scoped_string& scopedstrFaceName, bool bBold, HDC hdc, LOGFONTW* plf);
            static HFONT _create_point_font_indirect(LOGFONTW* pLogFont, HDC hdc);

         };



      } // namespace user


   } // namespace nano



} // namespace windows



