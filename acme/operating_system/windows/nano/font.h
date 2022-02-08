//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace windows
{


   class CLASS_DECL_ACME nano_font :
      virtual public ::nano_font,
      virtual public nano_object
   {
   public:


      nano_font();
      ~nano_font() override;


      void update(::nano_device * pnanodevice) override;


      static HFONT _create_point_font(int nPointSize, const char * pszFaceName, bool bBold, HDC hdc, LOGFONTW * plf);
      static HFONT _create_point_font_indirect(LOGFONTW * pLogFont, HDC hdc);

   };


} // namespace windows



