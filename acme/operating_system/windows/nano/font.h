//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/nano/font.h"
#include "object.h"


namespace windows
{


   class CLASS_DECL_ACME nano_font :
      virtual public ::nano_font,
      virtual public nano_object
   {
   public:

      //CreatableFromBase(nano_font, ::nano_font);


      nano_font();
      ~nano_font() override;


      void update(::nano_device * pnanodevice) override;


      static HFONT _create_point_font(int nPointSize, const ::scoped_string & scopedstrFaceName, bool bBold, HDC hdc, LOGFONTW * plf);
      static HFONT _create_point_font_indirect(LOGFONTW * pLogFont, HDC hdc);

   };


} // namespace windows



